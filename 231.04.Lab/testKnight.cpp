/***********************************************************************
 * Source File:
 *    TEST KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the knight
 ************************************************************************/

#include "testKnight.h"
#include "pieceKnight.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      



/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_blocked()
{
   BoardEmpty board;
   Knight knight(7, 7, false /*white*/);
   White white;
   knight.fWhite = true;
   knight.position.colRow = 0x34;
   board.board[2][6] = board.board[4][6] = &white;
   board.board[1][5] = board.board[5][5] = &white;
   board.board[1][3] = board.board[5][3] = &white;
   board.board[2][2] = board.board[4][2] = &white;
   set <Move> moves;

   knight.getMoves(moves, board);

   assertUnit(moves.size() == 0);

   board.board[2][6] = board.board[4][6] =
   board.board[1][5] = board.board[5][5] =
   board.board[1][3] = board.board[5][3] =
   board.board[2][2] = board.board[4][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_capture()
{
   BoardEmpty board;
   Knight knight(7, 7, false /*white*/);
   Black b1(PAWN), b2(PAWN), b3(PAWN), b4(PAWN), b5(PAWN), b6(PAWN), b7(PAWN), b8(PAWN);
   knight.fWhite = true;
   knight.position = 0x34;
   board.board[2][6] = &b1;
   board.board[4][6] = &b2;
   board.board[1][5] = &b3; 
   board.board[5][5] = &b4; 
   board.board[1][3] = &b5; 
   board.board[5][3] = &b6; 
   board.board[2][2] = &b7; 
   board.board[4][2] = &b8; 
   set <Move> moves;
   Move d5b6p, d5c7p, d5e7p, d5f6p, d5b4p, d5c3p, d5e3p, d5f4p;
   d5b6p.source.colRow = d5c7p.source.colRow = d5e7p.source.colRow =
   d5f6p.source.colRow = d5b4p.source.colRow = d5c3p.source.colRow =
   d5e3p.source.colRow = d5f4p.source.colRow = 0x34;
   d5b6p.capture = d5c7p.capture = d5e7p.capture = d5f6p.capture =
   d5b4p.capture = d5c3p.capture = d5e3p.capture = d5f4p.capture = PAWN;
   d5b6p.dest.colRow = 0x15;
   d5c7p.dest.colRow = 0x26;
   d5e7p.dest.colRow = 0x46;
   d5f6p.dest.colRow = 0x55;
   d5b4p.dest.colRow = 0x13;
   d5c3p.dest.colRow = 0x22;
   d5e3p.dest.colRow = 0x42;
   d5f4p.dest.colRow = 0x53;

   //excersize
   knight.getMoves(moves, board);

   //verify
   assertUnit(moves.size() == 8);   // many possible moves
   assertUnit(moves.find(d5b6p) != moves.end());
   assertUnit(moves.find(d5c7p) != moves.end());
   assertUnit(moves.find(d5e7p) != moves.end());
   assertUnit(moves.find(d5f6p) != moves.end());
   assertUnit(moves.find(d5b4p) != moves.end());
   assertUnit(moves.find(d5c3p) != moves.end());
   assertUnit(moves.find(d5e3p) != moves.end());
   assertUnit(moves.find(d5f4p) != moves.end());

   //TEARDOWN
   board.board[2][6] = nullptr;
   board.board[4][6] = nullptr;
   board.board[1][5] = nullptr;
   board.board[5][5] = nullptr;
   board.board[1][3] = nullptr;
   board.board[5][3] = nullptr;
   board.board[2][2] = nullptr;
   board.board[4][2] = nullptr;

}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       .   .         7
 * 6     .       .       6
 * 5        (n)          5
 * 4     .       .       4
 * 3       .   .         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_free()
{

   // SETUP
   BoardEmpty board;
   Knight knight(7, 7, false /*white*/);
   knight.fWhite = true;
   knight.position.colRow = 0x34;
   set <Move> moves;
   Move d5b6, d5c7, d5e7, d5f6, d5b4, d5c3, d5e3, d5f4;
   d5b6.source.colRow = d5c7.source.colRow = d5e7.source.colRow =
      d5f6.source.colRow = d5b4.source.colRow = d5c3.source.colRow =
      d5e3.source.colRow = d5f4.source.colRow = 0x34;
   d5b6.capture = d5c7.capture = d5e7.capture = d5f6.capture =
   d5b4.capture = d5c3.capture = d5e3.capture = d5f4.capture = SPACE;
   d5b6.dest.colRow = 0x15;
   d5c7.dest.colRow = 0x26;
   d5e7.dest.colRow = 0x46;
   d5f6.dest.colRow = 0x55;
   d5b4.dest.colRow = 0x13;
   d5c3.dest.colRow = 0x22;
   d5e3.dest.colRow = 0x42;
   d5f4.dest.colRow = 0x53;
   // EXERCISE
   knight.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 8);   // many possible moves
   assertUnit(moves.find(d5b6) != moves.end());
   assertUnit(moves.find(d5c7) != moves.end());
   assertUnit(moves.find(d5e7) != moves.end());
   assertUnit(moves.find(d5f6) != moves.end());
   assertUnit(moves.find(d5b4) != moves.end());
   assertUnit(moves.find(d5c3) != moves.end());
   assertUnit(moves.find(d5e3) != moves.end());
   assertUnit(moves.find(d5f4) != moves.end());

   // TEARDOWN
   board.board[6][0] = nullptr; // white knight
   board.board[4][1] = nullptr; // black pawn
   board.board[5][2] = nullptr; // white pawn
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3             p   .   3
 * 2           P         2
 * 1              (n)    1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   Knight knight(7, 7, false /*white*/); // we will reset all this.
   knight.fWhite = true;
   knight.position.colRow = 0x60;
   board.board[6][0] = &knight;
   Black black(PAWN);
   board.board[4][1] = &black;
   White white(PAWN);
   board.board[5][2] = &white;
   set <Move> moves;
   Move g1e2p;
   g1e2p.source.colRow = 0x60;
   g1e2p.dest.colRow = 0x41;
   g1e2p.capture = PAWN;
   Move g1h3;
   g1h3.source.colRow = 0x60;
   g1h3.dest.colRow = 0x52;
   g1h3.capture = SPACE;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // many possible moves
   assertUnit(moves.find(g1e2p) != moves.end());
   assertUnit(moves.find(g1h3) != moves.end());

   // TEARDOWN
   board.board[6][0] = nullptr; // white knight
   board.board[4][1] = nullptr; // black pawn
   board.board[5][2] = nullptr; // white pawn

}

/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{

   // SETUP  
   const Knight knight(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = knight.getType();

   // VERIFY
   assertUnit(pt == KNIGHT);
}  // TEARDOWN
