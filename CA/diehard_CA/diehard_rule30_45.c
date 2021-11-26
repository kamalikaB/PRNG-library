/***************window for hybrid rule 30 and 45 similar to PRNG************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define N 32
#define d 2 
#define u 32

main()
{
	srand(time(NULL));

	int castate[N],cnt=0,deci=0;//n= no of cell,u=length of bin
	FILE *fp,*fp1;
	unsigned int dc=0, index=1;
	int i,j;
	int rule1[]={0,1,1,1,1,0,0,0}; //rule 30
	int rule2[]={1,0,1,1,0,1,0,0}; //rule 45
	
		fp = fopen("rule30_45_7.bin", "w"); // Open The File
		if (fp == NULL) {
        		printf("file not found\n");
        		exit(0);
      		}

		
		
		for(i=0;i<N;i++)
        	{
              		castate[i]=0;
		}
		
		
       		int state[]={1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		for(i=0;i<N;i++)
    			printf("%d",state[i]); //print initial state
		printf("\n\n");

		char ch=0,s=0;
		while(cnt< 2883584) // calculating Next state 90000000
    		{
			deci=state[N-1]*4 +state[0]*2+ state[1];
			castate[0]=rule1[deci];

			for(i=2;i<N-1;i=i+2)
        		{
             			deci=state[i-1]*4+state[i]*2+state[i+1];
             			castate[i]=rule1[deci];
             		}

			for(i=1;i<N-1;i=i+2)
        		{
             			deci=state[i-1]*4+state[i]*2+state[i+1];
             			castate[i]=rule2[deci];
             		}

 	
			deci=state[N-2]*4 +state[N-1]*2+ state[0];
			castate[N-1]=rule2[deci];

			for(i=0;i<N;i++)
          		{
				state[i]=castate[i];
	        	}
			
							
			
	        	/***** (Binary)*******/

			for(i=0;i<N;i++){
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
			}
			dc=0;
			index=1;
			cnt++;
			
		
		}//End of while cnt
		cnt=0;
	
	 fclose(fp);
	
			
	return;
}//End of main


