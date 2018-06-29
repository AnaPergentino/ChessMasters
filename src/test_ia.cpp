/**
 * Implementa os testes do módulo de minimax
 */

#include "includes/catch.hpp"
#include "includes/ia.hpp"
using namespace std;

SCENARIO("Teste de pontuação de peças")
{
	GIVEN("Tabuleiro na posição inicial")
	{
		Board board;
		Ia ia;
		board.populate();

		THEN("O score de peças é zero (empatado)")
		{
			REQUIRE(ia.getMaterialScore(board) == 0);
		}

		WHEN("Um peão preto é comido")
		{
			board.movePiece(1, 0, 3, 0);
			board.movePiece(6, 1, 4, 1);
			board.movePiece(3, 0, 4, 1);

			THEN("O score é +1")
			{
				REQUIRE(ia.getMaterialScore(board) == 1);
			}
		}

		WHEN("Branco Cheque-mate")
		{
			board.clear();
			board.putPiece(KING, 0, 0);
			board.putPiece(-ROOK, 0, 7);
			board.putPiece(-ROOK, 1, 7);
			board.putPiece(-KING, 7, 7);
			board.setPlayer(WHITE);

			THEN("Considera como se o rei em cheque-mate fosse comido")
			{
				REQUIRE(ia.getMaterialScore(board) == -KING_WEIGHT - 2 * ROOK_WEIGHT);
			}
		}
	}
}

SCENARIO("Teste de pontuação de mobilidade")
{
	GIVEN("Tabuleiro na posição inicial")
	{
		Board board;
		Ia ia;
		board.populate();

		THEN("O score de mobilidade é zero (empatado)")
		{
			REQUIRE(ia.getMobilityScore(board) == 0);
		}

		WHEN("O peão branco na frente de um bispo é movido")
		{
			board.movePiece(1, 2, 3, 2);

			THEN("O score de mobilidade é 2")
			{
				REQUIRE(ia.getMobilityScore(board) == 2);
			}
		}

		WHEN("Branco cheque-mate")
		{
			board.clear();
			board.putPiece(KING, 0, 0);
			board.putPiece(-ROOK, 0, 7);
			board.putPiece(-ROOK, 1, 7);
			board.putPiece(-KING, 7, 7);
			board.setPlayer(WHITE);

			THEN("Mobilidade do branco é zero")
			{
				REQUIRE(ia.getMobilityScore(board) == - (double) board.moveList(BLACK).size());
			}
		}
	}
}

SCENARIO("Teste deutilidade de estado do tabuleiro")
{
	GIVEN("Tabuleiro na posição inicial")
	{
		Board board;
		Ia ia;
		board.populate();

		THEN("A utilidade é zero (empatado")
		{
			REQUIRE(ia.utility(board, board.getPlayer()) == 0);
		}

		WHEN("O peão branco na frente de um bispo é movido")
		{
			board.movePiece(1, 2, 3, 2);

			THEN("A utilidade é 2 * peso de mobilidade * -1 pois vez das pretas")
			{
				REQUIRE(ia.utility(board, board.getPlayer()) == 2 * MOBILITY_WEIGHT * -1);
			}
		}

		WHEN("Um peão preto é comido")
		{
			board.movePiece(1, 0, 3, 0);
			board.movePiece(6, 1, 4, 1);
			board.movePiece(3, 0, 4, 1);

			THEN("A utilidade é 1 + o escore de mobilidade * o peso * -1 pois vez das pretas")
			{
				REQUIRE(ia.utility(board, board.getPlayer()) == (1 + ia.getMobilityScore(board) * MOBILITY_WEIGHT) * -1);
			}
		}

		WHEN("Branco cheque-mate")
		{
			board.clear();
			board.putPiece(KING, 0, 0);
			board.putPiece(-ROOK, 0, 7);
			board.putPiece(-ROOK, 1, 7);
			board.putPiece(-KING, 7, 7);
			board.setPlayer(WHITE);

			THEN("Utilidade é mobilidade do preto - 2 * ROOK_WEIGHT - KING_WEIGHT")
			{
				REQUIRE(ia.utility(board, board.getPlayer()) == ia.getMobilityScore(board) * MOBILITY_WEIGHT - 2 * ROOK_WEIGHT - KING_WEIGHT);
			}
		}
	}
}