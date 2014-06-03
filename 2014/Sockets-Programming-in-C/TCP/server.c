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

    struct sockaddr_in serv_addr; 

    int serv_sock = 0, client_sock = 0;
    int recv_size = 0;
    char sendBuff[1025];
    char recvBuff[1025];


    /* Initilization */
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(recvBuff, '\0', sizeof(recvBuff)); 
    memset(sendBuff, '\0', sizeof(sendBuff)); 
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERVE_PORT); 
    puts("[] Initializing... done");

    /* Create a TCP socket */
    if ((serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
      puts("socket() failed, Can't Create Socket to Listen On\n");      /* If Socket Creation Failed */
      return 1;
    }
    puts("[] Creating TCP socket... done");
    
    /* Assign a port to socket */
    if ((bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
      puts("bind() failed\n");  /* If Bind Failed */
      return 1;
    } 
    puts("[] Assigning a port to socket... done");


    /* Set socket to listen */
    if ((listen(serv_sock, MAXPENDING) < 0)) {
      puts("listen() failed\n");  /* If Listen Failed */
      return 1;
    } 
    puts("[] Ok, it's listenning now~");


/* LISTEN, Repeate in a for loop */
    for (;;) {

      /* Accept new connection */
      if((client_sock = accept(serv_sock, (struct sockaddr*)NULL, NULL)) < 0) {
        puts("accpet() failed\n");  /* If accept Failed */
        return 1;
      } 
      puts("[] New connection in~");

/* Communicate */
      /* Receive message from client */
      if ((recv_size = recv(client_sock, recvBuff, sizeof(recvBuff), 0)) < 0) {
        puts("recv() failed\n");
      }

      /* Send received string and receive again until end of transmission */
      // if (send(client_sock, recvBuff, strlen(recvBuff), 0) != strlen(recvBuff)) {/* Message Here */}
      puts("[Got Messsage From Client...]");
      printf(">> %s\n", recvBuff);
      
      puts("[] What You want to say to client?..."); 
      printf("<< ");
      scanf("%[^\n]",sendBuff);

      /* Send the string to the client */
      if (send(client_sock, sendBuff, strlen(sendBuff), 0) != strlen(sendBuff)) {
        puts("send() failed\n");
        return 1;
      }
      puts("[Msg Sent to Client, waiting for reply now]");
      
    }

}


