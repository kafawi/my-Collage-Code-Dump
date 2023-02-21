package graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import helper.Count;

public class ListGraph implements iGraph {
	public HashMap<Integer, Node<?>> graphList;
	public int anzNodes = 0;
	public List<Node<?>> nodes;

	public ListGraph(HashMap<Integer, Node<?>> graphList) {
		super();
		this.graphList = graphList;
		this.anzNodes = graphList.size();
		nodes = new ArrayList<>();
		
		for (Integer i: graphList.keySet()){
			nodes.add(graphList.get(i));
		}
		// }

	}

	@Override
	public void addNode(Node<?> node) {
		// graphList.add(new NodeEdgeList(node, null));
		// anzNodes++;
	}

	@Override
	public void addEdge(Edge edge) {
		// addEdge(edge.from, edge.to, edge.weight);
	}

	@Override
	public void addEdge(Node<?> from, Node<?> to, int weight) {
		Node<?> temp = null;
		int index = 0;
		// finde from
		for (int i = 0; temp != from || i < graphList.size(); i++) {
			// if (from.equals(graphList.get(i).node)) {
			// temp = graphList.get(i).node;
			index = i;
			// }
		}
		if (temp == null) {
			System.out.println("fehler addEDge");
			// throw new NodeNotFoundException();
		}
		// update oder setze list von from
		// if (graphList.get(index).neighbors.containsKey(to)) {
		// graphList.get(index).neighbors.replace(to, weight);
		// } else {
		// graphList.get(index).neighbors.put(to, weight);
		// }
		// finde to
		index = 0;
		temp = null;
		for (int i = 0; temp != to || i < graphList.size(); i++) {
			// if (to.equals(graphList.get(i).node)) {
			// temp = graphList.get(i).node;
			index = i;
			// }
		}
		if (temp == null) {
			System.out.println("fehler addEDge");
			// throw new NodeNotFoundException();
		}
		// update oder setze list von to
		// if (graphList.get(index).neighbors.containsKey(from)) {
		// graphList.get(index).neighbors.replace(from, weight);
		// } else {
		// graphList.get(index).neighbors.put(from, weight);
		// 7 }

	}

	@Override
	public void removeNode(Node<?> node) {
		int index = 0;
		// finde alle Knoten die node als nachbar haben und l�sche node aus der
		// Hashmap
		for (int i = 0; i < graphList.size(); i++) {
			// if (!graphList.get(i).node.equals(node)) {
			// ggf contains vorher?oder doppelte abfrage
			// graphList.get(i).neighbors.remove(node);
			// } else if (graphList.get(i).node.equals(node)) {
			// index = i;
			// }
		}
		graphList.remove(index);
		anzNodes--;
	}

	/*
	 * @Override public void traverse(Node<?> from, Node<?> to) { // TODO
	 * Auto-generated method stub
	 * 
	 * }
	 */

	@Override
	public List<Node<?>> getNeighbors(Node<?> node) {
		List<Node<?>> temp = new ArrayList<>();

		// finde node in graphList
		int index = 0;

		for (Edge e : graphList.get(node.id).neighbors) {
			Count.neighbor++;
			Count.up();
			temp.add(e.getTo());
		}

		return temp;
	}

	@Override
	public int getWeight(Node<?> nodeA, Node<?> nodeB) {
		// finde nodeA oder nodeB in graphList
		Node<?> temp = new Node<Object>(null);
		int index = 0;
		int weight = -1;

		for (Edge e : nodeA.neighbors) {
			 Count.up();
			 Count.getweight++;
			if (e.to.equals(nodeB)) {
				weight = e.getWeigth();
			}
		}

		// if (nodeA.equals(null) || nodeB.equals(null)) {
		// System.out.println("erere");
		// return -1;
		// }
		// for (int i = 0; i < graphList.size() && !temp.equals(nodeA); i++) {
		// temp = graphList.get(i).node;
		// index = i;
		// }

		// gucke ob sie eine gemeinsame Edge haben und hole das weight
		// if (graphList.get(index).neighbors.containsKey(nodeB)) {
		
		// weight = graphList.get(index).neighbors.get(nodeB);
		// }
		return weight;
	}

	@Override
	public List<Node<?>> getNodes() {
		return nodes;
	}

}
