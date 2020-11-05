#include <stdio.h>
#include <string.h>
void Scanner(char c[], int len)//定义一个字串，length是其长度不应大于c的容量，但实际能承载信息的字是length-1个
{
	for (int n = 0; n < len - 1; n++)
	{
		c[n] = getchar();
		if (c[n] == '\n')
		{
			c[n] = '\0';
			goto Break;//要不然就会强制用户多打一堆没用的字
		}
	}
	while (getchar() != '\n');//把多余的字符全抓起来
Break:;
	c[len - 1] = '\0';//保险
}
int IntScanner(int def)//定义一个字串，length是其长度不应大于c的容量，但实际能承载信息的字是length-1个
{
	int i = 0;
	bool start=true;
	bool sign = false;
	for (char c; c = getchar();)
	{
		if (c == '\n')
		{
			goto Break;
		}
		if ((c >= '0' && c <= '9'))
		{
			i = i * 10 + (c - '0');
		}
		else if (c == '-' && start) 
		{
			sign = true;
		}
		else
		{
			i = def;
			break;
		}
		start = false;
	}
	while (getchar() != '\n');//把多余的字符全抓起来
Break:;
	if (sign)
		i = i * -1;
	return i;
}
void Scanner1(char c[], char input[], int len)//定义一个字串，length是其长度不应大于c的容量，但实际能承载信息的字是length-1个
{
	int l = (int)strlen(input);
	for (int n = 0; n < len - 1; n++)
	{
		if (n < l)
			c[n] = input[n];
		else
			c[n] = '\0';
	}
	c[len - 1] = '\0';//保险
}