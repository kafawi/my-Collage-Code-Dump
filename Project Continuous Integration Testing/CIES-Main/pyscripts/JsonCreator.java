import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.Queue;
import java.util.Scanner;
import java.util.LinkedList;
import java.util.HashMap;


/**
 * Converts Clang analysis script output to Mongo-DB compatible JSON suitable
 * to create Tables organized by source name.
 * To be deployed in same directory as analysis-script .
 * 
 * @author Lennart Hartmann
 * @version 8.1.2018
 */
public class JsonCreator {
	//access indexes for split message
	public static final int PATH_IDX = 0;
	public static final int LINE_IDX = 1;
	public static final int ROW_IDX = 2;
	public static final int MSG_TYPE_IDX = 3;
	public static final int MSG_START_IDX = 4;
	public static final int MIN_ARGS_NUMBER = 5;
	
	public static final String DEFAULT_SOURCE_PATH = "report.txt";
	public static final String OUTPUT_FILENAME = "report.json";
	
	public static final String SEPARATOR = ":";
	public static final String CLOSING_BRACKET = "}";
	public static final String UP_ARROW = "^";
	public static final String CLANG_IDENTIFIER = "clang";
	//public static final String SOURCE_IDENTIFIER = "./";
	public static final String BLANK = " ";
	public static final String STATS = "statistics";
	public static final String TABS5 = "\n\t\t\t\t\t";
	public static final String TABS4 = "\n\t\t\t\t";
	public static final String TABS3 = "\n\t\t\t";
	public static final String TABS2 = "\n\t\t";
	public static final String TABS1 = "\n\t";
	
	private static int errid=0;
	private static int numberOfLines=-1;
	private static int numberOfErrors = 0;
	private static int numberOfWarnings = 0;

	private static String sourceIdentifier = "./";
	private static int sourceIdentifierLen = 3;
	
	/**
	 * provides JSON suitable to create table in Mongo-DB
	 */
	public static void read(){
		read(DEFAULT_SOURCE_PATH);
	}
	
	/**
	 * provides JSON suitable to create table in Mongo-DB
	 */
	public static void read(String path){
		//for debug purposes
//		int clangCount = 0;
//		int sourceCount = 0;
//		int statsCount = 0;
//		int blankcount = 0;
		
		//Original lines for parsing
		Queue<String> srcLines = new LinkedList<>();
		 
		//Stats
		Queue<String> statsList = new LinkedList<>();
		//Clang messages
		Queue<String> clangMsgsList = new LinkedList<>();
		//maps messages to filename
		HashMap<String,LinkedList<String>> fileMap = new HashMap<String, LinkedList<String>>(); 

		//get lines from file
		try{
			Scanner s = new Scanner(new File(path));
			while(s.hasNext()) srcLines.add(s.nextLine());
			s.close();
			
			String prevKey = STATS;
			String key = null;
			int subStringIndex = 0;

			//organize files according to source
			for(Object obj:srcLines){
				String line = (String)obj;
				
				if(line.startsWith(BLANK)||line.startsWith(CLOSING_BRACKET)||line.startsWith(UP_ARROW)){
//					blankcount++;
					try{
						//appendMessage(fileMap.get(prevKey).getLast(),line);
						appendMessage(fileMap,prevKey,line);
					}catch(NullPointerException e){
						//if entry does not exist yet: create
						LinkedList<String> list = new LinkedList<>();
						list.add(line);
						fileMap.put(prevKey, list);
					}
				}else{
					if(line.startsWith(CLANG_IDENTIFIER)){
//						clangCount++;
						clangMsgsList.add(line);
						key=CLANG_IDENTIFIER;
					}else if(line.contains(sourceIdentifier)){
//						sourceCount++;
						subStringIndex = line.indexOf(sourceIdentifier);
						key = line.split(SEPARATOR)[PATH_IDX].substring(subStringIndex + sourceIdentifierLen).trim();
						if(!fileMap.containsKey(key)) fileMap.put(key,new LinkedList<String>());
						fileMap.get(key).add(line.substring(subStringIndex + sourceIdentifierLen));
						prevKey=key;
					}else{
//						statsCount++;
						statsList.add(line);
						key = STATS;
					}
				}
			}
		}catch(Exception e){
			e.printStackTrace();
		}
		
//		System.out.printf("lines read: %d\n", srcLines.size());
//		System.out.printf("sources found (list): %d\n", fileMap.keySet().size());
//		System.out.printf("clang: %d\nsources: %d\nblanks: %d\nstats: %d\n", clangCount, sourceCount,blankcount,statsCount);
//		System.out.println("=============Source-List==============");
//		for (String str : fileMap.keySet()) {
//			System.out.println(str);
//		}
		
		System.out.println("=============Clang-Reports==============");
		for(String str: clangMsgsList) {
			System.out.println(str);
		}

		int numberOfSources = fileMap.keySet().size();
		System.out.println("=============Stats-Reports==============");
		for(String str: statsList) {
			System.out.println(str);
			if (str.contains("warning")) {
				numberOfWarnings += Character.getNumericValue(str.charAt(0));
			}else if(str.contains("error")) {
				numberOfErrors += Character.getNumericValue(str.charAt(0));
			}
		}
		
		
		
		System.out.printf("Total number of lines: %d\nTotal number of errors: %d\nTotal number of warnings: %d\n",numberOfLines,numberOfErrors,numberOfWarnings);
		
		System.out.println("================Map-Test================");
		for(String key: fileMap.keySet()) {
			for(String line: fileMap.get(key)) {
				System.out.println(line);
			}
		}
		
		//create json file
		System.out.println(createJson("json report",fileMap));
	}
	
