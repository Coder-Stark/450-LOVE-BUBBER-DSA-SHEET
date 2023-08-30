//BINARY SEARCH TREE (BST)

#include<bits/stdc++.h>
using namespace std;


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//236. SEARCH IN A BST                                                             {T.C = THETA(LOGN), S.C = O(N)}
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == NULL){
            return NULL;
        }
        if(root->val == val){
            return root;
        }

        if(root->val > val){
            return searchBST(root->left, val);
        }else{
            return searchBST(root->right, val);
        }
    }
};
/*
Input: root = [4,2,7,1,3], val = 2
Output: [2,1,3]
*/


//237. DELETE NODE IN A BST                                                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    TreeNode* minValue(TreeNode* root){
        TreeNode* temp = root;
        while(temp->left){
            temp = temp->left;
        }
        return temp;
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        //base case
        if(root == NULL){
            return root;
        }

        if(root->val == key){
            //0 child /leaf node delete
            if(root->left == NULL && root->right == NULL){
                delete root;
                return NULL;
            }

            //1 child either left or right node delete
            if(root->left != NULL && root->right == NULL){
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            if(root->left == NULL && root->right != NULL){
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }

            //2 child node delete
            TreeNode* temp = minValue(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
            return root;
        }
        else if(root->val > key){           //val present in left subtree
            root->left = deleteNode(root->left, key);
            return root;
        }else{ //root->val < key            //val present in right subtree
            root->right = deleteNode(root->right,  key);
            return root;
        }
        return root;
    }
};
/*
Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.
*/


struct Node
{
    int key;
    int data;
    struct Node* next;
    struct Node* left;
    struct Node* right;
    Node(int data){
        this->data = data ;
        this->left = NULL;
        this->right = NULL;
    }
};
//238a. MINIMUM ELEMENT IN BST                                                 {T.C = O(N), S.C = O(1)}
int minValue(Node* root) {
    if(root == NULL){
        return -1;
    }
    Node* temp = root;
    while(temp->left){
        temp = temp->left;
    }
    return temp->data;
}
/*
Input:
           5
         /    \
        4      6
       /        \
      3          7
     /
    1
Output: 1
*/


//238b. MAXIMUM ELEMENT IN BST                                                         {T.C = O(N), S.C = O(1)}
int maxValue(Node* root) {
    if(root == NULL){
        return -1;
    }
    Node* temp = root;
    while(temp->right){
        temp = temp->right;
    }
    return temp->data;
}
/*
Input:
           5
         /    \
        4      6
       /        \
      3          7
     /
    1
Output: 7
*/


//239. PREDECESSOR AND SUCCESSOR                                                        {T.C = O(N), S.C = O(H)}
class Solution
{
    public:
    void findPreSuc(Node* root, Node*& pre, Node*& suc, int x)
    {
        Node* temp = root;
        
        //finding succ
        while(temp){
            if(temp->key <= x){
                temp = temp->right;
            }else{
                suc = temp;         //potential candidate for successor
                temp = temp->left;
            }
        }
        temp = root;                       //reset temp
        //finding pred
        while(temp){
            if(temp->key >= x){
                temp = temp->left;
            }
            else{
                pre = temp;         //potential candidate for predecessor
                temp = temp->right;
            }
        }
    }
};

//another approach
pair<int,int> predecessorSuccessor(Node* root, int key)
{
    Node*temp = root;
    int pred = -1;
    int succ = -1;

    //find key
    while(temp->data != key){
        if(temp->data > key){
            succ = temp->data;
            temp = temp->left;
        }
        else{
            pred = temp->data;
            temp = temp->right;
        }
    }

    //pred
    Node*leftTree = temp->left;
    while(leftTree != NULL){
        pred = leftTree->data;
        //max value of left subtree
        leftTree = leftTree->right;
    }

    //succ
    Node*rightTree = temp->right;
    while(rightTree != NULL){
        succ = rightTree->data;
        //min value of right subtree
        rightTree = rightTree->left;
    }

    pair<int,int>ans = make_pair(pred, succ);
    return ans;
}
/*
Input:
        10
      /   \
     2    11
   /  \ 
  1    5
      /  \
     3    6
      \
       4
key = 8
Output: 
6 10
Explanation: 
In the given BST the inorder predecessor of 8 is 6 and inorder successor of 8 is 10.
*/


