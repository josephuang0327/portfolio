/**
 *  Name:	WeiChieh Huang
 *	ASUID:	1215427213
 *	CoursID:70605-CSE360
 *	Assignment# 3
 *	Description: Update the panel to get new values. Output the interface to 
 *				 the user.
 */

import java.awt.*;
import java.util.Observable;
import java.util.Observer;
import javax.swing.*;

public class PlotPanel extends JPanel implements Observer
{
	
	Drawable drawable;
	
	/**
	 * let the drawable object be the parameter object.
	 * @param drawable, the drawable object.
	 */
	public PlotPanel(Drawable drawable)
	{
		this.drawable = drawable;
		
	}
	
	/**
	 * override the update method. to get new value from the source class
	 * and set it to the linked list.
	 */
	@Override
	public void update(Observable o, Object arg)
	{
		drawable.setValue(((Source)o).getValue());
		repaint();
	}
	
	/**
	 * paint the component (draw the plot)
	 * @param g, the default graphics object.
	 */
	public void paintComponent(Graphics g)
	{
		if(drawable != null)
		{
			drawable.draw(g);
		}
	}
	
}
