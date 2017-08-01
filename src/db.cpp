#include "db.h"
#include <iostream>
#include <fstream>
#include <ctime>

Data::Data(int id, std::string lp, std::string time, std::string date)
{
  ID = id;
  LP = lp;
  Time = time;
  Date = date;
}

std::string Data::getLP()
{
  return LP;
}

std::string Data::getTime(std::string lp)
{

}

std::string Data::getDate(std::string lp)
{

}

void writeData(std::vector<Data> data)
{
  time_t t = time(0);
  struct tm * now = localtime(&t);
  std::ofstream output;
  output.open("lpData");
  
  for(int i = 0; i < data.size(); ++i)
  {
    output << "ID:" << i << std::endl;
    output << "LP:" << data[i].getLP() << std::endl;
    output << "Time:" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << std::endl;
    output << "Date:" << now->tm_mon << ":" << now->tm_mday << ":" << now->tm_year+1900 << std::endl;
  }
}
