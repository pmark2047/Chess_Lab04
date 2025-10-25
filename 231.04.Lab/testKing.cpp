/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
#include "pieceRook.h"
#include "pieceKing.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       p p p         6
 * 5       p(k)p         5
 * 4       p p p         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   White white;
   king.fWhite = true;
   king.position.colRow = 0x21;
   board.board[1][2] = board.board[3][2] = &white;
   board.board[1][0] = board.board[3][0] = &white;
   board.board[1][1] = board.board[3][1] = &white;
   board.board[2][0] = board.board[2][2] = &white;
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 0); // no possible moves
   
   // TEARDOWN
   board.board[1][2] = board.board[3][2] = nullptr;
   board.board[1][0] = board.board[3][0] = nullptr;
   board.board[1][1] = board.board[3][1] = nullptr;
   board.board[2][0] = board.board[2][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   Black black;
   king.fWhite = true;
   king.position.colRow = 0x34;
   board.board[2][5] = board.board[2][4] = &black;
   board.board[2][3] = board.board[3][3] = &black;
   board.board[4][3] = board.board[4][4] = &black;
   board.board[4][5] = board.board[3][5] = &black;
   set <Move> moves;
   Move d5c4, d5c5, d5c6, d5d6, d5e6, d5e5, d5e4, d5d4;
   d5c4.source.colRow = d5c5.source.colRow = d5c6.source.colRow =
   d5d6.source.colRow = d5e6.source.colRow = d5e5.source.colRow =
   d5e4.source.colRow = d5d4.source.colRow = 0x34;
   d5c4.capture = d5c5.capture = d5c6.capture =
   d5d6.capture = d5e6.capture = d5e5.capture =
   d5e4.capture = d5d4.capture = PieceType::PAWN;
   d5c4.dest.colRow = 0x23;
   d5c5.dest.colRow = 0x24;
   d5c6.dest.colRow = 0x25;
   d5d6.dest.colRow = 0x35;
   d5e6.dest.colRow = 0x45;
   d5e5.dest.colRow = 0x44;
   d5e4.dest.colRow = 0x43;
   d5d4.dest.colRow = 0x33;
   
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 8); // 8 possible moves
   assertUnit(moves.find(d5e5) != moves.end());
   assertUnit(moves.find(d5e6) != moves.end());
   assertUnit(moves.find(d5d6) != moves.end());
   assertUnit(moves.find(d5c6) != moves.end());
   assertUnit(moves.find(d5c5) != moves.end());
   assertUnit(moves.find(d5c4) != moves.end());
   assertUnit(moves.find(d5d4) != moves.end());
   assertUnit(moves.find(d5e4) != moves.end());
   
   // TEARDOWN
   board.board[2][5] = board.board[2][4] = nullptr;
   board.board[2][3] = board.board[3][3] = nullptr;
   board.board[4][3] = board.board[4][4] = nullptr;
   board.board[4][5] = board.board[3][5] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{

   // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   king.fWhite = true;
   king.position.colRow = 0x34;
   set <Move> moves;
   Move d5e5, d5e6, d5d6, d5c6, d5c5, d5c4, d5d4, d5e4;
   d5e5.source.colRow = d5e6.source.colRow = d5d6.source.colRow =
      d5c5.source.colRow = d5c4.source.colRow = d5c6.source.colRow =
      d5d4.source.colRow = d5e4.source.colRow = 0x34;
   d5e5.capture = d5e6.capture = d5d6.capture = d5c5.capture =
      d5c4.capture = d5c6.capture = d5d4.capture = d5e4.capture = SPACE;
   d5e5.dest.colRow = 0x44;
   d5e6.dest.colRow = 0x45;
   d5d6.dest.colRow = 0x35;
   d5c6.dest.colRow = 0x25;
   d5c5.dest.colRow = 0x24;
   d5c4.dest.colRow = 0x23;
   d5d4.dest.colRow = 0x33;
   d5e4.dest.colRow = 0x43;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);   // many possible moves
   assertUnit(moves.find(d5e5) != moves.end());
   assertUnit(moves.find(d5e6) != moves.end());
   assertUnit(moves.find(d5d6) != moves.end());
   assertUnit(moves.find(d5c6) != moves.end());
   assertUnit(moves.find(d5c5) != moves.end());
   assertUnit(moves.find(d5c4) != moves.end());
   assertUnit(moves.find(d5d4) != moves.end());
   assertUnit(moves.find(d5e4) != moves.end());
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   king.fWhite = true;
   king.position.colRow = 0x00;
   set <Move> moves;
   Move a1a2, a1b2, a1b1;
   a1a2.source.colRow = a1b2.source.colRow = a1b1.source.colRow = 0x00;
   a1a2.capture = a1b2.capture = a1b1.capture = SPACE;
   a1a2.dest.colRow = 0x01;
   a1b2.dest.colRow = 0x11;
   a1b1.dest.colRow = 0x10;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);   // 3 possible moves
   assertUnit(moves.find(a1a2) != moves.end());
   assertUnit(moves.find(a1b2) != moves.end());
   assertUnit(moves.find(a1b1) != moves.end());
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   White white;
   Rook rook(7, 7, false /*white*/);
   king.fWhite = rook.fWhite = true;
   king.position.colRow = 0x40;
   king.nMoves = rook.nMoves = 0;
   board.board[3][1] = board.board[4][1] = board.board[5][1] = &white;
   board.board[0][0] = board.board[7][0] = &rook;
   set <Move> moves;
   Move e1c1c, e1g1C, e1d1, e1f1;
   e1c1c.source.colRow = e1g1C.source.colRow =
   e1d1.source.colRow = e1f1.source.colRow = 0x40;
   e1c1c.capture = e1g1C.capture =
   e1d1.capture = e1f1.capture = PieceType::SPACE;
   e1c1c.dest.colRow = 0x20;
   e1g1C.dest.colRow = 0x60;
   e1d1.dest.colRow = 0x30;
   e1f1.dest.colRow = 0x50;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);   // 4 possible moves
   assertUnit(moves.find(e1c1c) != moves.end());
   assertUnit(moves.find(e1g1C) != moves.end());
   assertUnit(moves.find(e1d1) != moves.end());
   assertUnit(moves.find(e1f1) != moves.end());
   
   // TEARDOWN
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[0][0] = board.board[7][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blackCastle()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   Black black;
   Rook rook(7, 7, false /*white*/);
   king.fWhite = rook.fWhite = false;
   king.position.colRow = 0x47;
   king.nMoves = rook.nMoves = 0;
   board.board[3][6] = board.board[4][6] = board.board[5][6] = &black;
   board.board[0][7] = board.board[7][7] = &rook;
   set <Move> moves;
   Move e8c8c, e8g8C, e8d8, e8f8;
   e8c8c.source.colRow = e8g8C.source.colRow =
   e8d8.source.colRow = e8f8.source.colRow = 0x47;
   e8c8c.capture = e8g8C.capture =
   e8d8.capture = e8f8.capture = PieceType::SPACE;
   e8c8c.dest.colRow = 0x27;
   e8g8C.dest.colRow = 0x67;
   e8d8.dest.colRow = 0x37;
   e8f8.dest.colRow = 0x57;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);   // 4 possible moves
   assertUnit(moves.find(e8c8c) != moves.end());
   assertUnit(moves.find(e8g8C) != moves.end());
   assertUnit(moves.find(e8d8) != moves.end());
   assertUnit(moves.find(e8f8) != moves.end());
   
   // TEARDOWN
   board.board[3][6] = board.board[4][6] = board.board[5][6] = nullptr;
   board.board[0][7] = board.board[7][7] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   White white;
   Rook rook(7, 7, false /*white*/);
   king.fWhite = rook.fWhite = true;
   king.position.colRow = 0x40;
   king.nMoves = 1;
   rook.nMoves = 0;
   board.board[3][1] = board.board[4][1] = board.board[5][1] = &white;
   board.board[0][0] = board.board[7][0] = &rook;
   set <Move> moves;
   Move e1d1, e1f1;
   e1d1.source.colRow = e1f1.source.colRow = 0x40;
   e1d1.capture = e1f1.capture = PieceType::SPACE;
   e1d1.dest.colRow = 0x30;
   e1f1.dest.colRow = 0x50;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);   // 4 possible moves
   assertUnit(moves.find(e1d1) != moves.end());
   assertUnit(moves.find(e1f1) != moves.end());
   
   // TEARDOWN
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[0][0] = board.board[7][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   White white;
   Rook rook(7, 7, false /*white*/);
   king.fWhite = rook.fWhite = true;
   king.position.colRow = 0x40;
   king.nMoves = 0;
   rook.nMoves = 1;
   board.board[3][1] = board.board[4][1] = board.board[5][1] = &white;
   board.board[0][0] = board.board[7][0] = &rook;
   set <Move> moves;
   Move e1d1, e1f1;
   e1d1.source.colRow = e1f1.source.colRow = 0x40;
   e1d1.capture = e1f1.capture = PieceType::SPACE;
   e1d1.dest.colRow = 0x30;
   e1f1.dest.colRow = 0x50;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);   // 4 possible moves
   assertUnit(moves.find(e1d1) != moves.end());
   assertUnit(moves.find(e1f1) != moves.end());
   
   // TEARDOWN
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[0][0] = board.board[7][0] = nullptr;
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{

   // SETUP
   const King king(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = king.getType();

   // VERIFY
   assertUnit(pt == KING);
}  // TEARDOWN


