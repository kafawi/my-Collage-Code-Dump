package dykstra;

import graph.Node;

public class DNode implements Comparable<DNode> {
	/**
	 * infinity
	 */
	public static final int UNCOST = -1;

	/**
	 * node of interest
	 */
	public Node<?> node;
	/**
	 * gateway to goal
	 */
	public DNode pred;
	/**
	 * Cost to goal (min)
	 */
	public int cost;
	/**
	 * flag, if this node got its the shortest path to goal
	 */
	public boolean marked;

	/**
	 * Constructor with
	 * 
	 * @param node
	 */
	public DNode(Node<?> node) {
		this.node = node;
		pred = null;
		cost = UNCOST;
		marked = false;
	}

	/**
	 * makes the node as done
	 */
	public void mark() {
		marked = true;
	}

	@Override
	public int compareTo(DNode o) {
		return cost - o.cost;
	}
}
