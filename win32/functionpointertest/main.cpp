
#include <stdio.h>
void my_int_func(int x ){
	printf("%d\n",x);
}

int main(){
	void (*foo)(int);
	foo= &my_int_func;
	
	// possible
	foo( 2 );
	// same behavior
	(*foo)(2);
}

