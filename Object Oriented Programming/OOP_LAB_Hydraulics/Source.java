package hydraulic;

/**
 * Represents a source of water, i.e. the initial element for the simulation.
 *
 * Lo status of the source is defined through the method
 * {@link #setFlow(double) setFlow()}.
 */
public class Source extends Element {
	
	private double flow;

	public Source(String name) {
		super(name);
		//TODO: complete
	}

	public void setFlow(double flow){
		this.flow = flow;
	}
	
	public double getFlow() {
		return flow;
	}

	@Override
	public void simulate(double inputFlow) {
		inputFlow = this.flow;
		System.out.println("Source " + super.getName() + ": output " + inputFlow);
		
		Element nextElement = super.getOutput();
		if(nextElement == null) {
			System.out.println("Error: source " + super.getName() + " should have an output");
			return;
		}
		nextElement.simulate(inputFlow);
	}

	@Override
	public StringBuffer layout(double inputFlow, int spacesBefore) {
		inputFlow = flow;
		StringBuffer outputString = new StringBuffer();
		
		outputString.append("[" + super.getName() + "]Source -> ");
		outputString.append(super.getOutput().layout(inputFlow, spacesBefore + outputString.length()));
		
		return outputString;
	}
	
}
