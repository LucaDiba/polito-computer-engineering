package hydraulic;

/**
 * Represents the sink, i.e. the terminal element of a system
 *
 */
public class Sink extends Element {

	/**
	 * Constructor
	 * @param name
	 */
	public Sink(String name) {
		super(name);
		//TODO: complete
	}
	
	@Override
	public void connect(Element elem) {
		System.out.println("Error: cannot connect element to a sink\n");
	}
	
	@Override
	public void simulate(double inputFlow) {
		System.out.println("Sink " + super.getName() + ": input " + inputFlow);
	}

	@Override
	public StringBuffer layout(double inputFlow, int spacesBefore) {
		return new StringBuffer("[" + super.getName() + "]Sink |\n");
	}
}
