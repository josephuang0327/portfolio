package AvaialbilityDemand;

import java.util.Date;

public class StayPeriod {
	
	private Date from;
	private Date to;
	
	public StayPeriod(Date from, Date to)
	{
		this.from = from;
		this.to = to;
		
	}
	
	public Date getFromDate()
	{
		return from;
	}
	
	public Date getToDate()
	{
		return to;
	}
	
	
}