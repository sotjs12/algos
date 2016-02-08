/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ml_a1;

import static java.lang.Math.pow;
import java.util.ArrayList;
import java.util.Arrays;

/**
 *
 * @author cho
 */
public class Cluster {

        double[] Poins = new double[4];
        double[] ChagePoints = new double[4];
        int ID;
        ArrayList<Dataset> InItems = new ArrayList<Dataset>();
        double Up_Point;
        double Up_AVR;

        Cluster(int id, double i1, double i2, double i3, double i4) {
            ID = id;
            Poins[0] = i1;
            Poins[1] = i2;
            Poins[2] = i3;
            Poins[3] = i4;
            Up_Point = 0;
        }

        Cluster() {
        }

        void AddItem(Dataset In) {
            InItems.add(In);
        }

        void RemoveItem(Dataset In) {
            InItems.remove(In);
        }

        void Change_Central() {
            for (Dataset InItem : InItems) {
                ChagePoints[0] += InItem.GetPoints()[0];
                ChagePoints[1] += InItem.GetPoints()[1];
                ChagePoints[2] += InItem.GetPoints()[2];
                ChagePoints[3] += InItem.GetPoints()[3];
            }
            ChagePoints[0] /= (InItems.size() + 1);
            ChagePoints[1] /= (InItems.size() + 1);
            ChagePoints[2] /= (InItems.size() + 1);
            ChagePoints[3] /= (InItems.size() + 1);
            Poins[0] = ChagePoints[0];
            Poins[1] = ChagePoints[1];
            Poins[2] = ChagePoints[2];
            Poins[3] = ChagePoints[3];
        }

        double Calc_Distance(double[] d, int C) {
            double Distance = 0;
            switch (C) {
                case 0:
                    Distance = (Poins[0] - d[0]) * (Poins[0] - d[0]) + (Poins[1] - d[1]) * (Poins[1] - d[1]) + (Poins[2] - d[2]) * (Poins[2] - d[2]) + (Poins[3] - d[3]) * (Poins[3] - d[3]);
                    break;
                case 1:
                    Distance = (Poins[1] - d[1]) * (Poins[1] - d[1]) + (Poins[2] - d[2]) * (Poins[2] - d[2]) + (Poins[3] - d[3]) * (Poins[3] - d[3]);

                    break;
                case 2:

                    Distance = (Poins[0] - d[0]) * (Poins[0] - d[0]) + (Poins[2] - d[2]) * (Poins[2] - d[2]) + (Poins[3] - d[3]) * (Poins[3] - d[3]);
                    break;
                case 3:

                    Distance = (Poins[0] - d[0]) * (Poins[0] - d[0]) + (Poins[1] - d[1]) * (Poins[1] - d[1]) + (Poins[3] - d[3]) * (Poins[3] - d[3]);
                    break;
                case 4:

                    Distance = (Poins[0] - d[0]) * (Poins[0] - d[0]) + (Poins[1] - d[1]) * (Poins[1] - d[1]) + (Poins[2] - d[2]) * (Poins[2] - d[2]);
                    break;
                case 5:

                    Distance = (Poins[2] - d[2]) * (Poins[2] - d[2]) + (Poins[3] - d[3]) * (Poins[3] - d[3]);
                    break;
                case 6:

                    Distance = (Poins[1] - d[1]) * (Poins[1] - d[1]) + (Poins[3] - d[3]) * (Poins[3] - d[3]);
                    break;
                case 7:

                    Distance = (Poins[1] - d[1]) * (Poins[1] - d[1]) + (Poins[2] - d[2]) * (Poins[2] - d[2]);
                    break;
                case 8:

                    Distance = (Poins[0] - d[0]) * (Poins[0] - d[0]) + (Poins[3] - d[3]) * (Poins[3] - d[3]);
                    break;
                case 9:

                    Distance = (Poins[0] - d[0]) * (Poins[0] - d[0]) + (Poins[2] - d[2]) * (Poins[2] - d[2]);
                    break;
                case 10:

                    Distance = (Poins[0] - d[0]) * (Poins[0] - d[0]) + (Poins[1] - d[1]) * (Poins[1] - d[1]);
                    break;

            }
                return (Distance);
            //return Math.sqrt(Distance);
        }

        void Calc_UpPoint() {
            double tem1 = 0;double tem2 = 0;
            int up = 0;
            int down = 0;
            Up_AVR = 0;
            Up_Point = 0;
            for (Dataset InItem : InItems) {
                if (InItem.GetRate() > 0.4) 
                {
                    up++;
                    tem1 += InItem.GetRate();
                }
                else if(InItem.GetRate()  < -0.4) 
                {
                    down++;
                    tem2 += InItem.GetRate();
                }
            }
            if (up + down == 0) {
                Up_Point = 50;
                Up_AVR = 0;
            } else {
                Up_Point = up * 100 / (up + down);
                if(Up_Point >=45 && Up_Point <=55)
                {
                    Up_AVR = 0;
                }
                else if (up >= down) {
                    Up_AVR = tem1/up;
                } else {
                    Up_AVR = tem2/down;
                }
            }
        }
    }
