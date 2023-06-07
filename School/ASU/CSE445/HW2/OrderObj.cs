using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HW2
{
    class OrderObj
    {
        private int senderID, cardNo, amount, receiverID;
        private string time;

        public OrderObj(int s, int c, int r, int a, string t)
        {
            senderID = s;
            cardNo = c;
            receiverID = r;
            amount = a;
            time = t;
        }

        public String getorder()
        {
            return "sender:" + senderID + " cardNo:" + cardNo + " amont:" + amount + " receiverID: " + receiverID;
        }

        public int getSID()
        {
            return senderID;
        }
        public int getCard()
        {
            return cardNo;
        }
        public int getAmount()
        {
            return amount;
        }
        public int getRID()
        {
            return receiverID;
        }

        public string getTime()
        {
            time = GetTimestamp(DateTime.Now);
            return time;
        }
        public static String GetTimestamp(DateTime value)
        {
            return value.ToString("MMddHHmmss");
        }
    }
}
