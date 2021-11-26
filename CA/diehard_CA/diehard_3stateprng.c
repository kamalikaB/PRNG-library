/***************PRNG_with_window************/
/*******************Diehard test to binary files listed in a .txt file*********************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "die.c"

#define N 51
#define d 3 
#define u 32
#define w 21
#define neighbor 3

int passed=0;
int results[20],i;
char pvalues[20][10];
int no_test=-1;
void diehard(char *);
FILE *fp,*fp1;

int main()
{
	srand(0);
	int ns[N],ps[N],cnt=0,deci,*bin,window[w],a,counter=0;//n= no of cell,u=length of bin
	unsigned int dc=0, index=32;
	int j,i,q,k,v,n,num;
	char ch=0;
	unsigned int number=0,t;
	int rule[]={0,1,2,1,2,0,1,2,0,0,2,1,1,2,0,1,2,0,0,2,1,1,2,0,0,2,1};
	n=2600000;
	for(v=0;v<1000;v++)
	{
		
		fp = fopen("3stateprng.bin", "w"); // Open The File
		fp1=fopen("output_3stateprng.csv","a+");
		for(i=0;i<N;i++)
		{
		      	ns[i]=0;
			ps[i]=0;
		}
		ps[N-1]=1;		
		num=rand();
		printf("%d\n",num);

		//int state[]={1,1,0,1,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,0,1,1,0};
		for(i=0;i<w;i++)
		{
			ps[i]=num%d;
			num=num/d;
			//printf("%d",ps[i]); //print initial state
		}
		for(i=0;i<N;i++)
		{
			printf("%d ",ps[i]);
		}


		for(i=0;i<N;i++)
		{

				if(i==0)
				{
					a=ps[N-1]*pow(d,neighbor-1)+ps[0]*pow(d,neighbor-2)+ps[1]*pow(d,neighbor-3);
	
				}
		 		else if(i==N-1)
				{
					a=ps[0]*pow(d,neighbor-3)+ps[N-1]*pow(d,neighbor-2)+ps[N-2]*pow(d,neighbor-1);
				}
				else 
				{
					a=ps[i-1]*pow(d,neighbor-1)+ps[i]*pow(d,neighbor-2)+ps[i+1]*pow(d,neighbor-3);
				}
				//printf("%d",a);
				//printf("\n");
				ns[i]=rule[a];
				//printf(" %d",ns[i]);
				
		}
		for(i=0;i<N;i++)
		{
				ps[i]=ns[i];
		}
		for(q=0;q<n;q++)
		{
			
			for(i=0;i<N;i++)
			{

				if(i==0)
				{
					a=ps[N-1]*pow(d,neighbor-1)+ps[0]*pow(d,neighbor-2)+ps[1]*pow(d,neighbor-3);
	
				}
		 		else if(i==N-1)
				{
					a=ps[0]*pow(d,neighbor-3)+ps[N-1]*pow(d,neighbor-2)+ps[N-2]*pow(d,neighbor-1);
				}
				else 
				{
					a=ps[i-1]*pow(d,neighbor-1)+ps[i]*pow(d,neighbor-2)+ps[i+1]*pow(d,neighbor-3);
				}
				//printf("%d",a);
				//printf("\n");
				ns[i]=rule[a];
				//printf(" %d",ns[i]);
				
			}
			for(i=0;i<N;i++)
			{
				ps[i]=ns[i];
			}
			k=0;
			number=0;
	  		for(i=N/2;i<(N/2+w);i++)
			{
				number=number+ns[i]*pow(d,N-1-k);	
				k++;
			}
			//printf("number=%u\n",number);
			t=number;		
			bin=(int *)calloc(index,sizeof(int));
			for(j=0;j<index;j++)
			{
				bin[index-j-1]=t&1;
				t=t>>1;
			}

			/****** Convert bin[] to store in a character ch ******/
		
			for(j=0;j<index;j++)
			{	
				ch=(ch<<1)|bin[j];
				counter++;
		
				if(counter==7)
				{
					fprintf(fp,"%c",ch);
					counter=0;
					ch=0;		
				}
		
			}
			free(bin);
		
		}
		fclose(fp);
		
		passed=0;
		no_test=-1;
		for(i=0;i<20;i++){
		results[i]=0;
		sprintf(pvalues[i],"%s","0");
		}
		diehard("3stateprng.bin");
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

}
