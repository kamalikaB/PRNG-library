/********************The program generates .bin file for Diehard and TestU01 from a seed using Knuth's LCG MMIX**********************/
/*************We have taken n = 1000 for lattice tests and 250 for space time diagram whereas seed values are 7, 1234, 12345, 19650218 and 123456789123456789*******************/
/*********************The same program can be used for NIST by giving n suitably to generate file of size atleast 100 MB**************************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main()
{
	unsigned long long int m=pow(2,64);
	uint64_t a=6364136223846793005,c=1442695040888963407,z,t;
	int i,j,n,*bin,index,counter=0;
	float u,k,l;
	char ch=0;
	char str[50];

	printf("enter the number of terms want to generate\n");
	scanf("%d",&n);
	printf("enter the seed value\n");
	scanf("%u",&z);
	printf("enter a output file name (with .bin) within 50 characters\n");
	scanf("%s",str);
	FILE *fp;
    	fp = fopen(str, "wb");
	if (fp == NULL) {
        printf ("File not created!! \n");
	}
	for(i=0;i<n;i++)
	{
		z=((a*z)+c)%m;
		//u=(float)z/m;
		t=z;
		//printf("%" PRIu64  "\n",z);
		//printf("\n");
		index=64; //64 bit number
		bin=(int *)calloc(index,sizeof(int));
		for(j=0;j<index;j++)
		 {
			bin[index-j-1]=t&1;
			t=t>>1;
		 }

		/*for(j=0;j<index;j++){
			printf("%d",bin[j]);
		}
		printf("\n");*/
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
	
}
