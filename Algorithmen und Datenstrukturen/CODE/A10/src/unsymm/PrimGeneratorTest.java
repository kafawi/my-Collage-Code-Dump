package unsymm;

import static org.junit.Assert.*;

import org.junit.Test;

public class PrimGeneratorTest {

  @Test
  public void testGetPrim() {
   for(int i =0; i<100; i++){
     assertEquals(true, isPrime(PrimGenerator.getPrim()));
   }
  }
  
  public boolean isPrime(int num) {
    if(num<=1){
      return false;
    }
    if(num==2){     
      return true;
    }
    for (int i = 2; i <= Math.sqrt(num); i ++) {  
      if (num % i == 0) {      
        return false;
      }
    }
    return true;
  }

}
