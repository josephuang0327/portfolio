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

/**
 * Project:		CSE360 Final Project
 * Course ID:	70605
 * Instructor:	Gonzalez Sanchez
 * Team Member:	Wei Chieh Huang
 * 				Yinghua Li
 * 				Chenghao Xie
 *				Ziqi Gong
 */

/**
 * Create the windows that would load, add, save, and plot tables from the cvs
 * file. 
 */
public class gui extends JFrame implements ActionListener, MenuListener
{
	
	File file;
	Scanner fileIn;
	JFileChooser chooser = new JFileChooser(".");
	//Only shows .CSV file in file chooser
	FileNameExtensionFilter filter = new FileNameExtensionFilter("*.csv", "csv");
	
	
	int response;
	
	//Items as global variable in order to add Actionlistener on each of them
	JMenuItem LoadRoaster;
	JMenuItem AddAtttendance;
	JMenuItem Save;
	JMenuItem PlotData;
	JFrame jf;
	
	//data structure to store info in .csv file
	private Object[][] data;
	private HashMap<String, String> add_data;
	   private String[] columnNames = {"ID","First Name","Last Name", "Program", "Level", "ASURITE"};
	   private String[] add_columnNames = {"ID","First Name","Last Name", "Program", "Level", "ASURITE","time"};
	   private DefaultTableModel tableModel;
	   private JTable table;
	   private StudentInfoList myList;

	  
	/**
	 * Adding all the menu item to the frame.
	 * Call the action listener and menu listener
	 */
	public gui()
	{
		//The overall Jframe
		jf = new JFrame();
		jf.setSize(800, 800);
		jf.setTitle("CSE360 Final Project");
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jf.setVisible(true);
		
		//Menu Bar
		JMenuBar jmb = new JMenuBar();
		jf.setJMenuBar(jmb);
		
		//File choice
		JMenu file = new JMenu("File");
		file.setMnemonic(KeyEvent.VK_F);
		jmb.add(file);
		
		//About choice
		JMenu about = new JMenu("About");
		about.setMnemonic(KeyEvent.VK_E);
		about.addMenuListener(this);
		jmb.add(about);
		
		//Options
		LoadRoaster = new JMenuItem("Load a Roaster");
		LoadRoaster.setMnemonic(KeyEvent.VK_L);
		LoadRoaster.addActionListener(this);
		file.add(LoadRoaster);
		
		file.addSeparator();
		
		AddAtttendance = new JMenuItem("Add Attendance");
		AddAtttendance.setMnemonic(KeyEvent.VK_S);
		AddAtttendance.addActionListener(this);
		file.add(AddAtttendance);
		
		file.addSeparator();
		
		Save = new JMenuItem("Save");
		Save.setMnemonic(KeyEvent.VK_A);
		Save.addActionListener(this);
		file.add(Save);
		
		file.addSeparator();
		
		PlotData = new JMenuItem("Plot Data");
		PlotData.setMnemonic(KeyEvent.VK_Q);
		PlotData.addActionListener(this);
		file.add(PlotData);
		
		
		file.addSeparator();
		
		
		jf.setVisible(true);
		
	}

	
	// Here is the Actionlistener that will do the job when mouse clicks on it
	@Override
	public void actionPerformed(ActionEvent arg0) 
	{
		
		//Action listener for LoadRoaster
		if(arg0.getSource() == LoadRoaster)
		{  
            chooser.setFileFilter(filter);
			chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
			response = chooser.showOpenDialog(null);
			
			if(response == JFileChooser.APPROVE_OPTION)
			{
				file = chooser.getSelectedFile();	
				
				//Display the Load Roaster diagram
				  setBounds(0,0,800,800);
			      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			      myList = new StudentInfoList();
			      myList.readFromCSV(file.getAbsolutePath());
			      data = myList.convert2Data();
			      tableModel = new DefaultTableModel(data, columnNames);
			      table = new JTable(tableModel);
			      table.setAutoCreateRowSorter(true);
			      
			      JPanel panel = new JPanel();
			      JScrollPane scrollPane = new JScrollPane(table, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);	      
			      scrollPane.setPreferredSize(new Dimension(700,700));

			      panel.add(scrollPane);
			      jf.add(panel,BorderLayout.CENTER);	
			      jf.setVisible(true);											
			}
			

			
		}
		//Action listener for AddAtttendance
		else if(arg0.getSource() == AddAtttendance)
		{
			chooser.setFileFilter(filter);
			chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
			response = chooser.showOpenDialog(null);
			if(response == JFileChooser.APPROVE_OPTION)
			{
				file = chooser.getSelectedFile();	
				//Display the Load Roaster diagram
				  setBounds(0,0,800,800);
			      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			      myList = new StudentInfoList();
			      myList.add_readFromCSV(file.getAbsolutePath());			      
			      add_data = myList.add_convert2Data();
			      
			      //create copy all data to temp for Jdialog
			      HashMap<String, String> temp = new HashMap<String, String>();
			      temp.putAll(add_data);
			      int extra=0;
			      //for new column
			      Vector<Integer> columnData = new Vector<>();
			     
			    	  for(int j=0;j<data.length;j++)
			    	  {		    		  
			    		  if(add_data.containsKey(data[j][5]))
			    		  {
			    			  columnData.add(Integer.parseInt(add_data.get(data[j][5]))); //if find the student, append the time
			    			  temp.remove(data[j][5]); //remove that student from temp. this will end up have all additional students
			    		  }
			    		  else
				    	  {
			    			  columnData.add(0);
			    			  extra++;  
				    	  }
			    	  }
			    	StringBuffer sb=new StringBuffer();
	    			String line1 = "Data loaded for "+ add_data.size()+" users in the roster.\n";
	    			String line2 = extra + " aditional attendee was found: \n";
	    			String full = line1+line2;
			      	for(String key:temp.keySet())
			      	{
			      		String lineadd = key + ", connected for "+ temp.get(key) + " minute\n";
			      		full+=lineadd;
			      	}
			      
			      	JOptionPane.showMessageDialog(null, full," ", JOptionPane.INFORMATION_MESSAGE);
					DatePicker adp = new DatePicker();
					tableModel.addColumn(adp.dateToString(), columnData);      
					System.out.println(table.getRowCount()-1);
											
		}
		}
		//when the user click on save menu item
		else if(arg0.getSource() == Save)
		{
				//Display the save Roaster diagram
				try 
				{
					//chooser for saving file
					JFileChooser saveChooser = new JFileChooser();
					saveChooser.setDialogTitle("Select a file to save");
					int saveSelection = saveChooser.showSaveDialog(jf);
					
					//if the option is valid
					if (saveSelection == JFileChooser.APPROVE_OPTION) 
					{
					    File fileToSave = saveChooser.getSelectedFile();
					    System.out.println("Save as file: " + fileToSave.getAbsolutePath());

					    TableModel exportModel = table.getModel();				    
				        FileWriter exportCsv = new FileWriter(fileToSave + ".csv");
	
				        //write every column name to file
				        for (int i = 0; i < exportModel.getColumnCount(); i++) 
				        {
				        	exportCsv.write(exportModel.getColumnName(i) + ",");
				        }
	
				        exportCsv.write("\n");
	
				        //export every column and rows.
				        for (int i = 0; i < exportModel.getRowCount(); i++) 
				        {
				            for (int j = 0; j < exportModel.getColumnCount(); j++) 
				            {
				            	exportCsv.write(exportModel.getValueAt(i, j).toString() + ",");
				            }
				            exportCsv.write("\n");
				        }
	
				        exportCsv.close();
					}
			    } 
			    catch (IOException e) 
			    {
			        e.printStackTrace();
			    }
		}
		else if(arg0.getSource()==PlotData)
		{		     
			     ScatterPlot dataChart = new ScatterPlot();
			     dataChart.setSize(800, 400);
			     dataChart.setVisible(true);
		}
			
	}
	/**
	 * default menuListener method
	 * When the about menu is selected then open the dialog
	 */
	@Override
	public void menuSelected(MenuEvent e) 
	{
		JFrame About = new JFrame();
		JOptionPane.showMessageDialog(About,  "Team Name: Four Guys\n" 
											+ "Team Members:\n"
											+ " - Weichieh Huang\n"
											+ " - Chenghao Xie\n"
											+ " - Yinghua Li\n"
											+ " - Ziqi Gong");
	}
	/**
	 * default menuListener method
	 */
	@Override
	public void menuDeselected(MenuEvent e) 
	{
		// TODO Auto-generated method stub
		
	}

	/**
	 * default menuListener method
	 */
	@Override
	public void menuCanceled(MenuEvent e) 
	{
		// TODO Auto-generated method stub
		
	}
}
	
	
