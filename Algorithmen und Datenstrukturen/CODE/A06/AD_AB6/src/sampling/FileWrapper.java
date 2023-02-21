package sampling;

import java.io.FileWriter;
import java.io.IOException;

public class FileWrapper {
	
	static FileWriter[] files;
	
	FileWrapper(){
		this("sample.txt");
	}
	
	FileWrapper(String... names){
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
	
	public void write( String s) {
		write(0,s);
	}
	
	public void write(int  fileNo, String s) {
		try {
			files[fileNo].write(s);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
		}
	}
	

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
