#include <stdio.h>
#include <math.h>
#include "graphics.h"
#define PI 3.14159265

int main(void) {
    setWindowSize(500, 500);
    drawLine(0, 250, 500, 250);
    drawLine(250, 0, 250, 500);
    drawString("0", 250, 250);
    drawString("-90", 160, 250);
    drawString("-180", 70, 250);
    drawString("90", 340, 250);
    drawString("180", 430, 250);
    drawString("1.0",250,150);
    drawString("2.0",250,50);
    drawString("-1.0",250,350);
    drawString("-2.0",250,450);
    double x = -360;
    double y;
    double c;
    double t;
    while (x <= 360) {
        y = sin(x*PI/180);
        c = cos(x*PI/180);
        t = tan(x*PI/180);
        setColour(red);
        fillRect(x+250,100*y+250,1,1);
        setColour(blue);
        fillRect(x+250,100*c+250,1,1);
        setColour(yellow);
        fillRect(x+250,100*t+250,1,1);
        x=x+0.001;
    }
}
