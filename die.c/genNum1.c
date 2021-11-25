#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define n 10000
#define d 10
#define neighbor 3
#define size 12
#define index 32
int i;
int main()
{
	int a=0,j=0,ps[n],ns[n],number[size],m,l,k=0,rn,*bin,counter=0;
	long number1=0, t=0;
char*rule1="9402568173903148672595247106388162495730795246308104159862378425763910263187509443862105972170648935723984560174286103956490187235209615384715236890740716932854395786014254132067989542016837260891457305687293142914567803192734860518594732069132465780540169723853462108791259486073735689102486721309548697431025736812409583694015279680572134503796841296735812401072398564617509284367420531980325798416294765318054627093183921786504492651738059347208162094658173941360528775390486215849137602523407816921038675490698475132926745831002591368479018352647261703598447162598301705683924716325094824503961787809265143729156834087506392411472805369524873106928317045690614598732259864713023741659086587129403981075623473869051243270861495238971465083549621707961524308498520361739421605873102657894853401926745802796316274539180127485063903768945129653210487093524617896023475185890273146407532861934672810597935048216589421306775619832408340671592421708639573458016296534712089491580372609417263858435120976";
	FILE *fp;
	//printf("%c\n",rule1[5]);
	char ch=0;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		rn=rand();
		rn=rn%d;	
		ps[i]=rn;
		//printf("ps[%d]=%d",i,ps[i]);

	}
	
	m=3010656;
	//printf("enter how many number you  want to generate\n");
	//scanf("%d",&m);
	
    	fp = fopen("ca_gen_no101.bin", "wb");
	for(l=0;l<m;l++)
	{
		for(i=0;i<n;i++)
		{
			if(i==0)
			{
				a=ps[n-1]*pow(d,neighbor-1)+ps[0]*pow(d,neighbor-2)+ps[1];
			}
			else if(i==(n-1))
			{
				a=ps[0]+ps[n-1]*pow(d,neighbor-2)+ps[n-2]*pow(d,neighbor-1);
			}
			else 
			{
				a=ps[i-1]*pow(d,neighbor-1)+ps[i]*pow(d,neighbor-2)+ps[i+1];
			}


			//printf("\ni=%d	a=%d\n",i,a);
			ns[i]=rule1[999-a]-48;
			//printf("ps[%d] %d  %c\n",i-1,a,rule1[999-a]);	
		}
		/*for(i=0;i<n;i++)
			printf("%d",ns[i]);
		printf("\n");*/

		k=0;
		for(j=(n/2-size/2);j<(n/2+size/2);j++)/*collect random number*/
		{
			number[k]=ns[j];
			//printf("%d",number[k]);
			number1=number1+number[k]*pow(d,size-k-1);
			k++;
		}
		//printf("\nk=%d\n",k);
		t=number1;
		number1=0;
		for(j=0;j<n;j++)
		{
			ps[j]=ns[j];
		
		}
		//printf("\t%lu\n",t);
		//fprintf(fp,"%lu\n",t);
		bin=(int *)calloc(index,sizeof(int));
		for(j=0;j<index;j++)
		 {
			bin[index-j-1]=t&1;
			t=t>>1;
		
		 }
		
		/****** Convert bin[] to store in a character ch ******/
		
		for(j=0;j<index;j++)
		{	
			ch=(ch<<1)|bin[j];
			counter++;
			
			if(counter==8) 
			{
				fprintf(fp,"%c",ch);
				counter=0;
				ch=0;		
			}
			
		}
	}
	fprintf(fp,"%c",ch);
	fclose(fp);

	return 0;
}
