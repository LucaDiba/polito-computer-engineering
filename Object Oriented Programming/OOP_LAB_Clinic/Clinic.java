package clinic;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

/**
 * Represents a clinic with patients and doctors.
 * 
 */
public class Clinic {
	private Map<String, Patient> patients;
	private Map<Integer, Doctor> doctors;
	
	public Clinic() {
		patients = new HashMap<>();
		doctors  = new HashMap<>();
	}

	/**
	 * Add a new clinic patient.
	 * 
	 * @param first first name of the patient
	 * @param last last name of the patient
	 * @param ssn SSN number of the patient
	 */
	public void addPatient(String first, String last, String ssn) {
		Patient p = new Patient(first, last, ssn);
		patients.put(ssn, p);
	}


	/**
	 * Retrieves a patient information
	 * 
	 * @param ssn SSN of the patient
	 * @return the object representing the patient
	 * @throws NoSuchPatient in case of no patient with matching SSN
	 */
	public String getPatient(String ssn) throws NoSuchPatient {
		Patient p = patients.get(ssn);
		if(p != null) {
			return p.toString();
		}else {
			throw new NoSuchPatient();
		}
	}

	/**
	 * Add a new doctor working at the clinic
	 * 
	 * @param first first name of the doctor
	 * @param last last name of the doctor
	 * @param ssn SSN number of the doctor
	 * @param docID unique ID of the doctor
	 * @param specialization doctor's specialization
	 */
	public void addDoctor(String first, String last, String ssn, int docID, String specialization) {
		Doctor d = new Doctor(first, last, ssn, docID, specialization);
		Patient p = new Patient(first, last, ssn);
		doctors.put(docID, d);
		patients.put(ssn, p);
	}

	/**
	 * Retrieves information about a doctor
	 * 
	 * @param docID ID of the doctor
	 * @return object with information about the doctor
	 * @throws NoSuchDoctor in case no doctor exists with a matching ID
	 */
	public String getDoctor(int docID) throws NoSuchDoctor {
		Doctor d = doctors.get(docID);
		if(d == null) {
			throw new NoSuchDoctor();
		}else {
			return d.toString();
		}
	}
	
	/**
	 * Assign a given doctor to a patient
	 * 
	 * @param ssn SSN of the patient
	 * @param docID ID of the doctor
	 * @throws NoSuchPatient in case of not patient with matching SSN
	 * @throws NoSuchDoctor in case no doctor exists with a matching ID
	 */
	public void assignPatientToDoctor(String ssn, int docID) throws NoSuchPatient, NoSuchDoctor {
		Patient p = patients.get(ssn);
		Doctor d = doctors.get(docID);
		if(p == null) {
			throw new NoSuchPatient();
		}
		if(d == null) {
			throw new NoSuchDoctor();
		}
		if(p.getAssignedDoctor() != null) {
			System.out.println("Doctor alrealy assigned to patient " + p.toString());
			return;
		}
		p.assignDoctor(d);
		d.assignPatient(p);
	}
	
	/**
	 * Retrieves the id of the doctor assigned to a given patient.
	 * 
	 * @param ssn SSN of the patient
	 * @return id of the doctor
	 * @throws NoSuchPatient in case of not patient with matching SSN
	 * @throws NoSuchDoctor in case no doctor has been assigned to the patient
	 */
	public int getAssignedDoctor(String ssn) throws NoSuchPatient, NoSuchDoctor {
		Patient p = patients.get(ssn);
		if(p == null) {
			throw new NoSuchPatient();
		}
		Doctor d = p.getAssignedDoctor();
		if(d == null) {
			throw new NoSuchDoctor();
		}
		return d.getDocId();
	}
	
	/**
	 * Retrieves the patients assigned to a doctor
	 * 
	 * @param id ID of the doctor
	 * @return collection of patient SSN
	 * @throws NoSuchDoctor in case the {@code id} does not match any doctor 
	 */
	public Collection<String> getAssignedPatients(int id) throws NoSuchDoctor {
		Doctor d = doctors.get(id);
		if(d == null) {
			throw new NoSuchDoctor();
		}

		return d.getAssignedPatients().stream().map(Patient::getSsn).collect(Collectors.toList());
	}


