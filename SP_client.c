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
 char server_msg[255],rem_s[10];
 int remote_s, p_num;
 socklen_t len;
 struct sockaddr_in s_address;

  if(argc != 3){
   write(2,"Call Model: ./client <server_ip> <server_port_number>",strlen("Call Model: ./client <server_ip> <server_port_number>"));
  }
  if((remote_s = socket(AF_INET, SOCK_STREAM, 0))<0){
   write(2, "Cannot create socket\n",strlen("Cannot create socket\n"));
   exit(1);
  }
  s_address.sin_family = AF_INET;
  sscanf(argv[2], "%d", &p_num);
  s_address.sin_port = htons((uint16_t)p_num);

  if(inet_pton(AF_INET,argv[1], &s_address.sin_addr)<0){
   write(2, "inet_pton() has failed\n",strlen("inet_pton() has failed\n"));
   exit(2);
  }

  if(connect(remote_s,(struct sockaddr *) &s_address, sizeof(s_address))<0){
   write(2, "connect() has failed, exiting\n",strlen("connect() has failed, exiting\n"));
   exit(3);
  }

 
  while(1)
    {
   if(read(remote_s, server_msg, 255)<0){
    write(2, "read() error\n",strlen("read() error\n"));
    exit(3);
   }
  write(2, "\nServer's message: ",strlen("\nServer's message: "));
  write(2,server_msg,strlen(server_msg));
  write(2,"\nType 'quit' to quit or a command to execute on server\n",strlen("\nType 'quit' to quit or a command to execute on server\n"));
  memset(server_msg,'\0',255);
  read(0,server_msg,255);
  server_msg[strlen(server_msg)-1]='\0';
  write(2,"Message to server: ",strlen("Message to server: "));
  write(2,server_msg,strlen(server_msg));
  write(remote_s, server_msg, strlen(server_msg)+1);
  int res = strcmp(server_msg,"quit");
  if( res == 0)
    {  
    close(remote_s);
    exit(0);
    }
  memset(server_msg,'\0',255);
 }
}
 







