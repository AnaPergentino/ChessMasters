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
		}
	}
}