package ice_skating;

import java.util.*;

/**
 * Created by wing on 11/29/15.
 */
public class Solution {
    public class Point {
        public int x;
        public int y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public String toString() {
            return String.format("(%d, %d)", x, y);
        }

        @Override
        public boolean equals(Object other) {
            if (!(other instanceof Point)) return false;
            if (other == this) return true;
            Point p = (Point) other;
            return this.x == p.x && this.y == p.y;
        }

        @Override
        public int hashCode() {
            return x * 1000 + y;
        }
    }

    public class Input {
        public Input(int NUM_POINTS, ArrayList<Point> pointList) {
            this.NUM_POINTS = NUM_POINTS;
            this.pointList = pointList;
        }

        public final int NUM_POINTS;
        public ArrayList<Point> pointList;

        public void print() {
            System.out.println(String.format("number of points = %d", NUM_POINTS));
            System.out.println("Points:");
            for (Point p : pointList) {
                System.out.println(p);
            }
        }
    }

    public Input readInput() {
        Scanner sc = new Scanner(System.in);
        final int NUM_OF_SNOW_DRIFT = sc.nextInt();
        ArrayList<Point> pl = new ArrayList<>(NUM_OF_SNOW_DRIFT);
        for (int i = 0; i < NUM_OF_SNOW_DRIFT; i++) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            pl.add(new Point(x, y));
        }
        return new Input(NUM_OF_SNOW_DRIFT, pl);
    }

    private int minSnowDriftNeeded(final Input in) {
        class Vertex {
            public Vertex(Point p) {
                this.p = p;
            }

            public Point p;
            public boolean visited = false;
            public List<Vertex> neighbors = new ArrayList<>(in.NUM_POINTS);
        }
        int hash_size = 1000;
        Vertex[][] indicator = new Vertex[2][hash_size]; // denotes x and y entry taken
        List<Vertex> graph = new ArrayList<>(in.NUM_POINTS);
        for (Point p : in.pointList) {
            int px = p.x - 1;
            int py = p.y - 1;
            if (indicator[0][px] == null && indicator[1][py] == null) {
                Vertex v = new Vertex(p);
                indicator[0][px] = v;
                indicator[1][py] = v;
                graph.add(v);
            } else if (indicator[0][px] == null && indicator[1][py] != null) {
                // don't add the vertex to the graph but indicate that is known
                indicator[0][px] = indicator[1][py];
            } else if (indicator[0][px] != null && indicator[1][py] == null) {
                // don't add the vertex to the graph but indicate that is known
                indicator[1][py] = indicator[0][px];
            } else { // both occupied, try to do union: join the components
                indicator[0][px].neighbors.add(indicator[1][py]);
                indicator[1][py].neighbors.add(indicator[0][px]);
            }
        }
        // do dfs to check how many components in the forest
        int num_components = 0;
        for (Vertex v : graph) {
            if (!v.visited) {
                num_components++;
                Stack<Vertex> stack = new Stack<>();
                stack.push(v);
                while (!stack.isEmpty()) {
                    Vertex a = stack.pop();
                    a.visited = true;
                    for (Vertex n : a.neighbors) {
                        if (!n.visited)
                            stack.push(n);
                    }
                }
            }
        }

        return num_components == 0 ? 0 : num_components - 1;
    }

    public static void main(String args[]) {
        Solution sol = new Solution();
        Input in = sol.readInput();
//        in.print();
        int ans = sol.minSnowDriftNeeded(in);
        System.out.println(ans);
    }

}
