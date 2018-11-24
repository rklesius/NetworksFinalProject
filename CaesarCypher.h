//Header File for the CaesarCypher.c
#ifndef CAESAR_CYPHER_H
#define CAESAR_CYPHER_H

#include <stdio.h>
#include <string.h>
#include <windows.h>  //for malloc in windows

char *Encrypt(char *msg, int length, int key);
char *Decrypt(char *msg, int length, int key);
void Deallocate(char *msg);

#endif