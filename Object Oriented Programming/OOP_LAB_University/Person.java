package university;

public class Person {
	private String firstname;
	private String lastname;
	
	/**
	 * Constructor
	 * @param lastname last name of the person
	 * @param firstname first name of the person
	 */
	public Person(String lastname, String firstname) {
		this.lastname  = lastname;
		this.firstname = firstname;
	}
	
	/**
	 * Retrives informations about the person
	 * @return the following string: "FIRSTNAME LASTNAME" 
	 */
	public String getString() {
		return firstname + ' ' + lastname;
	}
}