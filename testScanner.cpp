//
// Created by Admin on 3/13/2024.
//

#include <string.h>
#include <stdio.h>

//#include "scanner.h"
//#include "token.h"
#include "testScanner.h"
//Global vars
char nextChar;
char T_k;
FILE *file_pointer_filterd_file;
// char input_char;
struct Token tokens;


//let us get rid of all the comments in, they will start with # and end with one.
void testScanner(char *inputfile, char *outputfile) {
    FILE *input_file = fopen(inputfile, "r");
    if (input_file == NULL) {printf("Error opening input file.\n"); return;}

    FILE *output_file = fopen(outputfile, "w");
    if (output_file == NULL) { printf("Error opening output file.\n");  return;}

    char input_char;
    bool comments = false;

    while ((input_char = fgetc(input_file)) != EOF) {

        if (!comments) {
            if (input_char != '#') {
                if(input_char != '\t'|| input_char != '\n') {
                    fputc(input_char, output_file); // Write character to output file if not in a comment
                }
            }else{ // # is encounterd we set comment to true
                comments = true; //start of comment
            }
        }else{ //
            if(input_char == '#'){
                comments = false; //end of comment when
            }
        }
    }//END OF WHILE LOOp


    fclose(input_file);
    fclose(output_file);

    readFromFile(outputfile); //passing the char array not the file pointer

}


// reading from the file and setting the nextchar as the global variable.
void readFromFile(char* filename) {

    file_pointer_filterd_file = fopen(filename, "r"); // Open the file in read mode
    if (file_pointer_filterd_file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    nextChar = fgetc(file_pointer_filterd_file);

        if (nextChar == '\n') {
            tokens.line_num++;
        }

        tokens = Scanner();
        S();

        if(tokens.tokenid == EOFtk){
            printf("OK\n");}
//        }else{
//            printf("error in the parser!!! %c------%s.\n", nextChar, tokens.tokeninstance);
//        }

        //printf("token found: %s--- %s--line: %d\n", tokenNames[tokens.tokenid], tokens.tokeninstance, line_nums);

    fclose(file_pointer_filterd_file);
}
////////////////////////////////////////////////////////////////////////
// grammer = CD  then we have first set of S = t2
void S() {
    if (tokens.tokenid == T2_tk) {
        printf("S. %s s if statement %s\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
        C();
        D();
        return;
    }else{
        printf("error in function S \n");
    }
}
// t2* -> first set of C = t2
// predicts C -> t2*
// processes t2
// processes * not nullable so need to have error check.
void C(){
    if (tokens.tokenid == T2_tk){
        printf("C 1.1. %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        if(tokens.tokenid ==  T3_tk || tokens.tokeninstance[0] == '*')
            printf("C 1.2. %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        return;
    }else{
        printf("error in function C \n");
    }
}
// grammer D first set -> , ,; . t2 *" ? empty
// predict D -> L
// processing -> ,
// processing -> ,;
// processing -> .
// processing -> t2
// processing -> *
// processing -> "
// processing -> ?
// processing -> empty  it is nullable
void D(){
    //if(tokens.tokenid == T3_tk){
//        tokens = Scanner();
        //L();
        if(tokens.tokenid == (tokens.tokeninstance[0] == ',')){
            printf("D 1.1 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            return;
        }
        else if(tokens.tokenid == ((tokens.tokeninstance[0] == ',') && (tokens.tokeninstance[1] == ';') )){
            printf("D 1.2 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        }
        else if (tokens.tokenid == (tokens.tokeninstance[0] == '.' )){
            printf("D 1.3 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        }
        else if(tokens.tokenid == T2_tk){
            printf("4. %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        }
        else if(tokens.tokenid == (tokens.tokeninstance[0] == '"' )){
            printf("D 1.4 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        }
        else if(tokens.tokenid == (tokens.tokeninstance[0] == '"' )){
            printf("D 1.5%s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        }
        else if(tokens.tokenid == (tokens.tokeninstance[0] == '?' )){
            printf("D 1.6 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        }
        else{ printf("empty\n"); return; }

}


