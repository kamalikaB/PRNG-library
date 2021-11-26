/********************************This program generates random STRATEGY II SEMIREVERSIBLE RULES THAT FOLLOWS A SIMPLE PERMUTATION***************
 */

//package randomness.decimalCA;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Set;

import javax.swing.JOptionPane;

//import dStateReversiblityComplexity.PermuteString;
//import sufficientCellLength.CopyCheckReversibilityForAllCell;


/**
 * @author kamalika
 *
 */
public class DecimalCAPRNGFromGivenPermutation {
	int n;
	int d = 10;
	int window;
	int seedDeci[] = new int[window];
	int noRMTs = d*d*d;
	int Rule[]= new int [noRMTs];
	int[] PC; // to store present configuration
	int[] NC; // to store next configuration

	static String shiftLeftRule(int k, String ruleString){ //right shift rule segments k times
		String shiftRule = ruleString.substring(k)+ruleString.substring(0,k);
	//	System.out.println(k+" time left shift of "+ruleString+" is "+shiftRule);
		return shiftRule;
	}
	
	private int[] splitDigits(long seed, int window, int base) {
		// TODO Auto-generated method stub
		seedDeci = new int[window];
		String seedStr = Long.toString(seed);
		/*
		 * int j=window-1; for( int i = seedStr.length()-1; i>=0; i--){
		 * 
		 * seedDeci[j--] = Integer.parseInt(String.valueOf(seedStr.charAt(i))); }
		 */
		int j=seedStr.length()-1;
		for( int i = window-1; i>=0 && j>=0; i--){
				
			seedDeci[i] = Integer.parseInt(String.valueOf(seedStr.charAt(j--)));
		}
		return seedDeci;
	}
	
	public String DecToBin(String decS) {
		int len = decS.length();
		char[] deci = new char[len];
		for(int i=0;i<len;i++) {
			deci[i]=decS.charAt(i);
			//System.out.print(deci[i]);
		}
		
		String bin = new String();
		Boolean flag=false;
		do {
			flag=false;
			int carry=0;
			char[] div = new char[len];
			for(int i=0;i<len;i++) {
				int temp = 10*carry+Character.getNumericValue(deci[i]);
			//	System.out.println(temp);
				if(temp%2==0) {
					carry=0;
				}
				else
					carry=1;
				div[i]= (char) ((temp/2)+'0');
				if(temp/2!=0)
					flag=true;
			}
			bin=carry+bin;
			String out = new String(div);
		//	System.out.println("Carry = "+carry+"\n Dividend = "+out+"\n binary = "+bin);
			for (int i=0;i<len;i++) {
				deci[i]=div[i];
			//	System.out.print("New value = "+deci[i]);
			}
		}while(flag);
	//	System.out.println("binary = "+bin);
		return bin;
	}

