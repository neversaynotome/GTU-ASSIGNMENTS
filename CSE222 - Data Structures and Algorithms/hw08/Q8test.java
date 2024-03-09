/**
* Testing for for Q4
* 
* @author  Siyar
*/

import java.lang.*;
import java.util.*;
import src.*;

public class Q8test {

	public static void main(String args[]) {

		System.out.println("\n------------------------------------\n\n");

		MyGraph graph = new MyGraph(true);	// initialize a graph

		graph.addVertex(graph.newVertex("deneme9"));	// add vertices
		graph.addVertex(graph.newVertex("deneme8"));
		graph.addVertex(graph.newVertex("deneme7"));
		graph.addVertex(graph.newVertex("deneme5"));
		graph.addVertex(graph.newVertex("deneme3"));
		graph.addVertex(graph.newVertex("deneme1"));

		graph.addEdge(0, 1, 5.0);	// add edges
		graph.addEdge(0, 2, 9.0);
		graph.addEdge(1, 2, 10.0);
		graph.addEdge(1, 3, 7.0);
		graph.addEdge(2, 3, 8.0);
		graph.addEdge(3, 0, 6.0);
		graph.addEdge(3, 4, 2.0);
		graph.addEdge(5, 4, 4.0);

		graph.addProperty(0, "Boost", "0.0");	// add boosting values for dijkstra's algorithm
		graph.addProperty(1, "Boost", "3.0");
		graph.addProperty(2, "Boost", "3.0");
		graph.addProperty(3, "Boost", "1.0");
		graph.addProperty(4, "Boost", "4.0");
		graph.addProperty(5, "Boost", "2.0");

		graph.addProperty(1, "color", "red");
		graph.addProperty(3, "color", "red");

		graph.printGraph();
		
		graph.weightDifference();	// second question

		graph.getDA(0);				// third question

		double[][] export = graph.exportMatrix();	// exportmatrix test
		printMatrix(export);

		graph.removeVertex("deneme3");
		graph.printGraph();
		graph.addVertex(graph.newVertex("deneme5", 5));
		graph.printGraph();
		graph.removeVertex(0);

		MyGraph graphCopy = graph.filterVertices("color", "red");
		
		graphCopy.printGraph();

		MyGraph undirectedgraph = new MyGraph(false);	// initialize a graph

		undirectedgraph.addVertex(undirectedgraph.newVertex("deneme7"));	// add vertices
		undirectedgraph.addVertex(undirectedgraph.newVertex("deneme5"));
		undirectedgraph.addVertex(undirectedgraph.newVertex("deneme3"));
		undirectedgraph.addVertex(undirectedgraph.newVertex("deneme1"));

		undirectedgraph.addEdge(0, 1, 5.0);	// add edges which are mirrored for undirected graphs
		undirectedgraph.addEdge(0, 2, 9.0);
		undirectedgraph.addEdge(1, 2, 10.0);
		undirectedgraph.addEdge(1, 3, 7.0);
		undirectedgraph.addEdge(2, 3, 8.0);
		undirectedgraph.addEdge(3, 0, 6.0);

		undirectedgraph.printGraph();

		System.out.println("\n\n------------------------------------\n");
	}

	public static void printMatrix(double[][] export) {	// prints the matrix out

		System.out.printf("\n");
		for (int i = 0; i < 6; ++i) {
			System.out.printf("[Node:");
			System.out.print(i + "]");
			for (int j = 0; j < 6; ++j) {
				System.out.printf(" > ");
				System.out.printf("[Node:" + j);
				if (export[i][j] == Double.POSITIVE_INFINITY)
					System.out.printf("|" + "null" + "]");				
				else
					System.out.printf("|" + export[i][j] + "]");				
			}
			System.out.printf("\n");		
		}
		System.out.printf("\n");

	}
}