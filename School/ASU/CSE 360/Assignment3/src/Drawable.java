/**
 *  Name:	WeiChieh Huang
 *	ASUID:	1215427213
 *	CoursID:70605-CSE360
 *	Assignment# 3
 *	Description: Head of the decorator pattern. It creates the integer
 *				 LinkedList and add each value to the linked list. 
 */

import java.awt.*;
import java.util.LinkedList;

public abstract class Drawable 
{
	protected LinkedList<Integer> values = new LinkedList<Integer>();
	
	/**
	 * The parameter takes in a random variable from the source class and add
	 * it to the linked list. If the linked list has more than 20 values then
	 * delete the first value in the linked list.
	 * @param v
	 */
	public void setValue(int v)
	{
		values.add(v);
		
		if(values.size() > 20)
		{
			values.remove(0);
		}

	}
	
	/**
	 * @param g, is the default graphics object.
	 */
	public void draw(Graphics g)
	{
		
	}

}
