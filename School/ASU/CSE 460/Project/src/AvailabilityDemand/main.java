/**
 * Name: 		Wei-Chieh Huang
 * Assignment: 	Final Project
 * ASU_ID:		1215427213
 */
package AvailabilityDemand;

import java.text.ParseException;
import java.util.*;


public class main {
	
	public static HashMap<String, Boolean> checker = new HashMap<>();
	public static Listing listing = new Listing();
	public static List<String> notification = new ArrayList<>();
	
	public static void main(String[] args) throws ParseException
	{
		AvailabilityDemand ad = new AvailabilityDemand();
		
		/**
		 * own test case
		 */
//		ad.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
//		ad.processInput("subscribe, abcd, ugly City, 11/05/2021, 11/10/2021");
//		ad.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
//		ad.processInput("publish, xxbb, ugly City, 11/4/2021, 11/11/2021");
//		ad.getAggregatedOutput();
//		ad.reset();
//		/**
//		 * test case 1
//		 */
//		ad.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
//		
//        ad.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
//        
//        ad.processInput("subscribe, Jane Doe, Tempe, 11/29/2021, 12/02/2021");
//        
//        ad.processInput("publish, High-Mountains, Tempe, 11/28/2021, 12/02/2021");
//        
//        ad.processInput("publish, AirCloud, Tempe, 11/28/2021, 12/05/2021");
		
		/**
		 * test case 2
		 */
//		ad.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
//		
//        ad.processInput("subscribe, William, New York City, 12/10/2021, 12/15/2021");
//        // John Doe's subscription fits within the criteria thus, John Doe should get notified of this event
//        
//        ad.processInput("publish, High-Mountains, New York City, 12/01/2021, 12/05/2021");
//        // William's subscription fits within the criteria thus, William should get notified of this event
//        
//        ad.processInput("publish, AirClouds, New York City, 12/10/2021, 12/15/2021");
        
		/**
		 * test case 3 -- invalid date format
		 */
//        ad.processInput("subscribe, John Doe, New York City, 15/01/2022, 30/01/2022");
//        //Date format invalid: DD MMM YYYY
//        ad.processInput("publish, High-Mountains, New York City, 14 Jan 2022, 30 Jan 2022");
//        //stay period to date must be smaller than stay period from date
//        ad.processInput("subscribe, John Doe, New York City, 30/01/2022, 15/01/2022");
//        //extra parameter in the publish method
//        ad.processInput("publish, High-Mountains, New York City, 14 Jan 2022, 30 Jan 2022, great view and lot of space");
//        //available till date must be smaller than available from date
//        ad.processInput("publish, AirClouds, New York City, 30/01/2022, 15/01/2022");
        
		/**
		 * test case 4 -- 
		 */
//		ad.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
//        ad.processInput("subscribe, William, New York City, 12/10/2021, 12/15/2021");
//        // to date needs to be same as or greater than end date of subscribed period
//        ad.processInput("publish, High-Mountains, New York City, 11/29/2021, 12/02/2021");
//        // start date of availability period needs to be later than default date which is 11/27/2021
//        ad.processInput("publish, High-Mountains, New York City, 11/20/2021, 12/05/2021");
//        // start date of stay period needs to be later than default date which is 11/27/2021
//        ad.processInput("subscribe, Jane Doe, New York City, 11/20/2021, 12/05/2021");
		
		/**
		 * test case 5 -- 
		 */
        ad.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
        ad.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/05/2021");
        //overlaps with the first published availability, should be discarded
        ad.processInput("publish, High-Mountains, New York City, 11/29/2021, 12/02/2021");
        //overlaps with the first published availability, should be discarded
        ad.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
		ad.getAggregatedOutput();

        
		/**
		 * test case 6-- 
		 */
//		ad.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
//        ad.processInput("subscribe, William, New York City, 12/10/2021, 12/15/2021");
//        //both subscribers should get the notification as satisfy the criteria
//        ad.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
//        //one subscriber removed from system
//        ad.processInput("unsubscribe, William, New York City, 12/10/2021, 12/15/2021");
//        //duplicate published event, no action taken
//        ad.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
//        //one subscriber removed from system, no subscribers in system
//        ad.processInput("unsubscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
//        //no subscribers in system, system will store the event
//        ad.processInput("publish, AirClouds, New York City, 11/30/2021, 12/15/2021");
//        // both stored published events will be fired for below customer since this one comes as a new subscription
//        ad.processInput("subscribe, William, New York City, 12/10/2021, 12/15/2021");
//        // both stored published events will be fired for below customer since this one comes as a new subscription
//        ad.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
        
        
//		ad.getAggregatedOutput();
	}

}
