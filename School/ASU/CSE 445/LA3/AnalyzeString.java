import java.util.*;
import java.util.concurrent.*;
import java.util.Scanner;

public class AnalyzeString {
    public static void main(String[] args) throws Exception {
        Scanner scan = new Scanner(System.in);

        System.out.println("Enter a string");
        String str = scan.nextLine();

        // List<upperCount> upper = new ArrayList<upperCount>();
        // List<DigitCountThread> digit = new ArrayList<DigitCountThread>();
        // List<isPalindrome> palin = new ArrayList<isPalindrome>();

        upperCount upper = new upperCount(str);
        DigitCountThread digit = new DigitCountThread(str);
        isPalindrome palin = new isPalindrome(str);

        // Create an instance of upperCountThread
        // upperCount upperThread = new upperCount(str);
        // upper.add(upperThread);
        // // Start DigitCountThread instance created above
        // DigitCountThread digitThread = new DigitCountThread(str);
        // digit.add(digitThread);
        // // Start isPalindrome instance created above
        // isPalindrome palinThread = new isPalindrome(str);
        // palin.add(palinThread);

        // upper.get(0).start();
        // digit.get(0).start();
        // palin.get(0).start();

        upper.start();
        digit.start();
        palin.start();

        // wait for the three threads to complete
        try {
            // upper.get(0).join();
            // digit.get(0).join();
            // palin.get(0).join();

            upper.join();
            digit.join();
            palin.join();
        } catch (InterruptedException e) {
        }

        // display digit count, upper count and whether the string is a palindrome or
        // not
    }
}