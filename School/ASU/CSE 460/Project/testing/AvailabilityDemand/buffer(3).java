package AvaialbilityDemand;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map.Entry;

public class buffer {
	
	private static HashMap<String, HashMap<String, StayPeriod>> OuterMap = new HashMap<>();  //nested map for storing information of customers;
	private static HashMap<String, HashMap<String, StayPeriod>> publishMap = new HashMap<>();
         
		public void addSubscriber(String Name, String location, Date startDate, Date endDate) {
		//@Begin
		StayPeriod date = new StayPeriod(startDate, endDate);
			
		
			if (OuterMap.containsKey(location) && OuterMap.get(location).containsKey(Name)) //&& OuterMap.get(location).get(Name).getFromDate().compareTo(startDate) == 0 && OuterMap.get(location).get(Name).getToDate().compareTo(endDate) == 0
			{
				
			}
			else if(OuterMap.containsKey(location) )
			{   
				
				
					OuterMap.get(location).put(Name, date);
						
				
				
			}
			else
			{
				HashMap<String, StayPeriod> tmpMap = new HashMap<>();
				tmpMap.put(Name, date);
	         	OuterMap.put(location, tmpMap);
	         	
	         
			}
		
					
		
		}
			
		
		

		public void removeSubscriber(String Name, String location, Date startDate, Date endDate) {
		//@Begin
		if(OuterMap.containsKey(location))
				{
			      OuterMap.get(location).remove(Name);
			      Main.check.put(Name, false);
				}
		//@End
		
		}

		public void send(String pubName, String location, Date startDate, Date endDate) {
		
		while(OuterMap.containsKey(location))
	           {   
			     
	        	   for(Entry<String, StayPeriod> entry : OuterMap.get(location).entrySet())
	        	   {
	        		if((startDate.before(entry.getValue().getToDate()) || startDate.equals(entry.getValue().getFromDate())) && (endDate.after(entry.getValue().getToDate()) || endDate.equals(entry.getValue().getToDate())))//Check the time range here, and compared with published time range
	        		{           			
	        			
	        			
	        			
	        			String listStr = Main.resultList.toString();
	        			if(listStr.contains(entry.getKey()) && listStr.contains(pubName))
	        			{
	        				
	        			}
	        			else
	        			{
	        				subscriber.notify(entry.getKey(), pubName, location, startDate, endDate);
	        			}
	        			//remove subscriber
	        			//OuterMap.get(location).remove(entry.getKey());
	        		}
	        		
	        	   }
	        	
	        	   break;   
	        }
		
		}

		public void clear() {
		//@Begin
		OuterMap.clear();
		//@End
		}	
		
		
		
		
		public void addpulisher(String Name, String location, Date startDate, Date endDate) {
			//@Begin
			StayPeriod date = new StayPeriod(startDate, endDate);
				
			
				if (publishMap.containsKey(location) && publishMap.get(location).containsKey(Name)) //&& OuterMap.get(location).get(Name).getFromDate().compareTo(startDate) == 0 && OuterMap.get(location).get(Name).getToDate().compareTo(endDate) == 0
				{
					
				}
				else if(publishMap.containsKey(location) )
				{
					publishMap.get(location).put(Name, date);
				}
				else
				{
					HashMap<String, StayPeriod> tmpMap = new HashMap<>();
					tmpMap.put(Name, date);
					publishMap.put(location, tmpMap);
		         
				}
			
						
			
			}
				
			

			public void sendpublish(String SubName, String location, Date startDate, Date endDate) {
			
			while(publishMap.containsKey(location))
		           {   
				     
		        	   for(Entry<String, StayPeriod> entry : publishMap.get(location).entrySet())
		        	   {
		        		if((entry.getValue().getFromDate().before(startDate) || startDate.equals(entry.getValue().getFromDate())) && (entry.getValue().getToDate().after(endDate) || endDate.equals(entry.getValue().getToDate())))//Check the time range here, and compared with published time range
		        		{           			
		        			
		        			
		        			
		        			String listStr = Main.resultList.toString();
		        			if(listStr.contains(entry.getKey()) && listStr.contains(SubName))
		        			{
		        				if(Main.check.containsKey(SubName) && Main.check.get(SubName) == false)
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
			publishMap.clear();
			//@End
			}	
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
