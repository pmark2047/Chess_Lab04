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
set <Move> Bishop::moveSlide(const Board & board,
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
   
   moves = moveSlide(board, delta, sizeof(delta) / sizeof(delta[0]));

}
