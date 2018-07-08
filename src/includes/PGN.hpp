#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include "board.hpp"
#include <sstream>


using namespace std;

class Board;

class PGN
{
  public:
      //Propriedades do cabeçalho
      std::string event;  //nome do torneio ou evento
      std::string site; //local do evento
      std::string date; //data do evento
      std::string round;  //numero da partida no evento
      std::string white;  //jogador peças brancas
      std::string black;  //jogador peças pretas
      std::string result;
      vector<string> moves;

      // Construtor
      PGN();
      PGN(ifstream& pgnFile);

      //Funções

      // Armazena jogo PGN em arquivo passado
    //    static void savePgn(const Board& board, const string pgnFile);

private:
    //Funções

    void pgnHeader(const string varName, const string value);
    void addMoves(const string moveString);
    static string getResultString(const Board board);
};
