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

void serviceClient(int s_des);
int main(int argc, char *argv[]){
  int s_des, remote_c, p_Num;
  socklen_t len;
  struct sockaddr_in s_add,c_add;

  if(argc != 2){
   printf("Call model: %s <Port #>\n", argv[0]);
   exit(0);
  }
  if ((s_des=socket(AF_INET, SOCK_STREAM, 0))<0){
   fprintf(stderr, "Cannot create socket\n");
   exit(1);
  }
  s_add.sin_family = AF_INET;
  s_add.sin_addr.s_addr = htonl(INADDR_ANY);
  sscanf(argv[1], "%d", &p_Num);
  s_add.sin_port = htons((uint16_t)p_Num);
  bind(s_des,(struct sockaddr*)&s_add,sizeof(s_add));
  listen(s_des, 5);

  while(1){
   remote_c=accept(s_des,(struct sockaddr*)&c_add,sizeof(c_add));
   printf("***Client is ready for communication***\n");
   if(!fork())
   serviceClient(remote_c);
   close(remote_c);
  }
}

void serviceClient(int s_des){
  char buff[255];
  static int client;
  struct sockaddr_in c_add;

  while(1){
  // fprintf(stderr, "Enter message for a client:\n");
   //fgets(buff, 254, stdin);
 //  if(!read(s_des, buff, 255)){
  //  close(s_des);
    //if(close(s_des)<0)
    //fprintf(stderr,"Ooops!! Current client is busy now\nWaiting for a new client...\n");
    if ( dup2(client, 0) < 0 )
    perror("Dup stdin");
    if ( dup2(client, 1) < 0 )
    perror("Dup stdout");
    if ( dup2(client, 2) < 0 )
    perror("Dup stderr");
    read(0, buff, 255);
    printf("Client: ");
    printf("Connected: %s:%d\n", inet_ntoa(c_add.sin_addr), ntohs(c_add.sin_port));
    puts(buff);
    //buff[strlen(buff)]='\0';
    write(stderr,system(buff), 1000);
    exit(0);
   
  }
}
