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

std::string rec(std::string input)
{
  if(input == "all")
  {
    return readData();
  }else if(input == ""){

  }
}

void command(int listenfd)
{
  int connfd = 0;
  int n = 0;
  char recvBuff[1024];
  char sendBuff[1024];
  while(1)
  {
    connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
    n = read(connfd, recvBuff,sizeof(recvBuff)-1);
    std::string recvBuffs = recvBuff;
    recvBuff[n] = 0;
    std::string response = rec(recvBuffs);
    snprintf(sendBuff,sizeof(sendBuff), response.c_str());
    write(connfd,sendBuff,strlen(sendBuff));
    close(connfd);
    sleep(1);
  }
}

void sendText(std::vector<std::string> data)
{
  int connfd = 0, listenfd = 0, n = 0;
  char sendBuff[1024];
  struct sockaddr_in serv_addr;

  //listenfd = socket(AF_NET, SOCK_STREAM, 0);

  while(1)
  {
    //connfd = accept(listenfd,(struct sockaddr*),NULL,NULL);
    
  }
}

void server()
{
  int listenfd = 0, connfd = 0;
  struct sockaddr_in serv_addr;
  char sendBuff[1024];
  
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  bind(listenfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));

  listen(listenfd, 10);
  
  command(listenfd);
}
