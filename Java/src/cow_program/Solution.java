package cow_program;
/*
Idea:
Only consider plus reachable
But bfs starts from halt state (go from reverse arrows), no matter the edge is '-' or '+'
 */

import java.util.*;

/**
 * Created by wing on 12/1/15.
 */
public class Solution {
    public class Graph {
        public class Vertex {
            public Vertex(int index, int weight) {
                this.index = index;
                this.weight = weight;
            }

            @Override
            public String toString() {
                return index + ": " + plusTails + '|' + minusTails;
            }


            int index;
            int weight;
            List<Edge> plusTails = new ArrayList<>();
            List<Edge> minusTails = new ArrayList<>();
            boolean plusVisited = false;
            boolean minusVisited = false;
        }

        public class Edge { // need to revert the direction
            public Edge(Vertex tail, int type) {
                this.tail = tail;
                this.type = type;
            }

            @Override
            public String toString() {
                return (type == 1 ? "+" : type == 2 ? "-" : "?") + tail.index;
            }

            Vertex tail;
            int type = 0; // can be, in binary, '01'(+), '10'(-), or '11'(both + and -), 00 is uninitialized (not reachable)
        }

        @Override
        public String toString() {
            String res = "";
            for (Vertex v : vertices) {
                res += (v.toString() + "\n");
            }
            return res;
        }

        List<Vertex> vertices;
        Vertex haltState;
    }

    public Graph readInput() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        List<Graph.Vertex> nodes = new ArrayList<>(n - 1);
        Graph g = new Graph();
        Graph.Vertex halt = g.new Vertex(0, 0);
        halt.minusVisited = true;
        halt.plusVisited = true;
        Graph.Vertex start = g.new Vertex(1, 0);
        nodes.add(halt); // halt state
        nodes.add(start); // starts from here but should never visit here again

        for (int i = 2; i <= n; i++) {
            int weight = sc.nextInt();
            nodes.add(g.new Vertex(i, weight)); // no a_1, index = 2, 3, ..., n  (total n - 1 nodes)
        }

        for (Graph.Vertex node : nodes) {
            int plusLand = node.index + node.weight;
            int minusLand = node.index - node.weight;
            if (plusLand < 1 || plusLand > n) plusLand = 0;
            if (minusLand < 1 || minusLand > n) minusLand = 0;
            Graph.Vertex nodePlus = nodes.get(plusLand);
            Graph.Vertex nodeMinus = nodes.get(minusLand);
            nodePlus.plusTails.add(g.new Edge(node, 1));
            nodeMinus.minusTails.add(g.new Edge(node, 2));
            if (node.index != 0) node.plusTails.add(g.new Edge(start, 1));
        }
        g.haltState = halt;
        g.vertices = nodes;
        start.plusTails.clear();

//        System.out.println(g);
        return g;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        Graph graph = sol.readInput();
        class ScoreState {
            public ScoreState(int score, Graph.Vertex v) {
                this.score = score;
                this.v = v;
            }

            Graph.Vertex v;
            int score;
        }
        Stack<ScoreState> s = new Stack<>();
        s.push(new ScoreState(0, graph.haltState));
        int[] ans = new int[graph.vertices.size() - 2]; // (n + 1) - 2
        for (int i = 0; i < graph.vertices.size() - 2; i++) {
            ans[i] = -1;
        }

        // must alternate between + and - edges
        while (!s.isEmpty()) {
            ScoreState ss = s.pop();
            if (ss.v.plusVisited) {
                for (Graph.Edge e : ss.v.minusTails) {
                    if (!e.tail.minusVisited) {
                        int newScore = ss.score + e.tail.weight;
                        s.push(new ScoreState(newScore, e.tail));
                        e.tail.minusVisited = true;
                    }
                }
            }
            if (ss.v.minusVisited) {
                for (Graph.Edge e : ss.v.plusTails) {
                    if (!e.tail.plusVisited) {
                        int newScore = ss.score + e.tail.weight;
                        if (e.tail.index == 1) ans[ss.v.index - 2] = newScore + ss.v.index - 1;
                        else {
                            s.push(new ScoreState(newScore, e.tail));
                            e.tail.plusVisited = true;
                        }
                    }
                }
            }
        }
        for (int a : ans) {
            System.out.println(a);
        }

    }
}
