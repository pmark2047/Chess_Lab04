/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    Peyton and Jackson
 * Summary:
 *    The Pawn class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Pawn::display(ogstream* pgout) const
{
   pgout->drawPawn(position, !isWhite());
}

/***************************************************
* PIECE : GEN MOVES NO SLIDE
*         From a list of deltas, find all the
*         possible moves
***************************************************/
set <Move> Pawn::getMovesNoslide(const Board &board,
                                   const Delta *deltas,
                                   int numDelta) const
{
   set <Move> moves;
   for (int i = 0; i < numDelta; i++)
   {
      Position posMove(position, deltas[i]);
      // capture if there is a piece at the end of the slide
      if (!posMove.isValid())
      {
         continue;
      }

      if (posMove.isValid() &&
          (board[posMove].isWhite() != fWhite || board[posMove] == SPACE))
      {
         Move move;
         move.setSrc(getPosition());
         move.setDes(posMove);
         move.setWhiteMove(isWhite());
         if (board[posMove] != SPACE)
            move.setCapture(board[posMove].getType());
         moves.insert(move);
      }
   }
   
   return moves;
}
/**********************************************
 * PAWN : Double Move
 *********************************************/
set <Move> Pawn::MovePawnDouble(set <Move> & moves, const Board & board) const
{
   if (!isMoved())
   {
      Position posMove(getPosition().getCol(), getPosition().getRow() + (isWhite() ? 2 : -2));
      Position posCheck(getPosition().getCol(), getPosition().getRow() + (isWhite() ? 1 : -1));
      
      if (board[posMove] == SPACE && board[posCheck] == SPACE)
      {
         Move move;
         move.setSrc(getPosition());
         move.setDes(posMove);
         move.setWhiteMove(isWhite());
         moves.insert(move);
      }
   }
   return moves;
}

/**********************************************
 * PAWN : ENPASSANT
 *********************************************/
set <Move> Pawn::MoveEnPassant(set <Move> & moves, const Board & board) const
{
   const int cDelta[] = { 1,-1 }; // right and left
   for (int i = 0; i < 2; i++)
   {
      Position posMove(getPosition().getCol() + cDelta[i],
                       getPosition().getRow() + (isWhite() ? 1 : -1));
      Position posKill(getPosition().getCol() + cDelta[i], getPosition().getRow());
      
      if (posMove.isValid() &&
          getPosition().getRow() == (isWhite() ? 4 : 3) &&
          board[posMove] == SPACE &&
          board[posKill] == PAWN &&
          board[posKill].isWhite() !=  isWhite() &&
          board[posKill].justMoved(board.getCurrentMove()))
      {
         Move move;
         move.setSrc(getPosition());
         move.setDes(posMove);
         move.setWhiteMove(isWhite());
         move.setCapture(board[posMove].getType());
         move.setEnPassant();
         moves.insert(move);
      }
   }
   return moves;
}
   

/**********************************************
 * PAWN : ATTACK
 *********************************************/
set <Move> Pawn::MovePawnAttack(set <Move> & moves, const Board & board) const
{
   const int cDelta[] = { 1,-1 }; // right and left
   for (int i = 0; i < 2; i++)
   {
      Position posMove(getPosition().getCol() + cDelta[i],
                       getPosition().getRow() + (isWhite() ? 1 : -1));
      if (posMove.isValid() &&
          board[posMove] != SPACE &&
          board[posMove].isWhite() != isWhite())
      {
         Move move;
         move.setSrc(getPosition());
         move.setDes(posMove);
         move.setWhiteMove(isWhite());
         move.setCapture(board[posMove].getType());
         
         // Do promotion if we are at the front rank
         if (posMove.getRow() == (isWhite() ? 7 : 0))
         {
            move.setPromote(PieceType::QUEEN);
         }
         moves.insert(move);
      }
   }
   return moves;
}

/**********************************************
 * PAWN : GET POSITIONS
 *********************************************/
void Pawn::getMoves(set <Move>& moves, const Board& board) const
{
   Position posMove(getPosition(), isWhite() ? ADD_R : SUB_R);
   
   if (posMove.isValid() &&
       board[posMove] == SPACE)
   {
      Move move;
      move.setSrc(getPosition());
      move.setDes(posMove);
      move.setWhiteMove(isWhite());
      
      // Do promotion if we are at the front rank
      if (posMove.getRow() == (isWhite() ? 7 : 0))
      {
         move.setPromote(PieceType::QUEEN);
      }
      
      moves.insert(move);
   }
   moves = MovePawnAttack(moves, board);
   moves = MoveEnPassant(moves, board);
   moves = MovePawnDouble(moves, board);
}
