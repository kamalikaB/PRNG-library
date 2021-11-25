#include<stdio.h>
#include<stdlib.h>
#define SEED 19650218 //123456789
static unsigned int z1 = SEED, z2 = SEED, z3 = SEED, z4 = SEED;
double lfsr113_double (void)
{
   unsigned int b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294UL) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27; 
   z2 = ((z2 & 4294967288UL) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280UL) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168UL) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4) * 2.3283064365386963e-10;
}
main()
{
	
	double x,t,x1,x3;
	int i,j,k,l,n,*bin,index=32,counter=0,x2;
	char ch=0;
        FILE *fp;
    	fp = fopen("lfsr_double_19650218.txt", "w");
	/*printf("how many no you want to generate?\n");
	scanf("%d",&n);*/
n=5000;
	for(i=0;i<n;i++)
	{
		t=lfsr113_double();
		printf("%0.32lf\n",t);
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
		for(k=0;k<index;k++)
		{
			fprintf(fp,"%d",bin[k]);
		}
		fprintf(fp,"\n");
	
	}
	fclose(fp);	
		
}
