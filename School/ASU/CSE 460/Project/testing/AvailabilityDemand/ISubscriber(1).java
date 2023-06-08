package AvaialbilityDemand;

import java.util.Date;

public interface ISubscriber {
	
	public boolean subscribe(String name, String location, Date from, Date to);
	
	public boolean unSubscribe(String name, String location, Date from, Date to);
    
}
