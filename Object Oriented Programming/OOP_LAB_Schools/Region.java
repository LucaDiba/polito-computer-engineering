package schools;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.TreeMap;

// Hint: to write compact stream expressions
// you can include the following
import static java.util.stream.Collectors.*;

/**
 * Represents the region and serves as a facade class
 * for the package.
 * 
 * It provides factory methods for creating instances of
 * {@link Community}, {@link Municipality}, {@link School}, and {@link Branch}
 *
 */
public class Region {
	private String name;
	Collection<School> schools;
	Collection<Branch> branches;
	Collection<Community> communities;
	Collection<Municipality> municipalities;
	
	/**
	 * Creates a new region with the given name.
	 * @param name the name of the region
	 */
	public Region(String name){
		this.name = name;
		schools = new ArrayList<School>();
		branches = new ArrayList<Branch>();
		communities = new ArrayList<Community>();
		municipalities = new ArrayList<Municipality>();
	}
	
	/**
	 * Getter method
	 * @return the name of the region
	 */
	public String getName(){
		return name;
	}
	
	/**
	 * Retrieves all schools in the region
	 * @return collection of schools
	 */
	public Collection<School> getSchools() {
		return schools;
	}
	
	/**
	 * Retrieves all the communities
	 * @return the collection of all communities
	 */
	public Collection<Community> getCommunities() {
		return communities;
	}
	
	/**
	 * Retrieves all municipalities in the region
	 * @return the collection of municipalities
	 */
	public Collection<Municipality> getMunicipalies() {
		return municipalities;
	}
	
	
	// factory methods
	
	/**
	 * Factory method that build a new community of the given type.
	 * The type is {@link Community.Type}
	 * 
	 * @param name name of the community
	 * @param type type of the community
	 * @return the new created community
	 */
	public Community newCommunity(String name, Community.Type type){
		Community c = new Community(name, type);
		communities.add(c);
		return c;
	}

	/**
	 * Factory method that build a new municipality.
	 * 
	 * @param nome 		name of the municipality
	 * @param province 	province of the municipality
	 * @return the new created municipality
	 */
	public Municipality newMunicipality(String nome, String province){
		Optional<Municipality> municipality = municipalities.stream().filter(mu -> mu.getName().equals(nome)).findFirst();
		if(municipality.isPresent()) {
			return municipality.get();
		}else {
			Municipality m = new Municipality(nome, province, Optional.empty());
			municipalities.add(m);
			return m;
		}
	}
	
	/**
	 * Factory methods, that build a new municipality that
	 * is part of a community.
	 * 
	 * @param nome 		name of the municipality
	 * @param province 	province of the municipality
	 * @param comunita  community the municipality belongs to 
	 * @return the new created municipality
	 */
	public Municipality newMunicipality(String nome, String province, Community community){
		Optional<Municipality> municipality = municipalities.stream().filter(mu -> mu.getName().equals(nome)).findFirst();
		if(municipality.isPresent()) {
			return municipality.get();
		}else {
			Municipality m;
			Optional<Community> c = Optional.of(community);
			if(c.isPresent()) {
				m = new Municipality(nome, province, c);
				c.get().addMunicipalty(m);
				municipalities.add(m);
			}else {
				System.out.println("Community not found");
				m = null;
			}
			return m;
		}
	}
	
	/**
	 * Factory method that creates a new school
	 * 
	 * @param name    name of the school
	 * @param code    code of the school
	 * @param grade	  grade of the school (1 to 4)
	 * @param description  description of the school
	 * 
	 * @return a new school object
	 */
	public School newSchool(String name, String code, int grade, String description){
		Optional<School> school = schools.stream().filter(sc -> sc.getCode().equals(code)).findFirst();
		if(school.isPresent()) {
			return school.get();
		} else {
			School s = new School(name, code, grade, description);
			schools.add(s);
			return s;
		}
	}
	
	/**
	 * Factory method that creates a new school branch
	 * 
	 * @param regionalCode	regional code of the branch
	 * @param municipality	municipality where the branch is located
	 * @param address		address of the branch
	 * @param zipCode		zip code of the branch
	 * @param school		school the branch is part of
	 * @return	the new created branch
	 */
	public Branch newBranch(int regionalCode, Municipality municipality, String address, int zipCode, School school)	{
		Branch b = new Branch(regionalCode, municipality, address, zipCode, school);
		branches.add(b);
		school.addBranch(b);
		municipality.addBranch(b);
		return b;
	}
	
