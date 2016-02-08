/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ml_a1;

/**
 *
 * @author cho
 */
public class Dataset {

        double[] DItems = new double[4];
        int ID;
        int clusterID=-1;
        double rate;
        double tomorrow;
        double close;
        String Date;

        Dataset(int id, double i1, double i2, double i3, double i4, double r, double t, double c,String d) {
            ID = id;
            DItems[0] = i1;
            DItems[1] = i2;
            DItems[2] = i3;
            DItems[3] = i4;
            rate = r;
            tomorrow = t;
            close = c;
            Date = d;
        }

        Dataset() {

        }

        double[] GetPoints() {
            return DItems;
        }
        int GetId() {
            return ID;
        }

        double GetRate() {
            return tomorrow;
        }

        String ToString() {
            return String.valueOf(ID) + "," + String.valueOf(DItems[0]) + "," + String.valueOf(DItems[1]) + "," + String.valueOf(DItems[2]) + ","
                    + String.valueOf(DItems[3]) + "," + String.valueOf(rate) + "," + String.valueOf(tomorrow)+","+ Date+ "," +String.valueOf(close);
        }
    }
