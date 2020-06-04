#include<stdio.h>
#include<string.h>
void main (int argc, char* argv[]) 
{
  if(argc<=1) 
  {
    printf("请输入密码!\n");
    scanf("%s",&argc);
    return;
  }
  else 
  {
    const char * password = argv[1];
    if(0 == strcmp(password , "123"))
    {
      printf("开始执行\n");// 正确
    }
    else 
    {
       printf("您的权限无法运行此程序\n");// 错误
    }
  }
}