//240. CHECK FOR BST                                                               {T.C = O(N), S.C = O(H)}
class Solution
{
    public:
    bool solve(Node* root, int minVal ,int maxVal){
        //base case
        if(root == NULL){
            return true;
        }
        if(root->data >= maxVal || root->data <= minVal){
            return false;
        }
        bool ans = solve(root->left, minVal, root->data) && solve(root->right, root->data, maxVal);    
        
        return ans;
    }
    bool isBST(Node* root) 
    {
        return solve(root, INT_MIN, INT_MAX);
    }
};
/*
Input:
  2
   \
    7
     \
      6
       \
        5
         \
          9
           \
            2
             \
              6
Output: 0 
Explanation: 
Since the node with value 7 has right subtree 
nodes with keys less than 7, this is not a BST.
*/


//241. POPULATE INORDER SUCCESSOR FOR ALL NODES                                         {T.C = O(N), S.C = O(N)}
class Solution
{
public:
    void solve(Node* root, Node* &prev){
        //base case
        if(root == NULL){
            return;
        }
        //LNR
        solve(root->left, prev);
        
        if(prev){
            prev->next = root;
        }
        prev = root;
        
        solve(root->right, prev);
    }
    void populateNext(Node *root)
    {
        Node* prev = NULL;
        solve(root, prev);
    }
};
/*
Input:
           10
       /  \
      8    12
     /
    3
  

Output: 3->8 8->10 10->12 12->-1
Explanation: The inorder of the above tree is :
3 8 10 12. So the next pointer of node 3 is 
pointing to 8 , next pointer of 8 is pointing
to 10 and so on.And next pointer of 12 is
pointing to -1 as there is no inorder successor 
of 12.
*/


//242. LOWEST COMMON ANCESTOR IN A BST                                                  {T.C = O(N), S.C = O(N)}
//same as BT
class Solution{
    public:
        Node* LCA(Node *root, int n1, int n2)
        {
            //base case
            if(root == NULL){
                return root;
            }
            
            //NLR(NOT SPECIFIC)
            if(root->data == n1 || root->data == n2){
                return root;
            }
            Node* leftAns = LCA(root->left, n1, n2);
            Node* rightAns = LCA(root->right, n1, n2);
            
            if(leftAns != NULL && rightAns != NULL){
                return root;
            }
            else if(leftAns != NULL && rightAns == NULL){
                return leftAns;
            }
            else if(leftAns == NULL && rightAns != NULL){
                return rightAns;
            }
            else{
                return NULL;
            }
        }

};

//using BST property                                                             {T.C = O(H), S.C = O(H)}
class Solution{
    public:
        Node* LCA(Node *root, int n1, int n2)
        {
            //base case
            if(root == NULL){
                return NULL;
            }
            
            //NLR(NOT SPECIFIC)
            int curr = root->data;
            if(curr > n1 && curr > n2){
                return LCA(root->left, n1, n2);
            }
            if(curr < n1 && curr < n2){
                return LCA(root->right, n1, n2);
            }
            return root;
        }

};
/*
Input:
              5
            /   \
          4      6
         /        \
        3          7
                    \
                     8
n1 = 7, n2 = 8
Output: 7
*/



//243a. CONSTRUCT BST FROM PREORDER TRAVERSAL                                          {T.C = O(N), S.C = O(H)}
class Solution {
public:
    TreeNode* solve(vector<int>&preorder, int &i , int bound){
        //base case
        if(i == preorder.size() || preorder[i] > bound){
            return NULL;
        }

        TreeNode* root = new TreeNode(preorder[i++]);
        root->left = solve(preorder, i, root->val);
        root->right = solve(preorder, i, bound);
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return solve(preorder, i, INT_MAX);                   //INT_MAX == BOUND
    }
};
/*
Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]
Example 2:
*/

//243b. CONSTRUCT BST FROM POSTORDER TRAVERSAL                                      {T.C = O(N), S.C = O(H)}
//reverse of preorder
TreeNode* solve(int post[], int &i , int bound){
    //base case
    if(i < 0 || post[i] < bound){                            
        return NULL;
    }
    
    TreeNode* root = new TreeNode(post[i--]);
    root->right = solve(post, i , root->val);
    root->left = solve(post, i, bound);
    
    return root;
}
TreeNode *constructTree (int post[], int size)
{
    int i = size-1;
    return solve(post, i, INT_MIN);
}
/*
Input:
6
1 7 5 50 40 10
Output:
1 5 7 10 40 50
*/


