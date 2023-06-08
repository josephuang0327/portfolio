package AvaialbilityDemand;

import java.text.SimpleDateFormat;
import java.util.Date;

public class subscriber implements ISubscriber {
   
	private String customerName;
	private String location;
	private Date fromDate;
	private Date toDate;
	
	public subscriber() {
		
		}
	
	public subscriber(String name, String location, Date from, Date to) {
		 customerName = name;
		 this.location = location;
		 fromDate = from;
		 toDate = to;
		}
	
	
	@Override
	public boolean subscribe(String name, String location, Date from, Date to) {
	    
		Main.b.addSubscriber(name, location, from, to);
		Main.b.sendpublish(name, location, from, to);
		
		
		return true;
	}
	
	

	@Override
	public boolean unSubscribe(String name, String location, Date from, Date to) {
		
		Main.b.removeSubscriber(name, location, from, to);
		
		return true;
	}
	
	public static void notify(String subname, String pubname, String location, Date from, Date to) {
		
		
		String strFromDate = new SimpleDateFormat("MM/dd/yyyy").format(from);
		String strToDate = new SimpleDateFormat("MM/dd/yyyy").format(to);
		Main.resultList.add(subname + " notified of B&B availability in" + location + " from " + strFromDate + " to " + strToDate + " by" + pubname + " B&B");
		//System.out.println(subname + " notified of B&B availability in" + location + " from " + from + " to " + to + " by" + pubname + " B&B");
		
		}


	
	
	
	
	
}