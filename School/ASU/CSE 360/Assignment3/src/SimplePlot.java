/**
 *  Name:	WeiChieh Huang
 *	ASUID:	1215427213
 *	CoursID:70605-CSE360
 *	Assignment# 3
 *	Description: Draw the line diagram that connect every value in the chart.
 */

import java.awt.*;

public class SimplePlot extends Drawable
{
	/**
	 * create the plot by drawing the line from the current value to the
	 * previous value. Repeat the process until all line are drawn.
	 * @param g, is the default graphics object.
	 */
	public void draw(Graphics g)
	{
		int x;
		int endX = 0;;
		int endY = 0;

		for(int curr = 0; curr < values.size(); curr++)
		{	
			x = curr * 20;				// current x point
			g.setColor(Color.BLACK);
			g.drawLine(x, values.get(curr), endX, endY);
			
			endX = x;					// previous x point
			endY = values.get(curr);	// previous y point
		}		
		super.draw(g);

	}
}
