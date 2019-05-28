package university;

public class Student {
	private static final int MAX_COURSES_ATTEND = 25;
	
	private String lastname;
	private String firstname;
	private int studentId;
	
	private Course[] attendingCourses = new Course[MAX_COURSES_ATTEND];
	private int numberAttendingCourses = 0;
	
	public Student(String lastname, String firstname, int studentId) {
		this.lastname = lastname;
		this.firstname = firstname;
		this.studentId = studentId;
	}

	public String getString() {
		return studentId + " " + firstname + " " + lastname;
	}
	
	public void register(Course course) {
		if(numberAttendingCourses >= MAX_COURSES_ATTEND)
			return;
		attendingCourses[numberAttendingCourses++] = course;
	}
	
	public String studyPlan() {
		StringBuffer list = new StringBuffer();
		for (Course course : attendingCourses) {
			if(course == null)
				break;
			list.append(course.getString() + "\n");
		}
		return list.toString();
	}
}
