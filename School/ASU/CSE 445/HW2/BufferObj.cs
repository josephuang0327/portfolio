using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace HW2
{
    class BufferObj
    {

        private OrderObj order;
        private Object BufferLock = new Object();
        public delegate void orderDelegate();
        public event orderDelegate makingOrder;
        public Airline airline = new Airline();

        const int Size = 3;
        OrderObj[] data = new OrderObj[Size];
        int head = 0, tail = 0, n = 0;
        bool writable = true;

        public BufferObj()
        {
            order = null;
        }

        public void setBuffer(OrderObj newOrder)
        {
            /*lock (BufferLock)
            {
                while (n == Size)
                {
                    Monitor.Wait(BufferLock);
                }

                Console.WriteLine("writing thread enters");
                data[tail] = newOrder;
                tail = (tail + 1) % Size;
                n++;
                Console.WriteLine("writing thread " + Thread.CurrentThread.Name + " " + newOrder + " " + n);
                makingOrder();
                Monitor.Pulse(BufferLock);
            }*/

            while(!writable)
            {
                try
                {
                    Monitor.Wait(this);
                }
                catch { }
            }

            order = newOrder;
            writable = false;
            makingOrder();
            Monitor.PulseAll(this);
        }

        public String getBuffer()
        {
           /*lock(BufferLock) 
            {
                while(n == 0)
                {
                    Monitor.Wait(BufferLock);
                }

                Console.WriteLine("reading thread entered");
                OrderObj order = data[head];
                head = (head + 1) % Size;
                n--;

                Console.WriteLine("Reading thread " + Thread.CurrentThread.Name + " " + order + " " + n);
                Monitor.Pulse(BufferLock);

                return order.getorder();
            }*/
            while(writable)
            {
                try
                {
                    Monitor.Wait(this);
                }
                catch { }
            }
            writable = true;
            Monitor.PulseAll(this);
            return order.getorder();

        }

        public void scan(string str) //scan if order valid
        {
            //Console.WriteLine("work123?: " + str);
            airline.OrderProcessing(str);

        }

        public int getSID()
        {
            return order.getSID();
        }
        public int getCard()
        {
            return order.getCard();
        }
        public int getAmount()
        {
            return order.getAmount();
        }
        public int getRID()
        {
            return order.getRID();
        }
        public string getTime()
        {
            return order.getTime();
        }
       
        public int getAcceptt1a1()
        {
            return airline.getAcceptt1a1();
        }
        public int getAcceptt1a2()
        {
            return airline.getAcceptt1a2();
        }
        public int getRejectt1a1()
        {
            return airline.getRejectt1a1();
        }
        public int getRejectt1a2()
        {
            return airline.getRejectt1a2();
        }
        public int getAcceptt2a1()
        {
            return airline.getAcceptt2a1();
        }
        public int getAcceptt2a2()
        {
            return airline.getAcceptt2a2();
        }
        public int getRejectt2a1()
        {
            return airline.getRejectt2a1();
        }
        public int getRejectt2a2()
        {
            return airline.getRejectt2a2();
        }


    }
}
