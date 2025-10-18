/***********************************************************************
 * Header File:
 *    TEST MOVE
 * Author:
 *    Jackson and Peyton
 * Summary:
 *    test the Move class
 ************************************************************************/


#include "testMove.h"
#include "move.h"
#include <cassert>

 /*************************************
  * Constructor : default
  * Input:
  * Output: source=INVALID
  *         dest  =INVALID
  **************************************/
void TestMove::constructor_default()
{
   //Setup
   Move move;

   //Excersize
   assertUnit(move.source.isInvalid() == true);
   assertUnit(move.dest.isInvalid() == true);

   //Takedown
}

/*************************************
 * CONSTRUCTOR : standard string move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::constructString_simple()
{
   //Setup and Excersize
   Move move("e5e6");

   //verify
   assertUnit(move.source == 0x44);
   assertUnit(move.dest == 0x45);

   //takedown
}

/*************************************
 * READ simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::read_simple()
{
   Move move("e5e6");

   assertUnit(move.source == 0x44);
   assertUnit(move.dest == 0x45);
   assertUnit(move.moveType == Move::MOVE);
}

/*************************************
 * READ capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::read_capture()
{
   Move move("e5d6r");

   assertUnit(move.source == 0x44);
   assertUnit(move.dest == 0x35);
   assertUnit(move.moveType == Move::MOVE);
   assertUnit(move.capture == ROOK);
}

/*************************************
 * READ enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::read_enpassant()
{
   Move move("e5f6E");

   assertUnit(move.source == 0x44);
   assertUnit(move.dest == 0x55);
   assertUnit(move.moveType == Move::ENPASSANT);
}

/*************************************
 * READ king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::read_castleKing()
{
   Move move("e1g1c");

   assertUnit(move.source == 0x40);
   assertUnit(move.dest == 0x60);
   assertUnit(move.moveType == Move::CASTLE_KING);
}

/*************************************
 * READ queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::read_castleQueen()
{
   Move move("e1c1C");

   assertUnit(move.source == 0x44);
   assertUnit(move.dest == 0x45);
   assertUnit(move.moveType == Move::CASTLE_QUEEN);
}

/*************************************
 * ASSIGN simple move
 * Input:  e5e6
 * Output: source=5,5
 *         dest  =5,6
 *         type  =MOVE
 **************************************/
void TestMove::assign_simple()
{
   Move move("e5e6");

   assertUnit(move.source == 0x44);
   assertUnit(move.dest == 0x45);
   assertUnit(move.moveType == Move::MOVE);
}

/*************************************
 * ASSIGN capture move
 * Input:  e5d6r
 * Output: source=5,5
 *         dest  =4,6
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::assign_capture()
{
   Move move("e5d6r");

   assertUnit(move.source.colRow == 0x44);
   assertUnit(move.dest.colRow == 0x35);
   assertUnit(move.moveType == Move::MOVE);
   assertUnit(move.capture == ROOK);

}

/*************************************
 * ASSIGN enpassant move
 * Input:  e5f6E
 * Output: source=5,5
 *         dest  =6,6
 *         type  =ENPASSANT
 **************************************/
void TestMove::assign_enpassant()
{
   Move move("e5f6E");

   assertUnit(move.source.colRow == 0x44); // (5, 5)
   assertUnit(move.dest.colRow == 0x55); // (6, 6)
   assertUnit(move.moveType == Move::ENPASSANT);
}

/*************************************
 * ASSIGN king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::assign_castleKing()
{
   Move move("e1g1c");

   assertUnit(move.source.colRow == 0x40); //(4, 4)
   assertUnit(move.dest.colRow == 0x60);
   assertUnit(move.moveType == Move::CASTLE_KING);
}

/*************************************
 * ASSIGN queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::assign_castleQueen()
{
   Move move("e5d6r");

   assertUnit(move.source.colRow == 0x44);
   assertUnit(move.dest.colRow == 0x35);
   assertUnit(move.moveType == Move::MOVE);
   assertUnit(move.capture == ROOK);
}

/*************************************
 * GET TEXT simple move
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 * Output:  e5e6
 **************************************/
