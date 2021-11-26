/********************The program generates .bin file for Diehard and TestU01 from a seed using xorshift64STAR**********************/
/*************We have taken n = 1000 for lattice tests and 250 for space time diagram whereas seed values are 7, 1234, 12345, 19650218 and 123456789123456789*******************/
/*********************The same program can be used for NIST by giving n suitably to generate file of size atleast 100 MB**************************/

#include <stdint.h>
#include <inttypes.h>
#include<stdio.h>
#include<stdlib.h>
static FILE *fp;
static int counter=0;
static char ch=0;
uint64_t s[2]={1234};//7
uint64_t next(void) {
	int t,j,n,*bin,index;
	uint64_t s1 = s[0];
	const uint64_t s0 = s[1];
	const uint64_t result = s0 + s1;
	s[0] = s0;
	s1 ^= s1 << 23; // a
	s[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5); // b, c
	printf("%" PRIu64  "\n",result);

	/*editting portion*/

	t=result;
	index=32;
        bin=(int *)calloc(index,sizeof(int));
	for(j=0;j<index;j++)
	{
		bin[index-j-1]=t&1;
		t=t>>1;
		
	}

	/****** Convert bin[] to store in a character ch ******/
		
	for(j=0;j<index;j++)
	{	
		ch=(ch<<1)|bin[j];
		counter++;
			
		if(counter==8) 
		{
			fprintf(fp,"%c",ch);
			counter=0;
			ch=0;		
		}
			
	 } 
	
}

void jump(void) {
	
	static const uint64_t JUMP[] = { 0x8a5cd789635d2dff, 0x121fd2155c472f96 };
	int i,b;
	uint64_t s0 = 0;
	uint64_t s1 = 0;
	for(i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
		for(b = 0; b < 64; b++) {
			if (JUMP[i] & 1ULL << b) {
				s0 ^= s[0];
				s1 ^= s[1];
			}
			//printf("%" PRIu64  "\n",next());
			next();
		}

	s[0] = s0;
	s[1] = s1;
}


main()
{
	int i,n;
	fp = fopen("xor128_seed_1234.bin", "wb");
	printf("enter the n value\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		
		next();
	}
	fprintf(fp,"%c",ch);//to print the last less than 8 bits
}

