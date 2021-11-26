/********************The program generates numbers in binary form from a seed using xorshift128+**********************/
/*************We have taken n = 1000 for lattice tests and 250 for space time diagram whereas seed values are 7, 1234, 12345, 19650218 and 123456789123456789*******************/
/*********************The same program can be used for NIST by giving n suitably to generate file of size atleast 100 MB**************************/

#include <stdint.h>
#include <inttypes.h>
#include<stdio.h>
#include<stdlib.h>
static FILE *fp;
static int counter=0;
static char ch=0;
uint64_t s[2];
uint64_t next(void) {
	int t,j,n,*bin,index;
	uint64_t s1 = s[0];
	const uint64_t s0 = s[1];
	const uint64_t result = s0 + s1;
	s[0] = s0;
	s1 ^= s1 << 23; // a
	s[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5); // b, c
	printf("%" PRIu64  "\n",result);

	return result;
	
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


void main(int argc, char * argv[])
{

	int i,j,n,*bin,index=64;
	uint64_t seed,result,t;
	//sscanf( argv[2], "%d", &n ) ;
	//sscanf( argv[3], "%" SCNu64  "\n", &seed ) ;
	
	FILE *fp;
    	//fp = fopen(argv[1], "wb");

n =5000;
seed=19650218;
fp = fopen("xorshift_19650218.txt", "wb");
	s[0]=0;
	s[1]=seed;
	

	for(i=0;i<n;i++)
	{
		
		result = next();
		//printf("%" PRIu64  "\n",result);
		t=result;
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

