#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Include local header files

// TODO: Use all unused parameters and remove this temporary definition
// Helps eliminating warning C4100: 'error': unreferenced formal parameter
#define UNUSED_PARAMETER(name) (void)name

/***********************************LOG*************************************/
//date: 17-09-16
//advises about Errors: 
//1.创建以枚举数组为基础的全局变量，设置当前状态标识符（全局变量，默认参数为正常），
//  在遇到需要报错的情况下调用该状态标识符，按照具体情况对标识符所对应的错误状态进行
//  赋值。
//2.完成上述操作后调用报错函数，参数为该状态标识符。在报错函数中，按照需要使用switch
//  语句进行报错，并讨论在退出程序时，将状态标识符更改为默认参数——正常。
//3.尽量在各个模块执行循环操作开始时，先进行查错
//4.此操作目的：将报错函数尽可能提高其独立性，通过使用全局变量的状态标识符，减少在函数内复杂报错结构。
//
//advises about ReadLine & main 
//1.尽可能在程序设计初期明确需要在主函数体内创建和传递的各个参数，以减少后续程序复杂度为目的。
//2.所创建的参数拥有的具体性质：
//  a.需要重复引用的指针变量
//	b.对程序计算需要的计数器
//	c.
//
//advises about enum 
//1.确定需要枚举结构的变量类型，具体参照其他例程具有的错误类型；
//2.包括：报错需要的对应错误的枚举类型，表达错误信息的并需要打印出来的枚举或结构体类型；
//3.具有上述功能的函数或变量类型：error_t，char const* GetErrorString(error_t error)；
//
//Questions：
//1.讨论是否需要增加一个打印函数，逐行打印需要打印的信息，传递参数为，
//	需要打印的类型（正常或需要打印错误的类型）,但是使用状态标识符不需要作为参数传递；
//	需要打印的字符串，可能是表达式，或者需要打印的错误信息；
//2.讨论是将状态参数的值（表示错误提示或其他状态），通过枚举还是宏定义的方式表示，是否可以
//	将所有状态统一放入一个枚举结构里，或者简单的状态使用整型变量，用布尔表示法判断。
//3.需要优先设计状态表示的方法，以及是否统一表示和是否只使用一种枚举类型表达所有状态（包括错误提示）
/******************************END******************************************/


/******************Private parameters**************************************/
#define TRUE 0
#define FALSE 1
/*************************END*********************************************/


//////////////////////////////////////////////////////////////////////////////
// Dummy calc module

// TODO: Move to a separate module 'calc'
typedef enum
{
  ERR_OK,
  ERR_NOT_ENOUGH_MEMORY,
  // TODO: Add your own error codes
} error_t;
error_t error = ERR_OK;

// TODO: Move to a separate module 'calc'
char const* GetErrorString(error_t error)
{
  // TODO: Find the corresponding error description
  UNUSED_PARAMETER(error);
  return "";
}

// TODO: Move to a separate module 'calc'
double Calculate(char const* expression, error_t* error)
{
  double result;

  // TODO: Replace with a computational algorithm subdivided into modules/functions
  UNUSED_PARAMETER(expression);
  result = 4.0;
  if (error != NULL)
    *error = ERR_OK;

  return result;
}

//////////////////////////////////////////////////////////////////////////////
// UI functions

//parameters: FILE, sizeofline
//function: To read the line of messages from the stdin
//return： The first address of the messages which be read
//the types of errors are included at here: 
//
//需要决策的设计：
//在这里需要对内存不足，内存溢出，行结尾，文件结尾，以及正常状态进行判断，如前述，是否使用同一标识符表示？
//一种方法是设计一个状态变量类型，在需要用到的函数体内创建相应的状态变量，否则单一使用一个全局变量来进行判断，其数量不足以满足判断需求。
//为了解决上述问题，是否取消全局变量而只使用相应状态变量类型来创建需要的变量。
//该功能实现并不困难，关键先统一表示法。需要自行设计。
char* ReadLine(FILE* in, int sizeofline)
{
  char* line = NULL;
  char c;
/*
  do{
	c = fgetc(in);
	if(c == EOF)
  }while(c != '\n');
*/
  UNUSED_PARAMETER(in);
  return line;
}

