/**
 * Name: 		Wei-Chieh Huang
 * Assignment: 	Final Project
 * ASU_ID:		1215427213
 */
package AvailabilityDemand;

import java.util.Date;

public interface IPublisher {

	public abstract boolean publish(String providerName, String location, Date availableFrom, Date availableDate);

}
