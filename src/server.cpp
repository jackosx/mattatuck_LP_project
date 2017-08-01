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

#include "server.h"

void server()
{
  int listenfd = 0, connfd = 0;
  struct sockaddr_in serv_addr;

  int n = 0;
  
  char sendBuff[1024];
  time_t ticks;

  char recvBuff[1024];
  
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  bind(listenfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));

  listen(listenfd, 10);
  
  while(1)
  {
    connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
    n = read(connfd, recvBuff,sizeof(recvBuff)-1);
    
      //for(int i = 0; i < sizeof(recvBuff); ++i)
      //{

      //}
      std::cout << recvBuff << std::endl;
      
      recvBuff[n] = 0;	
    
    ticks = time(NULL);
    std::cout << "time done" << std::endl;
    snprintf(sendBuff,sizeof(sendBuff), "%.24s\r\n",ctime(&ticks));
    std::cout << "converted" << std::endl;
    write(connfd,sendBuff,strlen(sendBuff));
    std::cout << "sent" << std::endl;

    close(connfd);
    sleep(1);
  }
}
