package src;

import java.util.*;

/** A class that implements Dijkstra's algorithm.
 *  @author Siyar
 */

public class DijkstrasAlgorithm {

	/** Dijkstra's Shortest-Path algorithm.
			@param graph graph to be searched
			@param start initial vertex
			@param pred Output array of the predecessors
			@param dist Output array that contains the distance
	 */
	public static void dijkstrasAlgorithm(MyGraph graph, int start, int[] pred, double[] dist) {

		int numV = graph.getNumV();
		HashSet < Integer > vs = new HashSet < Integer > (numV);

		for (int i = 0; i < numV; i++) {
			if (i != start) {
				vs.add(i);
			}
		}

		for (int v : vs) {
			pred[v] = start;
			dist[v] = graph.getWeight(start, v) - Double.parseDouble(graph.getProperty(v, "Boost"));
		}

		while (vs.size() != 0) {

			double minDist = Double.POSITIVE_INFINITY;
			int u = -1;
			for (int v : vs) {
				if (dist[v] <= minDist) {
					minDist = dist[v];
					u = v;
				}
			}

			vs.remove(u);

			for (int v : vs) {
				if (graph.isEdge(u, v)) {
					double weight = graph.getWeight(u, v) - Double.parseDouble(graph.getProperty(v, "Boost"));
					if (dist[u] + weight < dist[v]) {
						dist[v] = dist[u] + weight;
						pred[v] = u;
					}
				}
			}
		}
	}
}
