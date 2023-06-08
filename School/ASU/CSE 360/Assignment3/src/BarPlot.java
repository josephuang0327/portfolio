/**
 *  Name:	WeiChieh Huang
 *	ASUID:	1215427213
 *	CoursID:70605-CSE360
 *	Assignment# 3
 *	Description: Draw the bar graph diagram and it contains simple plot and
 *				 marked plot.
 */

import java.awt.*;

public class BarPlot extends DecoratedPlot
{
	/**
	 * It create a rectangle that will fill from the bottom to the random value
	 * in the linked list.
	 * @param g, is the default graphics object 
	 */
	public void draw(Graphics g)
	{
		g.setColor(Color.GRAY);		
		for(int curr = 0; curr < values.size(); curr++)
		{
			g.setColor(Color.BLACK);
			g.fillRect(curr * 20, values.get(curr), 10, 300);
		}
		super.draw(g);

	}
}
