/**
 * Name: 		Wei-Chieh Huang
 * Assignment: 	Final Project
 * ASU_ID:		1215427213
 */
package AvailabilityDemand;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;

public class Listing {
	
//	private static HashMap<String, HashMap<String, AvailableTime>> OuterMap = new HashMap<String, HashMap<String, AvailableTime>>();  //nested map for storing information of customers;
	private static HashMap<String, HashMap<String, AvailableTime>> OutMap = new HashMap<>();
	private static HashMap<String, HashMap<String, AvailableTime>> pubMap = new HashMap<>();

	//@End
	List<String> tempList = new ArrayList<String>();
;
		/**
		 * adding subscriber to the hashmap.
		 * @param Name
		 * @param location
		 * @param startDate
		 * @param endDate
		 */
		public void addSub(String Name, String location, Date startDate, Date endDate) {
		//@Begin
		AvailableTime atime = new AvailableTime(startDate, endDate);
			
			/**
			 * check if same person has subscribe to a place more than once
			 */
			if(OutMap.containsKey(location) && OutMap.get(location).containsKey(Name))
			{
				
			}
			/**
			 * if there is someone subscribe to a same location but 
			 * different name add them to the Hashmap
			 */
			else if(OutMap.containsKey(location)) 
			{
				OutMap.get(location).put(Name, atime);
			}
			/**
			 * otherwise, add the information to the Hashmap
			 */
			else
			{
//				System.out.println("adding " + Name);
//				OuterMap.put(location, new HashMap<String, AvailableTime>());
//				OuterMap.get(location).put(Name, atime);
//				System.out.println(OuterMap.get(location).get(Name));
				HashMap<String, AvailableTime> tempMap = new HashMap<>();
				tempMap.put(Name, atime);
	         	OutMap.put(location, tempMap);
			}
		}
		/**
		 * remove subscription system
		 * @param Name
		 * @param location
		 * @param startDate
		 * @param endDate
		 */
		public void rmSub(String Name, String location, Date startDate, Date endDate) {
		//@Begin
			if(OutMap.containsKey(location))
			{
				OutMap.get(location).remove(Name);
				main.checker.put(Name, false);
			}
		//@End
		
		}
		
		/**
		 * determine if there is notification needed to be sent, and store it to the list in main class.
		 * @param pubName
		 * @param location
		 * @param startDate
		 * @param endDate
		 */
		public void sendNotify(String pubName, String location, Date startDate, Date endDate) 
		{

			while(OutMap.containsKey(location))
		    {   
				/**
				 * iterate through all location to determine if notification needed to be send   
				 */
				for(Entry<String, AvailableTime> entry : OutMap.get(location).entrySet())
				{
					/**
					 * the entire time is available
					 */

					
					
					if(startDate.before(entry.getValue().getFromDate()) && endDate.after(entry.getValue().getToDate()))
		        	{   
		        		main.notification.add(Customer.notify(entry.getKey(), pubName, location, startDate, endDate));

//		        		main.notification.add(Customer.notify(entry.getKey(), pubName, location, entry.getValue().getFromDate(), entry.getValue().getToDate()));
		        		
//		        		System.out.println(tempList.get(0));
		        	}
					/**
					 * only part of the time are available
					 */
					else if(startDate.before(entry.getValue().getFromDate()) && endDate.equals(entry.getValue().getToDate()))
					{
		        		main.notification.add(Customer.notify(entry.getKey(), pubName, location, startDate, endDate));
					}
					/**
					 * exact date are the same
					 */
					else if(startDate.equals(entry.getValue().getFromDate()) && endDate.equals(entry.getValue().getToDate()))
					{
		        		main.notification.add(Customer.notify(entry.getKey(), pubName, location, startDate, endDate));
					}
					
					
					
	        		if((startDate.before(entry.getValue().getToDate()) || startDate.equals(entry.getValue().getFromDate())) && (endDate.after(entry.getValue().getToDate()) || endDate.equals(entry.getValue().getToDate())))//Check the time range here, and compared with published time range
	        		{           			
	        			
	        			
	        			
	        			String listStr = main.notification.toString();
	        			if(listStr.contains(entry.getKey()) && listStr.contains(pubName))
	        			{
	        				
	        			}
	        			else
	        			{
	        				Customer.notify(entry.getKey(), pubName, location, startDate, endDate);
	        			}
	        			//remove subscriber
	        			//OuterMap.get(location).remove(entry.getKey());
	        		}
		        }	
		        break;   
		    }
		
		}
		/**
		 * print out the store notification
		 */
		public void getNotification() 
		{
			for(int i = 0; i < main.notification.size(); i++)
			{
				System.out.println(main.notification.get(i));
			}
		}
	/**
	 * clears the hashmap
	 */
	public void clear() 
	{
		//@Begin
			OutMap.clear();
		//@End
	}	

