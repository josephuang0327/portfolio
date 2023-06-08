using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

// NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service" in code, svc and config file together.
public class Service : IService
{
	public string reverse(string str)
	{
		char[] chrArr = str.ToCharArray();
		Array.Reverse(chrArr);
		return new string(chrArr);
	}

	public int AddDigit(string numbers)
	{
		int temp = Convert.ToInt32(numbers);
		int sum = 0;
		while (temp != 0)
		{
			sum += temp % 10;
			temp /= 10;
		}
		return sum;
	}
}
