import java.applet.Applet;
import java.awt.*;

public class BubbleSortApplet extends Applet
{
	Label prompt=new Label("���������������������(���10��)��");
	TextField input=new TextField(5);
	Button sortbtn=new Button("����");
	Button resetbtn=new Button("��������");
	int[] DataArray=new int[10];
	int[] InitialDataArray=new int[10];
	int DataInputed=0;
	int n=0;
	String msg1=new String("�����������˳���ǣ�");
	String msg2=new String("�����Ľ��Ϊ��");
	
	public void init()
	{
		add(prompt);add(input);add(sortbtn);add(resetbtn);
	}
	
	public void paint(Graphics g)
	{
		g.drawString(msg1,40,55);
		
		for(int j=0;j<InitialDataArray.length;j++)
		{
			g.drawString(Integer.toString(InitialDataArray[j]),40+30*j,70);
		}
		
		g.drawString(msg2,40,85);
		
        for(int j=0;j<DataArray.length;j++)
		{
			g.drawString(Integer.toString(DataArray[j]),40+30*j,100);
		}		
	}
	
	public boolean action(Event e,Object o)
	{
		if(e.target==input)
		{
			DataArray[DataInputed++]=Integer.parseInt(input.getText());
			if(DataInputed<10)
			{
				prompt.setText("������"+DataInputed+"�������������");
				input.setText("");
			}
			else
			{
				prompt.setText("������10�����ݣ�������������");
				input.hide();
				for(n=0;n<DataArray.length;n++)
				{
					InitialDataArray[n]=DataArray[n];
				}
			}
		}
		if(e.target==sortbtn)
		{
			for(n=0;n<DataArray.length;n++)
			{
				InitialDataArray[n]=DataArray[n];
			}
			SortProcedure();
			repaint();
		}
		if(e.target==resetbtn)
		{
			DataInputed=0;
			prompt.setText("���������������������(���10��)��");
			input.show();
			
			for(n=0;n<DataArray.length;n++)
			{
				DataArray[n]=0;
			}
			for(n=0;n<InitialDataArray.length;n++)
			{
				InitialDataArray[n]=0;
			}
			repaint();
		}
		return true;
	}
	void SortProcedure()
	{
		int pass,i,temp,exchangeCnt;
		
		for(pass=0;pass<DataArray.length;pass++)
		{
			exchangeCnt=0;
			for(i=0;i<DataArray.length-pass-1;i++)
			{
				if(DataArray[i]>DataArray[i+1])
				{
					temp=DataArray[i];
					DataArray[i]=DataArray[i+1];
					DataArray[i+1]=temp;
					exchangeCnt++;
				}
			}
			if(exchangeCnt==0)
			   return;
		}
	}
}