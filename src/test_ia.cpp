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

			THEN("O score de mobilidade é -1")
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