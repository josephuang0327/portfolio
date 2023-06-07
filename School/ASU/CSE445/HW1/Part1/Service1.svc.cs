using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace HW1_Part1
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        public string reverse(string str)
        {
            char[] cArray = str.ToCharArray();
            Array.Reverse(cArray);
            return new string(cArray);
        }

        public stringStatistic analyzeStr(string str)
        {

            int uppercount = 0;
            int lowercount = 0;
            int digitcount = 0;
            int vowelcount = 0;

            int uppercase()
            {
                for(int i = 0; i < str.Length; i++)
                {
                    if (char.IsUpper(str[i])) uppercount++;
                }
                return uppercount;
            }
            int lowercase()
            {
                for (int i = 0; i < str.Length; i++)
                {
                    if(char.IsLower(str[i])) lowercount++;
                }
                return lowercount;
            }
            int digit()
            {
                for (int i = 0; i < str.Length; i++)
                {
                    if (char.IsDigit(str[i])) digitcount++;
                }
                return digitcount;
            }
            int vowel()
            {
                string tempStr = str.ToLower();
                for (int i = 0; i < str.Length; i++)
                {
                    if (tempStr[i] == 'a' || tempStr[i] == 'e' || tempStr[i] == 'i' || tempStr[i] == 'o' || tempStr[i] == 'u')
                    {
                        vowelcount++;
                    }
                }
                return vowelcount;
            }

            uppercount = uppercase();
            lowercount = lowercase();
            digitcount = digit();
            vowelcount = vowel();

            stringStatistic aStr = new stringStatistic(uppercount, lowercount, digitcount, vowelcount);


            return aStr;
        }
    }
}
