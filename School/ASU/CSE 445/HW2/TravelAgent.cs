using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace HW2
{
    public class TravelAgent
    {
        static Random rnum = new Random();
        int senderID, amount, cardNo, receiverID;
        string encodedOrder, time;
        int currentTicketPrice, previousTicketPrice;
        Airline airline = new Airline();
        int ordercount1 = 0;
        public TravelAgent(int sid, int card, int rid)
        {
            senderID = sid;
            cardNo = card;
            receiverID = rid;
            amount = 0;
            encodedOrder = "";
            currentTicketPrice = 10;
            previousTicketPrice = 1000;
            time = "";
        }

        public void placeOrder()
        {
            amount = 10;
            OrderObj oo = new OrderObj(senderID, cardNo, amount, receiverID, time);
            Monitor.Enter(Program.bo);
            try
            {
                Console.WriteLine("\nThread" + Thread.CurrentThread.Name + " Setting Order");
                Program.bo.setBuffer(oo);
                Program.bo.scan(getEncodedOrder());
            }
            finally { Monitor.Exit(Program.bo); }
        }

        public void TravelAgentFunc()
        {
            int ransleep = rnum.Next(500, 1250);
            for(int i = 0; i < 10; i++) // how many price cut event
            {
                placeOrder();
                ordercount1++;
                Thread.Sleep(ransleep);
                if(currentTicketPrice < previousTicketPrice)
                {
                    Console.WriteLine("Travel Agent {0} has get a new low price: ${1} each", Thread.CurrentThread.Name, currentTicketPrice);
                }
            }
            summary();
        }

        public void summary()
        {
            Thread.Sleep(5000);
            Console.WriteLine("\n--------------------Travel Agent {0} Summary--------------------", Thread.CurrentThread.Name);
            Console.WriteLine("Total number of order: " + ordercount1);
            Console.WriteLine("Travel Agent {0} has get a total of : 10 price cut events", Thread.CurrentThread.Name);
            Console.WriteLine("Travel Agent {0} has order a total of : 10 orders", Thread.CurrentThread.Name);
            if(Thread.CurrentThread.Name == "T1")
            {
                Console.WriteLine("Number of success orders for Airline 1: {0}", Program.bo.getAcceptt1a1());
                Console.WriteLine("Number of unsuccess orders for Airline 1: {0}", Program.bo.getRejectt1a1());
                Console.WriteLine("Number of success orders for Airline 2: {0}", Program.bo.getAcceptt1a2());
                Console.WriteLine("Number of unsuccess orders for Airline 2: {0}", Program.bo.getRejectt1a2());
            }
            else if(Thread.CurrentThread.Name == "T2")
            {
                Console.WriteLine("Number of success orders for Airline 1: {0}", Program.bo.getAcceptt2a1());
                Console.WriteLine("Number of unsuccess orders for Airline 1: {0}", Program.bo.getRejectt2a1());
                Console.WriteLine("Number of success orders for Airline 2: {0}", Program.bo.getAcceptt2a2());
                Console.WriteLine("Number of unsuccess orders for Airline 2: {0}", Program.bo.getRejectt2a2());
            }

        }

        public void ticketOnSale(int p)
        {
            currentTicketPrice = p;
        }

        public void getEncoded(string c)
        {
            encodedOrder = c;
           // Console.WriteLine("Encoded: " + encodedOrder);
        }

        public string getEncodedOrder()
        {
            return encodedOrder;
        }
    }
}
