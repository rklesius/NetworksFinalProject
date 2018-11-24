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