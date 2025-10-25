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
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = true;
   pawn.position.colRow = 0x13;
   pawn.nMoves = 1;
   set <Move> moves;
   Move b4b5;
   b4b5.source.colRow = 0x13;
   //b4b5.capture = PieceType::SPACE;
   b4b5.dest.colRow = 0x14;
   
   // EXERCISE
   pawn.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 1);
   assertUnit(moves.find(b4b5) != moves.end());
              
   // TEARDOWN
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
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, true /*white*/);
   pawn.fWhite = false;
   pawn.position.colRow = 0x13;
   pawn.nMoves = 1;
   set <Move> moves;
   Move b4b3;
   b4b3.source.colRow = 0x13;
   //b4b5.capture = PieceType::SPACE;
   b4b3.dest.colRow = 0x12;
   
   // EXERCISE
   pawn.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 1);
   assertUnit(moves.find(b4b3) != moves.end());
              
   // TEARDOWN
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
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = true;
   pawn.position.colRow = 0x11;
   pawn.nMoves = 0;
   set <Move> moves;
   Move b2b3, b2b4;
   b2b3.source.colRow = b2b4.source.colRow = 0x11;
   //b4b5.capture = PieceType::SPACE;
   b2b3.dest.colRow = 0x12;
   b2b4.dest.colRow = 0x13;
   
   // EXERCISE
   pawn.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b2b3) != moves.end());
   assertUnit(moves.find(b2b4) != moves.end());

              
   // TEARDOWN
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
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = false;
   pawn.position.colRow = 0x26;
   pawn.nMoves = 0;
   set <Move> moves;
   Move c7c6, c7c5;
   c7c6.source.colRow = c7c5.source.colRow = 0x26;
   //b4b5.capture = PieceType::SPACE;
   c7c6.dest.colRow = 0x25;
   c7c5.dest.colRow = 0x24;
   
   // EXERCISE
   pawn.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(c7c6) != moves.end());
   assertUnit(moves.find(c7c5) != moves.end());

              
   // TEARDOWN
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
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   Black black(PAWN);
   pawn.fWhite = true;
   pawn.position.colRow = 0x15;
   pawn.nMoves = 1;
   board.board[0][6] = board.board[1][6] = board.board[2][6] = &black;
   set <Move> moves;
   Move b6a7p, b6c7p;
   b6a7p.source.colRow = b6c7p.source.colRow = 0x15;
   b6a7p.capture = b6c7p.capture = PieceType::PAWN;
   b6a7p.dest.colRow = 0x06;
   b6c7p.dest.colRow = 0x26;
   
   // EXERCISE
   pawn.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b6a7p) != moves.end());
   assertUnit(moves.find(b6c7p) != moves.end());

              
   // TEARDOWN
   board.board[0][6] = board.board[1][6] = board.board[2][6] = nullptr;
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
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   White white(PAWN);
   pawn.fWhite = false;
   pawn.position.colRow = 0x15;
   pawn.nMoves = 1;
   board.board[0][4] = board.board[1][4] = board.board[2][4] = &white;
   set <Move> moves;
   Move b6a5p, b6c5p;
   b6a5p.source.colRow = b6c5p.source.colRow = 0x15;
   b6a5p.capture = b6c5p.capture = PieceType::PAWN;
   b6a5p.dest.colRow = 0x04;
   b6c5p.dest.colRow = 0x24;
   
   // EXERCISE
   pawn.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b6a5p) != moves.end());
   assertUnit(moves.find(b6c5p) != moves.end());

              
   // TEARDOWN
   board.board[0][4] = board.board[1][4] = board.board[2][4] = nullptr;
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
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   Pawn pawnBlack(7, 7, false /*white*/);
   pawn.fWhite = true;
   pawnBlack.fWhite = false;
   pawn.position.colRow = 0x14;
   pawn.nMoves = 1;
   pawnBlack.nMoves = 1;
   pawnBlack.lastMove = 10;
   board.numMoves = 11;
   board.board[0][4] = board.board[2][4] = board.board[1][5] = &pawnBlack;
   set <Move> moves;
   Move b6a6E, b6c6E;
   b6a6E.source.colRow = b6c6E.source.colRow = 0x14;
   b6a6E.capture = b6c6E.capture = PieceType::PAWN;
   b6a6E.moveType = b6c6E.moveType = Move::MoveType::ENPASSANT;
   b6a6E.dest.colRow = 0x05;
   b6c6E.dest.colRow = 0x25;
   
   // EXERCISE
   pawn.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b6a6E) != moves.end());
   assertUnit(moves.find(b6c6E) != moves.end());

              
   // TEARDOWN
   board.board[0][4] = board.board[2][4] = board.board[1][5] = nullptr;
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
   assertUnit(NOT_YET_IMPLEMENTED);
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
   assertUnit(NOT_YET_IMPLEMENTED);
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
   assertUnit(NOT_YET_IMPLEMENTED);
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

