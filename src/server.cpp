#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "server.h"
#include "db.h"

/*
commands
get all
get day
get hour number
add lp name
rm
*/

std::vector<std::string> split(std::string input)
{
  std::vector<std::string> commands;
  std::string word;
  for(int i = 0; i < input.length(); ++i)
  {
    if(input.at(i) == ' ')
    {
      commands.push_back(word);
      word = "";
    }else{
      word += input.at(i);
    }
  }
  commands.push_back(word);
  return commands;
}

std::string response(std::vector<std::string> input)
{
  if(input[0] == "get")
  {
    if(input[1] == "all")
    {
      std::cout << "get all" << std::endl;
      return readData();
    }else if(input[1] == "hour"){

    }else if(input[1] == "day"){

    }
  }else if(input[0] == "add"){
    addContact(input[1],input[2]);
    return "added";
  }else if(input[0] == "rm"){
    
  }else{
    std::cout << "Not proper command" << std::endl;
    return "no command";
  }
}

void server()
{
  int listenfd = 0, connfd = 0, n = 0;
  struct sockaddr_in serv_addr;
  
  char recvBuff[1024];
  char sendBuff[1024];
  std::string recvBuffs;

  std::vector<std::string> commands;
  std::string res;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(8080);

  bind(listenfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));

  listen(listenfd, 10);
  
  while(1)
  {
    connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
    std::cout << "user connect" << std::endl;
    //receive data
    n = read(connfd,recvBuff,sizeof(recvBuff)-1);
    recvBuffs = recvBuff;
    recvBuff[n] = 0;
    std::cout << "recvBuff: " << recvBuffs << std::endl;

    commands = split(recvBuffs);
    res = response(commands);
    //send data
    snprintf(sendBuff,sizeof(sendBuff), res.c_str());
    write(connfd,sendBuff,strlen(sendBuff));
    close(connfd);
    sleep(1);
  }
}
