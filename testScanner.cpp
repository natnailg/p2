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
    S(); // call FUNCTION S

    if(tokens.tokenid == EOFtk){ printf("OK\n");}
//        }else{
//            printf("error in the parser!!! %c------%s.\n", nextChar, tokens.tokeninstance);
//        }

        //printf("token found: %s--- %s--line: %d\n", tokenNames[tokens.tokenid], tokens.tokeninstance, line_nums);

    fclose(file_pointer_filterd_file);
}
////////////////////////////////////////////////////////////////////////
// grammer = CD  then we have first set of S = t2
// predict t2
// process C
//process D
void S() {
    if (tokens.tokenid == T2_tk) {
        //tokens = Scanner(); // consume t2
        printf("S. %s s if statement %s\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
        C();
        D();
        return;
    }else{ printf("error in function S \n");}
}
// production A-> FK     // first of A -> t1 | t2
// predict T1 or T2 (first OF F)
// predict
// this just calls the functions?
void A(){
        F();
        K();
        printf("A. %s  if id: %s\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
}

//B->.t2A! first set B-> .
//prediction  .
//process t2
//process A
//process !
//??????????????????????????????????????????????????? WHY TOKEN3?
void B(){
    if(tokens.tokenid == (tokens.tokeninstance[0] == '.')) {
        printf("B 1.1 instance %s  tk id: %s { . }\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner(); // process .
        if(tokens.tokenid == T2_tk){    // process t2
            printf("B 1.2 instance %s  tk id: %s { t2 }\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner(); // consume t2
            A(); //Process A
            if(tokens.tokenid == (tokens.tokeninstance[0] == '!')){
                printf("B 1.3 instance %s  tk id: %s { ! }\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
                tokens = Scanner(); //consume !
                return;
            }else{ printf("B1. error in function S \n");}
        } else{ printf("B2. error in function S \n");} // t2 if
    } else {printf("B3. B: ERROR\n");}
}

// C -> t2*  first set of C -> t2
// predicts t2
// processes t2
// processes * not nullable so need to have error check.
void C(){
    if (tokens.tokenid == T2_tk){
        printf("C 1.1. instance %s tk id %s { t2 }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner(); // process/consume T2

        if(tokens.tokenid ==  T3_tk && tokens.tokeninstance[0] == '*'){ // process *
            printf("C 1.2. instance %s tk id %s { * }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner(); // T3 or *
            return;

        }else{printf("error in function C \n");}

    } else {printf("C: ERROR\n");}
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
    printf("D 1.2. instance %s tk id %s { }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        L();

//        if(tokens.tokenid == (tokens.tokeninstance[0] == ',')){
//            printf("D 1.1 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner();
//            return;
//        }
//        else if(tokens.tokenid == ((tokens.tokeninstance[0] == ',') && (tokens.tokeninstance[1] == ';'))){
//            printf("D 1.2 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner();
//            return;
//        }
//        else if (tokens.tokenid == (tokens.tokeninstance[0] == '.' )){
//            printf("D 1.3 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner();
//            return;
//        }
//        else if(tokens.tokenid == T2_tk){
//            printf("4. %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner();
//            return;
//        }
//        else if(tokens.tokenid == (tokens.tokeninstance[0] == '*' )){
//            printf("D 1.4 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner();
//            return;
//        }
//        else if(tokens.tokenid == (tokens.tokeninstance[0] == '"' )){
//            printf("D 1.5%s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner();
//            return;
//        }
//        else if(tokens.tokenid == (tokens.tokeninstance[0] == '?' )){
//            printf("D 1.6 %s out of s in C if statement %s\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner();
//            return;
//        }
//        else{ printf("D: 1.7 empty\n"); return; }
}

// production rule E -> , A A H | . ; F H
// first set of E -> ,|,;
// predict ,
// process A
// PROCESS A ???
// Porcess H
// predict ,;
// process F
// Process H
void E(){
    if(tokens.tokeninstance[0] == ','){
        printf("E 1.1. instance %s tk id %s { , }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner(); // process ,
        A(); // process A
        A(); // process A
        H(); // Process H
        return;
    }
    else if(tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';'){
        printf("E 1.2. instance %s tk id %s { ,; }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner(); // process ,;
        F(); // process F
        H(); // Process H
        return;
    }
    else {printf("error in function E\n");}
}

// production rule: F -> t1|t2
// predicts t1
// predicts t2
// process empty
// processes empty
void F(){
    if (tokens.tokenid == T1_tk) {
        printf("F 1.1 instance %s tk id %s { t1 }}\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner(); // processing T1_tk
        return;
    }
    else if(tokens.tokenid == T2_tk){
        printf("F 1.2 instance %s tk id %s {t2}\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner(); // processing T2_tk
        return;

    }else {printf("error in function F \n");}

}

// production G-> B|C|J
// predict . or t2 or *"

void G(){
    if(tokens.tokeninstance[0] == '.'){
        printf("G 1.2. instance %s tk id %s { . }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        //tokens = Scanner(); //consume .????????????????????????????????
        B();
        return;
    }
    else if(tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"'){
        printf("G 1.2. instance %s tk id %s { *\"}\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        //tokens = Scanner(); //consume *" ??????????????????????
        J();
        return;
    }
    else if(tokens.tokenid == T2_tk){
        printf("G 1.2. instance %s tk id %s { t2 }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        //tokens = Scanner(); //consume t2 >??????????????????????????????
        C();

        return;
    }else {printf("G 1.1 ERROR!!\n");}
}


// production rule H-> E?|G.|empty
// first sets of H -> , ,; | . t2 * " | empty
// predict ,  ,; (first of E)
// process ?
// predict . T2 * "
// process .
// predict empty
// return empty
void H(){
    if (tokens.tokeninstance[0] == ',' ||
     (tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';')) {
        E(); // process
        printf("H 1.1.1 instance %s tk id %s { , }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner(); // consume , ????????????????????????????????
        if(tokens.tokeninstance[0] == '?') { // process ?
            printf("H 1.1.2 instance %s tk id %s { ? }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner(); // consumes ?
            return;

        }else{ printf("L 1.3 ERROR!!\n"); }
    }
    else if(tokens.tokeninstance[0] == '.' ||
        tokens.tokenid == T2_tk ||
        (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"')){ // predicts . or t2 or * or "

        printf("H 1.2.1 instance %s tk id %s { . t2 *\" } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        G();
       //tokens = Scanner(); // consumes . or t2 or *"?????????????????????????????

        if(tokens.tokenid == (tokens.tokeninstance[0] == '.')) { // process .
            printf("H 1.2.2 instance %s tk id %s { . } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner(); // consume .
            return;
        }

        }else { printf("H: 1.3 empty\n"); return; }

}

// production J -> * " A .
// first set of J -> *"
// predict *"
// process A
// process A
void J(){
    if (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"'){
        printf("J 1.1 instance %s tk id %s { *\"} \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner(); // consume *"
        A(); // process A

        if(tokens.tokenid == (tokens.tokeninstance[0] == '.')){
            printf("J 1.2 instance %s tk id %s { . } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner(); // consume .
            return;

        }else{ printf("j 1.3 ERROR!!\n"); }
    }else{ printf("j 1.4 ERROR!!\n"); }

}
//production rule -> F?% | .
// predict t1 | t2 (First of F)
// process ?
// process %
// predict .

void K(){
    if(tokens.tokenid == T1_tk || tokens.tokenid == T2_tk){
        printf("k 1.1 instance %s tk id %s { T2/T3} \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        F();
        //tokens = Scanner(); // consumes t2 or t1??????????????????
        if (tokens.tokenid == (tokens.tokeninstance[0] == '?')){ // process ?
            printf("k 1.2 instance %s tk id %s { ? } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner(); // consumes ?

            if(tokens.tokenid == (tokens.tokeninstance[0] == '%')){ // process %
                printf("K 1.3 instance %s tk id %s { PERCENT } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
                tokens = Scanner(); // consumes %
                return;
            }else {printf("K 1.1 ERROR!!\n"); }
        }
    }
    else if(tokens.tokeninstance[0] == '.'){
        printf("K 1.4 instance %s tk id %s { . } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();

    }
    else {printf("K 1.2 Error\n");}
}

/*******************************/
//production rule: L -> empty | H?L
//first sets of L -> empty | , ,; . t2 * " ?
// predict , ,; . t2 * ' ? (first set of H)
// process ?
// process L
// predict empty
// return empty
void L(){
    if((tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';') ||
        (tokens.tokeninstance[0] == ',') ||
        (tokens.tokeninstance[0] == '.') ||
        (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"') ||
        (tokens.tokeninstance[0] == '?') ||
         tokens.tokenid == T2_tk ){
//
        H(); //call H

        printf("L 1.1 instance %s tk id %s { ,; , . *\" } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        //tokens = Scanner(); // consumes the fist of H ( for test 2 if i didn't consume it it was throwing an error);

        if(tokens.tokeninstance[0] == '?') { //process ?
            printf("L 1.2 instance %s tk id %s { ? } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner(); //consumes ?
            L();
            printf("L 1.2.1instance %s tk id %s { ? } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
// processing L
            return;
            printf("Hello\n");
        }else{ printf("L 1.3 ERROR!!\n"); }
    }
    else{printf("L/D: 1.2 empty\n"); return;
    }

}

