#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define DATA "Hello world of Socket"


int main(int argc,char *argv[])
{
   /* variables */
  int sock;
  struct sockaddr_in server;
  char buff[1024];
  struct hostent *hp;   
  int cmd, command;

  sock = socket(AF_INET,SOCK_STREAM,0);
  if(sock<0)
  {
     perror("socket failed\n");
     exit(1);   
  }  
  
  server.sin_family = AF_INET; 	
  hp = gethostbyname( argv[1]); 
  if(hp==0)
  {
      perror("get Hostname failed");
      close(sock);
      exit(1);  

  }     
  memcpy(&server.sin_addr,hp->h_addr,hp->h_length);

  server.sin_port = htons(5000);

  if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
  {
      perror("connect failed");
      close(sock);
      exit(1);
  }

do {
//Select Command
        printf("RADAR CONTROL SYSTEM\n");
        printf("Please enter your choice:\n");
        printf("1. Start Scan\n");
        printf("2. Stop Scan\n");
        printf("3. Scan at Heading\n");
        printf("4. Display Coordinate\n");
        printf("5. Terminate Connection\n");
        scanf("%d",&cmd);
        command = htonl(cmd);	

//Send Command to Server/BBB
  	 if(send(sock,&command,sizeof(command),0)<0)
  	 {
     		perror("Could not connect to Beagle...");
     		close(sock);
     		exit(1);
  	 }
        if(cmd == 5) { exit(0);} //Quit

//Receive Data from BBB
  	 else
  	 {
     		memset(buff,0,sizeof(buff)); 
     		if(recv(sock,buff,sizeof(buff),0)<0)
     		{
        	perror("Data not available...");
        	close(sock);
        	exit(1);
     		}
     		else
    		{
    		printf("\nData received from Radar = %s \n",buff);
    		}
 	 }

}while(1);
  
close(sock);

return 0;
 


}
