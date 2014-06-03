#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    /* Variables */  
    const int SERVE_PORT = 5600;
    const int MAXPENDING = 10;
    const int MAX_BUFFSIZE = 1025;
    struct sockaddr_in serv_addr; 

    int serv_sock = 0, client_sock = 0;
    int recv_size = 0;
    char sendBuff[MAX_BUFFSIZE];
    char recvBuff[MAX_BUFFSIZE];


    /* Initilization */
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(recvBuff, '\0', sizeof(recvBuff)); 
    memset(sendBuff, '\0', sizeof(sendBuff)); 
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVE_PORT); 
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    puts("[] Initializing... done");


    /* Create socket for sending/receiving datagrams */
    if ((serv_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
      puts("socket() failed, Can't Create UDP Socket");      /* If Socket Creation Failed */
      return 1;
    }
    puts("[] Creating UDP socket... done");
    
    /* Assign a port to socket */
    if ((bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
      puts("bind() failed\n");  /* If Bind Failed */
      return 1;
    } 
    puts("[] Assigning a port to socket... done");


/* Run forever */
    for (;;) {

      /* Receive */
      clientAddrLen = sizeof(echoClientAddr);
      /* Set the size of the in-out parameter, Block until receive message from client */
      if ((recv_size = recvfrom(serv_sock, 
                                recvBuff, 
                                MAX_BUFFSIZE,
                                0,
                                (struct sockaddr *) &echoClientAddr, 
                                sizeof(echoClientAddr))) < 0) {
        puts("recvfrom() failed... exiting now");
        return 1;
      }

      /* Send */
      printf("\nWhat you want to say to server?...\n<< ");
      scanf("%[^\n]", sendBuff);
      if (sendto(serv_sock, 
                 sendBuff, 
                 strlen(sendBuff), 
                 0,
                 (struct sockaddr *) &echoClientAddr, 
                 sizeof(echoClientAddr)) != strlen(sendBuff)) {
        puts("sendto() failed... exiting now");
        return 1;
      }
      if (strcmp(sendBuff, "bye") == 0) { /* You sent "bye" to client, so we exit now */
        puts("Ok, you entered \"bye\", so we say \"Bye Bye\" to server");
        close(client_sock);
        return 0;
      }

      
      
    } // end of for loop

}


