package src;

import java.util.*;

/** Vertex class that holds necessary 
 * information for
 *	@author Siyar
*/

public class Vertex {

	private int id;
	private String label;
	private double weight;
	private ArrayList<String[]> properties = new ArrayList<String[]>(); 

	public Vertex(int id, String label) {
		this.id = id;
		this.label = label;
		weight = 1.0;
	}

	public Vertex(int id, String label, double w) {
		this.id = id;
		this.label = label;
		weight = w;
	}

	/** Get the id
		@return The value of id
	 */
	public int getID() {
		return id;
	}

	/** Get the label
		@return The value of label
	 */
	public String getLabel() {
		return label;
	}

	/** Get the weight
		@return the value of weight
	 */
	public double getWeight() {
		return weight;
	}

	public boolean addProperty(String key, String value) {
		String[] toAdd = {key, value};
		properties.add(toAdd);
		return true;
	}

	public String getProperty(String key) {

		for (int i = 0; i < properties.size(); ++i) {
			if (properties.get(i)[0].equals(key)) return properties.get(i)[1];
		}
		return "null";
	}

	/** toString override
		@return string representation
	 */
	public String toString() {
		StringBuffer sb = new StringBuffer("[(");
		sb.append(Integer.toString(id));
		sb.append(", ");
		sb.append(label);
		sb.append("): ");
		sb.append(Double.toString(weight));
		sb.append("]");
		return sb.toString();
	}

	/** Return true if two Vertexs are equal. Vertexs
		are equal if the id and label
		are equal. Weight is not conidered.
		@param obj The object to compare to
		@return true if the Vertexs have the same id
		and label
	 */
	public boolean equals(Object obj) {
	if (obj instanceof Vertex) {
		Vertex Vertex = (Vertex) obj;
		return (id == Vertex.id
				&& label == Vertex.label);
	}
	else
		return false;
	}
}
