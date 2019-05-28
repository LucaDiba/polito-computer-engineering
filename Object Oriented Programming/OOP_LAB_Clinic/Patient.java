package clinic;

public class Patient {
	private String firstName;
	private String lastName;
	private String ssn;
	private Doctor assignedDoctor;
	
	public Patient(String firstName, String lastName, String ssn) {
		this.firstName = firstName;
		this.lastName = lastName;
		this.ssn = ssn;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getSsn() {
		return ssn;
	}

	public void setSsn(String ssn) {
		this.ssn = ssn;
	}
	
	public Doctor getAssignedDoctor() {
		return assignedDoctor;
	}
	
	public void assignDoctor(Doctor d) {
		assignedDoctor = d;
	}
	
	@Override
	public String toString() {
		return this.lastName + " " + this.firstName + " (" + this.ssn + ")";
	}
}
