#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>

#define SIZE 1014
#define STD_IN 0

void communicate(int fd)
{
  char buff[SIZE];
  while(1)
  {
    bzero(buff,SIZE);
    printf("Enter Message\n");
    read(STD_IN,buff,sizeof(buff));
    write(fd,buff,sizeof(buff));
    bzero(buff,SIZE);
    read(fd,buff,SIZE);
    printf("Server Sent %s",buff);
    if(strncmp("exit",buff,4) == 0)
    {
      printf("Exit...");
      break;
    }
  }
}

int main()
{
  int socket_fd;
  struct sockaddr_in server;

  // Create a socket
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_fd == -1)
  {
    perror("socket creation failed\n");
    exit(1);
  }
  else
  {
    printf("Socket created successfully...\n");
  }

  // Server Config
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(8080);

  //Accepting
  int connection_socket_fd = connect(socket_fd,(struct sockaddr *)&server,sizeof(server));
  if(connection_socket_fd == 0)
  {
    printf("Connected...\n");
  }
  else
  {
    perror("Connection failed...");
    exit(1);
  }
 

  communicate(socket_fd);

  //Closing the connection
  close(socket_fd);

  return 0;
}
