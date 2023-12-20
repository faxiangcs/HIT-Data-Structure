//ʵ��һ ����ջʵ���������� 
#include<iostream>
#include<string.h>
#include<cctype>
using namespace std;

#define ERROR 0
#define OK 1
//�ַ�ջ 
struct Stack
{
	char data[100];
	int top;
};
//����ջ 
struct StackNum
{
	int data[100];
	int top;
};
//��ʼ������
void Init(Stack &s){
	s.top = -1;
} 
void InitNum(StackNum &s){
	s.top = -1;
}
//ѹջ����
int push(Stack &s,char e){
	if(s.top==99)//ջ�� 
	{
		return ERROR; 
	}
	s.top++;
	s.data[s.top]=e;
	printf("��ʱ�ַ�ջ�ڵ�Ԫ����:"); 
	for(int i=0;i<s.top+1;i++){
		printf("%c ",s.data[i]);
	}
	printf("\n");
	return OK;
} 
int pushNum(StackNum &s,int e){
	if(s.top==99)//ջ�� 
	{
		return ERROR; 
	}
	s.top++;
	s.data[s.top]=e;
	printf("��ʱ����ջ�ڵ�Ԫ����:"); 
	for(int i=0;i<s.top+1;i++){
		printf("%d ",s.data[i]);
	}
	printf("\n");
	return OK;
}
//��ջ����
int pop(Stack &s){//���س�ջ��ֵ 
	if(s.top==-1){
		cout<<"ջ��"<<endl;
		return ERROR;
	}
	s.top--;
	printf("��ʱ�ַ�ջ�ڵ�Ԫ����:"); 
	for(int i=0;i<s.top+1;i++){
		printf("%c ",s.data[i]);
	}
	printf("\n");
	return s.data[s.top+1];
} 
int popNum(StackNum &s){//���س�ջ��ֵ 
	if(s.top==-1){
		cout<<"ջ��"<<endl;
		return ERROR;
	}
	s.top--;
	printf("��ʱ����ջ�ڵ�Ԫ����:"); 
	for(int i=0;i<s.top+1;i++){
		printf("%d ",s.data[i]);
	}
	printf("\n");
	return s.data[s.top+1];
}
//��ú�׺���ʽ����
void getSuffix(char *str,char *p){
	Stack s; //�ַ�ջ 
	int j=0; 
	Init(s);
	for(int i=0;i<strlen(str);i++){
		//��������ֱ����� 
		while(isdigit(str[i])){
			p[j]=str[i];
			i++;
			j++;
			if(!isdigit(str[i])){
				p[j]=' ';//����ո�����ͬ���� 
				j++;
				i--;
				break;
			}			
		}
		//����������ֱ��ѹջ 
		if(str[i]=='(')
		{
			push(s,str[i]);
		}
		//���������ţ���������֮ǰ�ķ��ų�ջ 
		if(str[i]==')')
		{
			while(s.data[s.top]!='(')
			{
				p[j]=pop(s);//��ջ������ջ��Ԫ����� 
				j++; 
				p[j]=' ';
				j++;
			}
			pop(s); //����ջ���������ų�ջ 
		}
		//����������������Ƚ����ȼ�
		//����ǼӼ������ջΪ�ջ���ջ�������ž���ջ�������������ջ 
		if(str[i]=='+'||str[i]=='-'){
			while(s.top!=-1&&s.data[s.top]!='('){
				p[j]=pop(s);
				j++;
				p[j]=' ';
				j++;
			}
			push(s,str[i]);
		}
		//�����˺ͳ������ջΪ�ջ���ջ���������Ż��������Ӽ�������ջ�������ջ 
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
    //���ջ�Ƿ�Ϊ�գ�������Ԫ�ؾ����
	while(s.top!=-1){
		p[j]=pop(s);
		j++;
		p[j]=' ';
		j++;
	} 
	p[j]='\0';
	j--;
}
//�����׺���ʽ
int Calculate(char *str){
	StackNum s;
	int m=0,n=0;
	InitNum(s);
	for(int i=0;i<strlen(str);i++){
		//�������� 
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
	//���ջ�����ս�� 
	m=popNum(s);
	return m;	
} 

int main()
{
    char str[100];//��׺���ʽ�ַ��� 
	char p[100];//��׺���ʽ�ַ��� 
	printf("��������ʽ��");
	gets(str);
	getSuffix(str,p);//��ú�׺���ʽ 
	printf("��׺���ʽΪ%s\n",p);
	printf("������Ϊ%d",Calculate(p));
	return 0;
}
