#ifndef _SCIENTIFIC_CALCULATOR_H_
#define _SCIENTIFIC_CALCULATOR_H_

//Constants
#define N 200    //Max Length of input string
#define Pi M_PI
#define E M_E
#define MAX INT_MAX
#define MIN INT_MIN
#define MIN_FLOAT 0.000001
#define ERROR result-(int)result

double func_num(void);
double func(void);
double times_divides(void);
double plus_mines(void);
int scientific_calculator(void);

#endif