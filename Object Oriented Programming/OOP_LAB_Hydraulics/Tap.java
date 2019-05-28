package hydraulic;

/**
 * Represents a tap that can interrupt the flow.
 * 
 * The status of the tap is defined by the method
 * {@link #setOpen(boolean) setOpen()}.
 */

public class Tap extends Element {
	
	private boolean open;

	public Tap(String name) {
		super(name);
		//TODO: complete
	}
	
	public void setOpen(boolean open){
		this.open = open;
	}
	
	public boolean isOpen() {
		return open;
	}

	@Override
	public void simulate(double inputFlow) {
		double outputFlow = (this.open) ? inputFlow : 0;
		
		System.out.println("Tap " + super.getName() + ": input " + inputFlow + ", output " + outputFlow);
		
		Element nextElement = super.getOutput();
		if(nextElement == null) {
			System.out.println("Error: tap " + super.getName() + " should have an output");
			return;
		}
		
		nextElement.simulate(outputFlow);
	}

	@Override
	public StringBuffer layout(double inputFlow, int spacesBefore) {
		double outputFlow = (open) ? inputFlow : 0;
		
		StringBuffer outputString = new StringBuffer();
		
		outputString.append("[" + super.getName() + "]Tap -> ");
		outputString.append(super.getOutput().layout(outputFlow, spacesBefore + outputString.length()));
		
		return outputString;
	}

}