//244. CONVERT BINARY TREE TO BST                                                {T.C = O(N*LOGN), S.C = O(N)}
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


//245. NORMAL BST TO BALANCED BST                                                 {T.C = O(N), S.C = O(N)}
void inOr(Node* root, vector<int>&v){
    //base case
    if(root == NULL){
        return ;
    }
    
    //LNR
    inOr(root->left, v);
    v.push_back(root->data);
    inOr(root->right, v);
}
Node* inOrToBst(vector<int>&v, int s, int e){
    //base case
    if(s > e){
        return NULL;
    }
    
    int mid = (s + e)/2;
    
    Node* root = new Node(v[mid]);
    root->left = inOrToBst(v, s, mid-1);
    root->right = inOrToBst(v, mid+1, e);
    
    return root;
}
Node* buildBalancedTree(Node* root)
{
    //approach tree - > vector then find mid and adjust accordingly and again vector->tree
    vector<int>v;                                 
	inOr(root, v);
	
	int sz = v.size()-1;
	return inOrToBst(v, 0, sz);                  //vector, initial index, final index
}
/*
Input:
       30
      /
     20
    /
   10
Output:
     20
   /   \
 10     30

Input:
         4
        /
       3
      /
     2
    /
   1
Output:
      3            3           2
    /  \         /  \        /  \
   1    4   OR  2    4  OR  1    3   OR ..
    \          /                   \
     2        1                     4 
*/


//246. MERGE 2 BST'S
//TLE                                                                            {T.C = O(N*LOGN), S.C = O(N)}            
class Solution
{
    public:
    void inOr(Node* root, vector<int>&v){
        //base case
        if(root == NULL){
            return;
        }
        //LNR
        inOr(root->left, v);
        v.push_back(root->data);
        inOr(root->right, v);
    }
    
    vector<int> merge(Node *root1, Node *root2)
    {
        vector<int>v;
        inOr(root1,v);
        inOr(root2, v);
        
        sort(v.begin(), v.end());
        return v;
    }
};

//optimized approach                                                          {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    void inOr(Node* root, vector<int>&v){
        //base case
        if(root == NULL){
            return;
        }
        //LNR
        inOr(root->left, v);
        v.push_back(root->data);
        inOr(root->right, v);
    }
    vector<int>mergeBST(vector<int>&a, vector<int>&b){
        vector<int>ans(a.size() + b.size());
        
        int i = 0, j = 0, k = 0;
        while(i < a.size() && j < b.size()){
            if(a[i] < b[j]){
                ans[k] = a[i];
                k++, i++;
            }
            else{ //(a[i] > b[j])
                ans[k] = b[j];
                k++, j++;
            }
        }
        while(i < a.size()){
            ans[k] = a[i];
            k++, i++;
        }
        while(j < b.size()){
            ans[k] = b[j];
            k++, j++;
        }
        
        return ans;
    }
    Node* inOrToBST(vector<int>&v, int s, int e){
        //base case
        if(s > e){
            return NULL;
        }
        
        int mid = (s + e)/2;
        
        Node* root = new Node(v[mid]);
        root->left = inOrToBST(v, s, mid-1);
        root->right = inOrToBST(v, mid+1, e);
        
        return root;
    }
    vector<int> merge(Node *root1, Node *root2)
    {
        vector<int>v1, v2;
        inOr(root1,v1);
        inOr(root2, v2);
        
        vector<int> v = mergeBST(v1, v2);
        return v;

        /* for converting vector to bst
        int sz = v.size()-1;
        //vector to bst
        return inOrToBST(v, 0, sz);
        */
    }
};
/*
Input:
BST1:
       5
     /   \
    3     6
   / \
  2   4  
BST2:
        2
      /   \
     1     3
            \
             7
            /
           6
Output: 1 2 2 3 3 4 5 6 6 7
Explanation: 
After merging and sorting the
two BST we get 1 2 2 3 3 4 5 6 6 7.
*/


