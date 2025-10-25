/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "testPawn.h"
#include "piecePawn.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      



 /*************************************
  * GET MOVES Simple White
  * White pawn in the middle of the board: b4b5
  *
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5     .               5
  * 4    (p)              4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestPawn::getMoves_simpleWhite()
{
   BoardEmpty board;
   Pawn pawn(7, 7, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x13;
   pawn.nMoves = 1;
   set <Move> moves;
   Move b4b5;
   b4b5.source.colRow = 0x13;
   b4b5.dest.colRow = 0x14;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 1);
   assertUnit(moves.find(b4b5) != moves.end());
}

/*************************************
 * GET MOVES Simple Black
 * Black pawn in the middle of the board: b4b3
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4    (P)              4
 * 3     .               3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
   BoardEmpty board;
   Pawn pawn(7, 7, true);
   pawn.fWhite = false;
   pawn.position.colRow = 0x13;
   pawn.nMoves = 1;
   set <Move> moves;
   Move b4b3;
   b4b3.source.colRow = 0x13;
   b4b3.dest.colRow = 0x12;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 1);
   assertUnit(moves.find(b4b3) != moves.end());
}


/*************************************
 * GET MOVES Initial Advance White
 * White pawn initial advance: b2b3, b2b4
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4     .               4
 * 3     .               3
 * 2    (p)              2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
   BoardEmpty board;
   Pawn pawn(7, 7, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x11;
   pawn.nMoves = 0;
   set <Move> moves;
   Move b2b3, b2b4;
   b2b3.source.colRow = b2b4.source.colRow = 0x11;
   b2b3.dest.colRow = 0x12;
   b2b4.dest.colRow = 0x13;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b2b3) != moves.end());
   assertUnit(moves.find(b2b4) != moves.end());
}

/*************************************
 * GET MOVES Initial Advance Black
 * Black pawn initial advance: c7c6, c7c5
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7      (P)            7
 * 6       .             6
 * 5       .             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
   BoardEmpty board;
   Pawn pawn(7, 7, true);
   pawn.fWhite = false;
   pawn.position.colRow = 0x26;
   pawn.nMoves = 0;
   set <Move> moves;
   Move c7c6, c7c5;
   c7c6.source.colRow = c7c5.source.colRow = 0x26;
   c7c6.dest.colRow = 0x25;
   c7c5.dest.colRow = 0x24;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 2);
   assertUnit(moves.find(c7c6) != moves.end());
   assertUnit(moves.find(c7c5) != moves.end());
}


/*************************************
 * GET MOVES Capture White
 * Double capture with b7 blocked: b6a7p, b6c7p
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7   P P P             7
 * 6    (p)              6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureWhite()
{
   BoardEmpty board;
   Pawn pawn(7, 7, false);
   Black black(PAWN);
   pawn.fWhite = true;
   pawn.position.colRow = 0x15;
   pawn.nMoves = 0;
   set <Move> moves;
   board.board[0][6] = &black;
   board.board[1][6] = &black;
   board.board[2][6] = &black;
   Move b6c7p, b6a7p;
   b6c7p.source.colRow = b6a7p.source.colRow = 0x15;
   b6c7p.capture = b6a7p.capture = PieceType::PAWN;
   b6a7p.dest.colRow = 0x06;
   b6c7p.dest.colRow = 0x26;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b6a7p) != moves.end());
   assertUnit(moves.find(b6c7p) != moves.end());

   board.board[0][6] = nullptr;
   board.board[1][6] = nullptr;
   board.board[2][6] = nullptr;
}


/*************************************
 * GET MOVES Capture Black
 * Double capture with b5 blocked: b6a5p, b6c5p
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6    (P)              6
 * 5   p p p             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureBlack()
{
   BoardEmpty board;
   Pawn pawn(7, 7, true);
   White white(PAWN);
   pawn.fWhite = false;
   pawn.position.colRow = 0x15;
   pawn.nMoves = 1;
   set <Move> moves;
   board.board[0][4] = &white;
   board.board[1][4] = &white;
   board.board[2][4] = &white;
   Move b6a5p, b6c5p;
   b6a5p.source.colRow = b6c5p.source.colRow = 0x15;
   b6a5p.capture = b6c5p.capture = PieceType::PAWN;
   b6a5p.dest.colRow = 0x04;
   b6a5p.dest.colRow = 0x24;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b6a5p) != moves.end());
   assertUnit(moves.find(b6c5p) != moves.end());

   board.board[0][4] = nullptr;
   board.board[1][4] = nullptr;
   board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES Enpassant White
 * Enpassant with b6 blocked: b5a6E, b5c6E
 * 
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6   . P .             6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{
   BoardEmpty board;
   Pawn pawn(7, 7, false);
   Pawn pawnBlack(7, 7, true);
   pawn.fWhite = true;
   pawnBlack.fWhite = false;
   pawn.position.colRow = 0x14;
   pawn.nMoves = 1;
   pawnBlack.nMoves = 1;
   pawnBlack.lastMove = 10;
   board.board[0][4] = &pawnBlack;
   board.board[2][4] = &pawnBlack;
   board.board[1][5] = &pawnBlack;
   set <Move> moves;
   Move b5a6E, b5c6E;
   b5a6E.source.colRow = b5c6E.source.colRow = 0x14;
   b5a6E.capture = b5c6E.capture = PieceType::PAWN;
   b5a6E.moveType = b5c6E.moveType = Move::MoveType::ENPASSANT;
   b5a6E.dest.colRow = 0x05;
   b5c6E.dest.colRow = 0x25;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b5a6E) != moves.end());
   assertUnit(moves.find(b5c6E) != moves.end());

   board.board[0][4] = nullptr;
   board.board[2][4] = nullptr;
   board.board[1][5] = nullptr;
}


/*************************************
 * GET MOVES Enpassant Black
 * Enpassant with f3 blocked: f4g3E, f4e3E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4           p(P)p     4
 * 3           . p .     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{
   BoardEmpty board;
   Pawn pawn(7, 7, false);
   Pawn pawnWhite(7, 7, true);
   pawn.fWhite = true;
   pawnWhite.fWhite = false;
   pawn.position.colRow = 0x53;
   pawn.nMoves = 1;
   pawnWhite.nMoves = 1;
   pawnWhite.lastMove = 10;
   board.board[4][3] = &pawnWhite;
   board.board[5][2] = &pawnWhite;
   board.board[6][3] = &pawnWhite;
   set <Move> moves;
   Move f4g3E, f4e3E;
   f4g3E.source.colRow = f4e3E.source.colRow = 0x53;
   f4g3E.capture = f4e3E.capture = PieceType::PAWN;
   f4g3E.moveType = f4e3E.moveType = Move::MoveType::ENPASSANT;
   f4g3E.dest.colRow = 0x42;
   f4e3E.dest.colRow = 0x62;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 2);
   assertUnit(moves.find(f4g3E) != moves.end());
   assertUnit(moves.find(f4e3E) != moves.end());

   board.board[4][3] = nullptr;
   board.board[5][2] = nullptr;
   board.board[6][3] = nullptr;
}


/*************************************
 * GET MOVES Enpassant Denied
 * Enpassant: b6 is blocked with black pawn
 *            pawn at a5 moved twice
 *            pawn at c5 move two turns ago
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6     P               6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantDenied()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}

/*************************************
 * GET MOVES Promotion White
 * Promotion white pawn b7 can capture two pawns: a8 and c8. 
 *          It can also move into b8. All three are promoted to queen: 
 *          b7a8pQ, b7b8Q, b7c8pQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   P . P             8
 * 7    (p)              7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionWhite()
{
   BoardEmpty board;
   Pawn pawn(7, 7, false);
   Black black(PAWN);
   pawn.fWhite = true;
   pawn.position.colRow = 0x16;
   pawn.nMoves = 1;

   board.board[0][7] = &black;
   board.board[2][7] = &black;

   set <Move> moves;
   Move b7a8pQ, b7b8Q, b7c8pQ;
   b7a8pQ.source.colRow = b7b8Q.source.colRow = 0x16;
   b7a8pQ.capture = b7c8pQ.capture = PieceType::PAWN;
   b7a8pQ.promote = b7b8Q.promote = b7c8pQ.promote = PieceType::QUEEN;
   b7a8pQ.dest.colRow = 0x07;
   b7b8Q.dest.colRow = 0x17;
   b7c8pQ.dest.colRow = 0x27;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 3);
   assertUnit(moves.find(b7a8pQ) != moves.end());
   assertUnit(moves.find(b7b8Q) != moves.end());
   assertUnit(moves.find(b7c8pQ) != moves.end());

   board.board[0][7] = nullptr;
   board.board[2][7] = nullptr;
}


/*************************************
 * GET MOVES Promotion Black
 * Promotion: black pawn e2 can capture two rooks: d1 and f1.
 *            It can also move into e1. All three are promoted to quee
 *            e2d1rQ, e2e1Q, e2f1rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2          (P)        2
 * 1         r . r       1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
   BoardEmpty board;
   Pawn pawn(7, 7, true);
   White white(ROOK);
   pawn.fWhite = false;
   pawn.position.colRow = 0x41;
   pawn.nMoves = 1;

   board.board[3][0] = &white;
   board.board[5][0] = &white;

   set <Move> moves;
   Move e2d1rQ, e231Q, e2f1rQ;
   e2d1rQ.source.colRow = e231Q.source.colRow = e2f1rQ.source.colRow = 0x41;
   e2d1rQ.capture = e2f1rQ.capture = PieceType::ROOK;
   e2d1rQ.promote = e231Q.promote = e2f1rQ.promote = PieceType::QUEEN;
   e2d1rQ.dest.colRow = 0x30;
   e231Q.dest.colRow = 0x40;
   e2f1rQ.dest.colRow = 0x50;

   pawn.getMoves(moves, board);

   assertUnit(moves.size() == 3);
   assertUnit(moves.find(e2d1rQ) != moves.end());
   assertUnit(moves.find(e231Q) != moves.end());
   assertUnit(moves.find(e2f1rQ) != moves.end());

   board.board[3][0] = nullptr;
   board.board[5][0] = nullptr;
}


/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{

   // SETUP
   const Pawn pawn(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = pawn.getType();

   // VERIFY
   assertUnit(pt == PAWN);
}  // TEARDOWN

