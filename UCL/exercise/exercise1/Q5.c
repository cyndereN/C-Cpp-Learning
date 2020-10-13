#include "graphics.h"

int main(void)
{
    setWindowSize(500,500);
    drawLine(30,30,120,30);
    drawLine(120,30,120,80);
    drawLine(120,80,30,80);
    drawLine(30,80,30,30);
    drawRect(150,50,60,140);
    return 0;
}
