//////////////////////////////////////////////////////////////////////////////////////
//	This program is a simple Caesar Cypher that works with any random integer       /
//  to seed the data for the cypher.  It ignores punctuation, leaving it           /
//  unchanged, so that in other security protocols the different parts can be     /
//  easily identified.                                                           /
//	By Rachel Klesius and Garrett Moncrief, 11/21/18                            /
////////////////////////////////////////////////////////////////////////////////

#include "CaesarCypher.h"

char *Encrypt(char *msg, int key) 
{
	printf("Original message sent to cypher: %s\n", msg);
	int i;
	char temp;
	char *encrypted = (char *) malloc(sizeof(char) * strlen(msg));
	for(i = 0; i < strlen(msg); i++)
	{
		//only change alphanumeric numbers, leave symbols
		if(msg[i] >= 'a' && msg[i] <= 'z')
		{
			temp = msg[i] + key;  //add key to msg
			if(temp > 'z')  //if goes over edge, bring back to start
			{
				temp = temp - 'z' + 'a' - 1;
			}
			encrypted[i] = temp;
		}
		if(msg[i] >= 'A' && msg[i] <= 'Z')
		{	
			temp = msg[i] + key;
			if(temp > 'Z')
			{
				temp = temp - 'Z' + 'A' - 1;
			}
			encrypted[i] = temp;
		}
		else if(msg[i] >= '0' && msg[i] <= '9')
		{
			temp = msg[i] + key;
			if(temp > '9')
			{
				temp = temp - '9' + '0' - 1;
			}
			encrypted[i] = temp;
		}
		else 
		{
			encrypted[i] = msg[i];
		}
	}
	encrypted[i] = '\0';
	return encrypted;
}


char *Decrypt(char *msg, int key)
{
	int i;
	char temp;
	char *decrypted = (char *) malloc(sizeof(char) * strlen(msg));
	for(i = 0; i < strlen(msg); i++)
	{
		//only change alphanumeric numbers, leave symbols
		if(msg[i] >= 'a' && msg[i] <= 'z')
		{
			temp = msg[i] - key;
			if(temp < 'a')
			{
				temp = temp + 'z' - 'a' + 1;
			}
			decrypted[i] = temp;
		}
		if(msg[i] >= 'A' && msg[i] <= 'Z')
		{
			temp = msg[i] - key;
			if(temp < 'A')
			{
				temp = temp + 'Z' - 'A' + 1;
			}
			decrypted[i] = temp;
		}
		else if(msg[i] >= '0' && msg[i] <= '9')
		{
			temp = msg[i] - key;
			if(temp < '0')
			{
				temp = temp + '9' - '0' + 1;
			}
			decrypted[i] = temp;
		}
		else 
		{
			decrypted[i] = msg[i];
		}
	}
	decrypted[i] = '\0';
	return decrypted;
}


//main function just for testing purposes.  To test some values, simply run the following commands after
//uncommenting this main function:
//gcc CaesarCypher.c -lws2_32 -o cypher
//cypher
/*
int main(void)
{
	int key;  //Shared secret between client and server	
	char test1[] = "HAIL JULIUS CAESAR!!!";
	int length1 = 5;
	char test2[] = "This is a really long test meant to simulate how long these strings can be";
	int length2 = 75;
	char test3[] = "Shh!  Don't tell Trudy the shared secret!";
	int length3 = 42;
	printf("Enter a key: ");
	scanf("%d", &key);
	key = key % 26;  //no point in making a key over 26, since it will just loop back but easy to break this
	
	printf("Message to encrypt: %s\n", test3);
	char *result = Encrypt(test3, length3, key);
	printf("Message after encryption: %s\n", result);
	char *original = Decrypt(result, length3, key);
	printf("Message after decryption: %s\n\n", original);
	
	free(result);
	free(original);
	return 0;
}
*/
