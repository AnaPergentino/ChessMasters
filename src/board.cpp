#include "includes/board.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>
#include "includes/PGN.hpp"

using namespace std;

Board::Board()
{
	for(int row = 0; row < NUM_ROWS; row++)
	{
		for(int col = 0; col < NUM_COLS; col++)
		{
			boardArray[row][col] = 0;
		}
	}

	player = WHITE;
	whiteKingCastle = whiteQueenCastle = blackKingCastle = blackQueenCastle = true;
	drawCounter = 0;
}
Board::Board(const string pgnFileName)
{
	ifstream pgnFileStream(pgnFileName);
	if (pgnFileStream.fail())
	{
		throw 1;
	}
	PGN PGN(pgnFileStream);
	for (int i = 0; i < PGN.moves.size(); i++) {
		string move = PGN.moves.at(i);
		if (move.at(move.size() - 2) == '=')
		{
			//caso promotion
			if (move.at(move.size() - 1) != 'Q')
			{
			}
			move = move.substr(0, move.size() - 2);
		}
		else if (move.at(move.size() - 1) == '+' || move.at(move.size() - 1) == '#')
		{
			// movimento de check
			move = move.substr(0, move.size() - 1);
		}
		if (move == "O-O") {
			// Castling Kingside
		}
		else if (move == "O-O-O") {
			// Castling Queenside
		}
		else {
			string coordinateString = move.substr(move.size() - 2, 2);
			int col = (int)coordinateString[0] - 96;
			int row = (int)coordinateString[1] - 48;
			int newSquare = this->getSquareValue(col,row);

			move = move.substr(0, move.size() - 2);
		}
	}
}


void Board::clear()
{
	for(int row = 0; row < NUM_ROWS; row++)
	{
		for(int col = 0; col < NUM_COLS; col++)
		{
			if(getSquareValue(row, col) != 0)
			{
				removePiece(row, col);
			}
		}
	}

	player == WHITE;
	whiteKingCastle = whiteQueenCastle = blackKingCastle = blackQueenCastle = true;
	drawCounter == 0;
}

int Board::getSquareValue(int row, int col)
{
	if ((row >= NUM_ROWS && row < 0) || (col >= NUM_COLS && col < 0))
	{
		cout << "Coordenadas inválidas\n";
		return ERROR;
	}

	assert(boardArray[row][col] >= -KING && boardArray[row][col] <= KING);

	return boardArray[row][col];
}

int Board::getPlayer()
{
	assert(player == WHITE || player == BLACK);
	return player;
}

vector<int> Board::getPieceVector(int piece, int color)
{
	assert(piece >= -KING && piece <= KING);
	assert(color == BLACK || color == WHITE);
	if (color == BLACK)
	{
		return blackPiecesPos[piece - 1];
	}
	else
	{
		return whitePiecesPos[piece - 1];
	}

}

int Board::setPlayer(int newPlayer)
{
	if (newPlayer != WHITE && newPlayer != BLACK)
	{
		cout << "Valor " << newPlayer << " inválido\n";
		return ERROR;
	}

	player = newPlayer;
	return 0;
}

void Board::populate()
{
	for(int row = 0; row < NUM_ROWS; row++)
	{
		for(int col = 0; col < NUM_COLS; col++)
		{
			putPiece(START_ARRAY[row][col], row, col);
		}
	}
}

int Board::putPiece(int piece, int row, int col)
{
	if ((row >= NUM_ROWS || row < 0) || (col >= NUM_COLS || col < 0))
	{
		cout << "Coordenadas("<< row << ", " << col <<  ") inválidas\n";
		return ERROR;
	}

	if (boardArray[row][col] != 0)
	{
		cout << "Posição ("<< row << ", " << col <<  ") ocupada\n";
		return ERROR;
	}

	if (piece < -KING || piece > KING)
	{
		cout << "Peça " << piece << " inválida\n";
		return ERROR;
	}

	boardArray[row][col] = piece;
	if (piece > 0)
	{
		whitePiecesPos[piece - 1].push_back(row * NUM_COLS + col);
	}
	else if (piece == 0)
	{
		return 0;
	}
	else
	{
		piece *= -1;
		blackPiecesPos[piece - 1].push_back(row * NUM_COLS + col);
	}

	return 0;
}

