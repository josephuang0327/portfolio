using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace HW2
{
    class encodeDecode
    {
        public delegate void encodeDelegate();
        public static event encodeDelegate encoded;

        public static void getOrder()
        {
            Monitor.Enter(Program.bo);
            try
            {
                string order = Program.bo.getBuffer();
                //Console.WriteLine("Got the order : " + order);

                Program.t1.getEncoded(Encode(Program.bo.getSID(), Program.bo.getCard(), Program.bo.getAmount(), Program.bo.getRID(), Program.bo.getTime()));
                Program.t2.getEncoded(Encode(Program.bo.getSID(), Program.bo.getCard(), Program.bo.getAmount(), Program.bo.getRID(), Program.bo.getTime()));
            }

            finally { Monitor.Exit(Program.bo); }
        }

        public static string Encode(int sid, int card, int amount, int rid, string time)
        {
            string result = "";

            result += sid.ToString() + "," + card.ToString() + "," + amount.ToString() + "," + rid.ToString() + "," + time.ToString();

            return result;
        }

        public static int[] Decode(String str)
        {
            int[] decodelist = new int[5] ;
            string[] strlist = str.Split(',');
            decodelist[0] = int.Parse(strlist[0]);
            decodelist[1] = int.Parse(strlist[1]);
            decodelist[2] = int.Parse(strlist[2]);
            decodelist[3] = int.Parse(strlist[3]);
            decodelist[4] = int.Parse(strlist[4]);
            return decodelist;
        }


    }

}
