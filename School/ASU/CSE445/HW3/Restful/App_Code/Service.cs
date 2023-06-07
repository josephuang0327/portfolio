using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Text.RegularExpressions;
using HtmlAgilityPack;
using System.Net;
using System.IO;

// NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service" in code, svc and config file together.
public class Service : IService
{
	public string GetData(string value)
	{
		return string.Format("You entered: {0}", value);
	}

	public string[] tenwords()
    {
		string[] arr = new string[10];
        arr[0] = "hello";
        /*HtmlWeb web_obj = new HtmlWeb();
        var htmlDoc = web_obj.Load(url);
        HtmlNode node = htmlDoc.DocumentNode.SelectSingleNode("//body");*/

        string url2 = @"https://www.wsj.com/livecoverage/russia-ukraine-latest-news-2022-03-31";
        HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url2);
        WebResponse response = request.GetResponse();
        Stream dataStream = response.GetResponseStream();
        StreamReader sreader = new StreamReader(dataStream);
        string responsereader = sreader.ReadToEnd();
        response.Close();
        Console.WriteLine(responsereader);
        
        /*Console.WriteLine("Node Name: " + node.Name + "\n" + node.OuterHtml);

        var content = node.InnerText;
        var cotentwords = Regex.Split(content, @"[\W\d]+").Where(c => !String.IsNullOrWhiteSpace(c));
        var freqWord =
            (from word in cotentwords
             group word by word into GroupWords
             select new { Word = GroupWords.Key, Freq = GroupWords.Count() }).OrderByDescending(word => word.Freq).Take(10);

        int i = 0;

        foreach (var str in freqWord)
        {
            String ele = str.ToString();
            arr[i] = ele.Split(',')[0].Replace("{ Word =", String.Empty);
            i++;
            if(i == 10)
            {
                break;
            }
        }*/

        return arr;
    }
}
