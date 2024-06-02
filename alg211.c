#include <stdio.h>

int main (void){

long int a = 3;

long int m = 32749;
long int p = 1;
long int x = a;
int con = 1;

while (con && a < m){
	p = 1;
	x = a;

	while (x != 1&& p < m){

		p++;
		x = (a * x) %m;
		if (p%10 == 0){
			//printf("p = %ld, x = %ld\n", p, x);
		}	
	}

	if(p == m-1){
		printf("%li is full-period multiplier\n", a);
		con = 0;
	}else{
		printf("%li is  non-full-period multiplier\n", a);
	}
	a++;
}
return 0;
}
