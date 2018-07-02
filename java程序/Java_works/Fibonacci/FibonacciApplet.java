import java.applet.Applet;
import java.awt.*;
import java.io.*;

public class FibonacciApplet extends Applet
{
	Label prompt=new Label("请输入菲波那契数列的位置(最大为10)：");
	TextField input=new TextField(5);
	String msg;
	long result;
	
	public void init()
	{
		add(prompt);
		System.out.print("\n");
		add(input);
	}
	
	public void paint(Graphics g)
	{
		g.drawString(msg,40,55);
	}
	
	public boolean action(Event e,Object o)
	{
		if(e.target==input)
		{
			if(Integer.parseInt(input.getText())>10)
			{
				prompt.setText("输入的数据过大，请输入小于10的整数：");
				input.setText("");
			}
			else
			   result=Fibonacci(Integer.parseInt(input.getText()));
			   msg="Fibonacci数列中第"+input.getText()+"个数是："+result;
		}
		repaint();
		return true;
	}
	
	long Fibonacci(int n)
	{
		if(n==0||n==1)
		  return n;
		else
		  return(Fibonacci(n-1)+Fibonacci(n-2));
	}
}