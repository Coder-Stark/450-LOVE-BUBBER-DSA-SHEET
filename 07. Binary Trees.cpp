//BINARY TREES
//DFS = PREORDER, INORDER, POSTORDER TRAVERSALS
//BFS = LEVEL ORDER TRAVERSAL

#include<bits/stdc++.h>
using namespace std;


struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};
//201. LEVEL ORDER TRAVERSAL                                                              {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    vector<int> levelOrder(Node* node)
    {
        vector<int>ans;
        queue<Node*>q;
        q.push(node);
        
        if(node == NULL){
            return ans;
        }
        while(!q.empty()){
            Node* temp = q.front();
            q.pop();
            ans.push_back(temp->data);
            
            if(temp->left){
                q.push(temp->left);
            }
            if(temp->right){
                q.push(temp->right);
            }
        }
        return ans;
    }
};
/*
Input:
        10
     /      \
    20       30
  /   \
 40   60
Output:10 20 30 40 60
*/


//202. REVERSE LEVEL ORDER TRAVERSAL                                                {T.C = O(N), S.C = O(N)}
vector<int> reverseLevelOrder(Node *root)
{
    vector<int>ans;
    queue<Node*>q;
    stack<Node*>s;
    q.push(root);
    
    if(root == NULL){
        return ans;
    }
    
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        s.push(temp);
        
        //reverse pushing in queue first right then left
        if(temp->right){
            q.push(temp->right);
        }
        if(temp->left){
            q.push(temp->left);
        }
    }
    
    while(!s.empty()){
        Node* temp = s.top();
        ans.push_back(temp->data);
        s.pop();
    }
    return ans;
}
/*
Input :
       10
      /  \
     20   30
    / \ 
   40  60

Output: 40 60 20 30 10
Explanation:
Traversing level 2 : 40 60
Traversing level 1 : 20 30
Traversing level 0 : 10
*/


//203. HEIGHT  OF A TREE                                                                {T.C = O(N), S.C = O(H/N)}
class Solution{
    public:
    int height(struct Node* node){
        //base case
        if(node == NULL){
            return 0;               //height is 0
        }
        
        //LRN
        int left = height(node->left);
        int right = height(node->right);
        
        int ans = max(left, right) + 1;                     //1 = rootnode
        
        return ans;
    }
};
/*
Input:
  2
   \
    1
   /
 3
Output: 3   
*/


//204. DIAMETER OF A BINARY TREE                                                  {T.C = O(N), S.C = O(H/N)}
class Solution {
  public:
    pair<int,int>diameterFast(Node* root){
        pair<int,int>p = {0,0};            //initialization  pair<diameter,height>
        
        //base case
        if(root == NULL){
            return p;                      //diameter = height = 0
        }
        
        //LRN
        pair<int,int>left = diameterFast(root->left);
        pair<int,int>right = diameterFast(root->right);
        
        int op1 = left.first;                            //diameter ans in leftSubtree
        int op2 = right.first;                           //diameter ans in rightSubtree
        int op3 = left.second + right.second + 1;        //height of leftSubtree + height of rightSubtree + rootnode(1)
        
        pair<int,int>ans;
        ans.first = max(op1, max(op2, op3));
        ans.second = max(left.second, right.second) + 1;
        
        return ans;
    }
    int diameter(Node* root) {
        return diameterFast(root).first;
    }
};
/*
Input:
         10
        /   \
      20    30
    /   \ 
   40   60
Output: 4
*/


//205a. MIRROR OF A TREE                                                       {T.C = O(N), S.C = O(N/H)}
class Solution {
  public:
    void mirror(Node* node) {
        if(node == NULL){
            return;
        }
        
        //LRN
        mirror(node->left);
        mirror(node->right);
        
        swap(node->left, node->right);
    }
};
/*
Input:
      10
     /  \
    20   30
   /  \
  40  60
Output: 30 10 60 20 40
Explanation: The tree is
      10               10
    /    \  (mirror) /    \
   20    30    =>   30    20
  /  \                   /   \
 40  60                 60   40
The inroder traversal of mirror is
30 10 60 20 40.
*/


//205b. MIRROR OF A GIVEN NODE                                                 {T.C = O(N), S.C = O(N)}
class Solution
{
public:
    int solve(Node* originalNode, Node* mirrorNode, int target){
        //base case
        if(originalNode == NULL || mirrorNode == NULL){
            return -1;
        }
        if(originalNode->data == target){
            return mirrorNode->data;
        }
        
        //LRN
        int mirrorLeft = solve(originalNode->left, mirrorNode->right, target);
        int mirrorRight = solve(originalNode->right, mirrorNode->left, target);
        
        if(mirrorLeft != -1){
            return mirrorLeft;
        }
        else{
            return mirrorRight;
        }
    }
    int findMirror(Node *root, int target)
    {
        return solve(root, root, target);              //root = original, root = mirror
    }
};
/*
Input: 
          1        
        /   \       
       2     3     
      / \   / \    
     4   5 6   7   
and target = 4
Output: 7
Explanation: You can see below that the mirror 
node of 4 is 7.
          1       |       1
        /   \     |     /   \
       2     3    |    3     2
      / \   / \   |   / \   / \
     4   5 6   7  |  7   6 5   4
*/


