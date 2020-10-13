#include <graphics.h>
#include <math.h>

double angle = 60*M_PI/180;
void koch(int x1,int y1,int x4,int y4,int lv)
{
    int x2=(2*x1+x4)/3;
    int y2=(2*y1+y4)/3;
    int x3=(2*x4+x1)/3;
    int y3=(2*y4+y1)/3;
    int xt=x2+(x3-x2)*cos(angle)+(y3-y2)*sin(angle);
    int yt=y2-(x3-x2)*sin(angle)+(y3-y2)*cos(angle);
    if (lv > 0)
    {
        koch(x1,y1,x2,y2,lv-1);
        koch(x2,y2,xt,yt,lv-1);
        koch(xt,yt,x3,y3,lv-1);
        koch(x3,y3,x4,y4,lv-1);
    }
    else
    {
        drawLine(x1,y1,x2,y2);
        drawLine(x2,y2,xt,yt);
        drawLine(xt,yt,x3,y3);
        drawLine(x3,y3,x4,y4);
    }
}

int main(void)
{
    int x1 = 100, y1 = 100, x4 = 200, y4 = 100, level = 3;
    int xb=x1+(x4-x1)*cos(angle)+(y4-y1)*sin(angle);
    int yb=y1-(x4-x1)*sin(angle)+(y4-y1)*cos(angle);
    koch(x4,y4,x1,y1,level);
    koch(x1,y1,xb,yb,level);
    koch(xb,yb,x4,y4,level);
    return 0;
}