int Board::removePiece(int row, int col)
{
	int piece;

	if ((row >= NUM_ROWS || row < 0) || (col >= NUM_COLS || col < 0))
	{
		cout << "Coordenadas("<< row << ", " << col <<  ") inválidas\n";
		return ERROR;
	}

	if (boardArray[row][col] == 0)
	{
		cout << "Posição ("<< row << ", " << col <<  ") desocupada\n";
		return ERROR;
	}

	piece = boardArray[row][col];

	assert(piece >= -KING && piece <= KING);

	if (piece > 0)
	{
		whitePiecesPos[piece - 1].erase(remove(whitePiecesPos[piece - 1].begin(), whitePiecesPos[piece - 1].end(), row * NUM_ROWS + col), whitePiecesPos[piece - 1].end());
	}
	else
	{
		blackPiecesPos[-piece - 1].erase(remove(blackPiecesPos[-piece - 1].begin(), blackPiecesPos[-piece - 1].end(), row * NUM_ROWS + col), blackPiecesPos[-piece - 1].end());

	}

	boardArray[row][col] = 0;


	return piece;
}

bool Board::isValid()
{
	int whiteKingPos, blackKingPos;

	if (getPieceVector(KING, WHITE).size() != 1 || getPieceVector(KING, BLACK).size() != 1 || getPieceVector(PAWN, WHITE).size() > 8 || getPieceVector(PAWN, BLACK).size() > 8)
	{
		return false;
	}

	whiteKingPos = getPieceVector(KING, WHITE)[0];
	blackKingPos = getPieceVector(KING, BLACK)[0];

	if (blackKingPos == whiteKingPos + UP or blackKingPos == whiteKingPos + DOWN or (whiteKingPos % 8 != 0 and blackKingPos == whiteKingPos + LEFT or blackKingPos == whiteKingPos + UP_LEFT or blackKingPos == whiteKingPos + DOWN_LEFT) or (whiteKingPos % 8 == 7 and blackKingPos == whiteKingPos + RIGHT or blackKingPos == whiteKingPos + UP_RIGHT or blackKingPos == whiteKingPos + DOWN_RIGHT))
	{
		return false;
	}

	if ((player == BLACK and isCheck(whiteKingPos / NUM_ROWS, whiteKingPos % NUM_COLS, WHITE)) or (player == WHITE and isCheck(blackKingPos / NUM_ROWS, blackKingPos % NUM_COLS, BLACK)))
	{
		return false;
	}

	return true;
}

