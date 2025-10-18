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

}
