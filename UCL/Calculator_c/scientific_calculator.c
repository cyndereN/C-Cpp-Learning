/*
Use recursion to parse and evaluate mathematical expressions.
The order is based on precedence of operators
*/

#include <stdio.h>
#include "framework.h"
#include "scientific_calculator.h"
#include "advanced_calculator.h"

extern double a,b,c,d;  

//Textual prompts
const char *S1 = "->To see the operators please input help.\n->To calculate please input the expression then press enter.\n->To exit please input exit.\n\n";

const char *S2 = "\n--------------------------------------------\n\n->Trigonometric function (X as the angle): sin(x),cos(x),tan(x)\n\
->Inverse trigonometric function (X as the angle):asin(x),acos(x),atan(x)\n->Logarithm: lg(x), ln(x)\n->SQRT, e^x: sqrt(x), exp(x)\n\
->Random number between (0,x): rand(x)\n\nNOTE: Don't input SPACE!!!\n\n--------------------------------------------\n\n";


char token[N] = {0};  // Expression string
char str[N];	//Input String
int n = 0, m = 0, t = 0;
int err = 0; //Flag of error


//Deal with brackets, floats, numbers
double func_num(){

	double value_p = 0;
	char number[N]; //Array of number
	int i = 0;

	if (token[m] == '('){

		token[++m] = str[t++];
		value_p = plus_mines();
		if (token[m] == ')')
			token[++m] = str[t++];

	}
	
	else if (isalpha(token[m]) && !isalpha(str[t]) ){ //Determine if it's variable
		switch(token[m]){
			case 'a': value_p = a; break;
			case 'b': value_p = b; break;
			case 'c': value_p = c; break;
			case 'd': value_p = d; break;

			default: break;
		}

		token[++m] = str[t++];
	}
	
	else if (isdigit(token[m]) || token[m] == '.'){
		while (isdigit(token[m]) || token[m] == '.'){
			number[i++] = token[m++];    
			token[m] = str[t++];
		}

		number[i] = '\0';
		value_p = atof(number); //Char to double
	}
	
	return value_p;

}



// Angle to radians
double a_to_r(double a){

	return Pi * a / 180;

}
// Radians to angle
double r_to_a(double a){

	return 180 * a / Pi;

}

double factorial(int a){

	double b=1;

	if (a){
		for (int i=1;i<=a;i++)
			b *= i;
	}
	return b;

}

//Random number generator (one of my favorite functions in a calculator :D)
double random_number(){

    srand(time(NULL));
    return (double)rand() / RAND_MAX;

}

//Deal with special operators
double func(){

	char a[5] = {0};
	int i = 0;
	double value_p = func_num(), value=0;

	while (isalpha(token[m]) || token[m]=='^' || token[m]=='!' || token[m]=='%'){

		a[i++] = str[t-1];

		switch (token[m]){

			case '^':
			token[++m] = str[t++];
			value = func_num();
			value_p = pow(value_p,value);
			break;

			case '!':
			token[++m] = str[t++];
			value_p = factorial(value_p);
			func_num();
			break;

			case '%':
			token[++m] = str[t++];
			value_p/=100;
			func_num();
			break;
			
			default:
			token[++m] = str[t++];
			break;

		}
	}
	
	//Trigonometric function
	if (islower(a[0]))
		value = func_num();

	if(strstr(a,"sin")&&a[0]!='a')
		value_p = sin(a_to_r(value));
	if(strstr(a,"cos")&&a[0]!='a')
		value_p = cos(a_to_r(value));
	if(strstr(a,"tan")&&a[0]!='a')
		value_p = tan(a_to_r(value));

	//Inverse trigonometric function
	if(strstr(a,"asin"))
		value_p = r_to_a(asin(value));
	if(strstr(a,"acos"))
		value_p = r_to_a(acos(value));
	if(strstr(a,"atan"))
		value_p = r_to_a(atan(value));

	//Logarithm
	if(strstr(a,"lg"))
		value_p = log10(value);
	if(strstr(a,"ln"))
		value_p = log(value);

	//Root, exp, random
	if(strstr(a,"sqrt"))
		value_p = sqrt(value);
	if(strstr(a,"exp"))
		value_p = exp(value);
	if(strstr(a,"rand"))
		value_p = random_number() * value;

	return value_p;
}



double times_divides(){

	double divisor;
	double value_p = func(), value = 0;

	while ((token[m] == '*') || (token[m] == '/'))
		switch (token[m]){

			case '*':
			token[++m] = str[t++];
			value = func();
			value_p *= value;
			break;

			case '/':
			token[++m] = str[t++];
			divisor = func();
			if (divisor == 0){
				printf("\nDivisor cannot be 0!!!\n");
				err = 1;
			}
			value_p /= divisor;
			
			break;

		}
	return value_p;

}


double plus_mines(){

	double value_p = times_divides();
	double value = 0;

	while ((token[m] == '+') || (token[m] == '-'))
		switch (token[m]){

			case '+':
			token[++m] = str[t++];
			value = times_divides();
			value_p += value;
			break;

			case '-':
			token[++m] = str[t++];
			value = times_divides();
			value_p -= value;
			break;
			
		}
	return value_p;

}



void scientific_calculator(){

	double result;
	int opt;

	printf("%s", S1);

	while (1) {// Main loop

		scanf("%s", str);

		opt = 0; // Input control

		if (!strcmp(str, "exit")){
			break;
		}

		if (!strcmp(str, "help")){
		    printf("%s", S2);
		    opt = 1;
		}

		if (!opt){

            if ( str[0]=='-' || str[0]=='+' || str[0]=='*' || str[0]=='/' ){  
                for ( int b = n; b >= 1 ; b-- )
                    str[b] = str[b-1];
                str[0] = '0';
            }
            
			
            m = t = 0;
            token[m] = str[t++];
            
            result = plus_mines();
            
            if ( !err && (result>MAX || result<MIN || (result>0 && result<MIN_FLOAT && !strstr(str,"sin") && !strstr(str,"cos"))) )
                printf("Result = %g\n", result);

			else if (err)
				printf("\nSorry, there seems to be an error. Please input again.\n");
			
            else{ //Calibration
                if (ERROR==0)
                    printf("Result = %d\n", (int)result);
                else
                    printf("Result = %lf\n", result);
            }

            printf("\n--------------------------------------------\n\n");


            strcpy(str,"\0");  //Clear str
            result = err = 0;

		}
	}
}