//206. INORDER TRAVERSAL
struct TreeNode
{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
//USING RECURSION                                                             {T.C = O(N), S.C = O(N/H)//heigh of BT}
class Solution {
public:
    void inorder(vector<int>&ans, TreeNode* root){
        if(root){
            //LNR
            inorder(ans, root->left);
            ans.push_back(root->val);
            inorder(ans, root->right);
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans;
        inorder(ans, root);
        return ans;
    }
};

//ITERATIVE APPORACH                                                            {T.C = O(N), S.C = O(N/H)//heigh of BT}
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans;
        stack<TreeNode*>s;
        TreeNode* temp = root;

        while(true){
            if(temp){                            //temp != NULL
                s.push(temp);
                temp = temp->left;
            }else{
                if(s.empty()){
                    break;
                }
                else{
                    temp = s.top();
                    s.pop();
                    ans.push_back(temp->val);
                    temp = temp->right;
                }
            }
        }
        return ans;
    }
};
/*
Input: root = [1,null,2,3]
Output: [1,3,2]
*/


//207. PREORDER TRAVERSAL
//USING RECURSION                                                                {T.C = O(N), S.C = O(N/H)//heigh of BT}
class Solution {
public:
    void preorder(vector<int>&ans, TreeNode* root){
        if(root){
            //NLR
            ans.push_back(root->val);
            preorder(ans, root->left);
            preorder(ans, root->right);
        }
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ans;
        preorder(ans, root);
        return ans;
    }
};

//ITERATIVE APPORACH                                                            {T.C = O(N), S.C = O(N/H)//heigh of BT}
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ans;
        stack<TreeNode*>s;

        if(root == NULL){
            return ans;
        }
        
        s.push(root);

        while(!s.empty()){
            root = s.top();
            s.pop();
            ans.push_back(root->val);
            if(root->right){
                s.push(root->right);
            }
            if(root->left){
                s.push(root->left);
            }
        }
        return ans;
    }
};
/*
Input: root = [1,null,2,3]
Output: [1,2,3]
*/


//208. POST ORDER TRAVERSAL
//USING RECURSION                                                                {T.C = O(N), S.C = O(N/H)//heigh of BT}
class Solution {
public:
    void postorder(vector<int>&ans, TreeNode* root){
        if(root){
            //LRN
            postorder(ans, root->left);
            postorder(ans, root->right);
            ans.push_back(root->val);
        }
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int>ans;
        postorder(ans, root);
        return ans;
    }
};

//ITERATIVE APPORACH                                                            {T.C = O(N), S.C = O(N/H)//heigh of BT}
//copied
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }

        stack<TreeNode*> s;
        TreeNode* current = root;
        TreeNode* lastVisited = nullptr;

        while (!s.empty() || current != nullptr) {
            if (current != nullptr) {
                s.push(current);
                current = current->left;
            } else {
                TreeNode* peekNode = s.top();
                if (peekNode->right != nullptr && lastVisited != peekNode->right) {
                    // Go right if right child exists and hasn't been visited
                    current = peekNode->right;
                } else {
                    ans.push_back(peekNode->val);
                    lastVisited = peekNode;
                    s.pop();
                }
            }
        }

        return ans;
    }
};

/*
Input: root = [1,null,2,3]
Output: [3,2,1]
*/


//209. LEFT VIEW OF A TREE                                                                               {T.C = O(N), S.C = O(N)}
void solve(Node* root, vector<int>&ans, int level){
    //base case
    if(root == NULL){
        return;
    }
    
    //entered into next level
    if(level == ans.size()){
        ans.push_back(root->data);                   //push first element (NLR = preorder traversal)
    }
    
    solve(root->left, ans, level+1);
    solve(root->right, ans, level+1);
}
vector<int> leftView(Node *root)
{
   vector<int>ans;
   solve(root, ans, 0);
   return ans;
}
/*
Input:
   1
 /  \
3    2
Output: 1 3
*/


//210. RIGHT VIEW OF A BINARY TREE                                                                  {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    void solve(Node* root, vector<int>&ans, int level){
        //base case
        if(root == NULL){
            return;
        }
        
        //entered into next level
        if(level == ans.size()){
            ans.push_back(root->data);                   //push first element (NRL = reverse post order traversal)
        }
        
        solve(root->right, ans, level+1);               //right call first then left
        solve(root->left, ans, level+1);
    }
    vector<int> rightView(Node *root)
    {
        vector<int>ans;
        solve(root, ans, 0);
        return ans;
    }
};
/*
Input:
       1
    /    \
   3      2
Output: 1 2
*/


