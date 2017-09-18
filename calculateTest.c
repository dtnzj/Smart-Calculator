#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int isFunction(char* op);
int isSymFunction(char op);

//判断运算符级别函数；其中* /的级别为2，+ -的级别为1；  
// 此处如果返回0 应当报错
int priority(char op)               
{  
    if (op=='+' || op=='-')  
        return 1;  
    if (op=='*' || op=='/')  
        return 2;  
    if (op == '^')
		return 3;
    if (isSymFunction(op))
        return 4;
    if (op == '~')
		return 5;
    else  
        return 0;  
}  

int isNumber(char *op)
{
    return (*op >='0' && *op<='9');
}

//这个函数有个bug，如果p 后面跟的不是i 就会出问题
int isConstantNum(char *op)
{
    return (((*op =='p' || *op =='P') && (*(op+1) =='i' || *(op+1) =='I')) 
            || *op =='e' );
}

int isDigit(char *op)
{
    return (*op =='.' || *op == 'E' || isNumber( op ) || isConstantNum( op ) );
}

int isOperator(char op)                //判断输入串中的字符是不是操作符，如果是返回true  
{  
    return (op=='+' || op=='-' || op=='*' || op=='/' || op=='^' || op=='~');  
}  

typedef struct
{
    char name[7];
    char sym;
} funName2Sym;
#define FUNMAX 13
funName2Sym funName[FUNMAX] = {   "sin",      'A',    //1
                            "cos",      'B',    //2
                            "tg",       'C',    //3
                            "tan",       'C',    //3
                            "ctg",      'D',    //4
                            "ctan",      'D',    //4
                            "arcsin",   'F',    //5
                            "arccos",   'G',    //6
                            "arctg",    'H',    //7
                            "sqrt",     'I',    //8
                            "ln",       'J',    //9
                            "floor",    'K',    //10
                            "ceil",     'L'     //11
};
                
int isFunction(char* op)
{
    for(int i=0; i<FUNMAX;i++)
        if( op == strstr(op,funName[i].name))
            return i+1;
    return 0;
}

int isSymFunction(char op)
{
    for(int i=0; i<FUNMAX;i++)
        if( op == funName[i].sym)
            return i+1;
    return 0;
}


char *strlwr(char *str)
{
    char *orign =str;
    for (; *str!='\0'; str++,orign++)
        *orign = tolower(*str);
    return orign;
}
// 将字符串中的数学函数转换为对应的字母代号
void fun2sym(char *expr)
{
    int tmp ;
    int i;
    strlwr(expr);  // 将字符串中所有字母转换为小写字母
    while (*expr)
    {
        tmp = isFunction(expr)-1;
        // 这个写法有点儿逆天，但是暂时没找到更好的优化方案
        if(tmp>-1) //if the first several alphabet consist of the function name
        {
            // replace it with its sym 
            *expr = funName[tmp].sym;
            for( i =strlen(funName[tmp].name); i>1; i--)
                *(++expr) = ' ';
        }
        else
        {
            // error;
        }
        ++expr;
    }
}

double OP(double op1,double op2,char op)  
{  
    double res = 0;  
    
    switch(op)
    {
        case '+': res = op1 + op2; break;
        case '-': res = op1 - op2; break;
        case '*': res = op1 * op2; break;
        case '/': res = op1 / op2; break;
        case '^': res =   pow(op1, op2); break;
        case 'A': res =   sin(op2); break;
        case 'B': res =   cos(op2); break;
        case 'C': res =   tan(op2); break;
        case 'D': res = 1/tan(op2); break;
        case 'F': res =  asin(op2); break;
        case 'G': res =  acos(op2); break;
        case 'H': res =  atan(op2); break;
        case 'I': res =  sqrt(op2); break;
        case 'J': res =   log(op2); break;
        case 'K': res = floor(op2); break;
        case 'L': res =  ceil(op2); break;
        
    }
    return res;  
}  
  