//parameters: string
//function: whether need to calculate
//return： True or False
//the types of errors are included at here: 
//
//在完成读功能后，参考设计需求和其他程序进行设计
//15行以内解决
//需要判断内容：是否含有非法参数，括号数量是否正好，是否以算术符结尾，
//这里需要讨论能否对sin cos等功能进行判断以及判断方法
int NeedCalculate(char const* line)
{
  // TODO: Determine if the line contains an expression
  UNUSED_PARAMETER(line);
  return 1;
}

error_t ReportError(error_t error)
{
  printf("ERROR: %s\n", GetErrorString(error));
  return error;
}


void Polish(char *s,int len)            //将一个中缀串转换为前缀串，  
{  
	  
	memset(output,'\0',sizeof output);  //输出串  
    outLen = 0;  
    for (int i=len-1; i >= 0; --i)       //1）求输入串的逆序。  
    {  
        if (isdigit(s[i]))              //经验见:http://blog.csdn.net/linraise/article/details/18566319#comments  
        {  
            output[outLen++] = s[i];    //3）假如是操作数，把它添加到输出串中。  
            while (i-1 >= 0 && isdigit(s[i-1]))  
            {  
                output[outLen++] = s[i-1];  
                --i;  
            }  
            output[outLen++] = ' ';     //空格隔开  
        }  
        if (s[i]==')')                  //4）假如是闭括号，将它压栈。  
        {  
            ++top;  
            stack[top] = s[i];  
        }  
        while (isOperator(s[i]))        //5)如果是运算符，执行算法对应操作；  
        {                                               //>=很重要  
            if (top==0 || stack[top]==')' || priority(s[i]) >= priority(stack[top])) //空栈||或者栈顶为)||新来的元素优先级更高  
            {  
                ++top;  
                stack[top] = s[i];  
                break;  
            }  
            else  
            {  
                output[outLen++] = stack[top];  
                output[outLen++] = ' ';  
                --top;  
            }  
        }  
        if (s[i]=='(')                  //6）假如是开括号，栈中运算符逐个出栈并输出，直到遇到闭括号。闭括号出栈并丢弃。  
        {  
            while (stack[top]!=')')  
            {  
                output[outLen++] = stack[top];  
                output[outLen++] = ' ';  
                --top;  
            }  
            --top;  // 此时stack[top]==')',跳过)  
        }  
        //7）假如输入还未完毕，跳转到步骤2。  
    }  
    while (top!=0)                      //8）假如输入完毕，栈中剩余的所有操作符出栈并加到输出串中。  
    {  
        output[outLen++] = stack[top];  
        output[outLen++] = ' ';  
        --top;  
    }  
}  


void ProcessLine(char const* line)
{
  error_t lastError = ERR_OK;
  if (!NeedCalculate(line))
  {
    puts(line);
    return;
  }

  printf("%s == ", line);
  double result = Calculate(line, &lastError);
  if (lastError == ERR_OK)
    printf("%lg\n", result);
  else
    ReportError(lastError);
}

int main(int argc, char const* argv[])
{
  FILE* in = stdin;
  char* line = NULL;

//Private part
  int sizeofline = 0;



// Choose an input source
  if (argc > 1 && (in = fopen(argv[1], "r")) == NULL)
  {
    printf("ERROR: Cannot open file '%s'", argv[1]);
    return -1;
  }

 // Process the data line by line
  while ((line = ReadLine(in, sizeofline)) != NULL)
  {
    ProcessLine(line);
    free(line);
  }

 // Clean up
  if (in != stdin)
    fclose(in);
  return 0;
}
