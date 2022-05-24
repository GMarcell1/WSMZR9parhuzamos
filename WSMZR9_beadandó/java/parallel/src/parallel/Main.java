package parallel;

import java.time.Duration;
import java.time.Instant;

public class Main {

	public static void main(String[] args) throws InterruptedException {
		ParallelSum first = new ParallelSum(14285);
		Thread taskOne = new Thread(first);
		
		ParallelSum second = new ParallelSum(14285);
		Thread taskTwo = new Thread(second);
		
		ParallelSum third = new ParallelSum(14285);
		Thread taskThree = new Thread(second);
		
		ParallelSum fourth = new ParallelSum(14285);
		Thread taskFour = new Thread(second);
		
		ParallelSum fifth = new ParallelSum(14285);
		Thread taskFive = new Thread(second);
		
		ParallelSum sixth = new ParallelSum(14285);
		Thread taskSix = new Thread(second);
		
		ParallelSum seventh = new ParallelSum(14285);
		Thread taskSeven = new Thread(second);
		
		int result = 0;
		Instant start = Instant.now();
		for(int i=0;i<22000;i++)
		{
			result += Math.random();
		}
		Instant end = Instant.now();
		System.out.println("Szekvenciálisan " + Duration.between(start, end).toNanos()/1000 + " microsec.");
		
		taskOne.start();
		taskTwo.start();
		taskThree.start();
		taskFour.start();
		taskFive.start();
		taskSix.start();
		taskSeven.start();
		
		taskOne.join();
		taskTwo.join();
		taskThree.join();
		taskFour.join();
		taskFive.join();
		taskSix.join();
		taskSeven.join();

		double sum = first.getSum()+second.getSum()+third.getSum()+fourth.getSum()+fifth.getSum()+sixth.getSum()+seventh.getSum();
		System.out.println("Végsõ eredmény: " + sum);
	}

}