	public void srandCA ( long seed ) { // Takes a decimal string as seed
		int i;
		seedDeci = splitDigits ( seed , window , 10) ; // To array of digits
		
		for (i =0; i < window ; i ++)		// initialize window
			PC [ i ]= seedDeci [ i ];
		for ( i = window ;i <n -1; i ++) { // initialize other values to 0...01
			PC [ i ]=0;
			PC [n -1]=1;
		}
		
		//////////////Testing///////////////////
		for(i=0;i<window;i++)
			System.out.print(PC[i]);
		System.out.println();
		
		for ( int j =0; j < n ; j ++) { // leave first n configurations
			for ( i =0; i < n ; i ++)
				NC [ i ] = Rule[100* PC [( i -1+ n ) % n ]+10* PC [ i ]+ PC [( i +1+ n ) % n ]];
			for ( i =0; i < n ; i ++)
				PC [ i ] = NC [ i ];		// update PC [] to use again
		}
		
		/*
		 * //////////////Testing/////////////////// for(i=0;i<window;i++)
		 * System.out.print(PC[i]); System.out.println();
		 */
	}
	/*
	 * public void srandCABin ( int b, int seed ) { // Takes size of output number
	 * as 32* b bits , a decimal string as seed window = (14* b ) ; // set window
	 * size n =( int ) (100* b +1) ; // set CA size seedDeci = splitDigits ( seed ,
	 * window, 10 ) ; // To array of digits int i; PC = new int[n]; // to store
	 * present configuration NC = new int[n]; // to store next configuration for ( i
	 * =0; i < window ; i ++) // initialize window PC [ i ]= seedDeci [ i ]; for (i
	 * = window ;i <n -1; i ++){// initialize other values to 0...01 PC [ i ]=0; PC
	 * [n -1]=1; }
	 * 
	 * //////////////Testing/////////////////// for(i=0;i<window;i++)
	 * System.out.print(PC[i]); System.out.println();
	 * 
	 * for ( int j =0; j < n ; j ++) { // leave first n configurations for ( i =0; i
	 * < n ; i ++) NC [ i ] = Rule[100* PC [( i -1+ n ) % n ]+10* PC [ i ]+ PC [( i
	 * +1+ n ) % n ]]; for ( i =0; i < n ; i ++) PC [ i ] = NC [ i ]; // update PC
	 * [] to use again }
	 * 
	 * 
	 * //////////////Testing/////////////////// for(i=0;i<window;i++)
	 * System.out.print(PC[i]); System.out.println();
	 * 
	 * }
	 */
	
	/*
	 * public void srandCA ( int window , int seed ) { // Takes size of output
	 * number in digits as window , a decimal string as seed int i; seedDeci =
	 * splitDigits ( seed , window , 10) ; // To array of digits PC = new int[n]; //
	 * to store present configuration NC = new int[n]; // to store next
	 * configuration
	 * 
	 * for (i =0; i < window ; i ++) // initialize window PC [ i ]= seedDeci [ i ];
	 * for ( i = window ;i <n -1; i ++) { // initialize other values to 0...01 PC [
	 * i ]=0; PC [n -1]=1; }
	 * 
	 * //////////////Testing/////////////////// for(i=0;i<window;i++)
	 * System.out.print(PC[i]); System.out.println();
	 * 
	 * for ( int j =0; j < n ; j ++) { // leave first n configurations for ( i =0; i
	 * < n ; i ++) NC [ i ] = Rule[100* PC [( i -1+ n ) % n ]+10* PC [ i ]+ PC [( i
	 * +1+ n ) % n ]]; for ( i =0; i < n ; i ++) PC [ i ] = NC [ i ]; // update PC
	 * [] to use again }
	 * 
	 * //////////////Testing/////////////////// for(i=0;i<window;i++)
	 * System.out.print(PC[i]); System.out.println(); }
	 */
	public String randCABin (int b) {	/* * Generates pseudo - random number in binary* */
		int i;
		for ( i =0; i < n ; i ++)
			NC [ i ] = Rule [100* PC [( i -1+ n ) % n ]+10* PC [ i ]+ PC [( i +1+ n ) % n ]];
		for ( i =0; i < n ; i ++)
			PC [ i ] = NC [ i ];		// update PC [] to use again
		
		String number = extractNumber (PC , window) ; // extract decimal number for window
		/*
		 * long numberBin = (long) ((long) Long.parseLong(number)%Math.pow (2,32*b )); String
		 * stringWord = Long.toBinaryString(numberBin);
		 * 
		 * while (stringWord.length() < 32*b) // ensure that length of word is 32*b
		 * stringWord = "0" + stringWord;
		 */
		String stringWord = DecToBin(number);
		if(stringWord.length()>32*b) {
			stringWord = stringWord.substring(stringWord.length()-32*b, stringWord.length());
		}
		return stringWord;
		}
	