//211. TOP VIEW OF BINARY TREE                                                                          {T.C = O(N), S.C = O(N)}
//USING BFS TRAVERSAL
class Solution
{
    public:
    vector<int> topView(Node *root)
    {
        vector<int>ans;
        
        //base case
        if(root == NULL){
            return ans;
        }
        
        map<int,int>mp;                    //<vertical line , node->data>
        queue<pair<Node*, int>>q;          //<initial node from left, vertical line>
        
        q.push({root, 0});                 //initiallise
        while(!q.empty()){
            auto it = q.front();
            q.pop();
            
            Node* node = it.first;
            int line = it.second;
            
            if(mp.find(line) == mp.end()){               //not found (first/unique entry and neglect second entry)
                mp[line] = node->data;               
            }
            
            //recursive call
            if(node->left){
                q.push({node->left, line-1});              //line = <-- -2 -1 0 
            }
            if(node->right){
                q.push({node->right, line+1});            //line = 0 1 2 --- > 
            }
        }
        
        for(auto it : mp){
            ans.push_back(it.second);                   //push node->data
        }
        
        return ans;
    }
};
/*
Input:
       10
    /      \
  20        30
 /   \    /    \
40   60  90    100
Output: 40 20 10 30 100
*/


//212. BOTTOM VIEW OF BINARY TREE                                                                         {T.C = O(N), S.C = O(N)}
class Solution {
  public:
    vector <int> bottomView(Node *root)
    {
        vector<int>ans;
        
        //base case
        if(root == NULL){
            return ans;
        }
        
        map<int,int>mp;                    //<vertical line , node->data>
        queue<pair<Node*, int>>q;          //<initial node from left, vertical line>
        
        q.push({root, 0});                 //initiallise
        while(!q.empty()){
            auto it = q.front();
            q.pop();
            
            Node* node = it.first;
            int line = it.second;
            
            /* this is for top view
            if(mp.find(line) == mp.end()){               //not found (unique entry)
                mp[line] = node->data;               
            }
            */
            
            //this is for bottom view                   
            mp[line] = node->data;                       //(no first/unique entry and update second entry)
            
            //recursive call
            if(node->left){
                q.push({node->left, line-1});              //line = <-- -2 -1 0 
            }
            if(node->right){
                q.push({node->right, line+1});            //line = 0 1 2 --- > 
            }
        }
        
        for(auto it : mp){
            ans.push_back(it.second);                   //push node->data
        }
        
        return ans;
    }
};
/*
Input:
         10
       /    \
      20    30
     /  \
    40   60
Output: 40 20 60 30
*/


//213. ZIG ZAG TREE TRAVERSAL                                                                                {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    vector <int> zigZagTraversal(Node* root)
    {
    	vector<int>result;
    	//base case
    	if(root == NULL){
    	    return result;
    	}
    	
    	bool leftToRight = true;
    	queue<Node*> q;
    	q.push(root);
    	
    	while(!q.empty()){
    	    int sz = q.size();
    	    vector<int>ans(sz);
    	    
    	    //level process
    	    for(int i = 0 ; i < sz ; i++){
        	    Node* frontNode = q.front();
        	    q.pop();
    	        
    	        //normal insert and reverse insert
    	        int index = leftToRight ? i : sz-i-1;
    	        ans[index] = frontNode->data;
    	        
    	        if(frontNode->left){
    	            q.push(frontNode->left);
    	        }
    	        
    	        if(frontNode->right){
    	            q.push(frontNode->right);
    	        }
    	    }
        	//level direction change
        	leftToRight = !leftToRight;
        	for(auto it : ans){
        	    result.push_back(it);
        	}
    	}
    	return result;
    }
};
/*
Input:
           7
        /     \
       9       7
     /  \     /   
    8    8   6     
   /  \
  10   9 
Output:
7 7 9 8 8 6 9 10 
*/


//214. CHECK FOR BALANCED TREE                                                                          {T.C = O(N), S.C = O(H)}
class Solution{
    public:
    pair<bool, int>isBalancedFast(Node* root){
        
        //<bool, height>
        pair<bool,int>p = {true, 0};
        //base case
        if(root == NULL){
            return p;
        }
        
        pair<bool, int>left = isBalancedFast(root->left);
        pair<bool, int>right = isBalancedFast(root->right);
        
        bool leftAns = left.first;
        bool rightAns = right.first;
        bool diff = abs(left.second - right.second) <= 1;
        
        pair<bool, int>ans;
        ans.second = max(left.second, right.second) + 1;
        
        if(leftAns && rightAns && diff){
            ans.first = true;
        }
        else{
            ans.first = false;
        }
        return ans;
    }
    bool isBalanced(Node *root)
    {
        return isBalancedFast(root).first;
    }
};
/*
Input:
      1
    /
   2
    \
     3 
Output: 0
Explanation: The max difference in height
of left subtree and right subtree is 2,
which is greater than 1. Hence unbalanced
*/


//215. DIAGONAL TRAVERSAL OF BINARY TREE                                                               {T.C = O(N), S.C = O(N)}
vector<int> diagonal(Node *root)
{
    vector<int>ans;
    queue<Node*>q;
    
    //base case
    if(root == NULL){
        return ans;
    }
    
    q.push(root);
    while(!q.empty()){
        Node* frontNode = q.front();
        q.pop();
        
        while(frontNode){
            if(frontNode->left){
                q.push(frontNode->left);
            }
            ans.push_back(frontNode->data);
            frontNode = frontNode->right;
        }
    }
    return ans;
}
/*
Input :
            8
         /     \
        3      10
      /   \      \
     1     6     14
         /   \   /
        4     7 13
Output : 8 10 14 3 6 7 13 1 4
*/


