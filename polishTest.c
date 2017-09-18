#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>

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
    return (*op =='p' || *op =='e' );
}

int isDigit(char *op)
{
    return (*op =='.' || *op == 'E' || isNumber( op ) || isConstantNum( op ) );
}

int isOperator(char op)                //判断输入串中的字符是不是操作符，如果是返回true  
{  
    return (op=='+' || op=='-' || op=='*' || op=='/' || op=='^' || op=='~');  
}  



// char funName[][7]={ "sqrt",     //1 A
//                     "sin",      //2 B
//                     "cos",      //3 C
//                     "tg",       //4 D
//                     "ctg",      //5 F
//                     "arcsin",   //6 G
//                     "arccos",   //7 H
//                     "arctg",    //8 I
//                     "ln",       //9 J
//                     "floor",    //10 K
//                     "ceil"      //11 L
//                 };
typedef struct
{
    char name[7];
    char sym;
} funName2Sym;
funName2Sym funName[11] = { "sin",      'A',    //1
                            "cos",      'B',    //2
                            "tg",       'C',    //3
                            "ctg",      'D',    //4
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
    for(int i=0; i<11;i++)
        if( op == strstr(op,funName[i].name))
            return i+1;
    return 0;
}

int isSymFunction(char op)
{
    for(int i=0; i<11;i++)
        if( op == funName[i].sym)
            return i+1;
    return 0;
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


int main()  
{  
    
    char* eq = "8 + 9 * ( 41 - 3.1 ) - B A 2e2 * 1";
    
    // char *output = (char*)malloc(10*strlen(eq) * sizeof(char));
    char *output = (char*)malloc(200* sizeof(char));
    
    char a;
    printf("Case:\n%s\n",eq);  
    
    Polish(eq, output);  
    
    printf("%s\n",output);  
    
    getchar();
    return 0;  
}  