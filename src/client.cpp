#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>

int main(int argc, char *argv[])
{
  int sockfd = 0, n = 0;
  char recvBuff[1024];
  struct sockaddr_in serv_addr;

  if(argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " <ip of server>" << std::endl;
    return 1;
  }

  memset(recvBuff, '0',sizeof(recvBuff));

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    std::cout << "Couldn't create socket" << std::endl;
    return 1;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
  {
    std::cout << "inet_pton error" << std::endl;
    return 1;
  }

  if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
  {
    std::cout << "failed to connect" << std::endl;
    return 1;
  }

  char sendBuff[] = "add 283ZGP whyyyyyyyyy";
  write(sockfd,sendBuff,strlen(sendBuff));

  while((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
  {
    //recvBuff[n] = 0;
    /*
    if(fputs(recvBuff,stdout) == EOF)
    {
      std::cout << "Fputs error" << std::endl;
    }
    */
  }
  std::string t = recvBuff;
  recvBuff[n] = 0;
  std::cout << t;

  if(n < 0)
  {
    std::cout << "Read error" << std::endl;
  }
  //while(1){}
}
