#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_FILE "file.html" // Change filename here

char a[][30] = {}; // Array to store tags
int size = 0; // Number of tags
int top = -1; // Index of top of the tag stack

int is_valid_tag_name(char* str){
    int flag = 0;
    if ( strcmp(str, "html")==0 || strcmp(str, "/html")==0 || strcmp(str, "br")==0 || strcmp(str, "hr")==0 \
            || strcmp(str, "body")==0 || strcmp(str, "/body")==0 || strcmp(str, "title")==0 || strcmp(str, "/title")==0 \
        || strcmp(str, "h1")==0 || strcmp(str, "/h1")==0 || strcmp(str, "h2")==0 || strcmp(str, "/h2")==0 \
            || strcmp(str, "h3")==0 || strcmp(str, "/h3")==0 || strcmp(str, "p")==0 || strcmp(str, "/p")==0 \
        || strcmp(str, "ul")==0 || strcmp(str, "/ul")==0 || strcmp(str, "li")==0 || strcmp(str, "/li")==0 \
            || strcmp(str, "a")==0 || strcmp(str, "/a")==0 || strcmp(str, "div")==0 || strcmp(str, "/div")==0 \
        || strncmp(str, "a ", 2)==0 || strncmp(str, "div ", 4)==0 || strcmp(str, "head")==0 || strcmp(str, "/head")==0\
            || strncmp(str, "html ", 5)==0 || strncmp(str, "head ", 5)==0 || strncmp(str, "body ", 5)==0 || strncmp(str, "h1 ", 3)==0\
        || strncmp(str, "h2 ", 3)==0 || strncmp(str, "h3 ", 3)==00 || strncmp(str, "br ", 3)==0 || strncmp(str, "hr ", 3)==0\
            || strncmp(str, "ul ", 3)==0 || strncmp(str, "li ", 3)==0 || strncmp(str, "title ", 6)==0){
        flag = 1;
    }
    return flag;
}

// Read file, check for validity of tag name and store the tags in an array
void read_file(){
    int index = 1;
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
            while ( c != '>' ){
                if (c == '<') { 
                    printf( "Missing bracket! \n" );
                    exit( 0 );
                }
                b[i] = c;
                i++;
                c = fgetc(fp);
            }
            b[i] = '\0';

            if(is_valid_tag_name(b)){
                strcpy(a[index],b);
                index++; 
            } else {
                printf( "Invalid tag name! \n" );
                exit( 0 );
            }
            
        }
        if ( c == '>')  r_bracket++;
    }

    fclose(fp);

    // Check missing bracket
    if(l_bracket != r_bracket){ 
        printf( "Missing bracket! \n" );
        exit( 0 );
    }
    
    size = index-1;
}

void check_html_tag(){
    if (strcmp(a[1], "html")!=0 || strcmp(a[size],"/html")!=0) {
        printf( "No <html> and </html> tags around the entire document. \n" );
        exit( 0 );
    }
}

void check_head_body(){
    int is_valid = 1;
    int head_flag = 0;
    int head_index = 0;
    int closing_head_flag = 0;
    int closing_head_index = 0;
    int body_flag = 0;
    int body_index = 0;
    int closing_body_flag = 0;
    int closing_body_index = 0;

    for ( int i=1; i<=size; i++ ){
        // Multiple head tag
        if (strcmp(a[i], "head")==0 && head_flag==0){
            head_flag = 1;
            head_index = i;
        } else if (strcmp(a[i], "head")==0 && head_flag==1){
            is_valid = 0;
        } 

        // Multiple closing head tag
        if (strcmp(a[i], "/head")==0 && closing_head_flag==0){
            closing_head_flag = 1;
            closing_head_index = i;
        } else if (strcmp(a[i], "/head")==0 && closing_head_flag==1){
            is_valid = 0;
        } 

        // Multiple body tag
        if (strcmp(a[i], "body")==0 && body_flag==0){
            body_flag = 1;
            body_index = i;
        } else if (strcmp(a[i], "body")==0 && body_flag==1){
            is_valid = 0;
        } 

        // Multiple closing body tag
        if (strcmp(a[i], "/body")==0 && closing_body_flag==0){
            closing_body_flag = 1;
            closing_body_index = i;
        } else if (strcmp(a[i], "/body")==0 && closing_body_flag==1){
            is_valid = 0;
        } 
    }

    // No head or body part or at wrong poition
    if ( head_index!=2 || closing_head_index==0 || body_index==0 || closing_body_index!=size-1 )  is_valid = 0;

    // Head not followed by body
    if ( closing_head_index + 1 != body_index)  is_valid = 0;

    if (is_valid == 0){
        printf( "No single <head>…</head> section followed by a single <body>…</body> section in that order. \n" );
        exit( 0 );
    }
}

