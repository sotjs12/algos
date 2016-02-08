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
import java.sql.SQLException;
import java.text.ParseException;
import java.util.ArrayList;

/**
 *
 * @author cho
 */
public class Run {

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     * @throws java.io.FileNotFoundException
     * @throws java.text.ParseException
     * @throws java.sql.SQLException
     */
    public static void main(String[] args) throws IOException, FileNotFoundException, ParseException, SQLException {
        Unit_Task Run = new Unit_Task();
        Run.Unit_Run(args);
    }

    public static class Unit_Task {

        ArrayList<String> CSVList = new ArrayList<>();

        public Unit_Task() throws IOException, FileNotFoundException, ParseException {
            BufferedReader br = new BufferedReader(new FileReader("public/models/nasdaq100list.csv"));
            String line;
            String[] parse;
            br.readLine();
            while ((line = br.readLine()) != null) {
                parse = line.split(",");
                CSVList.add(parse[0]);
            }

        }

        public void Unit_Run(String[] args) throws SQLException, IOException, FileNotFoundException, ParseException {
            int index = 0;
            String symbol;
            switch (args[0]) {
                case "analisis":
                    while (CSVList.size() != index) {
                        symbol = CSVList.get(index);
                        Analisis(symbol);
                        System.out.println(String.valueOf(index) + "...Done..." + symbol);
                        index++;
                    }
                    break;
                case "model":
                    
                    BufferedWriter bw = new BufferedWriter(new FileWriter("transedData_All.csv"));
                    bw.write("");
                    bw.close();
                    while (CSVList.size() != index) {
                        symbol = CSVList.get(index);
                        TransForm_Data Trans = new TransForm_Data(symbol);
                        Trans.Read_From_SQL();
                        Trans.CreateCsvRatinsFile(2);
                        index++;
                    }
                    System.out.println("...Done...");
                    ML_A1 Kmeans = new ML_A1("Total");
                    Kmeans.Calc_KMeans();
                    break;
                default:
                    break;
            }

        }

        void Analisis(String FName) throws IOException, ParseException, SQLException {            
            ML_A1 Kmeans = new ML_A1(FName);
            Kmeans.Analisis_Data("Analisis/" + FName + "_analysis.csv");
            Kmeans.Up_To_DB();
        }
    }
}
