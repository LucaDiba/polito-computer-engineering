package university;

public class Courses {
	private static final int MAX_COURSES = 50;
	private static final int COURSE_ID_START = 10;
	private int coursesNumber = 0;
	private int lastcourseID = coursesNumber - 1;
	
	Course[] courses;
	
	/**
	 * Constructor
	 */
	public Courses() {
		courses = new Course[MAX_COURSES];
	}
	
	
	private int courseIDToVectorID(int courseID) {
		return courseID - COURSE_ID_START;
	}
	private boolean isSpaceAvaiable() {
		if(coursesNumber < MAX_COURSES) {
			return true;
		} else {
			return false;
		}
	}
	
	
	public int newCourse(String name, String teacher) {
		if(this.isSpaceAvaiable()) {
			lastcourseID++;
			courses[lastcourseID] = new Course(name, teacher, COURSE_ID_START + lastcourseID);
			
			coursesNumber++;
			
			return COURSE_ID_START + lastcourseID;
		}else {
			return -1;
		}
	}
	
	public Course getCourse(int courseID) {
		return courses[courseIDToVectorID(courseID)];
	}
	
	public String getString(int courseID) {
		return courses[courseIDToVectorID(courseID)].getString();
	}
	
	public void register(int courseCode, Student student) {
		courses[courseIDToVectorID(courseCode)].register(student);
	}
	
	public String listAttendees(int courseCode) {
		return courses[courseIDToVectorID(courseCode)].listAttendees();
	}
}
