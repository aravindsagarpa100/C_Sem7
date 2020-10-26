#include<string.h>
#include<ctype.h>
#include<stdio.h>

void main()
{
int i,j,n,m,a[10][10],b[10],c,d,k;
printf("Enter no. of states: ");
scanf("%d",&n);
printf("Enter no. of inputs(Including epsilon): ");
scanf("%d",&m);
for(i=0;i<n;i++)
{
	for(j=0;j<m;j++)
	{
		printf("Enter output state of state %d with input %d: ",i,j);
		scanf("%d",&a[i][j]);
	}
}
for(i=0;i<n;i++)
{
	c=0;
	d=i;
	b[c]=i;
	while(a[i][m-1]!=-1)
	{
		for(k=0;k<c+1;k++)
		{
			if(a[i][m-1]==b[k])
			{
				goto x;
			}
		}
		c=c+1;
		b[c]=a[i][m-1];
		i=a[i][m-1];
	}
	x:
	printf("E-closure of state %d: ",d);
	for(j=0;j<c+1;j++)
	{
		printf("%d ",b[j]);
	}
	printf("\n");
	i=d;
}

}
