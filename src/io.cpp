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
			cout << "\033[33m    A   B   C   D   E   F   G   H  \n\033[0m";
		}

		for (int col = 0; col < NUM_COLS; col++)
		{
			if (col == 0)
			{
				cout << " " << "\033[33m" << row + 1 << "\033[0m  ";
			}

			switch(board.getSquareValue(row, col))
			{
				case(PAWN):
					cout << "P";
					break;
				case(BISHOP):
					cout << "B";
					break;
				case(ROOK):
					cout << "R";
					break;
				case(KNIGHT):
					cout << "N";
					break;
				case(QUEEN):
					cout << "Q";
					break;
				case(KING):
					cout << "K";
					break;
				case(-PAWN):
					cout << "\033[34mP\033[0m";
					break;
				case(-BISHOP):
					cout << "\033[34mB\033[0m";
					break;
				case(-ROOK):
					cout << "\033[34mR\033[0m";
					break;
				case(-KNIGHT):
					cout << "\033[34mN\033[0m";
					break;
				case(-QUEEN):
					cout << "\033[34mQ\033[0m";
					break;
				case(-KING):
					cout << "\033[34mK\033[0m";
					break;
				case(0):
					cout << "\033[33m_\033[0m";
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

bool computerPlays()
{
	bool correct = false;
	string answer;

	cout << "\nJogar contra computador? (s/n)" <<endl;

	while(!correct)
	{
		cin  >> answer;

		if (answer.length() != 1)
		{
			cout << "\nDigite s para computador joga ou n caso contrário\n";
			continue;
		}

		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		if (answer.at(0) != 's' and answer.at(0) != 'n')
		{
			cout << "\nDigite s para computador joga ou n caso contrário\n";
			continue;
		}
		else if (answer.at(0) == 's')
		{
			cout << "\nComputador: Prepare-se para me enfrentar!" << endl;
			return true;
		}
		else
		{
			cout << "\nHumanos se enfrentarão então." << endl;
			return false;
		}
	}
}

int getPlayerColor()
{
	bool correct = false;
	string answer;

	cout << "\nDeseja jogar com peças brancas ou pretas? (b/p)" <<endl;

	while(!correct)
	{
		cin  >> answer;

		if (answer.length() != 1)
		{
			cout << "\nDigite b para brancas ou p para pretas\n";
			continue;
		}

		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		if (answer.at(0) != 'b' and answer.at(0) != 'p')
		{
			cout << "\nDigite b para brancas ou p para pretas\n";
			continue;
		}
		else if (answer.at(0) == 'b')
		{
			cout << "\nComputador: Então jogarei com as pretas!" << endl;
			return WHITE;
		}
		else
		{
			cout << "\nComputador: Então jogarei com as brancas!" << endl;
			return BLACK;
		}
	}
}

Board makeComputerMove(Board board, pair<int, int> move)
{
	int fromRow, fromCol, toRow, toCol;
	fromRow =  move.first / NUM_ROWS;
	fromCol = move.first % NUM_COLS;
	toRow = move.second / NUM_ROWS;
	toCol = move.second % NUM_COLS;

	cout << endl << (char) (fromCol + 'A') << (char) (fromRow + '1') << " para " << (char) (toCol + 'A') <<  (char) (toRow + '1') << endl;

	board.movePiece(fromRow, fromCol, toRow, toCol);

	return board;
}

void showBestMoves(vector<pair<double, pair<int, int>>> moves)
{
	int fromRow, fromCol, toRow, toCol;
	vector<pair<double, pair<int, int>>>::iterator it;

	if(moves.empty())
	{
		return;
	}
	
	cout << "Melhores moves, do melhor para o pior:" << endl;

	for (it = moves.begin(); it != moves.end(); it++)
	{
		fromRow =  it->second.first / NUM_ROWS;
		fromCol = it->second.first % NUM_COLS;
		toRow = it->second.second / NUM_ROWS;
		toCol = it->second.second % NUM_COLS;

		cout << endl << (char) (fromCol + 'A') << (char) (fromRow + '1') << " para " << (char) (toCol + 'A') <<  (char) (toRow + '1') << " Avaliação: " << it->first << endl;
	}
	return;
}

bool wantBestMoves()
{
	bool correct = false;
	string answer;

	cout << "\nDeseja enxergar melhores moves? (s/n)" <<endl;

	while(!correct)
	{
		cin  >> answer;

		if (answer.length() != 1)
		{
			cout << "\nDigite s para enxergar melhores moves n caso contrário\n";
			continue;
		}

		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		if (answer.at(0) != 's' and answer.at(0) != 'n')
		{
			cout << "\nDigite s para enxergar melhores moves n caso contrário\n";
			continue;
		}
		else if (answer.at(0) == 's')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool pgnFileUpload()
{
	bool correct = false;
	string answer;

	cout << "\nCarregar arquivo PGN? (s/n)" <<endl;

	while(!correct){
		cin  >> answer;

	}
}