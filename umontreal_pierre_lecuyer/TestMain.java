package umontreal_pierre_lecuyer;

public class TestMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		System.out.println("---------------------------LFSR113---------------------");
		RandomStream stream3 = new LFSR113();
		for(int i=0;i<10;i++){
	    	int number = stream3.nextInt(0, Integer.MAX_VALUE);
			System.out.println("Next value ="+number);
		}
		System.out.println();
		/*
		 * System.out.println("-----------------------MT19937--------------------------"
		 * );
		 * 
		 * RandomStream stream4 = new MT19937((CloneableRandomStream) stream3); for(int
		 * i=0;i<10;i++){ int number = stream4.nextInt(0, Integer.MAX_VALUE);
		 * System.out.println("Next value ="+number);
		 * 
		 * } System.out.println();
		 */
		  System.out.println("----------------------LFSR258------------------------");
		  RandomStream stream5 = new LFSR258();
			for(int i=0;i<10;i++){
		    	int number = stream5.nextInt(0, Integer.MAX_VALUE);
				System.out.println("Next value ="+number);
			}
			System.out.println();
			System.out.println("-------------------------MRG31k3p---------------------");

			RandomStream stream6 = new MRG31k3p();
			for(int i=0;i<10;i++){
		    	int number = stream6.nextInt(0, Integer.MAX_VALUE);
				System.out.println("Next value ="+number);
			}
			System.out.println();
	}
}
