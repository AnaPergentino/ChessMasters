#include <iostream>
#include <cassert>
using namespace std;

#include "includes/gameHeader.hpp"

void PGN::gameHeader::setEvent(std::string str)
{
  this->event = str;
}
std::string PGN::gameHeader::getEvent()
{
  return this->event;
}
void PGN::gameHeader::setSite(std::string str)
{
  this->site = str;
}
std::string PGN::gameHeader::getSite()
{
  return this->site;
}
void PGN::gameHeader::setDate(std::string str)
{
  this->date = str;
}
std::string PGN::gameHeader::getDate()
{
  return this->date;
}
void PGN::gameHeader::setRound(std::string str)
{
  this->round = str;
}
std::string PGN::gameHeader::getRound()
{
  return this->round;
}
void PGN::gameHeader::setWhite(std::string str)
{
  this->white = str;
}
std::string PGN::gameHeader::getWhite(){
  return this->white;
}
void PGN::gameHeader::setBlack(std::string str)
{
  this->black = str;
}
std::string PGN::gameHeader::getBlack()
{
  return this->black;
}
void PGN::gameHeader::setResult(std::string str)
{
  this->result = str;
}
std::string PGN::gameHeader::getResult()
{
  return this->result;
}
