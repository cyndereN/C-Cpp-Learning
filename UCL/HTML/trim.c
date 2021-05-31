// Delete whitespace at the beginning and end of a string
char* trim(char *a){
	char *p1, *p2;
	p1 = a;
	p2 = a + strlen(a) - 1;
	while (p1 <= p2 && *p1 == ' '){
		p1++;
	}
	while (p2 >= p1 && *p2 == ' '){
		p2--;
	}
	*(++p2) = '\0';
	return p1;
}