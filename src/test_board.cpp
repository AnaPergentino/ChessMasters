/**
 * Implementa os testes de representação do tabuleiro
 */

#include "includes/catch.hpp"
#include "includes/board.hpp"
#include <iostream>
using namespace std;

SCENARIO("Teste de Criação de Tabuleiro", "[new Board]")
{
	GIVEN("Não há board")
	{
		WHEN("Tabuleiro Inicializado")
		{
			Board board;

			THEN("Tabuleiro é Inicializado com zeros")
			{
				for(int row = 0; row < NUM_ROWS; row++)
				{
					for(int col = 0; col < NUM_COLS; col++)
					{
						REQUIRE(board.getSquareValue(row, col) == 0);
					}
				}
			}

			THEN("Jogado branco começa")
			{
				REQUIRE(board.getPlayer() == WHITE);
			}

			THEN("Vector de peças estão vazias")
			{
				for (int piece = PAWN; piece <= KING; piece++)
				{
					REQUIRE(board.getPieceVector(piece, WHITE).empty() == true);
					REQUIRE(board.getPieceVector(piece, BLACK).empty() == true);
				}
			}
		}
	}

	GIVEN("Board criado")
	{
		Board board;

		WHEN("Tabuleiro populado com início padrão")
		{
			board.populate();

			THEN("Peças corretas nas posições corretas")
			{

				for(int row = 0; row < NUM_ROWS; row++)
				{
					for(int col = 0; col < NUM_COLS; col++)
					{
						REQUIRE(board.getSquareValue(row, col) == START_ARRAY[row][col]);
					}
				}
			}
			THEN("Numero de peças por Vector correto")
			{
					REQUIRE(board.getPieceVector(PAWN, WHITE).size() == 8);
					REQUIRE(board.getPieceVector(ROOK, WHITE).size() == 2);
					REQUIRE(board.getPieceVector(KNIGHT, WHITE).size() == 2);
					REQUIRE(board.getPieceVector(BISHOP, WHITE).size() == 2);
					REQUIRE(board.getPieceVector(QUEEN, WHITE).size() == 1);
					REQUIRE(board.getPieceVector(KING, WHITE).size() == 1);
					REQUIRE(board.getPieceVector(PAWN, BLACK).size() == 8);
					REQUIRE(board.getPieceVector(ROOK, BLACK).size() == 2);
					REQUIRE(board.getPieceVector(KNIGHT, BLACK).size() == 2);
					REQUIRE(board.getPieceVector(BISHOP, BLACK).size() == 2);
					REQUIRE(board.getPieceVector(QUEEN, BLACK).size() == 1);
					REQUIRE(board.getPieceVector(KING, BLACK).size() == 1);
			}
			THEN("Listas de peça em posição correta")
			{
				std::vector<int> whitePawns = {8, 9, 10, 11, 12, 13, 14, 15};
				std::vector<int> whiteRooks = {0, 7};
				std::vector<int> whiteKnights = {1, 6};
				std::vector<int> whiteBishops = {2, 5};
				std::vector<int> whiteQueen = {3};
				std::vector<int> whiteKing = {4};
				std::vector<int> blackPawns = {48, 49,  50, 51, 52, 53, 54, 55};
				std::vector<int> blackRooks = {56, 63};
				std::vector<int> blackKnights = {57, 62};
				std::vector<int> blackBishops = {58, 61};
				std::vector<int> blackQueen = {59};
				std::vector<int> blackKing = {60};
				REQUIRE(board.getPieceVector(PAWN, WHITE) == whitePawns);
				REQUIRE(board.getPieceVector(ROOK, WHITE) == whiteRooks);
				REQUIRE(board.getPieceVector(KNIGHT, WHITE) == whiteKnights);
				REQUIRE(board.getPieceVector(BISHOP, WHITE) == whiteBishops);
				REQUIRE(board.getPieceVector(QUEEN, WHITE) == whiteQueen);
				REQUIRE(board.getPieceVector(KING, WHITE) == whiteKing);
				REQUIRE(board.getPieceVector(PAWN, BLACK) == blackPawns);
				REQUIRE(board.getPieceVector(ROOK, BLACK) == blackRooks);
				REQUIRE(board.getPieceVector(KNIGHT, BLACK) == blackKnights);
				REQUIRE(board.getPieceVector(BISHOP, BLACK) == blackBishops);
				REQUIRE(board.getPieceVector(QUEEN, BLACK) == blackQueen);
				REQUIRE(board.getPieceVector(KING, BLACK) == blackKing);
			}
		}
	}
}

