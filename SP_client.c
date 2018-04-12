#include<stdio.h>
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

int main(int argc, char *argv[]){
 char server_msg[255];
 int remote_s, p_num;
 socklen_t len;
 struct sockaddr_in s_address;

  if(argc != 3){
   printf("Call model:%s <IP> <Port#>\n", argv[0]);
  }
  if((remote_s = socket(AF_INET, SOCK_STREAM, 0))<0){
   fprintf(stderr, "Cannot create socket\n");
   exit(1);
  }

  s_address.sin_family = AF_INET;
  sscanf(argv[2], "%d", &p_num);
  s_address.sin_port = htons((uint16_t)p_num);

  if(inet_pton(AF_INET,argv[1], &s_address.sin_addr)<0){
   fprintf(stderr, "inet_pton() has failed\n");
   exit(2);
  }

  if(connect(remote_s,(struct sockaddr *) &s_address, sizeof(s_address))<0){
   fprintf(stderr, "connect() has failled, exiting\n");
   exit(3);
  }

  while(1){
   if(read(remote_s, server_msg, 255)<0){
    fprintf(stderr, "read() error\n");
    exit(3);
   }
  fprintf(stderr, "Server's message: %s\n", server_msg);
  fprintf(stderr,"Enter the $ sign to quit or a message for the server\n");
  fgets(server_msg, 254, stdin);
  if(server_msg[0] == '$'){  
   close(remote_s);
   exit(0);
  }
  write(remote_s, server_msg, strlen(server_msg)+1);
 }
}
 







