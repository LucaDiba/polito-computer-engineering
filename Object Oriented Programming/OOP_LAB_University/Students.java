package university;

public class Students {
	private static final int MAX_STUDENTS = 1000;
	private static final int STUDENT_ID_START = 10000;
	
	private int studentsNumber = 0;
	private int laststudentID = studentsNumber - 1;
	
	private Student[] students;
	
	
	public Students() {
		students = new Student[MAX_STUDENTS];
	}	
	
	private int studentIDToVectorID(int studentID) {
		return studentID - STUDENT_ID_START;
	}
	private boolean isSpaceAvaiable() {
		if(studentsNumber < MAX_STUDENTS) {
			return true;
		} else {
			return false;
		}
	}
	
	
	public int newStudent(String lastname, String firstname) {
		if(this.isSpaceAvaiable()) {
			laststudentID++;
			students[laststudentID] = new Student(lastname, firstname, STUDENT_ID_START + laststudentID);
			
			studentsNumber++;
			
			return laststudentID + STUDENT_ID_START;
		}else {
			return -1;
		}
	}
	
	public String getString(int studentID) {
		return students[studentIDToVectorID(studentID)].getString();
	}
	
	public void register(int studentID, Course course) {
		students[studentIDToVectorID(studentID)].register(course);
	}
	
	public String studyPlan(int studentID) {
		return students[studentIDToVectorID(studentID)].studyPlan();
	}
}
