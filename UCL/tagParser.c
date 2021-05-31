#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a[][30] = {};

#define TEST_FILE "valid.txt" // Change filename here

int is_valid_tag_name(char* string){
    int flag = 1;
    
    return flag;
}

// Read file, store the tags in an array and check for validity of tag name
void read_file(){
    int index = 0;
    char c;
    char b[30] = {};
    FILE *fp;
    int l_bracket = 0;
    int r_bracket = 0;

    if( ( fp = fopen(TEST_FILE, "r" ) ) == NULL ){
      printf( "Cannot open file! \n" );
      exit( 0 );
    }

    while((c = fgetc(fp)) != EOF){
        if ( c == '<') {
            l_bracket++;
            int i = 0;
            c = fgetc(fp);
            while ( c != '>' && c != EOF){
                if (c == '<') { 
                    printf( "Missing bracket! \n" );
                    exit( 0 );
                }
                // Ignore whitespace
                if (c != ' ') {
                    b[i] = c;
                    i++;
                }
                c = fgetc(fp);
            }
            b[i] = '\0';

            if(is_valid_tag_name(b)){
                strcpy(a[index], b);
                index++; 
            } else {
                printf( "Invalid tag name! \n" );
                exit( 0 );
            }
            
        }
        if ( c == '>')  r_bracket++;
    }

    fclose(fp);

    printf("%d %d\n", l_bracket, r_bracket);
    for(int j=0;j<index;j++) printf("%s\n",a[j]);

    // Check missing bracket
    if(l_bracket != r_bracket){ 
        printf( "Missing bracket! \n" );
        exit( 0 );
    }
    
}


int main( ){
    read_file();

    return 0;
}