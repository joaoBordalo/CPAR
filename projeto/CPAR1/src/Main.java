import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;


public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int op;
		do {
			System.out.println(" \n 1. Multiplication");
			System.out.println("2. lin Multiplication");
			System.out.println("3. outputToFile");
			System.out.println("Selection?: ");
			Scanner a = new Scanner(System.in);
			op = a.nextInt();

			System.out.println("Dimensions: lins cols ? ");
			int lin = a.nextInt();
			int col = a.nextInt();
			System.out.println("Dimensional Increment: inc ? ");
			System.out.println("Dimensional Increment: limit ? ");
			int inc = a.nextInt();
			int limit = a.nextInt();

			switch (op){
			case 1: 
				double m1 = onMult(lin, col);
				//printMatrix(m1);
				break;
			case 2:
				double m2 = onMultlin(lin, col);
				//printMatrix(m2);
				break;
			case 3:
				outputToFile(lin,col,inc,limit/*,filename*/);
				//printMatrix(m2);
				break;
			}
		}while (op != 0);
	}


	private static void outputToFile(int lin, int col, int inc, int limit) {
		double temp;
		try
		{
		    FileWriter writer = new FileWriter("matrixMultResultJava.csv");
			for(int i=lin; i<=limit; i+=inc)
			{
				writer.append("i,Algoritmo a,Algoritmo b \n");
				temp = onMultlin(i, i);
				writer.append(String.valueOf(i));
				writer.append(",");
				writer.append(String.valueOf(temp));
				temp = onMultlin(i, i);
				writer.append(",");
				writer.append(String.valueOf(temp));
				writer.append('\n');
			}
		    writer.flush();
		    writer.close();
		}
		catch(IOException e)
		{
		     e.printStackTrace();
		} 
		
	}


	private static void printMatrix(double [][] matrix)
	{
		System.out.println("Result Matrix");
		for(int i=0; i<matrix.length; i++)
		{ for(int j=0; j<matrix.length; j++)
			System.out.print(matrix[i][j] + " ");
		System.out.println();
		}

	}

	private static double onMultlin(int lin, int col) {
		double[][] pha = new double [lin][col];
		double[][] phb = new double [lin][col];
		double[][] phc = new double [lin][col];
		for(int i=0; i<lin; i++)
			for(int j=0; j<col; j++)
				pha[i][j] = (double)1.0;

		for(int i=0; i<lin; i++)
			for(int j=0; j<col; j++)
				phb[i][j] = (double)(i+1);

		long startTime = System.nanoTime();
		for(int i=0; i<lin; i++)
		{	
			for( int k=0; k<lin; k++)
			{	 
				for( int j=0; j<col; j++)
				{	
					phc[i][j] += pha[i][k] * phb[k][j];
				}

			}
		}
		
		long totalTime = System.nanoTime() - startTime;
		//System.out.println("Total time = " + totalTime);
		//System.out.println();
		return (double) totalTime*Math.pow(10.0, -9.0);

	}




	public static double onMult(int lin, int col)
	{
		double[][] pha = new double [lin][col];
		double[][] phb = new double [lin][col];
		double[][] phc = new double [lin][col];
		for(int i=0; i<lin; i++)
			for(int j=0; j<col; j++)
				pha[i][j] = (double)1.0;

		for(int i=0; i<lin; i++)
			for(int j=0; j<col; j++)
				phb[i][j] = (double)(i+1);

		double temp;
		long startTime = System.nanoTime();
		for(int i=0; i<lin; i++)
		{	
			for( int j=0; j<col; j++)
			{	 
				temp  = 0;
				for( int k=0; k<lin; k++)
				{	
					temp += pha[i][k] * phb[k][j];
				}
				phc[i][j]=temp;
			}
		}
		
		long totalTime = System.nanoTime() - startTime;
		//System.out.println("Total time = " + totalTime);
		//System.out.println();
		
		return (double) totalTime*Math.pow(10.0, -9.0);
	}

}