SCENARIO("Teste de Colocação de peça no Tabuleiro", "[putPiece]")
{
	GIVEN("Tabuleiro Inicializado")
	{
		Board board;

		WHEN("Coloca peças válidas no tabuleiro em posições válidas")
		{
			board.putPiece(QUEEN, 0, 0);
			board.putPiece(-PAWN, 4, 3);

			THEN("Peças colocadas estarão no tabuleiro")
			{
				REQUIRE(board.getSquareValue(0, 0) == QUEEN);
				REQUIRE(board.getSquareValue(4, 3) == -PAWN);
			}
			THEN("Peças colocadas estão na lista de peças")
			{
				REQUIRE(board.getPieceVector(QUEEN, WHITE)[0] == 0);
				REQUIRE(board.getPieceVector(PAWN, BLACK)[0] == 35);
			}
		}

		WHEN("Coloca peça em posição inválida no tabuleiro")
		{
			int returnValue = board.putPiece(ROOK, 10, 1);

			THEN("Valor retornado indica erro")
			{
				REQUIRE(returnValue == ERROR);
			}
		}

		WHEN("Coloca peça em posição ocupada do tabuleiro")
		{
			board.putPiece(KNIGHT, 0, 0);
			int returnValue = board.putPiece(KING, 0, 0);

			THEN("Valor retornado indica erro")
			{
				REQUIRE(returnValue == ERROR);
			}

			THEN("Peça não é colocada")
			{
				REQUIRE(board.getSquareValue(0, 0) == KNIGHT);
				REQUIRE(board.getPieceVector(KING, WHITE).empty() == true);
			}
		}

		WHEN("Coloca peça inválida no tabuleiro")
		{
			int oldPiece = board.getSquareValue(2, 0);
			int returnValue = board.putPiece(12, 2, 0);

			THEN("Valor retornado indica erro")
			{
				REQUIRE(returnValue == ERROR);
			}

			THEN("Posiçao não se altera")
			{
				REQUIRE(board.getSquareValue(2, 0) == oldPiece);
			}
		}
	}
}

SCENARIO("Teste de remoção de peça no Tabuleiro", "[removePiece]")
{
	GIVEN("Tabuleiro Inicializado com peças")
	{
		Board board;
		board.populate();


		WHEN("Remove peça de posição válida")
		{
			int piece = board.removePiece(1, 0);

			THEN("Peças removida do tabuleiro e função retorna peça")
			{
				REQUIRE(board.getSquareValue(1, 0) == 0);
				REQUIRE(piece == PAWN);
			}
			THEN("Peça removida da lista de peças")
			{
				REQUIRE(board.getPieceVector(PAWN, WHITE)[0] != 8);
			}
		}

		WHEN("Remove peça de posição inválida no tabuleiro")
		{
			int piece = board.removePiece(10, 0);

			THEN("Valor retornado indica erro")
			{
				REQUIRE(piece == ERROR);
			}
		}

		WHEN("Remove peça em posição desocupada do tabuleiro")
		{
			int piece = board.removePiece(4, 4);

			THEN("Valor retornado indica erro e posição continua desocupada")
			{
				REQUIRE(piece == ERROR);
				REQUIRE(board.getSquareValue(4, 4) == 0);
			}
		}
	}
}

SCENARIO("Teste de validade de tabuleiro", "[isValid]")
{
	GIVEN("Tabuleiro com começo padrão")
	{
		Board board;
		board.populate();

		THEN("Tabuleiro é válido")
		{
			REQUIRE(board.isValid() == true);
		}

		WHEN("O tabuleiro não tem exatamente um rei branco e um rei preto")
		{
			board.putPiece(KING, 4, 4);

			THEN("Tabuleiro é inválido")
			{
				REQUIRE(board.isValid() == false);
			}
		}

		WHEN("Um rei está a um quadrado de distância do outro")
		{
			board.removePiece(1, 4);
			board.removePiece(7, 4);
			board.putPiece(-KING, 1, 4);

			THEN("Tabuleiro é inválido")
			{
				REQUIRE(board.isValid() == false);
			}
		}
	}
}