/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ml_a1;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import static java.lang.Math.pow;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Random;
import java.util.Stack;

/**
 *
 * @author m1
 */
public class ML_A1 {

    static final int C_SIZE = 11;
    static int K_SIZE;
    static ArrayList<Dataset> Items = new ArrayList<Dataset>();
    static ArrayList<Cluster>[] Clusters = new ArrayList[C_SIZE];
    String inputFile;
    String transedData;
    String modelPath;
    String bestModelPath;
    String originDataPath;
    String analysisPath;
    DateFormat format = new SimpleDateFormat("yyyy-MM-dd");
    int Best;
    double[] Max = new double[4];

    public ML_A1(String fTName) {
        inputFile = fTName;
        transedData = "Data/" + inputFile + "_transedData.csv";
        modelPath = "Model/Total_model";
        originDataPath = "OriginData/" + inputFile + "_origin.csv";
        bestModelPath = "Model/" + inputFile + "_bestModel.csv";
        analysisPath = "Analisis/" + inputFile + "_analysis.csv";
    }

    public void Up_To_DB() {
        Connection conn = null;
        Statement stmt = null;
        String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        String DB_URL = "jdbc:mysql://localhost:3306/analysis_db";
        String USER = "root";
        String PASS = "1124";
        try {
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.createStatement();
            SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
            String sql;
            String[] t;
            String line;
            String tableName = inputFile + "_analysis";
            Date date;
            BufferedReader br = new BufferedReader(new FileReader(analysisPath));
            br.readLine();
            stmt.executeUpdate("drop table if exists " + tableName);
            stmt.executeUpdate("create table if not exists " + tableName + " (dates date,close float,rsi float,scs float,macd float,vr float,longpre float,shortpre float)");

            while ((line = br.readLine()) != null) {
                t = line.split(",");
                if (t.length == 8) {
                    date = format.parse(t[0]);
                    sql = "insert into " + tableName
                            + " (dates,close,rsi,scs,macd,vr,longpre,shortpre)"
                            + " values (?,?,?,?,?,?,?,?)";
                    PreparedStatement ps = conn.prepareStatement(sql);
                    Timestamp sqldate = new Timestamp(date.getTime());
                    ps.setTimestamp(1, sqldate);
                    ps.setFloat(2, Float.valueOf(t[1]));
                    ps.setFloat(3, Float.valueOf(t[2]));
                    ps.setFloat(4, Float.valueOf(t[3]));
                    ps.setFloat(5, Float.valueOf(t[4]));
                    ps.setFloat(6, Float.valueOf(t[5]));
                    ps.setFloat(7, Float.valueOf(t[6]));
                    ps.setFloat(8, Float.valueOf(t[7]));
                    ps.executeUpdate();
                } else if (t.length == 7) {
                    date = format.parse(t[0]);
                    sql = "insert into " + tableName
                            + " (dates,close,rsi,scs,macd,vr,longpre,shortpre)"
                            + " values (?,?,?,?,?,?,?,?)";
                    PreparedStatement ps = conn.prepareStatement(sql);
                    Timestamp sqldate = new Timestamp(date.getTime());
                    ps.setTimestamp(1, sqldate);
                    ps.setFloat(2, Float.valueOf(t[1]));
                    ps.setFloat(3, Float.valueOf(t[2]));
                    ps.setFloat(4, Float.valueOf(t[3]));
                    ps.setFloat(5, Float.valueOf(t[4]));
                    ps.setFloat(6, Float.valueOf(t[5]));
                    ps.setFloat(7, Float.valueOf(t[6]));
                    ps.setFloat(8, 0);
                    ps.executeUpdate();
                } else {
                    break;
                }
            }
            br.close();
            stmt.close();
            conn.close();
        } catch (SQLException se) {
            //Handle errors for JDBC
            se.printStackTrace();
        } catch (Exception e) {
            //Handle errors for Class.forName
            e.printStackTrace();
        } finally {
            //finally block used to close resources
            try {
                if (stmt != null) {
                    stmt.close();
                }
            } catch (SQLException se2) {
            }// nothing we can do
            try {
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException se) {
                se.printStackTrace();
            }//end finally try
        }//end try
    }

    public void Read_TFile(String fn) throws FileNotFoundException, IOException {
        Items.clear();
        BufferedReader br = new BufferedReader(new FileReader(fn));
        String[] temp;
        String line;
        int DataId = 0;
        while ((line = br.readLine()) != null) {
            temp = line.split(",");
            Items.add(new Dataset(DataId, Double.parseDouble(temp[4]), Double.parseDouble(temp[5]),
                    Double.parseDouble(temp[3]), Double.parseDouble(temp[8]), Double.parseDouble(temp[6]),
                    Double.parseDouble(temp[7]), Double.parseDouble(temp[1]), temp[9])); //csv 에서 값받아와서 넣어줌 추후 추가되면 이부분 수정     
            DataId++;
        }
        br.close();
    }

