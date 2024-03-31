//
// Created by Admin on 3/13/2024.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#include "scanner.h"
//#include "token.h"
#include "testScanner.h"
#include "BuildTree.h"
#include "TreeNode.h"

//Global vars
char nextChar;
FILE *file_pointer_filterd_file;
// char input_char;
struct Token tokens;

char empty_String[] = "Empty";  // empty for the nullable functions

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
                if(input_char != '\t' && input_char != '\n' && input_char != ' '){
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

   //readFromFile(outputfile); //passing the char array not the file pointer

//    if (root == NULL) {
//        printf("Failed to create abstract syntax tree.\n");
//        return;
//    }
//    /// Print the abstract syntax tree (AST)
//    printf("Abstract Syntax Tree:\n");
//
//    // Add a print statement before and after calling printAST
//    printf("Before printing AST.\n");
//    printAST(root, 0);
//    printf("After printing AST.\n");
//
//    // Free the memory allocated for the root node
//    freeNode(root);


}


// reading from the file and setting the nextchar as the global variable.
node_t* readFromFile(char* filename) {

    node_t* root = NULL;
    file_pointer_filterd_file = fopen(filename, "r"); // Open the file in read mode
    if (file_pointer_filterd_file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }
    memset(tokens.tokeninstance, '\0', MAX_INSTANCE_TOKEN);

    nextChar = fgetc(file_pointer_filterd_file);

    if (nextChar == '\n') {
        tokens.line_num++;
    }

    //node_t* root;  // the root of our root tree

    tokens = Scanner();


    root = S(); // call FUNCTION S

    if(tokens.tokenid == EOFtk){
        printf("OK\n");
    }else{
        printf("error in the parser!!! %c------%s.\n", nextChar, tokens.tokeninstance);
    }

    //printf("token found: %s--- %s--line: %d\n", tokenNames[tokens.tokenid], tokens.tokeninstance, line_nums);

    //fclose(file_pointer_filterd_file)
    //added for the seg-fault

    return root;
}
////////////////////////////////////////////////////////////////////////
//S-CD (we just call those functions, First set of S = t2)

