#include "includes/io.hpp"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int printBoard(Board board)
{
	cout << "\n";
	for (int row = NUM_ROWS - 1; row >= 0; row--)
	{
		if (row == NUM_ROWS - 1)
		{
			cout << "    A    B    C    D    E    F    G    H   \n";
		}

		for (int col = 0; col < NUM_COLS; col++)
		{
			if (col == 0)
			{
				cout << " " << row + 1 << "  ";
			}

			switch(board.getSquareValue(row, col))
			{
				case(PAWN):
					cout << "wP";
					break;
				case(BISHOP):
					cout << "wB";
					break;
				case(ROOK):
					cout << "wR";
					break;
				case(KNIGHT):
					cout << "wN";
					break;
				case(QUEEN):
					cout << "wQ";
					break;
				case(KING):
					cout << "wK";
					break;
				case(-PAWN):
					cout << "bP";
					break;
				case(-BISHOP):
					cout << "bB";
					break;
				case(-ROOK):
					cout << "bR";
					break;
				case(-KNIGHT):
					cout << "bN";
					break;
				case(-QUEEN):
					cout << "bQ";
					break;
				case(-KING):
					cout << "bK";
					break;
				case(0):
					cout << "__";
					break;
				default:
					cout << "Quadrado com valor inválido\n";
					return ERROR;			
			}

			cout << "   ";
		}

		cout << "\n";
	}

	cout << "\n";
	return 0;
}

Board makeMove(Board board)
{
	string move;
	int fromRow, fromCol, toRow, toCol;
	bool correct = false;

	cout << "\nTurno do jogador " << (board.getPlayer() == 1 ? "branco" : "preto") << "\n";

	while (!correct)
	{
		cin >> move;

		if (move.length() != 5)
		{
			cout << "\nInserir <letraOrigem><númeroOrigem>-<letradestino><numeroDestino> Por exemplo: a2-a4\n";
			continue;
		}

		transform(move.begin(), move.end(), move.begin(), ::tolower);

		if (move.at(0) < 'a' or move.at(0) > 'h' or move.at(3) > 'h' or move.at(3) < 'a')
		{
			cout << "\nLetra deve estar entre a e h e representa coluna do tabuleiro\n";
			continue;
		}

		if (move.at(1) < '1' or move.at(1) > '8' or move.at(4) < '1' or move.at(4) > '8')
		{
			cout << "\nNúmero deve estar entre 1 e 8 e representa fileira do tabuleiro\n";
			continue;
		}

		fromRow = move.at(1) - '1';
		fromCol = move.at(0) - 'a';
		toRow = move.at(4) - '1';
		toCol = move.at(3) - 'a';

		correct = (board.movePiece(fromRow, fromCol, toRow, toCol) == ERROR ? false : true);
	}

	return board;

}