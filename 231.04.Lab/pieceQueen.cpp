/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The Queen class
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Queen::display(ogstream* pgout) const
{
   pgout->drawQueen(position, !isWhite());
}

/***************************************************
* PIECE : GEN MOVES SLIDE
*         From a list of deltas, find all the
*         possible moves
***************************************************/
set <Move> Queen::moveSlide(const Board & board,
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
 * QUEEN : GET POSITIONS
 *********************************************/
void Queen::getMoves(set <Move>& moves, const Board& board) const
{
   // Queen
   const Delta delta[] =
   {
               {-1, -1},
               {1, 1},
               {-1, 1},
               {1, -1}, // Diagonal

               {-1, 0},
               {1, 0},
               {0, -1},
               {0, 1},   // Across or Up and Down
   };
   
   moves = moveSlide(board, delta, sizeof(delta) / sizeof(delta[0]));

}
