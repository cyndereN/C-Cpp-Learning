/*
Use recursion to parse and evaluate mathematical expressions.
*/

#include <stdio.h>
#include "framework.h"
#include "scientific_calculator.h"
#include "advanced_calculator.h"

extern double a,b,c,d;  

//Textual prompts
const char *S1 = "->To see the operators please input help\n->To start calculating please input the expression\n->To exit please input exit.\n\n";

const char *S2 = "\n--------------------------------------------\n\n->Trigonometric function (X as the angle): sin(x),cos(x),tan(x)\n\
->Inverse trigonometric function (X as the angle):asin(x),acos(x),atan(x)\n->Logarithm: lg(x), ln(x)\n->SQRT, e^x: sqrt(x), exp(x)\n\
->Random number between (0,x): rand(x)\n\nNOTE: Don't input SPACE!!!\n\n";


char token[N];  // Expression string
char str[N];	//Input String
int n = 0, m = 0, t = 0;
int cal = 0;  //Flag of calculated


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

	if(strstr(a,"sin")&&a[0]!='a'&&a[3]!='h')
		value_p = sin(a_to_r(value));
	if(strstr(a,"cos")&&a[0]!='a'&&a[3]!='h')
		value_p = cos(a_to_r(value));
	if(strstr(a,"tan")&&a[0]!='a'&&a[3]!='h')
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
			if (divisor == 0)
				printf("Divisor cannot be 0!!!\n");
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

//Deal with brackets, floats, numbers
double func_num(){

	double value_p;
	char number[N]; //Array of number
	int i = 0;

	if (token[m] == '('){

		token[++m] = str[t++];
		value_p = plus_mines();
		if (token[m] == ')')
			token[++m] = str[t++];

	}
	else if (isalpha(token[m]) && !isalpha(token[m+1])){ //Determine if it's variable
		switch(token[m]){
			case 'a': value_p = a; break;
			case 'b': value_p = b; break;
			case 'c': value_p = c; break;
			case 'd': value_p = d; break;
		}

		token[++m] = str[t++];
	}
	else if (isdigit(token[m]) || token[m] == '.'){

		while (isdigit(token[m]) || token[m] == '.'){
			number[i++] = token[m++];    
			token[m] = str[t++];
		}

		number[i] = '\0';
		value_p = atof(number); //ASCII to float
	}
	return value_p;

}


int scientific_calculator(){

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
            
            cal = 1;
            m = t = 0;
            token[m] = str[t++];
            
            result = plus_mines();
            
            if ( result>MAX || result<MIN || (result>0 && result<MIN_FLOAT && !strstr(str,"sin") && !strstr(str,"cos")) )
                printf("Result = %g\n",result);
            else{ //Calibration
                if (ERROR==0)
                    printf("Result = %d\n", (int)result);
                else
                    printf("Result = %lf\n", result);
            }

            printf("\n--------------------------------------------\n\n");

            if (cal == 1) //Clear str
            {
                strcpy(str,"\0");
                cal = result = 0;
            }
		}
	}
}
