/**
 * @file PGN.hpp
 *
 * API de manipulação de arquivo PGN
 */

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

      /**
    	 * Função
    	 *      Construtora da classe PGN
    	 */
      PGN();
      /**
       * Função
       *      Construtora da classe PGN
       * Interface explícita
       *      pgnFile
       * Interfaces implícitas
       *    pgnHeader
       *    addMoves
       */
      PGN(ifstream& pgnFile);


      // Armazena jogo PGN em arquivo passado
    // static void savePgn(const Board& board, const string pgnFile);

private:
  /**
   * Função
   *      setar cabeçalho PGN
   * Interfaces explícitas
   *      varName
   *      value
   */
    void pgnHeader(const string varName, const string value);
    /**
     * Função
     *      criar vetor de movimentos de acordo
     *       com leitura do arquivo PGN
     * Interface explícita
     *      moveString
     */
    void addMoves(const string moveString);
    /**
     * Função
     *      retorna uma string com resultado do jogo
     * Interface explícita
     *      Board
     *
     */
    static string getResultString(const Board board);
};
