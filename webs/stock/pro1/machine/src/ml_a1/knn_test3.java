package ml_a1;

import java.io.*;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;


public class knn_test3 {
	//@SuppressWarnings("null")
	public void Run() throws FileNotFoundException, UnsupportedEncodingException {
		BufferedReader br = null;
		InputStreamReader isr = null;
		FileInputStream fis = null;
		File file = new File("test.csv");

		String temp = "";
		String Content = "";
		int k = 20;
		String[] array;
		String[][] Data;
		double array_double[][];
		String Data_compare[][];
		long Date[];
		

		try {
			fis = new FileInputStream(file);
			isr = new InputStreamReader(fis, "UTF-8");
			br = new BufferedReader(isr);

			while ((temp = br.readLine()) != null) {
				Content += temp + "\n";
			}
			
			/*Scanner scan = new Scanner(System.in);
			System.out.print("k =");
			k = scan.nextInt();*/
			
			array = Content.split("\n");
			
			Data = new String[array.length][];
			array_double = new double[array.length][];
			Data_compare = new String[array.length][];
			Date = new long[array.length];
			
			for(int i=0; i<array.length; i++){
				Data[i] = new String[10];
				//array_double[i] = new double[10];
				//Data_compare[i] = new String[4];
				//System.out.println(Data[i][9]);
				//System.out.println();
			}
			
			for(int i=0; i<array.length-1; i++){
				Data[i] = new String[10];
				//array_double[i] = new double[10];
				Data_compare[i] = new String[6];
				//System.out.println(Data[i][9]);
				//System.out.println();
			}
			
			String[] array_temp2 = null;
			for(int i=0; i<array.length;i++){
				array_temp2= array[i].split(",");
				for(int j=0; j<10;j++){
					//System.out.println(array_temp2[j]);
					Data[i][j] = array_temp2[j];
					//System.out.println(Data[i][j]);
					//System.out.println();
				}
				//System.out.println();
			}
			DateFormat format = new SimpleDateFormat("yyyy-MM-dd");
			Date temp_date = null;
			
			
			for(int i=0; i<array.length-1; i++){
				Data_compare[i][0] = (Data[i+1][3]);
				Data_compare[i][1] = (Data[i+1][4]);
				Data_compare[i][2] = (Data[i+1][5]);
				Data_compare[i][3] = (Data[i+1][8]);
				Data_compare[i][4] = (Data[i+1][6]);
				Data_compare[i][5] = (Data[i+1][6]);
//				temp_date = format.parse(Data[i][9]);
				try {
					temp_date = format.parse(Data[i+1][9]);
					temp_date.getTime();
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				Date[i] = temp_date.getTime();
				//System.out.println(Data_compare[i][4]);
			}
			
			
	        Random random = new Random();
	        int rand[] = null;
	        rand = new int[array.length/k+1];
	        for(int i=0; i<array.length/k+1; i++){
	        	rand[i] = random.nextInt(array.length);
	        	for(int j=0; j<i; j++){
	        		if(rand[i] == rand[j])
	        		{
	        			rand[i] = random.nextInt(array.length);
	        		}
	        	}
	        	//System.out.println(rand[i]);
	        }

	        
	        double array_knn[][][];
	        double D[];
	        double D_temp[];
	        int group[];
	        D = new double[array.length+1];
	        D_temp = new double[array.length+1];
	        group = new int[array.length];
	        
	        int index[];
	        int index_num=0;
	        index = new int[array.length-1];
	        
	         
	        
	        double avg_pro[];
	        double pro_temp=0;
	        avg_pro = new double[array.length-1];

	        
	        if(array.length%k == 0)
	        {
	        	array_knn = new double[array.length][][];
	        	for(int i=0; i<array.length/k; i++){
	        		array_knn[i] = new double[k][];
	        		for(int j=0; j<k; j++){
	        			array_knn[i][j] = new double[4];
	        			/*array_knn[i][j][0] = Double.parseDouble(Data_compare[rand[j]][0]);
	        			array_knn[i][j][1] = Double.parseDouble(Data_compare[rand[k-j-1]][1]);
	        			array_knn[i][j][2] = Double.parseDouble(Data_compare[rand[j]][2]);
	        			array_knn[i][j][3] = Double.parseDouble(Data_compare[rand[k-j-1]][3]);*/
	        			
	        			/*System.out.println(array_knn[i][j][0]);
	        			System.out.println(array_knn[i][j][1]);
	        			System.out.println(array_knn[i][j][2]);
	        			System.out.println(array_knn[i][j][3]);*/
	        		}
	        		//System.out.println();
	        	}
	        	
	        	for(int i=0; i<array.length/k; i++){
	        		array_knn[i][0][0] = Double.parseDouble(Data_compare[rand[i]][0]);
	        		array_knn[i][0][1] = Double.parseDouble(Data_compare[rand[i]][1]);
	        		array_knn[i][0][2] = Double.parseDouble(Data_compare[rand[i]][2]);
	        		array_knn[i][0][3] = Double.parseDouble(Data_compare[rand[i]][3]);
	        	}
	        	
	        	
	        	
	        	for(int i=0; i<array.length/k; i++){
	        		for(int j=0; j<array.length-1; j++){
	        			D[j] = (Math.pow(array_knn[i][0][0]-Double.parseDouble(Data_compare[j][0]), 2))+(Math.pow(array_knn[i][0][1]-Double.parseDouble(Data_compare[j][1]), 2))
	        					+(Math.pow(array_knn[i][0][2]-Double.parseDouble(Data_compare[j][2]), 2))+(Math.pow(array_knn[i][0][3]-Double.parseDouble(Data_compare[j][3]), 2));
	        			
	        		}
	        	}
	        	
	        }
	        
	        else
	        {
	        	array_knn = new double[array.length+1][][];
	        	for(int i=0; i<array.length/k;i++){
	        		array_knn[i] = new double[k][];
	        		for(int j=0; j<k; j++){
	        			array_knn[i][j] = new double[6];
	        		}
	        	}
	        	array_knn[array.length/k] = new double[array.length%k][];
	        	for(int i=0; i<array.length%k; i++){
	        		array_knn[array.length/k][i] = new double[5];
	        	}
	        	
	        	for(int i=0; i<array.length/k; i++){
	        		array_knn[i][0][0] = Double.parseDouble(Data_compare[rand[i]][0]);
	        		array_knn[i][0][1] = Double.parseDouble(Data_compare[rand[i]][1]);
	        		array_knn[i][0][2] = Double.parseDouble(Data_compare[rand[i]][2]);
	        		array_knn[i][0][3] = Double.parseDouble(Data_compare[rand[i]][3]);
	        		array_knn[i][0][4] = Double.parseDouble(Data_compare[rand[i]][4]);
	        	}
	        	array_knn[array.length/k][0][0] = Double.parseDouble(Data_compare[rand[array.length/k]][0]);
	        	array_knn[array.length/k][0][1] = Double.parseDouble(Data_compare[rand[array.length/k]][1]);
	        	array_knn[array.length/k][0][2] = Double.parseDouble(Data_compare[rand[array.length/k]][2]);
	        	array_knn[array.length/k][0][3] = Double.parseDouble(Data_compare[rand[array.length/k]][3]);
	        	array_knn[array.length/k][0][4] = Double.parseDouble(Data_compare[rand[array.length/k]][4]);

	        	for(int i=0; i<array.length/k; i++){
	        		for(int j=0; j<array.length-1; j++){
	        			D[j] = (Math.pow(array_knn[i][0][0]-Double.parseDouble(Data_compare[j][0]), 2))+(Math.pow(array_knn[i][0][1]-Double.parseDouble(Data_compare[j][1]), 2))
	        					+(Math.pow(array_knn[i][0][2]-Double.parseDouble(Data_compare[j][2]), 2))+(Math.pow(array_knn[i][0][3]-Double.parseDouble(Data_compare[j][3]), 2));
	        			D_temp[j] = D[j];

	        			}
	        		D[array.length] = (Math.pow(array_knn[array.length/k][0][0]-Double.parseDouble(Data_compare[array.length-2][0]), 2))+(Math.pow(array_knn[array.length/k][0][1]-Double.parseDouble(Data_compare[array.length-2][1]), 2))
	    					+(Math.pow(array_knn[array.length/k][0][2]-Double.parseDouble(Data_compare[array.length-2][2]), 2))+(Math.pow(array_knn[array.length/k][0][3]-Double.parseDouble(Data_compare[array.length-2][3]), 2));
	        		D_temp[array.length] = D[array.length];
	        		
	        		Arrays.sort(D_temp);
	        		for(int j=1; j<20; j++){
	        			for(int l=0; l<array.length-1; l++){
	        				if(D_temp[j] == D[l]){
	        					array_knn[i][j][0] = Double.parseDouble(Data_compare[l][0]);
	        					array_knn[i][j][1] = Double.parseDouble(Data_compare[l][1]);
	        					array_knn[i][j][2] = Double.parseDouble(Data_compare[l][2]);
	        					array_knn[i][j][3] = Double.parseDouble(Data_compare[l][3]);
	        					array_knn[i][j][4] = Double.parseDouble(Data_compare[l][4]);
	        					array_knn[i][j][5] = Double.parseDouble(Data_compare[l][5]);
	        					index[index_num++] = l;
	        				}
	        				/*for(int n=0; n<(array.length-1)/20; n++){
	        					for(int a = n*20; a<20*(n+1); n++){
	        						pro_temp += array_knn[i][j][4];
	        					}
	        					for(int b= n*20; b<20*(n+1); b++){
	        						array_knn[i][j][4] = pro_temp/20;
	        					}
	        					pro_temp = 0;
	        				}*/
	        				
	        				
	        			}
	        			for(int a=0; a<k; a++){
        					pro_temp = array_knn[i][j][4];
        				}
	        			for(int b=0; b<k; b++){
	        				array_knn[i][b][4] = pro_temp/k;
	        			}
	        			pro_temp = 0;
	        			
	        		}
        		/*	for(int a=0; a<array.length-1;a++)
                		System.out.println(D_temp[a]);*/
	        		}
	        }
	        
	        
	      //  System.out.println(array.length/k);*/
	                
	      /* for(int i=0; i<array.length/k; i++){
	        	for(int j=0; j<k; j++){
	        		System.out.print(array_knn[i][j][0]+"\t");
	        		System.out.print(array_knn[i][j][1]+"\t");
	        		System.out.print(array_knn[i][j][2]+"\t");
	        		System.out.println(array_knn[i][j][3]);
	        	}
	        	System.out.println();
	        }
*/	        
	        /*for(int i=0; i<array.length/k; i++)
	        {
	        	for(int j=0; j<k; j++){
	        		averg_profit[i] += array_knn[i][j][4];
	        	}
	        	System.out.println(averg_profit[i]);
	        }*/
	       // for(int i=0; i<array.length-1; i++)
	        	//System.out.println(index[i]);
	        
	       // for(int i=0; i<array.length; i++){
	     //   	System.out.println(D[i]);
	     //   }
	        
			/*PrintWriter pw = new PrintWriter("out.csv");
	        for(int i=0; i<array.length-1; i++) {
	            String data = Data_compare[i][0]+','+Data_compare[i][1]+','+Data_compare[i][2]+','+Data_compare[i][3]+','+Data_compare[i][4]+','+Date[i];
	            pw.println(data);
	        }
	       pw.close();*/
	        
	        PrintWriter pw = new PrintWriter("Analisis/knn_result.csv");
	        for(int i=0; i<array.length/k; i++)
	        {
	        	for(int j=0; j<k; j++){
	        		String data = Double.toString(array_knn[i][j][0])+','+Double.toString(array_knn[i][j][1])+','+Double.toString(array_knn[i][j][2])+','+Double.toString(array_knn[i][j][3])+','+Double.toString(array_knn[i][j][4])+','+Double.toString(array_knn[i][j][5]);
	        		pw.println(data);
	        	}
	        }
	        pw.close();


			/*double distance=0;
			double temp_distance=0;
			
			for(int i=0; i<array.length-1;i++){
				for(int j=i; j<array.length;j++){
					temp_distance = Math.pow(Data_compare[i][0]-Data_compare[j][0], 2)+Math.pow(Data_compare[i][1]-Data_compare[j][1], 2)
										+Math.pow(Data_compare[i][2]-Data_compare[j][2], 2)+Math.pow(Data_compare[i][3]-Data_compare[j][3], 2);
				}
			}*/
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}