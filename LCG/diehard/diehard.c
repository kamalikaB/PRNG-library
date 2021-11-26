#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "die.c"

int passed=0;
int results[20],i;
char pvalues[20][10];
int no_test=-1;
void diehard(char *);
static FILE *fp1;

void main(int argc, char * argv[])
{
	unsigned long int seed,result,t;
	int n,i,*bin,index=32,j,v,l,counter;
	char str[50];
	printf("enter the input file name (.bin) within 50 characters\n");
	scanf("%s",str);
	fp1=fopen("Result.txt","a+");
	if (fp1 == NULL) {
        	printf ("File not created!! \n");
	}
	for(i=0;i<20;i++){
		results[i]=0;
		sprintf(pvalues[i],"%s","0");
	}
	diehard(str);
		
	int passed_combined = 0;	
			
	for(i=0;i<20;i++){
  		printf(" %s |", pvalues[i]);
  		fprintf(fp1," %s |", pvalues[i]);
	}
	printf("\n\n");
	fprintf(fp1,"\n");

        for(i=0;i<20;i++)
	{	
		if((i==2) && (results[i]==1) && (results[i+1]==1))
		{
			passed_combined++;
		}
		if((i==6) && (results[i]==1) && (results[i+1]==1) && (results[i+2]==1))
		{
			passed_combined++;				
		}
		if((i==16) && (results[i]==1) && (results[i+1]==1))
		{
			passed_combined++;	
		}
		if((i==18) && (results[i]==1) && (results[i+1]==1))
		{
			passed_combined++;
		}
		if((i==0)||(i==1)||(i==4)||(i==5)||(i==9)||(i==10)||(i==11)||(i==12)||(i==13)||(i==14)||(i==15))
		{
			if(results[i]==1){
				passed_combined++;
			}			
		}
	}
	fprintf(fp1,"Diehard Test Passed = %d out of 15\n",passed_combined);
	fflush(fp1);
	printf("\nDiehard tests passed = %d out of 15\n", passed_combined);
	printf("__________________________________________________________________________________________\n");
 	fclose(fp1);
}