    public void Calc_KMeans() throws FileNotFoundException, IOException, ParseException {
        Read_TFile("transedData_All.csv");
        K_SIZE = (int) Math.sqrt((double) (Items.size() / 2)) * 4;
        System.out.println(K_SIZE);
        int jIndex = Items.size() / K_SIZE;
        Clusters[0] = new ArrayList<>();
        for (int i = 0; i < K_SIZE; i++) {
            Clusters[0].add(new Cluster(i, Items.get(i * jIndex).DItems[0], Items.get(i * jIndex).DItems[1], Items.get(i * jIndex).DItems[2], Items.get(i * jIndex).DItems[3]));   //클러스터 구성
        }
        for (int i = 0; i < C_SIZE; i++) {
            Cluster_Job(i);
            BufferedWriter bw2 = new BufferedWriter(new FileWriter(modelPath + String.valueOf(i) + ".csv"));
            bw2.write(String.valueOf(i));
            bw2.newLine();
            for (Cluster c : Clusters[0]) {
                if (!c.InItems.isEmpty()) {
                    c.Calc_UpPoint();
                    bw2.write(String.valueOf(c.ID) + "," + String.valueOf(c.Up_Point) + "," + String.valueOf(c.Up_AVR) + "," + String.valueOf(c.InItems.size())
                            + "," + String.valueOf(c.Poins[0]) + "," + String.valueOf(c.Poins[1]) + "," + String.valueOf(c.Poins[2]) + "," + String.valueOf(c.Poins[3]));
                    bw2.newLine();
                    bw2.flush();
                }
            }
            bw2.close();
            System.out.println(i);
        }

    }

    public void Cluster_Job(int para) {
        int index;
        int changeIndex = 1;
        int call = 0;
        while (changeIndex != 0) {
            changeIndex = 0;
            System.out.println(call++);
            for (index = 0; index < Items.size(); index++) {
                if (SetNearestCluster(index, para)) {
                    changeIndex++;
                }
            }
            for (index = 0; index < Clusters[0].size(); index++) {
                Clusters[0].get(index).Change_Central();
            }
        }
    }

    public boolean SetNearestCluster(int index, int C) {
        double distance = 999999999;
        double distance_C;
        Dataset tempSet = Items.get(index);
        double[] Points = tempSet.GetPoints();
        int i = 0;
        int Id = 0;
        int tempId = tempSet.clusterID;

        for (Cluster cluster : Clusters[0]) {
            distance_C = cluster.Calc_Distance(Points, C);
            if (distance > distance_C) {
                distance = distance_C;
                Id = i;
            }
            i++;
        }
        tempSet.clusterID = Id;
        if (Id == tempId && tempId != -1) {
            return false;
        }
        Clusters[0].get(Id).AddItem(tempSet);
        if (tempId != -1) {
            Clusters[0].get(tempId).RemoveItem(tempSet);
        }
        return true;
    }

    public void Analisis_Data(String OutDir) throws IOException, ParseException, SQLException {
        TransForm_Data Trans = new TransForm_Data(inputFile);
        Trans.Read_From_SQL();
        Trans.CreateCsvRatinsFile(1);
        Read_TFile(transedData);
        
        ArrayList<Cluster> OneCluster[] = new ArrayList[C_SIZE];
        String outputFile = OutDir;
        BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile));
        String VTemp;
        String[] LineS;
        Date temp;
        int Out_Size = 60;
        int j, i, index;
        double minDistance=9999999,minTemp;
        double upA=0,upP=0;
        String Input;
        Cluster tempCluster;
        Dataset tempItem;
        //////////////////////////////////////////단일 클러스터구성
   
        for (j = 0, i = 0; j < C_SIZE; j++) {
            BufferedReader br = new BufferedReader(new FileReader(modelPath+String.valueOf(j)+".csv"));
            OneCluster[j] = new ArrayList<>();
            br.readLine();
            while ((VTemp = br.readLine()) != null) {
                LineS = VTemp.split(",");
                OneCluster[j].add(new Cluster(i, Double.parseDouble(LineS[4]), Double.parseDouble(LineS[5]), Double.parseDouble(LineS[6]), Double.parseDouble(LineS[7])));   //클러스터 구성
                OneCluster[j].get(i).Up_Point = Double.parseDouble(LineS[1]);
                OneCluster[j].get(i).Up_AVR = Double.parseDouble(LineS[2]);
                i++;
            }
            i=0;
            br.close();
        }
        bw.write("Date,Close,RSI,SCS,MACD,VR,LongPre,ShortPre");
        bw.newLine();
        for (i = 0; i < Out_Size; i++) {
            tempItem = Items.get(i);
            for (j = 0; j < C_SIZE; j++) {
                for(index = 0; index < OneCluster[j].size();index++)
                {
                    tempCluster = OneCluster[j].get(index);
                    minTemp = tempCluster.Calc_Distance(tempItem.DItems, j);
                    if(minTemp < minDistance )
                    {  
                             
                            minDistance = minTemp;
                            upA = tempCluster.Up_AVR;
                            upP = tempCluster.Up_Point;
                    }
                }
            }
            minDistance = 99999999;
            temp = format.parse(tempItem.Date);                   //Date 형변환         
            Input = format.format(temp.getTime()) + "," + String.valueOf(tempItem.close)
                        + "," + String.valueOf(tempItem.DItems[0]) + "," + String.valueOf(tempItem.DItems[1]) + "," + String.valueOf(tempItem.DItems[2]) + "," + String.valueOf(tempItem.DItems[3])
                        + "," + String.valueOf(upP) + "," + String.valueOf(tempItem.close*(1+upA/100));            
            bw.write(Input);
            bw.newLine();
            bw.flush();
        }
        bw.close();
    }
}
