using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace LectureActivity2
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        public int sum(int inputValue)
        {
            int result = 0;
            while(inputValue > 0)
            {
                int temp = inputValue % 10;
                result += temp;
                inputValue = inputValue / 10;
            }

            return result;
        }

        public int count(string text)
        {
            int vowelCount = 0;
            for(int i = 0; i < text.Length; i++)
            {
                if (text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || text[i] == 'u')
                {
                  vowelCount++;
                }
            }
            return vowelCount;
        }

    }
}
