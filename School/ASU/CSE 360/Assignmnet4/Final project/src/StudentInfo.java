/**
 * Project:		CSE360 Final Project
 * Course ID:	70605
 * Instructor:	Gonzalez Sanchez
 * Team Member:	Wei Chieh Huang
 * 				Yinghua Li
 * 				Chenghao Xie
 *				Ziqi Gong
 */

public class StudentInfo 
{
   private String ID; 
   private String FirstName;
   private String LastName;
   private String Program;
   private String Level;
   private String ASURITE;
   private String time;
   public StudentInfo(String a, String b, String c, String d, String e, String f) 
   {
      ID = a.trim();
      FirstName = b.trim();
      LastName = c.trim();
      Program = d.trim();
      Level = e.trim();
      ASURITE = f.trim();
      
   }
   public StudentInfo(String a, String b)
   {
	   ASURITE=a.trim();
	   time=b.trim();
   }
   
   public String getID() {
	      return ID;
	   }
   public String getFirstName() {
	      return FirstName;
	   }
   public String getLastName() {
	      return LastName;
	   }
   public String getProgram() {
      return Program;
   }
   public String getLevel() {
      return Level;
   }
   public String getASURITE() {
	      return ASURITE;
	   }
   public String gettime() {
	      return time;
	   }
}