//216. BOUNDARY TRAVERSAL OF BINARY TREE                                                           {T.C = O(N), S.C = (H)}
class Solution {
public:
    void traversalLeft(Node* root, vector<int>&ans){
        //base case
        if(root == NULL || root->left == NULL && root->right == NULL){     //leaf node exception
            return;
        }
        
        ans.push_back(root->data);
        if(root->left){
            traversalLeft(root->left, ans);
        }
        else{
            traversalLeft(root->right,ans);
        }
    }
    
    void traversalLeaf(Node* root, vector<int>&ans){
        //base case
        if(root == NULL){
            return;
        }
        
        if(root->left == NULL && root->right == NULL){
            ans.push_back(root->data);
        }
        
        traversalLeaf(root->left, ans);
        traversalLeaf(root->right, ans);
    }
    
    void traversalReverseRight(Node* root, vector<int>&ans){       
        //base case
        if(root == NULL || root->left == NULL && root->right == NULL){            //leaf node exception
            return;
        }
        
        if(root->right){
            traversalReverseRight(root->right, ans);
        }
        else{
            traversalReverseRight(root->left, ans);
        }
        
        //wapas ate samay print karo
        ans.push_back(root->data);
        
    }
    vector <int> boundary(Node *root)
    {
        vector<int>ans;
        
        //base case
        if(root == NULL){
            return ans;
        }
        
        ans.push_back(root->data);             //push root data
        
        //left call
        traversalLeft(root->left, ans);
        
        //leaf call (left, right)
        //left subtree
        traversalLeaf(root->left, ans);
        //right subtree
        traversalLeaf(root->right, ans);
        
        //reverse right call
        traversalReverseRight(root->right, ans);
        
        return ans;
    }
};
/*
Input:
        1 
      /   \
     2     3  
    / \   / \ 
   4   5 6   7
      / \
     8   9
   
Output: 1 2 4 8 9 6 7 3
*/


//217. CONSTRUCT BINARY TREE FROM STRING WITH BRACKET REPRESENTATION             {T.C = O(N), S.C = O(N)}
class Solution{
public:
    int i = 0;
    void solve(Node* root, string &s){
        if(i < s.size() && isdigit(s[i])){
            int sum = 0;
            while(i < s.size() && isdigit(s[i])){
                sum = sum*10 + s[i] - '0';
                i++;
            }
            root->data = sum;
        }
        if(i < s.size() && s[i] == '('){                                      //first '('
            root->left = new Node(0);
            i++;
            solve(root->left, s);
            
            if(root->left->data == 0){
                root->left = 0;
            }
        }
        if(i < s.size() && s[i] == '('){                                    //second '('
            root->right = new Node(0);
            i++;
            solve(root->right, s);
            
            if(root->right->data == 0){
                root->right = 0;
            }
        }
        if(i >= s.size() || s[i] == ')'){
            i++;
            return;
        }
    }
    Node *treeFromString(string s){
        Node* root = new Node(0);
        solve(root, s);
        return root;
    }
};
/*
Input: "1(2)(3)" 
Output: 2 1 3
Explanation:
           1
          / \
         2   3
Explanation: first pair of parenthesis contains 
left subtree and second one contains the right 
subtree. Inorder of above tree is "2 1 3".
*/


//218. CONVERT BINARY TREE INTO DOUBLY LINKED LIST                                                     {T.C = O(N), S.C = O(H)}
class Solution
{
    public: 
    void solve(Node* root, Node* &head, Node* &prev){
        //base case
        if(root == NULL){
            return;
        }
        
        //inorder (LNR)
        //l = left call
        solve(root->left, head, prev);
        
        //N = print Node
        if(prev == NULL){                   //OR prev == NULL
            head = root;
            prev = root;
        }else{
            prev->right = root;             //40->20
            root->left = prev;              //40<-20
            prev = prev->right;             //20->
        }
        
        //R= right call
        solve(root->right, head, prev);
    }
    Node * bToDLL(Node *root)
    {
        Node* head = NULL;
        Node* prev = NULL;
        solve(root, head, prev);
        return head;
    }
};
/*
Input:
       10
      /   \
     20   30
   /   \
  40   60
Output:
40 20 60 10 30 
30 10 60 20 40
Explanation:  DLL would be 
40<=>20<=>60<=>10<=>30.
*/


//219. TRANSFORM TO SUM TREE                                                                       {T.C = O(N), S.C = O(H)}
class Solution {
  public:
    int solve(Node * root){
        //base case
        if(root == NULL){
            return 0;
        }
        
        int a = solve(root->left);
        int b = solve(root->right);
        int x = root->data;
        root->data = a + b;
        return x+a+b;
    }
    void toSumTree(Node *node)
    {
        solve(node);
    }
};
/*
Input:
             10
          /      \
        -2        6
       /   \     /  \
     8     -4   7    5

Output:
            20
          /    \
        4        12
       /  \     /  \
     0     0   0    0

Explanation:

           (4-2+12+6)
          /           \
      (8-4)          (7+5)
       /   \         /  \
      0     0       0    0
*/


