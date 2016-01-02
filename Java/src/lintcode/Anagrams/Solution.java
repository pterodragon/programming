package lintcode.Anagrams;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

/**
 * Created by wing on 1/2/16.
 */
public class Solution {
    /**
     * @param strs: A list of strings
     * @return: A list of strings
     */
    public List<String> anagrams(String[] strs) {
        // algoritm:
        // lexicographical count sort each string
        // string sort all strings
        // scan to output all consecutive equal
        int N = strs.length;
        String[] sortedStrings = new String[N];
        for (int i = 0; i < N; i++) {
            sortedStrings[i] = lexicographicalSort(strs[i]);
        }

        class Pack implements Comparable<Pack> {
            public Pack(String orig, String sorted) {
                this.orig = orig;
                this.sorted = sorted;
            }

            public String orig;
            public String sorted;

            @Override
            public int compareTo(Pack o) {
                return this.sorted.compareTo(o.sorted);
            }
        }
        Pack[] packs = new Pack[N];
        for (int i = 0; i < N; i++) {
            packs[i] = new Pack(strs[i], sortedStrings[i]);
        }
        Arrays.sort(packs);
        List<String> ans = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            if (i > 0 && Objects.equals(packs[i - 1].sorted, packs[i].sorted) || i < N - 1 && Objects.equals(packs[i].sorted, packs[i + 1].sorted)) {
                ans.add(packs[i].orig);
            }
        }
        return ans;
    }

    public String lexicographicalSort(String s) { // only lower-case
        int R = 26;
        int N = s.length();
        int[] count = new int[R];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }
        String ans = "";
        for (int z = 0; z < R; z++) {
            for (int i = 0; i < count[z]; i++) {
                ans += (char) (z + 'a');
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        String[] test = {"inlt", "lint", "ilnt", "e"};
        List<String> l = sol.anagrams(test);
        for (String s : l) {
            System.out.println(s);
        }
    }
}
