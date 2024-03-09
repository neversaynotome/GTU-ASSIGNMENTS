package src;

import java.util.*;
import java.io.*;

/** Implementation of MyGraph Class asked in the first question
*	 @author Siyar
*/

public class MyGraph implements DynamicGraph {

	// Data Fields
	private ArrayList < LinkedList < Vertex > > edges = new ArrayList < LinkedList < Vertex > >();
	private ArrayList < Vertex > vertices = new ArrayList < Vertex >();
	private int numV = 0;		// current number of vertices
	private int removedV = 0;	// removed vertex count
	private boolean directed;

	public MyGraph(boolean directed) {
		this.directed = directed;
	}

	/** Copy constructor.
	 */
	public MyGraph(MyGraph other) {
		this.vertices = new ArrayList < Vertex >(other.vertices);
		this.edges = new ArrayList < LinkedList < Vertex > >(other.edges);
		this.numV = other.numV;
		this.removedV = other.removedV;
		this.directed = other.directed;
	}
	
	public int getNumV() {
		return numV;
	}

	public boolean isDirected() {
		return directed;
	}

	private int getRemovedV() {
		return removedV;
	}

	/** Crucial part of traversal algorithms.
	 *  returns array of edges that is sorted by smallest
	 *  hence priorites smaller weight.
	 */
	public int[] getEdges(int vertexIndex) { // returns an array that includes indexes to adjecent vertices from the smaller to bigger

		int [] toReturn = new int[edges.get(vertexIndex).size()];

		for (int i = 0; i < toReturn.length; ++i)
			toReturn[i] = i;

		for (int i = 0; i < toReturn.length - 1; i++)
			for (int j = 0; j < toReturn.length - i - 1; j++)
				if ( edges.get(vertexIndex).get(toReturn[j]).getWeight() > edges.get(vertexIndex).get(toReturn[j + 1]).getWeight() ) {
					int temp = toReturn[j];				// swap if weight is smaller
					toReturn[j] = toReturn[j + 1];
					toReturn[j + 1] = temp;
				}

		for (int i = 0; i < toReturn.length; ++i)
			toReturn[i] = edges.get(vertexIndex).get(toReturn[i]).getID(); // return IDs in sorted order

		return toReturn;
	}

	public double getWeight(int vertexID1, int vertexID2) {	// return weight of an edge that is from vertexID1 to vertexID2

		for (int i = 0; i < edges.get(vertexID1).size(); ++i) {
			if (edges.get(vertexID1).get(i).getID() == vertexID2)
				return edges.get(vertexID1).get(i).getWeight();
		}
		return Double.POSITIVE_INFINITY;
	}

	/** looks if the edge exists
	 */
	public boolean isEdge(int source, int dest) {
		
		boolean toReturn = false;
		
		int index1 = indexFinder(source);
		int index2 = indexFinder(dest);

		if (index1 == -1 || index2 == -1) {
			System.out.printf("\nInvalid ID(s) detected, unable to find the edge.\n");
			return toReturn;
		}

		for (int i = 0; i < edges.get(index1).size(); ++i) {
			if (edges.get(index1).get(i).getID() == index2)
				toReturn = true;
		}

		return toReturn; 
	}

	/** return a new "Vertex" object
	 */
	public Vertex newVertex (String label, double weight) {
		return new Vertex(numV + removedV, label, weight);
	}

	/** return a new "Vertex" object
	 */
	public Vertex newVertex (String label) {
		return new Vertex(numV + removedV, label);
	}

	/** add a new "Vertex" object to "vertices"
	 */
	public boolean addVertex (Vertex new_vertex) {

		if (numV + removedV != new_vertex.getID()) {
			System.out.printf("\nInvalid ID detected, unable to add the vertex.\n");
			return false;
		}
		vertices.add(new_vertex);
		edges.add(new LinkedList < Vertex >());
		++numV;
		return true;
	}

	/** adds a new edge object to "edges"
	 * @param vertexID1 source vertex
	 * @param vertexID2 destination vertex
	 * @param weight weight of the edge
	 */
	public boolean addEdge (int vertexID1, int vertexID2, double weight) {

		if (vertexID1 >= numV || vertexID1 < 0 || vertexID2 < 0 || vertexID2 >= numV)
			System.out.printf("\nInvalid ID detected, unable to add the edge.\n");

		edges.get(vertexID1).add(new Vertex(vertexID2, "EDGE", weight));

		if (!directed)
			edges.get(vertexID2).add(new Vertex(vertexID1, "EDGE", weight));

		return true;
	}

	/** removes an edge
	 * @param vertexID1 source vertex
	 * @param vertexID2 destination vertex
	 */
	public boolean removeEdge (int vertexID1, int vertexID2) {

		if (indexFinder(vertexID1) == -1 || indexFinder(vertexID2) == -1) {
			System.out.printf("\nInvalid ID detected, unable to remove the edge.\n");
			return false;
		}

		remover(vertexID1, vertexID2);

		if (!directed)
			remover(vertexID2, vertexID1);
		return true;
	}

	private void remover (int vertexID1, int vertexID2) {	// helper method that actually removes the edge from the "edges" field

		int index1 = indexFinder(vertexID1);
		int index2 = indexFinder(vertexID2);

		for (int i = 0; i < edges.get(index1).size(); ++i) {
			if (edges.get(index1).get(i).getID() == vertexID2) {
				edges.get(index1).remove(i);
			}
		}
	}

