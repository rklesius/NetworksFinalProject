//////////////////////////////////////////////////////////////////////////////////////
                      
////////////////////////////////////////////////////////////////////////////////

#ifndef WEBLITE1_H
#define WEBLITE1_H

#include <stdio.h>        // Needed for printf()
#include <stdlib.h>       // Needed for exit()
#include <string.h>       // Needed for memcpy() and strcpy()
#include <fcntl.h>        // Needed for file i/o stuff
#include <time.h>
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



//----- Function prototypes -------------------------------------------------
void weblite1();

#ifdef WIN
  void handle_get(void *in_arg);   // Windows thread function to handle GET
#endif
#ifdef BSD
  void *handle_get(void *in_arg);  // POSIX thread function to handle GET
#endif

#endif