#include <iostream>
#include <cassert>
using namespace std;

#include "includes/gameMove.hpp"

void PGN::gameMove::setCountPlays(int play)
{
  this->countPlays = play;
}
int PGN::gameMove::getCountPlays()
{
  return this->countPlays;
}
void PGN::gameMove::setPiecePlayerOne(char piece)
{
  int pieceInt = getPieceToInt(piece);
  this->piecePlayerOne = pieceInt;
}
int PGN::gameMove::getPiecePlayerOne()
{
  return this->piecePlayerOne;
}
void PGN::gameMove::setSquarePlayerOne(std::string square)
{
  this->squarePlayerOne = square;
}
std::string PGN::gameMove::getSquarePlayerOne()
{
  return this->squarePlayerOne;
}
void PGN::gameMove::setPiecePlayerTwo(char piece)
{
  this->piecePlayerTwo = getPieceToInt(piece);
}
int PGN::gameMove::getPiecePlayerTwo()
{
  return this->piecePlayerTwo;
}
void PGN::gameMove::setSquarePlayerTwo(std::string square)
{
  this->squarePlayerTwo = square;
}
std::string PGN::gameMove::getSquarePlayerTwo()
{
  return this->squarePlayerTwo;
}
int PGN::gameMove::getPieceToInt(char piece)
{
  switch (piece) {
    case 'P':
      return PAWN;
    case 'N':
      return KNIGHT;
    case 'B':
      return BISHOP;
    case 'R':
      return ROOK;
    case 'Q':
      return QUEEN;
    case 'K':
      return KING;
    default:
      return 0;
  }
}
