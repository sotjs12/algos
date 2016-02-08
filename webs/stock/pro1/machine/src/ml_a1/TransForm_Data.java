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
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import static java.util.Collections.list;
import java.util.Date;

/**
 *
 * @author m1
 */
public class TransForm_Data {

    public String symbol;
    public String inputFile;
    public String outputFile;
    public String outputFile2;
    int i = 0;
    int lineCNT = 0;
    int lineVolume = 26;
    double AVR, AVRLong = 0;
    double[] closeV;// = new double[lineVolume];
    double[] closeVolume;// = new double[lineVolume];
    double UpDown = 0;
    double UpDownTomorrow = 0;
    DecimalFormat df = new DecimalFormat("00.0");

    double Max_AVR = 0;

    ArrayList<String> lines = new ArrayList<String>();
    ArrayList<String> Outlines = new ArrayList<String>();
    TransForm_Data(String inFile) {
        symbol = inFile;
        inputFile = "OriginData/" + inFile + "_origin.csv";
        outputFile = "Data/" + inFile + "_transedData.csv";
        outputFile2 = "transedData_All.csv";
        closeV = new double[lineVolume];
        closeVolume = new double[lineVolume];
    }

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    void Calc_MoveAvr() {
        String[] temp;
        AVR = AVRLong = 0;
        for (i = 0; i < lines.size() / 2; i++) {
            temp = lines.get(i).split(",");
            AVR += Double.parseDouble(temp[6]);
            AVRLong += Double.parseDouble(temp[6]);
        }
        for (; i < lines.size(); i++) {
            temp = lines.get(i).split(",");
            AVRLong += Double.parseDouble(temp[6]);
        }
        AVR /= lines.size() / 2;
        AVR *= 100;
        AVRLong /= lines.size();
        AVRLong *= 100;
    }

    double Calc_RSI() {
        double RV = 0;
        double RV2 = 0;
        double t;
        String[] temp;

        for (i = 0; i < lines.size()/2+1; i++) {
            temp = lines.get(i).split(",");
            closeV[i] = Double.parseDouble(temp[6]);
        }
        UpDown = (closeV[0] - closeV[1]) * 100 / closeV[1];
        for (i = 1; i < lines.size()/2+1; i++) {
            t = closeV[i - 1] - closeV[i];
            if (t > 0) {
                RV += t;
            } else {
                RV2 += t;
            }
        }
        return RV * 100 / (RV - RV2);
    }

    double Calc_Stochastics() {
        double RV;
        double RV2;
        double t;
        String[] temp;

        temp = lines.get(0).split(",");
        RV = RV2 = closeV[0] = Double.parseDouble(temp[6]);
        for (i = 1; i < lines.size()/5+1; i++) {
            temp = lines.get(i).split(",");
            closeV[i] = Double.parseDouble(temp[6]);
            if (RV < closeV[i]) {
                RV = closeV[i];
            }
            if (RV2 > closeV[i]) {
                RV2 = closeV[i];
            }
        }

        return (closeV[0] - RV2) * 100 / (RV - RV2);
    }

    double Calc_VR() {
        double RV = 0;
        double RV2 = 0;
        double NV = 0;
        double t = 0;
        String[] temp;

        for (i = 0; i < lines.size(); i++) {
            temp = lines.get(i).split(",");
            closeV[i] = Double.parseDouble(temp[6]);
            closeVolume[i] = Double.parseDouble(temp[5]);
        }

        for (i = 1; i < lines.size(); i++) {
            t = (closeV[i - 1] - closeV[i]) * 100 / closeV[i];
            if (t > 0.3) {
                RV += closeVolume[i];
            } else if (t <= 0.3 && t >= -0.3) {
                NV += closeVolume[i];
            } else {
                RV2 += closeVolume[i];
            }

        }
        if ((RV2 + NV / 2) == 0) {
            return -100;
        }
        return ((RV + NV / 2) * 100) / (RV2 + NV / 2);
    }

