package schools;

import java.util.ArrayList;
import java.util.Collection;

/**
 * Represents a community.
 * A community may consist of several {@link Municipality municipalities} belonging to the community.
 * There are two {@link Community.Type types} of community:
 * <ul>
 * <li>{@code Community.Type.MONTANA}: mountain community
 * <li>{@code Community.Type.COLLINARE}: hill community
 * </ul>
 */
public class Community {
	private String name;
	private Type type;
	private Collection<Municipality> municipalities;
	
	/**
	 * Enumeration of valid {@link Community} types.
	 *
	 */
	public enum Type {
		/**
		 * Mountain community
		 */
		MONTANA, 
		/**
		 * Hill community
		 */
		COLLINARE };
		
	public Community(String name, Type type) {
		this.name = name;
		this.type = type;
		municipalities = new ArrayList<>();
	}
	
	/**
	 * Getter method for the community name
	 * 
	 * @return name of the community
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Getter method for the community type
	 * 
	 * @return type of the community
	 */
	public Type getType(){
		return type;
	}

	/**
	 * Retrieves the municipalities the belong to this community
	 * 
	 * @return collection of municipalities
	 */
	public Collection<Municipality> getMunicipalities() {
		return municipalities;
	}
	
	/*
	 * Add municipalty to this community
	 */
	public void addMunicipalty(Municipality m) {
		municipalities.add(m);
	}
}