void push(char* a, int elem){
    a[++top]=elem;
}

void pop(char* a){
    if (top==-1) {
        return ;
    }
    top--;
}

char visit(char* a){
    if (top!=-1) {
        return a[top];
    }else{
        return ' ';
    }
}

void check_closing_tag(){
    int open_tag_num = 0;
    int closing_tag_num = 0;
    for ( int i=1 ; i<= size ; i++){
        if(a[i][0]=='/')  closing_tag_num += 1;
        else if(strcmp(a[i], "br")!=0 && strcmp(a[i], "hr")!=0)  open_tag_num += 1;
    }

    if (closing_tag_num > open_tag_num)  { printf( "Missing corresponding openning tag. \n" );  exit( 0 ); }
    else if (closing_tag_num < open_tag_num)  { printf( "Missing corresponding closing tag. \n" );   exit( 0 ); }
}

void check_proper_nesting(){
    char t[size]; // Stack to store tags to match.
    for ( int i=1; i<=size ; i++ ){
        // Different char represents different tag: 
        // {html, head, body, title, h1, h2, h3, p, ul, li, a, div,} 
        // {m, h, b, t, 1, 2, 3, p, u, l, a, d,} (br and hr have no closing tag)
        if (strcmp(a[i], "html")==0)  push(t, 'm');
        else if (strcmp(a[i], "head")==0)  push(t, 'h');
        else if (strcmp(a[i], "body")==0)  push(t, 'b');
        else if (strcmp(a[i], "title")==0)  push(t, 't');
        else if (strcmp(a[i], "h1")==0)  push(t, '1');
        else if (strcmp(a[i], "h2")==0)  push(t, '2');
        else if (strcmp(a[i], "h3")==0)  push(t, '3');
        else if (strcmp(a[i], "p")==0)  push(t, 'p');
        else if (strcmp(a[i], "ul")==0)  push(t, 'u');
        else if (strcmp(a[i], "li")==0)  push(t, 'l');
        else if (strncmp(a[i], "a", 1)==0)  push(t, 'a');
        else if (strncmp(a[i], "div", 3)==0)  push(t, 'd');
        else if (strcmp(a[i], "/html")==0) {
            if (visit(t)=='m')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/head")==0) {
            if (visit(t)=='h')  pop(t); 
            else break;
        }else if (strcmp(a[i], "/body")==0) {
            if (visit(t)=='b')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/title")==0) {
            if (visit(t)=='t')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/h1")==0) {
            if (visit(t)=='1')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/h2")==0) {
            if (visit(t)=='2')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/h3")==0) {
            if (visit(t)=='3')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/p")==0) {
            if (visit(t)=='p')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/ul")==0) {
            if (visit(t)=='u')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/li")==0) {
            if (visit(t)=='l')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/a")==0) {
            if (visit(t)=='a')  pop(t); 
            else break;
        } else if (strcmp(a[i], "/div")==0) {
            if (visit(t)=='d')  pop(t); 
            else break;
        } else continue;
    }

    // If all matches, stack is empty otherwise not
    if(top != -1) {
        printf( "Not nested properly.\n" ); 
        exit( 0 );
    }
}

void check_correct_nesting(){
    int is_valid = 1;
    int p_flag = 0;     // In <p> tag
    int body_flag = 0;  // In <body> tag

    // Check p and div are nested 
    for ( int i=1; i<=size ; i++ ){
        if (strcmp(a[i], "p")==0 && p_flag==0){
            p_flag = 1;
        } else if ((strcmp(a[i], "p")==0 && p_flag==1) || (strncmp(a[i], "div", 3)==0 && p_flag==1 )){
            is_valid = 0;
        } 
        if (strcmp(a[i], "/p")==0 && p_flag==1){
            p_flag = 0;
        } 

        if (strcmp(a[i], "body")==0 && body_flag==0){
            body_flag = 1;
        } else if ((strcmp(a[i], "title")==0 && body_flag==1)){
            is_valid = 0;
        } 
        if (strcmp(a[i], "/body")==0 && body_flag==1){
            body_flag = 0;
        }
    }
    if (is_valid == 0){
        printf( "(<p>, <div> or <title>) Not nested correctly. \n" );
        exit( 0 );
    }
}

int main( ){
    read_file();
    check_html_tag();
    check_head_body();
    check_closing_tag();
    check_proper_nesting();
    check_correct_nesting();
    printf( "HTML file is valid.\n" );
    return 0;
}