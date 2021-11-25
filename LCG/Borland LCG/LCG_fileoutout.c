/********************The program generates numbers in binary form from a seed using Borland's LCG**********************/
/*************We have taken n = 1000 for lattice tests and 250 for space time diagram whereas seed values are 7, 1234, 12345, 19650218 and 123456789123456789*******************/
/*********************The same program can be used for NIST by giving n suitably to generate file of size atleast 100 MB**************************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main()
{
	unsigned long a=22695477,c=1,m=pow(2,32),z,t;
	int i,j,n,*bin,index;
	float u,k,l;
	
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
	for(i=0;i<n;i++)
	{
		z=((a*z)+c)%m;
		u=(float)z/m;
		t=z;
		printf("\n %ld  ",z);
		//printf("\n");
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