bool Board::isMoveLegal(int fromRow, int fromCol, int toRow, int toCol)
{
	vector<int> legalMoves;
	int toPos = toRow * NUM_ROWS + toCol;

	if ((fromRow >= NUM_ROWS || fromRow < 0) || (fromCol >= NUM_COLS || fromCol < 0))
	{
		cout << "Coordenadas de partida("<< fromRow << ", " << fromCol <<  ") inválidas\n";
		return false;
	}

	if ((toRow >= NUM_ROWS || toRow < 0) || (toCol >= NUM_COLS || toCol < 0))
	{
		cout << "Coordenadas de chegada("<< toRow << ", " << toCol <<  ") inválidas\n";
		return false;
	}

	if (boardArray[fromRow][fromCol] == 0)
	{
		cout << "Posição ("<< fromRow << ", " << fromCol <<  ") desocupada\n";
		return false;
	}

	assert(boardArray[fromRow][fromCol] >= -KING and boardArray[fromRow][fromCol] <= KING);

	legalMoves = getMovesVector(fromRow, fromCol);

	if(find(legalMoves.begin(), legalMoves.end(), toPos) != legalMoves.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<int> Board::getMovesVector(int row, int col)
{
	int piece, color;

	piece = getSquareValue(row, col);

	if (piece < 0)
	{
		piece *= -1;
		color = BLACK;
	}
	else
	{
		color = WHITE;
	}

	if ((row >= NUM_ROWS || row < 0) || (col >= NUM_COLS || col < 0))
	{
		cout << "Coordenadas("<< row << ", " << col <<  ") inválidas\n";
		return {};
	}

	switch(piece)
	{
		case PAWN:
			return getPawnMoves(color, row, col);
		case ROOK:
			return getRookMoves(color, row, col);
		case KNIGHT:
			return getKnightMoves(color, row, col);
		case BISHOP:
			return getBishopMoves(color, row, col);
		case QUEEN:
			return getQueenMoves(color, row, col);
		case KING:
			return getKingMoves(color, row, col);
		default:
			cout << "Peça inválida\n";
			return {};
	}
}

vector<int> Board::getPawnMoves(int color, int row, int col)
{
	vector<int> destinations;
	int origin = row * NUM_ROWS + col;

	if (color == WHITE)
	{
		if (row == 1 and getSquareValue(row + 2, col) == 0 and getSquareValue(row + 1, col) == 0)
		{
			destinations.push_back(origin + UP + UP);
		}

		if (row != 7 and getSquareValue(row + 1, col) == 0)
		{
			destinations.push_back(origin + UP);
		}

		if (row != 7 and col != 0 and getSquareValue(row + 1, col - 1) < 0)
		{
			destinations.push_back(origin + UP_LEFT);
		}

		if (row != 7 and col != 7 and getSquareValue(row + 1, col + 1) < 0)
		{
			destinations.push_back(origin + UP_RIGHT);
		}
	}

	else
	{
		if (row == 6 and getSquareValue(row - 2, col) == 0 and getSquareValue(row - 1, col) == 0)
		{
			destinations.push_back(origin + DOWN + DOWN);
		}

		if (row != 0 and getSquareValue(row - 1, col) == 0)
		{
			destinations.push_back(origin + DOWN);
		}

		if (row != 0 and col != 0 and getSquareValue(row - 1, col - 1) > 0)
		{
			destinations.push_back(origin + DOWN_LEFT);
		}

		if (row != 0 and col != 7 and getSquareValue(row - 1, col + 1) > 0)
		{
			destinations.push_back(origin + DOWN_RIGHT);
		}
	}

	return destinations;
}

vector<int> Board::getRookMoves(int color, int row, int col)
{
	vector<int> destinations;
	int origin = row * NUM_ROWS + col;

	for (int spaces = 1; row + spaces < NUM_ROWS; spaces++)
	{
		if (boardArray[row + spaces][col] == 0)
		{
			destinations.push_back(origin + spaces * UP);
		}

		else if (boardArray[row + spaces][col] * color > 0)
		{
			break;
		}

		else
		{
			destinations.push_back(origin + spaces * UP);
			break;
		}
	}

	for (int spaces = 1; row - spaces >= 0; spaces++)
	{
		if (boardArray[row - spaces][col] == 0)
		{
			destinations.push_back(origin + spaces * DOWN);
		}

		else if (boardArray[row - spaces][col] * color > 0)
		{
			break;
		}

		else
		{
			destinations.push_back(origin + spaces * DOWN);
			break;
		}
	}

	for (int spaces = 1; col + spaces < NUM_COLS; spaces++)
	{
		if (boardArray[row][col + spaces] == 0)
		{
			destinations.push_back(origin + spaces * RIGHT);
		}

		else if (boardArray[row][col + spaces] * color > 0)
		{
			break;
		}

		else
		{
			destinations.push_back(origin + spaces * RIGHT);
			break;
		}
	}

	for (int spaces = 1; col - spaces >= 0; spaces++)
	{
		if (boardArray[row][col - spaces] == 0)
		{
			destinations.push_back(origin + spaces * LEFT);
		}

		else if (boardArray[row][col - spaces] * color > 0)
		{
			break;
		}

		else
		{
			destinations.push_back(origin + spaces * LEFT);
			break;
		}
	}

	return destinations;
}

vector<int> Board::getKnightMoves(int color, int row, int col)
{
	vector<int> destinations;
	int origin = row * NUM_ROWS + col;

	if (row + 2 < NUM_ROWS and col + 1 < NUM_COLS)
	{
		if (boardArray[row + 2][col + 1] * color <= 0)
		{
			destinations.push_back(origin + 2 * UP + RIGHT);
		}
	}

	if (row + 1 < NUM_ROWS and col + 2 < NUM_COLS)
	{
		if (boardArray[row + 1][col + 2] * color <= 0)
		{
			destinations.push_back(origin + UP + 2 * RIGHT);
		}
	}

	if (row + 2 < NUM_ROWS and col - 1 >= 0)
	{
		if (boardArray[row + 2][col - 1] * color <= 0)
		{
			destinations.push_back(origin + 2 * UP + LEFT);
		}
	}

	if (row + 1 < NUM_ROWS and col - 2 >= 0)
	{
		if (boardArray[row + 1][col - 2] * color <= 0)
		{
			destinations.push_back(origin + UP + 2 * LEFT);
		}
	}

	if (row - 2 >= 0 and col + 1 < NUM_COLS)
	{
		if (boardArray[row - 2][col + 1] * color <= 0)
		{
			destinations.push_back(origin + 2 * DOWN + RIGHT);
		}
	}

	if (row - 1 >= 0 and col + 2 < NUM_COLS)
	{
		if (boardArray[row - 1][col + 2] * color <= 0)
		{
			destinations.push_back(origin + DOWN + 2 * RIGHT);
		}
	}

	if (row - 2 >= 0 and col - 1 >= 0)
	{
		if (boardArray[row - 2][col - 1] * color <= 0)
		{
			destinations.push_back(origin + 2 * DOWN + LEFT);
		}
	}

	if (row - 1 >= 0 and col -2 >= 0)
	{
		if (boardArray[row - 1][col - 2] * color <= 0)
		{
			destinations.push_back(origin + DOWN + 2 * LEFT);
		}
	}

	return destinations;
}

vector<int> Board::getBishopMoves(int color, int row, int col)
{
	vector<int> destinations;
	int origin = row * NUM_ROWS + col;

	for (int spaces = 1; row + spaces < NUM_ROWS and col + spaces < NUM_COLS; spaces++)
	{
		if (boardArray[row + spaces][col + spaces] == 0)
		{
			destinations.push_back(origin + spaces * UP_RIGHT);
		}

		else if (boardArray[row + spaces][col + spaces] * color > 0)
		{
			break;
		}

		else
		{
			destinations.push_back(origin + spaces * UP_RIGHT);
			break;
		}
	}

	for (int spaces = 1; row + spaces < NUM_ROWS and col - spaces >= 0; spaces++)
	{
		if (boardArray[row + spaces][col - spaces] == 0)
		{
			destinations.push_back(origin + spaces * UP_LEFT);
		}

		else if (boardArray[row + spaces][col - spaces] * color > 0)
		{
			break;
		}

		else
		{
			destinations.push_back(origin + spaces * UP_LEFT);
			break;
		}
	}

	for (int spaces = 1; row - spaces >= 0 and col + spaces < NUM_COLS; spaces++)
	{
		if (boardArray[row - spaces][col + spaces] == 0)
		{
			destinations.push_back(origin + spaces * DOWN_RIGHT);
		}

		else if (boardArray[row - spaces][col + spaces] * color > 0)
		{
			break;
		}

		else
		{
			destinations.push_back(origin + spaces * DOWN_RIGHT);
			break;
		}
	}

	for (int spaces = 1; row - spaces >= 0 and col - spaces >= 0; spaces++)
	{
		if (boardArray[row - spaces][col - spaces] == 0)
		{
			destinations.push_back(origin + spaces * DOWN_LEFT);
		}

		else if (boardArray[row - spaces][col - spaces] * color > 0)
		{
			break;
		}

		else
		{
			destinations.push_back(origin + spaces * DOWN_LEFT);
			break;
		}
	}

	return destinations;
}

vector<int> Board::getQueenMoves(int color, int row, int col)
{
	vector<int> diagonalMoves, horizontalAndVerticalMoves;

	diagonalMoves = getBishopMoves(color, row, col);
	horizontalAndVerticalMoves = getRookMoves(color, row, col);

	horizontalAndVerticalMoves.insert(horizontalAndVerticalMoves.end(), diagonalMoves.begin(), diagonalMoves.end());

	return horizontalAndVerticalMoves;
}

vector<int> Board::getKingMoves(int color, int row, int col)
{
	vector<int> destinations;
	int origin = row * NUM_ROWS + col;

	for (int i = -1; i <2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 and j == 0 or row + i < 0 or row + i >= NUM_ROWS or col + j < 0 or col + j >= NUM_COLS)
			{
				continue;
			}
			if (boardArray[row + i][col + j] * color <= 0)
			{
				destinations.push_back(origin + i * UP + j * RIGHT);
			}
		}
	}

	if(color == WHITE and !isCheck(0, 4, WHITE))
	{
		if(whiteKingCastle and boardArray[0][5] == 0 and boardArray[0][6] == 0 and !isCheck(0, 5, WHITE) and !isCheck(0, 6, WHITE) and boardArray[0][7] == ROOK)
		{
			destinations.push_back(6);
		}
		if(whiteQueenCastle and boardArray[0][3] == 0 and boardArray[0][2] == 0 and !isCheck(0, 3, WHITE) and !isCheck(0, 2, WHITE) and boardArray[0][0] == ROOK)
		{
			destinations.push_back(2);
		}
	}
	else if (color == BLACK and !isCheck(7, 4, BLACK))
	{
		if(blackKingCastle and boardArray[7][5] == 0 and boardArray[7][6] == 0 and !isCheck(7, 5, BLACK) and !isCheck(7, 6, BLACK) and boardArray[7][7] == -ROOK)
		{
			destinations.push_back(62);
		}
		if(blackQueenCastle and boardArray[7][3] == 0 and boardArray[7][2] == 0 and !isCheck(7, 3, BLACK) and !isCheck(7, 2, BLACK) and boardArray[7][0] == -ROOK)
		{
			destinations.push_back(58);
		}
	}

	return destinations;
}

