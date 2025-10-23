/***********************************************************************
 * Header File:
 *    KNIGHT
 * Author:
*    <your name here>
 * Summary:
 *    The KNIGHT class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * KNIGHT
  * The knight, aka the "Horse"
  ***************************************************/
class Knight : public Piece
{
   public:
   Knight(const Position& pos, bool isWhite) : Piece(pos,   isWhite) { }
   Knight(int c, int r,        bool isWhite) : Piece(c, r,  isWhite) { }
   ~Knight() {                }
   PieceType getType()            const override { return KNIGHT; }
   void getMoves(std::set<Move>& moves, const Board& board) const override;
   void display(ogstream* pgout) const override;
   private:
   set <Move> getMovesNoslide(const Board& board,
                              const Delta deltas[],
                              int numDelta) const;
};
