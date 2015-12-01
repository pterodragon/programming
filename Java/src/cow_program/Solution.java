package cow_program;
/*
Idea:
Only consider plus reachable
But bfs starts from halt state (go from reverse arrows), no matter the edge is '-' or '+'
 */
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;

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

            int index;
            int weight;
            char edgeType = '?'; // can be '-', '+', or '*'(both), ? is uninitialized (not reachable)
            boolean plusVisited = false;
            boolean minusVisited = false;
            ArrayList<Vertex> revHeads = new ArrayList<>(); // need to revert the direction of them
        }

        List<Vertex> adjList = new ArrayList<>();
    }

    public Graph readInput() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        List<Graph.Vertex> nodes = new ArrayList<>(n - 1);
        Graph g = new Graph();
        Graph.Vertex halt = g.new Vertex(0, 0);
        halt.plusVisited = true;
        halt.minusVisited = true;
        Graph.Vertex start = g.new Vertex(0, 0);
        start.plusVisited = true;
        start.minusVisited = true;
        nodes.add(halt); // halt state
        nodes.add(start); // starts from here but should never visit here again

        for (int i = 2; i <= n; i++) {
            int weight = sc.nextInt();
            nodes.add(g.new Vertex(i, weight)); // no a_1, index = 2, 3, ..., n  (total n - 1 nodes)
        }

        for (Graph.Vertex node : nodes) {
            int plusLand = node.index + node.weight;
            int minusLand = node.index - node.weight;
            if (plusLand < 0 || plusLand > n) plusLand = 0;
            if (minusLand < 0 || minusLand > n) minusLand = 0;


        }
        return g;
    }

    public static void main(String[] args) {
        // note: need to add back the initially added a_1 (+ i)

    }
}
