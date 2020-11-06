/*
C coursework:
Intermediate level questions 3. Write a program that can parse and evaluate mathematical expressions, written in a textual
form (e.g., SQRT(10 * 11) + SQRT(5)). Simple expressions might make use of numbers and
functions such as log or sin, while more complicated expressions might involve variables.
*/

/*
2 options of calculator:
    1 is for scientific calculator with basic and special operators and 2 involves variables


NOTES:
- Use scientific notation for numbers that are too large or too small
- Brackets are needed. (sin30)^2 without brackets will be considered as sin(30^3)
- No space is allowed in the expression
*/

#include "framework.h"
#include <stdio.h>
#include "scientific_calculator.h"
#include "advanced_calculator.h"

void main_menu(void);
void display_menu(void);
char get_opt(void);
void do_opt(char);
char* get_input(void);

double a=0, b=0, c=0, d=0; //4 variables to assign (default 0)

int main(void){

    main_menu();
    return 0;

}

void main_menu(){

    while (1){
    
        display_menu();
        char opt = get_opt();

        if (opt == '3')  //Option 3 means exit program
            break;
        else
            do_opt(opt);
    }

}

void display_menu(){

    printf("\nCCoursework: Calculator\n");
    printf("%d. Scientific Calculator (basic & special operators, e.g. +, /, (), sin(x), sqrt(x)...)\n", 1);
    printf("%d. Advanced Calculator (variables)\n", 2);
    printf("%d. Quit\n", 3);

}

char get_opt(){
    char option;
    char *input = get_input();
    sscanf(input,"%c",&option);
    free(input);
    return option;
}

void do_opt(char option){

    switch (option){
    
    case '1' : scientific_calculator(); break;
    case '2' : advanced_calculator(); break;
    default : printf("\nSorry, please input again.\n");

    }
}


char* get_input(){   //In case of wrong input, reference: Graham, R (2020), phonebook.c.

    char buffer[N];
    fgets(buffer, N, stdin);
    size_t inputLength = strlen(buffer);
    char *input = calloc(sizeof(char), inputLength);
    strncpy(input, buffer, inputLength-1);
    input[inputLength] = '\0';
    return input;

}