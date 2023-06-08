<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Label ID="Label1" runat="server" Text="XML Verification" style="font-weight: 700"></asp:Label>
            <br />
            <br />
            <asp:Label ID="Label2" runat="server" Text="XML URL: "></asp:Label>
            <asp:TextBox ID="verifyXmlBox" runat="server" Width="420px"></asp:TextBox>
            <br />
            <br />
            <asp:Label ID="Label3" runat="server" Text="XSD URL: "></asp:Label>
            <asp:TextBox ID="verifyXsdBox" runat="server" Width="419px"></asp:TextBox>
            <br />
            <br />
            <asp:Button ID="verifyButton" runat="server" Text="Validate" OnClick="verifyButton_Click" />
            <br />
            <br />
            <asp:Label ID="verifyResult" runat="server"></asp:Label>
            <br />
            <br />
            <asp:Label ID="Label4" runat="server" Text="XPath Search" style="font-weight: 700"></asp:Label>
            <br />
            <br />
            <asp:Label ID="Label5" runat="server" Text="XML URL: "></asp:Label>
            <asp:TextBox ID="searchXmlBox" runat="server" Width="409px"></asp:TextBox>
            <br />
            <br />
            <asp:Label ID="Label6" runat="server" Text="XPath query/expression: "></asp:Label>
            <asp:TextBox ID="searchExpBox" runat="server" Width="394px"></asp:TextBox>
            <br />
            <br />
            <asp:Button ID="searchButton" runat="server" Text="Search" OnClick="searchButton_Click" />
            <br />
            <br />
            <asp:Label ID="searchResult" runat="server"></asp:Label>
        </div>
    </form>
</body>
</html>
