package hydraulic;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Main class that act as a container of the elements for
 * the simulation of an hydraulics system 
 * 
 */
public class HSystem {
	//private Element[] elements;
	private List<Element> elements;
	private int elementsNum = 0;
	
	public HSystem() {
		//elements = new Element[MAX_ELEMENTS];
		elements = new ArrayList<>();
	}
	
	/**
	 * Adds a new element to the system
	 * @param elem
	 */
	public void addElement(Element elem){
		//elements[elementsNum++] = elem;
		elements.add(elem);
	}
	
	/**
	 * returns the element added so far to the system
	 * @return an array of elements whose length is equal to the number of added elements
	 */
	public Element[] getElements(){
		return Arrays.copyOf(elements.toArray(new Element[elements.size()]), elements.size());
	}
	
	/**
	 * Starts the simulation of the system
	 */
	public void simulate(){
//		for(Element e : elements) {
//			if(e instanceof Source) {
//				e.simulate(0);
//			}
//		}
		
		elements.forEach(e -> {
			if(e instanceof Source) {
				e.simulate(0);
			}
		});
	}
	
	/**
	 * Prints the layout of the system starting at each Source
	 */
	public String layout(){
		StringBuffer layoutString = new StringBuffer();
		
		for(int i = 0; i < elementsNum; i++) {
			if(elements.get(i) instanceof Source) {
				layoutString.append(elements.get(i).layout(0, 0));
			}
		}
		return layoutString.toString();
	}
}
