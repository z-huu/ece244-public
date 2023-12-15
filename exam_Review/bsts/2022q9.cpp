
using namespace std;

/*

    Now, you are asked to complete the function is_symmetric. It should return 
    true if and only if the root is a symmetric tree. You should fill out the 
    recursive helper function is_symmetric_helper to make is_symmetric work 
    as expected. Hint: you should write less than 15 lines of code.

*/

/* Definition of the tree node */
class TreeNode {
 public:
  int data;
  TreeNode* left;
  TreeNode* right;
};

/* Recursive helper */
bool is_symmetric_helper(TreeNode* left, TreeNode* right);

bool is_symmetric(TreeNode* root) {
  if (root == nullptr) {
    return true;
  }
  return is_symmetric_helper(root->left, root->right);
}

// Implementation for Submission

bool is_symmetric_helper(TreeNode* left, TreeNode* right) {

    //To check for symmetry, we should do the following.

    //Should be returning nodes at some point to previous function calls.

    if  ( (left == nullptr) && (right == nullptr) ) { // Arrived at a leaf node

      return true;

    }

    if ((left->data == right->data)) {
      return ((is_symmetric_helper(left->left, right->right))
      &&(is_symmetric_helper(right->left, left->right)));
    }

    // Honestly, I'm stumped.
}