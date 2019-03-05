#include <stdlib.h>
#include <stdio.h>

int main (void) {
    int n;
    scanf("%d", &n);
    int a[100][2];
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i][0], &a[i][1]);
    }
    int count;
    scanf("%d", &count);
    unsigned int seed;
    scanf("%u", &seed);

    srand(seed);
    for (int i = 0; i < count; ++i) {

        double cur = (double)rand() / (1.0 + RAND_MAX) * 100;
        
        int j = 0, weight = 0;
        while (j < n && weight <= cur) {
            weight += a[j][1];
            j++;
        }
        printf("%d\n", a[j - 1][0]);
    }
return 0;
}