package dykstra;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import graph.ListGraph;
import graph.MatrixGraph;
import graph.Node;
import helper.GraphGenerator;

public class DykstraTest {

	List<Node<?>> nodeList;
	MatrixGraph mg;
	ListGraph lg;
	Dykstra dykmg;
	Dykstra dyklg;
	Node<String> A;
	Node<String> B;
	Node<String> C;
	Node<String> D;
	Node<String> E;
	Node<String> F;
	Node<String> G;

	@Before
	public void initDyk() {
		A = new Node<String>("A");
		B = new Node<String>("B");
		C = new Node<String>("C");
		D = new Node<String>("D");
		E = new Node<String>("E");
		F = new Node<String>("F");
		G = new Node<String>("G");
		nodeList = new ArrayList<Node<?>>();
		nodeList.add(A);
		nodeList.add(B);
		nodeList.add(C);
		nodeList.add(D);
		nodeList.add(E);
		nodeList.add(F);
		nodeList.add(G);

		int[][] mtrx =
				// { A, B, C, D, E, F, G}
				{ { 0, 4, -1, -1, -1, 10, 5 }, // A
						{ 4, 0, 7, -1, -1, -1, 2 }, // B
						{ -1, 7, 0, 12, -1, -1, 1 }, // C
						{ -1, -1, 12, 0, 4, -1, -1 }, // D
						{ -1, -1, -1, 4, 0, 3, 8 }, // E
						{ 10, -1, -1, -1, 3, 0, 4 }, // F
						{ 5, 2, 1, -1, 8, 4, 0 } // G
				};
		mg = new MatrixGraph(mtrx, nodeList);
		lg = new ListGraph(GraphGenerator.genListGraph(mtrx, nodeList));

	}

	@Test
	public void testAll() {
		dykmg = new Dykstra(mg, A);

		assertEquals("A to A", 0, dykmg.getMinCost(A));
		assertEquals("B to A", 4, dykmg.getMinCost(B));
		assertEquals("C to A", 6, dykmg.getMinCost(C));
		assertEquals("D to A", 16, dykmg.getMinCost(D));
		assertEquals("E to A", 12, dykmg.getMinCost(E));
		assertEquals("F to A", 9, dykmg.getMinCost(F));
		assertEquals("G to A", 5, dykmg.getMinCost(G));

		dyklg = new Dykstra(lg, A);

		assertEquals("A to A", 0, dyklg.getMinCost(A));
		assertEquals("B to A", 4, dyklg.getMinCost(B));
		assertEquals("C to A", 6, dyklg.getMinCost(C));
		assertEquals("D to A", 16, dyklg.getMinCost(D));
		assertEquals("E to A", 12, dyklg.getMinCost(E));
		assertEquals("F to A", 9, dyklg.getMinCost(F));
		assertEquals("G to A", 5, dyklg.getMinCost(G));

	}
}
