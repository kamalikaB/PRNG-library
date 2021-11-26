/***************window for hybrid rule 30  similar to PRNG************/
/***************PRNG_with_window************/
/*******************Diehard test to binary files listed in a .txt file*********************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "die.c"

#define N 101
#define d 2 
#define u 32
int passed=0;
int results[20],i;
char pvalues[20][10];
int no_test=-1;
void diehard(char *);
FILE *fp,*fp1;
main()
{
	srand(0);

	int castate[N],state[N],cnt=0,deci=0,v;//n= no of cell,u=length of bin
	unsigned int dc=0, index=1,num=0;
	int i,j;
	int rule1[]={0,1,1,1,1,0,0,0}; //rule 30
	//int rule2[]={1,0,1,1,0,1,0,0}; //rule 45
	for(v=0;v<1000;v++)
	{
		fp = fopen("rule30.bin", "w"); // Open The File
		fp1=fopen("output_rule30.csv","a+");

	
		for(i=0;i<N;i++)
		{
	      		castate[i]=0;
		}
		
		num=rand();
		printf("%d\n",num);
		//int state[]={1,1,0,1,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,0,1,1,0};
		for(i=0;i<N;i++)
		{
			state[i]=num%d;
			num=num/d;
			//printf("%d",state[i]); //print initial state
		}
		for(i=0;i<N;i++)
		{
			printf("%d ",state[i]);
		}
		printf("\n\n");

		char ch=0,s=0;
		while(cnt<2883584*N) //90000000 2883584 calculating Next state
		{
			deci=state[N-1]*4 +state[0]*2+ state[1];
			//printf("%d\n",deci);
			castate[0]=rule1[deci];
			//printf("%d",rule1[deci]);

			for(i=1;i<N-1;i++)
			{
	     			deci=state[i-1]*4+state[i]*2+state[i+1];
	     			castate[i]=rule1[deci];
				//printf("%d\n",deci);
				//printf("%d",rule1[deci]);
	     		}

			deci=state[N-2]*4 +state[N-1]*2+ state[0];
			//printf("%d\n",deci);
			castate[N-1]=rule1[deci];
			//printf("%d",rule1[deci]);			

			for(i=0;i<N;i++)
	  		{
				state[i]=castate[i];
				//printf("%d",state[i]);
			}
			//printf("\n");
		
						
			//for(i=0;i<N;i++)
			{
				/***** (Binary)*******/
				ch=(ch<<1)|state[0];
		
				if(s==7)
				{

					fprintf(fp,"%c",ch);
					s=0;
					ch=0;
				}
				else
				{
					s++;
				}
				//dc=0;
				//index=1;
			
			}
			cnt++;
	
		}//End of while cnt
		cnt=0;
	
		fclose(fp);
		passed=0;
		no_test=-1;
		for(i=0;i<20;i++){
		results[i]=0;
		sprintf(pvalues[i],"%s","0");
		}
		diehard("rule30.bin");
		int passed_combined = 0;	
		printf("\n\n");
		for(i=0;i<20;i++){
			printf(" %s |", pvalues[i]);
		}
		printf("\n\n");

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
		fprintf(fp1,"%d,\n",passed_combined);
		printf("\nDiehard tests passed = %d out of 15\n", passed_combined);
		printf("__________________________________________________________________________________________\n");
		fclose(fp1);      	
	}	
			
	return 0;
}//End of main


