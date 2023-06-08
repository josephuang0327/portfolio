/**
 *  Name:	WeiChieh Huang
 *	ASUID:	1215427213
 *	Course:	CSE360
 *	Assignment# 3
 *	Description: decorate the simple plot with more features. Which is marked
 *				 plot and bar plot.
 */

import java.awt.*;

public abstract class DecoratedPlot extends Drawable
{
	protected Drawable drawable;
	
	/**
	 * Let the drawable object be the parameter object.
	 * @param d, the drawable object
	 */
	public void add(Drawable d)
	{
		drawable = d;
	}
	
	/**
	 * The parameter takes in the random value from source class and add it to
	 * to the linked list. If the linked list has more than 20 values. Remove
	 * the first value.
	 */
	@Override
	public void setValue(int value)
	{
		values.add(value);
		if(values.size() > 20)
		{
			values.remove(0);
		}
		drawable.setValue(value);
	}
	
	/**
	 * Override the draw method from super class
	 * @param g, is the default graphics object.
	 */
	@Override
	public void draw(Graphics g)
	{
		drawable.draw(g);
	}
}
