#include <iostream>
#include <cassert>
#include "gameHeader.hpp"
#include "gameMove.hpp"

int readFile(string line,int count);

namespace PGN{
  struct gameData{
    PGN::gameHeader header;
    PGN::gameMove *moves;
  };
}

/*
[Event "F/S Return Match"]
[Site "Belgrade, Serbia JUG"]
[Date "1992.11.04"]
[Round "29"]
[White "Fischer, Robert J."]
[Black "Spassky, Boris V."]
[Result "1/2-1/2"]

Letter abbreviation:

K - King
Q - Queen
R - Rook (torre)
B - Bishop
N - Knight
P or empty - Paw (peão)

x - capture
If the move is a checking move, the plus sign "+" is also appended; if the move is a checkmating move, the number sign "#" is appended instead.

*/
