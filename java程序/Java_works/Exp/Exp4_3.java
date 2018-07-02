import java.applet.Applet;
import java.awt.*;

public class Exp4_3 extends Applet
{
	Label prompt=new Label("请输入两个整数:");
	TextField operand1=new TextField(6);
	TextField operand2=new TextField(6);
	Label result=new Label("最大公约数是　;最小公倍数是  ");
	
	public void init()
	{
		add(prompt);
		add(operand1);
		add(operand2);
		add(result);
	}
	
	public boolean action(Event e,Object o)
	{
		int x,y,oldm,div,mul,temp;
		
		x=Integer.parseInt(operand1.getText());
		y=Integer.parseInt(operand2.getText());
		oldm=x*y;
		if(x<y)
		{
			temp=y;
			y=x;
			x=temp;
		}
		if(x%y==0)   //y是最大公约数
		div=y;
		else
		{
			do{
				div=x%y;
				x=y;
				y=div;
			}while(div!=0);
			div=x;   //得到最大公约数
		}
		mul=oldm/div;   //得到最小公倍数
		result.setText("最大公约数是:"+div+"; "+"最小公倍数是:"+mul);
		repaint();
		return true;
	}
}
		