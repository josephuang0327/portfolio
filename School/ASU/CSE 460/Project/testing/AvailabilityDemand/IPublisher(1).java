package AvaialbilityDemand;

import java.util.Date;

public interface IPublisher {

	
	public boolean publish(String providerName, String location, Date avaliableFrom, Date avaliableDate);
}
