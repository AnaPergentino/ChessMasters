#include "includes/board.hpp"
#include "includes/io.hpp"
#include "includes/ia.hpp"
#include <iostream>

int main(void)
{
	Board board;
	Ia ia;
	board.populate();
	bool computerWillPlay = computerPlays();
	int playerColor;
	vector <pair<int, int>> bestMoves;

	if (computerWillPlay)
	{
		playerColor = getPlayerColor();
	}

	cout << "\nInício do jogo\n";
	cout << "\nExemplo de move: a2-a4\n";

	while(board.isGameEnd() == ERROR)
	{
		printBoard(board);

		if (computerWillPlay and board.getPlayer() != playerColor)
		{
			cout << "\nDeixe-me pensar.....\n";
			bestMoves = ia.bestMoves(board);
			board = makeComputerMove(board, bestMoves[0]);
		}
		else
		{
			if (wantBestMoves())
			{
				bestMoves = ia.bestMoves(board);
				showBestMoves(bestMoves);
			}
			board = makeMove(board);
		}
	}

	printBoard(board);

	if (board.isGameEnd() == 0)
	{
		cout << "\nHouve empate! Inacreditável!\n";
		if (computerWillPlay)
		{
			cout << endl << "Computador: O improvável aconteceu!" << endl;
		}
	}
	else
	{
		cout << "\nO jogador" << (board.isGameEnd() == WHITE ? " branco" : " preto") << " ganhou!\n";
		if (computerWillPlay)
		{
			if (board.isGameEnd() == playerColor)
			{
				cout << endl << "Computador: Não pode ser!" << endl;
			}
			else
			{
				cout << endl << "Computador: Há! Melhor sorte da próxima vez" << endl;
			}
		}
	}

	return 0;
}