//220. CONSTRUCT BINARY TREE FROM INORDER AND PREORDER TRAVERSAL                       {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    int findPos(int arr[], int start, int end, int data){
        for(int i = start ; i <= end ; i++){
            if(arr[i] == data){
                return i;
            }
        }
        return -1;
    }
    Node* solve(int in[], int pre[], int inOrStart, int inOrEnd, int &preIndex){
        //base case
        if(inOrStart > inOrEnd){
            return NULL;
        }
        
        Node* root = new Node(pre[preIndex++]);
        
        int inOrIndex = findPos(in, inOrStart, inOrEnd, root->data);
        
        //Post order (LRN)
        //L = left call
        root->left = solve(in, pre, inOrStart, inOrIndex-1, preIndex);
        //R = right call
        root->right = solve(in, pre, inOrIndex+1, inOrEnd, preIndex);
        //N = print root
        return root;
    }
    Node* buildTree(int in[],int pre[], int n)
    {
        int preIndex = 0;
        return solve(in, pre, 0, n-1, preIndex);            //0  = inorderStart index, //n-1 = inorderEnd index
    }
};
/*
Input:
N = 6
inorder[] = {3 1 4 0 5 2}
preorder[] = {0 1 3 4 2 5}
Output: 3 4 1 5 2 0
Explanation: The tree will look like
       0
    /     \
   1       2
 /   \    /
3    4   5
*/


//221a. BINARY TREE TO BST                                                           {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
  public:
    void inOrBt(Node* root, vector<int>&v){
        //base case
        if(root == NULL){
            return;
        }
        
        //LNR
        inOrBt(root->left, v);
        v.push_back(root->data);
        inOrBt(root->right, v);
    }
    void inOrBst(Node* root, vector<int>v, int &i){
        //base case
        if(root == NULL){
            return;
        }
        
        //LNR
        inOrBst(root->left, v, i);
        root->data = v[i];
        i++;
        inOrBst(root->right, v, i);
    }
    Node *binaryTreeToBST (Node *root)
    {
        vector<int>v;
        inOrBt(root, v);
        
        sort(v.begin(), v.end());           //BST inorder is Sorted always
        int i = 0;
        inOrBst(root, v, i);
        
        return root;
    }
};
/*
Input:
          1
       /    \
     2       3
   /        
 4       
Output: 
1 2 3 4
Explanation:
The converted BST will be

        3
      /   \
    2     4
  /
 1
*/


//221b. MINIMUM SWAPS REQUIRED TO CONVERT BINARY TREE TO BST                      {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
  public:
    vector<int>ans;
    void inOr(vector<int>&a, int i){
        //base case
        if(i >= a.size()){
            return;
        }
        //inorder = LNR
        inOr(a, 2*i+1);
        ans.push_back(a[i]);
        inOr(a, 2*i+2);
        
        return;
    }
    int minSwaps(vector<int>&A, int n){
        
        inOr(A, 0);                     //0 = initial index
        vector<pair<int,int>>temp;      //<values,index>
        for(int i = 0 ; i < n ; i++){
            temp.push_back({ans[i], i});  
        }
        
        int count = 0;
        sort(temp.begin(), temp.end());
        for(int i = 0 ; i < n ; i++){
            if(i == temp[i].second){
                continue;
            }else{
                while(i != temp[i].second){
                    swap(temp[i], temp[temp[i].second]);
                    count++;
                }
            }
        }
        return count;
    }
};
/*
A[] = { 5, 6, 7, 8, 9, 10, 11 }
Output: 3
Explanation: 
*/


//222. SUM TREE                                                               {T.C = O(N), S.C = O(N)}
class Solution
{
public:
    int sum(Node* root){
        //base case
        if(root == NULL){
            return 0;
        }
        
        int lh = sum(root->left);
        int rh= sum(root->right);
        return root->data + lh + rh;
    }
    bool isSumTree(Node* root)
    {
        //base case
        if(root == NULL || root->left == NULL && root->right == NULL){
            return true;
        }
        
        bool left = isSumTree(root->left);
        bool right = isSumTree(root->right);
        bool check = root->data == sum(root->left) + sum(root->right);
        
        if(left && right && check){
            return true;
        }
        return false;
    }
};

//another apporoach
class Solution
{
    public:
    pair<bool,int> isSumTreeFast(Node *root){
        //base case
        if(root == NULL){
            pair<bool,int>p = make_pair(true, 0);
            return p;
        }
        
        //leaf node manage
        if(root->left == NULL && root->right == NULL){
            pair<bool,int>p = make_pair(true, root->data);
            return p;
        }
        
        pair<bool,int>leftAns = isSumTreeFast(root->left);
        pair<bool,int>rightAns = isSumTreeFast(root->right);
        
        
        bool left = leftAns.first;
        bool right = rightAns.first;
        
        bool cond = root->data == leftAns.second + rightAns.second;
        
        pair<bool,int>ans;
        
        if(left && right && cond){
            ans.first = true;
            ans.second = 2*root->data;
        }
        else{
            ans.first = false;
        }
        
        return ans;
    }
    bool isSumTree(Node* root)
    {
         return isSumTreeFast(root).first;
    }
};
/*
Input:

          10
        /    \
      20      30
    /   \ 
   10    10

Output: 0
Explanation:
The given tree is not a sum tree.
For the root node, sum of elements
in left subtree is 40 and sum of elements
in right subtree is 30. Root element = 10
which is not equal to 30+40.
*/


