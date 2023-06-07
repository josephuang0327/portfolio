using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace HW1_Part1
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract]
    public interface IService1
    {

        [OperationContract]
        string reverse(string str);

        [OperationContract]
        stringStatistic analyzeStr(string str);

        // TODO: Add your service operations here
    }

    [DataContract]
    public class stringStatistic
    {
        public int uppercount;
        public int lowercount;
        public int digitcount;
        public int vowelcount;


        [DataMember]
        public int uppercase
        {
            get { return uppercount; }
            set { uppercount = value; }
        }

        [DataMember]
        public int lowercase
        {
            get { return lowercount; }
            set { lowercount = value; }
        }

        [DataMember]
        public int digit
        {
            get { return digitcount; }
            set { digitcount = value; }
        }

        [DataMember]
        public int vowel
        {
            get { return vowelcount; }
            set { vowelcount = value; }
        }


        public stringStatistic(int newuppercount, int newlowercount, int newdigitcount, int newvowelcount)
        {
            uppercase = newuppercount;
            lowercase = newlowercount;
            digit = newdigitcount;
            vowel = newvowelcount;
        }
    }
}
