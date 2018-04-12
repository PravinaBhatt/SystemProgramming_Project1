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
int main(int argc, char *argv[])
{
  int s_des, remote_c, p_Num;
  socklen_t len;
  struct sockaddr_in s_add;

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

  while(1)
    {
   write(2,"Waiting for Client....\n",strlen("Waiting for Client....\n"));
   remote_c=accept(s_des,(struct sockaddr*)NULL,NULL);
   if(remote_c < 0)
    {
        fprintf(stderr,"Some problem with accept.");
        exit(0);
    }
    else
    {
        fprintf(stderr,"***New Client is ready for communication***....\n");
        if(!fork())
        {
         serviceClient(remote_c);
        }
        else
         {
            close(remote_c);
         }
    }
  }
}

void serviceClient(int s_des)
{
  char buff[255];

  if ( dup2(s_des, 0) < 0 )
    perror("Dup stdin");  
  if ( dup2(s_des, 1) < 0 )
    perror("Dup stdout");
  if ( dup2(s_des, 2) < 0 )
    perror("Dup stderr");

  write(2,"Connected to me.",strlen("Connected to me.\0"));

  while(1)
    {
     memset(buff,'\0',255);
     read(0, buff, 255);
     if(strcmp(buff,"quit") == 0)
      {
        close(s_des);
        exit(0);
      }   
     else
     {
      system(buff);
     }
  }
}
