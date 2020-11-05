/*
An extension of scientific_calculator
Add a function of assigning values to variables
*/

#include <stdio.h>
#include "framework.h"
#include "advanced_calculator.h"
#include "scientific_calculator.h"

double a=0, b=0, c=0, d=0; //4 variables to assign(default)

void advanced_calculator(){

    printf("\nHello...\n\n");
    printf("Please input the variables(a b c d in order):\n");  
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    printf("\na=%g b=%g c=%g d=%g\nYou can use them in your expression now.\n", a, b, c, d);  

    scientific_calculator();

}