//247. KTH LARGEST ELEMENT IN BST                                                  {T.C = O(N), S.C = O(N) + vector space}
class Solution
{
    public:
    void solve(Node* root, vector<int>&v, int k){
        //base case
        if(root == NULL){
            return;
        }
        
        //LNR         //for reverse sorted vector of bst
        solve(root->right, v, k);
        if(k > 0){
            v.push_back(root->data);
            k--;
        }
        solve(root->left, v, k);
    }
    int kthLargest(Node *root, int K)
    {
        vector<int>v;
        solve(root, v, K);
        
        if(K > v.size()) {
            return -1; // Handle the case where K is greater than the number of nodes
        }
        return v[K-1];
    }
};

//optimized approach                                                               {T.C = O(N), S.C = O(H / 1)}
class Solution
{
    public:
    void solve(Node* root, int k, int count, int ans){
        //base case
        if(root == NULL){
            return;
        }
        
        //LNR         //for reverse sorted vector of bst
        solve(root->right, k, count, ans);
        count++;
        if(count == k){
            ans = root->data;
            return;
        }
        solve(root->left, k, count, ans);
    }
    int kthLargest(Node *root, int K)
    {
        int count = 0;
        int ans = -1;
        solve(root, K, count, ans);
        
        return ans;
    }
};
/*
Input:
      4
    /   \
   2     9
k = 2 
Output: 4
*/


//248. KTH SMALLEST ELEMENT IN BST                                                    {T.C = O(N), S.C = O(H / 1)}
class Solution {
  public:
    void solve(Node* root, int k , int &count, int&ans){
        //base case
        if(root == NULL){
            return;
        }
        
        //LNR                //sorted vector in bst
        solve(root->left, k , count, ans);
        count++;
        if(count == k){
            ans = root->data;
            return;
        }
        solve(root->right, k, count, ans);
    }
    int KthSmallestElement(Node *root, int K) {
        int count = 0;
        int ans = -1;
        
        solve(root, K, count, ans);
        
        return ans;
    }
};
/*
Input:
      4
    /   \
   2     9
k = 2 
Output: 4
*/


//249. BROTHERS FROM DIFFERENT ROOTS / COUNT PAIRS FROM 2 BST WHOSE SUM IS EQUAL TO GIVEN VALUE 'X'
//BRUTE FORCE APPROACH                                                        {T.C = O(N), S.C = O(N)}
class Solution
{
public:
    void solve(Node* root, vector<int>&v){
        //base case
        if(root == NULL){
            return;
        }
        
        //LNR
        solve(root->left, v);
        v.push_back(root->data);
        solve(root->right, v);
    }
    int countPairs(Node* root1, Node* root2, int x)
    {
        vector<int>v1,v2;
        solve(root1, v1 );
        solve(root2, v2);
        
        unordered_map<int, int>mp;
        for(auto i : v1){
            mp[i]++;
        }
        
        int count = 0;
        for(int i = 0 ; i < v2.size() ; i++){
            if(mp.find(x-v2[i]) != mp.end()){         //another pair exist in mp
                count++;
            }
        }
        return count;
    }
};
//another approach                                                           {T.C = O(N*H), S.C = O(H / 1)}
class Solution
{
public:
    bool search(Node* root2,int val){
        //base case
        if(root2 == NULL){
            return false;
        }
        if(root2->data == val){
            return true;
        }
        bool x = false, y = false;
        if(val < root2->data){
            x = search(root2->left, val);
        }else{
            y = search(root2->right, val);
        }
        return x or y;
    }
    void solve(Node* root1, Node* root2, int &x, int &count){
        //base case
        if(root1 == NULL){
            return;
        }
        //LNR
        solve(root1->left, root2, x , count);
        if(search(root2, x - (root1->data))){
            count++;
        }
        solve(root1->right, root2, x, count);
    }
    int countPairs(Node* root1, Node* root2, int x)
    {
        int count = 0;
        solve(root1, root2, x, count);
        return count;
    }
};
/*
Input:
BST1:
       5
     /   \
    3     7
   / \   / \
  2   4 6   8

BST2:
       10
     /    \
    6      15
   / \    /  \
  3   8  11   18

x = 16
Output:
3
Explanation:
*/


