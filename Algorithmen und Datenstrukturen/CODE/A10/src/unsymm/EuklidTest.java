package unsymm;

import static org.junit.Assert.*;

import org.junit.Test;

public class EuklidTest {

  @Test
  public void test() {
   assertEquals(6, Euklid.ggt(66, 6)); 
   assertEquals(1, Euklid.ggt(0, 1));
   assertEquals(1, Euklid.ggt(1, 0));
   assertEquals(0, Euklid.ggt(0, 0));
   assertEquals(11, Euklid.ggt(33, 11));
   assertEquals(11, Euklid.ggt(11, 33));
   assertEquals(3, Euklid.ggt(99, 6));
   
  }

}
