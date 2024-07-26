// name: Anastasia Yakauleva
// email: yakauleva.a@northeastern.edu

#include <stdio.h>

/*
The d array stores the number of ways to tile a 3*N rectangle using 1*2 and 2*1 tiles.
d[i] represents the number of ways to tile a 3*i rectangle.
 */
int d[20];

long long int dp(int n) {
    // base cases
    d[0] = 1; // one way of doing nothing
    d[1] = 0; // No way to tile a 3x1 rectangle with 1x2 and 2x1
    d[2] = 3;
    d[3] = 0; // same as N1, there would always be 1x1 gap

    // D[i] = 3 * D[i - 2] + (2 * D[i - 4] + 2 * D[i - 6] ... 2 * D[0])
    for (int i = 4; i <= n; i+=2) {
    d[i] = 3 * d[i - 2];
    for (int j = i -4; j>= 0; j-=2){
        d[i]+= 2 * d[j];
        }
    }

    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}