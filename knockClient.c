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

void knock1 (char *ip_addr);
void knock2 (char *ip_addr);
void knock3 (char *ip_addr);
//===== Main program ==========================================================
int main(int argc, char *argv[])
{
    #ifdef WIN
    WORD wVersionRequested = MAKEWORD(1,1); // Stuff for WSA functions
    WSADATA wsaData; // Stuff for WSA functions
    #endif

    #ifdef WIN
    // This stuff initializes winsock
    WSAStartup(wVersionRequested, &wsaData);
    #endif
    // Parse the command line input (no validity checking done)
    if (argc != 2)
    {
        printf("Usage: blah.c and server ip address");
        return(1);
    }
    char ip_addr[16]; // IP address of server
    strcpy(ip_addr, argv[1]);


    knock1(ip_addr);
    knock2(ip_addr);
    knock3(ip_addr);

    return 0;
    

}

//KNOCK 1

void knock1 (char *ip_addr)
{
    // Create a socket
    int client_s; // Client socket descriptor
    struct sockaddr_in server_addr; // Server Internet address
    client_s = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_s < 0)
    {
    printf("*** ERROR - socket() failed \n");
    exit(-1);
    }
    // Fill-in server1 socket's address information
    server_addr.sin_family = AF_INET; // Address family to use
    server_addr.sin_port = htons(KNOCK1); // Port num to use
    server_addr.sin_addr.s_addr = inet_addr(ip_addr); // IP address to use

    char out_buf[4096]; // Output buffer for data
    
    int retcode; // Return code
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
}

//KNOCK 2

void knock2 (char *ip_addr)
{
    // Create a socket
    int client_s; // Client socket descriptor
    struct sockaddr_in server_addr; // Server Internet address
    client_s = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_s < 0)
    {
    printf("*** ERROR - socket() failed \n");
    exit(-1);
    }
    // Fill-in server1 socket's address information
    server_addr.sin_family = AF_INET; // Address family to use
    server_addr.sin_port = htons(KNOCK2); // Port num to use
    server_addr.sin_addr.s_addr = inet_addr(ip_addr); // IP address to use

    char out_buf[4096]; // Output buffer for data
    
    int retcode; // Return code
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
}

//KNOCK 3

void knock3 (char *ip_addr)
{
    // Create a socket
    int client_s; // Client socket descriptor
    struct sockaddr_in server_addr; // Server Internet address
    client_s = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_s < 0)
    {
    printf("*** ERROR - socket() failed \n");
    exit(-1);
    }
    // Fill-in server1 socket's address information
    server_addr.sin_family = AF_INET; // Address family to use
    server_addr.sin_port = htons(KNOCK3); // Port num to use
    server_addr.sin_addr.s_addr = inet_addr(ip_addr); // IP address to use

    char out_buf[4096]; // Output buffer for data

    int retcode; // Return code
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
}