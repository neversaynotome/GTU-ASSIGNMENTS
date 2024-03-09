package src;

import java.util.*;

/** Interface DynamicGraph that 
*   is asked for the homework
*   @author Siyar
*/

public interface DynamicGraph extends Graph {

	Vertex newVertex (String label, double weight); // Generate a new vertex by given parameters.
	
	boolean addVertex (Vertex new_vertex); // Add the given vertex to the graph.
	
	boolean addEdge (int vertexID1, int vertexID2, double weight); // Add an edge between the given two vertices in the graph.
	
	boolean removeEdge (int vertexID1, int vertexID2); // Remove the edge between the given two vertices.
	
	boolean removeVertex (int vertexID); // Remove the vertex from the graph with respect to the given vertex id.
	
	boolean removeVertex (String label); // Remove the vertices that have the given label from the graph.
	
	MyGraph filterVertices (String key, String filter); // Filter the vertices by the given user-defined property and returns 
																				   // a subgraph of the graph.
	
	double[][] exportMatrix(); // Generate the adjacency matrix representation of the graph and returns the matrix.
	
	void printGraph(); // Print the graph in adjacency list format (You should use the format that can be imported by the method in AbstractGraph in the book).

}
