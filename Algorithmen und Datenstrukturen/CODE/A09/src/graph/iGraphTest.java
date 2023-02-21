package graph;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import helper.GraphGenerator;

public class iGraphTest {
  /**
   * fields for functionality tests
   */
  MatrixGraph matrixGraph;
  ListGraph listGraph;
  List<Node<?>> nodes;
  /**
   * Fields for Dykstra tests
   */
  MatrixGraph dykMatGra;
  ListGraph dykLiGra;
  List<Node<?>> dykNoList;
  
  @Before
  public void initDyk(){
    
    
    
    /*  TEST GRAPH FOR DYKSTRA
     *    0_             _4
     *      \1        3/  |
     *       \___   __/   |
     *            1       |5
     *          /  \      |
     *      _2_-    \ 4   |
     *     /          \__ |
     *    2               3
     * 
     */
    
    int[][] dykmat = {{0, 1, -1, -1, -1},
                      {1, 0, 2, 4, 3},
                      {-1, 2, 0, -1, -1},
                      {-1, 4, -1, 0, 5},
                      {-1, 3, -1, 5, 0}};
    dykNoList = new ArrayList<>();
    for(int i=0; i<5; i++){
      dykNoList.add(new Node<Integer>(i));
    }
    dykMatGra = new MatrixGraph(dykmat, dykNoList);
 //   dykLiGra = new ListGraph(GraphGenerator.genListGraph(dykmat, dykNoList));
  }
  /**
   * tests if get Neigbhors works
   */
  @Test
  public void testGetNeighborsDyk(){
    List <Node<?>> dykTempM = new ArrayList<>();
    List <Node<?>> dykTempL = new ArrayList<>();
    dykTempM = dykMatGra.getNeighbors(dykNoList.get(1));
    dykTempL = dykLiGra.getNeighbors(dykNoList.get(1));
    boolean isSame = true;
    for(int i =0; i<dykTempM.size();i++){
      if(dykTempL.get(i).equals(dykTempM.get(i))){
        //System.out.println(dykTempM.get(i));
        //System.out.println(dykTempL.get(i));
      }else{
        isSame= false;
      }
    }
   
    assertTrue(isSame);
  }
  /**
   * Tests if get Nodes works
   */
  @Test
  public void testGetNodesDyk(){
    List <Node<?>> dykTempM = new ArrayList<>();
    List <Node<?>> dykTempL = new ArrayList<>();
    dykTempM = dykMatGra.getNodes();
    dykTempL = dykLiGra.getNodes(); 
    boolean isSame = true;
    for(int i =0; i<dykTempM.size();i++){
      if(dykTempL.get(i).equals(dykTempM.get(i))){
        //System.out.println(dykTempM.get(i));
        //System.out.println(dykTempL.get(i));
      }else{
        isSame= false;
      }
    }
   
    assertTrue(isSame);
  }
  
  
  /**
   * Initialises the default test data
   */
  @Before
  public void init(){
    nodes = new ArrayList<>();
    for(int i =0; i<10; i++){
      nodes.add(new Node<Integer>(i));
    }
    int[][] matrix = GraphGenerator.genNonDirectionMatrix(10);
   
    matrixGraph = new MatrixGraph(matrix, nodes);
    
    listGraph = new ListGraph(GraphGenerator.genListGraph(matrix, nodes));
    
  }

  /**
   * tests if addNode works
   */
  @Test
  public void testAddNode() {
    Node<Integer> node = new Node<Integer>(100);
    listGraph.addNode(node);
    matrixGraph.addNode(node);
    assertEquals(11, listGraph.anzNodes);
    assertEquals(11, matrixGraph.anzNodes);
    
  }

  /**
   * tests if add Edge is possible
   */
  @Test
  public void testAddEdgeEdge() {
    Edge edge = new Edge(nodes.get(0), nodes.get(2), 999);
    listGraph.addEdge(edge);
    matrixGraph.addEdge(edge);
    assertEquals(999, matrixGraph.matrix[0][2]);
 //   assertEquals(999,(int) listGraph.graphList.get(0).neighbors.get(nodes.get(2)));
 //   assertEquals(999,(int) listGraph.graphList.get(2).neighbors.get(nodes.get(0)));
  }

  @Test
  public void testAddEdgeNodeOfQNodeOfQInt() {
    testAddEdgeEdge();
  }

  /**
   * tetst the remove node method
   */
  @Test
  public void testRemoveNode() {
    Node<?> node = nodes.get(0);
    nodes.remove(0);
    int oldSize = listGraph.anzNodes;
    listGraph.removeNode(node);
    matrixGraph.removeNode(node);
    boolean sizeIsSame=(listGraph.anzNodes==matrixGraph.anzNodes);
    assertTrue(sizeIsSame); 
    sizeIsSame = (listGraph.anzNodes+1)==oldSize;
    assertTrue(sizeIsSame); 
    
  }

  /**
   * tests if a weight can be extracted
   */
  @Test
  public void testGetWeight() {

    int mweight = matrixGraph.getWeight(nodes.get(0), nodes.get(1));
    System.out.println(mweight);
    int lweight = listGraph.getWeight(nodes.get(0), nodes.get(1));
    System.out.println(lweight);
    assertTrue(0==lweight-mweight);
  }
/**
 * test get Nodes in default
 */
  @Test
  public void testGetNodes() {
    boolean lGraphList = true;
    boolean mGraphList = true;
    List<Node<?>> tempList = listGraph.getNodes();
    for(int i=0; i<tempList.size();i++){
      if(!tempList.get(i).equals(nodes.get(i))){
        lGraphList= false;
      }
    }
    tempList = matrixGraph.getNodes();
    for(int i=0; i<tempList.size();i++){
      if(!tempList.get(i).equals(nodes.get(i))){
        mGraphList= false;
      }
    }
    assertTrue(lGraphList&&mGraphList);
  }

  /**
   * tests getNeighbors in Default
   */
  @Test
  public void testGetNeighborsNodeOfQ() {
    List<Node<?>> tempL =listGraph.getNeighbors(nodes.get(0));
    List<Node<?>> tempM =matrixGraph.getNeighbors(nodes.get(0));
    boolean gotSomeNeighbors = true;
    if(tempL.size()!=tempM.size()){
      gotSomeNeighbors = false;
      System.out.println(tempL.size());
      System.out.println(tempM.size());
      
    }
    for(int i=0; gotSomeNeighbors && i<tempL.size() && i<tempM.size();i++){
      if(!tempL.get(i).equals(tempM.get(i))){
        gotSomeNeighbors = false;
      }
    }
    assertTrue(gotSomeNeighbors);
    
  }

}
