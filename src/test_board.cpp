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
				REQUIRE(board.getSquareValue(1, 0) == piece);
				REQUIRE(piece == PAWN);
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