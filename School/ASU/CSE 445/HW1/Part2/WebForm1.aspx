<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebForm1.aspx.cs" Inherits="HW1_Part2.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
        </div>
        <p>
            <asp:Label ID="Label1" runat="server" Text="Please type your message in the text box"></asp:Label>
        </p>
        <p>
            <asp:TextBox ID="TextBox1" runat="server" Width="1158px"></asp:TextBox>
        </p>
        <p>
            <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="Encrypt" />
        </p>
        <p>
            &nbsp;</p>
        <p>
            <asp:Label ID="Label5" runat="server" Text="Encrypted Message"></asp:Label>
        </p>
        <p>
            <asp:TextBox ID="TextBox3" runat="server" Width="1154px"></asp:TextBox>
        </p>
        <p>
            &nbsp;</p>
        <p>
            <asp:Label ID="Label2" runat="server" Text="Message to decrypt"></asp:Label>
        </p>
        <p>
            <asp:TextBox ID="TextBox2" runat="server" Width="1150px"></asp:TextBox>
        </p>
        <p>
            <asp:Button ID="Button2" runat="server" OnClick="Button2_Click" Text="Decrypt" />
        </p>
        <p>
            <asp:Label ID="Label7" runat="server"></asp:Label>
        </p>
        <p>
            &nbsp;</p>
        <p>
            <asp:Label ID="Label6" runat="server" Text="Decrypted Message"></asp:Label>
        </p>
        <p>
            <asp:TextBox ID="TextBox4" runat="server" Width="1141px"></asp:TextBox>
        </p>
        <p>
            &nbsp;</p>
        <p>
            <asp:Label ID="Label8" runat="server" Text="------------------------------------------------------------------------------------------------------------------------------------------------------------------"></asp:Label>
        </p>
        <p>
            <asp:Label ID="Label9" runat="server"></asp:Label>
        </p>
        <p>
            <asp:Label ID="Label3" runat="server" Text=" Image String Length: "></asp:Label>
            <asp:TextBox ID="TextBox5" runat="server"></asp:TextBox>
        </p>
        <p>
            <asp:Image ID="Image1" runat="server" Height="133px" Width="326px" />
        </p>
        <p>
            <asp:Button ID="Button3" runat="server" OnClick="Button3_Click" Text="New Image String" />
        </p>
        <p>
            &nbsp;</p>
        <p>
            <asp:Label ID="Label4" runat="server" Text="Please enter the string here: "></asp:Label>
            <asp:TextBox ID="TextBox6" runat="server"></asp:TextBox>
        </p>
        <p>
            <asp:Button ID="Button4" runat="server" OnClick="Button4_Click" Text="Submit" />
        </p>
        <p>
            <asp:Label ID="Label10" runat="server"></asp:Label>
        </p>
        <p>
            &nbsp;</p>
        <p>
            &nbsp;</p>
    </form>
</body>
</html>
