package parallel;
import java.lang.Math;
import java.time.Duration;
import java.time.Instant;   


public class ParallelSum implements Runnable{

	private int parameter;
	private double sum;
	
	public ParallelSum(int parameter) {
		this.parameter = parameter;
	}
	
	@Override
	public void run() {
		Instant start = Instant.now();
		for(int i=0;i<parameter;i++)
		{
			sum += Math.random();
		}
		Instant end = Instant.now();
		System.out.println("A(z) " + parameter +" paraméterrel rendelkezõ összege: " +sum +" és " + Duration.between(start, end).toNanos()/1000 + " microsec telt el.");
	}

	public double getSum() {
		return sum;
	}
}
