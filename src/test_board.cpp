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

		WHEN("Jogador não ativo está em cheque")
		{
			board.clear();
			board.putPiece(-KING, 0, 0);
			board.putPiece(KING, 4, 4);
			board.putPiece(-ROOK, 4, 7);
			board.setPlayer(BLACK);

			THEN("Tabuleiro é inválido")
			{
				REQUIRE(board.isValid() == false);
			}
		}
	}
}

SCENARIO("Teste de movimentação de peão")
{
	GIVEN("Tabuleiro com começo padrão")
	{
		Board board;
		board.populate();

		THEN("Peão pode avançar uma ou duas casas")
		{
			REQUIRE(board.isMoveLegal(1, 0, 2, 0) == true);
			REQUIRE(board.isMoveLegal(1, 0, 3, 0) == true);
			REQUIRE(board.isMoveLegal(6, 2, 5, 2) == true);
			REQUIRE(board.isMoveLegal(6, 2, 4, 2) == true);
		}
		THEN("Peão não pode avançar mais de duas casas")
		{
			REQUIRE(board.isMoveLegal(1, 0, 4, 0) == false);
			REQUIRE(board.isMoveLegal(6, 0, 2, 0) == false);
		}

		WHEN("Tabuleiro modificado")
		{
			board.removePiece(1,3);
			board.removePiece(6,4);
			board.removePiece(6,3);
			board.putPiece(PAWN, 3, 3);
			board.putPiece(-PAWN, 4, 4);
			board.putPiece(-PAWN, 4, 3);

			THEN("Peões comem na diagonal")
			{
				REQUIRE(board.isMoveLegal(3, 3, 4, 4) == true);
				REQUIRE(board.isMoveLegal(4, 4, 3, 3) == true);
			}
			THEN("Peões não comem na frente")
			{
				REQUIRE(board.isMoveLegal(3, 3, 4, 3) == false);
				REQUIRE(board.isMoveLegal(4, 3, 3, 3) == false);
			}
			THEN("Peão pode andar uma casa desocupada para frente")
			{
				REQUIRE(board.isMoveLegal(4, 4, 3, 4) == true);
			}
			THEN("Peão não pode avançar mais de duas casas pra frente")
			{
				REQUIRE(board.isMoveLegal(4, 4, 2, 4) == false);
				REQUIRE(board.isMoveLegal(3, 3, 5, 3) == false);
			}
			THEN("Peão não pode andar diagonal, esquerda, direita ou para trás")
			{
				REQUIRE(board.isMoveLegal(3, 3, 2, 3) == false);
				REQUIRE(board.isMoveLegal(3, 3, 3, 2) == false);
				REQUIRE(board.isMoveLegal(4, 4, 4, 5) == false);
				REQUIRE(board.isMoveLegal(4, 4, 5, 4) == false);
			}
		}
	}
}

SCENARIO("Teste de movimentação de torres")
{
	GIVEN("Tabuleiro com peças")
	{
		Board board;
		board.putPiece(-ROOK, 7, 0);
		board.putPiece(ROOK, 0, 7);
		board.putPiece(-KING, 7, 4);
		board.putPiece(KING, 0, 4);
		board.putPiece(QUEEN, 4, 0);
		board.putPiece(-KNIGHT, 0, 6);

		THEN("Torres podem locomover quantos quadrados desocupados quiserem na horizontal e vertical")
		{
			REQUIRE(board.isMoveLegal(7, 0, 6, 0) == true);
			REQUIRE(board.isMoveLegal(7, 0, 5, 0) == true);
			REQUIRE(board.isMoveLegal(7, 0, 7, 3) == true);
			REQUIRE(board.isMoveLegal(0, 7, 4, 7) == true);
			REQUIRE(board.isMoveLegal(0, 7, 0, 6) == true);
		}

		THEN("Torres não podem sair do tabuleiro")
		{
			REQUIRE(board.isMoveLegal(7, 0, 8, 0) == false);
			REQUIRE(board.isMoveLegal(0, 7, 0, 8) == false);
		}

		THEN("Torres não podem pular posições ocupadas")
		{
			REQUIRE(board.isMoveLegal(7, 0, 7, 5) == false);
			REQUIRE(board.isMoveLegal(7, 0, 3, 0) == false);
			REQUIRE(board.isMoveLegal(0, 7, 0, 3) == false);
			REQUIRE(board.isMoveLegal(0, 7, 0, 5) == false);
		}

		THEN("Torres podem comer peças na horizontal e vertical")
		{
			REQUIRE(board.isMoveLegal(7, 0, 4, 0) == true);
			REQUIRE(board.isMoveLegal(0, 7, 0, 6) == true);
		}

		THEN("Torres não podem comer peças do mesmo time")
		{
			REQUIRE(board.isMoveLegal(7, 0, 7, 4) == false);
		}
		THEN("Torres não andam na diagonal")
		{
			REQUIRE(board.isMoveLegal(7, 0, 6, 1) == false);
			REQUIRE(board.isMoveLegal(0, 7, 1, 6) == false);
		}
	}
}

