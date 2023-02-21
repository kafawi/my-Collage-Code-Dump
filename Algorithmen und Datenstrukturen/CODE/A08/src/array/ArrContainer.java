package array;

public class ArrContainer {

  private ArrKnoten[] array;

  private int         contain = 0;

  public ArrContainer(int len) {
    array = new ArrKnoten[len];
  }

  public void set(int index, Integer obj) throws IndexOutOfBoundsException {
    if (index < 0) {
      throw new IndexOutOfBoundsException();
    }
    if (index >= array.length) {
      ArrKnoten[] tmp = new ArrKnoten[index * 2];
      System.arraycopy(array, 0, tmp, 0, array.length);
      array = tmp;
      System.gc();
    }
    array[index] = new ArrKnoten(obj);
    contain++;
  }

  public ArrKnoten get(int index) {
    ArrKnoten res = null;
    if (index >= array.length || index < 0) {
      res = null;
    } else {
      res = array[index];
    }
    return res;
  }

  public int size() {
    return array.length;
  }

  public int nContain() {
    return contain;
  }

}