bool Board::isCheck(int row, int col, int color)
{
	int origin = row * NUM_ROWS + col;

	for (int i = -1; i <2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 and j == 0 or row + i < 0 or row + i >= NUM_ROWS or col + j < 0 or col + j >= NUM_COLS)
			{
				continue;
			}
			if (boardArray[row + i][col + j] == KING * -color)
			{
				return true;
			}
		}
	}

	if (color == WHITE)
	{
		if (boardArray[row + 1][col - 1] == -PAWN  or boardArray[row + 1][col + 1] == -PAWN)
		{
			return true;
		}
	}
	else
	{
		if (boardArray[row - 1][col - 1] == PAWN or boardArray[row - 1][col + 1] == PAWN)
		{
			return true;
		}
	}

	if (row + 2 < NUM_ROWS and col + 1 < NUM_COLS)
	{
		if (boardArray[row + 2][col + 1] == KNIGHT * -color)
		{
			return true;
		}
	}

	if (row + 1 < NUM_ROWS and col + 2 < NUM_COLS)
	{
		if (boardArray[row + 1][col + 2] == KNIGHT * -color)
		{
			return true;
		}
	}

	if (row + 2 < NUM_ROWS and col - 1 >= 0)
	{
		if (boardArray[row + 2][col - 1] == KNIGHT * -color)
		{
			return true;
		}
	}

	if (row + 1 < NUM_ROWS and col - 2 >= 0)
	{
		if (boardArray[row + 1][col - 2] == KNIGHT * -color)
		{
			return true;
		}
	}

	if (row - 2 >= 0 and col + 1 < NUM_COLS)
	{
		if (boardArray[row - 2][col + 1] == KNIGHT * -color)
		{
			return true;
		}
	}

	if (row - 1 >= 0 and col + 2 < NUM_COLS)
	{
		if (boardArray[row - 1][col + 2] == KNIGHT * -color)
		{
			return true;
		}
	}

	if (row - 2 >= 0 and col - 1 >= 0)
	{
		if (boardArray[row - 2][col - 1] == KNIGHT * -color)
		{
			return true;
		}
	}

	if (row - 1 >= 0 and col -2 >= 0)
	{
		if (boardArray[row - 1][col - 2] == KNIGHT * -color)
		{
			return true;
		}
	}

	for (int spaces = 1; row + spaces < NUM_ROWS; spaces++)
	{
		if (boardArray[row + spaces][col] == 0)
		{
			continue;
		}

		else if (boardArray[row + spaces][col] * color > 0)
		{
			break;
		}

		else if (boardArray[row + spaces][col] == QUEEN * -color or boardArray[row + spaces][col] == ROOK * -color)
		{
			return true;
		}

		else
		{
			break;
		}
	}

	for (int spaces = 1; row - spaces >= 0; spaces++)
	{
		if (boardArray[row - spaces][col] == 0)
		{
			continue;
		}

		else if (boardArray[row - spaces][col] * color > 0)
		{
			break;
		}

		else if (boardArray[row - spaces][col] == QUEEN * -color or boardArray[row - spaces][col] == ROOK * -color)
		{
			return true;
		}

		else
		{
			break;
		}
	}

	for (int spaces = 1; col + spaces < NUM_COLS; spaces++)
	{
		if (boardArray[row][col + spaces] == 0)
		{
			continue;
		}

		else if (boardArray[row][col + spaces] * color > 0)
		{
			break;
		}

		else if (boardArray[row][col + spaces] == QUEEN * -color or boardArray[row][col + spaces] == ROOK * -color)
		{
			return true;
		}

		else
		{
			break;
		}
	}

	for (int spaces = 1; col - spaces >= 0; spaces++)
	{
		if (boardArray[row][col - spaces] == 0)
		{
			continue;
		}

		else if (boardArray[row][col - spaces] * color > 0)
		{
			break;
		}

		else if (boardArray[row][col - spaces] == QUEEN * -color or boardArray[row][col - spaces] == ROOK * -color)
		{
			return true;
		}

		else
		{
			break;
		}
	}

	for (int spaces = 1; row + spaces < NUM_ROWS and col + spaces < NUM_COLS; spaces++)
	{
		if (boardArray[row + spaces][col + spaces] == 0)
		{
			continue;
		}

		else if (boardArray[row + spaces][col + spaces] * color > 0)
		{
			break;
		}

		else if (boardArray[row + spaces][col + spaces] == QUEEN * -color or boardArray[row + spaces][col + spaces] == BISHOP * -color)
		{
			return true;
		}

		else
		{
			break;
		}
	}

	for (int spaces = 1; row + spaces < NUM_ROWS and col - spaces >= 0; spaces++)
	{
		if (boardArray[row + spaces][col - spaces] == 0)
		{
			continue;
		}

		else if (boardArray[row + spaces][col - spaces] * color > 0)
		{
			break;
		}

		else if (boardArray[row + spaces][col - spaces] == QUEEN * -color or boardArray[row + spaces][col - spaces] == BISHOP * -color)
		{
			return true;
		}

		else
		{
			break;
		}
	}

	for (int spaces = 1; row - spaces >= 0 and col + spaces < NUM_COLS; spaces++)
	{
		if (boardArray[row - spaces][col + spaces] == 0)
		{
			continue;
		}

		else if (boardArray[row - spaces][col + spaces] * color > 0)
		{
			break;
		}

		else if (boardArray[row - spaces][col + spaces] == QUEEN * -color or boardArray[row - spaces][col + spaces] == BISHOP * -color)
		{
			return true;
		}

		else
		{
			break;
		}
	}

	for (int spaces = 1; row - spaces >= 0 and col - spaces >= 0; spaces++)
	{
		if (boardArray[row - spaces][col - spaces] == 0)
		{
			continue;
		}

		else if (boardArray[row - spaces][col - spaces] * color > 0)
		{
			break;
		}

		else if (boardArray[row - spaces][col - spaces] == QUEEN * -color or boardArray[row - spaces][col - spaces] == BISHOP * -color)
		{
			return true;
		}

		else
		{
			break;
		}
	}

	return false;
}

