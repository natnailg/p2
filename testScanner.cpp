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


    int line_nums = 1;
    // int index = 0; // to keep track of the current position in tokeninstance

    do{

        nextChar = fgetc(file_pointer_filterd_file);
        if (nextChar == '\n') {
            line_nums++;
            //printf("%d\n", line_nums);
            //      nextChar = fgetc(file_pointer_filterd_file);
            continue;
        }

        tokens = Scanner(line_nums);
        S();

        if(tokens.tokenid == EOFtk){
            printf("OK\n");
        }else{
            printf("error in the parser!!!.\n");
        }

        //printf("token found: %s--- %s--line: %d\n", tokenNames[tokens.tokenid], tokens.tokeninstance, line_nums);


    } while (nextChar != EOF);

    fclose(file_pointer_filterd_file);
}
////////////////////////////////////////////////////////////////////////
void S(){
    if(tokens.tokenid ==  T2_tk ){
        printf("toke in S: %s\n", tokens.tokenid);
    }
    printf("out of s if statment %s\n", tokenNames[tokens.tokenid]);
}