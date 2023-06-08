import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.*;
import java.io.*;
import java.util.*;

import javax.swing.*;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;

import org.jdatepicker.impl.JDatePanelImpl;
import org.jdatepicker.impl.JDatePickerImpl;
import org.jdatepicker.impl.UtilDateModel;

import org.jdatepicker.impl.*;
import org.jdatepicker.util.*;
import org.jdatepicker.*;

import java.text.SimpleDateFormat;
import java.text.DateFormat;
import java.text.ParseException;
import javax.swing.JFormattedTextField.AbstractFormatter;





public class DatePicker extends JDialog implements ActionListener
{
JLabel CheckDate; JButton check;
public UtilDateModel model;
public JDatePanelImpl datePanel;
public JDatePickerImpl datePicker;
int month; 
int day = -1;
public DatePicker()
    {
	model = new UtilDateModel();
	Properties p = new Properties();
	p.put("text.today", "Today");
	p.put("text.month", "Month");
	p.put("text.year", "Year");
	datePanel = new JDatePanelImpl(model, p);
	datePicker = new JDatePickerImpl(datePanel,new DateLabelFormatter());
    JPanel panel=new JPanel();
    CheckDate=new JLabel("Pick a date:");
    check=new JButton("OK"); 
    check.addActionListener(this);
    panel.add(CheckDate);
    panel.add(datePicker);
    panel.add(check);
    add(panel);
    setBounds(200,150,400,300);
    //setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    //setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    setResizable(false);
    setModal(true);
    setVisible(true); 
    
    
    }
public void actionPerformed(ActionEvent e) 
    {
	if(check==e.getSource()&& !datePicker.getModel().isSelected())
	{
		JFrame sss = new JFrame();
		JOptionPane.showMessageDialog(sss,"Please pick a date by clicking the ... buttom");
	}else if(check==e.getSource())
    {
    day = datePicker.getModel().getDay();
    month = datePicker.getModel().getMonth();
    dispose();
    }
    }

public int getDayJD()
{
	return day;
}
public int getMonthJD()
{
	return month+1;// return actually month value according to real world
}
public String dateToString()
{
switch (month+1)
{
case 1:
    return ("Jan "+day);
case 2:
    return ("Feb "+day);
case 3:
   return ("Mar "+day);
    
  case 4:
	  return ("Apr "+day);
  
  case 5:
	  return ("May "+day);
   
  case 6:
	  return ("Jun "+day);
  
  case 7:
	  return ("Jul "+day);
   
  case 8:
	  return ("Aug "+day);
	 
  case 9:
	  return ("Sep "+day);
	    
  case 10:
	  return ("Oct "+day);
	
  case 11:
	  return ("Nov "+day);
	   
  case 12:
	  return ("Dec "+day);
	 
}
return "";
}
}