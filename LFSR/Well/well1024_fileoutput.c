#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define W 32
#define R 32
#define M1 3
#define M2 24
#define M3 10

#define MAT0POS(t,v) (v^(v>>t))
#define MAT0NEG(t,v) (v^(v<<(-(t))))
#define Identity(v) (v)

#define V0            STATE[state_i                   ]
#define VM1           STATE[(state_i+M1) & 0x0000001fU]
#define VM2           STATE[(state_i+M2) & 0x0000001fU]
#define VM3           STATE[(state_i+M3) & 0x0000001fU]
#define VRm1          STATE[(state_i+31) & 0x0000001fU]
#define newV0         STATE[(state_i+31) & 0x0000001fU]
#define newV1         STATE[state_i                   ]

#define FACT 2.32830643653869628906e-10

static unsigned int state_i = 0;
static unsigned int STATE[R];
static unsigned int z0, z1, z2;
static FILE *fp;
static int counter=0;
static char ch=0;
//int bin[64];

/*unsigned int a[]={0xDE410B75, 0x904FA5C7, 0x8BD4701E, 0x011EA361,
         0x6EB189E0, 0x7A2B0CE1, 0xE02631CA, 0x72EBA132,
         0x5189DA0F, 0x3EB72A2C, 0x51ABE513, 0x6D9EA57C,
         0x4D690BF1, 0x84217FCA, 0x7290DE1A, 0x429F5A48,
         0x6EC42EF3, 0x960AB315, 0x72C3A743, 0x48E13BF1,
         0x8917EAC8, 0x284AE026, 0x357BF240, 0x913B51AC,
         0x136AF195, 0x361ABC18, 0x731AB725, 0x63D3A7C9,
         0xE5F32A18, 0x91A8E164, 0x04EA61B5, 0xC72A6091};ORIGINAL SEED*/

unsigned int a[]={0x12BD6AA,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0};


void InitWELLRNG1024a (unsigned int *init){
   int j;
   state_i = 0;
   for (j = 0; j < R; j++)
     STATE[j] = init[j];
}

double WELLRNG1024a (void){
  z0    = VRm1;
  z1    = Identity(V0)       ^ MAT0POS (8, VM1);
  z2    = MAT0NEG (-19, VM2) ^ MAT0NEG(-14,VM3);
  newV1 = z1                 ^ z2; 
  newV0 = MAT0NEG (-11,z0)   ^ MAT0NEG(-7,z1)    ^ MAT0NEG(-13,z2) ;
  state_i = (state_i + 31) & 0x0000001fU;
  return ((double) STATE[state_i]  * FACT);
}


void main(int argc, char * argv[])
{
	int n,j,k,i,index=32,*bin;
	double x,t,x1,x3;
	unsigned int seed, x2;

	/*sscanf( argv[2], "%d", &n ) ;
	sscanf( argv[3], "%u", &seed ) ;

	fp = fopen(argv[1], "wb");*/
n = 5000;
seed = 123456789123456789;

	FILE *fp;
    fp = fopen("well1024_123456789123456789.txt", "wb");
	a[0]=seed;

	InitWELLRNG1024a(a);
	
	for(k=0;k<n;k++)
	{
		bin=(int *)calloc(index,sizeof(int));
		t=WELLRNG1024a();
		printf("%.32lf\n",t);
		x=t;
	   		/*convert double to bit*/
		for(i=0;i<index;i++)
		{
			x1=x*2;
			x2=(int)(x1);
			x3=x1-x2;
			bin[i]=x2;
			x=x3;
						
		}
		for(j=0;j<index;j++)
		{
			fprintf(fp,"%d",bin[j]);
		}
		fprintf(fp,"\n");

	}

	fclose(fp);
}



