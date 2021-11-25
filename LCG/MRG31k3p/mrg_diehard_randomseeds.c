
/********************The program is to test MRG31k3p for Diehard by generating .bin file from 1000 random seeds collected from rand**********************/
/*****************************************************************************
 *   this file: uniform.c                                                    *
 *                                                                           *
 *   CODE taken from UNURAN FILE: mrg31k3p.c                                 *
 *                                                                           *
 *   PURPOSE:                                                                *
 *         uniform random number generator provided by UNURAN                *
 *         random number generators inside UNURAN.                           *
 *                                                                           *
 *   DESCRIPTION:                                                            *
 *         Combined multiple recursive generator.                            *
 *         The two components of the generator are                           *
 *                                                                           *
 *   x_{1,k}  = (2^{22} x_{1,k-2} + (2^7 +1)x_{1,k-3}) mod (2^{31}-1)        *
 *   x_{2,k}  = (2^{15} x_{2,k-1} + (2^{15} +1)x_{2,k-3} mod (2^{31}-21069)  *
 *                                                                           *
 *         x_{1,k} and x_{2,k} are combined together and the result is       *
 *         multiplied by 1/(2^{31}-1) to have a number between 0 and 1.      *
 *                                                                           *
 *   REFERENCE:                                                              *
 *   L'Ecuyer, P. and R. Touzin (2000): Fast Combined Multiple Recursive     *
 *      Generators with Multipliers of the Form a = ±2^q±2^r.                *
 *      in: J.A. Jones, R.R. Barton, K. Kang, and P.A. Fishwick (eds.),      *
 *      Proc. 2000 Winter Simulation Conference, 683-689.                    *
 *                                                                           *
 *   Copyright for generator code by Renee Touzin.                           * 
 *                                                                           *
 *****************************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*****************************To test using Diehard*************************/
#include "die.c"

int passed=0;
int results[20],i;
char pvalues[20][10];
int no_test=-1;
void diehard(char *);

/***********************************************************************/
static FILE *fp,*fp1;

/* seed (must not be 0!) */
#define SEED10  (12345L)
#define SEED11  (23456L)
#define SEED12  (34067L)
#define SEED20  (45678L)
#define SEED21  (56789L)
#define SEED22  (67890L)

/* status variable */
static unsigned long x10 = SEED10;
static unsigned long x11 = SEED11;
static unsigned long x12 = SEED12;
static unsigned long x20 = SEED20;
static unsigned long x21 = SEED21;
static unsigned long x22 = SEED22;

/* seed of last stream */
static unsigned long x10_start = SEED10;
static unsigned long x11_start = SEED11;
static unsigned long x12_start = SEED12;
static unsigned long x20_start = SEED20;
static unsigned long x21_start = SEED21;
static unsigned long x22_start = SEED22;

/*---------------------------------------------------------------------------*/

double
uniform(void)
     /* Combined multiple recursive generator.                               */
     /* Copyright (c) 2002 Renee Touzin.                                     */
{

# define m1      2147483647
# define m2      2147462579
# define norm    4.656612873077393e-10
# define mask11  511
# define mask12  16777215
# define mask20  65535
 

  register unsigned long y1, y2;  /* For intermediate results */
  
  /* First component */
  y1 = ( (((x11 & mask11) << 22) + (x11 >> 9))
	 + (((x12 & mask12) << 7)  + (x12 >> 24)) );
  if (y1 > m1) y1 -= m1;
  y1 += x12;
  if (y1 > m1) y1 -= m1;
  x12 = x11;  x11 = x10;  x10 = y1;
 
  /* Second component */
  y1 = ((x20 & mask20) << 15) + 21069 * (x20 >> 16);
  if (y1 > m2) y1 -= m2;
  y2 = ((x22 & mask20) << 15) + 21069 * (x22 >> 16);
  if (y2 > m2) y2 -= m2;
  y2 += x22;
  if (y2 > m2) y2 -= m2;
  y2 += y1;
  if (y2 > m2) y2 -= m2;
  x22 = x21;  x21 = x20;  x20 = y2;

  /* Combination */
  if (x10 <= x20)
    return ((x10 - x20 + m1) * norm);
  else 
    return ((x10 - x20) * norm);

} /* end of unif() */
 
/*---------------------------------------------------------------------------*/

int
setseed (long seed)
{
  if (seed==0) {
    printf("ERROR in setseed!! A seed of 0 is not possible; seed not changed!!");
    return 0;
  }
  
  /* the following is not really optimal */
  x10 = x10_start = seed; 
  x11 = x11_start = seed; 
  x12 = x12_start = seed; 
  x20 = x20_start = seed; 
  x21 = x21_start = seed; 
  x22 = x22_start = seed; 

  return 1;
} /* end of setseed() */

/*---------------------------------------------------------------------------*/

int 
resetseed (void)
{
  x10 = x10_start;
  x11 = x11_start;
  x12 = x12_start;
  x20 = x20_start;
  x21 = x21_start;
  x22 = x22_start;

  return 1;
} /* end of resetseed() */

/*---------------------------------------------------------------------------*/
void main()
{
	srand(0); //start with this
	int i,j,k,l,n,*bin,index=32,counter=0,x2,v;
	double x,t,x1,x3;
	long seed;
	n = 2600000; // This is set for 10.5 MB file
	for(v=0;v<1000;v++) //generate 1000 numbers using rand
	{
		seed = rand();
		printf("%lu\n",seed);

		fp = fopen("mrg_32.bin", "w");
		fp1=fopen("output_mrg_32.csv","a+");
		char ch=0;
	
		setseed(seed);
		counter=0;
	
		for(i=0;i<n;i++)
		{
			t=uniform();
		//printf("%.64lf\n",t);
			x=t;
			bin=(int *)calloc(index,sizeof(int));
			for(j=0;j<index;j++)
			{
				x1=x*2;
				x2=(int)(x1);
			//printf("%0.32lf\n",x2);
				x3=x1-x2;
				bin[j]=x2;
				x=x3;
			//printf("%.32lf\t %d\n",x3, x2);
			
			}
		
		
		/****** Convert bin[] to store in a character ch ******/
		
			for(j=0;j<index;j++)
			{	
				ch=(ch<<1)|bin[j];
				counter++;
			
				if(counter==7)
				{
					fprintf(fp,"%c",ch);
					counter=0;
					ch=0;		
				}
			
			}

		}
		fprintf(fp,"%c",ch);
		fclose(fp);
		
		/********************************Diehard result compilation***************************/
		passed=0;
		no_test=-1;
		for(i=0;i<20;i++){
			results[i]=0;
			sprintf(pvalues[i],"%s","0");
		}
		diehard("mrg_32.bin");
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
		fflush(fp1);
		printf("\nDiehard tests passed = %d out of 15\n", passed_combined);
		printf("__________________________________________________________________________________________\n");
 		fclose(fp1);
	}

}
