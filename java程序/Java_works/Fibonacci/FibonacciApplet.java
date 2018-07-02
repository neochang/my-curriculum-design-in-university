import java.applet.Applet;
import java.awt.*;
import java.io.*;

public class FibonacciApplet extends Applet
{
	Label prompt=new Label("������Ʋ��������е�λ��(���Ϊ10)��");
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
				prompt.setText("��������ݹ���������С��10��������");
				input.setText("");
			}
			else
			   result=Fibonacci(Integer.parseInt(input.getText()));
			   msg="Fibonacci�����е�"+input.getText()+"�����ǣ�"+result;
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