using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace LectureActivity4
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter a string to analyze:");
            string str = Console.ReadLine();
            Analyzer analyzer = new Analyzer(str);

            Thread digit = new Thread(new ThreadStart(analyzer.runDigit));
            Thread upper = new Thread(new ThreadStart(analyzer.runUpper));
            Thread palin = new Thread(new ThreadStart(analyzer.runPalin));

            digit.Start();
            upper.Start();
            palin.Start();


            digit.Join();
            upper.Join();
            palin.Join();

            Console.WriteLine("Main Thread Completed");
        }
    }
}
