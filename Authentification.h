//////////////////////////////////////////////////////////////////////////////////////
//	This program is the header for the Authenfication protocol (Authentification.c) /
//  for our security system.  For the sake of modularity, this program is          /
//  completely separate from our Caesar Cypher, so that someone could use their   /
//  encryption of choice.                                                        /
//	By Rachel Klesius and Garrett Moncrief, 11/21/18                            / 
////////////////////////////////////////////////////////////////////////////////

#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <stdio.h>
#include <string.h>
#include <windows.h>         // For malloc in windows
#include <stdbool.h>
#include <time.h>           // For random number generation

char *getRandomString(int length);  //get a random string of length "length"
bool isEqual(char *a, char *b, int length);  //checks if the strings a and b are equal with the same length

#endif