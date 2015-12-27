package two_buttons;

import java.util.LinkedList;
import java.util.Scanner;

/**
 * Created by wing on 12/15/15.
 */
public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();
        if (a >= b) {
            System.out.println(a - b);
            return;
        }
        boolean[] visited = new boolean[20001];
        class Node {
            public int dist;
            public int value;

            public Node(int dist, int value) {
                this.dist = dist;
                this.value = value;
            }
        }
        LinkedList<Node> s = new LinkedList<>();
        s.add(new Node(0, a));
        int result = 0;
        while (!s.isEmpty()) {
            Node i = s.removeFirst();
            visited[i.value] = true;
            int left = i.value - 1;
            int right = i.value * 2;
            if (left == b || right == b) {
                result = i.dist + 1;
                break;
            }
            if (left > 0 && !visited[left]) {
                s.add(new Node(i.dist + 1, left));
            }
            if (right <= 20000 && !visited[right]) {
                s.add(new Node(i.dist + 1, right));
            }
        }
        System.out.println(result);
    }
}
