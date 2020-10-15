#include <stdio.h>
#include <math.h>
#include "graphics.h"
#define PI 3.14159265

int main(void)
{
    setWindowSize(500,500);
    double r = 0;
    double x = 0;
    double y = 0;
    double angle = 0;
    while (r <= 240 && angle<= 9*360) {
        x = x + r * cos(angle * PI / 180);
        y = y + r * sin(angle * PI / 180);
        drawRect(250+x,250+y,1,1);
        r = r + 0.01;
        angle = angle + 3;
    }
}
