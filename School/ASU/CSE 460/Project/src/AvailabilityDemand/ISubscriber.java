/**
 * Name: 		Wei-Chieh Huang
 * Assignment: 	Final Project
 * ASU_ID:		1215427213
 */
package AvailabilityDemand;

import java.util.Date;

public interface ISubscriber {

	public boolean subscribe(String name, String location, Date from, Date to);

	public boolean unsubscribe(String name, String location, Date from, Date to);

}
