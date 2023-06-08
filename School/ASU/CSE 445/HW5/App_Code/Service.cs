using HtmlAgilityPack;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text.RegularExpressions;
using System.Web.Http;

// NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service" in code, svc and config file together.
public class Service : IService
{
    public string[] tenwords(string url)
    {
        //example url :　http://localhost:50718/api/first/tenwords?url=https://www.wsj.com/livecoverage/russia-ukraine-latest-news-2022-03-31
        string[] arr = new string[10];

        HtmlWeb web_obj = new HtmlWeb();
        var htmlDoc = web_obj.Load(url);
        HtmlNode node = htmlDoc.DocumentNode.SelectSingleNode("//body");
        var content = node.InnerText;
        var cotentwords = Regex.Split(content, @"[\W\d]+").Where(c => !String.IsNullOrWhiteSpace(c));
        var freqWord =
            (from word in cotentwords
             group word by word into Gw
             select new { Word = Gw.Key, Freq = Gw.Count() }).OrderByDescending(word => word.Freq).Take(10);

        int i = 0;

        foreach (var str in freqWord)
        {
            String ele = str.ToString();
            arr[i] = ele.Split(',')[0].Replace("{ Word =", String.Empty);
            i++;
            if (i == 10)
            {
                break;
            }
        }

        return arr;
    }

