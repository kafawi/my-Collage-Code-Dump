package code;

import java.io.FileWriter;
import java.io.IOException;

public class Sampling {

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

  static public void main(String[] args) {

    int N_BASE = 2;
    int N_MAX_POWER = 5;
    int n = 0;

    String s = "";
    long startTime = 0;
    long time = 0;

    APascal[] pascals = { 
    		new RecursivePascal(),
    		new IterativePascal()
    ,new FastPascal()
    };

    FileWriter files[] = openFile("sample.txt");

    // for (int i = 0; i <= (int) Math.pow(N_BASE, N_MAX_POWER); i++) {
    // n = (int) Math.pow(N_BASE, i);
    for (n = 0; n <= (int) Math.pow(N_BASE, N_MAX_POWER); n++) {

      s += String.format("%6d", n);

      for (APascal pascal : pascals) {
        startTime = System.currentTimeMillis();
        pascal.calcNRow(n);
        time = System.currentTimeMillis() - startTime;
        System.out.format("%20s - N: %6d - Time: %d\n", pascal.getClass()
            .getName(), n, time);

        s += String.format(";%12d", APascal.globalCount);
        APascal.globalCount = 0;

      }
      s += "\n";
    }
    writeSample(files[0], s);

    closeFile(files);
  }

}
