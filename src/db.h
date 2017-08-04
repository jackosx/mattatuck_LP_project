#ifndef DB_H
#define DB_H
#include <string>
#include <vector>

class Data
{
 private:
  int ID;
  std::string LP;
  std::string Name;
  std::string Time;
  std::string Date;
 public:
  Data(int id, std::string lp);
  std::string getLP();
  std::string getTime(std::string lp);
  std::string getDate(std::string lp);
  void setLP(std::string name);
  std::string getName();
};

void writeData(std::vector<Data> data);
std::string readData();
void addContact(std::string lp,std::string name);
std::string checkContact(std::string lp);
#endif
