import java.io.*;

public class FibonacciApplication
{
	public static void main(String args[])
	{
	  char input[]=new char[1];
	  String temp;
	  int n=0;
	  long value=0;
	  
	  System.out.println("Please input the position of fibonacci series:");
	  
	  try{
		  input[0]=(char)System.in.read();
	  }
	  catch(IOException e)
	  {};
	  
	  temp=new String(input);
	  n=Integer.parseInt(temp);
	  value=fibonacci(n);
	  System.out.println("The value is:"+value);
	 }
	 public static long fibonacci(int n)
	  {
		if(n==0||n==1)
		  return 1;
		else
		  return(fibonacci(n-1)+fibonacci(n-2));
	  }
}