package helper;

import java.io.FileWriter;
import java.io.IOException;
/**
 * A file class for simpler O in I/O
 */
public class FileWrapper {

	private FileWriter[] files;

	FileWrapper() {
		this("sample.txt");
	}

	/**
	 * Open some files to write into
	 * 
	 * @param names
	 */
	public FileWrapper(String... names) {
		files = new FileWriter[names.length];
		int i = 0;
		for (String name : names) {
			try {
				files[i++] = new FileWriter(name);
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
			}
		}
	}

	/**
	 * default write into the first file
	 * 
	 * @param s
	 */
	public void write(String s) {
		write(0, s);
	}

	/**
	 * write methode
	 * 
	 * @param fileNo
	 * @param s
	 */
	public void write(int fileNo, String s) {
		try {
			files[fileNo].write(s);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
		}
	}

	/**
	 * close the file (Destructor alternative)
	 */
	public void close() {
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
}