// 函数功能：　	将常规中缀表达式转换为逆波兰（后缀）表达式
// 输入参数：	s 	包含中缀表达式的字符串,其中所有函数使用 funName 中对应的大写字母表示，且不含有任何其他字母。
// 输出参数：	output	包含逆波兰表达式的字符串,各元素间以空格作为间隔符。
void Polish(char *s, char *output)          //将一个中缀串转换为后缀串
{  
    unsigned int outLen = 0;  
    unsigned int top;           //stack count
    char *stack = (char*)malloc( strlen(s) * sizeof(char));
    int i;
    fun2sym(s);
    memset(output,'\0',sizeof output);  //输出串  
    while(*s != '\0')               //1）  
    {  
        if (isDigit(s))              
        {
            output[outLen++] = *s;        //3）假如是操作数，把它添加到输出串中。  
            while( *(s+1) !='\0' && isDigit( s +1 ))
            {  
                output[outLen++] = *( s+1 );  
                ++s;  
            }  
            output[outLen++] = ' ';     //空格隔开  
        }
        if (*s=='(' || isSymFunction(*s))                  //4）假如是闭括号，将它压栈。  
        {  
            ++top;  
            stack[top] = *s;  
        }  
        while (isOperator(*s) )        //5)如果是运算符，执行算法对应操作；  
        {  
            if (top==0 || stack[top]=='(' || priority(*s) > priority( *(stack+top))) //空栈||或者栈顶为)||新来的元素优先级更高  
            {  
                ++top;  
                stack[top] = *s;  
                break;  
            }  
            else  
            {  
                output[outLen++] = stack[top];  
                output[outLen++] = ' ';  
                --top;  
            }  
        }  
        if (*s==')')                  //6）假如是开括号，栈中运算符逐个出栈并输出，直到遇到闭括号。闭括号出栈并丢弃。  
        {  
            while (stack[top]!='(')  
            {  
                output[outLen++] = stack[top];  
                output[outLen++] = ' ';  
                --top;  
            }  
            --top;  // 此时stack[top]==')',跳过)  
        }
        s ++;  
        //7）假如输入还未完毕，跳转到步骤2。  
    }  
    while (top!=0)                      //8）假如输入完毕，栈中剩余的所有操作符出栈并加到输出串中。  
    {  
        output[outLen++] = stack[top];  
        output[outLen++] = ' ';  
        --top;  
    }  
}  


double calc(char *s)                //波兰式需要用两个栈，逆波兰式只需要一个栈  
{  
    char* dst = (char*)malloc( 20 * sizeof(char));  
    double* cSt1 = (double*)malloc( strlen(s) * sizeof(double));   
    unsigned int top1=0;  
    while ( *s )  
    {  
        printf( "\ns = %s ", s);
        if (*s != ' ')  
        {  
            sscanf(s,"%s",dst);  
            // printf("\n, %d ",dst,isDigit(dst));
            if (isDigit(dst))  
            {  
                ++top1;  
                cSt1[top1] = atof(dst);     //进栈  
            }  
            else if(isOperator(*dst))
            {  
                
                printf("\n %f %c %f=",cSt1[top1-1], dst[0], cSt1[top1]);
                cSt1[top1-1] = OP( cSt1[top1-1], cSt1[top1], dst[0]); 
                printf("%f",cSt1[top1-1]); 
                --top1;     //操作数栈：出栈俩，进栈一 
            }
            else if(isSymFunction(*dst))
            {
                printf("\n %c %f=", dst[0], cSt1[top1]);
                cSt1[top1] = OP( 0, cSt1[top1], dst[0]); 
                printf("%f",cSt1[top1]); 
            }
            while (*s && *s != ' ')  
            {
                // printf("p = %p\n",s);
                ++s;
            }  
        }
        ++s;  
    }  
    return cSt1[1];  
}  


int main()  
{  
    
    // char* eq = " 18 9 41 3.1 - * + 2e2 A 1 * - ";
    char eq[] = "8 + 9 * ( 41 - 3.1 ) - sInFloorTan 2e2 * 1 + 2^3";
    double result;
    char *output = (char*)malloc(2*strlen(eq) * sizeof(char));
    // char *output = (char*)malloc(200* sizeof(char));

    printf("\nCase:\n%s\n",eq);  
    Polish(eq, output);  
    
    printf("\noutput =%s\n",output);  
    result = calc(output);
    printf("\nresult =%f",result);  
    getchar();
    return 0;  
}  