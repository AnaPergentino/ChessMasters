#include "includes/board.hpp"
#include "includes/io.hpp"
#include <iostream>

int main(void)
{
	Board board;
	board.populate();

	cout << "\nInício do jogo\n";
	cout << "\nExemplo de move: a2-a4\n";

	while(board.isGameEnd() == ERROR)
	{
		printBoard(board);
		board = makeMove(board);
	}

	return 0;
}