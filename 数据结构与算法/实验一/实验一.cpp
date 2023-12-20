//实验一 利用栈实现四则运算 
#include<iostream>
#include<string.h>
#include<cctype>
using namespace std;

#define ERROR 0
#define OK 1
//字符栈 
struct Stack
{
	char data[100];
	int top;
};
//数字栈 
struct StackNum
{
	int data[100];
	int top;
};
//初始化操作
void Init(Stack &s){
	s.top = -1;
} 
void InitNum(StackNum &s){
	s.top = -1;
}
//压栈操作
int push(Stack &s,char e){
	if(s.top==99)//栈满 
	{
		return ERROR; 
	}
	s.top++;
	s.data[s.top]=e;
	printf("此时字符栈内的元素是:"); 
	for(int i=0;i<s.top+1;i++){
		printf("%c ",s.data[i]);
	}
	printf("\n");
	return OK;
} 
int pushNum(StackNum &s,int e){
	if(s.top==99)//栈满 
	{
		return ERROR; 
	}
	s.top++;
	s.data[s.top]=e;
	printf("此时数字栈内的元素是:"); 
	for(int i=0;i<s.top+1;i++){
		printf("%d ",s.data[i]);
	}
	printf("\n");
	return OK;
}
//出栈操作
int pop(Stack &s){//返回出栈的值 
	if(s.top==-1){
		cout<<"栈空"<<endl;
		return ERROR;
	}
	s.top--;
	printf("此时字符栈内的元素是:"); 
	for(int i=0;i<s.top+1;i++){
		printf("%c ",s.data[i]);
	}
	printf("\n");
	return s.data[s.top+1];
} 
int popNum(StackNum &s){//返回出栈的值 
	if(s.top==-1){
		cout<<"栈空"<<endl;
		return ERROR;
	}
	s.top--;
	printf("此时数字栈内的元素是:"); 
	for(int i=0;i<s.top+1;i++){
		printf("%d ",s.data[i]);
	}
	printf("\n");
	return s.data[s.top+1];
}
//获得后缀表达式函数
void getSuffix(char *str,char *p){
	Stack s; //字符栈 
	int j=0; 
	Init(s);
	for(int i=0;i<strlen(str);i++){
		//遇到整数直接输出 
		while(isdigit(str[i])){
			p[j]=str[i];
			i++;
			j++;
			if(!isdigit(str[i])){
				p[j]=' ';//输出空格间隔不同整数 
				j++;
				i--;
				break;
			}			
		}
		//遇到左括号直接压栈 
		if(str[i]=='(')
		{
			push(s,str[i]);
		}
		//遇到右括号，把左括号之前的符号出栈 
		if(str[i]==')')
		{
			while(s.data[s.top]!='(')
			{
				p[j]=pop(s);//出栈，并把栈顶元素输出 
				j++; 
				p[j]=' ';
				j++;
			}
			pop(s); //再让栈顶的左括号出栈 
		}
		//遇到其它运算符，比较优先级
		//如果是加减，如果栈为空或者栈顶左括号就入栈，其他情况都出栈 
		if(str[i]=='+'||str[i]=='-'){
			while(s.top!=-1&&s.data[s.top]!='('){
				p[j]=pop(s);
				j++;
				p[j]=' ';
				j++;
			}
			push(s,str[i]);
		}
		//遇到乘和除，如果栈为空或者栈顶是左括号或者遇到加减法就入栈，否则出栈 
		if(str[i]=='*'||str[i]=='/'){
			while(s.top!=-1&&s.data[s.top]!='('&&s.data[s.top]!='+'&&s.data[s.top]!='-'){
		    	p[j]=pop(s);
				j++;
				p[j]=' ';
				j++;
			}
			push(s,str[i]);
		} 
	}
    //检查栈是否为空，将所有元素均输出
	while(s.top!=-1){
		p[j]=pop(s);
		j++;
		p[j]=' ';
		j++;
	} 
	p[j]='\0';
	j--;
}
//计算后缀表达式
int Calculate(char *str){
	StackNum s;
	int m=0,n=0;
	InitNum(s);
	for(int i=0;i<strlen(str);i++){
		//遇到整数 
		while(isdigit(str[i])){
			if(!isdigit(str[i+1])){
				m=n+str[i]-'0';
				pushNum(s,m);
				i++;
			} 
			else{
				n=n+str[i]-'0';
				n=n*10;
				i++;
			}
		}
		m=0,n=0;
		if(str[i]=='+'){
			m=popNum(s);
			n=popNum(s);
			pushNum(s,m+n);
		}
        if(str[i]=='-'){
			m=popNum(s);
			n=popNum(s);
			pushNum(s,n-m);
		}
        if(str[i]=='*'){
			m=popNum(s);
			n=popNum(s);
			pushNum(s,m*n);
		}		
        if(str[i]=='/'){
			m=popNum(s);
			n=popNum(s);
			pushNum(s,n/m);
		}			
	}
	//输出栈顶最终结果 
	m=popNum(s);
	return m;	
} 

int main()
{
    char str[100];//中缀表达式字符串 
	char p[100];//后缀表达式字符串 
	printf("请输入表达式：");
	gets(str);
	getSuffix(str,p);//获得后缀表达式 
	printf("后缀表达式为%s\n",p);
	printf("计算结果为%d",Calculate(p));
	return 0;
}