node_t* S(){
    printf("Entering S()\n");

    node_t* P = createNode('S');

    P->left = C();
    P->center = D();

    printf("1. End of S non-terminal\n");
    printf("1.1 Value of P: %p, Left: %p, Right: %p\n", (void*)P, (void*)(P->left), (void*)(P->right)); // Print P, left, and right
    printf("EXITING S()\n");

    return P;

}
//
// A->FK (we will just call those functions, First set of A = t1 t2)
node_t* A(){
    node_t* P = createNode('A');
   // P-> left  = F();
   // P-> center = K();
    printf("1. End of A non-terminal\n");
    return  P;
}
//
// B-> . t2 A ! (first set of B = . )
node_t* B(){
    if (tokens.tokeninstance[0] == '.'){
        node_t* P = createNode('B'); //create the node

        node_t* B_token_ptr = createNode(' '); //create an empty node
        //B_token_ptr -> token_id = tokens.tokenid;   //getting token id
        strncpy(B_token_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
        P->center = B_token_ptr;

        tokens = Scanner(); //consume

        if(tokens.tokenid == T2_tk){

            node_t*  B_tk_ptr_2 = createNode(' '); //create an empty node
            B_tk_ptr_2 -> token_id = tokens.tokenid;   //getting token id
            strncpy(B_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = B_tk_ptr_2;

            tokens = Scanner(); //consume

            P->right = A(); //call A

            if (tokens.tokeninstance[0] == '!'){

                node_t*  B_tk_ptr_3 = createNode(' '); //create an empty node
                B_tk_ptr_3 -> token_id = tokens.tokenid;   //getting token id
                strncpy(B_tk_ptr_3->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
                P->far_right = B_tk_ptr_3;

                printf("5.B token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
                tokens = Scanner();
                printf("6.B token instance { %s } token Id %s consumed ( ! )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

                return P;

            }else{ printf("B1. ERROR\n");  }
        }else{ printf("B2. ERROR\n");}
    }else{ printf("B3. ERROR\n");}
}
//
// C -> t2 * (first set of C = T2)
node_t* C(){
    printf("Entering C()\n");

    node_t* P = createNode('C'); //create node C

    if(tokens.tokenid == T2_tk){
       // printf("1.C token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        printf("Token Instance: %s \n", tokens.tokeninstance);

        node_t* c_token_ptr = createNode(' ');
        c_token_ptr->token_id = tokens.tokenid;
        strncpy(c_token_ptr->token_instance, tokens.tokeninstance, MAX_INSTANCE_TOKEN);
        //sprintf(c_tokenptr->token_instance, "%s", tokens.tokeninstance);
        P->left = c_token_ptr;
        printf("!!!Token Instance: %s --%s \n", tokens.tokeninstance, c_token_ptr->token_instance );
        printf("tokens.tokenid: %d---%s\n", tokens.tokenid, tokenNames[tokens.tokenid]);


        tokens = Scanner();
       // printf("2.C token instance { %s } token Id %s consumed ( t2 )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        if(tokens.tokeninstance[0] == '*'){
           // printf("3.C token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            node_t* c_tokenptr_2 = createNode(' ');
            c_tokenptr_2 -> token_id = tokens.tokenid;   //getting token id
            strncpy(c_tokenptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = c_tokenptr_2;


            tokens = Scanner();
           // printf("4.C token instance { %s } token Id %s consumed ( * )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            printf("EXITING C()\n");
            return P;

        }else{ printf("C1. ERROR\n");}
    }else{ printf("C2. ERROR\n");}
}

//
//D -> L (first set of D = , ,; . t2 *" ? epsilon
node_t* D(){
    printf("Entering C()\n");

    node_t* P = createNode('D'); //create node

    P-> left = L(); //left child

    printf("1.5 Value of P: %p, Left: %p, Right: %p\n", (void*)P, (void*)(P->left), (void*)(P->right)); // Print P, left, and right
    printf("EXITING C()\n");

    return P;
}
/*
//
//E -> , A A H | ,; F H (first set of E = , | ,;
node_t* E(){
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
*/
//F
//
node_t* G(){

    node_t* P = createNode('G'); //create node

    if (tokens.tokeninstance[0] == '.'){
        printf("1.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        P->left = B();

        return P;
    }
    else if (tokens.tokenid == T2_tk){
        printf("2.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        P->right = C();
        return P;
    }
    else if(tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"'){
        printf("3.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        P->far_right =J();
        return P;

    }else{ printf("G1. ERROR\n");exit(EXIT_FAILURE);}
}

node_t* H(){
    printf("Entering H()\n");

    node_t* P = createNode('H'); //create node

    if(tokens.tokenid == T3_tk && tokens.tokeninstance[0] == ','){


       // P -> left = E();

        if(tokens.tokeninstance[0] == '?'){

            node_t* H_tk_ptr = createNode(' ');
            strncpy(H_tk_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = H_tk_ptr;

            tokens = Scanner(); //consume

            printf("EXITING H()\n");

            return P;
        }else{printf("1.H ERROR\n");}

    }else if(tokens.tokeninstance[0] == '.' || tokens.tokenid == T2_tk ||
             (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"')){
        //printf("5.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        P->left =G();


        if (tokens.tokeninstance[0] == '.' && tokens.tokenid == T3_tk){

            node_t* H_tk_ptr_2 = createNode(' ');
            strncpy(H_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = H_tk_ptr_2;

            tokens = Scanner(); //consume


            printf("EXITING H()\n");
            return P;
        }else{printf("2.H ERROR\n");}

    }else{
        printf("H.7 EMPTY\n");
        node_t* H_tk_ptr_3 = createNode(' ');
        //H_tk_ptr_3 -> token_id = tokens.tokenid;   //getting token id
        strncpy(H_tk_ptr_3->token_instance, empty_String,MAX_INSTANCE_TOKEN );
        P->left = H_tk_ptr_3;
        printf("!!!EXITING empty H()\n");
        return P;
    }
}
//
// J-> *" A . (first set of J = *"
node_t* J(){

    node_t* P = createNode('J'); //create node

    if (tokens.tokeninstance[0]=='*' && tokens.tokeninstance[1]=='"' && tokens.tokenid == T3_tk){

        node_t* J_tk_ptr= createNode(' '); //create node
        //J_tk_ptr -> token_id = tokens.tokenid;   //getting token id
        strncpy(J_tk_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
        P->left = J_tk_ptr;

        tokens = Scanner(); //consume

        P->center = A();

        if (tokens.tokeninstance[0] == '.'){
            node_t* J_tk_ptr_2 = createNode(' '); //create node
            //J_tk_ptr -> token_id = tokens.tokenid;   //getting token id
            strncpy(J_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->right = J_tk_ptr_2;

            tokens = Scanner(); //consume

            return P;

        }else{printf("1.J ERROR\n"); exit(EXIT_FAILURE);}
    }else{printf("2.J ERROR\n"); exit(EXIT_FAILURE); }

}
node_t* L(){
    printf("Entering L()\n");

    node_t* P = createNode('L'); //create the node
    printf("1.hit here %s--- \n", tokens.tokeninstance);
    printf("1.L token instance { %s } token Id %s ()\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

    if(tokens.tokenid == T2_tk || tokens.tokeninstance[0] == '?' || (tokens.tokenid == T3_tk && (tokens.tokeninstance[0] == ',' || (tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';') ||
                                                               tokens.tokeninstance[0] == '.' || (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"')))){

        node_t* P = createNode('L'); //create the node

        printf("2.L token instance { %s } token Id %s (  )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        printf("2.hit here %s--- \n", tokens.tokeninstance);
         P->left = H();
        printf("3. hit here\n");

        if (tokens.tokeninstance[0] == '?'){

            node_t* L_token_ptr = createNode(' ');
            L_token_ptr -> token_id = tokens.tokenid;   //getting token id
            strncpy(L_token_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = L_token_ptr;

            tokens = Scanner();

            P->right = L();

            printf("EXITING L()\n");

            return P;

        }else{printf("1.L ERROR\n"); }

    }else{

        printf("3.L EMPTY\n");
        node_t* L_token_ptr_2 = createNode(' ');
        //L_token_ptr_2 -> token_id = tokens.tokenid;   //getting token id
        strncpy(L_token_ptr_2->token_instance, empty_String,MAX_INSTANCE_TOKEN );
        P->left = L_token_ptr_2;

        printf("EXITING/empty L()\n");
        return P; }
}

//



// A->FK (we will just call those functions, First set of A = t1 t2)
/*
node_t* A(){
    node_t* P = createNode('S');
    P-> left  = F();
    P-> right = K();
    printf("1. End of A non-terminal\n");
    return  P;
}*/
//
// B-> . t2 A ! (first set of B = . )
/*
node_t* B(){
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

                return B();
            }else{ printf("B1. ERROR\n");  }
        }else{ printf("B2. ERROR\n");}
    }else{ printf("B3. ERROR\n");}
}
*/
/*
// C -> t2 * (first set of C = T2)
node_t* C(){
    node_t* P = createNode('C');

    if(tokens.tokenid == T2_tk){
        printf("1.C token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        tokens = Scanner();
        printf("2.C token instance { %s } token Id %s consumed ( t2 )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        if(tokens.tokeninstance[0] == '*'){
            printf("3.C token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("4.C token instance { %s } token Id %s consumed ( * )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            return P;

        }else{ printf("C1. ERROR\n");}
    }else{ printf("C2. ERROR\n");}
}

//D -> L (first set of D = , ,; . t2 *" ? epsilon
node_t* D(){
    node_t* P = createNode('D');
    P-> left = L();
    printf("D. called L\n");
    return P;
}*/
//
//E -> , A A H | ,; F H (first set of E = , | ,;
/*
node_t* E(){
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
}*/
//
// F-> t1 | t2 (first set of F = t1 | t2)
/*
node_t* F(){
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
}*/
// why don't we consume after a token in here?
// G -> B|C|J (fist set of G -> . | t2 | *"
/*
node_t* G(){
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
}*/

// why dont we consume here in t3
// H-> E? | G. | empty (first set of H = , ,; | . t2 *" | empty
/*
node_t* H(){
    node_t* P = createNode('H');
    if(tokens.tokenid == T3_tk && tokens.tokeninstance[0] == ','){
        printf("1.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        //P -> left = E();

        if(tokens.tokeninstance[0] == '?'){
            printf("2.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("3.H token instance { %s } token Id %s consumed ( ? )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            return P;
        }else{printf("1.H ERROR\n");}

    }else if(tokens.tokeninstance[0] == '.' || tokens.tokenid == T2_tk ||
        (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"')){
        printf("5.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        //G();


        if (tokens.tokeninstance[0] == '.' && tokens.tokenid == T3_tk){
            printf("5.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
            tokens = Scanner();
            printf("6.H token instance { %s } token Id %s consumed ( . )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            return P;
        }else{printf("2.H ERROR\n");}

    }else{ printf("H.7 EMPTY\n"); return P;}
}
 */
//
// J-> *" A . (first set of J = *"
/*
node_t* J(){
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

}*/
//we don't consume?
// K -> F ?$ | . (first set of K = t1 t2 | .
/*
node_t* K(){
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
*/
/*
//L-> H?L | empty (first set of L = , ,; . t2 *" ?
node_t* L(){
    node_t* P = createNode('L');
    if(tokens.tokenid == T2_tk || (tokens.tokenid == T3_tk && (tokens.tokeninstance[0] == ',' || (tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';') ||
            tokens.tokeninstance[0] == '.' || (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"') || tokens.tokeninstance[0] == '?'))){

            P-> left = H();

            if (tokens.tokeninstance[0] == '?'){
                printf("1.L token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

                tokens = Scanner();

                printf("2.L token instance { %s } token Id %s consumed ( ? )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

                P-> left = L();

                return P;
            }else{printf("1.L ERROR\n"); }

    }else{ printf("3.L EMPTY\n"); }
}


*/






























//
//
//
//void S() {
//    if (tokens.tokenid == T2_tk) {
//        //tokens = Scanner(); // consume t2
//        printf("S. %s s if statement %s\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        C(); // call C
//        D(); //call D
//        return;
//
//    }else{ printf("error in function S \n");}
//}
//// production A-> FK     // first of A -> t1 | t2 // predict T1 or T2 (first OF F) // predict // this just calls the functions?
//void A(){
//        F();
//        K();
//        printf("A. %s  if id: %s\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
//}
//
////B->.t2A! first set B-> . //prediction  . //process t2 //process  //process !
//void B(){
//    if(tokens.tokeninstance[0] == '.') {
//        printf("B 1.1 instance %s  tk id: %s { . }\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        tokens = Scanner(); // process .
//        if(tokens.tokenid == T2_tk){    // process t2
//            printf("B 1.2 instance %s  tk id: %s { t2 }\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner(); // consume t2
//            A(); //Process A
//            if(tokens.tokeninstance[0] == '!'){
//                printf("B 1.3 instance %s  tk id: %s { ! }\n",  tokens.tokeninstance, tokenNames[tokens.tokenid]);
//                tokens = Scanner(); //consume !
//                return;
//            }else{ printf("B1. error in function S \n");}
//        } else{ printf("B2. error in function S \n");} // t2 if
//    } else {printf("B3. B: ERROR\n");}
//}
//
//// C -> t2*  first set of C -> t2
//// predicts t2
//// processes t2
//// processes * not nullable so need to have error check.
//void C(){
//
//    if (tokens.tokenid == T2_tk){
//        printf("C 1.1. instance %s tk id %s { t2 }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        tokens = Scanner(); // process/consume T2
//
//        printf("C 1.2 instance %s tk id %s --consumed--{ t2 }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//
//        if(tokens.tokenid ==  T3_tk && tokens.tokeninstance[0] == '*'){ // process *
//            printf("C 1.3. instance %s tk id %s { * }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner(); // T3 or *
//           // printf("C 1.4. instance %s tk id %s consumed{ * }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//
//            return;
//
//        }else{printf("error in function C \n");}
//
//    } else {printf("C: ERROR\n");}
//}
//// grammer D first set -> , ,; . t2 *" ? empty
//// predict D -> L
//// processing -> ,
//// processing -> ,;
//// processing -> .
//// processing -> t2
//// processing -> *
//// processing -> "
//// processing -> ?
//// processing -> empty  it is nullable
//void D(){
//    //if(tokens.tokenid == T3_tk){
////        tokens = Scanner();
//    printf("D 1.1. instance %s tk id %s {called from S with token2}\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//    L();
//}
//
//// production rule E -> , A A H | . ; F H
//// first set of E -> ,|,;
//// predict ,
//// process A
//// PROCESS A ???
//// Porcess H
//// predict ,;
//// process F
//// Process H
//void E(){
//    if(tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] != ';' ){
//        printf("E 1.1. instance %s tk id %s { , }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        tokens = Scanner(); // process ,
//        printf("E 1.1. instance %s tk id %s { , }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        A(); // process A
//        A(); // process A
//        H(); // Process H
//        return;
//    }
//    else if(tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';'){
//        printf("E 1.2. instance %s tk id %s { ,; }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        tokens = Scanner(); // process ,;
//        F(); // process F
//        H(); // Process H
//        return;
//    }
//    else {printf("error in function E\n");}
//}
//
//// production rule: F -> t1|t2
//// predicts t1
//// predicts t2
//// process empty
//// processes empty
//void F(){
//    if (tokens.tokenid == T1_tk) {
//        printf("F 1.1 instance %s tk id %s { t1 }}\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        tokens = Scanner(); // processing T1_tk
//        return;
//    }
//    else if(tokens.tokenid == T2_tk){
//        printf("F 1.2 instance %s tk id %s {t2}\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        tokens = Scanner(); // processing T2_tk
//        return;
//
//    }else {printf("error in function F \n");}
//
//}
//
//// production G-> B|C|J
//// predict . or t2 or *"
//
//void G(){
//    if(tokens.tokeninstance[0] == '.'){
//        printf("G 1.1. instance %s tk id %s { . }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        //tokens = Scanner(); //consume .????????????????????????????????
//        B();
//        return;
//    }
//    else if(tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"'){
//        printf("G 1.1. instance %s tk id %s { *\"}\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        //tokens = Scanner(); //consume *" ??????????????????????
//        J();
//        return;
//    }
//    else if(tokens.tokenid == T2_tk){
//        printf("G 1.3. instance %s tk id %s { t2 }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        //tokens = Scanner(); //consume t2 >??????????????????????????????
//        C();
//
//        return;
//    }else {printf("G 1.1 ERROR!!\n");}
//}
//
//
//// production rule H-> E?|G.|empty
//// first sets of H -> , ,; | . t2 * " | empty
//// predict ,  ,; (first of E)
//// process ?
//// predict . T2 * "
//// process .
//// predict empty
//// return empty
//void H(){
//
//    if (tokens.tokeninstance[0] == ',') {
//
//        E(); // process
//
//        printf("H 1.1.1 instance %s tk id %s { , }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        //tokens = Scanner(); // consume , ????????????????????????????????
//        if(tokens.tokeninstance[0] == '?') { // process ?
//            printf("H 1.1.2 instance %s tk id %s { ? }\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner(); // consumes ?
//            return;
//
//        }else{ printf("L 1.3 ERROR!!\n"); }
//    }///
//    else if(tokens.tokeninstance[0] == '.' || tokens.tokenid == T2_tk ||
//      (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"')){ // predicts . or t2 or * or "
//        //tokens = Scanner(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//        printf("H 1.2.1 instance %s tk id %s { . t2 *\" } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        G();
//       //tokens = Scanner(); // consumes . or t2 or *" ?????????????????????????????
//        if(tokens.tokeninstance[0] == '.'){ // process .
//            printf("H 1.2.2 instance %s tk id %s { . } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner(); // consume .
//            return;
//
//        }else{ printf("H 1.3.1 ERROR!!\n"); }
//
//    }else { printf("H: 1.3 empty\n"); }
//
//}
//
//// production J -> * " A .
//// first set of J -> *"
//// predict *"
//// process A
//// process A
//void J(){
//    if (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"'){
//        printf("J 1.1 instance %s tk id %s { *\"} \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        tokens = Scanner(); // consume *"
//        A(); // process A
//
//        if(tokens.tokenid == (tokens.tokeninstance[0] == '.')){
//            printf("J 1.2 instance %s tk id %s { . } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner(); // consume .
//            return;
//
//        }else{ printf("j 1.3 ERROR!!\n"); }
//    }else{ printf("j 1.4 ERROR!!\n"); }
//
//}
////production rule -> F?% | .
//// predict t1 | t2 (First of F)
//// process ?
//// process %
//// predict .
//
//void K(){
//    if(tokens.tokenid == T1_tk || tokens.tokenid == T2_tk){
//        printf("k 1.1 instance %s tk id %s { T2/T3} \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        F();
//        //tokens = Scanner(); // consumes t2 or t1??????????????????
//        if (tokens.tokenid == (tokens.tokeninstance[0] == '?')){ // process ?
//            printf("k 1.2 instance %s tk id %s { ? } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner(); // consumes ?
//
//            if(tokens.tokenid == (tokens.tokeninstance[0] == '%')){ // process %
//                printf("K 1.3 instance %s tk id %s { PERCENT } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//                tokens = Scanner(); // consumes %
//                return;
//            }else {printf("K 1.1 ERROR!!\n"); }
//        }
//    }
//    else if(tokens.tokeninstance[0] == '.'){
//        printf("K 1.4 instance %s tk id %s { . } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        tokens = Scanner();
//
//    }
//    else {printf("K 1.2 Error\n");}
//}
//
///*******************************/
////production rule: L -> empty | H?L
////first sets of L -> empty | , ,; . t2 * " ?
//// predict , ,; . t2 * ' ? (first set of H)
//// process ?
//// process L
//// predict empty
//// return empty
//void L(){
//    if((tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';') ||
//        (tokens.tokeninstance[0] == ',') ||
//        (tokens.tokeninstance[0] == '.') ||
//        (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"') ||
//        (tokens.tokeninstance[0] == '?') ||
//         tokens.tokenid == T2_tk ){
////
//        H(); //call H
//
//        printf("L 1.1 instance %s tk id %s { ,; , . *\" } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//        //tokens = Scanner(); // consumes the fist of H ( for test 2 if i didn't consume it it was throwing an error);
//        //printf("L 1.1 instance %s tk id %s after consuming ? { ,; , . *\" } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//
//        if(tokens.tokeninstance[0] == '?') { //process ?
//            printf("L 1.2 instance %s tk id %s { ? } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//            tokens = Scanner(); //consumes ?
//            L();
//            printf("L 1.2.1 END instance %s tk id %s consumend { ? } \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
//// processing L
//            return;
//            printf("Hello\n");
//        }else{ printf("L 1.3 ERROR!!\n"); }
//
//    }else{printf("L/D: 1.2 empty\n"); return;}

//}

