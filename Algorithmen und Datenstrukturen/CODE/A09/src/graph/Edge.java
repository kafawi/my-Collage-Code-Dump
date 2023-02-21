package graph;

/**
 * Weighted Edge
 * @author kafa
 *
 */
public class Edge {
	/**
	 * source (origin) 
	 */
	protected Node<?> from;
	/**
	 * destination 
	 */
	protected Node<?> to;
	
	/**
	 * Cost from -> to
	 * 
	 */
	protected int weight;
	
	/**
	 * Constructor
	 * @param from
	 * @param to
	 * @param cost
	 */
	public Edge(Node<?> from, Node<?> to, int weight){
		this.from = from;
		this.to   = to;
		this.weight = weight;
	}
	
	/**
	 * Getter cost
	 * @return
	 */
	public int getWeigth(){
		return weight;
	}
	/**
	 * Getter from (origin)
	 * @return
	 */
	public Node<?> getFrom(){
		return from;
	}
	
	/**
	 * Getter to (destination)
	 * @return
	 */
	public Node<?> getTo(){
		return to;
	}
	
	

}
