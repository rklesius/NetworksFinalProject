//////////////////////////////////////////////////////////////////////////////////////
//	This program contains the functions used for the Authenfication protocol for    /
//  security system.  For the sake of modularity, this program is completely       /
//  separate from our Caesar Cypher, so that someone could use their encryption   /
//  of choice.                                                                   /
//	By Rachel Klesius and Garrett Moncrief, 11/21/18                            / 
////////////////////////////////////////////////////////////////////////////////

#include "Authentification.h"

//get a random string of length "length"
char *getRandomString(int length)  
{
  int i;
  srand(time(0)); //seed current time for random generator
  char *random = (char *) malloc(sizeof(char) * length + 1);
  for(i = 0; i < length; i++)
  {
	  random[i] = rand() % 26 + 'A';  //find a random number between 0 and 25, increment alphabet by that much 
  }
  random[i] = '\0';  //Add null terminator to end of string
  printf("Random string sent to server: %s\n", random);
  return random;
}

//checks if the strings a and b are equal with the same
bool isEqual(char *a, char *b, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		if(a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}