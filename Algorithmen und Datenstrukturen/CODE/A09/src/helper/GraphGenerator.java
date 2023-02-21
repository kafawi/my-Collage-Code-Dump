package helper;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Random;

import graph.Edge;
import graph.Node;
import graph.NodeEdgeList;

public class GraphGenerator {
	
	/**
	 * 
	 */
	
	/**
     * Generate a Matrix for an non Directional Graph. 
     * ggf durch -1 o� zu ersetzen, abh davon ob wir negative Gewichte zu lassen
     * @param Size anzahl der Knoten im Graph
     * @return Matrixdarstellung des Graphen
     */
    public static int[][] genNonDirectionMatrix(int Size){
      int nEdges = 2;
      int edgeCount = 0;
      int[][] tempMatrix = new int[Size][Size];
      Random random = new Random();
      int tmp;
      for(int   i=0; i < Size ;i++){
        for(int j=i; j < Size ;j++){
        		  tempMatrix[i][j] = -1;
        		  tempMatrix[j][i] = -1;
          }
        } 
      for(int i=1; i < Size- nEdges  ; i++){
    	  edgeCount=0;
    	  for(int j=i; j < Size ;j++){
    		  tmp = random.nextInt(100);
        	  if (tmp < 50 && edgeCount != nEdges){
              edgeCount++;
    		  tempMatrix[i][j] = random.nextInt(10)+1;
    		  tempMatrix[j][i] = tempMatrix[i][j];
        	  }
    	  }
      }
      
      for (int i =0 ; i < Size ; i++)
    	  tempMatrix[i][i] = 0;
      return tempMatrix;
    }
    
    /**
     * Generates a ListGraph with the Matrixrepresentation and a list of all Nodes of a Graph
     * @param matrix Matrix representation of a Graph
     * @param nodes List of all Nodes in a Graph
     * @return listGraph representation of a Graph
     */
    public static HashMap<Integer,Node<?>> genListGraph(int[][] matrix, List<Node<?>> nodes){
      HashMap<Integer,Node<?>> list = new HashMap<>();
      for(int i =0; i<matrix.length; i++){
        Node<?> temp = nodes.get(i);
        
        for(int j =0; j<matrix.length; j++){
          if(i!=j && matrix[i][j]>0){
              temp.addEdge(new Edge(temp, nodes.get(j),matrix[i][j]));
          }
        }
        list.put(temp.id,temp);
      }
      
      
      return list;
    }
      
      
 
}
