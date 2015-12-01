package network_topology;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

/**
 * Created by wing on 11/30/15.
 */
public class Solution {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        final int V = sc.nextInt();
        final int E = sc.nextInt();

        int[] degrees = new int[V];

        for (int i = 0; i < E; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            degrees[u - 1]++;
            degrees[v - 1]++;
        }
        int deg1count = 0;
        int deg2count = 0;
        int degXcount = 0;
        for (int d : degrees) {
            if (d == 1) deg1count++;
            else if (d == 2) deg2count++;
            else degXcount++;
        }

        if (deg1count == 0 && degXcount == 0) System.out.println("ring topology");
        else if (deg1count == 2 && degXcount == 0) System.out.println("bus topology");
        else if (deg2count == 0 && degXcount == 1) System.out.println("star topology");
        else System.out.println("unknown topology");
    }
}
