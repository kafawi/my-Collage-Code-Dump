package dykstra;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

import graph.Node;
import graph.iGraph;
import helper.Count;

/**
 * 
 * @author paul pappkammerad 
 *
 */
public class Dykstra {
	private Node<?> goal;
	private HashMap<Node<?>, DNode> map;
	private ArrayList<DNode> rand;
	private iGraph graph;

	
	/**
	 * Knostruktor and Algorithm
	 * @param graph
	 * @param goal
	 */
	public Dykstra(iGraph graph, Node<?> goal) {
		Count.reset();
		this.graph = graph;
		this.goal = goal;
		this.map = new HashMap<Node<?>, DNode>();
		this.rand = new ArrayList<DNode>();
		init();
		while (!rand.isEmpty()) {
			DNode v = getMinCostNode(rand);
			rand.remove(v);
			v.mark();
			updateRand(v);
		}
	}

	/**
	 * init the goal and rand and map
	 */
	private void init() {
		List<Node<?>> nodes = graph.getNodes();
		for (Node<?> node : nodes) {
			map.put(node, new DNode(node));
		}
		DNode dGoal = map.get(goal);
		dGoal.cost = 0;
		dGoal.marked = true;
		dGoal.pred = dGoal;
		// init rand
		updateRand(map.get(goal));
	}

	/**
	 * Update the rand on the base of node v
	 * also update the cost
	 * @param v
	 *   base, from where the new neigbours come from and 
	 */
	private void updateRand(DNode v) {
		List<Node<?>> neighbors = graph.getNeighbors(v.node);
		DNode k = null;
		for (Node<?> n : neighbors) {
			k = map.get(n);
			if (!k.marked){
				if (!rand.contains(k)){
				    rand.add(k);
				}
				updateCost(k, v);
			}
		}
	}

	/**
	 * setzt die Kosten eines Knotens um ihn zu erreichen
	 * 
	 * @param node
	 *            knoten der neue kosten bekommen soll
	 */
	private void updateCost(DNode nodeK, DNode nodeV) {
		int cost = nodeV.cost + graph.getWeight(nodeK.node, nodeV.node);
		if (nodeK.cost > cost || nodeK.cost > 0) {
			nodeK.cost = cost;
			nodeK.pred = nodeV;
		}

	}

	/**
	 * Gibt den Knoten mit minimalen Kosten aus einer Liste von Knoten zur�ck
	 * 
	 * @param list
	 *            Liste mit zu unterscheidenden Knoten
	 * @return Knoten mit geringstem Abstand
	 */
	private DNode getMinCostNode(List<DNode> list) {
		Collections.sort(list);
		return list.get(0);
	}

	/**
	 * F�gt alle Knoten in eine Liste ein vom Start bis zum Ziel
	 * 
	 * @param start
	 *            startKnoten
	 * @param goal
	 *            ziel Knoten
	 * @return Liste aller Knoten vom Start zum Ziel
	 */
	public List<DNode> getShortestPath(DNode start, DNode goal) {
		List<DNode> tempList = new ArrayList<>();
		DNode temp = goal;

		while (temp != start) {
			tempList.add(temp);
			temp = temp.pred;
		}
		Collections.reverse(tempList);
		return tempList;
	}

	/**
	 * Retruns the shortest (cheapest) way from start to goal
	 * 
	 * @param start
	 * @return lowes Cost.
	 */
	public int getMinCost( Node<?> start) {
		return map.get(start).cost;
	}

	public List<DNode> getShortestPathDNode(iGraph graph, Node<?> goal, Node<?> start) {
		if (!(this.goal.equals(goal))) {
			// do the dykstra
		}
		ArrayList<DNode> shortestPath = new ArrayList<DNode>();
		return shortestPath;
	}

	/** 
	 * 
	 */
	public List<Node<?>> getShortestPathNode(iGraph graph, Node<?> goal, Node<?> start) {
		if (!(this.goal.equals(goal))) {
			// do the dykstra
		}
		ArrayList<Node<?>> shortestPath = new ArrayList<Node<?>>();
		return shortestPath;
	}

}