void TestMove::getText_simple()
{
   Move move(Position(4, 4), Position(4, 5), Move::MOVE, SPACE);
   assertUnit(move.text == "d4d5");
}

/*************************************
 * GET TEXT capture
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 *         capture=ROOK
 * Output:  d5d6r
 **************************************/
void TestMove::getText_capture()
{
   Move move(Position(4, 4), Position(4, 5), Move::MOVE, ROOK);
   assertUnit(move.text == "d4d5r");
}

/*************************************
 * GET TEXT en passant
 * Input : source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 *         capture=PAWN
 * Output:  e5f6E
 **************************************/
void TestMove::getText_enpassant()
{
   Position pos1(5, 5);
   Position pos2(6, 6);
   Move move(pos1, pos2, Move::ENPASSANT, SPACE);
   assertUnit(move.text == "e5f6E");
}

/*************************************
 * GET TEXT king side castle
 * Input : source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 * Output:  e1g1c
 **************************************/
void TestMove::getText_castleKing()
{
   Move move(Position(5, 1), Position(7, 1), Move::CASTLE_KING, SPACE);

   assertUnit(move.text == "e1g1c");
}

/*************************************
 * GET TEXT queen side castle
 * Input : source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 * Output:  e1c1C
 **************************************/
void TestMove::getText_castleQueen()
{
   Move move(Position(5, 1), Position(3, 1), Move::CASTLE_QUEEN, SPACE);

   assertUnit(move.text == "e1c1C");
}

/*************************************
 * LETTER FROM PIECE TYPE space
 * Input :  SPACE
 * Output:  ' '
 **************************************/
void TestMove::letterFromPieceType_space()
{
   //setup
   Move move;

   //excersize
   const char output = move.letterFromPieceType(SPACE);

   //verify
   assertUnit(output == ' ');

   //teardown
}

/*************************************
 * LETTER FROM PIECE TYPE pawn
 * Input : PAWN
 * Output:  'p'
 **************************************/
void TestMove::letterFromPieceType_pawn()
{
   //setup
   Move move;

   //excersize
   const char output = move.letterFromPieceType(PAWN);

   //verify
   assertUnit(output == 'p');

   //teardown
}

/*************************************
 * LETTER FROM PIECE TYPE bishop
 * Input : BISHOP
 * Output:  'b'
 **************************************/
void TestMove::letterFromPieceType_bishop()
{
   //setup
   Move move;

   //excersize
   const char output = move.letterFromPieceType(BISHOP);

   //verify
   assertUnit(output == 'b');

   //teardown
}

/*************************************
 * LETTER FROM PIECE TYPE knight
 * Input : KNIGHT
 * Output:  'n'
 **************************************/
void TestMove::letterFromPieceType_knight()
{
   //setup
   Move move;

   //excersize
   const char output = move.letterFromPieceType(KNIGHT);

   //verify
   assertUnit(output == 'n');

   //teardown
}

/*************************************
 * LETTER FROM PIECE TYPE rook
 * Input : ROOK
 * Output:  'r'
 **************************************/
void TestMove::letterFromPieceType_rook()
{
   //setup
   Move move;

   //excersize
   const char output = move.letterFromPieceType(ROOK);

   //verify
   assertUnit(output == 'r');

   //teardown
}

/*************************************
 * LETTER FROM PIECE TYPE queen
 * Input : QUEEN
 * Output:  'q'
 **************************************/
void TestMove::letterFromPieceType_queen()
{
   //setup
   Move move;

   //excersize
   const char output = move.letterFromPieceType(QUEEN);

   //verify
   assertUnit(output == 'q');

   //teardown}
}

/*************************************
 * LETTER FROM PIECE TYPE king
 * Input : KING
 * Output:  'k'
 **************************************/
void TestMove::letterFromPieceType_king()
{
   //setup
   Move move;

   //excersize
   const char output = move.letterFromPieceType(KING);

   //verify
   assertUnit(output == 'K');

   //teardown}
}

