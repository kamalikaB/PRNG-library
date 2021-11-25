/********************The program generates numbers in binary form from a seed using PCG**********************/
/*************We have taken n = 1000 for lattice tests and 250 for space time diagram whereas seed values are taken as an array of 7, 1234, 12345, 19650218 and 123456789123456789*******************/
/*********************The same program can be used for NIST by giving n suitably to generate file of size atleast 100 MB**************************/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "pcg_basic.h"

uint64_t seedArray[5]={12345,123456789,123456789123456789,7,9650218};
uint32_t pcg32_random_r(pcg32_random_t* rng)
{
    uint64_t oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

static pcg32_random_t pcg32_global = PCG32_INITIALIZER;

void pcg32_srandom_r(pcg32_random_t* rng, uint64_t initstate, uint64_t initseq)
{
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_random_r(rng);
    rng->state += initstate;
    pcg32_random_r(rng);
}

void pcg32_srandom(uint64_t seed, uint64_t seq)
{
    pcg32_srandom_r(&pcg32_global, seed, seq);
}


void main()
{
	int rounds = 5,n;
	bool nondeterministic_seed = false;
	int i,j,*bin,index,k;
	uint32_t result,t;
	char ch=0;
	FILE *fp;
    	pcg32_random_t rng;
	char str[50];
	printf("HOW MANY NUMBER YOU WANT TO GENERATE?\n");
	scanf("%d",&n);
    	
	for(k=0;k<5;k++)
	{
		pcg32_srandom_r(&rng, seedArray[k], 0u);//42u,54u
		sprintf(string3,"%" PRIu64  "\n",seedArray[k]);
	
		printf("enter a output file name within 50 characters for seed ");
		printf("%" PRIu64  "\n",seedArray[k]);
		scanf("%s",str);
		fp = fopen(str, "wb");
		if (fp == NULL) {
       	 printf ("File not created!! \n");
		}
		for (i = 0; i < n; i++)
		{
		
			result=pcg32_random_r(&rng);
			printf("%" PRIu32  "\n",result);
			//printf("\n");
			t=result;
			index=32;
			bin=(int *)calloc(index,sizeof(int));
			for(j=0;j<index;j++)
			{
				bin[index-j-1]=t&1;
				t=t>>1;
		
		 	}
		
			for(j=0;j<index;j++)
			{
				fprintf(fp,"%d",bin[j]);
			}
			fprintf(fp,"\n");

		}

		fclose(fp);
    	}

	
	
}	
