#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
using namespace std;

#define INT(n) int n;scanf("%d", &n);
#define FOR(i, n) for(int i = 0; i < n; i ++)

int main() {
    INT(t)
    FOR(i, t) {
        INT(n)
        int sum = 0;
        int zero_count = 0;
        FOR(i, n) {
            INT(a);
            if (a == 0) {
                zero_count ++;
            }
            sum += a;
        }
        int result = zero_count;
        sum += zero_count;
        if (sum == 0) {
            result ++;
        }
        printf("%d\n", result);
    }
    return 0;
}