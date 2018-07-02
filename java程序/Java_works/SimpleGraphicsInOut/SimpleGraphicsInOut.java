/*
 * @(#)SimpleGraphicsInOut.java 1.0 03/04/03
 *
 * You can modify the template of this file in the
 * directory ..\JCreator\Templates\Template_2\Project_Name.java
 *
 * You can also create your own project template by making a new
 * folder in the directory ..\JCreator\Template\. Use the other
 * templates as examples.
 *
 */

import java.awt.*;
import java.applet.Applet;


public class SimpleGraphicsInOut extends Applet
{
	Label prompt;
	TextField input;
	Label output;
	
	public void init()
	{
		prompt=new Label("请输入一个或一串字符：");
		input=new TextField("在这里输入",6);
		output=new Label("                             ");
		add(prompt);
		add(input);
		add(output);
	}
	
	public boolean action(Event e,Object o)
	{
		output.setText("You've entered character"+o.toString());
		return true;
	}
}
