// Assignment #: 4
// Arizona State University - CSE205
// Name: Wei Chieh Huang
// StudentID: 1215427213
// Lecture: MW 4:35~5:50
// Description: Assignment 4 class displays a menu of choices to a user
//        and performs the chosen task. It will keep asking a user to
//        enter the next choice until the choice of 'Q' (Quit) is entered.

import java.util.*;

public class Assignment4
 {
  public static void main (String[] args)
   {
       // local variables, can be accessed anywhere from the main method
       char input1 = 'Z';
       String inputInfo;
       String title, yearStr, lengthStr, prodName, prodCity, prodState;
       int year, length;
       String line = new String();

       // instantiate a Movie object
       Movie movie1 = new Movie();

       printMenu();

       //Create a Scanner object to read user input
       Scanner scan = new Scanner(System.in);

       do  // will ask for user input
        {
            System.out.println("What action would you like to perform?");
            line = scan.nextLine();
            
            if (line.length() == 1)
            {
                input1 = line.charAt(0);
                input1 = Character.toUpperCase(input1);

                // matches one of the case statement
                switch (input1)
                {
                    case 'A':   //Add Movie
                        System.out.print("Please enter the Movie information:\n");
                        System.out.print("Enter its title:\n");
                        title = scan.nextLine();
                        movie1.setMovieTitle(title);

                        System.out.print("Enter its length:\n");
                        lengthStr = scan.nextLine();
                        length = Integer.parseInt(lengthStr);
                        movie1.setLength(length);
                    
                        System.out.print("Enter its year:\n");
                        yearStr = scan.nextLine();
                        year = Integer.parseInt(yearStr);
                        movie1.setYear(year);
                        
                        System.out.print("Enter its production company name:\n");
                        prodName = scan.nextLine();
                        System.out.print("Enter its production company's city:\n");
                        prodCity = scan.nextLine();
                        System.out.print("Enter its production company's state:\n");
                        prodState = scan.nextLine();
                        movie1.setProdCompany(prodName, prodCity, prodState);
                        break;
                    case 'D':   //Display Movie
                        System.out.print(movie1);
                        break;
                    case 'Q':   //Quit
                        break;
                    case '?':   //Display Menu
                        printMenu();
                        break;
                    default:
                        System.out.print("Unknown action\n");
                        break;
                }
          }
         else
          {
              System.out.print("Unknown action\n");
          }
        } while (input1 != 'Q' || line.length() != 1);
   }

  /** The method printMenu displays the menu to a user **/
  public static void printMenu()
   {
     System.out.print("Choice\t\tAction\n" +
                        "------\t\t------\n" +
                        "A\t\tAdd Movie\n" +
                        "D\t\tDisplay Movie\n" +
                        "Q\t\tQuit\n" +
                        "?\t\tDisplay Help\n\n");
  }
}
