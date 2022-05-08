package parallel;

public class Main {

	public static void main(String[] args) throws InterruptedException {
		TaskOne elso = new TaskOne(40);
		Thread feladat = new Thread(elso);
		
		TaskOne masodik = new TaskOne(50);
		Thread feladat2 = new Thread(masodik);
		
		feladat.start();
		feladat2.start();
		
		feladat.join();
		feladat2.join();

		double sum = elso.getSum()+masodik.getSum();
		System.out.println("Végsõ eredmény: " + sum);
	}

}
