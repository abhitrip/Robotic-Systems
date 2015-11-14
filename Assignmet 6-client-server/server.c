#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#define PORT 5000
#define DATA "I'm inside server"


void process_request (int);

int main(int argc,char *argv[])
{
   /* variables */
   int sock; //return value of socket()  
   struct sockaddr_in server;
   int mysock;//Socket holds connection when client connects to it.
   char buff[1024];
   int rval;
   int cmd=0;
   int command=0;
   /* Create socket */
   sock = socket(AF_INET,SOCK_STREAM,0);   // TCP IP Socket
   if(sock<0) {
     perror("Failed to create a socket");
     exit(1);
   } 

   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(PORT);
 
 
   /* Call bind */ 
   if(bind(sock,(struct sockaddr*)&server,sizeof(server)))
   {
       perror("bind failed");
       exit(1);

   }
  


  /* Listen  */

 listen(sock,5);	

   
  /* Accept */ 
  mysock = accept(sock,(struct sockaddr*) 0,0);

do{
   if(mysock==-1)
     perror("accept failed");   
   else
      {
        	memset(buff,0,sizeof(buff));
	        //Receive Command from Client
		if((recv(mysock,&cmd,sizeof(cmd),0))<=0)
	    		perror("Error reading command from client");
        	else {
			command = ntohl(cmd);
			//if(command == 5) {
			//printf ("Terminating Conection");
			//exit(0);
			//}
			//else {
           		//printf("Command Received cmd:%d\n",command);
			//}
			process_request(command);
		}
		//Send Reqested Data
		if((send(mysock,DATA,sizeof(DATA),0))<0)	
        	{   
            		perror("writing failed");
		        close(mysock);      
        	}
		 
	}    	
 }while(1);	
	
close(mysock);

}


void process_request (int command)
{

switch (command) {
case 1: printf("Base requesting Radar to START\n");
   	break;
case 2: printf("Base requesting Radar to STOP\n");
  	 break;
case 3: printf("Base requesting sweep at Ndegree\n");
        break;
case 4: printf ("Base requesting coordinates\n");
	break;
case 5: printf("Terminating Conection");
   	exit(0);
   	break;
	}
}
