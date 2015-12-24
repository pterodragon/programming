#include <bits/stdc++.h>
using namespace std;

class SegmentTreeNode {
public:
	int start, end, count;
	SegmentTreeNode *left, *right;
	SegmentTreeNode(int start, int end, int count) {
		this->start = start;
		this->end = end;
		this->count = count;
		this->left = this->right = NULL;
	}
	static SegmentTreeNode* build(int start, int end, vector<int> const& A) {
		if (start > end)
			return nullptr;
		SegmentTreeNode* root = new SegmentTreeNode(start, end, 0);
		helper(root, A);
		return root;
	}

	static void helper(SegmentTreeNode* node, vector<int> const& A) {
		if (node->start == node->end) {
			node->count = A[node->start];
			return;
		}
		node->left = new SegmentTreeNode(node->start, (node->start + node->end) / 2, 0);
		node->right = new SegmentTreeNode((node->start + node->end) / 2 + 1, node->end, 0);
		helper(node->left, A);
		helper(node->right, A);
		node->count = (node->left ? node->left->count : 0) + (node->right ? node->right->count : 0);
	}

	void print() const {
		printf("(%d, %d): count = %d\n", start, end, count);
		if (left)
			left->print();
		if (right)
			right->print();
	}

};

class Solution {
public:
	/**
	 *@param root, start, end: The root of segment tree and
	 *                         an segment / interval
	 *@return: The count number in the interval [start, end]
	 */
	int query(SegmentTreeNode *root, int start, int end) {
		if (start > end || root == nullptr)
			return 0;
		if (root->start == start && root->end == end)
			return root->count;
		auto left_up = (root->start + root->end) / 2;
		auto right_low = left_up + 1;
		int result = 0;
		if (start <= left_up) {
			printf("goes to left\n");
			printf("[%d, %d], (s, e) = (%d, %d)\n", root->start, root->end, start, end);
			printf("(lu, rl) = (%d, %d)\n", left_up, right_low);
			result += query(root->left, start, left_up);
		}
		if (end >= right_low) {
			printf("goes to right\n");
			printf("[%d, %d], (s, e) = (%d, %d)\n", root->start, root->end, start, end);
			printf("(lu, rl) = (%d, %d)\n", left_up, right_low);
			result += query(root->right, right_low, end);
		}
		return result;
	}
};

//"[0,14,count=3]
//[0,7,count=2]
//[8,14,count=1]
//[0,3,count=2]
//[4,7,count=0]
//[8,11,count=0]
//[12,14,count=1]
//[0,1,count=1]
//[2,3,count=1]
//[4,5,count=0]
//[6,7,count=0]
//[8,9,count=0]
//[10,11,count=0]
//[12,13,count=0]
//[14,14,count=1]
//[0,0,count=1]
//[1,1,count=0]
//[2,2,count=1]
//[3,3,count=0]
//[4,4,count=0]
//[5,5,count=0]
//[6,6,count=0]
//[7,7,count=0]
//[8,8,count=0]
//[9,9,count=0]
//[10,10,count=0]
//[11,11,count=0]
//[12,12,count=0]
//[13,13,count=0]
//", [query(1,1),query(2,12),query(1,16),query(8,13)]

int main() {
	vector<int> A { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	auto tree = SegmentTreeNode::build(0, 14, A);
	tree->print();
	Solution sol;
	array<pair<int, int>, 4> queries = { pair<int, int>{ 1, 1 }, pair<int, int>{ 2, 12 }, pair<int, int>{ 1, 16 }, pair<int, int>{ 8, 13 } };
	for (auto const& pair : queries) {
		auto ans = sol.query(tree, pair.first, pair.second);
		printf("query(%d, %d) = %d\n", pair.first, pair.second, ans);
	}
	return 0;
}
