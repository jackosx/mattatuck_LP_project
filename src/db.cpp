#include "db.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <fstream>

Data::Data(int id, std::string lp)
{
  ID = id;
  LP = lp;
}

std::string Data::getLP()
{
  return LP;
}

std::string Data::getTime(std::string lp)
{
  return Date;
}

std::string Data::getDate(std::string lp)
{
  return Time;
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

std::string readData()
{
  std::string data;
  std::ifstream inputFile("lpData");
  if(inputFile.is_open())
  {
    while(!inputFile.eof())
    {
      std::string input;
      std::getline(inputFile,input);
      data+=(input + "\n");
    }
  }
  return data;
}
