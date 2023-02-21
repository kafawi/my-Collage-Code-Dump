package graph;

import java.util.HashMap;
/**#
 * Gibt einem Knoten eine Liste aus Knoten zu denen er benachbart ist und die 
 * Kostenum die Nachbarn zu erreichen.
 * @author peter
 *
 */
public class NodeEdgeList {
  
  public Node<?>  node;
  public HashMap<Node<?> , Integer> neighbors;
  
  
  public NodeEdgeList(Node<?> node, HashMap<Node<?>, Integer> neighbors) {
    super();
    this.node = node;
    this.neighbors = neighbors;
  }
  
  
  
  
  
  
  

}
