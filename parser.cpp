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
    memset(tokens.tokeninstance, '\0', MAX_INSTANCE_TOKEN);

    nextChar = fgetc(file_pointer_filterd_file);

    if (nextChar == '\n') {
        tokens.line_num++;
    }
    printf("1.1 froms readfromFile: %s \n", tokens.tokeninstance);
    tokens = Scanner();
    printf("1.2 froms readfromFile: %s \n", tokens.tokeninstance);
    S(); // call FUNCTION S

    if(tokens.tokenid == EOFtk){ printf("OK\n");}
//        }else{
//            printf("error in the parser!!! %c------%s.\n", nextChar, tokens.tokeninstance);
//        }

    //printf("token found: %s--- %s--line: %d\n", tokenNames[tokens.tokenid], tokens.tokeninstance, line_nums);

    fclose(file_pointer_filterd_file);
}
////////////////////////////////////////////////////////////////////////
//S-CD (we just call those functions, First set of S = t2)
void S(){
    C();
    D();
    printf("1. End of S non-terminal\n");
}

// A->FK (we will just call those functions, First set of A = t1 t2)
void A(){
    F();
    K();
    printf("1. End of A non-terminal\n");
}
//
// B-> . t2 A ! (first set of B = . )
void B(){
    if (tokens.tokeninstance[0] == '.'){
        printf("1.B token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        printf("2.B token instance { %s } token Id %s consumed ( . )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        if(tokens.tokenid == T2_tk){
            printf("3.B token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("4.B token instance { %s } token Id %s consumed ( t2 )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            A(); //call A
            if (tokens.tokeninstance[0] == '!'){
                printf("5.B token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
                tokens = Scanner();
                printf("6.B token instance { %s } token Id %s consumed ( ! )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

                return;
            }else{ printf("B1. ERROR\n");}
        }else{ printf("B2. ERROR\n");}
    }else{ printf("B3. ERROR\n");}
}

// C -> t2 * (first set of C = T2)
void C(){
    if(tokens.tokenid == T2_tk){
        printf("1.C token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        printf("2.C token instance { %s } token Id %s consumed ( t2 )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        if(tokens.tokeninstance[0] == '*'){
            printf("3.C token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("4.C token instance { %s } token Id %s consumed ( * )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            return;

        }else{ printf("C1. ERROR\n");}
    }else{ printf("C2. ERROR\n");}
}
//D -> L (first set of D = , ,; . t2 *" ? epsilon
void D(){

    L();
    printf("D. called L\n");

}
//
//E -> , A A H | ,; F H (first set of E = , | ,;
void E(){
    if (tokens.tokeninstance[0] == ',' and tokens.tokeninstance[1] != ';'){
        printf("1.E token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        printf("2.C token instance { %s } token Id %s consumed ( , )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        A();
        A();
        H();
        return;
    }
    else if (tokens.tokeninstance[0] == ',' and tokens.tokeninstance[1] == ';'){
        printf("3.E token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        printf("4.C token instance { %s } token Id %s consumed ( ,; )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        F();
        H();
        return;
    }else{ printf("E1. ERROR\n");}
}
//
// F-> t1 | t2 (first set of F = t1 | t2)
void F(){
    if (tokens.tokenid == T1_tk){
        printf("1.F token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        printf("2.F token instance { %s } token Id %s consumed ( T1 )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        return;

    }
    else if( tokens.tokenid == T2_tk){
        printf("3.F token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        printf("4.C token instance { %s } token Id %s consumed ( T2 )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        return;

    }else{ printf("E1. ERROR\n");}
}
// why don't we consume after a token in here?
// G -> B|C|J (fist set of G -> . | t2 | *"
void G(){
    if (tokens.tokeninstance[0] == '.'){
        printf("1.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        B();
        return;
    }
    else if (tokens.tokenid == T2_tk){
        printf("2.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        C();
        return;
    }
    else if(tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"'){
        printf("3.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        J();
        return;
    }else{ printf("G1. ERROR\n");}
}
// why dont we consume here in t3
// H-> E? | G. | empty (first set of H = , ,; | . t2 *" | empty
void H(){
    if(tokens.tokenid == T3_tk && tokens.tokeninstance[0] == ','){
        printf("1.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        E();

        if(tokens.tokeninstance[0] == '?'){
            printf("2.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("3.H token instance { %s } token Id %s consumed ( ? )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            return;
        }else{printf("1.H ERROR\n");}

    }else if(tokens.tokeninstance[0] == '.' || tokens.tokenid == T2_tk ||
             (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"')){
        printf("5.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        G();


        if (tokens.tokeninstance[0] == '.' && tokens.tokenid == T3_tk){
            printf("5.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("6.H token instance { %s } token Id %s consumed ( . )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            return;
        }else{printf("2.H ERROR\n");}

    }else{ printf("H.7 EMPTY\n"); return;}
}
//
// J-> *" A . (first set of J = *"
void J(){
    if (tokens.tokeninstance[0]=='*' && tokens.tokeninstance[1]=='"' && tokens.tokenid == T3_tk){
        printf("1.J token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        printf("2.J token instance { %s } token Id %s consumed ( *\" )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        A();

        if (tokens.tokeninstance[0] == '.'){
            printf("3.J token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("4.J token instance { %s } token Id %s consumed ( . )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            return;
        }else{printf("1.J ERROR\n"); return;}
    }else{printf("2.J ERROR\n"); return; }

}
//we don't consume?
// K -> F ?$ | . (first set of K = t1 t2 | .
void K(){
    if (tokens.tokenid == T1_tk || tokens.tokenid == T2_tk ){
        F();

        if (tokens.tokeninstance[0] == '?' && tokens.tokeninstance[1] == '$' && tokens.tokenid == T3_tk){
            printf("1.K token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("2.K token instance { %s } token Id %s consumed ( ?$ )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            return;
        }else{printf("1.J ERROR\n"); return; }
    }
    else if(tokens.tokeninstance[0] == '.'){
        printf("3.K token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        tokens = Scanner();
        printf("4.K token instance { %s } token Id %s consumed ( . )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        return;
    }
    else{printf("2.J ERROR\n"); return; }
}
//
//L-> H?L | empty (first set of L = , ,; . t2 *" ?
void L(){
    if(tokens.tokenid == T2_tk || (tokens.tokenid == T3_tk && (tokens.tokeninstance[0] == ',' || (tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';') ||
                                                               tokens.tokeninstance[0] == '.' || (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"') || tokens.tokeninstance[0] == '?'))){

        H();
        if (tokens.tokeninstance[0] == '?'){
            printf("1.L token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("2.L token instance { %s } token Id %s consumed ( ? )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            L();
            return;
        }else{printf("1.L ERROR\n"); return; }

    }else{ printf("3.L EMPTY\n"); return;}
}

