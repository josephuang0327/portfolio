import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import java.util.Scanner;
/**
 * Name: 	Wei Chieh Huang
 * ASUID: 	1215427213
 * Course:	CSE360,70605
 * Assignment#4
 * Description: call the function is Palindrome.java class and test if the
 * function is working properly.
 */

class PalindromeTest 
{
	/**
	 * Test if the string is palindrom when it contains all alphanumeric 
	 * characters. The result from Palindrome.java should be true.
	 */
	@Test
	public void testAlpha()
	{	
		boolean expectedAlpha = true;

		// test if string is the same from and back 
		Palindrome alpha = new Palindrome("EYE");
		boolean actual = alpha.isPalindrome();		//actual should return true
		assertEquals(expectedAlpha, actual);		// work
		

	}
	/**
	 * Test if the string is palindrom when it contains all non-alphanumeric
	 * characters. The result from Palindrome.java should be true.
	 */
	@Test
	public void testNonAlpha()
	{
		boolean expectedNonAlpha = true;
		
		// test if string are all non-alphanumeric character
		Palindrome nonAlpha = new Palindrome("@#$%^&*");
		boolean actual = nonAlpha.isPalindrome();	//actual should return true
		assertEquals(expectedNonAlpha, actual);		// work
	}
	/**
	 * Test if the string is palindrom when it contains alphanumeric character
	 * and non-alphanumeric characters. The result from Palindrome.java should
	 * be false.
	 */
	@Test
	public void testMixture()
	{
		boolean expectedMixture = false;
		
		// test if string contains both
		Palindrome mixture = new Palindrome("abc&*asd");
		boolean actual = mixture.isPalindrome();	//actual should return false
		assertEquals(expectedMixture, actual);		// work
	}
}
