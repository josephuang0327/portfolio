/**
 * Name: 	Wei Chieh Huang
 * ASUID: 	1215427213
 * Course:	CSE360,70605
 * Assignment#4
 * Description: check if the string is palindrome or not. If the string
 * contains all alphanumeric character, or contains none alphanumeric character
 * than it is a palindrome. If it is a mixture of both then it is not a
 * palindrome.
 */
import java.util.Arrays;

public class Palindrome 
{
	private String testString;

	/**
	 * initialize the tesString variable
	 * @param testString, take in a string from the user
	 */
	public Palindrome(String input)
	{
		testString = input;
	}
	/**
	 * check if the user input all alphanumeric characters, mixture of both,
	 * or non alphanumeric character
	 * @return, return if the input is palindrome or not
	 */
	public boolean isPalindrome()
	{
		boolean checkAlpha = false;
			
		//check if the input is in alphanumeric form
		checkAlpha = testString.matches("[A-Za-z0-9]+");
		
		//check if there is no alphanumeric character		// only checks if it has weird char have to check both as well.
		boolean hasNonAlpha = testString.matches("^(?:\\W|\\s)*$");
		if(hasNonAlpha == true && checkAlpha == false)
		{
			return true;
		}
		
		char[] inOrder = new char[testString.length()];
		char[] postOrder = new char[testString.length()];
		
		// if input are all alphanumeric character
		if(checkAlpha == true)
		{
			inOrder = testString.toCharArray();
			
			//copy the string backward
			for(int i = 0; i < testString.length(); i++)
			{
				postOrder[i] = inOrder[testString.length() - i -1];
			}
	
			//check if two array are equal
			if(Arrays.equals(inOrder, postOrder))
			{
				return true;
			}
		}
		return false;
		
	}
}