int Board::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
	int whiteKingPos, blackKingPos, removedPiece, piece = boardArray[fromRow][fromCol];
	removedPiece = 0;
	whiteKingPos = getPieceVector(KING, WHITE)[0];
	blackKingPos = getPieceVector(KING, BLACK)[0];
	bool capture = false;

	if ((fromRow >= NUM_ROWS || fromRow < 0) || (fromCol >= NUM_COLS || fromCol < 0))
	{
		cout << "Coordenadas de partida("<< fromRow << ", " << fromCol <<  ") inválidas\n";
		return ERROR;
	}

	if ((toRow >= NUM_ROWS || toRow < 0) || (toCol >= NUM_COLS || toCol < 0))
	{
		cout << "Coordenadas de chegada("<< toRow << ", " << toCol <<  ") inválidas\n";
		return ERROR;
	}

	if (boardArray[fromRow][fromCol] == 0)
	{
		cout << "Posição ("<< fromRow << ", " << fromCol <<  ") desocupada\n";
		return ERROR;
	}

	if (piece * player < 0)
	{
		cout << "O turno é do jogador " << (player == 1 ? "branco" : "preto") << "\n";
		return ERROR;
	}

	if (piece == KING)
	{
		if (isCheck(toRow, toCol, WHITE))
		{
			cout << "Rei ficaria em cheque\n";
			return ERROR;
		}
	}

	else if (piece == -KING)
	{
		if(isCheck(toRow, toCol, BLACK))
		{
			cout << "Rei ficaria em cheque\n";
			return ERROR;
		}
	}

	if (isMoveLegal(fromRow, fromCol, toRow, toCol))
	{
		if(boardArray[toRow][toCol] != 0)
		{
			removedPiece = removePiece(toRow, toCol);
			capture = true;
		}
		if (piece == KING and whiteQueenCastle and toRow == 0 and toCol == 2)
		{
			removePiece(0, 0);
			putPiece(ROOK, 0, 3);
		}
		else if (piece == KING and whiteKingCastle and toRow == 0 and toCol == 6)
		{
			removePiece(0, 7);
			putPiece(ROOK, 0, 5);
		}
		else if (piece == -KING and blackQueenCastle and toRow == 7 and toCol == 2)
		{
			removePiece(7, 0);
			putPiece(-ROOK, 7, 3);
		}
		else if (piece == -KING and blackKingCastle and toRow == 7 and toCol == 6)
		{
			removePiece(7, 7);
			putPiece(-ROOK, 7, 5);
		}

		removePiece(fromRow, fromCol);
		putPiece(piece, toRow, toCol);

		if (piece == KING)
		{
			whiteKingPos = getPieceVector(KING, WHITE)[0];
		}
		else if (piece == -KING)
		{
			blackKingPos = getPieceVector(KING, BLACK)[0];
		}

		if((piece > 0 and isCheck(whiteKingPos/NUM_ROWS, whiteKingPos % NUM_COLS, WHITE) and piece != KING) or (piece < 0 and isCheck(blackKingPos/NUM_ROWS, blackKingPos % NUM_COLS, BLACK) and piece != -KING))
		{
			removePiece(toRow, toCol);
			putPiece(piece, fromRow, fromCol);
			putPiece(removedPiece, toRow, toCol);
			cout << "Rei em cheque\n";
			return ERROR;
		}
	}
	else
	{
		cout << "Movimento inválido\n";
		return ERROR;
	}

	if ((piece == PAWN and toRow == 7) or (piece == -PAWN and toRow == 0))
	{
		removePiece(toRow, toCol);
		putPiece(QUEEN * piece, toRow, toCol);
	}

	if (piece == KING)
	{
		whiteKingCastle = whiteQueenCastle = false;
	}

	if (piece == -KING)
	{
		blackKingCastle = blackQueenCastle = false;
	}

	if (piece == ROOK and fromRow == 0 and fromCol == 0 and whiteQueenCastle == true)
	{
		whiteQueenCastle == false;
	}
	else if (piece == ROOK and fromRow == 0 and fromCol == 7 and whiteKingCastle == true)
	{
		whiteKingCastle == false;
	}
	if (piece == -ROOK and fromRow == 7 and fromCol == 0 and blackQueenCastle == true)
	{
		blackQueenCastle == false;
	}
	if (piece == -ROOK and fromRow == 7 and fromCol == 7 and blackKingCastle == true)
	{
		blackKingCastle == false;
	}

	drawCounter++;
	setPlayer(-player);

	if (capture || piece == PAWN || piece == -PAWN)
	{
		drawCounter = 0;
	}

	return 0;
}

