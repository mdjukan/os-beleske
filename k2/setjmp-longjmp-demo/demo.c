#include <setjmp.h>
#include <stdio.h>

jmp_buf context;

void f(int *a, int n) {
    if (n==0) {
        longjmp(context, 1);
    }

    if (a[0]<0) {
        longjmp(context, 2);
    }

    f(++a, --n);
}

int main() {
    int a[] = {1, 2, 3, 4, -10, 5};
    int n = sizeof(a)/sizeof(int);

    int val = setjmp(context);

    if (val==0) {
        f(a, n);
    } else if (val==1) {
        printf("no negative values\n");
    } else if (val==2) {
        printf("found negative value\n");
    }
}
