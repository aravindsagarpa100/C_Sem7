#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expression[10];
int count, flag;

struct production
{
    char variable;
    char prod[10];
};

void E();
void T();
void Tprime();
void check();
void Eprime();

void E()
{
      T();
      Eprime();
}
 
void T()
{
      check();
      Tprime();
}
 
void Tprime()
{
      if(expression[count] == '*')
      {
            count++;
            check();
            Tprime();
      }
}
 
void check()
{
      if(isalnum(expression[count]))
      {
            count++;
      }
      else if(expression[count] == '(')
      {
            count++;
            E();
            if(expression[count] == ')')
            {
                  count++;
            }
            else
            {
                  flag = 1; 
            }
      }         
      else
      {
            flag = 1;
      }
}

void Eprime()
{
      if(expression[count] == '+')
      {
            count++;
            T();
            Eprime();
      }
}

int isTerminal(char ch, char terminals[10])
{
	int  i;
    for(i = 0;i < strlen(terminals);i++)
    {
        if (terminals[i] == ch)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int numberOfproductions;
    int i, j, k;
    printf("\nEnter the algebraic expression: ");
	scanf("%s", expression);
    printf("Enter the number of productions:");
    scanf("%d", &numberOfproductions);
    struct production productions[10];
    char terminals[10];

    for(i = 0;i < numberOfproductions;i++)
    {
        struct production tempProduction;
        printf("Variable: ");
        scanf(" %c", &tempProduction.variable);
        printf("gives: ");
        scanf("%s", &tempProduction.prod);
        productions[i] = tempProduction;
    }
    printf("Enter the terminal symbols:");
    scanf("%s", &terminals);
    for(i = 0;i < numberOfproductions;i++)
    {
        if(productions[i].variable == productions[i].prod[0])
        {
            //left recursion
            char A[10];
            char B[10];
            j = 1;
            k = 0;
            while(productions[i].prod[j] != '|')
            {
                A[k] = productions[i].prod[j];
                k++;
                j++;
            }
            A[k] = tolower(productions[i].variable);
            A[++k] = '\0';
            strcat(A, "|$");
            struct production temp;
            temp.variable = tolower(productions[i].variable);
            strcpy(temp.prod, A);
            productions[numberOfproductions] = temp;
            numberOfproductions++;
            j++;
            k = 0;
            while(productions[i].prod[j] != '\0')
            {
                B[k] = productions[i].prod[j];
                k++;
                j++;
            }
            B[k] = tolower(productions[i].variable);
            B[++k] = '\0';
            strcpy(productions[i].prod, B);
        }
    }
    printf("After removing left recursion, Productions are:");
    for(i = 0;i < numberOfproductions;i++)
    {
        printf("\n%c -> %s", productions[i].variable, productions[i].prod);
    }
    printf("\n");
    for(i = 0;i < numberOfproductions;i++)
    {
        printf("Procedure %c() \n", productions[i].variable);
        printf("{\n");
        j = 0;
        int terminalCount = 0;
        while(productions[i].prod[j] != '\0')
        {
            while(productions[i].prod[j] != '|' && productions[i].prod[j] != '\0')
            {
                if(1 == isTerminal((productions[i].prod[j]), terminals))
                {
                    terminalCount++;
                    printf("if(input == '%c' ) {\n", productions[i].prod[j]);
                    if(productions[i].prod[j+1] == '|' || productions[i].prod[j+1] == '\0')
					{
                        printf("return () \n");
                    }
                }
                else if(productions[i].prod[j] == '$')
				{
                    printf("return () \n");
                }
                else
                {
                    printf("%c()\n", productions[i].prod[j]);
                }
                j++;
            }
            while(terminalCount > 0)
            {
                printf("} \n");
                terminalCount--;
            }
            if(productions[i].prod[j] == '|')
			{
                j++;
            }
            if(j>= strlen(productions[i].prod))
			{
                break;
            }
        }
        printf("}\n");
    }
    count = 0;
	flag = 0;	
	E();
	if((strlen(expression) == count) && (flag == 0))
	{
	    printf("\nThe Expression %s is Valid\n", expression);
	}
	else 
	{
	    printf("\nThe Expression %s is Invalid\n", expression);
	}
}
