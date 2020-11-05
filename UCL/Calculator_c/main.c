/*
C coursework:
Intermediate level questions 3. Write a program that can parse and evaluate mathematical expressions, written in a textual
form (e.g., SQRT(10 * 11) + SQR(5)). Simple expressions might make use of numbers and
functions such as log or sin, while more complicated expressions might involve variables.
*/

/*
3 options of calculator:
1 is for computation of basic operators, 2 is for special operators and 3 involves variables
*/

#include "framework.h"
#include <stdio.h>
#include "basic_calculator.h"
#include "scientific_calculator.h"
#include "advanced_calculator.h"

void main_menu(void);
void display_menu(void);
int get_opt(void);
void do_opt(int);

int main(void){

    main_menu();
    return 0;

}

void main_menu(){

    while (1){
        display_menu();
        int opt = get_opt();

        if (opt == 4)  //Option 3 means exit program
            break;
        else
            do_opt(opt);
    }

}

void display_menu(){

    printf("\nC Coursework: Calculator\n");
    printf("%i. Basic Calculator (basic operators, e.g. +, -, *, /, ()\n", 1);
    printf("%i. Scientific Calculator (basic & special operators, e.g. +, /, (), sin(x), sqrt(x)...)\n", 2);
    printf("%i. Advanced Calculator (variables)\n", 3);
    printf("%i. Quit\n", 4);

}

int get_opt(){

    int opt = 0;
    scanf("%i", &opt);
    return opt;

}

void do_opt(int option){

    switch (option){
    
    case 1 : basic_calculator(); break;
    case 2 : scientific_calculator(); break;
    case 3 : advanced_calculator(); break;
    
    default : printf("\nSorry, please input again.\n");

    }
}