    void Read_From_SQL() throws SQLException {
        Connection conn = null;
        Statement stmt = null;
        String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        String DB_URL = "jdbc:mysql://localhost:3306/origin_db";
        String USER = "root";
        String PASS = "1124";
        try {
            //STEP 2: Register JDBC driver
            Class.forName(JDBC_DRIVER);
            //STEP 3: Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            //STEP 4: Execute a query
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            String sql;
            BufferedWriter bw = new BufferedWriter(new FileWriter(inputFile));
            bw.write("Date,Open,High,Low,Close,Volume,adjClose");
            bw.newLine();
            sql = "SELECT * FROM " + symbol + "_origin order by dates desc";
            ResultSet rs = stmt.executeQuery(sql);
            //STEP 5: Extract data from result set
            while (rs.next()) {
                //Retrieve by column name
                bw.write(rs.getString("dates") + "," + rs.getString("open") + "," + rs.getString("high")
                        + "," + rs.getString("low") + "," + rs.getString("close") + "," + rs.getString("volume") + "," + rs.getString("adjClose"));
                bw.newLine();
                lineCNT++;
            }
            //STEP 6: Clean-up environment
            bw.close();
            rs.close();
            stmt.close();
            conn.close();
            System.out.println("Done...");
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

    void CreateCsvRatinsFile(int c) throws FileNotFoundException, IOException {
        double[] macdArr;
        int cnt2;
        try (BufferedReader br = new BufferedReader(new FileReader(inputFile))) {
            String line;
            String line2write;
            String[] temp = null;
            String[] temp2;
            double RSI;
            double SCS;
            double VR;
            line = br.readLine();
            for (i = 0; i < lineVolume; i++) {  //20's move avr
                if ((line = br.readLine()) == null) {
                    break;
                }
                lines.add(line);
            }
            macdArr = new double[lineCNT];
            cnt2 = 0;
            while ((line = br.readLine()) != null) {
                Calc_MoveAvr();
                AVR -= AVRLong;
                RSI = Calc_RSI();
                SCS = Calc_Stochastics();
                VR = Calc_VR();

                if (temp != null) {
                    temp2 = lines.get(0).split(",");
                    UpDownTomorrow = (Double.parseDouble(temp[6]) - Double.parseDouble(temp2[6])) * 100 / Double.parseDouble(temp2[6]);
                }

                temp = lines.get(0).split(",");
                lines.remove(0);
                lines.add(line);

                macdArr[cnt2++] = AVR;

                line2write = temp[1] + "," + temp[4] + "," + temp[5] + "," + String.valueOf(AVR) + "," + String.valueOf(RSI) + ","
                        + String.valueOf(SCS) + "," + String.valueOf(Double.parseDouble(df.format(UpDown))) + ","
                        + String.valueOf(Double.parseDouble(df.format(UpDownTomorrow))) + "," + String.valueOf(VR) + "," + temp[0];
                Outlines.add(line2write);
            }

            Arrays.sort(macdArr);

            Max_AVR = macdArr[(int) (cnt2 * 0.9)];
            if (c == 1) {
                Nomalization(outputFile,false);
            } else {
                Nomalization(outputFile2,true);
            }
        }

    }

    public void Nomalization(String FName,boolean abc) throws IOException {
        String[] temp;
        String OutData;
        try (BufferedWriter bw2 = new BufferedWriter(new FileWriter(FName, abc))) {
            for (String Outline : Outlines) {
                temp = Outline.split(",");
                OutData = temp[0] + "," + temp[1] + "," + temp[2] + "," + String.valueOf(Double.parseDouble(temp[3]) * 100 / Max_AVR)
                        + "," + String.valueOf(Double.parseDouble(temp[4]) )
                        + "," + String.valueOf(Double.parseDouble(temp[5]) )
                        + "," + temp[6]
                        + "," + temp[7]
                        + "," + String.valueOf(Double.parseDouble(temp[8]))
                        + "," + temp[9];
                bw2.write(OutData);
                bw2.newLine();
                bw2.flush();
            }
        }
    }
}
