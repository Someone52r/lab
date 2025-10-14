#include <stdio.h>
#include <math.h>
float U;
int main() {
    for (float x=1; x<=2; x=x+0.3) {
        for (float y=2; y<=2.5; y=y+0.5) {
            if (x/(y*y)<1) {
                U=fmax(cos(pow(x,3)-sqrt(y)),cbrt(x*pow(y,2)));
                printf ("%f\n", U);
            } else {
                U=log(pow(y,2)-x);
                printf ("%f\n", U);
            }
        }
    }
    return 0;
}
