import java.io.*;
import java.math.*;

public class Exp4_5
{
	public static void main(String args[])
	{
		int i,j,k,n=100,m=1;
		
		while(n<1000)
		{
			i=n/100;
			j=(n-i*100)/10;
			k=n%10;
			if((Math.pow(i,3)+Math.pow(j,3)+Math.pow(k,3))==n)
			{
			   System.out.println("找到第"+m+"个水仙花数:"+n);
			   m++;
			 }
			n++;
		}
		
		m=1;
		for(n=100;n<1000;n++)
		{
			i=n/100;
			j=(n-i*100)/10;
			k=n%10;
			if((Math.pow(i,3)+Math.pow(j,3)+Math.pow(k,3))==n)
			{
			   System.out.println("找到第"+m+"个水仙花数:"+n);
			   m++;}
	     }
	   }
}
			