#include <assert.h>
#include "str.h"
#include "test_str.h"

void test_strcpy(){
	
	char s1[6] = "xxxxx";
	char s2[1] = "";
	my_strcpy(s1,s2);
	assert(s1[0] == '\0');
	char x1 [11] = "";
	char *p;
	char x2 [10] = "xxxxxxxxx";
	my_strcpy(x1,x2);
	p = x1;
	while (*p != '\0'){
		assert(*p == 'x');
		p++;
	}
}
void test_strcat () {
	char s1[7] = "xxx";
	char s2[4] = "Yyy";
	my_strcat(s1,s2);
	char *p;
	p = s1; 
	while (*p == 'x'){
		p++;
	}
	assert(*p=='Y');
	char x1[4] = "";
	char x2[4] = "xxx";
	my_strcat(x1,x2);
	p = x1;
	while (*p!='\0'){
		assert(*p =='x');
		p++;
	}
}
void test_strlen() {
	char s1[1]="";
	int x = my_strlen(s1);
	assert (x == 0);
	char s2[5] = "dead";
	x = my_strlen(s2);
	assert( x == 4);
}

void test_strcmp() {
	char s1[4] = "Lab";
	char s2[5] = "Lab2";
	int x = my_strcmp(s1,s2);
	assert (x== -1);
	char s3[4] = "HSE";
	char s4[4] = "HSE";
	int y = my_strcmp(s3,s4);
	assert(y==0);
}

	
