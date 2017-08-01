#ifndef DB_H
#define DB_H
#include <string>
#include <vector>

class Data
{
 private:
  int ID;
  std::string LP;
  std::string Time;
  std::string Date;
 public:
  Data(int id, std::string lp, std::string Time, std::string Date);
  std::string getLP();
  std::string getTime(std::string lp);
  std::string getDate(std::string lp);
};

void writeData(std::vector<Data> data);

#endif
