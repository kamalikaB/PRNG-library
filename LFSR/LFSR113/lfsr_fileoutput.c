#include<stdio.h>
#include<stdlib.h>
unsigned int lfsr113_Bits (void)
{
   static unsigned int z1 = 19650218, z2 = 19650218, z3 = 19650218, z4 = 19650218;//12345
   unsigned int b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27; 
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}
main()
{
	
	unsigned int z,t;
	
	int i,j,n,*bin,index;
        FILE *fp;
    	fp = fopen("lfsr_int_19650218.txt", "w");
	/*printf("how many no you want to generate?\n");
	scanf("%d",&n);*/
n=5000;
	for(i=0;i<n;i++)
	{
		z=lfsr113_Bits();
		printf("\n random_no=%u",z);
		printf("\n");
		t=z;
		index=32;
		bin=(int *)calloc(index,sizeof(int));
		for(j=0;j<index;j++)
		 {
			bin[index-j-1]=t&1;
			t=t>>1;
		
		 }
		
		for(j=0;j<index;j++){
			fprintf(fp,"%d",bin[j]);
		}
		fprintf(fp,"\n");
		
	}
	
	fclose(fp);
	
}
