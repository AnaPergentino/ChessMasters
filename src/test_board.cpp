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

		WHEN("Mais de oito peões brancos")
		{
			board.putPiece(PAWN, 4, 4);

			THEN("Tabuleiro é inválido")
			{
				REQUIRE(!board.isValid());
			}
		}

		WHEN("Mais de oito peões pretos")
		{
			board.putPiece(-PAWN, 4, 4);

			THEN("Tabuleiro é inválido")
			{
				REQUIRE(!board.isValid());
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

SCENARIO("Teste de movimentação de rainha")
{
	GIVEN("Tabuleiro com peças")
	{
		Board board;
		board.putPiece(QUEEN, 3, 3);
		board.putPiece(-QUEEN, 4, 4);

		THEN("Rainhas podem locomover quantos quadrados desocupados quiserem nas diagonais, verticais e horizontais")
		{
			REQUIRE(board.isMoveLegal(3, 3, 2, 2) == true);
			REQUIRE(board.isMoveLegal(3, 3, 1, 1) == true);
			REQUIRE(board.isMoveLegal(3, 3, 4, 3) == true);
			REQUIRE(board.isMoveLegal(3, 3, 5, 3) == true);
			REQUIRE(board.isMoveLegal(3, 3, 3, 2) == true);
			REQUIRE(board.isMoveLegal(3, 3, 3, 1) == true);
			REQUIRE(board.isMoveLegal(4, 4, 5, 5) == true);
			REQUIRE(board.isMoveLegal(4, 4, 6, 6) == true);
			REQUIRE(board.isMoveLegal(4, 4, 3, 4) == true);
			REQUIRE(board.isMoveLegal(4, 4, 2, 4) == true);
			REQUIRE(board.isMoveLegal(4, 4, 4, 5) == true);
			REQUIRE(board.isMoveLegal(4, 4, 4, 6) == true);
		}

		THEN("Rainhas não podem sair do tabuleiro")
		{
			REQUIRE(board.isMoveLegal(3, 3, 8, 3) == false);
			REQUIRE(board.isMoveLegal(4, 4, -1, -1) == false);
		}

		THEN("Rainhas não andam em L")
		{
			REQUIRE(!board.isMoveLegal(3, 3, 4, 5));
			REQUIRE(!board.isMoveLegal(4, 4, 2, 3));
		}

		WHEN("Outras peças no tabuleiro")
		{
			board.putPiece(-PAWN, 5, 3);
			board.putPiece(PAWN, 3, 4);
			board.putPiece(-KNIGHT, 5, 1);
			board.putPiece(KNIGHT, 2, 6);
			board.putPiece(ROOK, 3, 1);
			board.putPiece(-ROOK, 4, 6);

			THEN("Rainhas não podem pular posições ocupadas")
			{
				REQUIRE(board.isMoveLegal(3, 3, 6, 3) == false);
				REQUIRE(board.isMoveLegal(4, 4, 4, 7) == false);
			}

			THEN("Rainhas podem comer peças inimigas nas diagonais, horizontais e verticais")
			{
				REQUIRE(board.isMoveLegal(3, 3, 5, 3) == true);
				REQUIRE(board.isMoveLegal(3, 3, 5, 1) == true);
				REQUIRE(board.isMoveLegal(4, 4, 3, 4) == true);
				REQUIRE(board.isMoveLegal(4, 4, 2, 6) == true);
			}

			THEN("Rainhas não podem comer peças do mesmo time")
			{
				REQUIRE(board.isMoveLegal(3, 3, 3, 1) == false);
				REQUIRE(board.isMoveLegal(4, 4, 4, 6) == false);
			}
		}
	}
}

SCENARIO("Teste de movimentação dos reis")
{
	GIVEN("Tabuleiro com reis")
	{
		Board board;
		board.putPiece(KING, 2, 2);
		board.putPiece(-KING, 5, 5);	

		THEN("Reis andam somente uma peça em qualquer direção")
		{
			REQUIRE(board.isMoveLegal(2, 2, 3, 2) == true);
			REQUIRE(board.isMoveLegal(2, 2, 1, 2) == true);
			REQUIRE(board.isMoveLegal(2, 2, 2, 1) == true);
			REQUIRE(board.isMoveLegal(2, 2, 2, 3) == true);
			REQUIRE(board.isMoveLegal(5, 5, 6, 4) == true);
			REQUIRE(board.isMoveLegal(5, 5, 6, 6) == true);
			REQUIRE(board.isMoveLegal(5, 5, 4, 4) == true);
			REQUIRE(board.isMoveLegal(5, 5, 4, 6) == true);
		}

		
		WHEN("Outras peças no tabuleiro")
		{
			board.putPiece(-PAWN, 3, 2);
			board.putPiece(PAWN, 4, 5);
			board.putPiece(-KNIGHT, 2, 1);
			board.putPiece(KNIGHT, 6, 6);
			board.putPiece(ROOK, 2, 3);
			board.putPiece(-ROOK, 4, 4);


			THEN("Reis podem comer peças a um quadrado em qualquer direção")
			{
				REQUIRE(board.isMoveLegal(2, 2, 3, 2) == true);
				REQUIRE(board.isMoveLegal(2, 2, 2, 1) == true);
				REQUIRE(board.isMoveLegal(5, 5, 4, 5) == true);
				REQUIRE(board.isMoveLegal(5, 5, 6, 6) == true);
			}

			THEN("Reis não podem comer peças do mesmo time")
			{
				REQUIRE(board.isMoveLegal(2, 2, 2, 3) == false);
				REQUIRE(board.isMoveLegal(5, 5, 4, 4) == false);
			}
		}
	}
}

SCENARIO("Teste de cheque")
{
	GIVEN("Um tabuleiro da forma padrão")
	{
		Board board;
		board.populate();

		THEN("Reis não estão em cheque")
		{
			REQUIRE(!board.isCheck(0, 4, WHITE));
			REQUIRE(!board.isCheck(7, 4, BLACK));
		}

		THEN("Se os reis estivessem imediatamente a frente dos peões de cor oposta, estariam em cheque")
		{
			REQUIRE(board.isCheck(2, 0, BLACK));
			REQUIRE(board.isCheck(2, 1, BLACK));
			REQUIRE(board.isCheck(2, 2, BLACK));
			REQUIRE(board.isCheck(2, 3, BLACK));
			REQUIRE(board.isCheck(2, 4, BLACK));
			REQUIRE(board.isCheck(2, 5, BLACK));
			REQUIRE(board.isCheck(2, 6, BLACK));
			REQUIRE(board.isCheck(2, 7, BLACK));
			REQUIRE(board.isCheck(5, 0, WHITE));
			REQUIRE(board.isCheck(5, 1, WHITE));
			REQUIRE(board.isCheck(5, 2, WHITE));
			REQUIRE(board.isCheck(5, 3, WHITE));
			REQUIRE(board.isCheck(5, 4, WHITE));
			REQUIRE(board.isCheck(5, 5, WHITE));
			REQUIRE(board.isCheck(5, 6, WHITE));
			REQUIRE(board.isCheck(5, 7, WHITE));
		}
	}

	GIVEN("Tabuleiro modificado")
	{
		Board board;
		vector<int>::iterator it;
		vector<int> attackedSquares;
		board.putPiece(QUEEN, 0, 0);
		board.putPiece(-QUEEN, 4, 0);
		board.putPiece(ROOK, 0, 1);
		board.putPiece(-PAWN, 4, 1);
		board.putPiece(KNIGHT, 5, 1);

		THEN("Se o rei estivesse no caminho de ataque das peças de outra cor, estaria em cheque")
		{
			attackedSquares = board.getMovesVector(0, 0);
			for(it = attackedSquares.begin(); it != attackedSquares.end(); it++)
			{
			    REQUIRE(board.isCheck(*it / NUM_ROWS, *it % NUM_COLS, BLACK));
    		}
    		attackedSquares = board.getMovesVector(0, 1);
			for(it = attackedSquares.begin(); it != attackedSquares.end(); it++)
			{
			    REQUIRE(board.isCheck(*it / NUM_ROWS, *it % NUM_COLS, BLACK));
    		}
    		attackedSquares = board.getMovesVector(4, 1);
			for(it = attackedSquares.begin(); it != attackedSquares.end(); it++)
			{
			    REQUIRE(board.isCheck(*it / NUM_ROWS, *it % NUM_COLS, WHITE));
    		}
    		attackedSquares = board.getMovesVector(5, 1);
			for(it = attackedSquares.begin(); it != attackedSquares.end(); it++)
			{
		    	REQUIRE(board.isCheck(*it / NUM_ROWS, *it % NUM_COLS, BLACK));

    		}
		}

		THEN("Peças amigas ou inimigas bloqueiam o cheque")
		{
			REQUIRE(!board.isCheck(6, 1, BLACK));
			REQUIRE(!board.isCheck(5, 0, BLACK));
		}

		THEN("Rei no caminho de ataque de peças da mesma cor não entra em cheque")
		{
			REQUIRE(!board.isCheck(0, 2, WHITE));
			REQUIRE(!board.isCheck(1, 1, WHITE));
		}

	}
}

SCENARIO("Testes de movimentação")
{
	GIVEN("Tabuleiro com início padrão")
	{
		Board board;
		board.populate();

		THEN("Quando uma peça se move a origem fica vazia, o destino fica com a peça")
		{
			REQUIRE(board.movePiece(1, 3, 3, 3) == 0);
			REQUIRE(board.getSquareValue(1, 3) == 0);
			REQUIRE(board.getSquareValue(3, 3) == PAWN);
			REQUIRE(board.movePiece(0, 2, 5, 7) == 0);
			REQUIRE(board.getSquareValue(0, 2) == 0);
			REQUIRE(board.getSquareValue(5, 7) == BISHOP);
		}

		WHEN("Tabuleiro modificado")
		{
			board.clear();
			board.putPiece(KING, 0, 1);
			board.putPiece(-KING, 0, 6);
			board.putPiece(QUEEN, 4, 4);
			board.putPiece(-QUEEN, 3, 3);
			board.putPiece(BISHOP, 3, 4);

			THEN("Peças não podem comer amigas")
			{
				REQUIRE(board.movePiece(4, 4, 3, 4) == ERROR);
				REQUIRE(board.getSquareValue(4, 4) == QUEEN);
				REQUIRE(board.getSquareValue(3, 4) == BISHOP);
			}

			THEN("Peças podem comer inimigas")
			{
				REQUIRE(board.movePiece(4, 4, 3, 3) == 0);
				REQUIRE(board.getSquareValue(4, 4) == 0);
				REQUIRE(board.getSquareValue(3, 3) == QUEEN);
				REQUIRE(board.getPieceVector(QUEEN, BLACK).empty());
			}
		}

		WHEN("Tabuleiro modificado")
		{
			board.clear();
			board.putPiece(-KING, 7, 7);
			board.putPiece(KING, 3, 3);
			board.putPiece(-PAWN, 5, 2);

			THEN("Rei não pode andar para posição atacada")
			{
				REQUIRE(board.movePiece(3, 3, 4, 3) == ERROR);
				REQUIRE(board.getSquareValue(3, 3) == KING);
				REQUIRE(board.getSquareValue(5, 2) == -PAWN);
			}
		}

		WHEN("Rei em cheque")
		{
			board.clear();
			board.putPiece(-KING, 1, 1);
			board.putPiece(KING, 3, 3);
			board.putPiece(-QUEEN, 3, 4);
			board.putPiece(-ROOK, 7, 4);
			board.putPiece(ROOK, 0, 4);

			THEN("Peças só se movem se for para tirar o rei do cheque")
			{
				REQUIRE(board.movePiece(0, 4, 0, 7) == ERROR);
				REQUIRE(board.getSquareValue(0, 4) == ROOK);
				REQUIRE(board.movePiece(3, 3, 3, 4) == ERROR);
				REQUIRE(board.getSquareValue(3, 3) == KING);
				REQUIRE(board.movePiece(0, 4, 3, 4) == 0);
				REQUIRE(board.getSquareValue(0, 4) == 0);
				REQUIRE(board.getSquareValue(3, 4) == ROOK);
			}
		}
	}
}

SCENARIO("Testes de cheque-mate")
{
	GIVEN("Tabuleiro na posição inicial")
	{
		Board board;
		board.populate();

		THEN("Não há cheque-mate");
		{
			REQUIRE(!board.isCheckMate(WHITE));
			REQUIRE(!board.isCheckMate(BLACK));
		}

		WHEN("Tabuleiro modificado")
		{
			board.clear();
			board.putPiece(KING, 0, 0);
			board.putPiece(-ROOK, 0, 7);
			board.putPiece(-ROOK, 1, 7);
			board.putPiece(-KING, 7, 7);

			THEN("Branco sofreu cheque-mate")
			{
				REQUIRE(board.isCheckMate(WHITE));
			}

			THEN("Preto não sofreu cheque-mate")
			{
				REQUIRE(!board.isCheckMate(BLACK));
			}
		}

		WHEN("Tabuleiro modificado")
		{
			board.clear();
			board.putPiece(-KING, 7, 7);
			board.putPiece(QUEEN, 6, 6);
			board.putPiece(KNIGHT, 4, 5);
			board.putPiece(KING, 0, 0);

			THEN("Preto sofreu cheque-mate")
			{
				REQUIRE(board.isCheckMate(BLACK));
			}

			THEN("Branco não sofreu cheque-mate")
			{
				REQUIRE(!board.isCheckMate(WHITE));
			}
		}

		WHEN("Tabuleiro modificado")
		{
			board.clear();
			board.putPiece(-KING, 7, 7);
			board.putPiece(QUEEN, 6, 6);
			board.putPiece(KNIGHT, 4, 5);
			board.putPiece(KING, 0, 0);
			board.putPiece(-BISHOP, 7, 5);

			THEN("Ninguém em cheque-mate")
			{
				REQUIRE(!board.isCheckMate(BLACK));
				REQUIRE(!board.isCheckMate(WHITE));
			}
		}
	}
}

SCENARIO("teste de fim de jogo")
{
	GIVEN("Tabuleiro inicial")
	{
		Board board;
		board.populate();

		THEN("Jogo não terminou")
		{
			REQUIRE(board.isGameEnd() == ERROR);
		}

		WHEN("50 moves sem movimentação de peão ou captura")
		{
			for (int i = 0; i < 101; i++)
			{
				board.movePiece(0, 1, 2, 0);
				board.movePiece(7, 1, 5, 0);
				board.movePiece(2, 0, 0, 1);
				board.movePiece(5, 0, 7, 1);
			}

			THEN("Jogo empatou")
			{
				REQUIRE(board.isGameEnd() == 0);
			}
		}

		WHEN("49 moves sem movimentação de peão ou captura  seguido de uma movimentação de peão")
		{
			for (int i = 0; i < 10; i++)
			{
				board.movePiece(0, 1, 2, 0);
				board.movePiece(7, 1, 5, 0);
				board.movePiece(2, 0, 0, 1);
				board.movePiece(5, 0, 7, 1);
			}
			board.movePiece(0, 1, 2, 0);
			board.movePiece(6, 0, 4, 0);

			THEN("Jogo não terminou")
			{
				REQUIRE(board.isGameEnd() == ERROR);
			}
		}

		WHEN("Preto com cheque-mate")
		{
			board.clear();
			board.putPiece(-KING, 7, 7);
			board.putPiece(QUEEN, 6, 6);
			board.putPiece(KNIGHT, 4, 5);
			board.putPiece(KING, 0, 0);
			board.setPlayer(BLACK);

			THEN("Branco ganhou")
			{
				REQUIRE(board.isGameEnd() == WHITE);
			}
		}

		WHEN("Branco sofreu cheque-mate")
		{
			board.clear();
			board.putPiece(KING, 0, 0);
			board.putPiece(-ROOK, 0, 7);
			board.putPiece(-ROOK, 1, 7);
			board.putPiece(-KING, 7, 7);
			board.setPlayer(WHITE);

			THEN("Preto ganhou")
			{
				REQUIRE(board.isGameEnd() == BLACK);
			}
		}
	}
}