/**
 * Name: 		Wei-Chieh Huang
 * Assignment: 	Final Project
 * ASU_ID:		1215427213
 */
package AvailabilityDemand;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class BnBProvider implements IPublisher {

	public String providerName;
	public String location;
	public Date availableFrom;
	public Date availableDate;

	public BnBProvider(){
		
	}
	/**
	 * @see IPublisher#publish(String, String, Date, Date)
	 */
	public BnBProvider(String providerName, String location, Date availableFrom, Date availableDate)
	{
		this.providerName = providerName;
		this.location = location;
		this.availableFrom = availableFrom;
		this.availableDate = availableDate;
	}
	
	/**
	 * publish information to the Hashmap and check if notification need
	 * to be send.
	 */
	public boolean publish(String providerName, String location, Date availableFrom, Date availableDate) 
	{
		main.listing.addpub(providerName, location, availableFrom, availableDate);
		main.listing.sendNotify(providerName, location, availableFrom, availableDate);
		return true;
	}
	
	public static void notify(String subname, String pubname, String location, Date from, Date to)
	{
		String strFromDate = new SimpleDateFormat("MM/dd/yyyy").format(from);
		String strToDate = new SimpleDateFormat("MM/dd/yyyy").format(to);
		main.notification.add(subname + " notified of B&B availability in" + location + " from " + strFromDate + " to " + strToDate + " by" + pubname + " B&B");
			
	}
}
