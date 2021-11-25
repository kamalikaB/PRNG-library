/********************The program generates numbers in binary form from a seed using GNU lrand48**********************/
/*************We have taken n = 1000 for lattice tests and 250 for space time diagram whereas seed values are 7, 1234, 12345, 19650218 and 123456789123456789*******************/
/*********************The same program can be used for NIST by giving n suitably to generate file of size atleast 100 MB**************************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int i,j,k,n,*bin,index,counter=0;
	char ch=0;
	long int number,t,z;
	char str[50];
	
	printf("enter the number of terms want to generate\n");
	scanf("%d",&n);
	printf("enter the seed value\n");
	scanf("%ld",&z);
	printf("enter a output file name within 50 characters\n");
	scanf("%s",str);
	FILE *fp;
    	fp = fopen(str, "wb");
	if (fp == NULL) {
        printf ("File not created!! \n");
	}
	srand48(z);


	for(k=0;k<n;k++)
	{
		number=lrand48();
		printf("%ld\n",number);
		t=number;
		//printf("\n");
		index=32;
		bin=(int *)calloc(index,sizeof(int));
		for(j=0;j<index;j++)
		 {
			bin[index-j-1]=t&1;
			t=t>>1;
		 }

		for(j=0;j<index;j++)
		{
			fprintf(fp,"%d",bin[j]);
		}
		fprintf(fp,"\n");

	}

	fclose(fp);
	
	
}
