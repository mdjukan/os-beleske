#include <stdio.h>

extern int n;

void print(int x) {
    for (int i=0; i<n; i++) {
        printf("%d\n", x);
    }
}