	/**
	 * Creates file-substring containing all messages in JSON format
	 * @param filename	the file to be procressed
	 * @param list	the list containing descriptions
	 * @return	the substring created
	 */
	private static String getProcessFile(String filename, LinkedList<String> list) {
		int lastIdx = list.size();
		int idx=1;
		String fileString = "{"+TABS3+"\"file_name\":\""+filename+"\","+TABS3+"\"err_ids\":[{";
		for(String line : list) {
			String[] substrings = line.split(SEPARATOR);
			if(substrings.length >= MIN_ARGS_NUMBER) {
				String description="";
				for(int i = MSG_START_IDX; i<substrings.length; i++) {
					description+=substrings[i];
				}
				fileString+=(TABS5+"\"errid\":\""+ (errid++) +"\","+TABS5+"\"line\":\""+substrings[LINE_IDX]+"\","+TABS5+"\"row\":\""
				+substrings[ROW_IDX]+"\","+TABS5+"\"decription\":\""+description.trim()+"\","+TABS5+"\"type\":\""+substrings[MSG_TYPE_IDX].trim()+"\""
				+TABS4+"}");
				if(idx<lastIdx)fileString+=(","+TABS4+"{");
				idx++;
			}//throw exception?
		}
		return fileString+TABS3+"]"+TABS2+"}";
	}
	
	/**
	 * creates report json for table creation
	 * @param filename	the filename
	 * @param reportMap	maps reports to sourcename
	 * @return	static analysis report in json format	
	 */
	private static String createJson(String filename, HashMap<String,LinkedList<String>> reportMap) {
		Queue<String> fileList = new LinkedList<>();
		for(String sourceName: reportMap.keySet()) {
			fileList.add(getProcessFile(sourceName, reportMap.get(sourceName)));
		}
		int lastIdx = fileList.size();
		int idx=0;
		String jsonString = "{"+TABS1+"\"files\":[";
		for(String source: fileList) {
			jsonString+=source;
			if(idx < lastIdx-1) {
				jsonString+=",";
				jsonString+=TABS2;
			}
			idx++;
		}
		jsonString+=(TABS1+"],"+TABS1+"\"stats\":{"+
				TABS2+"\"numberOfLines\":\""+numberOfLines+"\","+
				TABS2+"\"numberOfErrors\":\""+numberOfErrors+"\","+
				TABS2+"\"numberOfWarnings\":\""+numberOfWarnings+"\""+
				TABS1+"}");
		
		jsonString+="\n}";
		
		Writer writer = null;
		try {
			System.out.println("writing to file");
			writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(OUTPUT_FILENAME), "utf-8"));
		    writer.write(jsonString);
		    System.out.println("success");
		} catch (IOException ex) {
		  System.out.println("Error while writing to file");
		}finally {
			try {
			   writer.close();
			}catch (Exception ex) {/*ignore*/}
		}
		return jsonString;
	}
	
	/**
	 * Concatenates analyzer output lines
	 * @param sourceMap	map holding all messages for given source
	 * @param curKey 	current source key
	 * @param addition	additional line
	 */
	private static void appendMessage(HashMap<String, LinkedList<String>> sourceMap, String curKey, String addition){
		String msg = sourceMap.get(curKey).removeLast() +" ;;; " + addition.trim(); //;;; signifies new line
		sourceMap.get(curKey).add(msg);
	}
	
	public static void main(String[]args) throws IOException{
		if(args.length==1) {
			numberOfLines=Integer.parseInt(args[0]);
		}else if(args.length==2){
			numberOfLines=Integer.parseInt(args[0]);
			sourceIdentifier =args[1];
			sourceIdentifierLen = sourceIdentifier.length();
			if (!sourceIdentifier.endsWith("/")) {
                sourceIdentifierLen++;
            }
		}
		JsonCreator.read();
	}
}
