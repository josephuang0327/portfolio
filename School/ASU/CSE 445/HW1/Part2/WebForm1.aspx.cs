using System;
using System.IO;
using System.Drawing.Imaging;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace HW1_Part2
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            Image1.ImageUrl = "~/imageProcess.aspx";
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            ServiceReference1.ServiceClient myClient1 = new ServiceReference1.ServiceClient();

            String strToEncrypt = TextBox1.Text;

            string encryptedStr = myClient1.Encrypt(strToEncrypt);
            TextBox3.Text = encryptedStr;
            TextBox2.Text = encryptedStr;
        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            ServiceReference1.ServiceClient myClient1 = new ServiceReference1.ServiceClient();

            String strToDecrypt = TextBox2.Text;

            if (String.IsNullOrEmpty(TextBox2.Text))
            {
                Label7.Text = "Please Encrypt a message first";
            }
            else
            {
                string decryptedStr = myClient1.Decrypt(strToDecrypt);
                TextBox4.Text = decryptedStr;
                Label7.Text = "";
            }

        }

        protected void Button3_Click(object sender, EventArgs e)
        {
            ServiceReference2.ServiceClient fromService = new ServiceReference2.ServiceClient();

            string userLength = TextBox5.Text;
            Session["userLength"] = userLength;
            string myStr = fromService.GetVerifierString(userLength);
            Session["generatedString"] = myStr;
            Image1.Visible = true;


        }

        protected void Button4_Click(object sender, EventArgs e)
        {
            ServiceReference2.ServiceClient myClient2 = new ServiceReference2.ServiceClient();

            string strToCheck = Session["generatedString"].ToString();
            if(strToCheck == TextBox6.Text)
            {
                Label10.Text = "Correct!";
            }
            else
            {
                Label10.Text = "Incorrect! Try again!";
            }

        }
    }
}