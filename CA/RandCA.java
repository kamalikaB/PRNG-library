package randomness;

import java.util.Arrays;

public class RandCA {
	/*****************PORTABLE JAVA CODE TO GENERATE ANY BIT NUMBER******************/

	int n = 51, window=0, i,j;
	char Rule[] = {'0','1','2','1','2','0','1','2','0','0','2','1','1','2','0','1','2','0','0','2','1','1','2','0','0','2','1'};
	
	char PS[],NS[];
	
	void srandCA(int size, String seed)
	{
		window = (10*size)/16;
		n=(int) (window*2.5);
		if(n%2==0)
			n=n+1;
		char[] seedTri=new char[window];
		seedTri=toTrinary(seed, window); //converts to a trinary number
		
		System.out.println(Arrays.toString(seedTri));
		
		PS = new char[n];
		NS = new char[n];
		
		for(i=0;i<window;i++) //initialize window	
			PS[i]=seedTri[i];
		for(i=window;i<n-1;i++)//initialize other values to 000...001
			PS[i]='0'; 
		PS[n-1]='1';
		
		/****Generate first n configurations****/
		for (j=0;j<n;j++){
			NS[0] = Rule[9*(PS[n-1]-48)+3*(PS[0]-48)+(PS[1]-48)];  // next state for left most cell
			for(i=1;i<n-1;i++)
			{
				NS[i] = Rule[9*(PS[i-1]-48)+3*(PS[i]-48)+(PS[i+1]-48)];
			}
			NS[n-1] = Rule[9*(PS[n-2]-48)+3*(PS[n-1]-48)+(PS[0]-48)]; // next state for right most cell
			
			
			for(i=0;i<n;i++){
				PS[i] = NS[i];
			}
		}
		
		
	}

	String randCA(){
					
		NS = new char[n];
		System.out.println(Arrays.toString(PS));

		NS[0] = Rule[9*(PS[n-1]-48)+3*(PS[0]-48)+(PS[1]-48)];  // next state for left most cell
		for(i=1;i<n-1;i++)
		{
			NS[i] = Rule[9*(PS[i-1]-48)+3*(PS[i]-48)+(PS[i+1]-48)];
		}
		NS[n-1] = Rule[9*(PS[n-2]-48)+3*(PS[n-1]-48)+(PS[0]-48)]; // next state for right most cell
		
		
		for(i=0;i<n;i++){
				PS[i] = NS[i];
		}
		System.out.println(Arrays.toString(PS));
		return toDecimal(PS,window);

	}

	char[] toTrinary(String seed, int window)
	{
		char[] tri=new char[window];
		int dc=0;
		dc=Integer.parseInt(seed);
		for(i=0;i<window;i++){
			tri[i]='0';
		}
		i=window-1;
		while ( i>= 0 )
	    	{
	       		tri[i--] = Character.forDigit(dc % 3,10) ;  
	       		dc = dc / 3 ;  
	       	}
		return tri;
	}

	String toDecimal(char[] number, int window)
	{
		int dc=0,index=1;
		for(i=0;i<window;i++) //Decimal Value
		{
			dc+=(number[window-1-i]-48)*index;
	        index*=3;
		}
		
	return Integer.toString(dc);
	}

	
}
