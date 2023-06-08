<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="Hw4.Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Label ID="Label1" runat="server" style="font-weight: 700" Text="XML Processor"></asp:Label>
        </div>
        <br />
        <asp:Label ID="Label2" runat="server" Text="XML URL input: "></asp:Label>
        <asp:TextBox ID="urlTextBox" runat="server"></asp:TextBox>
        <asp:Button ID="ProcessButton" runat="server" OnClick="ProcessButton_Click" Text="Process" />
        <br />
        <br />
        <asp:Label ID="Label3" runat="server" Text="Processed XML:"></asp:Label>
        <br />
        <br />
    </form>
    <div id="div1" runat="server">
    </div>
</body>
</html>
