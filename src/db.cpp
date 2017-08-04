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

void Data::setLP(std::string name)
{
  Name = name;
}

std::string Data::getLP()
{

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
    output << "Name" << data[i].getName() << std::endl;
    output << "Time:" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << std::endl;
    output << "Date:" << now->tm_mon << ":" << now->tm_mday << ":" << now->tm_year+1900 << std::endl;
  }
}

void addContact(std::string lp, std::string name)
{
  std::ofstream output;
  output.open("contactData");
  output << "LP:" << lp << std::endl;
  output << "name:" << name << std::endl;
}

std::string checkContact(std::string lp)
{
  std::string data;
  std::ifstream inputFile("contactData");
  bool get = false;
  if(inputFile.is_open())
  {
    while(!inputFile.eof())
    {
      std::string input;
      std::getline(inputFile,input);
      //std::cout << input.substr(0,6) << std::endl;
      //std::cout << input << std::endl;
      //std::cout << input.substr(0,3) << std::endl;
      if(input.substr(0,3) == "LP:")
      {
	//std::cout << input.substr(3,input.length()) << std::endl;
	if(input.substr(3,input.length()) == lp)
	{
	  get = true;
	}
      }else if(input.substr(0,5) == "name:" && get == true){
	return input.substr(5,input.length());
      }
    }
  }
  return "";
}

std::string readData()
{
  //use check contact
  std::string data;
  std::ifstream inputFile("lpData");
  if(inputFile.is_open())
  {
    std::string name;
    while(!inputFile.eof())
    {
      std::string input;
      std::getline(inputFile,input);
      if(input.substring(0,2) == "ID")
      {
	name = checkContact();
	if(name != "")
	{

	}else{ 
	  data+=(input + "|");
	}
      }
    }
  }
  return data;
}
