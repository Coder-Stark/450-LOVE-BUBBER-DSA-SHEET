//HEAP

#include<bits/stdc++.h>
using namespace std;

//258a. BUILD MAX HEAP                                                           {T.C = O(N*LOGN), S.C = O(1)}
//heapify = o(logn), build heap = o(n)
//STL = priority_queue<int>maxHeap
void heapify(vector<int>&arr, int n , int i){

	int largest = i;
	int left = 2*i + 1;                                       //0 based indexing
	int right = 2*i + 2;

	if(left < n && arr[largest] < arr[left]){
		largest = left;
	}
	if(right < n && arr[largest] < arr[right]){
		largest = right;
	}

	if(largest != i){
		swap(arr[largest], arr[i]);
		heapify(arr, n, largest);
	}
}
vector<int> buildHeap(vector<int> arr, int n)
{	
	for(int i = n/2-1 ; i >= 0 ; i--){
		heapify(arr, n , i);
	}
	return arr;
}
/*
Input Array (unsorted): [4, 10, 3, 5, 1]
Resulting Max Heap: [10, 5, 3, 4, 1]
*/

//258b. BUILD MIN HEAP                                                             {T.C = O(N*LOGN), S.C = O(1)}
//STL = priority_queue<int, vector<int>, greater<int> >minHeap
void heapify(vector<int>&arr , int n , int i){

    int smallest = i;
    int left = 2 * i + 1 ;
    int right = 2 * i + 2;

    if(left < n && arr[smallest] > arr[left]){
        smallest = left;
    }
    if(right < n && arr[smallest] > arr[right]){
        smallest = right;
    }

    if(smallest != i){
        swap(arr[smallest],arr[i]);
        heapify(arr,n,smallest);
    }
}


vector<int> buildMinHeap(vector<int> &arr)
{
    int n = arr.size();
    for(int i = n/2-1 ; i >= 0 ; i--){
        heapify(arr, n, i);
    }
    return arr;
}
/*
Input Array (unsorted): [4, 10, 3, 5, 1]
Resulting Min Heap: [1, 3, 4, 5, 10]
*/


//259. HEAP SORT                                                                {T.C = O(N*LOGN), S.C = O(1)}
class Solution{
    public:
    //Heapify function to maintain heap property.
    void heapify(int arr[], int n, int i)  
    {
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        
        if(left < n && arr[largest] < arr[left]){
            largest = left;
        }
        if(right < n && arr[largest] < arr[right]){
            largest = right;
        }
        
        if(largest != i){
            swap(arr[largest], arr[i]);
            heapify(arr, n, largest);
        }
    }

    public:
    //Function to build a Heap from array.
    void buildHeap(int arr[], int n)  
    { 
        for(int i = n/2-1 ; i >= 0 ; i--){
            heapify(arr, n, i);
        }
    }

    
    public:
    //Function to sort an array using Heap Sort.
    void heapSort(int arr[], int n)
    {
        buildHeap(arr, n);
        
        int size = n;
        while(size > 1){
            //step 1 swap
            swap(arr[0], arr[size-1]);
            
            //step 2 remove element
            size--;
            
            //step 3 propagate node to its correct position
            heapify(arr, size, 0);
        }
    }
};
/*
Input:
N = 5
arr[] = {4,1,3,9,7}
Output:
1 3 4 7 9
Explanation:
After sorting elements
using heap sort, elements will be
in order as 1,3,4,7,9.
*/


