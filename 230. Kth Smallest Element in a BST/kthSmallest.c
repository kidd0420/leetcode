/*********************************************************************
 * Given a binary search tree, 
 * write a function kthSmallest to find the kth smallest element in it.
 * 
 * Note: 
 * You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
 * 
 * Example 1:
 * Input: root = [3,1,4,null,2], k = 1
 *    3
 *   / \
 *  1   4
 *   \
 *    2
 * Output: 1
 * 
 * Example 2:
 * Input: root = [5,3,6,2,4,null,null,1], k = 3
 *       5
 *       / \
 *      3   6
 *     / \
 *    2   4
 *   /
 *  1
 * Output: 3
 * 
 * Follow up:
 * What if the BST is modified (insert/delete operations) 
 * ften and you need to find the kth smallest frequently? 
 * How would you optimize the kthSmallest routine?
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int ReturnSmallK(struct TreeNode* root, int* k)
{
	int ret;

	if (root->left != NULL) {
		if ((ret = ReturnSmallK(root->left, k)) != -1)
			return ret;
	}

	if ((--(*k)) == 0)
		return root->val;

	if (root->right != NULL) {
		if ((ret = ReturnSmallK(root->right, k)) != -1)
			return ret;
	}

	return -1;
}


int kthSmallest(struct TreeNode* root, int k) {
    return ReturnSmallK(root, &k);
}


int main()
{
    int output;

    return 0;
}