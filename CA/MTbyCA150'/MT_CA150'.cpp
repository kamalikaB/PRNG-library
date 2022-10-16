/************CA150' based PRNG that uses Tempering and Twist of MT-19937 and produces 44 32-bit integers at a time********/
#include <bits/stdc++.h>
#include "1409seedsks.h"
using namespace std;

/* Period parameters */  
#define N 44
#define L 1409

static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
bool ca[L];
bool ou[32];


void init_genrand(int seednum)
{
    // srand(time(0));

    for(int i=0;i<L;i++)
        ca[i] = seed[seednum][i];

        // ca[i] = rand()%2;
}


inline bool applyRule90Formula(bool a, bool b, bool c)
{
    return a^c; //Rule 90 = A XOR C
}

inline bool applyRule150Formula(bool a, bool b, bool c)
{
    return a^(b^c); //Rule 150 = A XOR (B XOR C)
}

void cagenerator()
{
    bool a,b,c,r;
    bool temp[L];
    
    a=0;//ca[L-1];
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
    c=0;//ca[0];

    r=applyRule150Formula(a,b,c);
    temp[L-1]=r;

    for(int i=0;i<L;i++)
        ca[i]=temp[i];
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;

    if (mti >= N) { /* generate N words at one time */
        cagenerator();
        mti = 0;
    }
    
    y=0UL;
    for(int i=0;i<32;i++)
    {
        y=y<<1;
        y=ca[(32*mti)+i]|y;
    }

    mti++;
    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
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