//223. LEAF AT SAME LEVEL                                                                        {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool solve(Node* root, int lvl, int &leafLvl) {
        // Base case
        if (root == NULL) {
            return true;
        }
        
        if (root->left == NULL && root->right == NULL) {
            // If this is the first leaf node encountered
            if (leafLvl == 0) {
                leafLvl = lvl;
                return true;           // Return true for leaf nodes
            }
            
            return (lvl == leafLvl);  // Check if the current leaf node is at the correct level
        }
        
        // Recursively check left and right subtrees
        return solve(root->left, lvl + 1, leafLvl) && solve(root->right, lvl + 1, leafLvl);
    }

    bool check(Node* root) {
        int lvl = 0, leafLvl = 0;
        return solve(root, lvl, leafLvl);
    }
};
/*
Input:
            10
          /    \
        20      30
       /  \        
     10    15

Output: 0

Explanation:
Leaves 10, 15 and 30 are not at same level.
*/


//224. DUPLICATE SUBTREE IN A BINARY TREE                                                {T.C = O(N) , S.C = O(N)}
class Solution {
  public:
    string solve(Node* root, unordered_map<string, int>&mp){
        //base case
        if(root == NULL){
            return "$";
        }
        
        string s = "#";
        //leaf node
        if(root->left == NULL && root->right == NULL){
            s = to_string(root->data);
            return s;
        }
        //NLR
        s += to_string(root->data);
        s += "#";
        s += solve(root->left, mp);
        s += "#";
        s += solve(root->right, mp);
        s += "#";
        mp[s]++;
        return s;
    }
    int dupSub(Node *root) {
        unordered_map<string, int>mp;
        solve(root, mp);
        for(auto it : mp){
            if(it.second >= 2){
                return 1;
            }
        }
        return 0;
    }
};
/*
Input : 
               1
             /   \ 
           2       3
         /   \       \    
        4     5       2     
                     /  \    
                    4    5
Output : 1
Explanation : 
    2     
  /   \    
 4     5
is the duplicate sub-tree.
*/


//225. CHECK MIRROR IN N-ARY TREES                                                                  {T.C = O(E), O(E)}
class Solution {
  public:
    int checkMirrorTree(int n, int e, int A[], int B[]) {
        
        unordered_map<int,stack<int>>mp;                //<value, value->other values (values == node->data)
        //n = 2*e, mapping of every 2nd element (value->value)
        for(int i = 0 ; i < 2*e ; i+= 2){               //A[] = {1 2 1 3 1 4 }, B[] = {1 4 1 3 1 2}
            mp[A[i]].push(A[i+1]);
        }
        
        //check in 2nd array
        for(int i = 0 ; i < 2*e ; i+=2){
            if(mp[B[i]].top() != B[i+1]){
                return 0;
            }
            mp[B[i]].pop();
        }
        return 1;
    }
};
/*
Input:
n = 3, e = 2
A[] = {1, 2, 1, 3}
B[] = {1, 2, 1, 3}
Output:
0
Explanation:
   1          1
 / \        /  \
2   3      2    3 
As we can clearly see, the second tree
isn't mirror image of the first.
*/


//226. SUM OF NODES ON THE LONGEST PATH FROM ROOT TO LEAF NODE                                           {T.C = O(N), S.C = O(N)}
class Solution
{
public:
    void solve(Node* root, int len, int &maxLen, int sum, int &maxSum){
        //base case
        if(root == NULL){          //leaf node
            if(len > maxLen){
                maxLen = len;
                maxSum = sum;
            }else if(len == maxLen){
                maxSum = max(sum, maxSum);
            }
            return;
        }
        
        //NLR
        sum += root->data;
        solve(root->left, len+1, maxLen, sum, maxSum);
        solve(root->right, len+1, maxLen, sum, maxSum);
    }
    int sumOfLongRootToLeafPath(Node *root)
    {
        int len = 0;
        int maxLen = 0;
        int sum = 0;
        int maxSum = 0;
        
        solve(root, len , maxLen, sum, maxSum);
        return maxSum;
    }
};

