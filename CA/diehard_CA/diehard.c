/***************3state CA PRNG_with_window for 1000 random seeds************/
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

int i,q,l=0,v;
int passed=0;
int results[20],i;
char pvalues[20][10];
int no_test=-1;
void diehard(char *);
FILE *fp,*fp1;

main()
{
	srand(0);
	for(v=0;v<1000;v++){

		int castate[N],state[N],cnt=0,deci,bin[u],window[w];//n= no of cell,u=length of bin
		FILE *fp,*fp1;
		unsigned int dc=0, index=1;
		int j;
		int rule[]={0,1,2,1,2,0,1,2,0,0,2,1,1,2,0,1,2,0,0,2,1,1,2,0,0,2,1};
	
		fp1=fopen("output_3stateprng.csv","a+");
		
		fp = fopen("3stateprng.bin", "w"); // Open The File
		if (fp == NULL) {
        		printf("file not found\n");
        		exit(0);
      		}
		for(i=0;i<N;i++)
        	{
              		castate[i]=0;
              		state[i]=0;
		}

		int num=rand();
		printf("%d\n",num);

		for(i=0;i<w;i++)
		{
			window[i]=num%d;
			num=num/d;
			//printf("%d",ps[i]); //print initial state
		}
			
		for(i=0;i<w;i++){
			state[i]=window[i];
		}

       		for(i=w;i<N-1;i++) 
		{
			state[i]=0;
		} 
		state[N-1]=1;

		for(i=0;i<N;i++)
    			printf("%d",state[i]); //print initial state
		printf("\n\n");

		for(q=0;q<N;q++){
			deci=state[N-1]*9 +state[0]*3+ state[1];
			castate[0]=rule[deci];

			for(i=1;i<N-1;i++)
        		{
             			deci=state[i-1]*9+state[i]*3+state[i+1];
             			castate[i]=rule[deci];
             			
          		}  	
			deci=state[N-2]*9 +state[N-1]*3+ state[0];
			castate[N-1]=rule[deci];

			for(i=0;i<N;i++)
          		{
				state[i]=castate[i];
	        	}
			
		}

		char ch=0,s=0;
		while(cnt<2883600) // calculating Next state
    		{
			deci=state[N-1]*9 +state[0]*3+ state[1];
			castate[0]=rule[deci];

			for(i=1;i<N-1;i++)
        		{
             			deci=state[i-1]*9+state[i]*3+state[i+1];
             			castate[i]=rule[deci];
             			
          		}  	
			deci=state[N-2]*9 +state[N-1]*3+ state[0];
			castate[N-1]=rule[deci];

			for(i=0;i<N;i++)
          		{
				state[i]=castate[i];
	        	}
			
			/*for(i=0;i<w;i++)
				window[i]=state[N-w-1+i]; //populate window*/

			for(i=0;i<w;i++)
				window[i]=state[N/2-w/2+i]; //populate window
			
				
			/*for(i=0;i<u;i++)
				bin[i]=0;*/

			for(i=0;i<w;i++) //Decimal Value
			{
				dc+=window[w-1-i]*index;
                		index*=3;
			}
				
			//fprintf(fp,"%u\n",dc);
			for(i=0;i<u;i++)  //Binary Value
			{
				bin[i]=dc&1;
				dc=dc>>1;
			}

			/*for(i=0;i<u;i++)
				fprintf(fp,"%d",bin[i]);
			fprintf(fp,"\n");*/		
		
	        	/***** (Binary)*******/
			
			for(i=0;i<u;i++)
			{
				ch=(ch<<1)|bin[i];
			
				if(s==7)
				{
					//printf("%c",ch);
					fprintf(fp,"%c",ch);
					s=0;
					ch=0;
				}
				else
				{
					s++;
				}
			}// End of Binary
			dc=0;
			index=1;
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
		fflush(fp1);
		printf("\nDiehard tests passed = %d out of 15\n", passed_combined);
		printf("__________________________________________________________________________________________\n");
		fclose(fp1);      	
	}	
	//}	
	return;
}//End of main


