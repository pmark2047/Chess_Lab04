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
   friend class TestKing;

   // constructor
   Move();
   Move(const Move & rhs) : promote(SPACE), capture(SPACE), isWhite(true), moveType(MOVE)
   {
      *this = rhs;
   }

   Move(Position source, Position dest, MoveType moveType, PieceType capture)
   {
      this->source = source;
      this->dest = dest;
      this->moveType = moveType;
      this->capture = capture;

      int x1 = source.getCol();
      int y1 = source.getRow();
      int x2 = dest.getCol();
      int y2 = dest.getRow();

      string newText;
      char letter = letterDetermine();
      std::stringstream ss;

      if (letter != 'o')
      {
         ss << letterFromRow(x1) << y1 << letterFromRow(x2) << y2 << letter;
      }
      else
      {
         ss << letterFromRow(x1) << y1 << letterFromRow(x2) << y2;
      }

      text = ss.str();
   }
   Move(string move)
   {
      text = move;
      moveType = MOVE;
      int sRow = rowFromLetter(move[0]);
      int sCol = move[1] - '0';
      sCol -= 1;
      source.set(sRow, sCol);
      int dRow = rowFromLetter(move[2]);
      int dCol = move[3] - '0';
      dCol -= 1;
      dest.set(dRow, dCol);
      lastLetterDetermine(move[4]);
   }
   // getters
   string getText()              const { return text; };
   const Position & getDes()     const { return dest;    }
   const Position & getSrc()     const { return source;  }
   PieceType getPromotion()      const { return promote; }
   PieceType getCapture()        const { return capture; }
   bool getEnPassant()           const { return moveType == ENPASSANT;     }
   bool getCastleK()             const { return moveType == CASTLE_KING;   }
   bool getCastleQ()             const { return moveType == CASTLE_QUEEN;  }
   bool getWhiteMove()           const { return isWhite;    }
   Move::MoveType getMoveType()  const { return moveType;   }
   bool operator == (const Move & rhs) const;
   bool operator == (const string & rhs) const { return getText() == rhs;  }
   bool operator != (const string & rhs) const { return getText() != rhs;  }
   bool operator != (const Move & rhs) const { return !(*this == rhs);     }
   bool operator <  (const Move & rhs) const
   {
      return dest.getLocation() < rhs.dest.getLocation();
   }
   
   // setters
   void update()                       { text      = getText(); }
   void setCapture(PieceType pt)       { capture   = pt;          update(); }
   void setWhiteMove(bool f)           { isWhite   = f;           update(); }
   void setSrc(const Position & src)   { source    = src;         update(); }
   void setDes(const Position & des)   { dest      = des;         update(); }
   void setEnPassant()                 { moveType  = ENPASSANT;   update(); }
   void setPromote(PieceType pt)       { promote   = pt;          update(); }
   void setCastle(bool isKing)
   {
      moveType    = (isKing ? CASTLE_KING : CASTLE_QUEEN);
      update();
   }
   
   // for file I/O though only file input is currently implemented
   friend ostream & operator << (ostream & out, Move & rhs);
   friend istream & operator >> (istream & in,  Move & rhs);
   
   const Move & operator = (const Move & rhs) { return *this; }
   const Move & operator = (const string & s)
   {
      read(s);
      return *this;
   }
   const Move & operator = (const char * s)
   {
      read(string(s));
      return *this;
   }

private:
   
   void read(const std::string & s) {  };
   char letterFromPieceType(PieceType pt) const;
   PieceType pieceTypeFromLetter(char letter) const;
   
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


