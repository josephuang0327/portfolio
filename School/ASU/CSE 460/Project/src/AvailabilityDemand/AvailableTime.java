/**
 * Name: 		Wei-Chieh Huang
 * Assignment: 	Final Project
 * ASU_ID:		1215427213
 */
package AvailabilityDemand;

import java.util.Date;

public class AvailableTime 
{

	private Date fromDate;
	private Date toDate;
	
	public AvailableTime(Date fromDate, Date toDate)
	{
		this.fromDate = fromDate;
		this.toDate = toDate;
		
	}
	
	public Date getFromDate()
	{
		return fromDate;
	}
	
	public Date getToDate()
	{
		return toDate;
	}
}
