/***************window for nonlinear ca to PRNG************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define N 45
#define d 2 
#define u 45

#include"die.c"

int passed=0;
int results[20],i;
char pvalues[20][10];
int no_test=-1;
void diehard(char *);

void main(int argc, char * argv[])
{
  	srand(time(NULL));
  	int rule[45][8]={{1,0,1,0,0,0,0,0}, //rule 5
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {1,0,1,0,0,1,0,1}, //rule 165
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {1,0,1,0,0,1,0,1}, //rule 165
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,1,0,0,1,0,1}, //rule 165
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {1,0,1,0,0,1,0,1}, //rule 165
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,1,0,0,1,0,1}, //rule 165
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,0,1,0,1,0,0,0}}; //Rule 20


			 /*{0,1,0,1,0,1,0,1}, //rule 170
                         {0,0,0,0,0,1,0,1}, //rule 160
			 
			 
			 {1,0,0,1,1,0,0,1}, //rule 153
			 {1,0,1,0,1,0,1,0}, //rule 85
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,1,0,1,0,1,0}, //rule 86
			 {1,0,1,0,0,1,0,1}, //rule 165
			 {1,0,0,1,1,0,0,1}, //rule 153
			 {0,1,1,0,0,1,1,0}, //rule 102
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,0,0,0,0,1,0,1}, //rule 160
			 {0,1,0,1,0,1,0,1}, //rule 170
			 
			 {0,1,0,1,1,0,0,1}, //rule 154
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,0,1,0,1,1,0}, //rule 106
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,0,1,0,1}, //rule 170
			 {0,0,0,0,0,1,0,1}, //rule 160
			 {0,1,1,0,1,0,1,0}, //rule 86
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {1,0,1,0,0,1,1,0}, //rule 101
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {1,0,1,0,0,1,0,1}, //rule 165
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,0,1,1,0,1,0}, //rule 89
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {1,0,0,1,1,0,0,1}, //rule 153
			 {1,0,1,0,1,0,0,1}, //rule 149
			 {1,0,1,0,0,1,0,1}, //rule 165
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {1,0,0,1,0,1,1,0}, //rule 105
			 {1,0,1,0,1,0,1,0}, //rule 85
			 {0,0,0,0,0,1,0,1}, //rule 160
			 {1,0,0,0,0,0,1,0}}; //rule 65*/
			
	
	long int seeds[5]={7,1234,12345,19650218,123456789123456789};
	int noSeeds=5,sI=0;
	
	for(sI=0;sI<noSeeds;sI++){
		long int num=seeds[sI];
		passed=0;
		no_test=-1;
		for(i=0;i<20;i++){
			results[i]=0;  //stores results of diehard test
			sprintf(pvalues[i],"%s","0");
		}

		int castate[N],bin[u],cnt=0,deci=0;//n= no of cell,u=length of bin
		FILE *fp;
		unsigned int dc=0, index=1;
		int i,j;
		long int t,m=pow(2,45),sum=0;

		fp = fopen("nonlinearCA.bin", "w"); // Open The File
		if (fp == NULL) {
        		printf("file not found\n");
        		exit(0);
      		}

		
		
		for(i=0;i<N;i++)
        	{
              		castate[i]=0;
		}
		
		
       		int state[u];//={1,1,0,1,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,0,1,1,0,0,1,1,0,1,0,0,0,0,0,1,0,1};
		for(i=0;i<N;i++)
		{
			state[i]=num%d;
			num=num/d;
			//printf("%d",state[i]); //print initial state
		}
		for(i=0;i<N;i++)
    			printf("%d",state[i]); //print initial state
		printf("\n\n");

		char ch=0,s=0;
		while(cnt<2050550) //2050550 90000000 2883584 calculating Next state
    		{
			deci=state[N-1]*4 +state[0]*2+ state[1];
			//printf("%d\n",deci);
			castate[0]=rule[0][deci];
			//printf("%d",rule[0][deci]);

			for(i=1;i<N-1;i++)
        		{
             			deci=state[i-1]*4+state[i]*2+state[i+1];
             			castate[i]=rule[i][deci];
				//printf("%d\n",deci);
				//printf("%d",rule[i][deci]);
             		}

 	
			deci=state[N-2]*4 +state[N-1]*2+ state[0];
			castate[N-1]=rule[44][deci];
			//printf("%d\n",deci);
			//printf("%d",rule[44][deci]);
			//printf("\n");
			
			for(i=0;i<N;i++)
          		{
				state[i]=castate[i];
				//printf("%d",state[i]);
	        	}
			//printf("\n");
			
							
			/*sum=0;
			for(i=N-1;i>=0;i--)
			{
				sum=sum+state[i]*pow(2,N-1-i);
			}				
			

			for(i=0;i<u;i++)  //Binary Value
			{
				bin[u-i-1]=sum&1; 
				sum=sum>>1;
			}

				/*for(i=0;i<index;i++)
				{
					printf("%d",bin[i]);
				}

				printf("\n");*/

			
	        	/***** (Binary)*******/
			for(i=0;i<N;i++)
			{	
				ch=(ch<<1)|state[i];
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
			
			}// End of Binary
			 		
			cnt++;		
		}//End of while cnt/*

		fprintf(fp,"%c",ch);
		fclose(fp);
		diehard("nonlinearCA.bin");
		int passed_combined = 0;	
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
		//fprintf(fp1,"%d,\n",passed_combined);
		fflush(stdout);
		printf("\nDiehard tests passed = %d out of 15\n", passed_combined);
		printf("__________________________________________________________________________________________\n");
 		
	}//end of for loop
  	//return;// Close the file
}//End of main