/*************************************
 * PIECE TYPE FROM LETTER pawn
 * Input : 'p'
 * Output:  PAWN
 **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
   //setup
   Move move;

   //excersize
   const char output = move.pieceTypeFromLetter('p');

   //verify
   assertUnit(output == PAWN);

   //teardown}
}

/*************************************
 * PIECE TYPE FROM LETTER bishop
 * Input : 'b'
 * Output:  BISHOP
 **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{
   //setup
   Move move;

   //excersize
   const char output = move.pieceTypeFromLetter('b');

   //verify
   assertUnit(output == BISHOP);

   //teardown}
}

/*************************************
 * PIECE TYPE FROM LETTER knight
 * Input : 'n'
 * Output:  KNIGHT
 **************************************/
void TestMove::pieceTypeFromLetter_knight()
{
   //setup
   Move move;

   //excersize
   const char output = move.pieceTypeFromLetter('n');

   //verify
   assertUnit(output == KNIGHT);

   //teardown
}

/*************************************
 * PIECE TYPE FROM LETTER rook
 * Input : 'r'
 * Output:  ROOK
 **************************************/
void TestMove::pieceTypeFromLetter_rook()
{
   //setup
   Move move;

   //excersize
   const char output = move.pieceTypeFromLetter('r');

   //verify
   assertUnit(output == ROOK);

   //teardown}
}

/*************************************
 * PIECE TYPE FROM LETTER queen
 * Input : 'q'
 * Output:  QUEEN
 **************************************/
void TestMove::pieceTypeFromLetter_queen()
{
   //setup
   Move move;

   //excersize
   const char output = move.pieceTypeFromLetter('q');

   //verify
   assertUnit(output == QUEEN);

   //teardown}
}

/*************************************
 * PIECE TYPE FROM LETTER king
 * Input : 'k'
 * Output:  KING
 **************************************/
void TestMove::pieceTypeFromLetter_king()
{
   //setup
   Move move;

   //excersize
   const char output = move.pieceTypeFromLetter('K');

   //verify
   assertUnit(output == KING);

   //teardown}
}


/*************************************
 * EQUAL - NOT
 * Input : b2b4 == b2b5
 * Output: false
 **************************************/
void TestMove::equal_not()
{
   //setup
   Move move1;
   Move move2;
   move1.text = "b2b4";
   move2.text = "b2b5";

   //excersize
   bool equal = (move1.text == move2.text);
   //verify
   assertUnit(equal == false);

   //teardown
}

/*************************************
 * EQUAL - EQUALS
 * Input : b2b4 == b2b4
 * Output: true
 **************************************/
void TestMove::equal_equals()
{
   //setup
   Move move1;
   Move move2;
   move1.text = "b2b4";
   move2.text = "b2b4";

   //excersize
   bool equal = (move1.text == move2.text);
   //verify
   assertUnit(equal == true);

   //teardown
}

/*************************************
 * LESS THAN - LESS THAN
 * Input : b2b2 < b2b4
 * Output: false
 *    Note that the less-than operator is needed
 *    so std::set<T> can sort the elements. Thus,
 *    any T in a set must define less-than. In this
 *    case, I defined it according to the
 *     destination's Position's location.
 **************************************/
void TestMove::lessthan_lessthan()
{
   //setup
   Move move1;
   Move move2;
   move1.text = "b2b2";
   move2.text = "b2b4";

   //excersize
   bool lessThan = (move1.text > move2.text);

   //verify
   assertUnit(lessThan == false);

   //teardown
}

/*************************************
 * LESS THAN - EQUALS
 * Input : b2b4 < b2b4
 * Output: false
 **************************************/
void TestMove::lessthan_equals()
{
   //setup
   Move move1;
   Move move2;
   move1.text = "b2b2";
   move2.text = "b2b4";

   //excersize
   bool lessThan = (move1.text > move2.text);

   //verify
   assertUnit(lessThan == false);

   //teardown
}

/*************************************
 * LESS THAN - GREATAER THAN
 * Input : b2b4 < b2b2
 * Output: false
 **************************************/
void TestMove::lessthan_greaterthan()
{
   //setup
   Move move1;
   Move move2;
   move1.text = "b2b4";
   move2.text = "b2b2";

   //excersize
   bool lessThan = (move1.text < move2.text);

   //verify
   assertUnit(lessThan == false);

   //teardown
}