	/**
	 * Loads data about doctors and patients from the given stream.
	 * <p>
	 * The text file is organized by rows, each row contains info about
	 * either a patient or a doctor.</p>
	 * <p>
	 * Rows containing a patient's info begin with letter {@code "P"} followed by first name,
	 * last name, and SSN. Rows containing doctor's info start with letter {@code "M"},
	 * followed by badge ID, first name, last name, SSN, and specialization.<br>
	 * The elements on a line are separated by the {@code ';'} character possibly
	 * surrounded by spaces that should be ignored.</p>
	 * <p>
	 * In case of error in the data present on a given row, the method should be able
	 * to ignore the row and skip to the next one.<br>

	 * 
	 * @param path the path of the required file
	 * @throws IOException in case of IO error
	 */
	public void loadData(Reader reader) throws IOException {
		BufferedReader bf = new BufferedReader(reader);
		String line = null;
		while((line = bf.readLine()) != null) {
			ArrayList<String> elements = new ArrayList<>(Arrays.asList(line.split("; *")));
			
			if(elements.get(0).equals("P")) { // if is patient
				if(elements.size() == 4) {
					String firstName = elements.get(1).trim();
					String lastName  = elements.get(2).trim();
					String ssn		 = elements.get(3).trim();
					this.addPatient(firstName, lastName, ssn);
				}else {
					System.out.println("Format error. Ignoring line");
				}
			}else if(elements.get(0).equals("M")) { // if is doctor
				if(elements.size() == 6) {
					Pattern p = Pattern.compile("[0-9]+");
					if(p.matcher(elements.get(1)).matches()) {
						int docId = Integer.parseInt(elements.get(1).trim());
						String firstName = elements.get(2).trim();
						String lastName  = elements.get(3).trim();
						String ssn		 = elements.get(4).trim();
						String specialization = elements.get(5).trim();
						this.addDoctor(firstName, lastName, ssn, docId, specialization);
					}else {
						System.out.println("Doctor id must be an integer. Ignoring line");
					}
				}else {
					System.out.println("Format error. Ignoring line");
				}
			}else {
				System.out.println("Type not valid. Ignoring line");
			}
		}
	}




	/**
	 * Retrieves the collection of doctors that have no patient at all, sorted in alphabetic order.
	 * 
	 * @return the collection of doctors with no patient sorted in alphabetic order (last name and then first name)
	 */
	public Collection<Integer> idleDoctors(){
		return doctors.values().stream()
				.filter(d -> d.getAssignedPatients().size() == 0)
				.sorted(
						Comparator
							.comparing(Doctor::getLastName)
							.thenComparing(Doctor::getFirstName)
						)
				.map(d->d.getDocId())
				.collect(Collectors.toList());
	}

	/**
	 * Retrieves the collection of doctors having a number of patients larger than the average.
	 * 
	 * @return  the collection of doctors
	 */
	public Collection<Integer> busyDoctors(){
		float media = doctors.values().stream()
				.map(d -> d.getAssignedPatients().size())
				.reduce(0, (a, b) -> a + b) / doctors.size();
		return doctors.values().stream()
				.filter(d -> d.getAssignedPatients().size() > media)
				.map(d -> d.getDocId())
				.collect(Collectors.toList());
	}

	/**
	 * Retrieves the information about doctors and relative number of assigned patients.
	 * <p>
	 * The method returns list of strings formatted as "{@code ### : ID SURNAME NAME}" where {@code ###}
	 * represent the number of patients (printed on three characters).
	 * <p>
	 * The list is sorted by decreasing number of patients.
	 * 
	 * @return the collection of strings with information about doctors and patients count
	 */
	public Collection<String> doctorsByNumPatients(){
		return doctors.values().stream()
				.filter(d->d.getAssignedPatients().size()>0)
				.sorted(Comparator.comparing(d->((Doctor)d).getAssignedPatients().size()).reversed())
				.map(d-> String.format("%3d", d.getAssignedPatients().size()) + " : "+d.getDocId()+" "+d.getLastName()+" "+d.getFirstName())
				.collect(Collectors.toList());
	}
	
	/**
	 * Retrieves the number of patients per (their doctor's)  specialization 
	 * <p>
	 * The information is a collections of strings structured as {@code ### - SPECIALITY}
	 * where {@code SPECIALITY} is the name of the speciality and 
	 * {@code ###} is the number of patients cured by doctors with such speciality (printed on three characters).
	 * <p>
	 * The elements are sorted first by decreasing count and then by alphabetic specialization.
	 * 
	 * @return the collection of strings with specialization and patient count information.
	 */
	public Collection<String> countPatientsPerSpecialization(){
		return patients.values().stream()
				.filter(p->p.getAssignedDoctor()!=null)
				.collect(
						Collectors.groupingBy(
									p -> ((Patient)p).getAssignedDoctor().getSpecialization(),
									Collectors.counting()
								)
						)
				.entrySet().stream()
				.map(item -> String.format("%3d", item.getValue()) + " - " + item.getKey())
				.collect(Collectors.toList());
	}
	
}
