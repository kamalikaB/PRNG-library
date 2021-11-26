/*
   64-bits Random number generator U[0,1): lfsr258
   Author: Pierre L'Ecuyer,
   Source: http://www.iro.umontreal.ca/~lecuyer/myftp/papers/tausme2.ps
   ---------------------------------------------------------
*/

#include "lfsr258.h"
#include <stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include <inttypes.h>

/**** VERY IMPORTANT **** :
  The initial seeds y1, y2, y3, y4, y5  MUST be larger than
  1, 511, 4095, 131071 and 8388607 respectively.
****/

#define GERME 123456789123456789

static uint64_t y1 = GERME,
    y2 = GERME, y3 = GERME, y4 = GERME, y5 = GERME;


double lfsr258 (void)
{
   uint64_t b;

   b = ((y1 << 1) ^ y1) >> 53;
   y1 = ((y1 & 18446744073709551614UL) << 10) ^ b;
   b = ((y2 << 24) ^ y2) >> 50;
   y2 = ((y2 & 18446744073709551104UL) << 5) ^ b;
   b = ((y3 << 3) ^ y3) >> 23;
   y3 = ((y3 & 18446744073709547520UL) << 29) ^ b;
   b = ((y4 << 5) ^ y4) >> 24;
   y4 = ((y4 & 18446744073709420544UL) << 23) ^ b;
   b = ((y5 << 3) ^ y5) >> 33;
   y5 = ((y5 & 18446744073701163008UL) << 8) ^ b;
   return (y1 ^ y2 ^ y3 ^ y4 ^ y5) * 5.421010862427522170037264e-20;
}

void main(int argc, char * argv[])
{

//modified for not using jump()

	int i,n,j,k,b,*bin,index=64, x2;
	double seed,result;
	double x,x1,x3;
	//sscanf( argv[2], "%d", &n ) ;
	//sscanf( argv[3], "%" SCNu64  "\n", &seed ) ;
	n =5000;
	//seed=19650218;
	FILE *fp;
	fp = fopen("lfsr258_123456789123456789.txt", "wb");	

	//printf("%d \n",p);
	//printf("%" PRIu64  "\n",s[p]);
    	//fp = fopen(argv[1], "wb");
	for(i=0;i<n;i++)
	{
		result=lfsr258();
		x = result;
		bin=(int *)calloc(index,sizeof(int));
		for(j=0;j<index;j++)
		{
			x1=x*2;
			x2=(int)(x1);
			x3=x1-x2;
			bin[j]=x2;
			x=x3;
		}
		
		for(k=0;k<index;k++)
		{
			fprintf(fp,"%d",bin[k]);
		}
		fprintf(fp,"\n");

		/****** Convert bin[] to store in a character ch ******/
		
		/*for(l=0;l<index;l++)
		{	
			ch=(ch<<1)|bin[l];
			counter++;
			
			if(counter==8)
			{
				fprintf(fp,"%c",ch);
				counter=0;
				ch=0;		
			}
			
		}*/
		free(bin);
		
	}
        fclose(fp);
		
	
}

