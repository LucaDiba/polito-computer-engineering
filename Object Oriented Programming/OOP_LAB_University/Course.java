package university;

public class Course {
	private static final int MAX_STUDENTS = 100;
	private String name;
	private String teacher;
	private int courseId;
	
	private Student[] attendees = new Student[MAX_STUDENTS];
	private int numberAttendees = 0;
	
	/**
	 * Constructor
	 * @param name name of the course
	 * @param teacher name of the teacher
	 * @param courseId ID of the course
	 */
	public Course(String name, String teacher, int courseId) {
		this.name = name;
		this.teacher = teacher;
		this.courseId = courseId;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getTeacher() {
		return teacher;
	}

	public void setTeacher(String teacher) {
		this.teacher = teacher;
	}
	
	public String getString() {
		return courseId + " " + name + " " + teacher;
	}
	
	public void register(Student student) {
		if(numberAttendees >= MAX_STUDENTS)
			return;
		attendees[numberAttendees++] = student;
	}
	
	public String listAttendees() {
		StringBuffer list = new StringBuffer("");
		for (Student student : attendees) {
			if(student == null)
				break;
			list.append(student.getString() + "\n");
		}
		return list.toString();
	}

}
