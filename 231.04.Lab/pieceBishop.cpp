/***********************************************************************
 * Source File:
 *    BISHOP
 * Author:
 *    Peyton and Jackson
 * Summary:
 *    The Bishop class
 ************************************************************************/

#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Bishop::display(ogstream* pgout) const
{
   pgout->drawBishop(position, !isWhite());
}

/***************************************************
* PIECE : GEN MOVES NO SLIDE
*         From a list of deltas, find all the
*         possible moves
***************************************************/
set <Move> Bishop::getMovesNoslide(const Board &board,
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
 * Bishop : GET POSITIONS
 *********************************************/
void Bishop::getMoves(set <Move>& moves, const Board& board) const
{
   // Bishop
   const Delta delta[] =
   {
               {-1, -1},
               {1, 1},
               {-1, 1},
               {1, -1}
   };
   
   moves = getMovesNoslide(board, delta, sizeof(delta) / sizeof(delta[0]));

}