    public string wordsfilter(string str)
    {
        List<string> stop_word = new List<string>()
            {
                "a", "able", "about", "above", "according", "accordingly", "across",
                "actually", "after", "afterwards", "again", "against", "ain't", "all",
                "allow", "allows", "almost", "alone", "along", "already", "also", "although",
                "always", "am", "among", "amongst", "an", "and", "another", "any", "anybody",
                "anyhow", "anyone", "anything", "anyway", "anyways", "anywhere", "apart", "appear",
                "appreciate","appropriate","are","aren't","around","as","a's","aside","ask","asking",
                "associated","at","available","away","awfully","be", "became", "because", "become",
                "becomes", "becoming", "been", "before", "beforehand", "behind", "being", "believe",
                "below", "beside", "besides", "best", "better", "between", "beyond", "both", "brief",
                "but", "by", "came", "can", "cannot", "cant", "can't", "cause", "causes", "certain",
                "certainly", "changes", "clearly", "c'mon", "co", "com", "come", "comes", "concerning",
                "consequently", "consider", "considering", "contain", "containing", "contains",
                "corresponding", "could", "couldn't", "course", "c's", "currently", "definitely",
                "described", "despite", "did", "didn't", "different", "do", "does", "doesn't", "doing",
                "done", "don't", "down", "downwards", "during", "each", "edu", "eg", "eight", "either",
                "else", "elsewhere", "enough", "entirely", "especially", "et", "etc", "even", "ever",
                "every", "everybody", "everyone", "everything", "everywhere", "ex", "exactly", "example",
                "except", "far", "few", "fifth", "first", "five", "followed", "following", "follows",
                "for", "former", "formerly", "forth", "four", "from", "further", "furthermore", "get",
                "gets", "getting", "given", "gives", "go", "goes", "going", "gone", "got", "gotten",
                "greetings", "had", "hadn't", "happens", "hardly", "has", "hasn't", "have", "haven't",
                "having", "he", "he'd", "he'll", "hello", "help", "hence", "her", "here", "hereafter",
                "hereby", "herein", "here's", "hereupon", "hers", "herself", "he's", "hi", "him",
                "himself", "his", "hither", "hopefully", "how", "howbeit", "however", "how's", "i",
                "i'd", "ie", "if", "ignored", "i'll", "i'm", "immediate", "in", "inasmuch", "inc",
                "indeed", "indicate", "indicated", "indicates", "inner", "insofar", "instead", "into",
                "inward", "is", "isn't", "it", "it'd", "it'll", "its", "it's", "itself", "i've", "just",
                "keep", "keeps", "kept", "know", "known", "knows", "last", "lately", "later", "latter",
                "latterly", "least", "less", "lest", "let", "let's", "like", "liked", "likely", "little",
                "look", "looking", "looks", "ltd", "mainly", "many", "may", "maybe", "me", "mean",
                "meanwhile", "merely", "might", "more", "moreover", "most", "mostly", "much", "must",
                "mustn't", "my", "myself", "name", "namely", "nd", "near", "nearly", "necessary", "need",
                "needs", "neither", "never", "nevertheless", "new", "next", "nine", "no", "nobody",
                "non", "none", "noone", "nor", "normally", "not", "nothing", "novel", "now", "nowhere",
                "obviously", "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones",
                "only", "onto", "or", "other", "others", "otherwise", "ought", "our", "ours", "ourselves",
                "out", "outside", "over", "overall", "own", "particular", "particularly", "per", "perhaps",
                "placed", "please", "plus", "possible", "presumably", "probably", "provides", "que", "quite",
                "qv", "rather", "rd", "re", "really", "reasonably", "regarding", "regardless", "regards",
                "relatively", "respectively", "right", "said", "same", "saw", "say", "saying", "says", "second",
                "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves",
                "sensible", "sent", "serious", "seriously", "seven", "several", "shall", "shan't", "she", "she'd",
                "she'll", "she's", "should", "shouldn't", "since", "six", "so", "some", "somebody", "somehow",
                "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry",
                "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure", "take", "taken",
                "tell", "tends", "th", "than", "thank", "thanks", "thanx", "that", "thats", "that's", "the",
                "their", "theirs", "them", "themselves", "then", "thence", "there", "thereafter", "thereby",
                "therefore", "therein", "theres", "there's", "thereupon", "these", "they", "they'd", "they'll",
                "they're", "they've", "think", "third", "this", "thorough", "thoroughly", "those", "though",
                "three", "through", "throughout", "thru", "thus", "to", "together", "too", "took", "toward",
                "towards", "tried", "tries", "truly", "try", "trying", "t's", "twice", "two", "un", "under",
                "unfortunately", "unless", "unlikely", "until", "unto", "up", "upon", "us", "use", "used",
                "useful", "uses", "using", "usually", "value", "various", "very", "via", "viz", "vs", "want",
                "wants", "was", "wasn't", "way", "we", "we'd", "welcome", "well", "we'll", "went", "were",
                "we're", "weren't", "we've", "what", "whatever", "what's", "when", "whence", "whenever",
                "when's", "where", "whereafter", "whereas", "whereby", "wherein", "where's", "whereupon",
                "wherever", "whether", "which", "while", "whither", "who", "whoever", "whole", "whom",
                "who's", "whose", "why", "why's", "will", "willing", "wish", "with", "within", "without",
                "wonder", "won't", "would", "wouldn't", "yes", "yet", "you", "you'd", "you'll", "your",
                "you're", "yours", "yourself", "yourselves", "you've", "zero"
            };
        string lowerStr = str.ToLower();
        string resultStr = string.Join(" ", lowerStr.Split(' ').Except(stop_word));
        return resultStr.ToString();
    }

    public string[] newsfocus([FromUri] string[] topic)
    {
        WebClient client = new WebClient();
        string temp = null;
        //query from the guardian documentation https://open-platform.theguardian.com/documentation/

        string reqQuery = "http://content.guardianapis.com/search?q=";

        for (int i = 0; i < topic.Length; i++)
        {
            temp += topic[i] + " ";
        }

        reqQuery += temp;
        reqQuery += "&api-key=54da7084-c161-4388-86c2-eccd64b2bdc3";

        string response = client.DownloadString(reqQuery);
        dynamic jsonParsed = JObject.Parse(response);
        int count = jsonParsed.response.pageSize;

        urlinfo[] urlList = new urlinfo[count];
        for (int i = 0; i < count; i++)
        {
            urlList[i] = new urlinfo();
            urlList[i].weburl = Convert.ToString(jsonParsed["response"]["results"][i]["webUrl"]);
        }

        string[] result = new string[count];

        for (int i = 0; i < count; i++)
        {
            result[i] = urlList[i].url_string();
        }

        return result;
    }
    public class urlinfo
    {
        public string weburl;
        public string url_string()
        {
            return this.weburl;
        }
    }
}
