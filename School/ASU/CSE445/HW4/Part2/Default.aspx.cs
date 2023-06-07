using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void verifyButton_Click(object sender, EventArgs e)
    {
        // a regular set up of httpwebrequest
        string url = @"http://localhost:58935/Service.svc/verify?xml=" + verifyXmlBox.Text + "&xmls=" + verifyXsdBox.Text;
        HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
        WebResponse response = request.GetResponse();
        Stream datastream = response.GetResponseStream();
        StreamReader reader = new StreamReader(datastream);
        var responseReader = reader.ReadToEnd();
        response.Close();

        string validate = JsonConvert.DeserializeObject<string>(responseReader);
        verifyResult.Text = validate;
    }

    protected void searchButton_Click(object sender, EventArgs e)
    {
        string url = @"http://localhost:58935/Service.svc/xPath?xml=" + searchXmlBox.Text + "&exp=" + searchExpBox.Text;
        HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
        WebResponse response = request.GetResponse();
        Stream datastream = response.GetResponseStream();
        StreamReader reader = new StreamReader(datastream);
        var responseReader = reader.ReadToEnd();
        response.Close();

        string pathResult = JsonConvert.DeserializeObject<string>(responseReader);
        searchResult.Text = pathResult;
    }
}