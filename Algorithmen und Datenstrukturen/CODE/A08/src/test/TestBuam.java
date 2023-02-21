package test;

import static org.junit.Assert.*;
import itree.IBaum;

import java.util.List;

import linked.LinBaum;

import org.junit.Test;

import array.ArrBaum;

public class TestBuam {

//1
//    2
//     3
//      4
//       5
//        6
  @Test
  public void testAEinfuegen() {
    IBaum abaum = new ArrBaum();
    System.out.println("  Arrbaum:");
    abaum.einfuegen(1);
    abaum.einfuegen(2);
    abaum.einfuegen(3);
    abaum.einfuegen(4);
    abaum.einfuegen(5);
    abaum.einfuegen(6);
    List<Integer> inO = abaum.inOrder();
    assertEquals(inO.get(0), (Integer) 1);
    List<Integer> preO = abaum.preOrder();
    assertEquals(preO.get(0), (Integer) 1);
    List<Integer> postO = abaum.postOrder();
    assertEquals(postO.get(0), (Integer) 6);
  }
  
  @Test
  public void testAInOrder() {
    IBaum baum = new ArrBaum();
    System.out.print("  Arraybaum:");
    baum.einfuegen(4);    
      baum.einfuegen(2);
        baum.einfuegen(1);
        baum.einfuegen(3);  
      baum.einfuegen(6);
        baum.einfuegen(5);
        baum.einfuegen(7);
    List<Integer> inO = baum.inOrder();
    assertEquals(inO.get(0),(Integer) 1);
    assertEquals(inO.get(1),(Integer) 2);
    assertEquals(inO.get(2),(Integer) 3);
    assertEquals(inO.get(3),(Integer) 4);
    assertEquals(inO.get(4),(Integer) 5);
    assertEquals(inO.get(5),(Integer) 6);
    assertEquals(inO.get(6),(Integer) 7);
  }
  
  
  //       10
  //   6       16      
  // 2   7   12  17
  //  4
  @Test
  public void testASumBetween() {
    IBaum baum = new ArrBaum();
    baum.einfuegen(10);    
      baum.einfuegen(6);
        baum.einfuegen(2);
          baum.einfuegen(4);
        baum.einfuegen(7);  
      baum.einfuegen(16);
        baum.einfuegen(12);
        baum.einfuegen(17);
    Integer sum =0;
    sum = baum.getSumBetween(0, 10);
    assertEquals(sum,(Integer) (2+4+6+7+10));
    sum = baum.getSumBetween(3, 10);
    assertEquals(sum,(Integer) (4+6+7+10));
    sum = baum.getSumBetween(9, 12);
    assertEquals(sum,(Integer) (10+12));
    sum = baum.getSumBetween(9, 20);
    assertEquals(sum,(Integer) (10+16+12+17));
  }

  
  @Test
  public void testLEinfuegen() {
    IBaum baum = new LinBaum();
    System.out.println("  Arrbaum:");
    baum.einfuegen(1);
    baum.einfuegen(2);
    baum.einfuegen(3);
    baum.einfuegen(4);
    baum.einfuegen(5);
    baum.einfuegen(6);
    List<Integer> inO = baum.inOrder();
    assertEquals(inO.get(0), (Integer) 1);
    List<Integer> preO = baum.preOrder();
    assertEquals(preO.get(0), (Integer) 1);
    List<Integer> postO = baum.postOrder();
    assertEquals(postO.get(0), (Integer) 6);
  }
  
  @Test
  public void testLInOrder() {
    IBaum baum = new LinBaum();
    System.out.print("  Arraybaum:");
    baum.einfuegen(4);    
      baum.einfuegen(2);
        baum.einfuegen(1);
        baum.einfuegen(3);  
      baum.einfuegen(6);
        baum.einfuegen(5);
        baum.einfuegen(7);
    List<Integer> inO = baum.inOrder();
    assertEquals(inO.get(0),(Integer) 1);
    assertEquals(inO.get(1),(Integer) 2);
    assertEquals(inO.get(2),(Integer) 3);
    assertEquals(inO.get(3),(Integer) 4);
    assertEquals(inO.get(4),(Integer) 5);
    assertEquals(inO.get(5),(Integer) 6);
    assertEquals(inO.get(6),(Integer) 7);
  }
  
  
  //       10
  //   6       16      
  // 2   7   12  17
  //  4
  @Test
  public void testLSumBetween() {
    IBaum baum = new LinBaum();
    baum.einfuegen(10);    
      baum.einfuegen(6);
        baum.einfuegen(2);
          baum.einfuegen(4);
        baum.einfuegen(7);  
      baum.einfuegen(16);
        baum.einfuegen(12);
        baum.einfuegen(17);
    Integer sum =0;
    sum = baum.getSumBetween(0, 10);
    assertEquals(sum,(Integer) (2+4+6+7+10));
    sum = baum.getSumBetween(3, 10);
    assertEquals(sum,(Integer) (4+6+7+10));
    sum = baum.getSumBetween(9, 12);
    assertEquals(sum,(Integer) (10+12));
    sum = baum.getSumBetween(9, 20);
    assertEquals(sum,(Integer) (10+16+12+17));
  }
  
  
}
