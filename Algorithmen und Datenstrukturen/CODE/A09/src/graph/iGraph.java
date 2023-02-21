package graph;

import java.util.List;

/**
 * Interface of an Graph
 *
 */
public interface iGraph {

	/**
	 * Adds an Node
	 * @param node
	 */
	public void addNode(Node<?> node);
	
	/**
	 * Adds an Edge 
	 * @param edge
	 */
	public void addEdge(Edge edge);
	
	/**
	 * Adds an Edge 
	 * @param from Node where the edge starts
	 * @param to   Node where the edge ends
	 * @param weight Weight of the Edge != -1 && 0
	 */
	public void addEdge(Node<?> from, Node<?> to, int weight);

	/**
	 * Removes a node in a Graph
	 * @param node node to remove
	 */
	public void removeNode(Node<?> node);

	
	///**
	// * Travers from a node to another
	// * @param from startNode
	// * @param to   endnode
	// */
	//public void traverse(Node<?> from, Node<?> to);


	/**
	 * Returns the weight of an edge between 2 nodes
	 * @param nodeA start node
	 * @param nodeB end node of edge
	 * @return weight of the edge, if no connection: -1
	 */
	public int getWeight(Node<?> nodeA, Node<?> nodeB);
	
	/**
	 * Returns all Nodes in a Graph
	 * @return List of all nodes in Graph
	 */
	public List<Node<?>> getNodes();

	
	/**
   * retruns all Neighbors of a Node
   * @param node node whoms neighbors are wanted
   * @return list of nodes
   */
  public List<Node<?>> getNeighbors(Node<?> node);
}
