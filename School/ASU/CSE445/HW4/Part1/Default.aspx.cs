using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;
using System.Web.UI.HtmlControls;

namespace Hw4
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void ProcessButton_Click(object sender, EventArgs e)
        {
            XmlDocument xmlDoc = new XmlDocument();
            
            Label dynamicLabel = new Label();
            div1.Controls.Add(dynamicLabel);

            try
            {
                xmlDoc.Load(urlTextBox.Text);
                XmlNodeList hotels = xmlDoc.GetElementsByTagName("Hotel");

                for(int i = 0; i < hotels.Count; i++)
                {
                    //references from discord to add element dynamically
                    HtmlGenericControl hotelDiv = new HtmlGenericControl("div");
                    HtmlGenericControl names = new HtmlGenericControl("p");
                    HtmlGenericControl stars = new HtmlGenericControl("p");
                    HtmlGenericControl contact = new HtmlGenericControl("p");
                    HtmlGenericControl phone = new HtmlGenericControl("p");
                    HtmlGenericControl email = new HtmlGenericControl("p");
                    HtmlGenericControl address = new HtmlGenericControl("p");
                    HtmlGenericControl busline = new HtmlGenericControl("p");
                    HtmlGenericControl spacing = new HtmlGenericControl("p");

                    names.InnerText = "Hotel Name: " + hotels[i].ChildNodes[0].InnerText;
                    stars.InnerText = "Stars: " + hotels[i].Attributes[0].InnerText;
                    
                    XmlNodeList contacts = xmlDoc.GetElementsByTagName("Contact");
                    for(int j = 0; j < contacts.Count; j++)
                    {
                        phone.InnerText = "Phone: " + contacts[i].ChildNodes[0].InnerText;
                        email.InnerText = "Email: " + contacts[i].ChildNodes[1].InnerText;
                    }

                    XmlNodeList addresses = xmlDoc.GetElementsByTagName("Address");
                    for (int k = 0; k < addresses.Count; k++)
                    {
                        address.InnerText = "Address: " + addresses[i].ChildNodes[0].InnerText
                                                         + addresses[i].ChildNodes[1].InnerText
                                                         + addresses[i].ChildNodes[2].InnerText
                                                         + addresses[i].ChildNodes[3].InnerText;
                        XmlElement tempNode= xmlDoc.DocumentElement;
                        if(hotels[i].ChildNodes[2].Attributes.Count == 1)
                        {
                            busline.InnerText = "Bus Lines: " + hotels[i].ChildNodes[2].Attributes[0].InnerText;
                        }
                        else
                        {
                            busline.InnerText = "Bus line not available";
                        }

                    }
                    spacing.InnerText = "-----------------------------------------------";
                    hotelDiv.Controls.Add(names);
                    hotelDiv.Controls.Add(stars);
                    hotelDiv.Controls.Add(contact);
                    hotelDiv.Controls.Add(phone);
                    hotelDiv.Controls.Add(email);
                    hotelDiv.Controls.Add(address);
                    hotelDiv.Controls.Add(busline);
                    hotelDiv.Controls.Add(spacing);
                    div1.Controls.Add(hotelDiv);
                }
            }
            finally 
            {
                
            }
        }
    }
}