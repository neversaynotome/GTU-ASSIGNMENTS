package src;

import java.util.*;

/** A class that implements the 
 *  breadth-first search algorithm.
 *  @author Siyar
 * */

public class BreadthFirstSearch {

	public static double total = 0;

	/** Perform breadth-first search of a graph.
			post: The array parent will contain the predecessor
						of each vertex in the breadth-first
						search tree.
			@param graph The graph to be searched
			@param start The start vertex
			@return The array of parents
	 */
	public static int[] breadthFirstSearch(MyGraph graph, int start) {

		Queue < Integer > queue = new LinkedList < Integer > ();	// used for adjacent operations
		int[] parent = new int[graph.getNumV()];	// holds predecessors
		for (int i = 0; i < graph.getNumV(); i++) {
			parent[i] = -1;
		}

		boolean[] visited = new boolean[graph.getNumV()];
		visited[start] = true;	// visited vertices
		queue.offer(start);

		while (!queue.isEmpty()) {

			int current = queue.remove();
			int neighbors[] = graph.getEdges(current);	// sorted edges are returned
			int i = 0;

			while (i < neighbors.length) {
				int neighbor = neighbors[i];
				++i;

				if (!visited[neighbor]) {

					visited[neighbor] = true;
					queue.offer(neighbor);
					total += graph.getWeight(current, neighbor);
					parent[neighbor] = current;
				}
			}
		}
		return parent;
	}
}
