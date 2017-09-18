#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>
#include <math.h>

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
    
    char* eq = " 18 9 41 3.1 - * + 2e2 A 1 * - ";
    
    // char *output = (char*)malloc(10*strlen(eq) * sizeof(char));
    // char *output = (char*)malloc(200* sizeof(char));

    // char a;
    // printf("Case:\n%s\n",eq);  
    
    // Polish(eq, output);  
    
    // printf("%s\n",output);  
    double output = calc(eq);
    // printf("%f\n",output);  
    getchar();
    return 0;  
}  