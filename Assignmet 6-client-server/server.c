/*
This Code is for the SERVER side i.e. BBB using C Socket Programming 
on Linux.  The Laptop i.e. the client should use the same wifi network as 
the client.
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 6
Last Modified: 14-Nov-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathi; Pulkit Bhatnagar
University of California, San Diego
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#define PORT 5000
#define DATA "I'm inside server"



#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define BUFSIZE 500
int tty_fd;
void InitSerial()
{
        struct termios tio;
        struct termios stdio;
        struct termios old_stdio;
        struct termios oldtio;

//        unsigned char c='D';
        tcgetattr(STDOUT_FILENO,&old_stdio);

	memset(&oldtio,0,sizeof(oldtio));  //n
	tcgetattr(tty_fd, &oldtio);  //n
        
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;
        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

        memset(&tio,0,sizeof(tio));
	memcpy(&tio, &oldtio, sizeof(oldtio)); //n
        //tio.c_iflag=0;
        tio.c_iflag &= ~(IXON | IXOFF | IXANY) ; //Commented by @atripath
        //tio.c_iflag |= (IXON | IXOFF | IXANY);//To enable software flow
        tio.c_oflag &= ~OPOST; // To enable raw output
	//tio.c_oflag = 0;

        tio.c_cflag &= ~PARENB;
        tio.c_cflag &= ~CSTOPB;
	tio.c_cflag &= ~CSIZE;
        tio.c_cflag |= (CS8|CREAD|CLOCAL);           // 8n1, see termios.h for more information
        tio.c_cflag &= ~CRTSCTS;  //Commented by @atripath 
	//tio.c_cflag |=	CRTSCTS;	

        tio.c_lflag &= ~(ICANON|ECHO|ECHOE|ISIG);

        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;

       // tty_fd=open("/dev/ttyO1", O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B9600);            // 115200 baud
        cfsetispeed(&tio,B9600);            // 115200 baud

        tcsetattr(tty_fd,TCSANOW,&tio);
        tty_fd=open("/dev/ttyO1", O_RDWR | O_NOCTTY |O_NDELAY);

	if(tty_fd < 0)
	{
		printf("\nFILE OPEN ERROR\n");
	}
	//tcsetattr(tty_fd,TCSANOW,&tio);
       else
           fcntl(tty_fd, F_SETFL,FNDELAY ); //@atripath  
		

}

off_t wSeek,rSeek;
char buff[BUFSIZE];
void WriteSerial(char c)
{
    fsync(tty_fd);//@atripath
	write(tty_fd,&c,1);                     // if new data is available on the console, send it to the serial port
                      
}

int ReadSerial()
{
	
        int nbytes = read(tty_fd,buff,BUFSIZE);                     // if new data is available on the console, send it to the serial port
        fprintf(stderr,"\n\rThe data from MBEd is %d, %s", nbytes, buff);
        return nbytes;             
  
}




   void process_request (int);
   int mysock;//Socket holds connection when client connects to it.
   //char buff[BUFSIZE];
int main(int argc,char *argv[])
{
   /* variables */
   int sock; //return value of socket()  
   struct sockaddr_in server;
   //char buff[100];
   int rval;
   int cmd=0;
   int command=0;
   /* Create socket */
   sock = socket(AF_INET,SOCK_STREAM,0);   // TCP IP Socket
   if(sock<0) {
     perror("Failed to create a socket");
     exit(1);
   } 

   InitSerial();	
   
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
			process_request(command);
		}
		//Send Reqested Data
		fprintf(stderr, "\ncommand=%d\n", command);
		//ReadSerial(buff);
                if(command==4)
                {    
	          ReadSerial();  	
		   if((send(mysock,buff,BUFSIZE,0))<0)	
        	   {      
            		perror("writing failed");
		        //close(mysock);      
        	    }

               }
		 
	}    	
 }while(1);	
	
close(mysock);

}


void process_request (int command)
{
char ch=0x80;
switch (command) {
case 1: printf("Base requesting Radar to START\n");
			WriteSerial('1');
   	break;
case 2: printf("Base requesting Radar to STOP\n");
			WriteSerial('2');
  	 break;
case 3: printf("Base requesting sweep at Ndegree\n");
			WriteSerial('3');
        break;
case 4: printf ("Base requesting coordinates\n");
			WriteSerial('4');
                       // ReadSerial();
	break;
case 5: printf("Terminating Conection");
   	//exit(0); #abhinav
        close(tty_fd);
        close(mysock);
   	break;

default: WriteSerial(ch);
}
}


