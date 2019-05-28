package hydraulic;

/**
 * Represents a split element, a.k.a. T element
 * 
 * During the simulation each downstream element will
 * receive a stream that is half the input stream of the split.
 */

public class Split extends Element {
	private static final int MAX_OUTPUT = 2;
	
	private Element[] outputElements = new Element[MAX_OUTPUT];

	/**
	 * Constructor
	 * @param name
	 */
	public Split(String name) {
		super(name);
	}
    
	/**
	 * returns the downstream elements
	 * @return array containing the two downstream element
	 */
    public Element[] getOutputs(){
    	int elementsNumber = 0;
    	for(Element element: outputElements) {
    		if(element != null)
    			elementsNumber++;
    	}
    	
    	Element[] returnElements = new Element[elementsNumber];
    	
    	for(int k=0, i=0; i<outputElements.length && k<elementsNumber; i++) {
    		if(outputElements[i] != null) {
    			returnElements[k++] = outputElements[i];
    		}
    	}
        return returnElements;
    }
    
    @Override
    public void connect(Element elem) {
    	System.out.println("Error: this is a T element. Please specify which output\n");
    }
    
	/**
	 * Connects one output of this element to a given element.
	 * The given element will be connected downstream of selected output
	 * @param elem the element that will be placed downstream
     * @param noutput the number of the output (0 or 1)
	 */
	public void connect(Element elem, int noutput){
		if(noutput != 0 && noutput != 1) {
			System.out.println("Error: a T element only has 2 output. Please use '0' and '1' only\n");
			return;
		}else{
			outputElements[noutput] = elem;
			elem.setInput(this);	
		}
	}

	@Override
	public void simulate(double inputFlow) {
		Element[] outputElements = getOutputs();
		
		if(outputElements.length != 2) {
			System.out.println("Error: split " + super.getName() + " should have 2 outputs");
			return;
		}
		
		double outputFlow = inputFlow / outputElements.length;
		
		System.out.println("Split " + super.getName() + ": input " + inputFlow + ", output " + outputFlow + " for each");
		for(Element outputElem: outputElements) {
			outputElem.simulate(outputFlow);
		}
	}

	@Override
	public StringBuffer layout(double inputFlow, int spacesBefore) {
		int spaces = 0;
		boolean isFirstOuput = true;
		Element[] outputElements = getOutputs();
		double outputFlow = inputFlow / outputElements.length;
		StringBuffer stringOutput = new StringBuffer();
		
		stringOutput.append("[" + super.getName() + "]Split ");
		
		for(Element outputElem: outputElements) {
			if(isFirstOuput) {
				isFirstOuput = false;
				spaces = spacesBefore + stringOutput.length();
			}else {
				stringOutput.append("");
				for(int i=0; i<spaces; i++)
					stringOutput.append(" ");
				stringOutput.append("|\n");
				for(int i=0; i<spaces; i++)
					stringOutput.append(" ");
			}
			
			/*
			 * 4 is the len of "+-> "
			 */
			stringOutput.append("+-> " + outputElem.layout(outputFlow, spaces + 4));
		}
		
		return stringOutput;
	}
}
