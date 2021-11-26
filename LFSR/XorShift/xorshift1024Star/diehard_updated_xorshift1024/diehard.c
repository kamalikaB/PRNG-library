/*  Written in 2014 by Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

/* This is a fast, top-quality generator. If 1024 bits of state are too
   much, try a xoroshiro128+ generator.

   Note that the three lowest bits of this generator are LSFRs, and thus
   they are slightly less random than the other bits. We suggest to use a
   sign test to extract a random Boolean value.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "die.c"

int passed=0;
int results[20],i;
char pvalues[20][10];
int no_test=-1;
void diehard(char *);
static FILE *fp,*fp1;
uint64_t x;
uint64_t s[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 

int p;
uint64_t next(void) {
	const uint64_t s0 = s[p];
	uint64_t s1 = s[p = (p + 1) & 15];
	s1 ^= s1 << 31; // a
	s[p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b,c
	//printf("%" PRIu64  "\n",s[p]);
	return s[p] * UINT64_C(1181783497276652981);
}


/* This is the jump function for the generator. It is equivalent
   to 2^512 calls to next(); it can be used to generate 2^512
   non-overlapping subsequences for parallel computations. */

/*void jump(void) {
			static const uint64_t JUMP[] = { 0x84242f96eca9c41d,
			0xa3c65b8776f96855, 0x5b34a39f070b5837, 0x4489affce4f31a1e,
			0x2ffeeb0a48316f40, 0xdc2d9891fe68c022, 0x3659132bb12fea70,
			0xaac17d8efa43cab8, 0xc4cb815590989b13, 0x5ee975283d71c93b,
			0x691548c86c1bd540, 0x7910c41d10a1e6a5, 0x0b5fc64563b3e2a8,
			0x047f7684e9fc949d, 0xb99181f2d8f685ca, 0x284600e3f30e38c3
			};
		int i,j,b;
		int t1,k,n,*bin,index;
		unsigned long long int result;
		double t2,m=pow(2,64);
		uint64_t t[16] = { 0 };
		for(i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
			for(b = 0; b < 64; b++) 
			{
				if (JUMP[i] & 1ULL << b)
				for(j = 0; j < 16; j++)
					t[j] ^= s[(j + p) & 15];
				result=next();
				t2=result/m;
				fprintf(fp,"%.20llf\n",t2);
				//printf("%d\n",result);
				//printf("%" PRIu64  "\n",result);
				/*t1=result;
				index=32;
        			bin=(int *)calloc(index,sizeof(int));
				for(k=0;k<index;k++)
				{
					bin[index-k-1]=t1&1;
					t1=t1>>1;
		
				}*/

			/****** Convert bin[] to store in a character ch ******/
		
				/*for(k=0;k<index;k++)
				{	
					ch=(ch<<1)|bin[k];
					counter++;
			
					if(counter==8) 
					{
						fprintf(fp,"%c",ch);
						counter=0;
						ch=0;		
					}
			
	 			}
	

			}

	for(j = 0; j < 16; j++)
		s[(j + p) & 15] = t[j];
}*/
main()
{
	//srand(0);
	int i,n=1300000,j;
	int k,*bin,index=64,counter=0,v;
	uint64_t  result,t1;
	char str[50];
	printf("enter the number of terms want to generate\n");
	scanf("%d",&n);
	printf("enter the seed value\n");
	scanf("%" SCNu64,&x);
	printf("enter a output file name (with .bin) within 50 characters\n");
	scanf("%s",str);
	s[15]=x;
	//for(v=0;v<1000;v++)
	//{
		char ch=0;
		fp = fopen(str, "wb");
		fp1=fopen("results.txt","a+");
		/*for(j=0;j<15;j++)
		{
			s[j]=0;	
		}
		s[15]=rand();
		printf("%d\n",s[15]);*/
		for(i=0;i<n;i++)
		{
			result=next();
			
			t1=result;
			//printf("%"PRIu32"\n",result);
			//fprintf(fp,"%.20lf\n",t);
			bin=(int *)calloc(index,sizeof(int));
			for(k=0;k<index;k++)
			{
				bin[index-k-1]=t1&1;
				t1=t1>>1;
		
			}

			/****** Convert bin[] to store in a character ch ******/
		
			for(k=0;k<index;k++)
			{	
				ch=(ch<<1)|bin[k];
				counter++;
			
				if(counter==8) 
				{
					fprintf(fp,"%c",ch);
					counter=0;
					ch=0;		
				}
			
	 		}
			free(bin);
		}
		fclose(fp);
		passed=0;
		no_test=-1;
		for(i=0;i<20;i++){
			results[i]=0;
			sprintf(pvalues[i],"%s","0");
		}
		diehard("xor1024.bin");
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
		printf("\nDiehard tests passed = %d out of 15\n", passed_combined);
		printf("__________________________________________________________________________________________\n");
		fclose(fp1);
	//}
}

