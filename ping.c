//====================================================== file = udpPing.c =====
//= A UDP ping client that sends a "PING" and listens for a "PONG" =
//=============================================================================
//= Notes: =
//= 1) This program conditionally compiles for Winsock and BSD sockets. =
//= Set the initial #define to WIN or BSD as appropriate. =
//= 2) This program needs udpPong to be running on the other host =
//= Program udpPong must be started first. =
//= 3) This program takes command line input for udpPong host IP address =
//= and number of PING to send =
//= 4) If a PONG response is not received, this program hangs =
//=---------------------------------------------------------------------------=
//= Example execution: (udpPong and udpPing running on host 127.0.0.1) =
//= udpPing 127.0.0.1 5 =
//= PONG received from IP = 127.0.0.1 -- RTT = 110 ms =
//= PONG received from IP = 127.0.0.1 -- RTT = 110 ms =
//= PONG received from IP = 127.0.0.1 -- RTT = 110 ms =
//= PONG received from IP = 127.0.0.1 -- RTT = 110 ms =
//= PONG received from IP = 127.0.0.1 -- RTT = 110 ms =
//=---------------------------------------------------------------------------=
//= Build: =
//= Windows (WIN): Borland: bcc32 udpPing.c =
//= MinGW: gcc udpPing.c -lws2_32 -o updPing =
//= Visual C: cl ucpPing.c wsock32.lib =
//= Unix/Mac (BSD): gcc ucpPing.c -lnsl -o ucpPing =
//=---------------------------------------------------------------------------=
//= Execute: udpPing ip_addr num_ping =
//=---------------------------------------------------------------------------=
//= Author: Ken Christensen =
//= University of South Florida =
//= WWW: http://www.csee.usf.edu/~christen =
//= Email: christen@csee.usf.edu =
//=---------------------------------------------------------------------------=
//= History: KJC (09/09/18) - Genesis (from udpClient.c) =
//=============================================================================
#define WIN // WIN for Winsock and BSD for BSD sockets
//----- Include files ---------------------------------------------------------
#include <stdio.h> // Needed for printf()
#include <string.h> // Needed for memcpy() and strcpy()
#include <stdlib.h> // Needed for exit()
#ifdef WIN
 #include <windows.h> // Needed for all Winsock stuff
 #include <sys\timeb.h> // Needed for ftime() and timeb structure
#endif
#ifdef BSD
 #include <sys/types.h> // Needed for sockets stuff
 #include <netinet/in.h> // Needed for sockets stuff
 #include <sys/socket.h> // Needed for sockets stuff
 #include <arpa/inet.h> // Needed for sockets stuff
 #include <fcntl.h> // Needed for sockets stuff
 #include <netdb.h> // Needed for sockets stuff
 #include <sys/timeb.h> // Needed for ftime() and timeb structure
#endif
//----- Defines ---------------------------------------------------------------
#define PORT_NUM 1050 // Port number used 
//===== Main program ==========================================================
int main(int argc, char *argv[])
{
#ifdef WIN
 WORD wVersionRequested = MAKEWORD(1,1); // Stuff for WSA functions
 WSADATA wsaData; // Stuff for WSA functions
#endif
 int client_s; // Client socket descriptor
 struct sockaddr_in server_addr; // Server Internet address
 int addr_len; // Internet address length
 char out_buf[4096]; // Output buffer for data
 char in_buf[4096]; // Input buffer for data
 char ip_addr[16]; // IP address of pong server
 int num_ping; // Number of pings to send
 struct timeb start; // Start time structure
 struct timeb stop; // Stop time structure
 double elapsed; // Elapsed time in seconds
 int retcode; // Return code
 int i; // Loop index
#ifdef WIN
 // This stuff initializes winsock
 WSAStartup(wVersionRequested, &wsaData);
#endif
 // Parse the command line input (no validity checking done)
 if (argc != 3)
 {
 printf("Usage: udpPing ip_addr num_ping where ip_addr is a valid \n");
 printf(" IP address and num_ping is the number of PING messages \n");
 printf(" to send. \n");
 return(1);
 }
 strcpy(ip_addr, argv[1]);
 num_ping = atoi(argv[2]);
 // Create a socket
 client_s = socket(AF_INET, SOCK_DGRAM, 0);
 if (client_s < 0)
 {
 printf("*** ERROR - socket() failed \n");
 exit(-1);
 }
 // Fill-in server1 socket's address information
 server_addr.sin_family = AF_INET; // Address family to use
 server_addr.sin_port = htons(PORT_NUM); // Port num to use
 server_addr.sin_addr.s_addr = inet_addr(ip_addr); // IP address to use
 // Main loop to send PING and receive PONG
 for (i=0; i<num_ping; i++)
 {
 // Assign a PING message to buffer out_buf
 strcpy(out_buf, "PING");
 // Start the timer
 ftime(&start);
 // Send the PING message to server 
 retcode = sendto(client_s, out_buf, (strlen(out_buf) + 1), 0,
 (struct sockaddr *)&server_addr, sizeof(server_addr));
 if (retcode < 0)
 {
 printf("*** ERROR - sendto() failed \n");
 exit(-1);
 }
 // Wait for the PONG message to arrive
 while(1)
 {
 addr_len = sizeof(server_addr);
 retcode = recvfrom(client_s, in_buf, sizeof(in_buf), 0,
 (struct sockaddr *)&server_addr, &addr_len);
 if (retcode < 0)
 {
 printf("*** ERROR - recvfrom() failed \n");
 exit(-1);
 }
 // Check if the received message is a PONG
 if (strcmp(in_buf, "PONG") == 0) break;
 }
 // Sample the final pong received time
 ftime(&stop);
 elapsed = ((double) stop.time + ((double) stop.millitm * 0.001)) -
 ((double) start.time + ((double) start.millitm * 0.001));
 // Output PONG received message with RTT in milliseconds
 printf("PONG received -- RTT = %f ms \n", 1000 * elapsed);
 }
 // Close all open sockets
#ifdef WIN
 retcode = closesocket(client_s);
 if (retcode < 0)
 {
 printf("*** ERROR - closesocket() failed \n");
 exit(-1);
 }
#endif
#ifdef BSD
 retcode = close(client_s);
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