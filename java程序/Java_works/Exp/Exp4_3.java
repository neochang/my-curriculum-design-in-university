import java.applet.Applet;
import java.awt.*;

public class Exp4_3 extends Applet
{
	Label prompt=new Label("��������������:");
	TextField operand1=new TextField(6);
	TextField operand2=new TextField(6);
	Label result=new Label("���Լ���ǡ�;��С��������  ");
	
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
		if(x%y==0)   //y�����Լ��
		div=y;
		else
		{
			do{
				div=x%y;
				x=y;
				y=div;
			}while(div!=0);
			div=x;   //�õ����Լ��
		}
		mul=oldm/div;   //�õ���С������
		result.setText("���Լ����:"+div+"; "+"��С��������:"+mul);
		repaint();
		return true;
	}
}
		