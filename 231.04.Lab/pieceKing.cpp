/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    Peyton and Jackson
 * Summary:
 *    The King class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void King::display(ogstream* pgout) const
{
   pgout->drawKing(position, !isWhite());
}

/***************************************************
* PIECE : GEN MOVES NO SLIDE
*         From a list of deltas, find all the
*         possible moves
***************************************************/
set <Move> King::getMovesNoslide(const Board &board,
                                   const Delta *deltas,
                                   int numDelta) const
{
   set <Move> moves;
   for (int i = 0; i < numDelta; i++)
   {
      Position posMove(getPosition(), deltas[i]);
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
/***************************************************
* KING : MOVE CASTLE KING
*         Perform a King-Side Castle
***************************************************/
set <Move> King::moveCastleKing(set <Move> & moves, const Board & board) const
{
   // only perform a king-side castle if we have not moved yet
   if (!isMoved())
   {
      assert(getPosition().getCol() == 4);
      assert(getPosition().getRow() == (isWhite() ? 0 : 7));
      
      // King side or short castle
      Position posSpace(5, getPosition().getRow());
      Position posMove(6, getPosition().getRow());
      Position posRook(7, getPosition().getRow());
      
      // Check the conditions
      if (board[posMove] == SPACE &&         // The move-to space is empty
          board[posSpace] == SPACE &&        // Space beside is empty
          board[posRook] == ROOK &&          // Rook is in the corner
          board[posRook].isMoved() == false)
      {
         Move move;
         move.setSrc(getPosition());
         move.setDes(posMove);
         move.setWhiteMove(isWhite());
         move.setCastle(true /*isKing*/);
         moves.insert(move);
      }
   }
   return moves;
}
/***************************************************
* KING : QUEEN SIDE CASTLE
*         Perform a Queen-Side Castle
***************************************************/
set <Move> King::moveCastleQueen(set <Move> & moves, const Board & board) const
{
   // only perform a king-side castle if we have not moved yet
   if (!isMoved())
   {
      assert(getPosition().getCol() == 4);
      assert(getPosition().getRow() == (isWhite() ? 0 : 7));
      
      // King side or short castle
      Position posSpace1(3, getPosition().getRow());
      Position posMove(2, getPosition().getRow());
      Position posSpace2(1, getPosition().getRow());
      Position posRook(0, getPosition().getRow());
      
      // Check the conditions
      if (board[posMove] == SPACE &&         // The move-to space is empty
          board[posSpace1] == SPACE &&       // Space beside is empty
          board[posSpace2] == SPACE &&       // Space beside is empty
          board[posRook] == ROOK &&          // Rook is in the corner
          board[posRook].isMoved() == false)
      {
         Move move;
         move.setSrc(getPosition());
         move.setDes(posMove);
         move.setWhiteMove(isWhite());
         move.setCastle(false /*isKing*/);
         moves.insert(move);
      }
   }
   return moves;
}
/**********************************************
 * KING : GET POSITIONS
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
   // the 8 possible positions relative to the current position
   const Delta delta[] =
   {
      {-1, 1}, { 0, 1}, { 1, 1},
      {-1, 0},          { 1, 0},
      {-1,-1}, { 0,-1}, { 1,-1}
   };
   
   moves = getMovesNoslide(board, delta, sizeof(delta) / sizeof(delta[0]));
   
   if (!isMoved())
   {
      Position startPos(4, isWhite() ? 0 : 7);
      if (position == startPos)
      {
         moves = moveCastleKing(moves, board);
         moves = moveCastleQueen(moves, board);
      }
   }
}
