using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

// NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService" in both code and config file together.
[ServiceContract]
public interface IService
{

	[OperationContract]
	[WebGet(UriTemplate = "verify?xml={xml}&xmls={xmls}", ResponseFormat = WebMessageFormat.Json)]
	string verify(string xml, string xmls);

	[OperationContract]
	[WebGet(UriTemplate = "xpath?xml={xml}&exp={pathExp}", ResponseFormat = WebMessageFormat.Json)]
	string pathSearch(string xml, string pathExp);
	// TODO: Add your service operations here
}

