//==================================================== file = tcpServer.c =====
//=  A message "server" program to demonstrate sockets programming            =
//=============================================================================
//=  Notes:                                                                   =
//=    1) This program conditionally compiles for Winsock and BSD sockets.    =
//=       Set the initial #define to WIN or BSD as appropriate.               =
//=    2) This program serves a message to program tcpClient running on       =
//=       another host.                                                       =
//=    3) The steps #'s correspond to lecture topics.                         =
//=---------------------------------------------------------------------------=
//=  Example execution: (tcpServer and tcpClient running on host 127.0.0.1)   =
//=    Waiting for accept() to complete...                                    =
//=    Accept completed (IP address of client = 127.0.0.1  port = 49981)      =
//=    Received from client: This is a reply message from CLIENT to SERVER    =
//=---------------------------------------------------------------------------=
//=  Build:                                                                   =
//=    Windows (WIN):  Borland: bcc32 tcpServer.c                             =
//=                    MinGW: gcc tcpServer.c -lws2_32 -o tcpServer           =
//=                    Visual C: cl tcpServer.c wsock32.lib                   =
//=    Unix/Mac (BSD): gcc tcpServer.c -lnsl -o tcpServer                     =
//=---------------------------------------------------------------------------=
//=  Execute: tcpServer                                                       =
//=---------------------------------------------------------------------------=
//=  Author: Ken Christensen                                                  =
//=          University of South Florida                                      =
//=          WWW: http://www.csee.usf.edu/~christen                           =
//=          Email: christen@csee.usf.edu                                     =
//=---------------------------------------------------------------------------=
//=  History:  KJC (08/02/08) - Genesis (from server.c)                       =
//=            KJC (09/07/09) - Minor clean-up                                =
//=            KJC (09/22/13) - Minor clean-up to fix warnings                =
//=            KJC (09/14/17) - Updated build instructions                    =
//=============================================================================
#define  WIN                // WIN for Winsock and BSD for BSD sockets

//----- Include files ---------------------------------------------------------
#include <stdio.h>          // Needed for printf()
#include <string.h>         // Needed for memcpy() and strcpy()
#include <stdlib.h>         // Needed for exit()
#include <time.h>           // For random number generation
#include "CaesarCypher.h"  //for homemade encryption 

#ifdef WIN
  #include <windows.h>      // Needed for all Winsock stuff
#endif
#ifdef BSD
  #include <sys/types.h>    // Needed for sockets stuff
  #include <netinet/in.h>   // Needed for sockets stuff
  #include <sys/socket.h>   // Needed for sockets stuff
  #include <arpa/inet.h>    // Needed for sockets stuff
  #include <fcntl.h>        // Needed for sockets stuff
  #include <netdb.h>        // Needed for sockets stuff
#endif

//----- Defines ---------------------------------------------------------------
#define  PORT_NUM   1050    // Arbitrary port number for the server
#define SCRT 7  //Shared secret for Caesar Cypher, clients should know this
#define NONCE_SIZE 4 //other shared secret of the size of the nonce

//Packet structure for security protocol
//TODO Garrett add the stuff to prevent DoS attacks here, i.e. clock time
struct SecurityPacket 
{
	char nonce[NONCE_SIZE];
};

