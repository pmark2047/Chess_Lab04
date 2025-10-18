/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE  = 32;   // number of pixels in a square by default

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
   int dRow;
   int dCol;
};

const Delta ADD_R = { 1, 0};
const Delta ADD_C = { 0,  1};
const Delta SUB_R = {-1,  0};
const Delta SUB_C = { 0, -1};


class PositionTest;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
   friend class PositionTest;
   friend class TestPosition;
   friend class TestMove;
   friend class TestKnight;
   friend class TestPiece;
   friend class TestBoard;
   friend class TestSpace;
   friend class Piece;
   friend class Move;
   friend class TestKing;
public:

   // Position :    The Position class can work with other positions,
   //               Allowing for comparisions, copying, etc.
   Position(const Position & rhs) { setCol(rhs.getCol()); setRow(rhs.getRow()); }
   Position() : colRow(0xff)      {              }
   bool isInvalid() const         { return !isValid(); }
   bool isValid()   const         { return (getCol() >= 0 && getCol() < 8) &&
                                           (getRow() >= 0 && getRow() < 8); }
   void setValid()                { colRow = 0x00; }
   void setInvalid()              { colRow = 0xFF; }
   bool operator <  (const Position & rhs) const { return colRow < rhs.colRow; }
   bool operator == (const Position & rhs) const { return colRow == rhs.colRow; }
   bool operator != (const Position & rhs) const { return colRow != rhs.colRow; }
   const Position & operator =  (const Position & rhs) { colRow = rhs.colRow;
                                                         return *this; }
   
   // Location : The Position class can work with locations, which
   //            are 0...63 where we start in row 0, then row 1, etc.
   Position(int location) : colRow(0xff) { }
   int getLocation() const               { return (getRow() * 8) + getCol(); }
   void setLocation(int location)        {           }

   
   // Row/Col : The position class can work with row/column,
   //           which are 0..7 and 0...7
   Position(int c, int r) : colRow(0x00)  { setCol(c); setRow(r); }
   virtual int getCol() const                     {
                                                   if (((colRow >> 4) & 0x0F ) >= 8||((colRow & 0x0F) >= 8))
                                                   {
                                                      return -1;
                                                   };
                                                   return (colRow >> 4) & 0x0F; }
   
   virtual int getRow() const                     {
                                                   if (((colRow >> 4) & 0x0F ) >= 8||((colRow & 0x0F) >= 8))
                                                   {
                                                      return -1;
                                                   };
                                                   return colRow & 0x0F; }
   
   void setRow(int r)                     { colRow = (colRow & 0xF0) | (r & 0x0F); }
   void setCol(int c)                     { colRow = (colRow & 0x0F) | (c & 0x0F) << 4; }
   void set(int c, int r)                 { colRow = (c & 0x0F) << 4 | (r & 0x0F); }

   // Text:    The Position class can work with textual coordinates,
   //          such as "d4"
   
   Position(const char * s) {
      int col = s[0] - 'a';
      int row = s[1] - '0' - 1;
      colRow = (col << 4) | row;
   }
   const Position & operator =  (const char     * rhs) {
                                                         int col = rhs[0] - 'a';
                                                         int row = (rhs[1] - '0') - 1;
                                                         colRow = (col << 4) | row;
                                                         return *this; }
   const Position & operator =  (const string   & rhs) {
                                                         int col = rhs[0] - 'a';
                                                         int row = (rhs[1] - '0') - 1;
                                                         colRow = (col << 4) | row;
                                                         return *this; }

   
   // Pixels:    The Position class can work with screen coordinates,
   //            a.k.a. Pixels, these are X and Y coordinates. Note that
   //            we need to scale them according to the size of the board.
   int getX()   const
   {
      return (int)((double)getCol() * getSquareWidth() + getSquareWidth());
   }
   int getY()   const
   {
      return (int)((double)getRow() * getSquareHeight() + getSquareHeight());
   }
   void setXY(double x, double y)
   {
      int newCol = (int)(x / getSquareWidth()) - 1;
      int rowBounds = (int)(y / getSquareHeight()) - 1;
      int newRow = 7 - rowBounds;
      if (newCol < 0 || newCol >= 8 || rowBounds < 0 || rowBounds >=8 )
      {
         if (newCol < 0 || newCol >= 8)
         {
            setInvalid();
         }else{
            setInvalid();
            setCol(newCol);
         }
         return;
      }
      setCol(newCol);
      setRow(newRow);
   }
   double getSquareWidth()  const { return squareWidth;  }
   double getSquareHeight() const { return squareHeight; }
   void setBoardWidthHeight(int widthBoard, int heightBoard)
   {
      if (widthBoard < 0 || heightBoard < 0)
         return;
      squareWidth  = (double)widthBoard / 10.0; // 8 squares + 2 spaces
      squareHeight = (double)heightBoard / 10.0;
   }

   // Delta:    The Position class can work with deltas, which are
   //           offsets from a given location. This helps pieces move
   //           on the chess board.
   Position(const Position & rhs, const Delta & delta) : colRow(0) { colRow = rhs.colRow;
                                                                     setCol(getCol() + delta.dCol);
                                                                     setRow(getRow() + delta.dRow);}
   void adjustRow(int dRow)   { setRow(getRow() + dRow);
      if (!(isValid())) {
         setInvalid();
         }
      }
                              
   void adjustCol(int dCol)   { setCol(getCol() + dCol);
      if (!(isValid())) {
         setInvalid();
         }
      }
   const Position & operator += (const Delta & rhs) { adjustRow(rhs.dRow);
                                                      adjustCol(rhs.dCol);
                                                      return *this; }
   Position operator + (const Delta & rhs) const { return *this; }

private:
   void set(uint8_t colRowNew) { }
   
   uint8_t colRow;
   static double squareWidth;
   static double squareHeight;
};


ostream & operator << (ostream & out, const Position & pos);
istream & operator >> (istream & in,  Position & pos);
      