bool Board::canMovePiece(int fromRow, int fromCol, int toRow, int toCol)
{
	int whiteKingPos, blackKingPos, removedPiece, piece = boardArray[fromRow][fromCol];
	removedPiece = 0;
	whiteKingPos = getPieceVector(KING, WHITE)[0];
	blackKingPos = getPieceVector(KING, BLACK)[0];

	if ((fromRow >= NUM_ROWS || fromRow < 0) || (fromCol >= NUM_COLS || fromCol < 0))
	{
		cout << "Coordenadas de partida("<< fromRow << ", " << fromCol <<  ") inválidas\n";
		return false;
	}

	if ((toRow >= NUM_ROWS || toRow < 0) || (toCol >= NUM_COLS || toCol < 0))
	{
		cout << "Coordenadas de chegada("<< toRow << ", " << toCol <<  ") inválidas\n";
		return false;
	}

	if (boardArray[fromRow][fromCol] == 0)
	{
		cout << "Posição ("<< fromRow << ", " << fromCol <<  ") desocupada\n";
		return false;
	}

	if (piece * player < 0)
	{
		return false;
	}

	if (piece == KING)
	{
		if (isCheck(toRow, toCol, WHITE))
		{
			return false;
		}
	}

	else if (piece == -KING)
	{
		if(isCheck(toRow, toCol, BLACK))
		{
			return false;
		}
	}

	if (isMoveLegal(fromRow, fromCol, toRow, toCol))
	{
		if(boardArray[toRow][toCol] != 0)
		{
			removedPiece = removePiece(toRow, toCol);
		}

		removePiece(fromRow, fromCol);
		putPiece(piece, toRow, toCol);

		if (piece == KING)
		{
			whiteKingPos = getPieceVector(KING, WHITE)[0];
		}
		else if (piece == -KING)
		{
			blackKingPos = getPieceVector(KING, BLACK)[0];
		}

		if((piece > 0 and isCheck(whiteKingPos/NUM_ROWS, whiteKingPos % NUM_COLS, WHITE)) or (piece < 0 and isCheck(blackKingPos/NUM_ROWS, blackKingPos % NUM_COLS, BLACK)))
		{
			removePiece(toRow, toCol);
			putPiece(piece, fromRow, fromCol);
			putPiece(removedPiece, toRow, toCol);
			return false;
		}
		else
		{
			removePiece(toRow, toCol);
			putPiece(piece, fromRow, fromCol);
			putPiece(removedPiece, toRow, toCol);
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Board::isCheckMate(int color)
{
	vector<int> legalMoves, pieceVector;
	vector<int>::iterator it, it2;
	int colorKingPos = getPieceVector(KING, color)[0];
	int row = colorKingPos / NUM_ROWS;
	int col = colorKingPos % NUM_COLS;

	if(!isCheck(row, col, color) and !moveList(color).empty())
	{
		return false;
	}

	for (int piece = KING; piece >= PAWN; piece--)
	{
		pieceVector = getPieceVector(piece, color);

		for (it = pieceVector.begin(); it != pieceVector.end(); it++)
		{
			legalMoves = getMovesVector(*it / NUM_ROWS, *it % NUM_COLS);

			for (it2 = legalMoves.begin(); it2 != legalMoves.end(); it2++)
			{
				if(canMovePiece(*it / NUM_ROWS, *it % NUM_COLS, *it2 / NUM_ROWS, *it2 % NUM_COLS))
				{
					return false;
				}
			}
		}
	}

	return true;
}

int Board::isGameEnd()
{
	if (drawCounter >= DRAW)
	{
		return 0;
	}

	else if (isCheckMate(player))
	{
		return -player;
	}

	else
	{
		return ERROR;
	}

}

vector<pair<int, int>> Board::moveList(int color)
{
	vector<pair<int, int>> moveList;
	vector<int> pieces;
	vector<int> candidateMoves;
	vector<int>::iterator it, it2;
	int originalPlayer = player;

	if(color != WHITE and color != BLACK)
	{
		cout << "Cor inválida\n";
		return {{ERROR, ERROR}};
	}

	player = color;

	for (int piece = KING; piece >= PAWN; piece--)
	{
		pieces = getPieceVector(piece, color);

		for (it = pieces.begin(); it != pieces.end(); it++)
		{
			candidateMoves = getMovesVector(*it / NUM_ROWS, *it % NUM_COLS);

			for (it2 = candidateMoves.begin(); it2 != candidateMoves.end(); it2++)
			{
				if (canMovePiece(*it / NUM_ROWS, *it % NUM_COLS, *it2 / NUM_ROWS, *it2 % NUM_COLS))
				{
					moveList.push_back(make_pair(*it, *it2));
				}
			}
		}
	}

	player = originalPlayer;

	return moveList;
}
