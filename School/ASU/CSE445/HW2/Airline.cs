using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace HW2
{
    public class Airline
    {
        static Random rnum = new Random();
        public static event priceCutEvent priceCut;
        private static int ticketPrice = 10;
        private encodeDecode encodeDecode;
        int a1reject = 0, a1accept = 0;
        int a2reject = 0, a2accept = 0;
        int[] t1ar = new int[4];
        int[] t2ar = new int[4];

        public int getPrice() { return ticketPrice; }

        public static void changePrice(int price)
        {
            if(price < ticketPrice) // if there is a price cut
            {
                if(priceCut != null) // if there is subscriber to price cut
                {
                    priceCut(price); // send event to subscribers
                }
            }

            ticketPrice = price;
        }

        public void PricingModel()
        {
            for(int i = 0; i < 50; i++)
            {
                Thread.Sleep(500);
                int p = rnum.Next(10, 30);
                Airline.changePrice(p);
            }
        }

        public void OrderProcessing(string str)
        {
            int[] checklist = new int[5];
            double totalprice = 0;
            double salestax = 1.081;
            bool validorder = false;
            checklist = encodeDecode.Decode(str);

            if(checklist[1] >= 100 && checklist[1] <= 200) // credit card number is between 100 ~ 200 then it is valid
            {
                //Console.WriteLine("\nFrom receiver ID: " + checklist[3]);
                //Console.WriteLine("valid card number: " + checklist[1]);
                validorder = true;
            }

            if(validorder)
            {
                Console.WriteLine("----- Valid order, Order Processing... -----");
                totalprice = checklist[2] * salestax * getPrice();
                Console.WriteLine("total order price: " + totalprice);
                if(checklist[2] == 1)
                {
                    if(checklist[0] == 1)
                    {
                        t1ar[0]++; // t1 a1 accept
                    }
                    if (checklist[0] == 2)
                    {
                        t2ar[0]++; // t2 a1 accept
                    }
                    //Console.WriteLine("a1accept: " + a1accept);
                }
                else if (checklist[2] == 2)
                {
                    if (checklist[0] == 1)
                    {
                        t1ar[1]++; // t1 a2 accept
                    }
                    if (checklist[0] == 2)
                    {
                        t2ar[1]++; // t2 a2 accept
                    }
                    //Console.WriteLine("a2accept: " + a2accept);
                }
                //Console.WriteLine("current price: " + getPrice() + "\n");
                //Console.WriteLine("current time: " + checklist[4]);
                Console.WriteLine("Time When Order Process: " + GetTimestamp(DateTime.Now));
            }
            else
            {
                Console.WriteLine("----- Invalid order, Order Reject... -----");
                if (checklist[2] == 1)
                {
                    if (checklist[0] == 1)
                    {
                        t1ar[2]++; // t1 a1 reject
                    }
                    if (checklist[0] == 2)
                    {
                        t2ar[2]++; // t2 a1 reject
                    }
                    //Console.WriteLine("a1reject: " + a1reject);
                }
                else if (checklist[2] == 2)
                {
                    if (checklist[0] == 1)
                    {
                        t1ar[3]++; // t1 a2 reject
                    }
                    if (checklist[0] == 2)
                    {
                        t2ar[3]++; // t2 a2 reject
                    }
                    //Console.WriteLine("a2reject: " + a2reject);
                }
                Console.WriteLine("Time When Order Process: " + GetTimestamp(DateTime.Now));

            }
        }

        public int getAcceptt1a1()
        {
            return t1ar[0];
        }
        public int getAcceptt1a2()
        {
            return t1ar[1];
        }
        public int getRejectt1a1()
        {
            return t1ar[2];
        }
        public int getRejectt1a2()
        {
            return t1ar[3];
        }
        public int getAcceptt2a1()
        {
            return t2ar[0];
        }
        public int getAcceptt2a2()
        {
            return t2ar[1];
        }
        public int getRejectt2a1()
        {
            return t2ar[2];
        }
        public int getRejectt2a2()
        {
            return t2ar[3];
        }

        public static String GetTimestamp(DateTime value)
        {
            return value.ToString("MMddHHmmssffffff");
        }
    }
}
