package parallel;
import java.lang.Math;   


public class TaskOne implements Runnable{

	private int parameter;
	private double sum;
	
	public TaskOne(int parameter) {
		this.parameter = parameter;
	}
	
	@Override
	public void run() {
		for(int i=0;i<parameter;i++)
		{
			sum += Math.random();
		}
		System.out.println("A(z) " + parameter +" paraméterrel rendelkezõ összege: " +sum);
	}

	public double getSum() {
		return sum;
	}
}
