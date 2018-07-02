import java.applet.Applet;
import java.awt.*;

public class Exp4_1 extends Applet
{
	Label prompt=new Label(" 请输入三个整数:");
	TextField operand1=new TextField(6);
	TextField operand2=new TextField(6);
	TextField operand3=new TextField(6);
	Label result=new Label ("最大数是:  最小数是:");
	
	public void init()
	{
		add(prompt);
		add(operand1);
		add(operand2);
		add(operand3);
		add(result);
	}
	
	public boolean action(Event e,Object o)
	{
		int x,y,z,max=0,min=0;
		
		x=Integer.parseInt(operand1.getText());
		y=Integer.parseInt(operand2.getText());
		z=Integer.parseInt(operand3.getText());
		
		if(x>y)
		{
			if(x>z)
			{
				max=x;
				if(y<z)
				  min=y;
				else
				  min=z;
		    }
		    else if(z>x)
		    {
		    	max=z;
		    	min=y;
		    }
		  }
		 else if(y>x)
		 {
		 	if(y>z)
		 	{
		 		max=y;
		 		if(x<z)
		 		  min=x;
		 		else
		 		  min=z;
		    }
		    else if(z>y)
		    {
		    	max=z;
		    	min=x;
		    }
		  }
		  
		  result.setText("最大数是:"+max+";"+"最小数是:"+min);
		  repaint();
		  return true;
   }
}