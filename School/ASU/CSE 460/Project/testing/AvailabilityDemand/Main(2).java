package AvaialbilityDemand;

import java.text.ParseException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Main {
	
	public static buffer b = new buffer();
	public static List<String> resultList = new ArrayList<>();
	public static HashMap<String, Boolean> check = new HashMap<>();
	
	public static void main(String[] args) throws ParseException {
		
	
		AvailabilityDemand availabilityDemand = new AvailabilityDemand();

		  availabilityDemand.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
	        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/05/2021");
	        //overlaps with the first published availability, should be discarded
	        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/29/2021, 12/02/2021");
	        //overlaps with the first published availability, should be discarded
	        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
	        
		System.out.println(availabilityDemand.getAggregatedOutput()); 
		
		
		
	}
	
	

}
