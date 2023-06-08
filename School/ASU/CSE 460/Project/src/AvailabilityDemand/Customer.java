/**
 * Name: 		Wei-Chieh Huang
 * Assignment: 	Final Project
 * ASU_ID:		1215427213
 */
package AvailabilityDemand;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Customer implements ISubscriber {

	public String customerName;
	public String location;
	public Date fromDate;
	public Date toDate;
	//private Listing[] listing;

	public Customer(){
		
	}
	
	public Customer(String name, String location, Date fromDate, Date toDate)
	{
		customerName = name;
		this.location = location;
		this.fromDate = fromDate;
		this.toDate = toDate;
	}

	/**
	 * @see ISubscriber#subscribe(String, String, Date, Date)
	 * add subscribe to the listing from main
	 */
	public boolean subscribe(String name, String location, Date fromDate, Date toDate) 
	{
		main.listing.addSub(name, location, fromDate, toDate);
		return true;
	}


	/**
	 * @see ISubscriber#unsubscribe(String, String, Date, Date)
	 * remove subscription in the list from main
	 */
	public boolean unsubscribe(String name, String location, Date fromDate, Date toDate) 
	{
		main.listing.rmSub(name, location, fromDate, toDate);
		return true;
	}
	
	/**
	 * @see notify(String, String, String, Date, Date)
	 * 
	 */
	public static String notify(String subName, String pubName, String location, Date fromDate, Date toDate)
	{
		String strFromDate = new SimpleDateFormat("MM/dd/yyyy").format(fromDate);
		String strToDate = new SimpleDateFormat("MM/dd/yyyy").format(toDate);
//		System.out.println(subName + " notified of B&B availability in " + location + " from " + strFromDate + " to " + strToDate + " by " + pubName + " B&B");
		String reStr = subName + " notified of B&B availability in " + location + " from " + strFromDate + " to " + strToDate + " by " + pubName + " B&B";
//		System.out.println(reStr);
		return (reStr);
	}
	
}
