/*************Non-linear PRNG based on CA150' that injects non-linear rules 86, 149, 101, 154 at a regular interval of 6 cells. It also uses tempering of MT-19937 and produces 44 32-bit integers at a time.************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <bits/stdc++.h>
#include "1409seednv.h"
//#include "TestU01.h"

/* Period parameters */  
#define N 44
#define L 1409

static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
bool ca[L];
bool ou[32];


void init_genrand(int seednum)
{
    for(int i=0;i<L;i++)
        ca[i] = seed[seednum][i];
}

void cagenerator()
{
    bool temp[L];
    
    temp[0]=ca[1];

    for(int i=1;i<L-1;i++)
    {
        temp[i]=ca[i-1]^(ca[i]^ca[i+1]);
    }
    
	int count=0;
	for(int i=5;i<L-1;i=i+6)
	{
		if(count%4==0)
		{
			temp[i]=(ca[i-1]|ca[i])^ca[i+1];				//86
		}
		else if(count%4==1)
		{
			temp[i]=(ca[i-1]&ca[i])^(!ca[i+1]);				//149
		}
		else if(count%4==2)
		{
			temp[i]=ca[i-1]^(ca[i-1]&ca[i])^(!ca[i+1]);		//101
		}
		else
		{
//			i+=6;
			temp[i]=ca[i-1]^((ca[i-1]&ca[i])^ca[i+1]);		//154
		}
		
		count++;
	}

    temp[L-1]=ca[L-2]^ca[L-1];

    for(int i=0;i<L;i++)
        ca[i]=temp[i];
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned int y=0;

    if (mti >= N) { /* generate N words at one time */
        cagenerator();
        mti = 0;
    }
    
    int t=mti<<5;
    for(int i=0;i<32;i++)
    {
        y=y<<1;
        y=ca[t+i]|y;
    }

    mti++;
    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

int main(int argc, char* argv[])
{
    int seednum=393;

    if(argc>1)
        seednum=atoi(argv[1]);

    int i,j;
    init_genrand(seednum);
    
    unsigned long out;
   

    printf("1000 outputs of genrand_int32()\n");

    for (j=0; j<1000; j++) {
    	
    	int bin_out[32]; 
    	out = genrand_int32();
    	printf("%lu\n", out);
    }  
    return 0;
}