//260. MAXIMUM OF ALL SUBARRAYS OF SIZE K
//BRUTE FORCE                                                                       {T.C = O(N*K), S.C = O(N)}
class Solution{
public:
    vector<int> max_of_subarrays(int *arr, int n, int k)
    {
        vector<int> ans;

        // Outer loop iterates over each possible subarray.
        for (int i = 0; i <= n - k; i++) {
            int maxi = INT_MIN; 
            // Inner loop iterates over elements within the current subarray.
            for (int j = i; j < i + k; j++) {
                maxi = max(maxi, arr[j]);
            }

            ans.push_back(maxi);
        }
        return ans;
    }
};
//USING MAXHEAP  (TLE)                                                            {T.C = O(N*LOGK), S.C = O(N)}
class Solution
{
  public:
    vector <int> max_of_subarrays(int *arr, int n, int k)
    {
        vector<int>ans;
        priority_queue<int>maxHeap;
        
        for(int i = 0 ; i < k ; i++){
            maxHeap.push(arr[i]);
        }
        ans.push_back(maxHeap.top());
        
        for(int i = k ; i < n ; i++){
            while(!maxHeap.empty() && maxHeap.top() <= arr[i-k]){
                maxHeap.pop();
            }
            maxHeap.push(arr[i]);
            ans.push_back(maxHeap.top());
        }
        return ans;
    }
};
//OPTIMIZED APPROACH                                                           {T.C = O(N), S.C = O(N)}
class Solution
{
  public:
    vector <int> max_of_subarrays(int *arr, int n, int k)
    {
        vector<int>ans;
        deque<int>dq;
        
        for(int i = 0 ;i < k ; i++){
            while(!dq.empty() && (arr[dq.back()] <= arr[i] )){
                dq.pop_back();
            }
            dq.push_back(i);
        }
        for(int i = k; i < n ;i++){
            ans.push_back(arr[dq.front()]);
            while(!dq.empty() && (dq.front() <= (i-k))){
                dq.pop_front();
            }
            while(!dq.empty() && (arr[dq.back()] <= arr[i])){
                dq.pop_back();
            }
            dq.push_back(i);
        }
        ans.push_back(arr[dq.front()]);
        return ans;
    }
};
/*
Input:
N = 9, K = 3
arr[] = 1 2 3 1 4 5 2 3 6
Output: 
3 3 4 5 5 5 6 
Explanation: 
1st contiguous subarray = {1 2 3} Max = 3
2nd contiguous subarray = {2 3 1} Max = 3
3rd contiguous subarray = {3 1 4} Max = 4
4th contiguous subarray = {1 4 5} Max = 5
5th contiguous subarray = {4 5 2} Max = 5
6th contiguous subarray = {5 2 3} Max = 5
7th contiguous subarray = {2 3 6} Max = 6
*/


//261. K LARGEST ELEMENT IN AN ARRAY                                       {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
public:	
	vector<int> kLargest(int arr[], int n, int k) {                                
	    vector<int>ans;
	    priority_queue<int>maxHeap;
	    
	    for(int i = 0 ; i < n ; i++){
	        maxHeap.push(arr[i]);
	    }
	    while(k > 0){
	        ans.push_back(maxHeap.top());
	        maxHeap.pop();
	        k--;
	    }
	    return ans;
	}
};
/*
Input:
N = 5, K = 2
Arr[] = {12, 5, 787, 1, 23}
Output: 787 23
Explanation: 1st largest element in the
array is 787 and second largest is 23.
*/


//262a. KTH SMALLEST ELEMENT IN AN UNSORTED ARRAY                                 {T.C = O(K*LOGK), S.C = O(K)}
//FOR SMALLEST ELEMENT FIND = MAXHEAP
//FOR LARGEST ELEMENT FIND = MINHEAP
class Solution{
    public:
    int kthSmallest(int arr[], int l, int r, int k) {
        priority_queue<int>maxHeap;
        
        //step1- make max heap of first k elements
        for(int i = 0 ; i < k ; i++){
            maxHeap.push(arr[i]);
        }
        
        //step2- for rest of elements
        for(int i = k ; i <= r ; i++){
            if(arr[i] < maxHeap.top()){
                maxHeap.pop();
                maxHeap.push(arr[i]);
            }
        }
        
        //step3- return ans
        return maxHeap.top();
    }
};
/*
Input:
N = 6
arr[] = 7 10 4 3 20 15
K = 3
Output : 7
Explanation :
3rd smallest element in the given 
array is 7.
*/

//262b. KTH LARGEST ELEMENT IN AN UNSORTED ARRAY                                  {T.C = O(K*LOGK), S.C = O(N)}
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //creating min heap
        priority_queue<int, vector<int>, greater<int>>minHeap;

        //put first k elements to min heap
        for(int i = 0 ; i < k ; i++){
            minHeap.push(nums[i]);
        }

        //for rest of elements
        for(int i = k ; i < nums.size() ; i++){
            if(nums[i] > minHeap.top()){
                minHeap.pop();
                minHeap.push(nums[i]);
            }
        }
        return minHeap.top();
    }
};
/*
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
*/


