#include <stdio.h>

 int main()

 {

 	int x;

 	int m = 1; 

 	int a = 2;

 	int b = 0;

 	int n = 0;


 	scanf("%d",&x);

 	if(x == 1){

 		printf("1ʲô������\n");

	}

 	printf("%d���ڵ�������:\n",x);

 	if(x >= 2){

 		printf("2  ");

 		n ++;

	}

 	if(x > 1){

 		for(m = 1;m <= x;m ++){

	 	for(a = 2; a < m;a ++){

 		if(m % a == 0){

 			b = 1;

 			break;

		}else{

		 	b = 2; //mark prime 

		}

	}

	if(b == 2){

	 	printf("%d  ",m);

	 	n ++;

	 	if(n % 5 == 0){

	 		printf("\n");

		}

	}

    }

	}

	printf("\n");

	printf("%d���ڹ���%d������",x,n);

	 

     return 0;

}
