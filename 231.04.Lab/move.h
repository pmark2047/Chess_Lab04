/***********************************************************************
 * Header File:
 *    MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#pragma once

#include <string>
#include <sstream>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type


class TestMove;
class TestBoard;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
public:
   enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

   friend TestMove;
   friend TestBoard;
   friend class TestKnight;

   // default constructor
   Move();

   // constructor w/Text
   Move(string move)
   {
      text = move;
      moveType = MOVE;
      source = (rowFromLetter(move[0]), move[1]);
       dest = (rowFromLetter(move[2]), move[3]);
      lastLetterDetermine(move[4]);
   }

   // constructor get Text
   Move(Position source, Position dest, MoveType moveType, PieceType capture)
   {
      this->source = source;
      this->dest = dest;
      this->moveType = moveType;
      this->capture = capture;

      int x1 = this->source.getRow();
      int y1 = this->source.getCol();
      int x2 = this->dest.getRow();
      int y2 = this->dest.getCol();

      string newText;
      char letter = letterDetermine();
      newText = x1 + y1 + x2 + y2 + letter;
      if (letter == ' ')
      {
         newText = x1 + y1 + x2 + y2;
      }

   }

private:
   char letterFromPieceType(PieceType pt);
   PieceType pieceTypeFromLetter(char letter);
   int rowFromLetter(char letter); // determines row from just letter
   void lastLetterDetermine(char letter);
   char letterDetermine();
   char letterFromRow(int row);

   Position  source;    // where the move originated from
   Position  dest;      // where the move finished
   PieceType promote;   // piece to be promoted to
   PieceType capture;   // did a capture happen this move?
   MoveType  moveType;  // what type of move is this?
   bool      isWhite;   // whose turn is it anyway?
   string    text;      // what is the textual version of the move?
};


