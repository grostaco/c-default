#include <stdio.h>
#include "cdefarg.h"

pythonize(void, foo, ARGS(int x, int y), KWARGS(int a; int b)) {
    printf("x: %d\ny: %d\na: %d\nb: %d\n", ARG(x), ARG(y), KWARG(a), KWARG(b));
};

int main () {
    pythonic(foo, 1, 2)(.a = 1); // prints x: 1
                                 //        y: 2
                                 //        a: 1
                                 //        b: 0

    pythonic(foo, 2, 1)(.b = 1);   // prints x: 2
                                 //        y: 1
                                 //        a: 0
                                 //        b: 1
}