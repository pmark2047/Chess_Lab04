/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    Peyton and Jackson
 * Summary:
 *    The Rook class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Rook::display(ogstream* pgout) const
{
   pgout->drawRook(position, !isWhite());
}

/***************************************************
* PIECE : GEN MOVES NO SLIDE
*         From a list of deltas, find all the
*         possible moves
***************************************************/
set <Move> Rook::moveSlide(const Board & board,
                                   const Delta deltas[],
                                   int numDelta) const
{
   set <Move> moves;
   for (int i = 0; i < numDelta; i++)
   {
      Position posMove(getPosition(), deltas[i]);
      
      // slide throught the blank spaces
      for(;
          posMove.isValid() && board[posMove] == SPACE;
          posMove += deltas[i])
      {
         Move move;
         move.setSrc(getPosition());
         move.setDes(posMove);
         move.setWhiteMove(isWhite());
         moves.insert(move);
      }
      
      // capture if there is a piece at the end of the slide
      if (posMove.isValid() && board[posMove].isWhite() != isWhite() && board[posMove] != SPACE)
      {
         Move move;
         move.setSrc(getPosition());
         move.setDes(posMove);
         move.setWhiteMove(isWhite());
         move.setCapture(board[posMove].getType());
         moves.insert(move);
      }
   }
   
   return moves;
}
/**********************************************
 * ROOK : GET POSITIONS
 *********************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
   // Rook
   const Delta delta[] =
   {
               {-1, 0},
               {1, 0},
               {0, -1},
               {0, 1}
   };
   
   moves = moveSlide(board, delta, sizeof(delta) / sizeof(delta[0]));

}
