#include <iostream>
#include <cassert>
namespace PGN{
  class gameHeader{
    private:
      std::string event; //nome do torneio ou evento
      std::string site;  //local do evento
      std::string date;				//data do evento
      std::string round;      								//numero da partida no evento
      std::string white;			//jogador peças brancas
      std::string black;			 //jogador peças pretas
      std::string result;
    public:
      void setEvent(std::string str);
      std::string getEvent();
      void setSite(std::string str);
      std::string getSite();
      void setDate(std::string str);
      std::string getDate();
      void setRound(std::string str);
      std::string getRound();
      void setWhite(std::string str);
      std::string getWhite();
      void setBlack(std::string str);
      std::string getBlack();
      void setResult(std::string str);
      std::string getResult();
  };
};
