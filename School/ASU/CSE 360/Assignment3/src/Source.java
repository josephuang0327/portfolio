/**
 *  Name:	WeiChieh Huang
 *	ASUID:	1215427213
 *	CoursID:70605-CSE360
 *	Assignment# 3
 *	Description: Create new values between 0 to 250 and return the value.
 */

import java.util.Observable;

public class Source extends Observable
{
	private int value;
	
	/**
	 * Create a random value from 0 to 250
	 */
	public void create()
	{
		value = (int) (Math.random() * 250) + 1;
		setChanged();
		notifyObservers();
	}
	
	/**
	 * return the random value that is created.
	 * @return
	 */
	public int getValue()
	{
		return value;
	}
}
