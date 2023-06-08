import java.util.ArrayList;
import java.util.HashMap;
import java.io.*; //File,FileReader,FileNotFoundException,BufferedReader,IOException
/**
 * Project:		CSE360 Final Project
 * Course ID:	70605
 * Instructor:	Gonzalez Sanchez
 * Team Member:	Wei Chieh Huang
 * 				Yinghua Li
 * 				Chenghao Xie
 *				Ziqi Gong
 */

public class StudentInfoList {
   private ArrayList<StudentInfo> infoList;
   public StudentInfoList() {
	   infoList = new ArrayList<StudentInfo>();
   }
   public void add(StudentInfo si) {
	   infoList.add(si);
   }
   public void readFromCSV(String filename) {
      File file = new File(filename);
      FileReader reader = null;
      try {
         reader = new FileReader(file);
      }
      catch (FileNotFoundException e) {
         e.printStackTrace();
         System.exit(1);
      }
      BufferedReader infile = new BufferedReader(reader);
      String line = "";
      try {
         boolean done = false;
         while (!done) {
            line = infile.readLine();
            if (line == null) {
               done = true;
            }
            else {
               String[] tokens = line.trim().split(",");
               String ID = tokens[0].trim();
               String FirstName = tokens[1].trim();
               String LastName = tokens[2].trim();
               String Program = tokens[3].trim();
               String Level = tokens[4].trim();
               String ASURITE = tokens[5].trim();
               
               StudentInfo si = new StudentInfo(ID,FirstName,LastName,Program,Level,ASURITE);
               infoList.add(si);
            }
         }
      }
      catch (IOException e) {
         e.printStackTrace();
         System.exit(1);
      }
   }
   public Object[][] convert2Data() {
       Object[][] data = new Object[infoList.size()][7];
       for (int i = 0; i < infoList.size(); i++) {
    	  data[i][0] = infoList.get(i).getID();
          data[i][1] = infoList.get(i).getFirstName();
          data[i][2] = infoList.get(i).getLastName();
          data[i][3] = infoList.get(i).getProgram();
          data[i][4] = infoList.get(i).getLevel();
          data[i][5] = infoList.get(i).getASURITE();
          data[i][6]=0;
          
       }
       return data;
   }


public void add_readFromCSV(String filename) {
    File file = new File(filename);
    FileReader reader = null;
    try {
       reader = new FileReader(file);
    }
    catch (FileNotFoundException e) {
       e.printStackTrace();
       System.exit(1);
    }
    BufferedReader infile = new BufferedReader(reader);
    String line = "";
    try {
       boolean done = false;
       while (!done) {
          line = infile.readLine();
          if (line == null) {
             done = true;
          }
          else {
             String[] tokens = line.trim().split(",");
             String ASURITE = tokens[0].trim();
             String time = tokens[1].trim();
             
             StudentInfo si = new StudentInfo(ASURITE,time);
             infoList.add(si);
          }
       }
       
    }
    catch (IOException e) {
       e.printStackTrace();
       System.exit(1);
    }
}
public HashMap<String, String> add_convert2Data() {
	HashMap<String, String> add_data = new HashMap<String, String>();
	add_data.put(infoList.get(0).getASURITE(),infoList.get(0).gettime());
    for (int i = 1; i < infoList.size(); i++) {
    	boolean flag = false;
    	for (String ASUID:add_data.keySet()) 
	      {	
	    	  String asurite = ASUID;
	    	  int value_time=Integer.parseInt(add_data.get(ASUID));	
	    	  if(asurite.equals(infoList.get(i).getASURITE()))
	    	  {
	    		  value_time+=Integer.parseInt(infoList.get(i).gettime());
	    		  add_data.put(infoList.get(i).getASURITE(),Integer.toString(value_time));
	    		  flag=true;
	    	  }	  
	      }
    	if(flag==false)
    	{
    		add_data.put(infoList.get(i).getASURITE(),infoList.get(i).gettime());
    	}
            
    }
    return add_data;
}
}