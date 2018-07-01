#include "includes/ia.hpp"
#include <iostream>
#include <cmath>
#include <chrono>
#include <limits>
#include <cassert>
#include <algorithm>

using namespace std;

static_assert(std::numeric_limits<double>::is_iec559, "IEEE 754 required");

Ia::Ia()
{
}


double Ia::getMaterialScore(Board board)
{
	double score = 0;
	int gameEnd;
	vector<int> pieceList;
	vector<int>::iterator it;

	score += ((double) board.getPieceVector(PAWN, WHITE).size() - (double) board.getPieceVector(PAWN, BLACK).size()) * PAWN_WEIGHT;
	score += ((double) board.getPieceVector(ROOK, WHITE).size() - (double) board.getPieceVector(ROOK, BLACK).size()) * ROOK_WEIGHT;
	score += ((double) board.getPieceVector(KNIGHT, WHITE).size() - (double) board.getPieceVector(KNIGHT, BLACK).size()) * KNIGHT_WEIGHT;
	score += ((double) board.getPieceVector(BISHOP, WHITE).size() - (double) board.getPieceVector(BISHOP, BLACK).size()) * BISHOP_WEIGHT;
	score += ((double) board.getPieceVector(QUEEN, WHITE).size() - (double) board.getPieceVector(QUEEN, BLACK).size()) * QUEEN_WEIGHT;

	gameEnd = board.isGameEnd();

	if(gameEnd != ERROR)
	{
		score += gameEnd * KING_WEIGHT;
	}

	return score;
}

double Ia::getMobilityScore(Board board)
{
	double score = 0;

	score += (double) board.moveList(WHITE).size() - (double) board.moveList(BLACK).size();

	return score;
}

double Ia::utility(Board board, int color)
{
	assert(color == WHITE or color== BLACK);
	return (getMaterialScore(board) + MOBILITY_WEIGHT * getMobilityScore(board)) * color;
}

double Ia::alphaBetaSearch(Board board, int color, bool startClock)
{
	double bestUtility;

	assert(color == WHITE or color == BLACK);

	if (startClock)
	{
		start = chrono::steady_clock::now();
	}


	if (board.getPlayer() == color)
	{
		bestUtility = maxValue(board, -INFINITY, INFINITY, color);
	}
	else
	{
		bestUtility = minValue(board, -INFINITY, INFINITY, color);
	}

	return bestUtility;
}

double Ia::maxValue(Board board, double alpha, double beta, int color)
{
	double value;
	vector<pair<int,int>> actions;
	vector<pair<int,int>>::iterator it;
	Board resultBoard;

	if (terminalState(board))
	{
		return utility(board, color);
	}

	value = -INFINITY;
	actions = board.moveList(color);

	for(it = actions.begin(); it != actions.end(); it++)
	{
		resultBoard = board;
		resultBoard.movePiece(it->first / NUM_ROWS, it->first % NUM_COLS, it->second / NUM_ROWS, it->second % NUM_COLS);
		value = max(value, minValue(resultBoard, alpha, beta, color));
		if (value >= beta)
		{
			return value;
		}
		alpha = max(alpha, value);
	}
	return value;
}

double Ia::minValue(Board board, double alpha, double beta, int color)
{
	double value;
	vector<pair<int,int>> actions;
	vector<pair<int,int>>::iterator it;
	Board resultBoard;

	if (terminalState(board))
	{
		return utility(board, color);
	}

	value = INFINITY;
	actions = board.moveList(-color);

	for(it = actions.begin(); it != actions.end(); it++)
	{
		resultBoard = board;
		resultBoard.movePiece(it->first / NUM_ROWS, it->first % NUM_COLS, it->second / NUM_ROWS, it->second % NUM_COLS);
		value = min(value, maxValue(resultBoard, alpha, beta, color));
		if (value <= alpha)
		{
			return value;
		}
		beta = min(beta, value);
	}

	return value;
}


bool Ia::terminalState(Board board)
{
	auto end = chrono::steady_clock::now();
	auto diff =chrono::duration_cast<chrono::seconds>(end - start).count();

	if(board.isGameEnd() != ERROR)
	{
		return true;
	}
	else if(diff > MAX_SECONDS)
	{
		return true;
	}
	else
	{
		return false;
	}

}

vector<pair<int, int>> Ia::bestMoves(Board board)
{
	vector<pair<int, int>> bestMoves;
	vector<pair<int, int>> actions;
	vector<pair<double, pair<int, int>>> movesWithValues;
	vector<pair<int,int>>::iterator it;
	vector<pair<double, pair<int, int>>>::reverse_iterator it2;
	double value;
	Board childBoard;
	int i = 0;

	actions = board.moveList(board.getPlayer());
	start = chrono::steady_clock::now();

	for(it = actions.begin(); it != actions.end(); it++)
	{
		childBoard = board;
		childBoard.movePiece(it->first / NUM_ROWS, it->first % NUM_COLS, it->second / NUM_ROWS, it->second % NUM_COLS);
		value = alphaBetaSearch(childBoard, board.getPlayer(), false);
		movesWithValues.push_back(make_pair(value, *it));
	}

	sort(movesWithValues.begin(), movesWithValues.end());


	for(it2 = movesWithValues.rbegin(); it2 != movesWithValues.rend() and i < N_BEST_MOVES; it2++, i++)
	{
		bestMoves.push_back(make_pair(it2->second.first, it2->second.second));
	}

	return bestMoves;
}