SCENARIO("Teste de movimentação dos cavalos")
{
	GIVEN("Tabuleiro com começo padrão")
	{
		Board board;
		board.populate();

		THEN("Cavalos podem pular peças")
		{
			REQUIRE(board.isMoveLegal(7, 1, 5, 0) == true);
			REQUIRE(board.isMoveLegal(7, 6, 5, 7) == true);
			REQUIRE(board.isMoveLegal(0, 1, 2, 2) == true);
			REQUIRE(board.isMoveLegal(0, 6, 2, 5) == true);
		}

		WHEN("Tabuleiro modificado")
		{
			board.clear();
			board.putPiece(KING, 0, 0);
			board.putPiece(-KNIGHT, 1, 2);
			board.putPiece(QUEEN, 3, 3);
			board.putPiece(-KING, 6, 6);
			board.putPiece(KNIGHT, 4, 5);
			board.putPiece(-ROOK, 2, 4);

			THEN("Cavalos podem andar em L até espaço desocupado")
			{
				REQUIRE(board.isMoveLegal(1, 2, 0, 4));
				REQUIRE(board.isMoveLegal(1, 2, 2, 0));
				REQUIRE(board.isMoveLegal(1, 2, 3, 1));
				REQUIRE(board.isMoveLegal(4, 5, 2, 6));
				REQUIRE(board.isMoveLegal(4, 5, 6, 4));
				REQUIRE(board.isMoveLegal(4, 5, 5, 3));
				REQUIRE(board.isMoveLegal(4, 5, 5, 7));
			}

			THEN("Cavalos podem comer peças inimigas")
			{
				REQUIRE(board.isMoveLegal(1, 2, 3, 3));
				REQUIRE(board.isMoveLegal(1, 2, 0, 0));
				REQUIRE(board.isMoveLegal(4, 5, 2, 4));
				REQUIRE(board.isMoveLegal(4, 5, 6, 6));
			}

			THEN("Cavalos não podem comer peças amigas")
			{
				REQUIRE(!board.isMoveLegal(1, 2, 2, 4));
				REQUIRE(!board.isMoveLegal(4, 5, 3, 3));
			}

			THEN("Cavalos andam somente em L")
			{
				REQUIRE(!board.isMoveLegal(1, 2, 1, 3));
				REQUIRE(!board.isMoveLegal(1, 2, 2, 2));
				REQUIRE(!board.isMoveLegal(4, 5, 4, 4));
				REQUIRE(!board.isMoveLegal(4, 5, 3, 5));
			}
		}
	}
}

SCENARIO("Teste de movimentação de bispos")
{
	GIVEN("Tabuleiro com peças")
	{
		Board board;
		board.putPiece(-BISHOP, 7, 0);
		board.putPiece(BISHOP, 0, 0);
		board.putPiece(QUEEN, 3, 4);
		board.putPiece(-KNIGHT, 3, 3);
		board.putPiece(BISHOP, 0, 1);
		board.putPiece(KNIGHT, 1, 2);

		THEN("Bispos podem locomover quantos quadrados desocupados quiserem nas diagonais")
		{
			REQUIRE(board.isMoveLegal(7, 0, 6, 1) == true);
			REQUIRE(board.isMoveLegal(7, 0, 5, 2) == true);
			REQUIRE(board.isMoveLegal(7, 0, 4, 3) == true);
			REQUIRE(board.isMoveLegal(0, 0, 1, 1) == true);
			REQUIRE(board.isMoveLegal(0, 0, 2, 2) == true);
		}

		THEN("Bispos não podem sair do tabuleiro")
		{
			REQUIRE(board.isMoveLegal(7, 0, 8, -1) == false);
			REQUIRE(board.isMoveLegal(0, 0, 8, 8) == false);
		}

		THEN("Bispos não podem pular posições ocupadas")
		{
			REQUIRE(board.isMoveLegal(7, 0, 2, 5) == false);
			REQUIRE(board.isMoveLegal(0, 0, 4, 4) == false);
		}

		THEN("Bispos podem comer peças nas diagonais")
		{
			REQUIRE(board.isMoveLegal(7, 0, 3, 4) == true);
			REQUIRE(board.isMoveLegal(0, 0, 3, 3) == true);
		}

		THEN("Bispos não podem comer peças do mesmo time")
		{
			REQUIRE(board.isMoveLegal(0, 1, 1, 2) == false);
		}
		THEN("Bispos não andam na horizontal e vertical")
		{
			REQUIRE(board.isMoveLegal(7, 0, 6, 0) == false);
			REQUIRE(board.isMoveLegal(7, 0, 7, 1) == false);
			REQUIRE(board.isMoveLegal(0, 1, 1, 1) == false);
			REQUIRE(board.isMoveLegal(0, 1, 0, 2) == false);
		}
	}
}