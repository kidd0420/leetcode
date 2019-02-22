#include "stdio.h"
#include "stdbool.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool hasPathSum(struct TreeNode* root, int sum)
{
    if (root == NULL)
        return 0;

    sum -= root->val;

    if (root->left != NULL) {
        if (hasPathSum(root->left, sum))
            return 1;
    } else if ((sum == 0) && (root->right == NULL)) {
        return 1;
    }

    if (root->right != NULL) {
        if (hasPathSum(root->right, sum))
            return 1;
    } else if ((sum == 0) && (root->left == NULL)) {
        return 1;
    }

    return 0;
}

int main (void)
{

}

