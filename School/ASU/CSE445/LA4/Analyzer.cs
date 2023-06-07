using System;
using System.Threading; // using namespace

class Analyzer
{
	string analyzeStr;
	public Analyzer(string str) { analyzeStr = str; }
	
	public void runDigit()
    {
		int count = 0;
		for (int i = 0; i < analyzeStr.Length; i++)
		{
			if ((analyzeStr[i] >= '0') && (analyzeStr[i] <= '9'))
			{
				count++;
			}
		}
		Console.WriteLine("Digits Count: " + count);
	}
	public void runUpper()
	{
		int count = 0;
		for (int i = 0; i < analyzeStr.Length; i++)
		{
			if (char.IsUpper(analyzeStr[i]))
			{
				count++;
			}
		}
		Console.WriteLine("Uppercase Count: " + count);
	}
	public void runPalin()
	{
		bool check = false;
		char[] charArr = analyzeStr.ToCharArray();
		Array.Reverse(charArr);
		string revStr = new string(charArr);
		if(analyzeStr.Equals(revStr))
        {
			check = true;
        }
		if(check)
        {
			Console.WriteLine("Palindrome Check: Is a Palindrom!" );
		}
        else
        {
			Console.WriteLine("Palindrome Check: Is NOT a Palindrom!");
		}
	}
}
