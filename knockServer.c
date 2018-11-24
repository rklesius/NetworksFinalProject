//this is a test of port knocking server side...if the correct sequence of ports
//are knocked it will open a connection for 10 seconds



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
#define KNOCK1 1050 // Arbitrary port number for the first knock
#define KNOCK2 1150 // Arbitrary port number for the second knock
#define KNOCK3 1250 // Arbitrary port number for the third knock

void answer1 ();
void answer2 ();
void answer3 ();
//===== Main program =========================================================
int main()
{
#ifdef WIN
 WORD wVersionRequested = MAKEWORD(1,1); // Stuff for WSA functions
 WSADATA wsaData; // Stuff for WSA functions
#endif

#ifdef WIN
 // This stuff initializes winsock
 WSAStartup(wVersionRequested, &wsaData);
#endif

answer1();
}

void answer1()
{
    int server_s; // Server socket descriptor
    // Create a socket
    server_s = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_s < 0)
    {
        printf("*** ERROR - socket() failed \n");
        exit(-1);
    }

    // Fill-in my socket's address information
    struct sockaddr_in server_addr; // Server Internet address 
    int retcode; // Return code

    server_addr.sin_family = AF_INET; // Address family to use
    server_addr.sin_port = htons(KNOCK1); // Port number to use
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on any IP address
    retcode = bind(server_s, (struct sockaddr *)&server_addr,
    sizeof(server_addr));

    if (retcode < 0)
    {
        printf("*** ERROR - bind() failed \n");
        exit(-1);
    }

    char out_buf[4096]; // Output buffer for data
    char in_buf[4096]; // Input buffer for data
    // Main loop (runs forever) for PING-PONG
    printf("Waiting for PING on port %d \n", KNOCK1);
    struct sockaddr_in client_addr; // Client Internet address
    struct in_addr client_ip_addr; // Client IP address
    int addr_len; // Internet address length
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
}

void answer2()
{
int server_s; // Server socket descriptor
// Create a socket
server_s = socket(AF_INET, SOCK_DGRAM, 0);
if (server_s < 0)
    {
        printf("*** ERROR - socket() failed \n");
        exit(-1);
    }

// Fill-in my socket's address information
struct sockaddr_in server_addr; // Server Internet address 
int retcode; // Return code

server_addr.sin_family = AF_INET; // Address family to use
server_addr.sin_port = htons(KNOCK2); // Port number to use
server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on any IP address
retcode = bind(server_s, (struct sockaddr *)&server_addr,
sizeof(server_addr));

if (retcode < 0)
    {
        printf("*** ERROR - bind() failed \n");
        exit(-1);
    }
}

void answer3()
{
int server_s; // Server socket descriptor
// Create a socket
server_s = socket(AF_INET, SOCK_DGRAM, 0);
if (server_s < 0)
{
printf("*** ERROR - socket() failed \n");
exit(-1);
}

// Fill-in my socket's address information
struct sockaddr_in server_addr; // Server Internet address 
int retcode; // Return code

server_addr.sin_family = AF_INET; // Address family to use
server_addr.sin_port = htons(KNOCK3); // Port number to use
server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on any IP address
retcode = bind(server_s, (struct sockaddr *)&server_addr,
sizeof(server_addr));

if (retcode < 0)
    {
        printf("*** ERROR - bind() failed \n");
        exit(-1);
    }

}