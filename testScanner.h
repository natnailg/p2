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
extern struct Token tokens;


void S(); // CD  -> first set of S = t2
void A(); // FK -> first set of A = t1 t2
void B(); // .t2A! -> first set of B = .
void C(); // t2* -> first set of C = t2
void D(); // L -> first set of D = , ,; . t2 *" ? empty
void E();
void F();
void G();
void H();
void J();
void K();
void L();
#endif