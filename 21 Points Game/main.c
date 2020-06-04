#include <stdio.h>
#include <stdlib.h>


int main() 
{
	int sel=1;
    while(sel!=0){
    	sel = menu();
    	switch(sel)
		{		
    		case 1:
				Point_21();
    			break;
    		case 2:
    			Poker();
    			break;
    		case 0:
    			Game_end();
    			continue;
    		default:
    			printf("Error!\n");
		}
}
	printf("请按任意键继续...");	
	return 0;
}
