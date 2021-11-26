/********************The program generates numbers in binary form from a seed using xorshift32**********************/
/*************We have taken n = 1000 for lattice tests and 250 for space time diagram whereas seed values are 7, 1234, 12345, 19650218 and 123456789123456789*******************/
/*********************The same program can be used for NIST by giving n suitably to generate file of size atleast 100 MB**************************/


#include <stdint.h>
#include <inttypes.h>
#include<stdio.h>
#include<stdlib.h>
//uint64_t state[static 1]
static FILE *fp;
static int counter=0;
static char ch=0;
static uint32_t y; /* The state must be seeded with a nonzero value. */
uint32_t xor32()
{
	//static uint32_t y = 2463534242UL;
	y^=(y<<13); y^=(y>>17); 
	return (y^=(y<<15));
}

void main(int argc, char * argv[])
{

	int i,n,k;
	int t1,*bin,index=32,result;
	uint32_t seed;
	char str[50];

	printf("enter the number of terms want to generate\n");
	scanf("%d",&n);
	printf("enter the seed value\n");
	scanf("%u",&seed);
	printf("enter a output file name within 50 characters\n");
	scanf("%s",str);
	FILE *fp;
    	fp = fopen(str, "wb");
	if (fp == NULL) {
        	printf ("File not created!! \n");
	}
//n =5000;
//seed=19650218;
//fp = fopen("xor32_19650218.txt", "wb");
	y=seed;
	for(i=0;i<n;i++)
	{
		result=xor32();
		printf("%" PRIu32  "\n",result);
		t1=result;
		
        	bin=(int *)calloc(index,sizeof(int));
		for(k=0;k<index;k++)
		{
			bin[index-k-1]=t1&1;
			t1=t1>>1;
		
		}

		for(k=0;k<index;k++)
		{
			fprintf(fp,"%d",bin[k]);
		}
		fprintf(fp,"\n");

	}

	fclose(fp);
}
