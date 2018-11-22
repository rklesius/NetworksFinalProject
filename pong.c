//====================================================== file = udpPong.c =====
//= A UDP ping server that listens on for "PING" and returns "PONG" =
//=============================================================================
//= Notes: =
//= 1) This program conditionally compiles for Winsock and BSD sockets. =
//= Set the initial #define to WIN or BSD as appropriate. =
//= 2) This program listens on port PORT_NUM for a "PING" message and then =
//= returns a "PONG" message =
//= 3) Ignore build warning for unreachable code =
//=---------------------------------------------------------------------------=
//= Example execution: (udpPing and udpPong running on host 127.0.0.1) =
//= Waiting for PING on port 1024... =
//= Received PING from address = 127.0.0.1 and port = 55476 =
//=---------------------------------------------------------------------------=
//= Build: =
//= Windows (WIN): Borland: bcc32 udpPong.c =
//= MinGW: gcc udpPong.c -lws2_32 -o updPong =
//= Visual C: cl ucpPong.c wsock32.lib =
//= Unix/Mac (BSD): gcc ucpPong.c -lnsl -o ucpPong =
//=---------------------------------------------------------------------------=
//= Execute: udpPong =
//=---------------------------------------------------------------------------=
//= Author: Ken Christensen =
//= University of South Florida =
//= WWW: http://www.csee.usf.edu/~christen =
//= Email: christen@csee.usf.edu =
//=---------------------------------------------------------------------------=
//= History: KJC (09/09/18) - Genesis (from udpServer.c) =
//=============================================================================
#define WIN // WIN for Winsock and BSD for BSD sockets
//----- Include files --------------------------------------------------------
#include <stdio.h> // Needed for printf()
#include <string.h> // Needed for memcpy() and strcpy()
#include <stdlib.h> // Needed for exit()
#ifdef WIN
 #include <windows.h> // Needed for all Winsock stuff
#endif
#ifdef BSD
 #include <sys/types.h> // Needed for sockets stuff
 #include <netinet/in.h> // Needed for sockets stuff
 #include <sys/socket.h> // Needed for sockets stuff
 #include <arpa/inet.h> // Needed for sockets stuff
 #include <fcntl.h> // Needed for sockets stuff
 #include <netdb.h> // Needed for sockets stuff
#endif
//----- Defines --------------------------------------------------------------
#define PORT_NUM 1050 // Arbitrary port number for the server
//===== Main program =========================================================
int main()
{
#ifdef WIN
 WORD wVersionRequested = MAKEWORD(1,1); // Stuff for WSA functions
 WSADATA wsaData; // Stuff for WSA functions
#endif
 int server_s; // Server socket descriptor
 struct sockaddr_in server_addr; // Server Internet address 

 struct sockaddr_in client_addr; // Client Internet address
 struct in_addr client_ip_addr; // Client IP address
 int addr_len; // Internet address length
 char out_buf[4096]; // Output buffer for data
 char in_buf[4096]; // Input buffer for data
 int retcode; // Return code
#ifdef WIN
 // This stuff initializes winsock
 WSAStartup(wVersionRequested, &wsaData);
#endif
 // Create a socket
 server_s = socket(AF_INET, SOCK_DGRAM, 0);
 if (server_s < 0)
 {
 printf("*** ERROR - socket() failed \n");
 exit(-1);
 }
 // Fill-in my socket's address information
 server_addr.sin_family = AF_INET; // Address family to use
 server_addr.sin_port = htons(PORT_NUM); // Port number to use
 server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on any IP address
 retcode = bind(server_s, (struct sockaddr *)&server_addr,
 sizeof(server_addr));
 if (retcode < 0)
 {
 printf("*** ERROR - bind() failed \n");
 exit(-1);
 }
 // Main loop (runs forever) for PING-PONG
 printf("Waiting for PING on port %d \n", PORT_NUM);
 while(1)
 {
 // Wait to receive a message from client
 addr_len = sizeof(client_addr);
 retcode = recvfrom(server_s, in_buf, sizeof(in_buf), 0,
 (struct sockaddr *)&client_addr, &addr_len);
 if (retcode < 0)
 {
 printf("*** ERROR - recvfrom() failed \n");
 exit(-1);
 }
 // If recieved message is not PING, then continue to top of loop
 if (strcmp(in_buf, "PING") != 0) continue;
 // Output PING received message
 memcpy(&client_ip_addr, &client_addr.sin_addr.s_addr, 4);
 printf(" Received PING from address = %s and port = %d \n",
 inet_ntoa(client_ip_addr), ntohs(client_addr.sin_port));
 // DEBUG (works for Windows only)...
 Sleep(100);
 // Send PONG to the client
 strcpy(out_buf, "PONG"); 

 retcode = sendto(server_s, out_buf, (strlen(out_buf) + 1), 0,
 (struct sockaddr *)&client_addr, sizeof(client_addr));
 if (retcode < 0)
 {
 printf("*** ERROR - sendto() failed \n");
 exit(-1);
 }
 }
 // Close all open sockets
#ifdef WIN
 retcode = closesocket(server_s);
 if (retcode < 0)
 {
 printf("*** ERROR - closesocket() failed \n");
 exit(-1);
 }
#endif
#ifdef BSD
 retcode = close(server_s);
 if (retcode < 0)
 {
 printf("*** ERROR - close() failed \n");
 exit(-1);
 }
#endif
#ifdef WIN
 // This stuff cleans-up winsock
 WSACleanup();
#endif
 // Return zero and terminate
 return(0);
} 