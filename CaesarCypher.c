//////////////////////////////////////////////////////////////////////////////////////
//	This program is a simple Caesar Cypher that works with any random integer       /
//  to seed the data for the cypher.  It ignores punctuation, leaving it           /
//  unchanged, so that in other security protocols the different parts can be     /
//  easily identified.                                                           /
//	By Rachel Klesius and Garrett Moncrief, 11/21/18                            /
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <windows.h>  //for malloc in windows

char *Encrypt(char *msg, int length, int nonce) 
{
	int i;
	char temp;
	char *encrypted = (char *) malloc(sizeof(char) * length);
	for(i = 0; i < length; i++)
	{
		//only change alphanumeric numbers, leave symbols
		if(msg[i] >= 'a' && msg[i] <= 'z')
		{
			temp = msg[i] + nonce;
			if(temp > 'z')
			{
				temp = temp - 'z' + 'a' - 1;
			}
			encrypted[i] = temp;
		}
		else if(msg[i] >= 'A' && msg[i] <= 'Z')
		{
			temp = msg[i] + nonce;
			if(temp > 'z')
			{
				temp = temp - 'Z' + 'A' - 1;
			}
			encrypted[i] = temp;
		}
		else if(msg[i] >= '0' && msg[i] <= '9')
		{
			temp = msg[i] + nonce;
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
	return encrypted;
}


char *Decrypt(char *msg, int length, int nonce)
{
	int i;
	char temp;
	char *decrypted = (char *) malloc(sizeof(char) * length);
	for(i = 0; i < length; i++)
	{
		//only change alphanumeric numbers, leave symbols
		if(msg[i] >= 'a' && msg[i] <= 'z')
		{
			temp = msg[i] - nonce;
			if(temp < 'a')
			{
				temp = temp + 'z' - 'a' + 1;
			}
			decrypted[i] = temp;
			continue;
		}
		else if(msg[i] >= 'A' && msg[i] <= 'Z')
		{
			temp = msg[i] - nonce;
			if(temp < 'A')
			{
				temp = temp + 'Z' - 'A' + 1;
			}
			decrypted[i] = temp;
			continue;
		}
		else if(msg[i] >= '0' && msg[i] <= '9')
		{
			temp = msg[i] - nonce;
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
	return decrypted;
}

void Deallocate(char *msg)
{
	free(msg);
}


//main function just for testing purposes.  To test some values, simply run the following commands after
//uncommenting this main function:
//gcc CaesarCypher.c -lws2_32 -o cypher
//cypher
/*
int main(void)
{
	int nonce;	
	char test1[] = "HELLO";
	int length1 = 5;
	char test2[] = "This is a really long test meant to simulate how long these strings can be";
	int length2 = 75;
	char test3[] = "we//are//going//to//use//a//lot//of//these";
	int length3 = 42;
	printf("Enter a nonce: ");
	scanf("%d", &nonce);
	nonce = nonce % 26;  //no point in making a nonce over 26, since it will just loop back but easy to break this
	
	printf("Message to encrypt: %s\n", test3);
	char *result = Encrypt(test3, length3, nonce);
	printf("Message after encryption: %s\n", result);
	char *original = Decrypt(result, length3, nonce);
	printf("Message after decryption: %s\n\n", original);
	
	Deallocate(result);
	Deallocate(original);
	return 0;
}
*/
