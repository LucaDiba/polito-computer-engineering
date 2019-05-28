package university;

import java.util.ArrayList;
import java.util.Collections;
import static java.util.Comparator.*;
import java.util.Map;
import java.util.TreeMap;

public class University {
	
	private String name;
	private Person rector;
	private int nextId;

	//private Students students = new Students();
	//private List<Student> students;
	private Map<Integer, Student> students;
	
	private Courses  courses  = new Courses();

	/**
	 * Constructor
	 * @param name name of the university
	 */
	public University(String name){
		this.name = name;
		//students = new ArrayList<>();
		students = new TreeMap<>();
	}
	
	/**
	 * Getter for the name of the university
	 * @return name of university
	 */
	public String getName(){
		return this.name;
	}
	
	/**
	 * Defines the rector for the university
	 * @param first
	 * @param last
	 */
	public void setRector(String first, String last){
		this.rector = new Person(last, first);
	}
	
	/**
	 * Retrieves the rector of the university
	 * @return
	 */
	public String getRector(){
		return rector.getString();
	}
	
	/**
	 * Enroll a student in the university
	 * @param first first name of the student
	 * @param last last name of the student
	 * @return
	 */
	public int enroll(String first, String last){
		Student s = new Student(first, last, nextId);
		students.put(nextId, s);
		return nextId++;
	}
	
	/**
	 * Retrieves the information for a given student
	 * @param id the id of the student
	 * @return information about the student
	 */
	public String student(int id){
		return students.get(id).getString();
	}
	
	/**
	 * Activates a new course with the given teacher
	 * @param title title of the course
	 * @param teacher name of the teacher
	 * @return the unique code assigned to the course
	 */
	public int activate(String title, String teacher){
		//TODO: to be implemented
		return courses.newCourse(title, teacher);
	}
	
	/**
	 * Retrieve the information for a given course
	 * @param code unique code of the course
	 * @return information about the course
	 */
	public String course(int code){
		return courses.getString(code);
	}
	
	/**
	 * Register a student to attend a course
	 * @param studentID id of the student
	 * @param courseCode id of the course
	 */
	public void register(int studentID, int courseCode){
		students.get(studentID).register(courses.getCourse(courseCode));
		courses.register(courseCode, students.get(studentID));
	}
	
	/**
	 * 
	 * @param studentID
	 * @return
	 */
	public Student getStudent(int studentID) {
		return students.get(studentID);
	}
	
	public String listAllStudents() {
		StringBuffer result = new StringBuffer();
		ArrayList<Student> studenti = new ArrayList<>(students.values());
		Collections.sort(studenti, (s1, s2)-> s1.getString().compareTo(s1.getString()));
		Collections.sort(studenti, comparing(Student::getString));
		
		for(Student s : studenti) {
			result.append(s).append("\n");
		}
		
//		for(Student s: students.values()) {
//			result.append(s).append("\n");
//		}
		return result.toString();
	}
	
	/**
	 * Retrieve a list of attendees
	 * @param courseCode unique id of the course
	 * @return list of attendees separated by "\n"
	 */
	public String listAttendees(int courseCode){
		return courses.listAttendees(courseCode);
	}

	/**
	 * Retrieves the study plan for a student
	 * @param studentID id of the student
	 * @return list of courses the student is registered for
	 */
	public String studyPlan(int studentID){
		return students.get(studentID).studyPlan();
	}
}
