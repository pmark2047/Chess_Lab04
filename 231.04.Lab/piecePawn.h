/***********************************************************************
 * Header File:
 *    PAWN
 * Author:
*    Peyton and Jackson
 * Summary:
 *    The Pawn class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * Pawn
  * The Pawn, aka the "Your Majesty"
  ***************************************************/
class Pawn : public Piece
{
   public:
   Pawn(const Position& pos, bool isWhite) : Piece(pos,   isWhite) { }
   Pawn(int c, int r,        bool isWhite) : Piece(c, r,  isWhite) { }
   ~Pawn() {                }
   PieceType getType()            const { return PAWN; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
   private:
   set <Move> getMovesNoslide(const Board& board,
                              const Delta deltas[],
                              int numDelta) const;
};

