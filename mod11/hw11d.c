// name: Anastasia Yakauleva
// email: yakauleva.a@northeastern.edu

#include <stdio.h>

/*
The d array stores the number of ways to tile a 2*N rectangle using 1*2, 2*1, and 1*1 tiles.
d[i] represents the number of ways to tile a 2*i rectangle.
*/
int d[20];

long long int dp(int n) {
    // base cases
    d[0] = 1; // one way of doing nothing
    d[1] = 2; // horizontal and vertical ways to tile a 2x1 rectangle

    for (int i = 2; i <= n; i++) {
        d[i] = 3 * d[i - 2] + 2 * d[i - 1];
        for (int j = i - 3; j >= 0; j--) {
            d[i] += 2 * d[j];
        }
    }

    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}