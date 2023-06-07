using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace HW2
{
    public delegate void priceCutEvent(Int32 pr);
    class Program
    {
        public static BufferObj bo = new BufferObj();
        public static TravelAgent t1 = new TravelAgent(1, 100, 1);
        public static TravelAgent t2 = new TravelAgent(2, 200, 2);
        public static TravelAgent t3 = new TravelAgent(3, 300, 3);
        public static TravelAgent t4 = new TravelAgent(4, 400, 4);
        public static TravelAgent t5 = new TravelAgent(5, 500, 5);
        TravelAgent ta;
        static void Main(string[] args)
        {

            Airline ticket = new Airline();
            Airline ticket1 = new Airline();
            Thread airline = new Thread(new ThreadStart(ticket.PricingModel));
            airline.Start();

            Thread.Sleep(450);

            Thread airline1 = new Thread(new ThreadStart(ticket1.PricingModel));
            airline1.Start();

            Airline.priceCut += new priceCutEvent(t1.ticketOnSale);
            Airline.priceCut += new priceCutEvent(t2.ticketOnSale);

            bo.makingOrder += new BufferObj.orderDelegate(encodeDecode.getOrder);

            Thread taThread = new Thread(new ThreadStart(t1.TravelAgentFunc));
            taThread.Name = "T1";
            taThread.Start();

            Thread taThread1 = new Thread(new ThreadStart(t2.TravelAgentFunc));
            taThread1.Name = "T2";
            taThread1.Start();

            taThread.Join();
            taThread1.Join();


            Console.WriteLine("Done");
            //Console.ReadKey();


            // misread the doc thouught it was 2 TA instead of 5. was looking at 2 airline and no time to change
            /*Thread[] travelagents = new Thread[5];  

             for(int i = 0; i < 5; i++)
             {
                 string name = ("t" + i.ToString());
                 Thread taThread = new Thread(new ThreadStart(name.TravelAgentFunc));
                 taThread.Name = "T1";
                 taThread.Start();
             }*/






        }
    }
}
