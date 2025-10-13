/***********************************************************************
 * Source File:
 *    BOARD
 * Author:
 *    Jackson and Peyton
 * Summary:
 *    A collection of pieces and the state of the board
 ************************************************************************/

#include "uiDraw.h"
#include "board.h"
#include "position.h"
#include "piece.h"
#include <cassert>
#include "pieceSpace.h"
#include "pieceKnight.h"
using namespace std;

/***********************************************
* BOARD : CONSTRUCT
*         Give every piece a place on the board.
***********************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   if (!noreset)
      reset(false /*fFree*/);
   else
      for (int r = 0; r < 8; r++)
         for (int c = 0; c < 8; c++)
            board[r][c] = nullptr;
}

/***********************************************
* BOARD : FREE
*         Free up all the allocated memory
***********************************************/
void Board::free()
{
   for (int r = 0; r < 8; r++)
      for (int c = 8; c < 8; c++)
         if (board[c][r] != nullptr)
            delete board[c][r];
}

/***********************************************
* BOARD : RESET
*         Put everything back to how it was.
***********************************************/
void Board::reset(bool fFree)
{
   // free up allocated memory if commanded to
   if (fFree)
      free();
   
   // free everything
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;
   // create four knights
   board[1][0] = new Knight(1, 0, true /*isWhite*/);
   board[6][0] = new Knight(6, 0, true /*isWhite*/);
   board[1][7] = new Knight(1, 7, false /*isWhite*/);
   board[6][7] = new Knight(6, 7, false /*isWhite*/);
   
   // everything else is a space
   for (int r = 0; r < 8; r++)
      for (int c =0; c < 8; c++)
         if (nullptr == board[c][r])
            board[c][r] = new Space(c, r);
   
   // reset the moves
   numMoves = 0;
   assertBoard();
}

/***********************************************
* BOARD : ASSERT BOARD
*         Verify the board is well-formed.
***********************************************/
void Board::assertBoard()
{
#ifndef NDEBUG
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         if (board[c][r] != nullptr)
         {
            Position pos = board[c][r]->getPosition();
            assert(pos.getRow() == r);
            assert(pos.getCol() == c);
            assert(board[c][r]->getType() == SPACE ||
               board[c][r]->getType() == KING ||
               board[c][r]->getType() == QUEEN ||
               board[c][r]->getType() == ROOK ||
               board[c][r]->getType() == BISHOP ||
               board[c][r]->getType() == KNIGHT ||
               board[c][r]->getType() == PAWN);
         }
#endif // NDEBUG
}


/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
   assert(0 <= pos.getCol() && pos.getCol() < 8);
   assert(0 <= pos.getRow() && pos.getRow() < 8);
   assert(nullptr != board[pos.getCol()][pos.getRow()]);
   return *board[pos.getCol()][pos.getRow()];
}
Piece& Board::operator [] (const Position& pos)
{
   assert(0 <= pos.getCol() && pos.getCol() < 8);
   assert(0 <= pos.getRow() && pos.getRow() < 8);
   assert(nullptr != board[pos.getCol()][pos.getRow()]);
   return *board[pos.getCol()][pos.getRow()];
}

/***********************************************
* BOARD : DISPLAY
*         Display the board
***********************************************/
void Board::display(const Position &posHover, const Position &posSelect) const
{
   // draw the base board
   pgout->drawBoard();
   
   // draw the pieces
   for (int r = 0; r < 8; r++)
      for (int c =0; c < 8; c++)
      {
         assert(nullptr != board[c][r]);
         board[c][r]->display(pgout);
      }
}


/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move & move)
{
   assertBoard();
   Position src = move.getSrc();
   Position des = move.getDes();
   Piece * pSrc = board[src.getCol()][src.getRow()];
   Piece * pDes = board[des.getCol()][des.getRow()];
   assert(pSrc->getType() != SPACE);
   assert(src.isValid());
   assert(des.isValid());
   
   switch (move.getMoveType())
   {
      case Move::MOVE:
      {
         //create new pieces
         PieceType ptNew = move.getPromotion() == SPACE ? pSrc->getType() :
                                                      move.getPromotion();
         Piece * pSpace = new Space(src.getCol(), src.getRow());
         Piece * pNew   = factory(ptNew, des.getCol(), des.getRow());
         *pNew = *pSrc;
         pNew->setLastMove(getCurrentMove());
         
         // set the board
         board[src.getCol()][src.getRow()] = pSpace;
         board[des.getCol()][des.getRow()] = pNew;
         
         // increment the number of moves
         numMoves++;
         break;
      }
      case Move::ENPASSANT:
         assert(false);
         break;
      case Move::CASTLE_KING:
         assert(false);
         break;
      case Move::CASTLE_QUEEN:
         assert(false);
         break;
      default:
         assert(false);
   }
}

/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr)
{
   //pSpace = new Space;
}
BoardEmpty::~BoardEmpty()
{
   delete pSpace;
}
