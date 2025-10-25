/***********************************************************************
 * Header File:
 *    QUEEN
 * Author:
*    Peyton and Jackson
 * Summary:
 *    The QUEEN class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * QUEEN
  * The queen, aka the "Your Majesty"
  ***************************************************/
class Queen : public Piece
{
   public:
   Queen(const Position& pos, bool isWhite) : Piece(pos,   isWhite) { }
   Queen(int c, int r,        bool isWhite) : Piece(c, r,  isWhite) { }
   ~Queen() {                }
   PieceType getType()            const { return QUEEN; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
   private:
   set <Move> moveSlide(const Board & board, const Delta deltas[],
                                int numDelta) const;
};

