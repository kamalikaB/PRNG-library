/********************The program generates numbers in binary form from a seed using MRG31k3p**********************/
/*************We have taken n = 1000 for lattice tests and 250 for space time diagram whereas seed values are 7, 1234, 12345, 19650218 and 123456789123456789*******************/
/*********************The same program can be used for NIST by giving n suitably to generate file of size atleast 100 MB**************************/


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
	int i,j,k,l,n,*bin,index=32,counter=0,x2;
	double x,t,x1,x3;
	unsigned int z;
	char str[50];
	
//n =5000;
//z=19650218;
	printf("enter the number of terms want to generate\n");
	scanf("%d",&n);
	printf("enter the seed value\n");
	scanf("%u",&z);
	printf("enter a output file name within 50 characters\n");
	scanf("%s",str);

	FILE *fp;
    	fp = fopen(str, "w");
    	if (fp == NULL) {
        printf ("File not created!!\n");}
	
	setseed(z);
	for(i=0;i<n;i++)
	{
		t=uniform();
		printf("%.64lf\n",t);
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
		for(j=0;j<index;j++)
		{
			fprintf(fp,"%d",bin[j]);
		}
		fprintf(fp,"\n");
		
	}
	fclose(fp);
}
