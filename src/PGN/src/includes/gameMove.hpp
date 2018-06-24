#include <iostream>
#include <cassert>

const int PAWN = 1;
const int ROOK = 2;
const int KNIGHT = 3;
const int BISHOP = 4;
const int QUEEN = 5;
const int KING = 6;

namespace PGN{
  class gameMove{

  private:
    int countPlays;
    int piecePlayerOne; // K, Q, R, B, N, P, ''
    std::string squarePlayerOne;
    int piecePlayerTwo; // K, Q, R, B, N, P, ''
    std::string squarePlayerTwo;
    char check; //+(cheque) ou #(chequemate)

  public:
    void setCountPlays(int play);
    int getCountPlays();
    void setPiecePlayerOne(char piece);
    int getPiecePlayerOne();
    void setSquarePlayerOne(std::string square);
    std::string getSquarePlayerOne();
    void setPiecePlayerTwo(char piece);
    int getPiecePlayerTwo();
    void setSquarePlayerTwo(std::string square);
    std::string getSquarePlayerTwo();
    int getPieceToInt(char piece);
  };
};
