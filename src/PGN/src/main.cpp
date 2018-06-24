#include <fstream>
#include <iostream>
using namespace std;

#include "includes/main.hpp"

PGN::gameMove move;
PGN::gameHeader header;

int main(){
  int count = 0;
    string line;
    ifstream arq ("game1.pgn");
    if (arq.is_open())
    {
      while ( arq.good() )
      {
        getline (arq,line);
        cout << line << endl;
        count = readFile(line,count);
      }
      arq.close();
    }
    else cout << "Unable to open file";
}

int readFile(string line,int count){
  if (line.compare(0,6,"[Event",0,6)==0 && count==0){
    header.setEvent(line);
    count++;
    cout << header.getEvent() << "nome do evento" << endl;
  }
  else if (line.compare(0,5,"[Site",0,5)==0 && count==1){
    header.setSite(line);
    count ++;
    cout << header.getSite() << "local do evento" << endl;
  }
  else if (line.compare(0,5,"[Date",0,5)==0 && count==2){
    header.setDate(line);
    count ++;
    cout << header.getDate() << "data do evento" << endl;
  }
  else if (line.compare(0,6,"[Round",0,6)==0 && count==2){
    header.setRound(line);
    count ++;
    cout << header.getRound() << "rodada" << endl;
  }
  return count;
}