//another apporoach (error)                                                                        {T.C = O(N), S.C = O(N)}
class Solution
{
public:
    pair<int,int>solve(Node* root, vector<pair<int,int>>&p){
        //base case
        if(root == NULL){
            return {0, 0};
        }
        
        //LRN
        pair<int,int>left = solve(root->left, p);
        pair<int,int>right = solve(root->right, p);
        
        int height = max(left.first, right.first) + 1;
        int sum = max(left.second, right.second) + root->data;
        
        p.push_back({height, sum});
        
        return {height,sum};
    }
    int sumOfLongRootToLeafPath(Node *root)
    {
        vector<pair<int,int>>p;                         //<height, sum>
        solve(root, p);
        
        int maxSum = 0;
        for(auto it : p){
            maxSum = max(maxSum, it.second);
        }
        return maxSum;
    }
};
/*
Input: 
        4        
       / \       
      2   5      
     / \ / \     
    7  1 2  3    
      /
     6
Output: 13
Explanation:
        4        
       / \       
      2   5      
     / \ / \     
    7  1 2  3 
      /
     6

The highlighted nodes (4, 2, 1, 6) above are 
part of the longest root to leaf path having
sum = (4 + 2 + 1 + 6) = 13
*/


//227. CHECK IF GIVEN GRAPH IS TREE OR NOT


//228. LARGEST SUBTREE SUM IN A TREE                                               {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int dfs(Node* node, int& ans) {
        if (node == NULL) {
            return 0;
        }
        
        int left_sum = dfs(node->left, ans);
        int right_sum = dfs(node->right, ans);
        ans = max(ans, left_sum + right_sum + node->data);
        
        return left_sum + right_sum + node->data;            //curr sum
    }
    int findLargestSubtreeSum(Node* root) {
        int ans = INT_MIN;
        dfs(root, ans);
        return ans;
    }
};
/*
Input:
              1
            /   \
           2      3
          / \    / \
         4   5  6   7
Output: 28
Explanation: 
As all the tree elements are positive,
the largest subtree sum is equal to
sum of all tree elements.
*/


//229. MAXIMUM SUM OF NON-ADJACENT NODES                                                           {T.C = O(N), S.C = O(H)}
class Solution{
  public:
    pair<int, int>solve(Node* root){
        //base case
        if(root == NULL){
            return {0,0};
        }
        
        //LRN
        pair<int,int>left = solve(root->left);
        pair<int,int>right = solve(root->right);
        
        pair<int, int>res;                               //<incl(root), excl(root)>
        res.first = root->data + left.second + right.second;
        res.second = max(left.first, left.second) + max(right.first, right.second);
        
        return res;
    }
    int getMaxSum(Node *root) 
    {
        pair<int,int>p = solve(root);
        return max(p.first, p.second);
    }
};
/*
Input:
        1
      /   \
     2     3
    /     /  \
   4     5    6
Output: 16
Explanation: The maximum sum is sum of
nodes 1 4 5 6 , i.e 16. These nodes are
non adjacent.
*/


//230. PRINT ALL "K" SUM PATHS IN A BINARY TREE                                                       {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void solve(Node* root, vector<int>& path, int k) {
        // Base case
        if (root == NULL) {
            return;
        }
        
        path.push_back(root->data);
        solve(root->left, path, k);
        solve(root->right, path, k);
        
        int f = k;
        for (int j = path.size() - 1; j >= 0 ; j--) {
            f -= path[j];
            if (f == 0) {
                for (int m = j ; m < path.size() ; m++) {
                    cout << path[m] << " ";
                }
                cout << endl;
            }
        }
        path.pop_back();
    }

    void sumK(Node* root, int k) {
        vector<int> path;
        solve(root, path, k);
    }
};
/*
Input: 
Tree = 
           1
        /     \
      3        -1
    /   \     /   \
   2     1   4     5                        
        /   / \     \                    
       1   1   2     6    
K = 5                    
The following paths sum to K.  
Output:
3 2 
3 1 1 
1 3 1 
4 1 
1 -1 4 1 
-1 4 2 
5 
1 -1 5 
*/

//23Ob. K SUM PATHS                                                                             {T.C = O(N), S.C = O(N)}
class Solution{
  public:
    void solve(Node* root, int k, unordered_map<int, int>& prefixSumCount, int currentSum, int& count) {
        if (root == NULL) {
            return;
        }
        
        currentSum += root->data;
        if (prefixSumCount.find(currentSum - k) != prefixSumCount.end()) {
            count += prefixSumCount[currentSum - k];
        }
        //if not found
        prefixSumCount[currentSum]++;
        
        solve(root->left, k, prefixSumCount, currentSum, count);
        solve(root->right, k, prefixSumCount, currentSum, count);
        
        prefixSumCount[currentSum]--;
    }
    int sumK(Node *root,int k)
    {
        unordered_map<int, int>prefixSumCount;
        prefixSumCount[0] = 1;            //correctly count paths that start from the root node and immediately satisfy the k requirement.
        int count = 0;
        solve(root, k, prefixSumCount, 0, count);              //0 = currSum
        return count;
    }
};
/*
Input: 
Tree = 
           1
        /     \
      3        -1
    /   \     /   \
   2     1   4     5                        
        /   / \     \                    
       1   1   2     6    
K = 5                    
Output: 8
Explanation:
The following paths sum to K.  
3 2 
3 1 1 
1 3 1 
4 1 
1 -1 4 1 
-1 4 2 
5 
1 -1 5 
*/


