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

int main(int argc,char *argv[])
{
    char buff[200],out[200];

    memset(buff,'\0',200);
    write(2,"Enter Comamnd: ",strlen("Enter Comamnd: "));
    read(0,buff,200);
    system(buff);    

    return 0;
}
