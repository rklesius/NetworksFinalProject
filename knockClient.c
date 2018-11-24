//This is a test of port knocking client side...it will knock the series of correct
//ports on the server side which will allow it to establish a connection for 10 seconds



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
//----- Defines --------------------------------------------------------------
#define KNOCK1 1050 // Arbitrary port number for the first knock
#define KNOCK2 1150 // Arbitrary port number for the second knock
#define KNOCK3 1250 // Arbitrary port number for the third knock

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
 // Similar to the ping.c command line input but don't care about number of pings
  if (argc != 2)
 {
 printf("Usage: knockClient.c and a valid ip address\n");
 return(1);
 }

 strcpy(ip_addr, argv[1]);

 // Create a socket
 client_s = socket(AF_INET, SOCK_DGRAM, 0);
 if (client_s < 0)
 {
 printf("*** ERROR - socket() failed \n");
 exit(-1);
 }

/* 
 ===KNOCK 1===
 */

  // Fill-in server1 socket's address information
 server_addr.sin_family = AF_INET; // Address family to use
 server_addr.sin_port = htons(KNOCK1); // Port num to use
 server_addr.sin_addr.s_addr = inet_addr(ip_addr); // IP address to use

  // Assign a KNOCK message to buffer out_buf
 strcpy(out_buf, "KNOCK");
 // Start the timer
 ftime(&start);
 // Send the KNOCK message to server 
 retcode = sendto(client_s, out_buf, (strlen(out_buf) + 1), 0,
 (struct sockaddr *)&server_addr, sizeof(server_addr));
 if (retcode < 0)
 {
 printf("*** ERROR - sendto() failed \n");
 exit(-1);
 }

  // Wait for the reply
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

/* TESTING */
  // Sample the final pong received time
 ftime(&stop);
 elapsed = ((double) stop.time + ((double) stop.millitm * 0.001)) -
 ((double) start.time + ((double) start.millitm * 0.001));
 // Output PONG received message with RTT in milliseconds
 printf("PONG received -- RTT = %f ms \n", 1000 * elapsed);
 }


