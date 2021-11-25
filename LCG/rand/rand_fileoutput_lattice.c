/********************The program generates numbers in binary form from a seed using GNU rand**********************/
/*************This is a sample code to generate normalized numbers for lattice test***********************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int i,j,n,*bin,index,counter=0,z;
	double t, number;
	char ch=0;
	char str[50];
	long max = pow(2, 32)-1;
	printf("%l",max);
	printf("enter the number of terms want to generate\n");
	scanf("%d",&n);
	printf("enter the seed value\n");
	scanf("%u",&z);
	printf("enter a output file name within 50 characters\n");
	scanf("%s",str);
	FILE *fp;
    	fp = fopen(str, "wb");
	if (fp == NULL) {
        printf ("File not created!! \n");
	}
	
	srand(z);
	for(i=0;i<n;i++)
	{
		number=rand();
		t=number/max;
		fprintf(fp,"%0.64lf\n",t);
		printf("%lf\n",t);
	}

	fclose(fp);
	
	
}
