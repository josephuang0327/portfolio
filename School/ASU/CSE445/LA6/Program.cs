using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using System.Net;
using System.IO;
using System.Xml;
//using System.Web.Script.Serialization;
using System.Net.Http;
using Newtonsoft.Json;

namespace LectureActivity6
{
    class Program
    {
        static void Main(string[] args)
        {
            GetNews();
        }

        public static void GetNews()
        {
            //bf09af856b0446c9ac0d180b21ec0f72
            string url = @"https://newsapi.org/v1/articles?source=techcrunch&apiKey=bf09af856b0446c9ac0d180b21ec0f72";
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            WebResponse response = request.GetResponse();
            Stream dataStream = response.GetResponseStream();
            StreamReader sreader = new StreamReader(dataStream);
            string responsereader = sreader.ReadToEnd();
            response.Close();

            //Console.WriteLine(responsereader);

            RootObject newObj = JsonConvert.DeserializeObject<RootObject>(responsereader);
            int i = 0;

            while (i < newObj.articles.Count)
            {
                Console.WriteLine(newObj.articles[i].title);
                Console.WriteLine(newObj.articles[i].author);
                Console.WriteLine(newObj.articles[i].url + "\n");
                i++;
            }
        }
        public class Articles
        {
            public string @author { get; set; }
            public string title { get; set; }
            public string description { get; set; }
            public string url { get; set; }
            public string urlToImage { get; set; }
            public string publishedAt { get; set; }
        }
        public class RootObject
        {
            public string status { get; set; }
            public string source { get; set; }
            public string sortBy { get; set; }
            public List<Articles> articles { get; set; }
        }

        
    }
}
