/*
An extension of scientific_calculator
Add a function of assigning values to variables
*/

#include <stdio.h>
#include "framework.h"
#include "advanced_calculator.h"
#include "scientific_calculator.h"

extern double a,b,c,d;  

void advanced_calculator(){

    printf("\nHello...\n\n");
    printf("Please input the variables(a b c d in order):\n");  
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    fflush(stdin);
    printf("\na=%g b=%g c=%g d=%g\nYou can use them in your expression now.\n", a, b, c, d);  

    scientific_calculator();

}