//250. MEDIAN OF A BST                                                                {T.C = O(N), S.C = O(H)}
void countNodes(Node* root, int &count){
    //base case
    if(root == NULL){
        return;
    }
    //LNR
    countNodes(root->left, count);
    count++;
    countNodes(root->right, count);
}
void solve(Node* root, Node* &curr, Node* &prev, int &c , int x, bool &found){
    //base case
    if(root == NULL){
        return;
    }
    //LNR
    solve(root->left, curr, prev, c, x, found);
    if(prev == NULL){
        prev = root;
        c++;
    }
    else if(c == x){
        c++;
        curr = root;
        found = 1;
        return;
    }else if(found == 0){
        c++;
        prev = root;
    }
    solve(root->right, curr, prev, c, x , found);
}
float findMedian(struct Node *root)
{
    int count = 0;
    countNodes(root, count);
    Node* curr = NULL;
    Node* prev = NULL;
    int c = 1;
    int x = count/2 + 1;
    bool found = 0;
    solve(root, curr, prev, c, x, found);
    if(count & 1){
        float ans = curr->data * 1.0;
        return ans;
    }
    else{
        float ans = ( (curr->data + prev->data)* 1.0 )/ 2 * 1.0;
        return ans;
    }
}
/*
Input:
       6
     /   \
   3      8   
 /  \    /  \
1    4  7    9
Output: 6
Explanation: Inorder of Given BST will be:
1, 3, 4, 6, 7, 8, 9. So, here median will 6.
*/


//251. COUNT BST NODES THAT LIE IN A GIVEN RANGE                                          {T.C = O(N), S.C = O(H)}
class Solution{
public:
    void solve(Node* root, int &l, int &h, int &count){
        //base case
        if(root == NULL){
            return;
        }
        //LNR
        solve(root->left, l, h, count);
        if(root->data >= l && root->data <= h){
            count++;
        }
        solve(root->right, l, h , count);
    }
    int getCount(Node *root, int l, int h)
    {
        int count = 0;
        solve(root, l, h, count);
        return count;
    }
};
/*
Input:
      10
     /  \
    5    50
   /    /  \
  1    40  100
l = 5, h = 45
Output: 3
Explanation: 5 10 40 are the node in the
range
*/


//252. REPLACE EVERY ELEMENT WITH THE LEAST GREATER ELEMENT ON ITS RIGHT                {T.C = O(N*LOGN/H), S.C = O(N)}
class Solution{
    public:

    Node* insert(Node* root,int val,Node* &succ){
        if(root == NULL){
            return new Node(val);   
        }
        if(root->data > val){
            succ= root;
            root->left=insert(root->left,val,succ);
        }
        else if(root->data <= val){
            root->right=insert(root->right,val,succ);
        }
        return root;
    }
    vector<int> findLeastGreater(vector<int>& arr, int n) {
       Node *root=NULL;
       for(int i=n-1;i>=0;i--){
           Node* succ =NULL;
           root= insert(root,arr[i],succ);
           if(succ){ 
               arr[i]=succ->data;
           }
           else{
               arr[i]=-1;  
           } 
       } 
       return arr;
    }
};
/*
Input:
arr[] = {8, 58, 71, 18, 31, 32, 63, 92, 43, 3, 91, 93, 25, 80, 28}
Output: {18, 63, 80, 25, 32, 43, 80, 93, 80, 25, 93, -1, 28, -1, -1}
Explanation: 
The least next greater element of 8 is 18.
The least next greater element of 58 is 63 and so on.
*/


//253. OVERLAPPING INTERVALS                                                  {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    vector<vector<int>> overlappedInterval(vector<vector<int>>& intervals) {
        vector<vector<int>>ans;
        //base case
        if(intervals.size() == 0){
            return ans;
        }
        
        //sort intervals
        sort(intervals.begin(), intervals.end());     //by default sort on the basis of 1st elemnt of range
        vector<int>tempInterval = intervals[0];
        for(auto it : intervals){
            if(it[0] <= tempInterval[1]){
                tempInterval[1] = max(tempInterval[1], it[1]);
            }else{
                ans.push_back(tempInterval);
                tempInterval = it;
            }
        }
        ans.push_back(tempInterval);
        
        return ans;
    }
};
/*
Input:
Intervals = {{1,3},{2,4},{6,8},{9,10}}
Output: {{1, 4}, {6, 8}, {9, 10}}
Explanation: Given intervals: [1,3],[2,4]
[6,8],[9,10], we have only two overlapping
intervals here,[1,3] and [2,4]. Therefore
we will merge these two and return [1,4],
[6,8], [9,10].
*/


