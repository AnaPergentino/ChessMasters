#include "includes/PGN.hpp"

using namespace std;
/*
int main(){

  ifstream pgnFile ("pgnTestFiles/game1.pgn");
  PGN(pgnFile);
}*/
PGN::PGN()
{
}

PGN::PGN(ifstream& pgnFile)
{
    this->moves = vector<string>(1);
    string line;
    while (getline(pgnFile, line))
    {
        string dataName;
        string value;
        int stringStart;
        int spacePosition;
        int stringEnd;

        switch (line[0])
        {
        case '[':
            spacePosition = line.find(' ');
            stringStart = line.find('"');
            stringEnd = line.find('"', stringStart + 1);

            dataName = line.substr(1, spacePosition - 1);
            value = line.substr(stringStart + 1, (stringEnd - 1) - stringStart);

            this->pgnHeader(dataName, value);
            break;
    /*    case '%':
            //
            break;*/
        default:
            // jogo - parte dos movimentos
            this->addMoves(line);
            break;
        }
    }

    if (this->white.size() < 1 || this->black.size() < 1 || this->result.size() < 1)
    {
        throw 8;
    }

    if (this->result != "*")
    {
        throw 9;
    }
}
void PGN::pgnHeader(const string varName, const string value) {
  if (varName == "Event")
  {
      this->event = value;
  }
  else if (varName == "Date")
  {
      this->date = value;
  }
  else if (varName == "Round")
  {
      this->round = value;
  }
  else if (varName == "White")
  {
      this->white = value;
  }
  else if (varName == "Black")
  {
      this->black = value;
  }
  else if (varName == "Result")
  {
      this->result = value;
  }
}

void PGN::addMoves(const string strMove)
{
    string strMoveClean;

    for (int i = 0; i < strMove.size(); i++)
    {
        if (isdigit(strMove.at(i)))
        {

            if (i - 1 >= 0 && isdigit(strMove.at(i - 1)))
            {
                continue;
            }
             else if (i + 1 < strMove.size())
             {
                if (strMove.at(i + 1) == '.' || isdigit(strMove.at(i + 1))) {
                    continue;
                }
            }
        }
        else if (strMove.at(i) == '.')
        {
            continue;
        }

        strMoveClean.push_back(strMove.at(i));
    }

    for (int i = 0; i < strMoveClean.size(); i++)
    {
        if (strMoveClean.at(i) == ' ')
        {
            if (this->moves.back() != "")
            {
                this->moves.push_back("");
            }

            continue;
        }
        this->moves.back().push_back(strMoveClean.at(i));
    }
}

string PGN::getResultString(Board board) {
    int game = board.isGameEnd();
    switch (game) {
        case 0://Empate
            return "1/2-1/2";
        case 1:
        // Branco ganha
            return "1-0";
        case -1:
        // Preto ganha
            return "0-1";
        case 10://ERROR
            return "*";
        default:
            return "*";
    }
}