//231. LOWEST COMMON ANCESTOR IN A BINARY TREE                                        {T.C = O(N), S.C = O(H)}
class Solution
{
    public:
    Node* lca(Node* root ,int n1 ,int n2 )
    {
       //base case
       if(root == NULL){
           return NULL;
       }
       
       //NLR
       if(root->data == n1 || root->data == n2){
           return root;
       }
       
       Node* leftAns = lca(root->left, n1, n2);
       Node* rightAns = lca(root->right, n1, n2);
       
       if(leftAns != NULL && rightAns != NULL){
           return root;
       }
       else if(leftAns == NULL && rightAns != NULL){
           return rightAns;
       }
       else if(leftAns != NULL && rightAns == NULL){
           return leftAns;
       }
       else{   //leftAns == NULL && rightAns == NULL
           return NULL;
       }
    }
};
/*
Input:
n1 = 3 , n2 = 4
           5    
          /    
         2  
        / \  
       3   4
Output: 2
Explanation:
LCA of 3 and 4 is 2. 
*/


//232. FIND DISTANCE BETWEEN 2 NODES IN BINARY TREE                              {T.C = O(N), S.C = O(H)}
class Solution{
    public:
    //finding LCA 
    Node* lca (Node* root, int a , int b){
        //base case
        if(root == NULL){
            return NULL;
        }
        
        //NLR
        if(root->data == a || root->data == b){
            return root;
        }
        Node* leftAns = lca(root->left, a, b);
        Node* rightAns = lca(root->right, a, b);
        
        //return back
        if(leftAns != NULL && rightAns != NULL){
            return root;
        }
        else if(leftAns != NULL && rightAns == NULL){
            return leftAns;
        }
        else if(leftAns == NULL && rightAns != NULL){
            return rightAns;
        }
        return NULL;
    }
    
    //finding height of tree from LCA node to actual node
    int solve(Node* root, int &val){
        //base case
        if(root == NULL){
            return 0;
        }
        
        //NLR
        if(root->data == val){
            return 1;
        }
        int left = solve(root->left, val);
        int right = solve(root->right, val);
        
        //return back
        if(left == NULL && right == NULL){
            return 0;
        }
        
        return left + right + 1;                      //1 = root node
    }
    
    int findDist(Node* root, int a, int b) {
        Node* LCA = lca(root, a, b);              //finding lowest common ancestor
        int leftDis = solve(LCA, a);              //finding distance from LCA to actual value
        int rightDis = solve(LCA, b);
        
        int ans = leftDis + rightDis - 2;                  //1 extra from both 
        
        return ans;
    }
};
/*
Input:
        1
      /  \
     2    3
a = 2, b = 3
Output: 2
Explanation: The tree formed is:
       1
     /   \ 
    2     3
We need the distance between 2 and 3.
Being at node 2, we need to take two
steps ahead in order to reach node 3.
The path followed will be:
2 -> 1 -> 3. Hence, the result is 2. 
*/


//233. KTH ANCESTOR IN A TREE                                                {T.C = O(N), S.C = O(H)}
Node *solve(Node *root, int&k , int&node){
    //base case
    if(root == NULL){
        return NULL;
    }
    if(root->data == node){
        return root;
    }
    
    Node *leftAns = solve(root->left, k, node);
    Node *rightAns = solve(root->right, k, node);
    
    //return back to upward
    if(leftAns != NULL && rightAns == NULL){
        k--;
        if(k <= 0){
            //answer lock
            k = INT_MAX;
            return root;
        }
        return leftAns;
    }
    if(leftAns == NULL && rightAns != NULL){
        k--;
        if(k <= 0){
            //answer lock
            k = INT_MAX;
            return root;
        }
        return rightAns;
    }
    return NULL;
}
int kthAncestor(Node *root, int k, int node)
{
    Node *ans = solve(root, k, node);
    if(ans == NULL || ans->data == node){
        return -1;
    }
    else{
        return ans->data;
    }
}
/*
Input:
k=1 
node=3
      1
    /   \
    2     3

Output:
1
Explanation:
K=1 and node=3 ,Kth ancestor of node 3 is 1.
*/


//234. FIND ALL DUPLICATES SUBTREE IN A BINARY TREE


//235. CHECK IF TREE IS ISOMORPHIC                                            {T.C = O(N), S.C = O(N)}
class Solution{
  public:
    // Return True if the given trees are isomotphic. Else return False.
    bool isIsomorphic(Node *root1,Node *root2)
    {
        if(root1 == NULL && root2 == NULL){           //root is null
            return true;
        }
        if(root1 == NULL || root2 == NULL){           //atleast one is different
            return false;
        }
        if(root1->data != root2->data){               //root node data different
            return false;
        }
        
        //both trees identical
        bool a = isIsomorphic(root1->left, root2->left) && isIsomorphic(root1->right , root2->right);
        //both trees identical after swaping nodes
        bool b = isIsomorphic(root1->left, root2->right) && isIsomorphic(root1->right, root2->left);
        
        return (a || b);
    }
};
/*
Input:
T1    1     T2:    1
    /  \         /   \
   2    3       3     2
  /                    \
  4                     4
Output: Yes
*/


/*-------------------------------------------------   THE END ----------------------------------------------------------*/