//263. MERGE K SORTED ARRAYS
//BRUTE FORCE APPROACH                                          {T.C = O(K^2*LOGK^2), S.C = O(K^2)} / {T.C = O(NK*LOG(NK)), S.C= O(NK)} 
class Solution
{
    public:
    vector<int> mergeKArrays(vector<vector<int>> arr, int k)            //k = size of matrix
    {
        vector<int>ans;
        for(int i = 0 ; i < k ; i++){
            for(int j = 0; j < k ; j++){
                ans.push_back(arr[i][j]);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
//OPTIMIZED APPROACH                                                         {T.C = O(NK*LOGK), S.C = O(N+K)}
class data {
public:
    int val, row, col;
    data(int val, int row, int col) {
        this->val = val;
        this->row = row;
        this->col = col;
    }
};

class compare {
public:
    bool operator()(data &d1, data &d2) {
        return d1.val > d2.val;
    }
};

class Solution {
public:
    vector<int> mergeKArrays(vector<vector<int>> arr, int k) {
        vector<int> ans;
        priority_queue<data, vector<data>, compare> minHeap;

        // Insert 1st k elements of each arrays
        for (int i = 0; i < k; i++) {
            data d(arr[i][0], i, 0);
            minHeap.push(d);
        }

        // Extract answer and push to vector
        while (!minHeap.empty()) {
            data curr = minHeap.top();
            minHeap.pop();
            ans.push_back(curr.val);
            int actualRow = curr.row;
            int actualCol = curr.col;

            if (actualCol + 1 < arr[actualRow].size()) {
                data d2(arr[actualRow][actualCol + 1], actualRow, actualCol + 1);
                minHeap.push(d2);
            }
        }
        return ans;
    }
};
/*
Input:
K = 3
arr[][] = {{1,2,3},{4,5,6},{7,8,9}}
Output: 1 2 3 4 5 6 7 8 9
Explanation:Above test case has 3 sorted
arrays of size 3, 3, 3
arr[][] = [[1, 2, 3],[4, 5, 6], 
[7, 8, 9]]
The merged list will be 
[1, 2, 3, 4, 5, 6, 7, 8, 9].
*/


//264. MERGE 2 BINARY MAX HEAPS                                                   {T.C = O(N+M(LOG(N+M))), S.C = O(N+M)}
class Solution{
    public:
    vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {
        vector<int>ans;
        priority_queue<int>maxHeap;
        
        for(auto it : a){
            maxHeap.push(it);
        }
        for(auto it : b){
            maxHeap.push(it);
        }
        while(!maxHeap.empty()){
            ans.push_back(maxHeap.top());
            maxHeap.pop();
        }
        return ans;
    }
};
/*
Input  : 
n = 4 m = 3
a[] = {10, 5, 6, 2}, 
b[] = {12, 7, 9}
Output : 
{12, 10, 9, 2, 5, 7, 6}
*/


//265. KTH LARGEST SUM CONTIGUOUS SUBARRAY
//BRUTE FORCE                                                              {T.C = O(N^2*LOG(N)), S.C = O(N^2)}
class Solution{
public:
    int kthLargest(vector<int> &arr,int n,int k){
        vector<int>ans;
        
        //finding different subarray sums we can get from the array eg Arr = {3,2,1} =  subarrays sum{6,5,3,2,1}
        for(int i = 0 ; i < n ; i++){
            int subArraySum = 0;
            for(int j = i ; j < n ; j++){
                subArraySum += arr[j];
                ans.push_back(subArraySum);
            }
        }
        
        //reverse decreasing sort for finding kth largest subarray sum
        sort(ans.rbegin(), ans.rend());
        
        return ans[k-1];                      //1 based indexing
    }
};
//OPTIMIZED APPROACH                                                             {T.C = O(N^2*LOGK), S.C = O(K)}
class Solution{
public:
    int kthLargest(vector<int> &arr,int n,int k){
        priority_queue<int, vector<int>, greater<int>>minHeap;
        
        for(int i = 0 ; i < n ; i++){
            int subArraySum = 0;
            for(int j = i ; j < n ; j++){
                subArraySum += arr[j];
                minHeap.push(subArraySum);
                if(minHeap.size() > k){
                    minHeap.pop();
                }
            }
        }
        return minHeap.top();
    }
};
/*
Input:
N = 3
K = 2
Arr = {3,2,1}
Output:
5
Explanation:
The different subarray sums we can get from the array
are = {6,5,3,2,1}. Where 5 is the 2nd largest.
*/


//266. REARRANGE STRING                                                              {T.C = O(N), S.C = O(1)}
class Solution {
public:
    string reorganizeString(string str) {
        // Step 1: Calculate character frequency using an array
        vector<int> freq(26, 0);
        for (char ch : str) {
            freq[ch - 'a']++;
        }

        // Step 2: Find the most frequent character
        int maxFreq = 0, mostFreqChar = 0;
        for (int i = 0; i < freq.size(); i++) {
            if (freq[i] > maxFreq) {
                maxFreq = freq[i];
                mostFreqChar = i;
            }
        }

        // Step 3: Check if the most frequent character dominates the string
        if (maxFreq > (str.length() + 1) / 2) {
            return "";
        }

        // Step 4: Create a character array to store the result
        char res[str.length()];

        // Step 5: Fill all even positions with the most frequent character
        int idx = 0;
        while (freq[mostFreqChar]-- > 0) {
            res[idx] = static_cast<char>(mostFreqChar + 'a');
            idx += 2;
        }

        // Step 6: Fill the remaining characters
        for (int i = 0; i < freq.size(); i++) {
            while (freq[i]-- > 0) {
                if (idx >= str.length()) {
                    idx = 1;
                }

                res[idx] = static_cast<char>(i + 'a');
                idx += 2;
            }
        }

        // Step 7: Convert the character array to a string and return
        return string(res, str.length());
    }
};
/*
Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""
*/


struct Node
{
	int data;
	Node* next;
	
	Node(int x){
	    data = x;
	    next = NULL;
	}
	
};
//267. MERGE K SORTED LINKED LIST                                                                    {T.C = O(NK*LOGK), S.C = O(K)}
class compare{
public: 
    bool operator()(Node* a, Node* b){
        return a->data > b->data;
    }
};
class Solution{
  public:
    Node * mergeKLists(Node *arr[], int k)
    {
        priority_queue<Node*, vector<Node*>, compare>minHeap;
        
        //Insert 1st k elements of each list
        for(int i = 0 ; i < k ; i++){
            if(arr[i]){
                minHeap.push(arr[i]);
            }
        }
        
        Node* head = NULL;
        Node* tail = NULL;
        //Extract answer and push to list
        while(!minHeap.empty()){
            Node* curr = minHeap.top();
            minHeap.pop();
            
            if(curr->next){
                minHeap.push(curr->next);
            }
            
            //answer ll is emepty/ first element 
            if(head == NULL){
                head = curr;
                tail = curr;
            }else{
                tail->next = curr;
                tail = curr;
            }
        }
        return head;
    }
};
/*
Input:
K = 3
value = {{1,3},{4,5,6},{8}}
Output: 1 3 4 5 6 8
Explanation:
The test case has 3 sorted linked
list of size 2, 3, 1.
1st list 1 -> 3
2nd list 4 -> 5 -> 6
3rd list 8
The merged list will be
1->3->4->5->6->8.
*/


//268. SMALLEST RANGE IN K LISTS                                                                      {T.C = O(NK*LOGK), S.C = O(K)}
//TLE
class data {
public:
    int val, row, col;
    data(int val, int row, int col) {
        this->val = val;
        this->row = row;
        this->col = col;
    }
};

class compare {
public:
    bool operator()(data& d1, data& d2) {
        return d1.val > d2.val;
    }
};

class Solution {
public:
    pair<int, int> findSmallestRange(int arr[][N], int n, int k) {
        int mini = INT_MAX;
        int maxi = INT_MIN;
        priority_queue<data, vector<data>, compare> minHeap;

        // Insert 1st k elements of each arrays
        for (int i = 0; i < k; i++) {
            data d(arr[i][0], i, 0);
            minHeap.push(d);
            mini = min(mini, arr[i][0]);
            maxi = max(maxi, arr[i][0]);
        }

        int start = mini;
        int end = maxi;

        // Process range
        while (!minHeap.empty()) {
            data curr = minHeap.top();
            minHeap.pop();
            mini = curr.val;

            // Range or answer updatation
            if (maxi - mini < end - start) {
                start = mini;
                end = maxi;
            }

            int actualRow = curr.row;
            int actualCol = curr.col;
            
            // If next element exists
            if (actualCol + 1 < n) {
                maxi = max(maxi, arr[actualRow][actualCol + 1]);
                data d2(arr[actualRow][actualCol + 1], actualRow, actualCol + 1);
                minHeap.push(d2);
            } else {
                break;
            }
        }
        
        return {start, end}; // Return the smallest range
    }
};
/*
Input:
N = 5, K = 3
KSortedArray[][] = {{1 3 5 7 9},
                    {0 2 4 6 8},
                    {2 3 5 7 11}}
Output: 1 2
Explanation: K = 3
A:[1 3 5 7 9]
B:[0 2 4 6 8]
C:[2 3 5 7 11]
Smallest range is formed by number 1
present in first list and 2 is present
in both 2nd and 3rd list.
*/


//269. FIND MEDIAN IN A STREAM                                                       {T.C = O(N*LOGN), S.C = O(N)}           
class Solution
{
    public:
    priority_queue<int>s;                                   //smaller half maxheap
    priority_queue<int, vector<int>, greater<int>>g;        //greater half minHeap
    
    //Function to insert heap.
    void insertHeap(int &x)
    {
        if(s.size() == 0){
            s.push(x);
            return;
        }
        //smaller and greater half size is different / smaller size is large
        if(s.size() > g.size()){
            if(x < s.top()){                           //element want to insert in left
                g.push(s.top());                       //first balance by putting top of left to right
                s.pop();
                s.push(x);
            }else{
                g.push(x);
            }
        }
        //smaller and greater half size if same
        else{
            if(x < s.top()){                          //element want to insert in left
                s.push(x);
            }else{
                g.push(x);                           
                s.push(g.top());
                g.pop();                             //maintain always left size is big not right
            }
        }
    }
    
    //Function to return Median.
    double getMedian()
    {
        if(s.size() == g.size()){
            return (s.top() + g.top())/2;
        }else{
            return s.top();
        }
    }
};
/*
Input:
N = 4
X[] = 5,15,1,3
Output:
5
10
5
4
Explanation:Flow in stream : 5, 15, 1, 3 
5 goes to stream --> median 5 (5) 
15 goes to stream --> median 10 (5,15) 
1 goes to stream --> median 5 (5,15,1) 
3 goes to stream --> median 4 (5,15,1 3) 
*/


struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
//270. IS BINARY TREE HEAP                                                           {T.C = O(N), S.C = O(N)}
class Solution {
  public:
    int countNodes(struct Node* root){
        //base case
        if(root == NULL){
            return 0;
        }
        int ans = countNodes(root->left) + countNodes(root->right) + 1;      //1 = root node
        return ans;
    }
    bool isCBT(struct Node* root, int i , int cnt){
        //base case
        if(root == NULL){
            return true;
        }
        
        if(i >= cnt){                                  //0 based indexing
            return false;
        }else{
            bool left = isCBT(root->left, 2*i + 1, cnt);
            bool right = isCBT(root->right, 2*i + 2, cnt);
            return (left && right);
        }
    }
    bool isMaxi(struct Node* root){
        //3 coditions = leaf node, 1 left child , both childs
        //leaf node
        if(root->left == NULL && root->right == NULL){
            return true;
        }
        //1 left child only
        if(root->right == NULL){
            return root->left->data < root->data;
        }
        //2 child 
        else{
            bool left = isMaxi(root->left);
            bool right = isMaxi(root->right);
            
            return left && right && root->left->data < root->data && root->right->data < root->data;
        }
    }
    bool isHeap(struct Node* tree) {
        int i = 0;
        int totalCount = countNodes(tree);
        if(isCBT(tree, i, totalCount) && isMaxi(tree)){
            return true;
        }
        return false;
    }
};
/*
Input:
      5
    /  \
   2    3
Output: 1
Explanation: The given tree follows max-heap property since 5,
is root and it is greater than both its children.
*/


//271. MINIMUM COST OF ROPES                                                  {T.C = O(N*LOGN), S.C = O(N)}
class Solution
{
    public:
    long long minCost(long long arr[], long long n) {
        long long cost = 0;
        priority_queue<long long, vector<long long>, greater<long long>>minHeap;
        
        for(int i = 0 ; i < n ; i++){
            minHeap.push(arr[i]);
        }
        
        while(minHeap.size() > 1){                   //pop till 1 element left
            long long a = minHeap.top();
            minHeap.pop();
            long long b = minHeap.top();
            minHeap.pop();
            
            long long sum = a + b;
            
            minHeap.push(sum);
            cost += sum;
        }
        return cost;
    }
};
/*
Input:
n = 4
arr[] = {4, 3, 2, 6}
Output: 
29
Explanation:
We can connect the ropes in following ways.
1) First connect ropes of lengths 2 and 3.
Which makes the array {4, 5, 6}. Cost of
this operation 2+3 = 5. 
2) Now connect ropes of lengths 4 and 5.
Which makes the array {9, 6}. Cost of
this operation 4+5 = 9.
3) Finally connect the two ropes and all
ropes have connected. Cost of this 
operation 9+6 =15
Total cost for connecting all ropes is 5
+ 9 + 15 = 29. This is the optimized cost
for connecting ropes. 
Other ways of connecting ropes would always 
have same or more cost. For example, if we 
connect 4 and 6 first (we get three rope of 3,
2 and 10), then connect 10 and 3 (we get
two rope of 13 and 2). Finally we
connect 13 and 2. Total cost in this way
is 10 + 13 + 15 = 38.
*/


class BinaryTreeNode {
		
	public :
		int data;
		BinaryTreeNode* left;
		BinaryTreeNode* right;

		BinaryTreeNode(int data) {
		this -> left = NULL;
		this -> right = NULL;
		this -> data = data;
		}
};
//272a. CONVERT BST TO MINHEAP                                                        {T.C = O(N), S.C = O(N)}
void inOr(BinaryTreeNode* root, vector<int>&v){
	//base case
	if(root == NULL){
		return;
	}
	//LNR
	inOr(root->left, v);
	v.push_back(root->data);
	inOr(root->right, v);
}
void prOr(BinaryTreeNode* root, vector<int>&v, int &i){
	//base case
	if(root == NULL){
		return;
	}
	//NLR
	root->data = v[i++];
	prOr(root->left, v, i);
	prOr(root->right, v, i);
}
BinaryTreeNode* convertBST(BinaryTreeNode* root)
{
	//condition = N < L < R       //use pre order
	vector<int>v;
	inOr(root, v);
	int i = 0;
	prOr(root, v, i);

	return root;
}
/*
Input :
                 4
               /   \
              2     6
            /  \   /  \
           1   3  5    7  

Output : 1 2 3 4 5 6 7 
Exaplanation :
               1
             /   \
            2     5
          /   \  /   \
         3     4 6    7
The given BST has been transformed into a
Min Heap and it's preorder traversal is
1 2 3 4 5 6 7.
*/

//272b. CONVERT BST TO MAXHEAP                                                  {T.C = O(N), S.C = O(N)}
class Solution{
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
    void poOr(Node* root, vector<int>&v, int &i){
        //base case
        if(root == NULL){
            return;
        }
        //LRN
        poOr(root->left, v, i);
        poOr(root->right, v, i);
        root->data = v[i++];
    }
    void convertToMaxHeapUtil(Node* root)
    {
        vector<int>v;
        inOr(root, v);
        int i = 0;
        poOr(root, v, i);
        
        //return root
    }    
};
/*
Input :
                 4
               /   \
              2     6
            /  \   /  \
           1   3  5    7  

Output : 1 2 3 4 5 6 7 
Exaplanation :
               7
             /   \
            3     6
          /   \  /   \
         1    2 4     5
The given BST has been transformed into a
Max Heap and it's postorder traversal is
1 2 3 4 5 6 7.
*/


//273. CONVERT MINHEAP TO MAXHEAP (SAME AS BUILD HEAP)                        {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
public:
    void heapify(vector<int>&arr, int n , int i){
        int largest = i;                //parent
        int left = 2*i+1;
        int right = 2*i+2;
        
        if(left < n && arr[largest] < arr[left]){
            largest = left;
        }
        if(right < n && arr[largest] < arr[right]){
            largest = right;
        }
        
        if(largest != i){
            swap(arr[largest], arr[i]);
            heapify(arr, n , largest);
        }
    
    void convertMinToMaxHeap(vector<int> &arr, int n){
        //build heap
        for(int i = n/2-1 ; i >= 0 ; i--){         //n/2 to n is leaf node no require to process
            heapify(arr, n , i);
        }
    }
};
/*
Input:
N = 5
arr = [3, 4, 8, 11, 13]
Output:
[13, 11, 8, 3, 4]
Explanation:

The given min Heap:

          3
        /   \
      4      8
    /   \ 
  11     13

Max Heap after conversion:

          13
        /    \
      11      8
    /   \ 
   3     4
*/


//274. REARRANGE STRING (same as 266)                                                        {T.C = O(N), S.C = O(1)}
class Solution{
public:
    string reorganizeString(string str) {
        // Step 1: Calculate character frequency using an array
        vector<int> freq(26, 0);
        for (char ch : str) {
            freq[ch - 'a']++;
        }

        // Step 2: Find the most frequent character
        int maxFreq = 0, mostFreqChar = 0;
        for (int i = 0; i < freq.size(); i++) {
            if (freq[i] > maxFreq) {
                maxFreq = freq[i];
                mostFreqChar = i;
            }
        }

        // Step 3: Check if the most frequent character dominates the string
        if (maxFreq > (str.length() + 1) / 2) {
            return "";
        }

        // Step 4: Create a character array to store the result
        char res[str.length()];

        // Step 5: Fill all even positions with the most frequent character
        int idx = 0;
        while (freq[mostFreqChar]-- > 0) {
            res[idx] = static_cast<char>(mostFreqChar + 'a');
            idx += 2;
        }

        // Step 6: Fill the remaining characters
        for (int i = 0; i < freq.size(); i++) {
            while (freq[i]-- > 0) {
                if (idx >= str.length()) {
                    idx = 1;
                }

                res[idx] = static_cast<char>(i + 'a');
                idx += 2;
            }
        }

        // Step 7: Convert the character array to a string and return
        return string(res, str.length());
    }
};
/*
Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""
*/


//275. MINIMUM SUM                                                             {T.C = O(N*LOGN), S.C = O(N)}
//ERROR
class Solution{   
public:
    string sumOf(string a, string b){             //reverse arguments
        int i = a.size()-1;
        int j = b.size()-1;
        string sum = "";
        int carry = 0;
        
        while(i >= 0 && j >= 0){
            int d1 = a[i]- '0';
            int d2 = b[j]- '0';
            int dSum =  d1+d2+carry;
            sum += to_string((dSum)%10);
            carry = dSum/10;
            i--, j--;
        }
        while(i >= 0){
            int d1 = a[i]-'0';
            sum += to_string((d1+carry)%10);
            carry = d1+carry/10;
            i--;
        }
        while(j >= 0){
            int d2 = b[j]-'0';
            sum += to_string((d2+carry)%10);
            carry = d2+carry/10;
            j--;
        }
        if(carry != 0){
            sum += to_string(carry);
        }
        
        for(int i = 0 ; i < sum.size() ; i++){             //01100 => 1100
            if(sum[i] != '0'){
                return sum.substr(i);
            }
        }
        return "0";
    }
    string solve(int arr[], int n) {
        string s1 = "";
        string s2 = "";
        sort(arr, arr+n);
        
        for(int i = 0 ; i < n ; i++){
            if(i % 2 == 0){
                s1 += to_string(arr[i]);
            }else{
                s2 += to_string(arr[i]);
            }
        }
        
        return sumOf(s1, s2);
    }
};
/*
Input:
N = 6
Arr[] = {6, 8, 4, 5, 2, 3}
Output: 604
Explanation: The minimum sum is formed 
by numbers 358 and 246.
*/



/*-----------------------------------------------  THE END   ----------------------------------------------------------*/