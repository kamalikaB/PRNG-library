/*******************Diehard from file as input for d=10*********************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"die.c"
#define n 51
#define d 10
#define neighbor 3
#define size 12 //size of window
#define index 32 //number of bits per window
#define loop_value 20
int passed=0,max_passed=0,loop=0;
int results[20],max_results[20],i;
void diehard();

void main(int argc, char * argv[])
{
  	srand(time(NULL));
  	int rule[d*d*d];
 	FILE *fp,*fp1;
  	char s[d*d*d+1];
  	char c;
  	fp1=fopen(argv[1],"r");
	printf("\n\t\t\t");
  	while(!feof(fp1))
  	{
     		fscanf(fp1,"%s",s);
     		for(i=0;i<strlen(s);i++)
     			rule[i]=s[i]-48;
     		for(i=0;i<strlen(s);i++)
   			printf("%d",rule[i]);
		printf("\n");
    

		while(loop<loop_value)
  	 	{
			passed=0;
			for(i=0;i<20;i++)
				results[i]=0;  //stores results of diehard test
			int rmt=0,castate[n],state[n],number[size],k=0,bin[index],counter=0,cnt=0;
			long number1=0, t=0;
			//int r,arr[20],castate[N],state[N],number[100],cnt=0,deci,index=1,dc=0,bin[u],cnt_r=0,k=0,t,j,number1=0;// n= no of cell, d=no of states, r=random int variable 			for d=3 ,u=length of bin


			fp = fopen("abc.bin", "w"); // Open The File
			if (fp == NULL) {
        			printf("file not found\n");
        			exit(0);
      			}	
		
               
		
			for(i=0;i<n;i++)
        		{
              			castate[i]=0;
              			state[i]=0;
			}
	
       			for(i=0;i<n;i++) //Random initial configuration
			{
				state[i]=rand()%d;
				//printf("%d",state[i]);
			} 
			//printf("\n\n");
		
			char ch=0;
			counter=0;
			while(cnt<3010000) // calculating Next state 3010000
    			{
				rmt=state[n-1]*d*d +state[0]*d+ state[1];
				castate[0]=rule[rmt];

				for(i=1;i<n-1;i++)
        			{
             				rmt=state[i-1]*d*d+state[i]*d+state[i+1];
             				castate[i]=rule[rmt];
             			
          			}  	
				rmt=state[n-2]*d*d +state[n-1]*d+ state[0];
				castate[n-1]=rule[rmt];
				for(i=0;i<n;i++)
          			{
					state[i]=castate[i];
	        		}
				
				//printf("\n");
				k=0;
				number1=0;
				for(i=(n/2-size/2);i<(n/2+size/2);i++)/*collect random number*/
				{
					number[k]=state[i];
					//printf("%d",number[k]);
					number1+=number[k]*pow(d,size-k-1); //deci_pow;	deci_pow=deci_pow/d;
					k++;
				}
				//printf("\t%lu\t",number1);
				t=number1;
				
							
				for(i=0;i<index;i++)  //Binary Value
				{
					bin[index-i-1]=t&1; //discard MSB if out of index size
					t=t>>1;
				}

				/*for(i=0;i<index;i++)
				{
					printf("%d",bin[i]);
				}

				printf("\n");*/

				
	        		/***** (Binary)*******/
				for(i=0;i<index;i++)
				{	
					ch=(ch<<1)|bin[i];
					counter++;
			
					if(counter==8) 
					{
						fprintf(fp,"%c",ch);
						counter=0;
						ch=0;		
					}
			
				}// End of Binary
			 
				t=0;
				cnt++;
		
			}//End of while cnt/*

			fprintf(fp,"%c",ch);
			fclose(fp);
		
			diehard();
			loop++;
			// print individual results
			printf("\t Number of tests passed = %d\n",passed);
			printf("\n");
		 	printf("\t\t\t");
		  	for(i=0;i<20;i++)
		  		printf(" %d |", results[i]);
		  	printf("\n\n");

               		if(max_passed<passed)
			{
				max_passed=passed;
				for(i=0;i<20;i++)
					max_results[i]=results[i];
			}	
  			if(loop==loop_value)
                	{
		   		printf("\n\t\t\tThe maximum number of tests passed : %d\n", max_passed);
				printf("\t\t\t");
		  		for(i=0;i<20;i++)
		  			printf(" %d |", max_results[i]);
		  		printf("\n\n\n");
              		}
		}//End of while loop
        	//printf(".................................................................\n");
      		loop=0;
       		max_passed=0;
        	do
		{
			fscanf(fp1,"%c",&c);
		}while(c!='\n');
		fscanf(fp1,"\n");
		printf("\t\t\t");
  	}
   	fclose(fp1);
  	//return;// Close the file
}//End of main

