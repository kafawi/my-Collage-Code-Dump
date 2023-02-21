package sample;

import java.util.List;

import dykstra.Dykstra;
import graph.ListGraph;
import graph.MatrixGraph;
import graph.Node;
import helper.Count;
import helper.FileWrapper;
import helper.GraphGenerator;

/**
 * A simple Sample class with main
 * 
 * @author kafa
 *
 */
public class Sample {

	public final static int MAX = 4;
	public final static int BASE = 10;
	public final static int TIMES = 3;

	public static List<Node<?>> nodeList;
	public static MatrixGraph mg;
	public static ListGraph lg;
	public static Dykstra dykmg;
	public static Dykstra dyklg;
	
	static long mgNeighborSum=0;
	static long mgWeightSum=0;
	static long mgCountSum=0;
	
	static long lgNeighborSum=0;
	static long lgWeightSum=0;
	static long lgCountSum=0;

	public static void main(String... args) {

		FileWrapper f = new FileWrapper(
				"neighbor.txt", "getweight.txt", "total.txt" 
				);
		int[][] mtrx;

		for (int i = 1; i < MAX + 1; i++) {	
			
			mgNeighborSum = 0;mgWeightSum =0;mgCountSum=0;
			lgNeighborSum = 0;lgWeightSum =0;lgCountSum=0;
			int N = (int) Math.pow(BASE, i);
			System.out.println("Starting Sampling with "+ N );
			f.write(0, ""+N);
			f.write(1, ""+N);
			f.write(2, ""+N);
			
            mtrx = GraphGenerator.genNonDirectionMatrix(N);
            
            mg = new MatrixGraph(mtrx, null);
            nodeList = mg.getNodes();
    		lg = new ListGraph(GraphGenerator.genListGraph(mtrx, nodeList));
            
    		
    		for (int j =0; j < TIMES; j++){
    			Count.count=0;Count.getweight=0;Count.neighbor=0;
    			dykmg = new Dykstra(mg,nodeList.get(j));
    			mgWeightSum += Count.getweight;
    			mgNeighborSum += Count.neighbor;
    			mgCountSum += Count.count;
    			System.out.println("matrix end");
    			Count.count=0;Count.getweight=0;Count.neighbor=0;
    			dykmg =null;
    			System.gc();
    			dyklg = new Dykstra(lg,nodeList.get(j));
    			lgWeightSum += Count.getweight;
    			lgNeighborSum += Count.neighbor;
    			lgCountSum += Count.count;
    			System.out.println("list end");
    			dyklg=null;
    			System.gc();
    		}
    		f.write(0,";"+mgNeighborSum/TIMES);
    		f.write(0,";"+lgNeighborSum/TIMES);
    		f.write(1,";"+mgWeightSum/TIMES);
    		f.write(1,";"+lgWeightSum/TIMES);
    		f.write(2,";"+mgCountSum/TIMES);
    		f.write(2,";"+lgCountSum/TIMES);
    		
    		f.write(0,"\n");
    		f.write(1,"\n");
    		f.write(2,"\n");
    		
		}
        f.close();
	}

}
