// name: Anastasia Yakauleva
// email: yakauleva.a@northeastern.edu

#include <stdio.h>

/*
The d array stores the number of ways to tile a 2*N rectangle using 1*2 and 2*1 tiles
d[i] represents the number of ways to tile a 2*i  rectangle.
 */
int d[20];

long long int dp(int n) {

    // base cases
    d[0] = d[1] = 1;

    // Fill the array using the recurrence relation
    for (int i  = 2; i <=n; i++){
        d[i] = d[i - 1] + d[i - 2];
    }
    return d[n];

}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}