	public String randCA () {	/* * Generates psudo - random number in decimal * */
		int i;
		for ( i =0; i < n ; i ++)
			NC [ i ] = Rule [100* PC [( i -1+ n ) % n ]+10* PC [ i ]+ PC [( i +1+ n ) % n ]];
		for ( i =0; i < n ; i ++)
			PC [ i ] = NC [ i ];		// update PC [] to use again
		
		/*
		 * //////////////Testing/////////////////// for(i=0;i<window;i++)
		 * System.out.print(PC[i]); System.out.println();
		 */
		
		return extractNumber (PC, window) ; // return decimal number corresponding to the window
	}
	
	private String extractNumber(int[] PC, int window) {
		// TODO Auto-generated method stub
		int i;
		String number="";
		for (i=0; i<window;i++)
			number+=PC[i];
		//System.out.println(number);
		return number;
	}
	public DecimalCAPRNGFromGivenPermutation(String ruleStringSegment, int b, long seed){ //initialization and calling of srandCABin
	
		String ruleString = new String();
		String[] sibl = new String[d*d];
	    sibl[0]=ruleStringSegment;
	    for(int i=1;i<d;i++){
	    	sibl[i]= shiftLeftRule(i,ruleStringSegment);
	    }
	    
	    for(int i=10;i<d*d;i++){
	    	if(i%11!=0)
	    		sibl[i]=shiftLeftRule((i/d),sibl[i%d]);
	    	else
	    		sibl[i]=sibl[0];
	    }
	   
	    int j=0;
	    for(int i=0;i<d;i++){
	    	for(j=i+1;j<d;j++){
	    		int k =i*d+j;
	    		int l= j*d+i;
	    		if(k%11==0)
	    			sibl[l]=sibl[k];
	    		else if(l%11==0)
	    			sibl[k]=sibl[l];
	    		else
	    			sibl[l]=sibl[k];
	    	}
	    }
			    
	    for( j=d*d-1;j>=0;j--){
	    	ruleString +=sibl[j];
		}
			    
		System.out.println("The rule is "+ruleString);
		j=0;
		for( int i = noRMTs-1; i>=0; i--){
				
			Rule[j++] = Integer.parseInt(String.valueOf(ruleString.charAt(i))); // if rule is valid , stores it into integer array
		}  
		
		
		window = (14* b ) ; // set window* size 
		n =( int ) (100* b +1) ; // set CA size for binary
		
		PC = new int[n];
	    NC = new int[n];
	    srandCA(seed);
		
	}	
	public DecimalCAPRNGFromGivenPermutation(String ruleStringSegment, long seed){//initialization and calling of srandCA for DECIMAL
		
		String ruleString = new String();
		String[] sibl = new String[d*d];
	    sibl[0]=ruleStringSegment;
	    for(int i=1;i<d;i++){
	    	sibl[i]= shiftLeftRule(i,ruleStringSegment);
	    }
	    
	    for(int i=10;i<d*d;i++){
	    	if(i%11!=0)
	    		sibl[i]=shiftLeftRule((i/d),sibl[i%d]);
	    	else
	    		sibl[i]=sibl[0];
	    }
	   
	    int j=0;
	    for(int i=0;i<d;i++){
	    	for(j=i+1;j<d;j++){
	    		int k =i*d+j;
	    		int l= j*d+i;
	    		if(k%11==0)
	    			sibl[l]=sibl[k];
	    		else if(l%11==0)
	    			sibl[k]=sibl[l];
	    		else
	    			sibl[l]=sibl[k];
	    	}
	    }
			    
	    for( j=d*d-1;j>=0;j--){
	    	ruleString +=sibl[j];
		}
			    
		System.out.println("The rule is "+ruleString);
		j=0;
		for( int i = noRMTs-1; i>=0; i--){
				
			Rule[j++] = Integer.parseInt(String.valueOf(ruleString.charAt(i))); // if rule is valid , stores it into integer array
		}  
		
		window = Integer.parseInt(JOptionPane.showInputDialog("Enter the number of digits of the output number"));

		n =( int ) (( window /10+1) *100+1) ;	// set CA size for Decimal
		PC = new int[n];
	    NC = new int[n];
	   		
	    srandCA(seed);
	}	
}
