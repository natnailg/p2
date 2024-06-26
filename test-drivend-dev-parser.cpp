
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

//
// Created by kerub on 3/31/2024.
//
