//
// Created by Admin on 3/13/2024.
//

#ifndef P2_TESTSCANNER_H
#define P2_TESTSCANNER_H

//#include "token.h"
#include "scanner.h"

void readFromFile(char* file); // read from file and map
void testScanner(char *, char  *); //remove comments and write to new file.

extern FILE *file_pointer_filterd_file;
extern int line_nums;
extern char T_k;

#endif