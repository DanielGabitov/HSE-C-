#include "str.h"
#include <stddef.h>

char* my_strcpy (char * restrict s1, const char * restrict s2) {
	char* p = s1;
	while (*s2 != '\0') {
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return p;
}

int my_strlen (const char* s) {
	int n = 0;
	while (*s){
		n++;
		s++;
	}
	return n;
}
int my_strcmp (const char* s1, const char* s2) {
	while( *s1 != '\0' && *s2 != '\0' && (*s1 == *s2)){
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return 0;
	else if (*s1 > *s2)
		return 1;
	else return -1;
}
char* my_strcat(char* restrict s1, const char* restrict s2) {
	char* p = s1;
	s1+=my_strlen(p);
	my_strcpy(s1,s2);
	return p;	
}
