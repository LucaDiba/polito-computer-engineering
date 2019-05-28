package clinic;

import java.util.Collection;
import java.util.LinkedList;

public class Doctor extends Patient {
	private int docId;
	private String specialization;
	private Collection<Patient> assignedPatients;
	
	public Doctor(String first, String last, String ssn, int docID, String specialization) {
		super(first, last, ssn);
		this.docId = docID;
		this.specialization = specialization;
		assignedPatients = new LinkedList<>();
	}
	
	public int getDocId() {
		return docId;
	}
	
	public String getSpecialization() {
		return specialization;
	}
	
	public Collection<Patient> getAssignedPatients(){
		return assignedPatients;
	}
	
	public void assignPatient(Patient p) {
		assignedPatients.add(p);
	}
	
	@Override
	public String toString() {
		return super.getLastName()+" "+super.getFirstName()+" ("+super.getSsn()+") ["+docId+"]: "+specialization;
	}
}
