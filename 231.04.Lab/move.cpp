/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *    Jackson And Peyton
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move() {}

char Move::letterFromPieceType(PieceType pt) const{
	if (pt == PAWN)
	{
		return 'p';
	}
	else if (pt == KING)
	{
		return 'K';
	}
	else if (pt == ROOK)
	{
		return 'r';
	}
	else if (pt == BISHOP)
	{
		return 'b';
	}
	else if (pt == QUEEN)
	{
		return 'q';
	}
	else if (pt == KNIGHT)
	{
		return 'n';
	}
	else if (pt == SPACE)
	{
		return ' ';
	}
	else
	{
		return 'z';
	}
}


PieceType Move::pieceTypeFromLetter(char letter) const
{
	if (letter == 'p')
	{
		return PAWN;
	}
	else if (letter == 'K')
	{
		return KING;
	}
	else if (letter == 'r')
	{
		return ROOK;
	}
	else if (letter == 'b')
	{
		return BISHOP;
	}
	else if (letter == 'q')
	{
		return QUEEN;
	}
	else if (letter == 'n')
	{
		return KNIGHT;
	}
	else
	{
		return INVALID;
	}
}

int Move::rowFromLetter(char letter)
{
	if (letter == 'a')
	{
		return 0;
	}
	else if (letter == 'b')
	{
		return 1;
	}
	else if (letter == 'c')
	{
		return 2;
	}
	else if (letter == 'd')
	{
		return 3;
	}
	else if (letter == 'e')
	{
		return 4;
	}
	else if (letter == 'f')
	{
		return 5;
	}
	else if (letter == 'g')
	{
		return 6;
	}
	else if (letter == 'h')
	{
		return 7;
	}
	else
	{
		return 0;
	}
}

void Move::lastLetterDetermine(char letter)
{
	if (letter == 'p')
	{
		capture = PAWN;
	}
	else if (letter == 'r')
	{
		capture = ROOK;
	}
	else if (letter == 'b')
	{
		capture = BISHOP;
	}
	else if (letter == 'n')
	{
		capture = KNIGHT;
	}
	else if (letter == 'k')
	{
		capture = KING;
	}
	else if (letter == 'q')
	{
		capture = QUEEN;
	}
	else if (letter == 'c')
	{
		moveType = CASTLE_KING;
	}
	else if (letter == 'C')
	{
		moveType = CASTLE_QUEEN;
	}
	else if (letter == 'E')
	{
		moveType = ENPASSANT;
	}
}

char Move::letterDetermine()
{
	if (moveType == ENPASSANT)
	{
		return 'E';
	}
	else if (moveType == CASTLE_QUEEN)
	{
		return 'C';
	}
	else if (moveType == CASTLE_KING)
	{
		return 'c';
	}
	else if (capture == PAWN)
	{
		return 'p';
	}
	else if (capture == BISHOP)
	{
		return 'b';
	}
	else if (capture == KNIGHT)
	{
		return 'n';
	}
	else if (capture == ROOK)
	{
		return 'r';
	}
	else if (capture == QUEEN)
	{
		return 'q';
	}
	else if (capture == KING)
	{
		return 'k';
	}
	else if (capture == SPACE)
	{
		return 'o';
	}
	else
	{
		return 'o';
	}
}

char Move::letterFromRow(int row)
{
	if (row == 1)
	{
		return 'a';
	}
	else if (row == 2)
	{
		return 'b';
	}
	else if (row == 3)
	{
		return 'c';
	}
	else if (row == 4)
	{
		return 'd';
	}
	else if (row == 5)
	{
		return 'e';
	}
	else if (row == 6)
	{
		return 'f';
	}
	else if (row == 7)
	{
		return 'g';
	}
	else if (row == 8)
	{
		return 'h';
	}
	else
	{
		return 'o';
	}
}
