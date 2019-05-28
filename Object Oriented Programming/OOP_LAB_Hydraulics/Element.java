package hydraulic;

/**
 * Represents the generic abstract element of an hydraulics system.
 * It is the base class for all elements.
 *
 * Any element can be connect to a downstream element
 * using the method {@link #connect(Element) connect()}.
 */
public abstract class Element {
	
	private String name;
	private Element inputElement;
	private Element outputElement;
	
	/**
	 * Constructor
	 * @param name the name of the element
	 */
	public Element(String name){
		this.name = name;
	}
	protected Element(String name, int n) {
		
	}

	/**
	 * getter method
	 * @return the name of the element
	 */
	public String getName(){
		return this.name;
	}
	
	/**
	 * setter method
	 * @param name the name of the element
	 */
	protected void setName(String name) {
		this.name = name;
	}
	
	/**
	 * Connects this element to a given element.
	 * The given element will be connected downstream of this element
	 * @param elem the element that will be placed downstream
	 */
	public void connect(Element elem){
		if(elem instanceof Source) {
			System.out.println("Error: cannot connect element to a source\n");
			return;
		}
		outputElement = elem;
		elem.inputElement = this;
	}
	
	/**
	 * Connects a given element to this.
	 * This element will be connected downstream of the given element
	 * @param elem the element that will be placed upstream
	 */
	protected void setInput(Element elem){
		this.inputElement = elem;
	}
	
	
	public Element getInput(Element elem) {
		return inputElement;
	}
	
	/**
	 * Retrieves the element connected downstream of this
	 * @return downstream element
	 */
	public Element getOutput(){
		return outputElement;
	}
	
	/**
	 * Simulate from this element
	 * @param inputFlow the input flow
	 */
	public abstract void simulate(double inputFlow);
	
	public abstract StringBuffer layout(double inputFlow, int spacesBefore);
}
