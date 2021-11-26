/********************The program generates .bin file for Diehard and TestU01 from a seed using xorshift32**********************/
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
static uint32_t y;  /* The state must be seeded with a nonzero value. */
uint32_t xor32()
{
	//static uint32_t y = 2463534242UL;
	y^=(y<<13); y^=(y>>17); 
	return (y^=(y<<15));
}

void main()
{

	int i,n;
	int t1,k,*bin,index,result;
	char str[50];
	uint32_t seed;
	printf("enter the number of terms want to generate\n");
	scanf("%d",&n);
	printf("enter the seed value\n");
	scanf("%u",&seed);
	printf("enter a output file name (with .bin) within 50 characters\n");
	scanf("%s",str);
	FILE *fp;
    	fp = fopen(str, "wb");
	if (fp == NULL) {
        	printf ("File not created!! \n");
	}
	
	y=seed;
	for(i=0;i<n;i++)
	{
		result=xor32();
		printf("%" PRIu32  "\n",result);
		t1=result;
		index=32;
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
	}
	fprintf(fp,"%c",ch);//to print the last less than 8 bits
}
