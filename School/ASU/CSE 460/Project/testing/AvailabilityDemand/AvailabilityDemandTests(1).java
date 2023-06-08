package AvaialbilityDemand;
import org.junit.After;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

import java.text.ParseException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

/**
 * CSE 460 Software Analysis and Design Project - Sample Test Cases
 * This class contains some test cases that will be used in automated grading of your project.
 * Note that these test cases are not exhaustive
 *
 * These tests concern only with the correctness and robustness of your implementation. You are still required to
 * adopt Publisher-Subscriber pattern in your design and make use of good programming practises.
 *
 * The undisclosed part of the test will differ from this test somewhat:
 * - Test cases are automatically generated with random characters (other than commas and leading/trailing spaces).
 * - The generated test cases can be very long and contains unusual sequences.
 * - The generated test cases are based on criteria imposed in the project descriptions, which any implementation is
 *   bound to abide.
 * - Instead of testing the output of your program against a "standard answer", your output would be compared against
 *   the output of a "Reference Implementation" (RI), which is seen as the authoritative answer.
 *  - Could the RI be wrong? Yes, but unlikely. Contact us if you believe it is the case.
 * @version 1.0
 * Author: Sheetal Mohite <smohite3@asu.edu>
 */

public class AvailabilityDemandTests {
    private static AvailabilityDemand availabilityDemand;

    // Create AvailabilityDemand object to test with
    @BeforeClass
    public static void setupAvailabilityDemand() {
        availabilityDemand = new AvailabilityDemand();
    }

    // Reset the availabilityDemand object every time a test finishes so that it can accept a new batch of commands
    @After
    public void resetAvailabilityDemand() {
        availabilityDemand.reset();
    }

    // Note: @GradedTest is for GradeScope scoring only and does not affect the test in any way.
    @Test
    //@GradedTest(name = "Normal 1 - Subscribes and publishes on random order", max_score = 2)
    public void testSubPubForValidInputs() throws ParseException {
        // Expected output
        List<String> expected = new ArrayList<>(Arrays.asList(
                "John Doe notified of B&B availability in New York City from 11/30/2021 to 12/15/2021 by High-Mountains B&B",
                "Jane Doe notified of B&B availability in Tempe from 11/28/2021 to 12/02/2021 by High-Mountains B&B",
                "Jane Doe notified of B&B availability in Tempe from 11/28/2021 to 12/05/2021 by AirCloud B&B"
                ));

        // Feed the SD object with some commands
        availabilityDemand.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
        availabilityDemand.processInput("subscribe, Jane Doe, Tempe, 11/29/2021, 12/02/2021");
        availabilityDemand.processInput("publish, High-Mountains, Tempe, 11/28/2021, 12/02/2021");
        availabilityDemand.processInput("publish, AirCloud, Tempe, 11/28/2021, 12/05/2021");

        // Obtain the actual result from your availabilityDemand object and compare it with the expected output
        List<String> actual = availabilityDemand.getAggregatedOutput().stream()
                .map(String::strip)
                .map(String::toLowerCase)
                .collect(Collectors.toList());
        expected =  expected.stream().map(String :: toLowerCase).collect(Collectors.toList());
        assertEquals(expected, actual);
    }
    @Test
    //@GradedTest(name = "Abnormal 2 - date constraint of notification", max_score = 2)
    public void testSameDatePublishedEventsShouldBeProvidedToCustomersSatisfyingTheCriteria() throws ParseException {
        // Expected output
        List<String> expected = new ArrayList<>(Arrays.asList(
                "John Doe notified of B&B availability in New York City from 12/01/2021 to 12/05/2021 by High-Mountains B&B",
                "William notified of B&B availability in New York City from 12/10/2021 to 12/15/2021 by AirClouds B&B"
        ));
        // Feed the SD object with some commands
        availabilityDemand.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
        availabilityDemand.processInput("subscribe, William, New York City, 12/10/2021, 12/15/2021");
        // John Doe's subscription fits within the criteria thus, John Doe should get notified of this event
        availabilityDemand.processInput("publish, High-Mountains, New York City, 12/01/2021, 12/05/2021");
        // William's subscription fits within the criteria thus, William should get notified of this event
        availabilityDemand.processInput("publish, AirClouds, New York City, 12/10/2021, 12/15/2021");

        // Obtain the actual result from your availabilityDemand object and compare it with the expected output
        List<String> actual = availabilityDemand.getAggregatedOutput().stream()
                .map(String::strip)
                .map(String::toLowerCase)
                .collect(Collectors.toList());
        expected =  expected.stream().map(String :: toLowerCase).collect(Collectors.toList());

        assertEquals(expected, actual);
    }
    @Test
    //@GradedTest(name = "Abnormal 1 - Illegal parameter lengths", max_score = 2)
    public void testIllegalParamLens() throws ParseException {

        //Date format invalid: DD/MM/YYYY
        availabilityDemand.processInput("subscribe, John Doe, New York City, 15/01/2022, 30/01/2022");
        //Date format invalid: DD MMM YYYY
        availabilityDemand.processInput("publish, High-Mountains, New York City, 14 Jan 2022, 30 Jan 2022");
        //stay period to date must be smaller than stay period from date
        availabilityDemand.processInput("subscribe, John Doe, New York City, 30/01/2022, 15/01/2022");
        //extra parameter in the publish method
        availabilityDemand.processInput("publish, High-Mountains, New York City, 14 Jan 2022, 30 Jan 2022, great view and lot of space");
        //available till date must be smaller than available from date
        availabilityDemand.processInput("publish, AirClouds, New York City, 30/01/2022, 15/01/2022");
        // Obtain the actual result from your SD object and compare it with the expected output
        List<String> actual = availabilityDemand.getAggregatedOutput();
        // Expected output (nothing)
        assertEquals(0, actual.size());
    }

