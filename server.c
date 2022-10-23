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
    read(fd,buff,sizeof(buff));
    printf("Client %s",buff);
    bzero(buff,SIZE);
    int n = 0;
    while((buff[n++] = getchar()) != '\n');
    write(fd,buff,sizeof(buff));
    if(strncmp("exit",buff,4) == 0)
    {
      printf("Exit...");
      break;
    }
  }
}


int main()
{
  int server_socket_fd, connection_socket_fd;
  struct sockaddr_in server , client;

  // Create a socket
  server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(server_socket_fd == -1)
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
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(8080);

  //Biding
  if(bind(server_socket_fd,(struct sockaddr *)&server, sizeof(server)) == 0)
  {
    printf("Binding successful...\n");
  }
  else
  {
    perror("Binding failed");
    exit(1);
  }

  //Listening
  if(listen(server_socket_fd,1) == 0)
  {
    printf("Listening...\n");
  }
  else
  {
    perror("Listening failed...");
    exit(1);
  }

  //Accepting
  connection_socket_fd = connect(server_socket_fd,(struct sockaddr *)&client,sizeof(client));
  if(connection_socket_fd == 0)
  {
    printf("Connected...\n");
  }
  else
  {
    perror("Connection failed...");
    exit(1);
  }
 

  //Closing the connection
  close(server_socket_fd);
  return 0;
}
