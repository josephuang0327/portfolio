package AvaialbilityDemand;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Publisher implements IPublisher{
	
	private String pubname;

	private String location;

	private Date from;
	private Date to;
   
	public Publisher() {
	
	}
	
	public Publisher(String Name, String location, Date from, Date to) {
		pubname = Name;
		this.location = location;
		this.from = from;
		this.to = to;
	}

	

	@Override
	public boolean publish(String providerName, String location, Date avaliableFrom, Date avaliableDate) {
		
		Main.b.addpulisher(providerName, location, avaliableFrom, avaliableDate);
		Main.b.send(providerName, location, avaliableFrom, avaliableDate);
	
		return true;
	}
	
    public static void notify(String subname, String pubname, String location, Date from, Date to) {
		
		
		String strFromDate = new SimpleDateFormat("MM/dd/yyyy").format(from);
		String strToDate = new SimpleDateFormat("MM/dd/yyyy").format(to);
		Main.resultList.add(subname + " notified of B&B availability in" + location + " from " + strFromDate + " to " + strToDate + " by" + pubname + " B&B");
		//System.out.println(subname + " notified of B&B availability in" + location + " from " + from + " to " + to + " by" + pubname + " B&B");
		
		}

	
}