	public void addpub(String Name, String location, Date startDate, Date endDate) 
	{
	//@Begin
	AvailableTime atime = new AvailableTime(startDate, endDate);

		if (pubMap.containsKey(location) && pubMap.get(location).containsKey(Name)) //&& OuterMap.get(location).get(Name).getFromDate().compareTo(startDate) == 0 && OuterMap.get(location).get(Name).getToDate().compareTo(endDate) == 0
		{
			
		}
		else if(pubMap.containsKey(location) )
		{
			pubMap.get(location).put(Name, atime);
		}
		else
		{
			HashMap<String, AvailableTime> tmpMap = new HashMap<>();
			tmpMap.put(Name, atime);
			pubMap.put(location, tmpMap);
         
		}
	}
	public void sendpublish(String SubName, String location, Date startDate, Date endDate) {
		
	while(pubMap.containsKey(location))
           {   
		     
        	   for(Entry<String, AvailableTime> entry : pubMap.get(location).entrySet())
        	   {
        		if((entry.getValue().getFromDate().before(startDate) || startDate.equals(entry.getValue().getFromDate())) && (entry.getValue().getToDate().after(endDate) || endDate.equals(entry.getValue().getToDate())))//Check the time range here, and compared with published time range
        		{           			
        			
        			
        			
        			String listStr = main.notification.toString();
        			if(listStr.contains(entry.getKey()) && listStr.contains(SubName))
        			{
        				if(main.checker.containsKey(SubName) && main.checker.get(SubName) == false)
        				{
        					Publisher.notify(SubName, entry.getKey(), location, entry.getValue().getToDate(), entry.getValue().getFromDate());
        				}
        			}
        			else
        			{
        			   Publisher.notify(SubName, entry.getKey(), location, entry.getValue().getToDate(), entry.getValue().getFromDate());
        			}
        			//remove subscriber
        			//OuterMap.get(location).remove(entry.getKey());
        		}
        		
        	   }
        	
        	   break;   
        }
	
	}

	public void pubclear() {
	//@Begin
	pubMap.clear();
	//@End
	}	
	
}

	

	
				
	
	
	
	
	
	
	
	
	
	
	
	
//	public Listing(String command) throws ParseException 
//	{
//		System.out.println("---------in listing ---------");
//		String[] token = command.split(", ", 4);
//		Date toDateToken = new SimpleDateFormat("MM/dd/yyyy").parse(token[2]);
//		Date fromDateToken = new SimpleDateFormat("MM/dd/yyyy").parse(token[3]);
//		
////		System.out.println(token[2]);
////		System.out.println(token[3]);
////		System.out.println(toDateToken);
////		System.out.println(fromDateToken);
//
//		setName(token[0]);
//		setLocation(token[1]);
//		setFromDate(toDateToken);
//		setToDate(fromDateToken);
//		
////		System.out.println("--------- ---------");
////		System.out.println(getName());
////		System.out.println(getLocation());
////		System.out.println(getToDate());
////		System.out.println(getFromDate());
//		
//	}
//
//	public void setLocation(String location) {
//		this.location = location;
//
//	}
//
//	public void setFromDate(Date fromDate) {
//		this.fromDate = fromDate;
//	}
//
//	public void setToDate(Date toDate) {
//		this.toDate = toDate;
//	}
//
//	public void setName(String name) {
//		this.name = name;
//	}
//
//	public String getLocation() {
//		return location;
//	}
//
//	public Date getFromDate() {
//		return fromDate;
//	}
//
//	public Date getToDate() {
//		return toDate;
//	}
//
//	public String getName() {
//		return name;
//	}

//}
