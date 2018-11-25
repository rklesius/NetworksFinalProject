//////////////////////////////////////////////////////////////////////////////////////
//	This is the header for a simple Caesar Cypher (CaesarCypher.c) that works with  /
//  any random integer to seed the data for the cypher. It ignores punctuation,    /
//  leaving it unchanged, so that in other security protocols the different       /
//  parts can be easily identified.                                              /
//	By Rachel Klesius and Garrett Moncrief, 11/21/18                            /
////////////////////////////////////////////////////////////////////////////////

#ifndef CAESAR_CYPHER_H
#define CAESAR_CYPHER_H

#include <stdio.h>
#include <string.h>
#include <windows.h>  //for malloc in windows

char *Encrypt(char *msg, int key);
char *Decrypt(char *msg, int key);

#endif