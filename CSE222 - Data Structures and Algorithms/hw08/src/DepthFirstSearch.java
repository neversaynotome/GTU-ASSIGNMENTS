package src;

import java.util.*;

/** A class that implements the 
 *  depth-first search algorithm.
 *  @author Siyar
**/

public class DepthFirstSearch {

	private MyGraph graph;		// the graph itself
	private int[] parent;		// array of predecessor
	private boolean[] visited;	// holds visited vertices
	private int[] discovery;	// discovery order
	private int[] finish;		// finish order
	private int dIndex = 0;
	private int fIndex = 0;
	private double total = 0;	// total weight

	/** Constructor initializes data fields accordingly.
	 *	@param graph The graph
	 */
	public DepthFirstSearch(MyGraph graph) {

		this.graph = graph;
		int n = graph.getNumV();
		parent = new int[n];
		visited = new boolean[n];
		discovery = new int[n];
		finish = new int[n];

		for (int i = 0; i < n; i++) {
			parent[i] = -1;
		}
		for (int i = 0; i < n; i++) {
			if (!visited[i])
				depthFirstSearch(i);
		}
	}

	/** Recursive method that does depth-first
	 *  search of the graph starting at current.
	 *	@param current initial vertex
	 */
	public void depthFirstSearch(int current) {

		visited[current] = true;		// initial vertex is marked
		discovery[dIndex++] = current;	// and it is added to discovery

		int neighbors[] = graph.getEdges(current);	// sorted edges are returned
		int i = 0, neighbor;
		while (i < neighbors.length) {

			neighbor = neighbors[i];
			++i;

			if (!visited[neighbor]) {
				total += graph.getWeight(current, neighbor);
				parent[neighbor] = current;
				depthFirstSearch(neighbor);	// recursive call
			}
		}
		finish[fIndex++] = current;
	}

	public double getTotal() {
		return total;
	}
}
