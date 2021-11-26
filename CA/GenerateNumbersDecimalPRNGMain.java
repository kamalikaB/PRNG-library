//package randomness.decimalCA;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JOptionPane;

public class GenerateNumbersDecimalPRNGMain {
	public static void main(String [] args){
		String ruleStringSegment = JOptionPane.showInputDialog("Enter the rule number for 10-state CA :");

		int d=10;
		long seed = Long.parseLong(JOptionPane.showInputDialog("Enter the seed for the "+ d +" state CA based PRNG:"));
		
		try {
			BufferedWriter bw1 = new BufferedWriter(new FileWriter(new File("PRNG_Output_"+d+"state_"+ruleStringSegment+"_"+seed+".txt"), false));
		   	
		
			
			
			int op = Integer.parseInt(JOptionPane.showInputDialog("Enter the option to generate random numbers:\n Enter 1 for binary, 2 for decimal"));
					
			if(op==1){
				int b = Integer.parseInt(JOptionPane.showInputDialog("Enter the number of multiples of 32 bits for the output number. \n For example, for 32, input 1, for 64 input 2 etc."));
				DecimalCAPRNGFromGivenPermutation prng = new DecimalCAPRNGFromGivenPermutation(ruleStringSegment,b, seed);
				//bw1.write(Long.toBinaryString(seed));
			//	bw1.newLine();
			//	bw1.flush();
				//prng.srandCA(b, seed);
				/*******************Generating random binary numbers*********************/
				 for(int nIndex = 0; nIndex < 1000; nIndex++){
					 
					String number = prng.randCABin(b);
					System.out.println(number);
					//bw1.write(Long.toBinaryString(Long.parseLong(number)));
					bw1.write(number);
					//bw1.newLine();
					bw1.flush();
			   	  
				 }
			}
			else {
					DecimalCAPRNGFromGivenPermutation prng = new DecimalCAPRNGFromGivenPermutation(ruleStringSegment,seed);
					
					bw1.write(String.valueOf(seed));
					bw1.newLine();
					bw1.flush();
					//prng.srandCA(window, seed);
					/*******************Generating random decimal numbers*********************/
					 for(int nIndex = 0; nIndex < 1000; nIndex++){
						 
						String number = prng.randCA();
						System.out.println(number);
						bw1.write(number);
						bw1.newLine();
						bw1.flush();
			   	  
				 }
			}
			
			 bw1.close();
		
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}	
	
}
