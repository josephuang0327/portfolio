using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.Xml.XPath;

// NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service" in code, svc and config file together.
public class Service : IService
{
	public string verifyResult = "No Error";
	public string verify(string xml, string xmls)
	{
		//http://localhost:58935/
		//localhost:58935/Service.svc/verify?xml=http://localhost:58935/Hotels.xml&xmls=http://localhost:58935/Hotels.xsd
		//http//localhost:58935/Service.svc/verify?xml=http://localhost:58935/Hotels.xml&xmls=http://localhost:58935/Hotels.xsd
		try
		{
			XmlReaderSettings xmlSetting = new XmlReaderSettings();
			xmlSetting.ValidationType = ValidationType.Schema;
			xmlSetting.Schemas.Add(null, xmls);
			xmlSetting.ValidationFlags |= XmlSchemaValidationFlags.ProcessInlineSchema;
			xmlSetting.ValidationFlags |= XmlSchemaValidationFlags.ProcessSchemaLocation;
			xmlSetting.ValidationFlags |= XmlSchemaValidationFlags.ReportValidationWarnings;
			xmlSetting.ValidationEventHandler += new ValidationEventHandler(hotelsValidationEventHandler);
			xmlSetting.IgnoreWhitespace = true;

			XmlReader hotels = XmlReader.Create(xml, xmlSetting);

			while (hotels.Read()) { }
		}
		catch(Exception ex)
        {
			return ex.Message;
        }
		return verifyResult;
	}
	public void hotelsValidationEventHandler(object sender, ValidationEventArgs e)
	{
		verifyResult = "";
		if (e.Severity == XmlSeverityType.Warning)
		{
			verifyResult = "Warning: " + e.Message;
		}
		else if (e.Severity == XmlSeverityType.Error)
		{
			verifyResult = "Error: " + e.Message;
		}
	}

	//http://localhost:58935/Service.svc/xPath?xml=http://localhost:58935/Hotels.xml&exp=/Hotels/Hotel/Name
	public string pathSearch(string xml, string pathExp)
	{
		XPathDocument dx = new XPathDocument(xml);
		XPathNavigator nav = dx.CreateNavigator();
		XPathNodeIterator iterator = nav.Select(pathExp);
		string data = "";
		while(iterator.MoveNext())
        {
			XPathNodeIterator it = iterator.Current.Select("Name");
			it.MoveNext();
			data += it.Current.Value + ", ";
		}
		return data;
	}
}
