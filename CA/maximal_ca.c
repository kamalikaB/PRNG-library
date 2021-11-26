/***************window for nonlinear ca to PRNG************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define N 32
#define d 2 
#define u 32

main()
{
	//srand(time(NULL));

	int castate[N],cnt=0,deci=0;//n= no of cell,u=length of bin
	FILE *fp,*fp1;
	unsigned int dc=0, index=1;
	int i,j;
	double t,m=pow(2,32),sum=0;
	int rule[N][d*d*d]={{0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
		         {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}, //rule 150
			 {0,1,0,1,1,0,1,0}, //rule 90
			 {0,1,1,0,1,0,0,1}}; //rule 150
			 

			

	
	
		fp = fopen("maxlength_ca_7.txt", "w"); // Open The File
		if (fp == NULL) {
        		printf("file not found\n");
        		exit(0);
      		}

		
		
		for(i=0;i<N;i++)
        	{
              		castate[i]=0;
		}
		
		
       		int state[]={1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		for(i=0;i<N;i++)
    			printf("%d",state[i]); //print initial state
		printf("\n\n");

		char ch=0,s=0;
		while(cnt<5000) //2050550 90000000 2883584 32768000 calculating Next state
    		{
			deci=0*4 +state[0]*2+ state[1];
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

 	
			deci=state[N-2]*4 +state[N-1]*2+ 0;
			castate[N-1]=rule[N-1][deci];
			//printf("%d\n",deci);
			//printf("%d",rule[44][deci]);
			//printf("\n");
			
			for(i=0;i<N;i++)
          		{
				state[i]=castate[i];
				printf("%d",state[i]);
	        	}
			printf("\n");
			sum = 0;
			for(i=N-1;i>=0;i--)
			{
				sum=sum+state[i]*pow(2,N-1-i);
			}				
			t=sum/m;
			cnt++;
			fprintf(fp,"%lf %.20lf\n",sum,t);
		}//End of while cnt
		cnt=0;
	
	 fclose(fp);
	
			
	return;
}//End of main


