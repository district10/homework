/* Compile: `gcc client.c -o client`
 * Run: `./client`
 */

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

int main(int argc, char *argv[])
{
  const int CONN_PORT = 5600;
  const int MAX_BUFFSIZE = 1024;

  char recvBuff[MAX_BUFFSIZE];
  char sendBuff[MAX_BUFFSIZE];
  int client_sock = 0;
  int recv_size = 0;
  struct sockaddr_in serv_addr; 

  if(argc != 2) {
      printf("\n[] Use default Server IP:Port(localhost:%d)", CONN_PORT);
      printf("\n[] You can also specify ip by calling: %s <ip of server> \n",argv[0]);
  } 


  /* Initialization */
  memset(recvBuff, '\0',sizeof(recvBuff));
  memset(sendBuff, '\0',sizeof(sendBuff));
  memset(&serv_addr, '0', sizeof(serv_addr)); 
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(CONN_PORT); 
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  puts("[] Initializing... done");


  /* Create socket for sending/receiving datagrams */
  if ((client_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
      printf("\n Error : Could not create socket \n");
      return 1;
    } 
  puts("[] Creating UDP socket... done");

  /* Assign a port to socket */
  if ((bind(client_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
    puts("bind() failed\n");  /* If Bind Failed */
    return 1;
  } 
  puts("[] Assigning a port to socket... done");


/* Communicate */
  /* Send the string to the server */
  printf("\nWhat you want to say to server?...\n<< ");
  scanf("%[^\n]", sendBuff);
  if (sendto(client_sock, 
             sendBuff, 
             strlen(sendBuff), 
             0, 
             (struct sockaddr *) &serv_addr, 
             sizeof(serv_addr)) != strlen(sendBuff)) {
    puts("sendto() troubled... Sorry, we'll exit now");
    return 1;
  }
  if (strcmp(sendBuff, "bye") == 0) { /* You sent "bye" to server, so we exit now */
    puts("Ok, you entered \"bye\", so we say \"Bye Bye\" to server");
    close(client_sock);
    return 0;
  }





  for(;;) {

    /* Get Msg From User */
    printf("\nWhat you want to say to server?...\n<< ");
    scanf("%[^\n]", sendBuff);
    if (strcmp(sendBuff, "bye") == 0) {
      /* Let's say goodbye to server */
      /* Close the connection here */
      puts("Ok, you entered \"bye\", so we say \"Bye Bye\" to server");
      close(client_sock);
      return 0;
    }

    /* Send msg to the server, using the client_sock */
    if (send(client_sock, sendBuff, strlen(sendBuff), 0) != strlen(sendBuff)) {
      puts("send() failed\n");
      return 1;
    }
    puts("[Msg Sent To Server, Waiting For Reply Now...]");

    /* Receive message from client */
    if ((recv_size = recv(client_sock, recvBuff, sizeof(recvBuff), 0)) < 0) {
      puts("recv() failed\n");
      return 1;
    }

    printf("[Got Msg From Client...]\n>> %s", recvBuff);
  
  } // end of for loop



   return 0;
}
