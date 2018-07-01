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

double Ia::getPositionScore(Board board)
{
	double score = 0;
	bool endGame;
	vector<int> whitePieceList, blackPieceList;
	vector<int>::iterator it;
	int whiteKingPos, blackKingpos;

	for (int piece = PAWN; piece < KING; piece++)
	{
		whitePieceList = board.getPieceVector(piece, WHITE);
		blackPieceList = board.getPieceVector(piece, BLACK);

		for(it = whitePieceList.begin(); it != whitePieceList.end(); it++)
		{
			switch(piece)
			{
				case PAWN:
					score += PAWN_SCORE_ARRAY[-(*it/8 - 7)][*it % 8];
					break;
				case ROOK:
					score += ROOK_SCORE_ARRAY[-(*it/8 - 7)][*it % 8];
					break;
				case BISHOP:
					score += BISHOP_SCORE_ARRAY[-(*it/8 - 7)][*it % 8];
					break;
				case KNIGHT:
					score += KNIGHT_SCORE_ARRAY[-(*it/8 - 7)][*it % 8];
					break;
				case QUEEN:
					score += QUEEN_SCORE_ARRAY[-(*it/8 - 7)][*it % 8];
					break;
			}
		}
		for(it = blackPieceList.begin(); it != blackPieceList.end(); it++)
		{
			switch(piece)
			{
				case PAWN:
					score -= PAWN_SCORE_ARRAY[*it/8][*it % 8];
					break;
				case ROOK:
					score -= ROOK_SCORE_ARRAY[*it/8][*it % 8];
					break;
				case BISHOP:
					score -= BISHOP_SCORE_ARRAY[*it/8][*it % 8];
					break;
				case KNIGHT:
					score -= KNIGHT_SCORE_ARRAY[*it/8][*it % 8];
					break;
				case QUEEN:
					score -= QUEEN_SCORE_ARRAY[*it/8][*it % 8];
					break;
			}
		}
	}

	whiteKingPos = board.getPieceVector(KING, WHITE)[0];
	blackKingpos = board.getPieceVector(KING, BLACK)[0];
	endGame = (board.getPieceVector(QUEEN, WHITE).empty() and board.getPieceVector(QUEEN, BLACK).empty()) or
			  (!board.getPieceVector(QUEEN, WHITE).empty() and board.getPieceVector(ROOK, WHITE).empty() and board.getPieceVector(BISHOP, WHITE).size() + board.getPieceVector(KNIGHT, WHITE).size() < 2) or
			  (!board.getPieceVector(QUEEN, BLACK).empty() and board.getPieceVector(ROOK, BLACK).empty() and board.getPieceVector(BISHOP, BLACK).size() + board.getPieceVector(KNIGHT, BLACK).size() < 2);			  
	if(endGame)
	{
		score += KING_SCORE_ARRAY_END[-(whiteKingPos/8 -7)][whiteKingPos%8] - KING_SCORE_ARRAY_MID[blackKingpos/8][blackKingpos%8];
	}
	else
	{
		score += KING_SCORE_ARRAY_MID[-(whiteKingPos/8 -7)][whiteKingPos%8] - KING_SCORE_ARRAY_END[blackKingpos/8][blackKingpos%8];

	}
	return score;
}

double Ia::utility(Board board, int color)
{
	assert(color == WHITE or color== BLACK);
	return (getMaterialScore(board) + MOBILITY_WEIGHT * getMobilityScore(board) + getPositionScore(board)) * color;
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

	depth += 1;

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

	depth += 1;

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
	if(board.isGameEnd() != ERROR)
	{
		return true;
	}
	else if(depth >= depthLimit)
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
	double value, timePerMove;
	Board childBoard;
	depth = 0;
	int i = 0;

	actions = board.moveList(board.getPlayer());
	timePerMove = MAX_MILLISECONDS / actions.size();

	for(it = actions.begin(); it != actions.end(); it++)
	{
		childBoard = board;
		childBoard.movePiece(it->first / NUM_ROWS, it->first % NUM_COLS, it->second / NUM_ROWS, it->second % NUM_COLS);
		start = chrono::steady_clock::now();
		depthLimit = 0;
		while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < timePerMove)
		{
			value = alphaBetaSearch(childBoard, board.getPlayer(), false);
			depthLimit += 1;
			depth = 0;
		}
		movesWithValues.push_back(make_pair(value, *it));
	}

	sort(movesWithValues.begin(), movesWithValues.end());


	for(it2 = movesWithValues.rbegin(); it2 != movesWithValues.rend() and i < N_BEST_MOVES; it2++, i++)
	{
		bestMoves.push_back(make_pair(it2->second.first, it2->second.second));
	}

	return bestMoves;
}