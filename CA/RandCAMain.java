package randomness;

import javax.swing.JOptionPane;

public class RandCAMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
			int numberLength;
			numberLength = Integer.parseInt(JOptionPane.showInputDialog("Enter the length of the number : "));
				
			String seed = JOptionPane.showInputDialog("Enter the random seed ");
			
			RandCA rand = new RandCA();
				
			rand.srandCA(numberLength,seed);	
		  		
			//char Number[] = rand.randCA();
			String Number = rand.randCA();
			System.out.println("random number is "+Number);
			Number = rand.randCA();
			System.out.println("random number is "+Number);
			Number = rand.randCA();
			System.out.println("random number is "+Number);
			
		}

}