//===== Main program ==========================================================
int main()
{
#ifdef WIN
  WORD wVersionRequested = MAKEWORD(1,1);       // Stuff for WSA functions
  WSADATA wsaData;                              // Stuff for WSA functions
#endif
  int                  welcome_s;       // Welcome socket descriptor
  struct sockaddr_in   server_addr;     // Server Internet address
  int                  connect_s;       // Connection socket descriptor
  struct sockaddr_in   client_addr;     // Client Internet address
  struct in_addr       client_ip_addr;  // Client IP address
  int                  addr_len;        // Internet address length
  char                 out_buf[4096];   // Output buffer for data
  char                 in_buf[4096];    // Input buffer for data
  int                  retcode;         // Return code

#ifdef WIN
  // This stuff initializes winsock
  WSAStartup(wVersionRequested, &wsaData);
#endif

  // >>> Step #1 <<<
  // Create a welcome socket
  //   - AF_INET is Address Family Internet and SOCK_STREAM is streams
  welcome_s = socket(AF_INET, SOCK_STREAM, 0);
  if (welcome_s < 0)
  {
    printf("*** ERROR - socket() failed \n");
    exit(-1);
  }

  // >>> Step #2 <<<
  // Fill-in server (my) address information and bind the welcome socket
  server_addr.sin_family = AF_INET;                 // Address family to use
  server_addr.sin_port = htons(PORT_NUM);           // Port number to use
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Listen on any IP address
  retcode = bind(welcome_s, (struct sockaddr *)&server_addr,
    sizeof(server_addr));
  if (retcode < 0)
  {
    printf("*** ERROR - bind() failed \n");
    exit(-1);
  }

  // >>> Step #3 <<<
  // Listen on welcome socket for a connection
  listen(welcome_s, 1);

  // >>> Step #4 <<<
  // Accept a connection.  The accept() will block and then return with
  // connect_s assigned and client_addr filled-in.
  printf("Waiting for accept() to complete... \n");
  addr_len = sizeof(client_addr);
  connect_s = accept(welcome_s, (struct sockaddr *)&client_addr, &addr_len);
  if (connect_s < 0)
  {
    printf("*** ERROR - accept() failed \n");
    exit(-1);
  }

  // Copy the four-byte client IP address into an IP address structure
  memcpy(&client_ip_addr, &client_addr.sin_addr.s_addr, 4);

  // Print an informational message that accept completed
  printf("Accept completed (IP address of client = %s  port = %d) \n",
    inet_ntoa(client_ip_addr), ntohs(client_addr.sin_port));

  // >>> Step #5 <<<
  // Send to the client using the connect socket
  // Send a random string of 4 uppercase characters (a 4 character nonce string) to the client
  struct SecurityPacket connection1;
  int i;
  srand(time(0)); //seed current time for random generator
  for(i = 0; i < NONCE_SIZE; i++)
  {
	  connection1.nonce[i] = rand() % 26 + 'A';  //find a random number between 0 and 25, increment alphabet by that much 
  }
  printf("Message sent to client: %s\n", connection1.nonce);
  strcpy(out_buf, connection1.nonce);
  retcode = send(connect_s, out_buf, (strlen(out_buf) + 1), 0);
  if (retcode < 0)
  {
    printf("*** ERROR - send() failed \n");
    exit(-1);
  }

  // >>> Step #6 <<<
  // Receive from the client using the connect socket
  retcode = recv(connect_s, in_buf, sizeof(in_buf), 0);
  if (retcode < 0)
  {
    printf("*** ERROR - recv() failed \n");
    exit(-1);
  }
  char *recieved = Decrypt(in_buf, NONCE_SIZE, SCRT);
  printf("Message from client decrypted:  %s\n", recieved);
  if (strcmp(in_buf, recieved) == 0)  //if decoded message is the same as the nonce, connect
  {
	  printf("Authentification successful, connecting.../n");
  }
  else  //otherwise, Trudy is afoot!  
  {
	  printf("Authenfication failed, go away Trudy!\n");
	  //close the connection
	  ///////////GARRETT, I don't know how to close the connection (or keep it open for that matter) maybe you should
	  ///////////create a function to close so that way it would be easier.  How does it stay open in the first place?
	  ///////////the code after it should close it no matter what, but it stayed open when we did ping and pong
  }
  
   Deallocate(recieved);  //deallocate recieved message after decrypting

  // >>> Step #7 <<<
  // Close the welcome and connect sockets
#ifdef WIN
  retcode = closesocket(welcome_s);
  if (retcode < 0)
  {
    printf("*** ERROR - closesocket() failed \n");
    exit(-1);
  }
  retcode = closesocket(connect_s);
  if (retcode < 0)
  {
    printf("*** ERROR - closesocket() failed \n");
    exit(-1);
  }
#endif
#ifdef BSD
  retcode = close(welcome_s);
  if (retcode < 0)
  {
    printf("*** ERROR - close() failed \n");
    exit(-1);
  }
  retcode = close(connect_s);
  if (retcode < 0)
  {
    printf("*** ERROR - close() failed \n");
    exit(-1);
  }
#endif

#ifdef WIN
  // Clean-up winsock
  WSACleanup();
#endif

  // Return zero and terminate
  return(0);
}
