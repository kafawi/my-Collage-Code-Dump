package graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import helper.Count;

/**
 * Implementation of an Graph with an Adjazenzmatrix
 * 
 * @author petra patretra
 *
 */
public class MatrixGraph implements iGraph {

	public Map<Node<?>, Integer> matrixMap;
	public int matrix[][];
	public int anzNodes = 0;
	public int nextInd;
	private List<Node<?>> nodes;

	/**
	 * Konstruktor Kein default weil der nicht gebraucht wird
	 * 
	 * @param matrix
	 *            Adjazenzmatrix zum initialisieren
	 * @param nodes
	 *            Liste der nodes, wenn null, default nodes
	 */
	public MatrixGraph(int[][] matrix, List<Node<?>> nodes) {
		this.nodes = new ArrayList<>();
		// super();
		if (null != matrix) {
			this.matrix = matrix;
			this.anzNodes = matrix[0].length;
			matrixMap = new HashMap<Node<?>, Integer>();

			for (int i = 0; i < anzNodes; i++) {
				if (null == nodes) {
					Node<?> n = new Node<Object>(null);
					matrixMap.put(n, i);
					this.nodes.add(n);
				} else {
					matrixMap.put(nodes.get(i), i);
					this.nodes.add(nodes.get(i));
				}
			}
		}
		nextInd = anzNodes;
	}

	@Override
	public void addNode(Node<?> node) {
		if (node != null && !(matrixMap.containsKey(node))) {
			int index = nextInd;
			matrixMap.put(node, index);
			anzNodes++;

			if (matrix[0].length < anzNodes) {
				enlargeMatrix(matrix[0].length);
			}

			matrix[index][index] = 0;
		}
	}

	/**
	 * vergroessert die weight matrix und initialisiert die verbleibenden
	 * stellen mit -1
	 * 
	 * @param oldLen
	 *            alte länge dr matrix
	 */
	private void enlargeMatrix(int oldLen) {
		int len = oldLen * 2;
		int newmat[][] = new int[len][len];
		for (int i = oldLen; i < len; i++) {
			for (int j = oldLen; j < len; j++) {
				newmat[i][j] = -1;
			}
		}
		for (int i = 0; i < oldLen; i++) {
			System.arraycopy(matrix[i], 0, newmat[i], 0, oldLen);
		}
		matrix = newmat;
	}

	@Override
	public void addEdge(Edge edge) {
		addEdge(edge.from, edge.to, edge.weight);
	}

	@Override
	public void addEdge(Node<?> from, Node<?> to, int weight) {
		Integer iFrom = matrixMap.get(from);
		Integer iTo = matrixMap.get(to);
		if (iFrom != null && iTo != null)
			matrix[iFrom][iTo] = weight;
	}

	/*
	 * Edges sollten auch entfernt werdn können, jedoch kann man dann einfach
	 * weight auf -1 setzten. also addEdge(from, to, -1)
	 * 
	 */

	@Override
	public void removeNode(Node<?> node) {
		/*
		 * Integer index = matrixMap.get(node); Integer last = anzNode;
		 * matrixMap. for (int i = 0; i < anzNodes; i++){ // put the last
		 * written row and col in this place // but how get i the node from the
		 * index?
		 * 
		 * }
		 */
		matrixMap.remove(node);
		nodes.remove(node);
		anzNodes--;

	}

	// @Override
	// public void traverse(Node<?> from, Node<?> to) {
	// TODO Auto-generated method stub
	// }

	@Override
	public List<Node<?>> getNeighbors(Node<?> node) {
		List<Node<?>> temp = new ArrayList<>();
		Integer index = matrixMap.get(node);
		if (index != null) {
			for (Node<?> neighbor : matrixMap.keySet()) {
				Count.up();
				Count.neighbor++;
				if (!neighbor.equals(node) && isEdge(index, neighbor)) {
					temp.add(neighbor);
				}
			}
		}
		return temp;
	}

	/// **
	// * Test ob ein edge existiert
	// *
	// * @param from
	// * ursprngsknotens
	// * @param to
	// * deastination Node
	// * @return
	// * wenn Edge existiert true, else false
	// */
	// private boolean isEdge(Node<?> from, Node<?> to){
	// boolean ret = false;
	// Integer iFrom = matrixMap.get(from);
	// Integer iTo = matrixMap.get(to);
	// if (iFrom != null && iTo !=null && matrix[iFrom][iTo] >= 0){
	// ret = true;
	// }
	// return ret;
	// }
	/**
	 * Test ob ein edge existiert
	 * 
	 * @param iFrom
	 *            index des ursprngsknotens
	 * @param to
	 *            deastination Node
	 * @return wenn Edge existiert true, else false
	 */
	private boolean isEdge(Integer iFrom, Node<?> to) {
		boolean ret = false;
		Integer iTo = matrixMap.get(to);
		if (iFrom != null && iTo != null && matrix[iFrom][iTo] >= 0) {
			ret = true;
		}
		return ret;
	}

	@Override
	public int getWeight(Node<?> nodeA, Node<?> nodeB) {
		int weight = -1;
		Count.up();
		Count.getweight++;
		Integer iFrom = matrixMap.get(nodeA);
		Integer iTo = matrixMap.get(nodeB);
		if (iFrom != null && iTo != null) {
			weight = matrix[iFrom][iTo];
		}
		return weight;
	}

	@Override
	public List<Node<?>> getNodes() {
		return nodes;
	}
}
