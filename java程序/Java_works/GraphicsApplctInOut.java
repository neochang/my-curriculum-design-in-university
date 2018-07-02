//在图形界面下的Application程序：GraphicsApplctInOut.java
import java.awt.*;
public class GraphicsApplctInOut
{
	public static void main(String args[])
	{
		ApplctFrame MyFrame=new ApplctFrame();
	}
}

class ApplctFrame extends Frame
{
	Label prompt;
	TextField input;
	Label output;
	
	ApplctFrame()
	{
		super("Application 图形界面窗口");
		setLayout(new FlowLayout());
		prompt=new Label("Enter a character please:");
		input=new TextField(4);
		output=new Label("                         ");
		add(prompt);
		add(input);
		add(output);
		pack();
		show();
	}
	
	public boolean action(Event e,Object o)
	{
		output.setText("You've entered character:"+o.toString());
		return true;
	}
	
	public boolean handleEvent(Event evt)
	{
		if(evt.id==Event.WINDOW_DESTROY)
		System.exit(0);
		return super.handleEvent(evt);
	}
}