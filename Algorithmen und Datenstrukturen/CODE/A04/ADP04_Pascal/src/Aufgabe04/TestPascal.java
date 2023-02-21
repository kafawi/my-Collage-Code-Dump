package code;

import org.junit.Assert;
import org.junit.Test;

public class TestPascal {
  
  APascal pascal = 
   // new RecursivePascal();
   // new IterativePascal();
    new FastPascal();
  
  //expectedes Arrays
  int[] N0  =                 { 1};
  int[] N1  =               { 1, 1};
  int[] N2  =             { 1, 2, 1};
  int[] N3  =           { 1, 3, 3, 1};
  int[] N4  =         { 1, 4, 6, 4, 1};
  int[] N5  =       { 1, 5,10,10, 5, 1};
  int[] N6  =     { 1, 6,15,20,15, 6, 1};
  int[] N7  =   { 1, 7,21,35,35,21, 7, 1};
  int[] N8  = { 1, 8,28,56,70,56,28, 8, 1};
  
  /*
  static int[][] N ={
      { 1},
     { 1, 1},
    { 1, 2, 1},        
   { 1, 3, 3, 1},         
   { 1, 4, 6, 4, 1},      
   { 1, 5,10,10, 5, 1},
   { 1, 6,15,20,15, 6, 1},
   { 1, 7,21,35,35,21, 7, 1},
   { 1, 8,28,56,70,56,28, 8, 1}
   };
  */
  
  @Test
  public void CalcNRowTest(){
    
    Assert.assertArrayEquals(N0, pascal.calcNRow(0));
    Assert.assertArrayEquals(N1, pascal.calcNRow(1));
    Assert.assertArrayEquals(N2, pascal.calcNRow(2));
    Assert.assertArrayEquals(N3, pascal.calcNRow(3));
    Assert.assertArrayEquals(N4, pascal.calcNRow(4));
    Assert.assertArrayEquals(N5, pascal.calcNRow(5));
    Assert.assertArrayEquals(N6, pascal.calcNRow(6));
    Assert.assertArrayEquals(N7, pascal.calcNRow(7));
    Assert.assertArrayEquals(N8, pascal.calcNRow(8));
    
  }

}
