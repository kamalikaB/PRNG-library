#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define N 51
#define d 3 
#define u 32
#define w 20

void main()
{

	int i;
	unsigned int random_number=0;
	int rule[]={0,1,2,1,2,0,1,2,0,0,2,1,1,2,0,1,2,0,0,2,1,1,2,0,0,2,1};
	FILE *fp;
	int castate[N],state[N],cnt=0,deci,bin[u],window[w];
	unsigned int dc=0, index=1;
	int j;
	for(i=0;i<20;i++){
		window[i]=0;
	}
	srand(time(NULL));
	fp = fopen("abc.bin", "w"); // Open The File
	if (fp == NULL) {
        	printf("file not found\n");
        	exit(0);
      	}

	
	for(i=0;i<N;i++)
		state[i]=0;
		
	//printf("\nEnter %d random ternary value for the window : \n",w);
	for(i=0;i<w;i++){
		//scanf("%d",&state[i]);
		state[i]=rand()%d;
	}
	for(i=w;i<N-1;i++) //initialize other values to 000...001
		state[i]=0;		
	state[N-1]=1;
		
    	
	/*// Next state generation 
	NS[0] = Rule[d*d*PS[n-1]+d*PS[0]+PS[1]];  // next state for left most cell
	for(i=1;i<n-1;i++)
	{
		NS[i] = Rule[d*d*PS[i-1]+d*PS[i]+PS[i+1]];
	}
	NS[n-1] = Rule[d*d*PS[n-2]+d*PS[n-1]+PS[0]]; // next state for right most cell
	
	for(i=0;i<n;i++)
		PS[i] = NS[i];

	printf("\n Random Number : ");
	
	for(i=0;i<window;i++){
		random_number += PS[i]*pow(d,window-1-i);	 //converts to decimal
		printf("%d",PS[i]);
	}		 	

	printf("\t = %u (in decimal)\n", random_number);

	//return(random_number);*/

	for(i=0;i<N;i++)
    		printf("%d",state[i]); //print initial state
	printf("\n\n");

	for(j=0;j<N;j++){
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
		while(cnt<3200000) // calculating Next state
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
			
			for(i=0;i<w;i++)
				window[i]=state[i]; //populate window
			
				
			for(i=0;i<u;i++)
				bin[i]=0;

			for(i=0;i<w;i++) //Decimal Value
			{
				dc+=window[w-1-i]*index;
                		index*=3;
			}
				
			for(i=0;i<u;i++)  //Binary Value
			{
				bin[i]=dc&1;
				dc=dc>>1;
			}		
		
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
}
