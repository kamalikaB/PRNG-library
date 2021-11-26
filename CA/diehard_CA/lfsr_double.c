/*******************Diehard test to binary files listed in a .txt file*********************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "die.c"
int passed=0;
int results[20],i;
char pvalues[20][10];
int no_test=-1;
void diehard(char *);
static FILE *fp,*fp1;
double lfsr113_double (unsigned int y)
{
   unsigned int b;
   unsigned int z1,z2,z3,z4;
   z1=y;z2=y;z3=y;z4=y;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294UL) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27; 
   z2 = ((z2 & 4294967288UL) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280UL) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168UL) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4) * 2.3283064365386963e-10;
}
main()
{
	srand(0);
	double x,t,x1,x3;
	int i,j,k,l,n,*bin,index=64,counter=0,x2,v;
	for(v=0;v<1000;v++)
	{
    		char ch=0;
    		fp = fopen("lfsr_double.bin", "w");
		fp1=fopen("output_lfsr.csv","a+");
		n=1300000;
		unsigned int y;
		y=rand();
		printf("%u\n",y);
		t=lfsr113_double(y);
		for(i=0;i<n;i++)
		{
			
			printf("%0.32lf\n",t);
			x=t;
			bin=(int *)calloc(index,sizeof(int));
			for(j=0;j<index;j++)
			{
				x1=x*2;
				x2=(int)(x1);
				//printf("%0.32lf\n",x2);
				x3=x1-x2;
				bin[j]=x2;
				x=x3;
				//printf("%.32lf\t %d\n",x3, x2);
			
			}
		
		/****** Convert bin[] to store in a character ch ******/
		
			for(l=0;l<index;l++)
			{	
				ch=(ch<<1)|bin[l];
				counter++;
			
				if(counter==8)
				{
					fprintf(fp,"%c",ch);
					counter=0;
					ch=0;		
				}
			
			}
			free(bin);
			t=lfsr113_double(t);
		}
                fclose(fp);
		passed=0;
		no_test=-1;
		for(i=0;i<20;i++){
		results[i]=0;
		sprintf(pvalues[i],"%s","0");
		}
		diehard("lfsr_double.bin");
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
	
}
