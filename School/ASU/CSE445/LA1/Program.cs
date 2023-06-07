using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LectureActivity1
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceReference1.CountryInfoServiceSoapTypeClient myClient = new ServiceReference1.CountryInfoServiceSoapTypeClient("CountryInfoServiceSoap");

            Console.WriteLine("Enter Country Name:");
            string countryInput = Console.ReadLine();

            Console.WriteLine("Result: \n");

            string isocode = myClient.CountryISOCode(countryInput);
            string countryName = myClient.CountryName(isocode);
            string capital = myClient.CapitalCity(isocode);
            var currency = myClient.CountryCurrency(isocode);
            string isocurrency = currency.sISOCode;

            Console.WriteLine(countryName);
            Console.WriteLine(isocode);
            Console.WriteLine(capital);
            Console.WriteLine(isocurrency);


        }
    }
}
