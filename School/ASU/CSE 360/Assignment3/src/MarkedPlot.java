/**
 *  Name:	WeiChieh Huang
 *	ASUID:	1215427213
 *	CoursID:70605-CSE360
 *	Assignment# 3
 *	Description: Draw the square on each values. and above the simple plot.
 */

import java.awt.*;

public class MarkedPlot extends DecoratedPlot
{
	/**
	 * It creates the rectangle at the random value that is in the linked list.
	 * @param g, is the default graphics object
	 */
	public void draw(Graphics g)
	{		
		for(int curr = 0; curr < values.size(); curr++)
		{
			g.setColor(Color.BLACK);
			g.fillRect(curr * 20, values.get(curr), 10, 10);
		}
		super.draw(g);
	}
}