	/** removes an Vertex
	 * @param vertexID vertex to be deleted
	 */
	public boolean removeVertex (int vertexID) {

		int index = indexFinder(vertexID);

		if (index == -1) {
			System.out.printf("\nInvalid ID detected, unable to remove the vertex.\n");
			return false;
		}
		vertices.remove(index);
		for (int i = 0; i < edges.size(); ++i) {
			for (int j = 0; j < edges.get(i).size(); ++j) {
				if (i != index && edges.get(i).get(j).getID() == vertexID) {
					edges.get(i).remove(j);
				}
			}
		}
		edges.remove(index);
		--numV; ++removedV;
		return true;
	}

	/** removes an Vertex
	 * @param label vertex to be deleted
	 */
	public boolean removeVertex (String label) {

		int index = indexFinder(label);

		if (index == -1) {
			System.out.printf("\nInvalid ID detected, unable to remove the vertex.\n");
			return false;
		}

		return removeVertex( vertices.get( index ).getID() );
	}
	// helper function to find index of a vertex
	private int indexFinder(int vertexID) {
		for (int i = 0; i < vertices.size(); ++i)
			if (vertices.get(i).getID() == vertexID)
				return i;
		return -1;
	}
	// helper function to find index of a vertex
	private int indexFinder(String vertexLabel) {
		for (int i = 0; i < vertices.size(); ++i)
			if (vertices.get(i).getLabel() == vertexLabel)
				return i;
		return -1;
	}

	/** adds a new property to a vertex object
	 * @param vertexID ID of the vertex
	 * @param key key of the property
	 * @param value propery itself
	 */
	public boolean addProperty(int vertexID, String key, String value) {

		int index = indexFinder(vertexID);

		if (index == -1) {
			System.out.printf("\nInvalid ID detected, unable to add the property.\n");
			return false;
		}

		return vertices.get(index).addProperty(key, value);
	}

	/**	returns a value according to parameter
	 * @param vertexID ID of the vertex
	 * @param key key to return value of
	 */
	public String getProperty(int vertexID, String key) {

		int index = indexFinder(vertexID);

		if (index == -1) {
			System.out.printf("\nInvalid ID detected, unable to get the value.\n");
			return "null";
		}

		return vertices.get(index).getProperty(key);
	}

	public MyGraph filterVertices (String key, String filter) {

		MyGraph toReturn = new MyGraph(this);

		for (int i = 0; i < vertices.size(); ++i)
			if (!vertices.get(i).getProperty(key).equals(filter))
				toReturn.removeVertex(vertices.get(i).getID());

		return toReturn;
	}

	/** returns a matrix representation of the graph.
	 */
	public double[][] exportMatrix() {

		double[][] export = new double[numV][];

			for (int i = 0; i != numV; ++i) {
				export[i] = new double[numV];
				for (int j = 0; j != numV; ++j) {
					export[i][j] = Double.POSITIVE_INFINITY;
				}
			}
			for (int i = 0; i < edges.size(); ++i) {
				for (int j = 0; j < edges.get(i).size(); ++j) {
					export[i][indexFinder( edges.get(i).get(j).getID() )] = edges.get(i).get(j).getWeight();
				}
			}
		
		return export;
	}

	/** prints the graph.
	 */
	public void printGraph() {

		System.out.printf("\n");
		for (int i = 0;i < vertices.size(); ++i) {
			System.out.printf("[Node:");
			System.out.print(vertices.get(i).getID() + "]");
			for (int j = 0; j < edges.get(i).size(); ++j) {
				System.out.printf(" > ");
				System.out.printf("[Node:" + edges.get(i).get(j).getID());
				System.out.printf("|" + edges.get(i).get(j).getWeight() + "]");				
			}
			System.out.printf("\n");		
		}
		System.out.printf("\n");
	}

	/** method for the second question,
	 *  prints the difference between BFS and DFS.
	 */
	public double weightDifference() {

		DepthFirstSearch dfs = new DepthFirstSearch(this);

		BreadthFirstSearch bfs = new BreadthFirstSearch();
		bfs.breadthFirstSearch(this, 0);

		System.out.printf("\nDistance of BFS: " + bfs.total
						 + " Distance of DFS: " + dfs.getTotal() + "\n"
						 + "Difference: " + (bfs.total - dfs.getTotal()) + "\n");

		return bfs.total - dfs.getTotal();
	}


	/** method for the third question,
	 *  prints shortest path.
	 */
	public void getDA(int vertexID) {

		int[] pred = new int[getNumV()];
		double[] dist = new double[getNumV()];

		DijkstrasAlgorithm.dijkstrasAlgorithm(this, vertexID, pred, dist);

		for (int i = vertexID; i < dist.length; ++i)
			dist[i] += Double.parseDouble(getProperty(i, "Boost"));

		System.out.printf("\nDistances from " + vertexID + " to:\n");

		for (int i = 0; i < dist.length; ++i)
			if (i != vertexID)
				System.out.print(i + ": " + dist[i] + "\n");
	
		System.out.printf("\n");
	}

	/** Insert a new vertex into the graph.
		@param vertex The new vertex
	 */
	public void insert(Edge edge) {
		addEdge (edge.getSource(), edge.getDest(), edge.getWeight());
	}

	public Iterator < Edge > edgeIterator(int source) {
		ArrayList < ArrayList < Edge > > dummy = new ArrayList < ArrayList < Edge > >();
		return dummy.get(source).iterator();
	}

	public Edge getEdge(int source, int dest) {
		Edge edge = new Edge(source, dest, Double.POSITIVE_INFINITY);
		return edge;
	}
}