    @Test
    //@GradedTest(name = "Abnormal 2 - date constraint of notification", max_score = 2)
    public void testDateConstraintInPublishingInformation() throws ParseException {
        // Expected output (nothing)
        // Feed the SD object with some commands
        availabilityDemand.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
        availabilityDemand.processInput("subscribe, William, New York City, 12/10/2021, 12/15/2021");
        // to date needs to be same as or greater than end date of subscribed period
        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/29/2021, 12/02/2021");
        // start date of availability period needs to be later than default date which is 11/27/2021
        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/20/2021, 12/05/2021");
        // start date of stay period needs to be later than default date which is 11/27/2021
        availabilityDemand.processInput("subscribe, Jane Doe, New York City, 11/20/2021, 12/05/2021");

        // Obtain the actual result from your SD object and compare it with the expected output
        List<String> actual = availabilityDemand.getAggregatedOutput();

        assertEquals(0, actual.size());
    }

    @Test
    //@GradedTest(name = "Abnormal 2 - date constraint of notification", max_score = 2)
    public void testPublishDatesFromSameProviderCannotOverlap() throws ParseException {
        // Expected output
        List<String> expected = new ArrayList<>(Arrays.asList(
                "John Doe notified of B&B availability in New York City from 11/30/2021 to 12/05/2021 by High-Mountains B&B"
        ));
        // Feed the SD object with some commands
        availabilityDemand.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/05/2021");
        //overlaps with the first published availability, should be discarded
        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/29/2021, 12/02/2021");
        //overlaps with the first published availability, should be discarded
        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
        // Obtain the actual result from your availabilityDemand object and compare it with the expected output
        List<String> actual = availabilityDemand.getAggregatedOutput().stream()
                .map(String::strip)
                .map(String::toLowerCase)
                .collect(Collectors.toList());
        expected =  expected.stream().map(String :: toLowerCase).collect(Collectors.toList());

        assertEquals(expected, actual);
    }


    @Test
    // @GradedTest(name = "Normal 2 - Multi providers subscribe to & unsubscribe from the same type", max_score = 2)
    public void testMultiSubUnsubForValidInputs() throws ParseException {
        // Expected output
        List<String> expected = new ArrayList<>(Arrays.asList(
                "John Doe notified of B&B availability in New York City from 11/30/2021 to 12/15/2021 by High-Mountains B&B",
                "William notified of B&B availability in New York City from 11/30/2021 to 12/15/2021 by High-Mountains B&B",
                "William notified of B&B availability in New York City from 11/30/2021 to 12/15/2021 by High-Mountains B&B",
                "William notified of B&B availability in New York City from 11/30/2021 to 12/15/2021 by AirClouds B&B",
                "John Doe notified of B&B availability in New York City from 11/30/2021 to 12/15/2021 by High-Mountains B&B",
                "John Doe notified of B&B availability in New York City from 11/30/2021 to 12/15/2021 by AirClouds B&B"
        ));
        // Feed the SD object with some commands
        availabilityDemand.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
        availabilityDemand.processInput("subscribe, William, New York City, 12/10/2021, 12/15/2021");
        //both subscribers should get the notification as satisfy the criteria
        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
        //one subscriber removed from system
        availabilityDemand.processInput("unsubscribe, William, New York City, 12/10/2021, 12/15/2021");
        //duplicate published event, no action taken
        availabilityDemand.processInput("publish, High-Mountains, New York City, 11/30/2021, 12/15/2021");
        //one subscriber removed from system, no subscribers in system
        availabilityDemand.processInput("unsubscribe, John Doe, New York City, 12/01/2021, 12/05/2021");
        //no subscribers in system, system will store the event
        availabilityDemand.processInput("publish, AirClouds, New York City, 11/30/2021, 12/15/2021");
        // both stored published events will be fired for below customer since this one comes as a new subscription
        availabilityDemand.processInput("subscribe, William, New York City, 12/10/2021, 12/15/2021");
        // both stored published events will be fired for below customer since this one comes as a new subscription
        availabilityDemand.processInput("subscribe, John Doe, New York City, 12/01/2021, 12/05/2021");

        // Obtain the actual result from your availabilityDemand object and compare it with the expected output
        List<String> actual = availabilityDemand.getAggregatedOutput().stream()
                .map(String::strip)
                .map(String::toLowerCase)
                .collect(Collectors.toList());
        expected =  expected.stream().map(String :: toLowerCase).collect(Collectors.toList());

        assertEquals(expected, actual);
    }
}