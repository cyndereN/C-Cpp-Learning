#include <math.h>
#include "graphics.h"
void drawRectangle(int,int,int,int);
void drawEquilateralTriangle(int, int, int, int);
void drawPicture();
void drawRectangle(int x, int y, int width, int height)
{
    drawLine(x, y, x + width, y);
    drawLine(x + width, y, x + width, y + height);
    drawLine(x + width, y + height, x, y + height);
    drawLine(x, y + height, x, y);
}
void drawEquilateralTriangle(int x, int y, int width, int height)
{
    drawLine(x, y, x + width, y);
    drawLine(x, y, x + (width / 2), y - height);
    drawLine(x + (width / 2), y - height, x + width, y);
}
void drawPicture()
{
    drawRectangle(150, 120, 200, 170);
    drawRectangle(230, 230, 40, 60);
    drawRectangle(170, 230, 40, 30);
    drawRectangle(290, 230, 40, 30);
    drawRectangle(170, 160, 40 , 30);
    drawRectangle(290, 160, 40 , 30);
    drawEquilateralTriangle(150, 120, 200, 70);
}
int main(void)
{
    drawPicture();
    return 0;
}