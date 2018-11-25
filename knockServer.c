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
void weblite1();
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
answer2();
answer3();
weblite1();

//we'll probably need these in a while loop and have a timeout that breaks answer2 and answer3

//if you've made it this far the port knocking was successful...opening for 10 seconds
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
        printf("Received PING from address = %s and port = %d \n",
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
        break;
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

    char out_buf[4096]; // Output buffer for data
    char in_buf[4096]; // Input buffer for data
    // Main loop (runs forever) for PING-PONG
    printf("Waiting for PING on port %d \n", KNOCK2);
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
        printf("Received PING from address = %s and port = %d \n",
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
        break;
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

    char out_buf[4096]; // Output buffer for data
    char in_buf[4096]; // Input buffer for data
    // Main loop (runs forever) for PING-PONG
    printf("Waiting for PING on port %d \n", KNOCK3);
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
        printf("Received PING from address = %s and port = %d \n",
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
        break;
    }
}

//----- Include files ---------------------------------------------------------
#include <stdio.h>        // Needed for printf()
#include <stdlib.h>       // Needed for exit()
#include <string.h>       // Needed for memcpy() and strcpy()
#include <fcntl.h>        // Needed for file i/o stuff
#ifdef WIN
  #include <process.h>    // Needed for _beginthread() and _endthread()
  #include <stddef.h>     // Needed for _threadid
  #include <windows.h>    // Needed for all Winsock stuff
  #include <sys\stat.h>   // Needed for file i/o constants
  #include <io.h>         // Needed for file i/o stuff
#endif
#ifdef BSD
  #include <pthread.h>    // Needed for pthread_create() and pthread_exit()
  #include <sys/stat.h>   // Needed for file i/o constants
  #include <sys/types.h>  // Needed for sockets stuff
  #include <netinet/in.h> // Needed for sockets stuff
  #include <sys/socket.h> // Needed for sockets stuff
  #include <arpa/inet.h>  // Needed for sockets stuff
  #include <fcntl.h>      // Needed for sockets stuff
  #include <netdb.h>      // Needed for sockets stuff
  #include <unistd.h>     // Needed to avoid read and close warnings
#endif

//----- HTTP response messages ----------------------------------------------
#define OK_IMAGE  "HTTP/1.0 200 OK\r\nContent-Type:image/gif\r\n\r\n"
#define OK_TEXT   "HTTP/1.0 200 OK\r\nContent-Type:text/html\r\n\r\n"
#define OK_BINARY "HTTP/1.0 200 OK\r\nContent-Type:application/octet-strean\r\n\r\n"
#define NOTOK_404 "HTTP/1.0 404 Not Found\r\nContent-Type:text/html\r\n\r\n"
#define MESS_404  "<html><body><h1>FILE NOT FOUND</h1></body></html>"

//----- Defines -------------------------------------------------------------
#define  PORT_NUM            8080     // Port number for Web server
#define  BUF_SIZE            4096     // Buffer size (big enough for a GET)

//----- Function prototypes -------------------------------------------------
#ifdef WIN
  void handle_get(void *in_arg);   // Windows thread function to handle GET
#endif
#ifdef BSD
  void *handle_get(void *in_arg);  // POSIX thread function to handle GET
#endif

//===== Main program ========================================================
void weblite1()
{
#ifdef WIN
  WORD wVersionRequested = MAKEWORD(1,1);  // Stuff for WSA functions
  WSADATA wsaData;                         // Stuff for WSA functions
#endif
  int                  server_s;           // Server socket descriptor
  struct sockaddr_in   server_addr;        // Server Internet address
  int                  client_s;           // Client socket descriptor
  struct sockaddr_in   client_addr;        // Client Internet address
  struct in_addr       client_ip_addr;     // Client IP address
#ifdef WIN
  int                  addr_len;           // Internet address length
#endif
#ifdef BSD
  socklen_t            addr_len;           // Internet address length
  pthread_t            thread_id;          // Thread ID
#endif
  int                  retcode;            // Return code

#ifdef WIN
  // This stuff initializes winsock
  WSAStartup(wVersionRequested, &wsaData);
#endif

  // Create a server socket
  server_s = socket(AF_INET, SOCK_STREAM, 0);
  if (server_s < 0)
  {
    printf("*** ERROR - socket() failed \n");
    exit(-1);
  }

  // Fill-in server (my) address information and bind the socket
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT_NUM);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  retcode = bind(server_s, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (retcode < 0)
  {
    printf("*** ERROR - bind() failed \n");
    exit(-1);
  }

  // Set-up the listen
  listen(server_s, 100);

  // Main loop to accept connections and then spin-off thread to handle the GET
  printf(">>> weblite is running on port %d <<< \n", PORT_NUM);
  while(1)
  {
    addr_len = sizeof(client_addr);
    client_s = accept(server_s, (struct sockaddr *)&client_addr, &addr_len);
    if (client_s == -1)
    {
      printf("ERROR - Unable to create a socket \n");
      exit(1);
    }

#ifdef WIN
    if (_beginthread(handle_get, 4096, (void *)client_s) < 0)
#endif
#ifdef BSD
    if (pthread_create(&thread_id, NULL, handle_get, (void *)client_s) != 0)
#endif
    {
      printf("ERROR - Unable to create a thread to handle the GET \n");
      exit(1);
    }
  }
}

//===========================================================================
//=  Thread function to handle a GET                                        =
//===========================================================================
#ifdef WIN
void handle_get(void *in_arg)
#endif
#ifdef BSD
void *handle_get(void *in_arg)
#endif
{
  int            client_s;             // Client socket descriptor
  char           in_buf[BUF_SIZE];     // Input buffer for GET request
  char           out_buf[BUF_SIZE];    // Output buffer for HTML response
  int            fh;                   // File handle
  int            buf_len;              // Buffer length for file reads
  char           command[BUF_SIZE];    // Command buffer
  char           file_name[BUF_SIZE];  // File name buffer
  int            retcode;              // Return code

  // Set client_s to in_arg
  client_s = (int) in_arg;

  // Receive the (presumed) GET request from the Web browser
  retcode = recv(client_s, in_buf, BUF_SIZE, 0);

  // If the recv() return code is bad then bail-out (see note #3)
  if (retcode <= 0)
  {
    printf("ERROR - Receive failed --- probably due to dropped connection \n");
#ifdef WIN
    closesocket(client_s);
    _endthread();
#endif
#ifdef BSD
    close(client_s);
    pthread_exit(NULL);
#endif
  }

  // Parse out the command from the (presumed) GET request and filename
  sscanf(in_buf, "%s %s \n", command, file_name);

  // Check if command really is a GET, if not then bail-out
  if (strcmp(command, "GET") != 0)
  {
    printf("ERROR - Not a GET --- received command = '%s' \n", command);
#ifdef WIN
    closesocket(client_s);
    _endthread();
#endif
#ifdef BSD
    close(client_s);
    pthread_exit(NULL);
#endif
  }

  // It must be a GET... open the requested file
  //  - Start at 2nd char to get rid of leading "\"
#ifdef WIN
  fh = open(&file_name[1], O_RDONLY | O_BINARY, S_IREAD | S_IWRITE);
#endif
#ifdef BSD
  fh = open(&file_name[1], O_RDONLY, S_IREAD | S_IWRITE);
#endif

  // If file does not exist, then return a 404 and bail-out
  if (fh == -1)
  {
    printf("File '%s' not found --- sending an HTTP 404 \n", &file_name[1]);
    strcpy(out_buf, NOTOK_404);
    send(client_s, out_buf, strlen(out_buf), 0);
    strcpy(out_buf, MESS_404);
    send(client_s, out_buf, strlen(out_buf), 0);
#ifdef WIN
    closesocket(client_s);
    _endthread();
#endif
#ifdef BSD
    close(client_s);
    pthread_exit(NULL);
#endif
  }

  // Generate and send the response
  printf("Sending file '%s' \n", &file_name[1]);
  if (strstr(file_name, ".gif") != NULL)
    strcpy(out_buf, OK_IMAGE);
  else if (strstr(file_name, ".html") != NULL)
    strcpy(out_buf, OK_TEXT);
  else if (strstr(file_name, ".txt") != NULL)
    strcpy(out_buf, OK_TEXT);
  else
    strcpy(out_buf, OK_BINARY);
  send(client_s, out_buf, strlen(out_buf), 0);
  while(1)
  {
    buf_len = read(fh, out_buf, BUF_SIZE);
    if (buf_len == 0) break;
    send(client_s, out_buf, buf_len, 0);
  }

  // Close the file, close the client socket, and end the thread
  close(fh);
#ifdef WIN
    closesocket(client_s);
    _endthread();
#endif
#ifdef BSD
    close(client_s);
    pthread_exit(NULL);
#endif
}
