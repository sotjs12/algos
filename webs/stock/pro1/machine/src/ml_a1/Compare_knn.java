package ml_a1;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.Locale;

public class Compare_knn {

	public static void Run() throws FileNotFoundException, UnsupportedEncodingException {
		BufferedReader br = null;
		InputStreamReader isr = null;
		FileInputStream fis = null;
		File file = new File("Analisis/knn_result.csv");
		File file2 = new File("Data.csv");

		String temp = "";
		String Content = "";
		String Content2 = "";
		String[] array = null;
		String[] array2 = null;
		String[][] Data;
		String[][] Data2;
		String Data_compare[][];
		String Data_compare2[][];
		long Date[];
		
		
		try {
			fis = new FileInputStream(file);
			isr = new InputStreamReader(fis, "UTF-8");
			br = new BufferedReader(isr);

			while ((temp = br.readLine()) != null) {
				Content += temp + "\n";
			}
			
			fis = new FileInputStream(file2);
			isr = new InputStreamReader(fis, "UTF-8");
			br = new BufferedReader(isr);

			while ((temp = br.readLine()) != null) {
				Content2 += temp + "\n";
				
			}
			
			array = Content.split("\n");
			Data = new String[array.length][];
			Data_compare = new String[array.length][];
			
			array2 = Content2.split("\n");
			Data2 = new String[array2.length][];
			Data_compare2 = new String[array2.length][]; 
			
			
			
			/*for(int i=0; i<array.length; i++){
				Data[i] = new String[5];
			}*/
			
			for(int i=0; i<array.length; i++){
				Data[i] = new String[6];
				//array_double[i] = new double[10];
				Data_compare[i] = new String[6];
				//System.out.println(Data[i][9]);
				//System.out.println();
			}
			
			

			for(int i=0; i<array2.length; i++)
			{
				Data2[i] = new String[10];
				Data_compare2[i] = new String[10];
			}
			
			String[] array_temp2;
			array_temp2 = new String[6];
			for(int i=0; i<array.length;i++){
				
				array_temp2= array[i].split(",");
				
				for(int j=0; j<6;j++){					
					Data[i][j] = array_temp2[j];					
				}
				//System.out.println();
			}
			
			String[] array_temp3;
			array_temp3 = new String[10];
			for(int i=0; i<array2.length; i++){
				
				array_temp3 = array2[i].split(",");
				for(int j=0; j<10; j++){
					Data2[i][j] = array_temp3[j];
					
					//System.out.println(Data2[i][j]);
				}
			}
			
			for(int i=0; i<array.length-1; i++){
				Data_compare[i][0] = (Data[i+1][0]);
				Data_compare[i][1] = (Data[i+1][1]);
				Data_compare[i][2] = (Data[i+1][2]);
				Data_compare[i][3] = (Data[i+1][3]);
				Data_compare[i][4] = (Data[i+1][4]);
				Data_compare[i][5] = (Data[i+1][5]);
				//System.out.println(Data_compare[i][4]);
			}
			
			for(int i=0; i<array2.length-1; i++){
				Data_compare2[i][0] = (Data2[i+1][4]);
				Data_compare2[i][1] = (Data2[i+1][5]);
				Data_compare2[i][2] = (Data2[i+1][6]);
				Data_compare2[i][3] = (Data2[i+1][8]);
				Data_compare2[i][4] = null;
				
			}
			
			double D[];
			double D_temp[];
			D = new double[array2.length];
			D_temp = new double[array.length];
			
			for(int i=0; i<array2.length-1; i++){
				for(int j=0; j<array.length-1; j++){
					D_temp[j] = (Math.pow(Double.parseDouble(Data_compare[j][0])-Double.parseDouble(Data_compare2[i][0]), 2)
							+Math.pow(Double.parseDouble(Data_compare[j][1])-Double.parseDouble(Data_compare2[i][1]), 2)
							+Math.pow(Double.parseDouble(Data_compare[j][2])-Double.parseDouble(Data_compare2[i][2]), 2)
							+Math.pow(Double.parseDouble(Data_compare[j][3])-Double.parseDouble(Data_compare2[i][3]), 2));
				}
				Arrays.sort(D_temp);
				D[i] = D_temp[0];
				Data_compare2[i][4] = Data_compare[i][4];
				//System.out.println(D_temp[i]);
				//System.out.println();
				System.out.println(D[i]);
			}
			
			DateFormat format = new SimpleDateFormat("yyyy-MM-dd");
			Date temp_date = null;
			Date = new long[array2.length-1];
			
			for(int i=0; i<array2.length-1; i++){
				try {
					temp_date = format.parse(Data2[i+1][9]);
					temp_date.getTime();
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				Date[i] = temp_date.getTime();
				//System.out.println(Date[i]);
			}
			SimpleDateFormat formatter = new SimpleDateFormat("yyyy_MM_dd",Locale.KOREA); 
			Date today = new Date();
			String dTime = formatter.format(today);
			System.out.println(dTime);
			
	        PrintWriter pw = new PrintWriter("Analisis/knn("+dTime+").csv");
	        for(int i=0; i<array2.length-1; i++)
	        {
	        		String data = Data_compare2[i][0]+','+Data_compare2[i][1]+','+Data_compare2[i][2]+','+Data_compare2[i][3]+','+Data_compare[i][5]+','+Data_compare2[i][4]+','+Date[i];
	        		pw.println(data);
	        	
	        }
	        pw.close();
			
		} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
				
		}
}
