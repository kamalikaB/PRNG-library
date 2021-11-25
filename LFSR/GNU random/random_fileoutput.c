#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int i,j,n,*bin,index,counter=0;
	unsigned long int number,t;
	srandom(19650218);
	FILE *fp;
	fp = fopen("random_32_19650218.txt", "w");

	/*printf("enter the term value y want to generate\n");
	scanf("%d",&n);*/

n=5000;

	for(i=0;i<n;i++)
	{
		number=random();
		printf("%ld\n",number);
		t=number;
		printf("\n");
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