	/**
	 * Load data from a file.
	 * 
	 * The file must be a CSV file and it is supposed to contain the following fields:
	 * <ul>
	 *  <li>0  {@code "Provincia"},   (province)
	 *  <li>1  {@code "Comune"},		(municipality)
	 *  <li>2  {@code "Grado Scolastico"}, (school grade)
	 *  <li>3  {@code "Descrizione Scuola"}, (school description)
	 *  <li>4  {@code "Cod Sede"}, (branch code)
	 *  <li>5  {@code "Cod Scuola"}, (school code)
	 *  <li>6  {@code "Denominazione Scuola"}, (name of the school)
	 *  <li>7  {@code "Indirizzo e n. civico"}, (address of the branch)
	 *  <li>8  {@code "C.A.P."}, (zip code of the branch)
	 *  <li>9  {@code "Comunita Collinare"}, (Hill community)
	 *  <li>10 {@code "Comunita Montana"},  (Mountain community)
	 * </ul>
	 * 
	 * @param file the path of the file
	 */
	public void readData(String file) {
		List<String> lines = null;
		try(BufferedReader in = new BufferedReader(new FileReader(file))){
			lines = in.lines().collect(toList());
		}catch(IOException e) {
			System.err.println(e.getMessage());
		}

		lines.remove(0);
		lines.forEach(line -> {
			String[] data = line.split(",", -1);
			Municipality m;

			if(!data[9].isEmpty()) {
				m = newMunicipality(data[1], data[2], newCommunity(data[9], Community.Type.COLLINARE)); 
			}else if(!data[10].isEmpty()) {
				m = newMunicipality(data[1], data[2], newCommunity(data[10], Community.Type.MONTANA)); 
			}else {
				m = newMunicipality(data[1], data[2]);
			}
			School s = newSchool(data[6], data[5], Integer.parseInt(data[2]), data[3]);
			newBranch(Integer.parseInt(data[4]), m, data[7], Integer.parseInt(data[8]), s);
		});
	}

	/**
	 * Counts how many schools there exist for each description
	 * @return a map of school count vs. description
	 */
	public Map<String,Long>countSchoolsPerDescription(){
		return
			schools.stream()
			.collect(
				groupingBy(
					School::getDescription,
					counting()
				)
			);
	}

	/**
	 * Count how many school branches there exist for each municipality
	 * @return a map of branch count vs. municipality
	 */
	public Map<String,Long>countBranchesPerMunicipality(){
//		return
//			branches.stream()
//			.collect(
//				groupingBy(
//					b -> ((Branch)b).getMunicipality().getName(),
//					counting()
//				)
//			);

		return
			municipalities.stream()
			.collect(
					toMap(
						Municipality::getName,
						m -> new Long(m.getBranches().size())
					)
			);
	}

	/**
	 * Counts the number of school branches per municipality
	 * and groups them by province.
	 * @return a map of maps the inner reports count of branches vs. municipality
	 * 			the outer reports provinces as keys
	 */
	public Map<String,Map<String,Long>>countBranchesPerMunicipalityPerProvince(){
		return
			branches.stream()
			.collect(
				groupingBy(
					b -> ((Branch)b).getMunicipality().getProvince(),
					groupingBy(
						b -> ((Branch)b).getMunicipality().getName(),
						counting()
					)
				)
			);
	}


	/**
	 * returns a list of strings with format
	 * {@code "### - XXXXXX"}, where 
	 * {@code ###} represents the number of schools (not branches)
	 * and {@code XXXXXX} represents the name of the municipality.
	 * If a school has more than one branch in a municipality
	 * it must be counted only once.
	 * 
	 * @return a collection of strings with the counts
	 */
	public Collection<String> countSchoolsPerMunicipality(){
		return
			branches.stream()
			.collect(
				groupingBy(
					b -> ((Branch)b).getMunicipality().getName(),
					TreeMap::new,
					groupingBy(
						b -> ((Branch)b).getSchool().getCode(),
						counting()
					)
				)
			)
			.entrySet()
			.stream()
			.map(v -> v.getValue().size() + " - " + v.getKey())
			.collect(toList());
	}
	
	/**
	 * returns a list of strings with format
	 * {@code "### - XXXXXX"}, where 
	 * {@code ###} represents the number of schools (not branches)
	 * and {@code XXXXXX} represents the name of the community.
	 * They are sorted by descending number of schools.
	 * The list must contain only schools having at least
	 * a branch in a municipality part of a community.
	 * 
	 * @return a collection of strings with the counts
	 */
	public List<String> countSchoolsPerCommunity(){
		return
			branches.stream()
			.filter(b -> ((Branch)b).getMunicipality().getCommunity().isPresent())
			.collect(
				groupingBy(
					b -> ((Branch)b).getMunicipality().getCommunity().get().getName(),
					groupingBy(
						b -> ((Branch)b).getSchool().getCode(),
						counting()
					)
				)
			).entrySet()
			.stream()
			.sorted((a,b)->b.getValue().values().size()-a.getValue().values().size())
			.map(v -> v.getValue().size() + " - " + v.getKey())
			.collect(toList());
	}

	
}
