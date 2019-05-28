package schools;

import java.util.Collection;
import java.util.Map;
import java.util.Optional;
import java.util.TreeMap;

/**
 * Represents a municipality.
 * A municipality may belong to a {@link Community}
 *
 */

public class Municipality {
	private String name;
	private String province;
	private Optional<Community> community;
	private Map<Integer, Branch> branches;
	
	public Municipality(String name, String province, Optional<Community> community) {
		this.name = name;
		this.province = province;
		this.community = community;
		this.branches = new TreeMap<>();
	}

	/**
	 * Getter method for the municipality's name
	 * 
	 * @return name of the municipality
	 */
	public String getName() {
		return name;	
	}
	
	/**
	 * Getter method for province where the municipality lies
	 * 
	 * @return province of the municipality
	 */
	public String getProvince() {
		return province;
	}

	/**
	 * Retrieves the community the municipality belongs to as an {@link Optional}
	 * If the municipality the optional will be empty.
	 * 
	 * @return optional community
	 */
	public Optional<Community> getCommunity() {
		return community;
	}
	
	/**
	 * Retrieves all the school branches located in the municipality 
	 * 
	 * @return collection of branches
	 */
	public Collection<Branch> getBranches() {
		return branches.values();
	}
	
	public void addBranch(Branch branch) {
		if(!branches.containsKey(branch.getCode())) {
			branches.put(branch.getCode(), branch);
		}
	}
}