//254. CHECK PREORDER IS VALID OR NOT / PREORDER TO POSTORDER                                       {T.C = O(N), S.C = O(N)}
class Solution{
public:
    Node* solve(int pre[],int size, int &i , int minRange, int maxRange){
        //base case
        if(i == size || pre[i] > maxRange || pre[i] < minRange ){
            return NULL;
        }
        Node* root = new Node(pre[i++]);
        root->left = solve(pre, size, i, minRange, root->data);
        root->right = solve(pre, size, i, root->data, maxRange);
        
        return root;
    }
    Node* post_order(int pre[], int size)
    {
        int i = 0;
        return solve(pre,size, i, INT_MIN, INT_MAX);
    }
};
/*
Input:
N = 5
arr[]  = {40,30,35,80,100}
Output: 35 30 100 80 40
Explanation: PreOrder: 40 30 35 80 100
Therefore, the BST will be:
              40
           /      \
         30       80
           \        \   
           35      100
Hence, the postOrder traversal will
be: 35 30 100 80 40
*/


//255. CHECK WHETHER BST CONTAINS DEAD END                                                              {T.C = O(N), S.C = O(H)}
bool solve(Node* root, int minRange , int maxRange){
    //base case
    if(root == NULL){
        return false;
    }
    
    if(minRange == maxRange){
        return true;
    }
    
    return solve(root->left, minRange, root->data-1) or solve(root->right, root->data + 1, maxRange);
}
bool isDeadEnd(Node *root)
{
    return solve(root, 1, INT_MAX);              //1 = lower bound , INT_MAX = upper bound
}
/*
Input :   
               8
             /   \ 
           5      9
         /  \     
        2    7 
       /
      1     
          
Output : 
Yes
Explanation : 
Node "1" is the dead End because after that 
we cant insert any element.
*/


//256. LARGEST BST (ERROR)                                                                             {T.C = O(N), S.C = O(H)}
class info{
public:
    int maxi;
    int mini;
    int size;
    bool isBST;
};

class Solution{
    public:
    info solve(Node* root, int &ans){
        //base case
        if(root == NULL){
            return {INT_MAX, INT_MIN, 0, true};
        }
        
        //LRN
        info left = solve(root->left, ans);
        info right = solve(root->right, ans);
        
        info currNode;
        
        currNode.maxi = max(root->data, right.maxi);
        currNode.mini = min(root->data, left.mini);
        currNode.size = left.size + right.size + 1;
        currNode.isBST = left.isBST && right.isBST && root->data > left.maxi;
        
        //answer update
        if(currNode.isBST){
            ans = max(ans, currNode.size);
        }
        
        return currNode;
    }
    int largestBst(Node *root)
    {
    	int ans = 0;
    	info temp = solve(root, ans);
    	
    	return ans;
    }
};
/*
Input: 6 6 3 N 2 9 3 N 8 8 2
            6
        /       \
       6         3
        \      /   \
         2    9     3
          \  /  \
          8 8    2 
Output: 2
Explanation: The following sub-tree is a
BST of size 2: 
       2
    /    \ 
   N      8
*/


//257. FLATTEN BINARY TREE INTO LIST                                                              {T.C = O(N), S.C = O(1)}
//morris traversal (S.C = O(1))
class Solution
{
    public:
    void flatten(Node *root)
    {
        Node *curr = root;
        while(curr != NULL){
            if(curr->left){
                Node *pred = curr->left;
                while(pred->right){
                    pred = pred->right;
                }
                pred->right = curr->right;
                curr->right = curr->left;
                curr->left = NULL;
            }
            curr = curr->right;
        }
    }
};
/*
Input : 
          1
        /   \
       2     5
      / \     \
     3   4     6
Output :
1 2 3 4 5 6 
Explanation: 
After flattening, the tree looks 
like this
    1
     \
      2
       \
        3
         \
          4
           \
            5
             \
              6 
Here, left of each node points 
to NULL and right contains the 
next node in preorder.The inorder 
traversal of this flattened tree 
is 1 2 3 4 5 6.
*/


/*--------------------------------------------------------   THE END   ----------------------------------------------------------------------*/