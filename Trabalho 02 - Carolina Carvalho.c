/*
    Aluna: Carolina Carvalho Aragão
    DRE: 121060252
*/

#include <stdio.h>
#include <stdlib.h>


/* Pilhas */
char stack[100];
int topo = -1;

void push (char x){
    stack[++topo] = x; 
}

char pop (){
    if (topo == -1){
        return -1;
    }
    else return stack[topo--];
}


float stack2[100];
int topo2 = -1;

void push2 (float x){
    stack2[++topo2] = x;
}

float pop2 (){
    if (topo2 == -1){
        return -1;
    }
    else return stack2[topo2--];
}


int stack3[100];
int topo3 = -1;

void push3 (int x){
    stack3[++topo3] = x;
}

int pop3 (){
    if (topo3 == -1){
        return -1;
    }
    else return stack3[topo3--];
}

int empty3 (){
    return topo3 == -1;
}


/* Dá prioridade aos operadores matemáticos */ 
int prioridadeDeOperacao (char x){

    if (x == '(') return 0;

    if (x == '+' || x == '-') return 1;

    if (x == '*' || x == '/') return 2;


}

/* Transforma uma expressão matemática normal para uma expressão na forma RPN (Infix 2 Postfix) e calcula o resultado */
int infix2Postfix (){

    char expressionInfix[100];
    char expressionPostfix[100];
    char *eI, x;
    char *eP;
    int index = 0;
    int a, b, i;
    int order, number;
    float result = 0;
 
    

    printf("Entre a expressao desejada: \n");
    scanf("%s", expressionInfix);

    eI = expressionInfix;

       
    /* Transforma a expressão matemática (infix) para uma expressão em RPN */
    while (*eI != '\0'){

        if(isalnum(*eI)){
            
            expressionPostfix[index] = *eI;
            index++;
        
        }

        else if (*eI == '('){

            push(*eI);

        }  
        
        else if (*eI == ')'){

            while((x = pop()) != '('){
                expressionPostfix[index] = x;
                index++;
            }
        }

        else{

            expressionPostfix[index] = ' ';
            index++;

            while(prioridadeDeOperacao(stack[topo]) >= prioridadeDeOperacao(*eI)){
                
                expressionPostfix[index] = pop();
                index++;

                expressionPostfix[index] = ' ';
                index++;


            }
            push(*eI);
            
        }

        eI++;
        
    }
    
    while (topo != -1){

        expressionPostfix[index] = pop();
        index++;
    }

    /* Calcula a expressão em RPN utilizando pilha */

    eP = expressionPostfix;

    while (*eP != '\0'){

        if(isalnum(*eP)){

            order = 1;
            number = 0;
            
            while(isalnum(*eP)){
                
                push3(*eP  - '0');
                eP++;
            }

            while (!empty3()){
                
                number += pop3()*order;
                order *= 10;

            }

            result = (float) number;
            push2(result);
            continue;    
        
        }
        
        else if(*eP == '+'){

            a = pop2();
            b = pop2();
            result = a + b;
            push2(result);  

        }

        else if(*eP == '-'){
            
            b = pop2();
            a = pop2();
            result = a - b;
            push2(result);  

        }

        else if(*eP == '*'){

            a = pop2();
            b = pop2();
            result = a * b;
            push2(result);   

        }

        else if (*eP == '/'){

            b = pop2();
            a = pop2();
            result = a / b;
            push2(result); 

        }

        else if(*eP == ' '){
            eP++;
            continue;
        }

        eP++;

        
    }

    printf("\n%.2f", result);

}

int main (){

    infix2Postfix();

}