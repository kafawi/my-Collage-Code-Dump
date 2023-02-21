package sample;

import itree.IBaum;

import java.io.FileWriter;
import java.io.IOException;

import linked.LinBaum;
//import array.ArrBaum;

public class Sample {
  
  final static private int BASE = 2;
  final static private int MAX_EXPONENT = 15; 
  final static private int RAND_LOOP_COUNT = 10;
  

  static void fillBest(int N, IBaum b) {
    int n = N / 2;
    b.einfuegen(n);
    // left
    fillBest(0, n, b);
    // right
    fillBest(n, n, b);
  }

  static void fillBest(int start, int N, IBaum b) {
    int n = N / 2;
    if (0 == n)
      return;
    b.einfuegen(start + n);
    // left
    fillBest(start, n, b);
    // reight
    fillBest(start + n, n, b);
  }

  static void fillWorst(int N, IBaum b) {
    for (int i = 1; i < N; i++) {
      b.einfuegen(i);
    }
  }

  static void fillRand(int N, IBaum b) {
    Integer n = 0;
    for (int i = 1; i < N; i++) {
      n = (int) (Math.random() * N * 10);
      b.einfuegen(n);
    }
  }

  // ---------------------------------------------------------- File gedoenst
  static private void writeSample(FileWriter file, String s) {
    try {
      file.write(s);
    } catch (IOException e) {
      e.printStackTrace();
    } finally {
    }
  }

  static private FileWriter[] openFile(String... names) {
    FileWriter[] files = new FileWriter[names.length];
    int i = 0;
    for (String name : names) {
      try {
        files[i++] = new FileWriter(name);
      } catch (IOException e) {
        e.printStackTrace();
      } finally {
      }
    }
    return files;
  }

  static private void closeFile(FileWriter... files) {
    for (FileWriter file : files) {
      if (file != null) {
        try {
          file.close();
        } catch (IOException e) {
          e.printStackTrace();
        } finally {
          file = null;
        }
      }
    }
  }
// ---------------------------------------------------------- actual samplening
  static public void main(String[] args) {
    
    FileWriter[] fc = openFile("sample.txt");
    String s = "";
    IBaum b;
    
    int[] countRand = new int[RAND_LOOP_COUNT];
    
    for (int i =0; i <= MAX_EXPONENT ;i++) {
      int N = (int) Math.pow(BASE, i);
      s = String.format("%6d", N);
      // best tree, worst search
      b = new LinBaum();
      fillBest(N, b);
      b.reset();
      b.getSumBetween(0, 10*N);
      s += String.format(";%12d", b.count());
      
      //best thre best search
      b.reset();
      b.getSumBetween(N/2, N/2);
      s += String.format(";%12d", b.count());
      
      // rand
      for (int j =0 ; j < RAND_LOOP_COUNT; j++) {
        b = new LinBaum();
        fillRand(N,b);
        b.reset();
        b.getSumBetween(0, N*10);
        countRand[j]= b.count();
        
      }
      int countSum =0;
      for (int j =0 ; j < RAND_LOOP_COUNT; j++){
        countSum += countRand[j]; 
      }
      int countMean = countSum/RAND_LOOP_COUNT;
      
      s += String.format(";%12d", countMean);
      
      // worst three left best search right worst search
      b = new LinBaum();
      fillWorst(N,b);
      b.reset();
      b.getSumBetween(0, 10*N);
      
      s += String.format(";%12d", b.count());

      // ende
      s += "\n";
      System.out.print(s);
      writeSample(fc[0], s);
    }

    closeFile(fc);
    
  }
}
