/********************The program generates .bin file for Diehard and TestU01 from a seed using xorshift64STAR**********************/
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
uint64_t x; /* The state must be seeded with a nonzero value. */
uint64_t xorshift64star(void) 
{
	x ^= x >> 12; // a
        x ^= x << 25; // b
        x ^= x >> 27; // c
        return x * 2685821657736338717LL;
}

void main()
{

	int i,n;
	int k,*bin,index;
	uint64_t t1, result;
	char str[50];
	printf("enter the number of terms want to generate\n");
	scanf("%d",&n);
	printf("enter the seed value\n");
	scanf("%" SCNu64,&x);
	printf("enter a output file name (with .bin) within 50 characters\n");
	scanf("%s",str);
	FILE *fp;
    	fp = fopen(str, "wb");
	if (fp == NULL) {
        	printf ("File not created!! \n");
	}
	for(i=0;i<n;i++)
	{
		result=xorshift64star();
		//printf("%" PRIu64  "\n",result);
		t1=result;
		index=64;
        	bin=(int *)calloc(index,sizeof(int));
		for(k=0;k<index;k++)
		{
			bin[index-k-1]=t1&1;
			t1=t1>>1;
		
		}
		
		/*****************For printing binary numbers in any file use the following********************************/
		/*
		for(j=0;j<index;j++){
			fprintf(fp,"%d",bin[j]);
		}
		fprintf(fp,"\n");
		*
		******************************************************/

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
