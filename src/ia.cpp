#include "includes/ia.hpp"
#include <iostream>

using namespace std;

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

double Ia::utility(Board board)
{
	return getMaterialScore(board) + MOBILITY_WEIGHT * getMobilityScore(board);
}