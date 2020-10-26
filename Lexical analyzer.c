#include<string.h>
#include<ctype.h>
#include<stdio.h>
void main()
{

FILE *f1;
char c,str[10];
int line=1,n=0,i=0;

printf("Enter the code\n");
f1=fopen("file.txt","w");
while((c=getchar())!=EOF)
{
    putc(c,f1);
}
fclose(f1);

f1=fopen("file.txt","r");
while((c=getc(f1))!=EOF) 
{
    if(isdigit(c))  
    {
    	n=c-48;
		c=getc(f1);
		while(isdigit(c))
		{
		n=n*10+(c-48);
		c=getc(f1);
		}
        printf("%d is a number\n",n);
    }
    else if(isalpha(c)) 
    {
        str[i++]=c;
        c=getc(f1);
        while(isdigit(c)||isalpha(c)||c=='_'||c=='$')
        {
            str[i++]=c;
            c=getc(f1);
        }
        str[i++]='\0';
        if(strcmp("for",str)==0||strcmp("while",str)==0||strcmp("do",str)==0||
        strcmp("int",str)==0||strcmp("float",str)==0||strcmp("char",str)==0||
        strcmp("double",str)==0||strcmp("static",str)==0||
        strcmp("switch",str)==0||strcmp("case",str)==0||strcmp("printf",str)==0)
        {
            printf("%s is a keyword\n",str);
        }           
        else
        {
            printf("%s is an identifier\n",str);
        }           
        i=0;
        line++;
    }
    else if(c==' ')
    {
        printf("\n");
    }       
    else if(c=='\\')
    {
    	c=getc(f1);
    	if(c=='n' || c=='t')
		{
    		printf("\n");	
		} 		      
    } 
	else if(c=='/')
	{
		c=getc(f1);
		if(c=='/')
		{
			c=getc(f1);
	        while(isdigit(c)||isalpha(c)||c=='_'||c=='$')
	        {
	            str[i++]=c;
	            c=getc(f1);
	        }
	        str[i++]='\0';
	        printf("%s is a comment\n",str);
		}
	}       
    else
    {
        printf("%c is a special symbol\n",c);
    }       
}

printf("Total number of lines: %d\n",line-1);
fclose(f1);
}
