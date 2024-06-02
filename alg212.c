#include <stdio.h>



long int gcd(long int a, long int b){
    long int r = a%b;
    while (r > 0){
        a = b;
        b = r;
        r = a%b;
    }
    return b;
}

int main (void){
    long int a = 2;
    long int i = 1;
    long int x = a;
    long int m = 32749;
    while (x != 1){
        if ((m % x < m / x) && gcd(i, m - 1) ==1){
            printf("%ld,\n ", x);
        }
        i++;
        x = (a * x) % m;
    }
    return 0;
}


