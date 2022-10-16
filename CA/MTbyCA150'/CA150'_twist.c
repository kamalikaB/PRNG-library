/************CA150' based PRNG that uses Tempering and Twist on configuration like MT-19937 and produces 44 32-bit integers at a time********/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "1409seedsks.h"
#include <bits/stdc++.h>

/* Period parameters */
#define N 44
#define L 1409
#define upper_mask 0x80000000UL
#define lower_mask 0x7fffffffUL
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
bool ca[L];
unsigned int temp_arr[45];
bool ou[32];
int m=23;

void init_genrand(int seednum)
{

    for(int i=0;i<L;i++)
        ca[i] = seed[seednum][i];// seed[500][1409] stored in 1409sks.h file

}


bool applyRule90Formula(bool a, bool b, bool c)
{
    return a^c; //Rule 90 = A XOR C
}

bool applyRule150Formula(bool a, bool b, bool c)
{
    return a^(b^c); //Rule 150 = A XOR (B XOR C)
}

void cagenerator()
{
    bool a,b,c,r;
    bool temp[L];

    a=0;
    b=ca[0];
    c=ca[1];

    r=applyRule90Formula(a,b,c);
    temp[0]=r;

    for(int i=1;i<L-1;i++)
    {
        a=ca[i-1];
        b=ca[i];
        c=ca[i+1];

        r=applyRule150Formula(a,b,c);
        temp[i]=r;
    }

    a=ca[L-2];
    b=ca[L-1];
    c=0;

    r=applyRule150Formula(a,b,c);
    temp[L-1]=r;

    for(int i=0;i<L;i++)
        ca[i]=temp[i];
}

void twist(){
	unsigned int a=0x9908B0DF;
	for(int i=0;i<44;i++)
	{
		unsigned int ab=0;
		for(int j=0;j<32;j++)
		{
			ab=(ab<<1)|ca[32*i + j];
		}
		temp_arr[i]=ab;
	}

	for(int i=0;i<43;i++)
	{
		unsigned int x=(temp_arr[i] & upper_mask)+(temp_arr[(i+1)%44] & lower_mask);
		unsigned int xa=x>>1;
		if((x%2)!=0)
			xa=xa ^ a;
		temp_arr[i]=temp_arr[(i+m)%44] ^ xa;
	}
}
/* generates a random number on [0,0xffffffff]-interval */
unsigned int genrand_int32(void)
{
    unsigned int y=0x00000000;

    if (mti >= N) { /* generate N words at one time */
        cagenerator();
		memset(temp_arr,0,sizeof(temp_arr));
		twist();
//		cout<<endl;
        mti = 0;
    }

    y=temp_arr[mti];

    mti++;
    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= (y >> 18);
    return y;
}

void util_convert(unsigned long a1)
{
  for(int i=0;i<32;i++)
  {
    ou[i]=a1%2;
    a1=a1>>1;
  }
}

int main(int argc, char* argv[])
{
    int seednum=367;

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
