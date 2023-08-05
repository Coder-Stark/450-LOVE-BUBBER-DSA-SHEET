//SEARCHING AND SORTING

#include<bits/stdc++.h>
using namespace std;


//91. FIRST AND LAST OCCURANCE OF X(ELEMENT) IN SORTED ARRAY
//BRUTE FORCE                                                                     {T.C = O(N), S.C = O(1)}
vector<int> find(int arr[], int n , int x )
{
    vector<int>ans(2, -1);                          //store value of 2 index if not present -1
    for(int i = 0 ; i < n ; i++){
        if(arr[i] == x){
            ans[0] = i;
            break;
        }
    }
    
    for(int j = n-1 ; j >= 0 ; j--){
        if(arr[j] == x){
            ans[1] = j;
            break;
        }
    }
    
    return ans;
}

//USING BINARY SEARCH                                                                      {T.C = O(LOGN), S.C = O(1)}
vector<int> find(int arr[], int n , int x )
{
    vector<int>ans(2, -1);
    
    //binary search for first occurance
    int left = 0;
    int right = n-1;
    
    while(left <= right){
        int mid = left + (right-left)/2;
        if(x == arr[mid]){
            ans[0] = mid;
            right = mid-1;                       //for searching in 1st half
        }
        else if(x > arr[mid]){
            left = mid+1;
        }
        else{  //x < arr[mid]
            right = mid-1;
        }
    }
    
    //binary search for last occurance
    left = 0;
    right = n-1;
    
    while(left <= right){
        int mid = left + (right-left)/2;
        if(x == arr[mid]){
            ans[1] = mid;
            left = mid+1;                        //for searching in 2nd half
        }
        else if(x > arr[mid]){
            left = mid+1;
        }
        else{  //x < arr[mid]
            right = mid-1;
        }
    }
    
    return ans;
}
/*
Input:
n=9, x=5
arr[] = { 1, 3, 5, 5, 5, 5, 67, 123, 125 }
Output:  2 5
Explanation: First occurrence of 5 is at index 2 and last
             occurrence of 5 is at index 5. 
*/


//92. VALUE IS EQUAL TO INDEX VALUE                                                     {T.C = O(N), S.C = O(N)}                          {T.C = O(N), S.C = O(1)}
class Solution{
public:

	vector<int> valueEqualToIndex(int arr[], int n) {
	    vector<int>ans;
	    //1 based indexing
	    for(int i = 0 ; i < n ;i++){
	        if(arr[i] == i+1){
	            ans.push_back(arr[i]);
	        }
	    }
	    return ans;
	}
};
/*
Input:
N = 5
Arr[] = {15, 2, 45, 12, 7}
Output: 2
Explanation: Only Arr[2] = 2 exists here.
*/


//93. SEARCH IN ROTATED SORTED ARRAY                                                {T.C = O(LOGN), S.C = O(1)}
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int low = 0; 
        int high = n-1;

        while(low <= high){
            int mid = low + (high-low)/2;

            if(nums[mid] == target){
                return mid;
            }

            //left sorted
            if(nums[low] <= nums[mid]){
                if(nums[low] <= target && target <= nums[mid]){
                    high = mid-1;                                 //eleminate right part
                }else{
                    low = mid+1;
                }
            }
            //right sorted
            else{
                if(nums[mid] <= target && target <= nums[high]){
                    low = mid+1;                                  //eleminate left part
                }else{
                    high = mid-1;
                }
            }
        }
        return -1;
    }
};
/*
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
*/


//94. COUNT SQUARES                                                              {T.C = O(SQRTN), S.C = O(1)}
class Solution {
  public:
    int countSquares(int N) {
        int count = 0;
        for(int i = 1 ; i*i < N ; i++){
            if(i < N){
                count++;
            }
        }
        return count;
    }
};
/*
Input :
N = 9
Output:
2
Explanation:
1 and 4 are the only Perfect Squares
less than 9. So, the Output is 2.
*/


//95. MIDDLE OF THREE                                                             {T.C = O(1), S.C = O(1)}
class Solution{
  public:
    int middle(int A, int B, int C){
        
        if(A <= B && A >=C || A <= C && A >= B ){
            return A;
        }
        else if(B <= A && B >= C || B <= C && B >= A){
            return B;
        }
        else {
            return C;
        }
    }
};
/*
Input:
A = 978, B = 518, C = 300
Output:
518
Explanation:
Since 518>300 and 518<978, so 
518 is the middle element.
*/


//96. Optimum location of point to minimize total distance


//97. FIND REPEATING AND MISSING                                                            {T.C = O(N), S.C = O(N)}
class Solution{
public:
    vector<int> findTwoElement(vector<int> arr, int n) {
        
        // vector<int>hash(n+1, 0);
        int hash[n+1] = {0};
        
        for(int i = 0 ; i < n ;i++){
            hash[arr[i]]++;
        }
        
        int repeating = -1;
        int missing = -1;
        for(int i = 1 ; i <= n ; i++){
            
            if(hash[i] == 2){
                repeating = i;
            }
            else if (hash[i] == 0){
                missing = i;
            }
            
            if(repeating != -1 && missing != -1){
                break;
            }
        }
        return {repeating , missing };
    }
};
/*
Input:
N = 2
Arr[] = {2, 2}
Output: 2 1
Explanation: Repeating number is 2 and 
smallest positive missing number is 1.
*/


//98. MAJORITY ELEMENT
//BRUTE FORCE                                                                      {T.C = O(N^2), S.C = O(1)}
class Solution{
  public:
    int majorityElement(int a[], int size)
    {
        for(int i = 0 ; i < size ; i++){
            int count = 0;
            for(int j = 0 ; j < size ; j++){
                if(a[j] == a[i]){
                    count++;
                }
            }
            if(count > size/2){
                return a[i];
            }
        }
        return -1;
    }
};

//BETTER SOLUTION (UNORDERED_MAP)                                                      {T.C = O(N), S.C = O(N)}
class Solution{
  public:
    int majorityElement(int a[], int size)
    {
        unordered_map<int, int>mp;
        for(int i = 0 ; i < size; i++){
            mp[a[i]]++;
            if(mp[a[i]] > size/2){
                return a[i];
            }
        }
        return -1;
    }
};
//same as above                                                                              {T.C = O(N), S.C = O(N)}
class Solution{
  public:
    int majorityElement(int a[], int size)
    {
        unordered_map<int, int>mp;
        for(int i = 0 ; i < size; i++){
            mp[a[i]]++;
        }
        
        for(auto it : mp){
            if(it.second > size/2){
                return it.first;
            }
        }
        return -1;
    }
};

//OPTIMIZED APPROACH(MOORE'S ALGO)                                                       {T.C = O(N), S.C = O(1)}
class Solution{
  public:
    int majorityElement(int a[], int size)
    {
        //using MOORE'S ALGORITHM
        int c = 1 ; int val = a[0];
        for(int i = 1 ; i < size ; i++){
            if(a[i] == val){
                c++;
            }
            else{
                c--;
                if(c == 0){
                    val = a[i];
                    c = 1;
                }
            }
        }
        //check valid answer or not
        c = 0;
        for(int i = 0 ; i < size ; i++){
            if(a[i] == val){
                c++;
            }
        }
        if(c > size/2){
            return val;
        }
        else{
            return -1;
        }
    }
};
/*
Input:
N = 5 
A[] = {3,1,3,3,2} 
Output:
3
Explanation:
Since, 3 is present more
than N/2 times, so it is 
the majority element.
*/


//99. SEARCHING IN AN ARRAY WHERE ADJACENT DIFFER BY AT MOST K
//BRUTE FORCE (SIMPLE LINEAR SEARCH)                                          {T.C = O(N), S.C = O(1)}
//OPTIMIZED APPROACH                                                          {T.C = O(N), S.C = O(1)}
int search(int arr[], int n, int x, int k)
{
    int ans = -1;
    int i = 0;
    while(i < n){
        if(arr[i] == x){
            ans = i;
            break;
        }else{
            i = i + max(1, abs(arr[i]-x)/k);
        }
    }
    return ans;
}
/*
Input : arr[ ] = {4, 5, 6, 7, 6}, K = 1 
        and X = 6
Output : 2
Explanation:
In an array arr 6 is present at index 2.
So, return 2.
*/


//100. FIND PAIR GIVEN DIFFERENCE
//BRUTE FORCE                                                               {T.C = O(N^2), S.C = O(1)}
bool findPair(int arr[], int size, int n){
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            if(abs(arr[i]-arr[j]) == n){
                return 1;
            }
        }
    }
    return 0;
}
//OPTIMIZED (TLE = not for big data set)                                         {T.C = O(N*LOGN), S.C = O(1)}
bool findPair(int arr[], int size, int n){
    sort(arr, arr+size);
    int i = 0;
    int j = size-1;
    
    while(i <= j){
        if((arr[j]-arr[i]) == n){
            return 1;
        }
        else if((arr[j]-arr[i]) < n ){
            i++;
        }
        else{
            j--;
        }
    }
    return 0;
}
//similar to above(working solution)                                                         {T.C = O(N*LOGN), S.C = O(1)}
bool findPair(int arr[], int size, int n){
    sort(arr,arr+size);
    int i=0,j=i+1;
    while(i<size && j<size){
        if(i==j){
            j++;
        }
        if(arr[j]-arr[i] == n){
            return true;
        }else if(arr[j] - arr[i] < n){
            j++;
        }else {
            i++;
        }
    }
    return false;
}
//OPTIMIZED(USING BINARY SEARCH)                                                           {T.C = O(N*LOGN), S.C = O(1)}
bool findPair(int arr[], int size, int x){
    if (size == 0) {
      return false;
    }  
    // Sort the array.
    sort(arr, arr + size); 
    // Iterate through the array.
    for (int i = 0; i < size; i++) {
      // Check if there exists an element in the array whose difference with arr[i] is N.
      int j = lower_bound(arr + i + 1, arr + size, arr[i] + x) - arr;
      if (j < size && arr[j] == arr[i] + x) {
        // There exists a pair with difference N.
        return true;
      }
    }  
    // There is no pair with difference N.
    return false;
}
/*
Input:
L = 6, N = 78
arr[] = {5, 20, 3, 2, 5, 80}
Output: 1
Explanation: (2, 80) have difference of 78.
*/


//101a. FIND ALL 3 SUM NUMBERS(SIMILAR)                                                          {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    bool find3Numbers(int A[], int n, int X) {
        int l , r;
        sort(A, A+n);
        
        for(int i = 0 ; i < n-2 ; i++){
            l = i+1;
            r = n-1;
            
            while(l < r){
                if(A[i] + A[l] + A[r] == X){
                    return true;
                }
                else if(A[i] + A[l] + A[r] < X){
                    l++;
                }
                else{
                    r--;
                }
            }
        }
        return false;
    }
};
/*
Input:
n = 6, X = 13
arr[] = [1 4 45 6 10 8]
Output:
1
Explanation:
The triplet {1, 4, 8} in 
the array sums up to 13.
*/

//101b. FIND ALL 4 SUM NUMBERS                                                                 {T.C = O(N^3), S.C = O(N^2)}
class Solution{
    public:
    vector<vector<int> > fourSum(vector<int> &arr, int k) {
        
        vector<vector<int>>res;
        int n = arr.size();
        sort(arr.begin(), arr.end());
        
        for(int i = 0 ; i < n-3 ; i++){
            for(int j = i+1 ;  j < n-2 ; j++){
                int l = j+1;
                int r = n-1;
                
                while(l < r){
                    int sum = arr[i]+arr[j]+arr[l]+arr[r];
                    if(sum == k){
                        res.push_back({arr[i], arr[j], arr[l], arr[r]});
                        l++;
                        r--;
                    }
                    else if(sum < k){
                        l++;
                    }
                    else{
                        r--;
                    }
                }
            }
        }
        // Using a set to remove duplicate quadruples from the result
        set<vector<int>> uniqueQuadruples(res.begin(), res.end());
        res.assign(uniqueQuadruples.begin(), uniqueQuadruples.end());
        return res;
    }
};
/*
Input:
N = 5, K = 3
A[] = {0,0,2,1,1}
Output: 0 0 1 2 
Explanation: Sum of 0, 0, 1, 2 is equal
to K.
*/


//102. STICKLER THIEF / MAXIMUM SUM SUCH THAT NO 2 ELEMENTS ARE ADJACENT                
//RECRUSTION                                                                            {T.C = O(EXP), S.C = O(1)}
class Solution
{
    public:
    int solveMem(int arr[], int i){
        //base case
        if(i < 0){
            return 0;
        }
        
        //calculate recursively
        int incl = arr[i] + solveMem(arr, i-2);         //adjacent element can not be included
        int excl = 0 + solveMem(arr, i-1);              //previous element
        int res = max(incl , excl);
        
        return res;
    }
    int FindMaxSum(int arr[], int n)
    {
        return solveMem(arr, n-1);                      //valid indexs = 0 to n-1
    }
};

//RECURSION + MEMOIZATION                                                                  {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    int solveMem(int arr[], int i , vector<int>&dp){
        //base case
        if(i < 0){
            return 0;
        }
        
        //step-3 if answer already present return it
        if(dp[i] != -1){
            return dp[i];
        }
        
        //calculate recursively
        int incl = arr[i] + solveMem(arr, i-2, dp);         //adjacent element can not be included
        int excl = 0 + solveMem(arr, i-1, dp);              //previous element
        int res = max(incl , excl);
        
        //step-2 store ans in dp
        dp[i] = res;
        return dp[i];
    }
    int FindMaxSum(int arr[], int n)
    {
        //step-1 create a dp vector
        vector<int>dp(n, -1);
        return solveMem(arr, n-1, dp);                      //valid indexs = 0 to n-1
    }
};
/*
Input:
n = 6
a[] = {5,5,10,100,10,5}
Output: 110
Explanation: 5+100+5=110
*/


//103. COUNT TRIPLETS WITH SUM SMALLER THAN X                                                    {T.C = O(N^2), S.C = O(1)}
class Solution{
	public:
	long long countTriplets(long long arr[], int n, long long sum)
	{
	    sort(arr, arr+n);
	    
	    long long count = 0;
	    for(int i = 0 ; i < n-2 ; i++){
	        int l = i+1;
	        int r = n-1;
	        
	        while(l < r){
	            long long totalSum = arr[i] + arr[l] + arr[r];
	            if(totalSum < sum ){
                    count += (r-l);                  //i < x(i) < r (GIVEN)
                    l++;
	            }else{
	                r--;
	            }
	        }
	    }
	    return count;
	}
};
/*
Input: N = 4, sum = 2
arr[] = {-2, 0, 1, 3}
Output:  2
Explanation: Below are triplets with 
sum less than 2 (-2, 0, 1) and (-2, 0, 3).
*/


//104. MERGE SORTED ARRAY                                                                    {T.C = O(M+N), S.C = O(1)}
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(i >= 0 && j >= 0){
            if(nums1[i] > nums2[j]){
                nums1[k] = nums1[i];
                i--, k--;
            }else{
                nums1[k] = nums2[j];
                j--, k--;
            }
        }
        while(i >= 0){
            nums1[k] = nums1[i];
            i--, k--;
        }
        while(j >= 0){
            nums1[k] = nums2[j];
            j--, k--;
        }
    }
};
/*
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
*/


//105. ZERO SUM SUBARRAYS                                                               {T.C = O(N), S.C = O(N)}
class Solution{
public:
    long long int findSubarray(vector<long long int> &arr, int n ) {
        // Create an unordered map to store the cumulative sum of elements and their frequencies.
        // The key will be the cumulative sum, and the value will be the count of occurrences of that sum.
        unordered_map<long long int, int> mp;
        
        // Initialize the frequency of cumulative sum 0 as 1, since an empty subarray has a sum of 0.
        mp[0] = 1;
        
        // Initialize variables to store the cumulative sum and the answer (count of subarrays with equal sum).
        long long int sum = 0;
        long long int ans = 0;
        
        // Loop through the array to find the cumulative sum and calculate the answer.
        for (int i = 0; i < n; i++) {
            // Add the current element to the cumulative sum.
            sum += arr[i];
            
            // If the current cumulative sum has been encountered before (i.e., already in the map),
            // it means there is a subarray whose sum is equal to the current sum - some previous sum.
            // So, we add the frequency of that previous sum to the answer.
            if (mp.find(sum) != mp.end()) {
                ans += mp[sum];
            }
            
            // Update the frequency of the current cumulative sum in the map.
            mp[sum]++;
        }
        
        // Return the final answer, which represents the count of subarrays with equal sum.
        return ans;
    }
};
/*
Input:
n = 6
arr[] = {0,0,5,5,0,0}
Output: 6
Explanation: The 6 subarrays are 
[0], [0], [0], [0], [0,0], and [0,0].
*/


//106. PRODUCT ARRAY PUZZLE                                                                      {T.C = O(N), S.C = O(N)}
class Solution{
  public:
    vector<long long int> productExceptSelf(vector<long long int>& nums, int n) {
       
        //create 2 additional arrays
        vector<long long int>l(n), r(n);
        
        //initialize both arrays
        l[0] = 1;
        r[n-1] = 1;
        
        
        for(int i = 1 ; i < n ;i++){
            l[i] = nums[i-1]*l[i-1];                //prev product
        }
        for(int j = n-2 ; j >= 0 ; j--){
            r[j] = nums[j+1]*r[j+1];                //forward product
        }
        
        //final product
        for(int k = 0 ; k < n ; k++){
            nums[k] = l[k]*r[k];
        }
        
        return nums;
    }
};
/*
Input:
n = 5
nums[] = {10, 3, 5, 6, 2}
Output:
180 600 360 300 900
Explanation: 
For i=0, P[i] = 3*5*6*2 = 180.
For i=1, P[i] = 10*5*6*2 = 600.
For i=2, P[i] = 10*3*6*2 = 360.
For i=3, P[i] = 10*3*5*2 = 300.
For i=4, P[i] = 10*3*5*6 = 900.
*/


//107. SORT BY SET BIT COUNT                                                                 {T.C = O(N*LOGX), S.C = O(N)}
class Solution{
    public:
    int countSetBit(int x){
        int cnt = 0;
        while(x){
            if(x % 2 == 1){
                cnt++;
            }
            x = x/2;
        }
        return cnt;
    }
    void sortBySetBitCount(int arr[], int n)
    {
        unordered_map<int, vector<int>>mp;           //setbit->arr[i]
        int maxi = INT_MIN;
        int mini = INT_MAX;
        
        for(int i = 0 ; i < n ; i++){
            int val = countSetBit(arr[i]);
            
            mp[val].push_back(arr[i]);               //mapping setbit->arr[i]
            
            maxi = max(maxi, val);
            mini = min(mini, val);
        }
        
        //put answer in vector in decreasing order
        int idx = 0;
        for(int i = maxi ; i >= mini ; i--){
            if(mp.count(i)){
                for(auto it : mp[i]){
                    arr[idx] = it;
                    idx++;
                }
            }
        }
        return;
    }
};
/*
Input: 
arr[] = {5, 2, 3, 9, 4, 6, 7, 15, 32};
Output:
15 7 5 3 9 6 2 4 32
Explanation:
The integers in their binary
representation are:
15 - 1111
7  - 0111
5  - 0101
3  - 0011
9  - 1001
6  - 0110
2  - 0010
4  - 0100
32 - 10000
hence the non-increasing sorted order is:
{15}, {7}, {5, 3, 9, 6}, {2, 4, 32}
*/


//108. MINIMUM SWAPS TO SORT                                                            {T.C = O(N*LOGN), S.C = O(N)}
class Solution 
{
    public:
    //Function to find the minimum number of swaps required to sort the array. 
	int minSwaps(vector<int>&nums)
	{
	    int n = nums.size();
	    vector<pair<int, int>>v(n);
	    for(int i = 0 ; i < n ; i++){
	        v[i] = {nums[i], i};
	    }
	    sort(v.begin(), v.end());                       //sort the elements
	    int count = 0;
	    for(int i = 0 ; i < n ; i++){
	        if(v[i].second == i){
	            continue;
	        }
	        else{
	            count++;
	            swap(v[i], v[v[i].second]);             //swap element with its correct index
	            i--;
	        }
	    }
	    return count;
	}
};
/*
Input:
nums = {10, 19, 6, 3, 5}
Output:
2
Explaination:
swap 10 with 3 and swap 19 with 5.
*/


//109. BISHU AND SOLDIERS                                                             {T.C = O(N*LOGN), S.C = O(N)}
int main(){
	int n;
	cin>>n;
	int a[n];
	for(int i = 0 ; i < n ; i++){          //store array in 0 based indexing
		cin>>a[i];
	}

	int q;
	cin>>q;

	sort(a, a+n);

	int preSum[n+1];                      //create presum array 1 based indexing
	preSum[0] = 0;
	for(int i = 1 ; i <= n ; i++){         
		preSum[i] = preSum[i-1] + a[i-1];
	}

	while(q--){
		int x;
		cin>>x;
		int idx = upper_bound(a, a+n, x) - a;
		cout<<idx<<" "<<preSum[idx]<<endl;
	}
	return 0;
}
//same as above
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int q;
    cin >> q;

    sort(a.begin(), a.end());

    vector<int> preSum(n + 1);
    preSum[0] = 0;
    for (int i = 1; i <= n; i++) {
        preSum[i] = preSum[i - 1] + a[i - 1];
    }

    while (q--) {
        int x;
        cin >> x;
        int idx = upper_bound(a.begin(), a.end(), x) - a.begin();
        cout << idx << " " << preSum[idx] << endl;
    }

    return 0;
}
/*
input
7
1 2 3 4 5 6 7
3
3
10
2
output
3 6
7 28
2 3
*/


//110. RASTA KHESHTAK


//111. KTH SMALLEST NUMBER AGAIN                                                           {T.C = O(t * (n + q) + nlog(n) + qn), S.C = O(t*(n+q) + n)}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) {
            int x, y;                               //(1,2)=> 1 = x, 2 = y
            cin >> x >> y;                           // Corrected this line
            v.push_back({x, y});
        }

        // Step 1: Sorting
        sort(v.begin(), v.end());                        //sort on the basis of 1st element by default

        // Step 2: Merge overlapping intervals
        int idx = 0;
        for (int i = 1; i < v.size(); i++) {
            if (v[idx].second >= v[i].first) {
                v[idx].second = max(v[idx].second, v[i].second);
            } else {
                idx++;
                v[idx] = v[i];
            }
        }

        // Step 3: Searching kth element
        while (q--) {
            int k;
            cin >> k;
            int ans = -1;
            for (int i = 0; i <= idx; i++) {
                if (((v[i].second - v[i].first) + 1) >= k) {
                    ans = v[i].first + k - 1;
                    break;
                } else {
                    k = k - (v[i].second - v[i].first);
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
/*
input
1
1 3
1 5
1
3
6
output
1
3
-1
*/


//112. FIND PIVOT ELEMENT OF 2 SORTED ARRAYS                                                         
//copied
#include <iostream>
using namespace std;

// O(n) solution - Linear Search
int findPivotLinear(int array[], int n) {
    int pivot = -1;

    if (array != nullptr && n > 0) {
        pivot = 0;
        for (int i = 0; i < n - 1; i++) {
            if (array[i] > array[i + 1]) {
                pivot = i + 1;
                break;
            }
        }
    }
    return pivot;
}

// O(log n) solution - Binary Search
int findPivotBinarySearch(int array[], int n) {
    if (array == nullptr || n == 0) {
        return -1;
    }

    // Case when array is not rotated. Then first index is the pivot
    if (n == 1 || array[0] < array[n - 1]) {
        return 0;
    }

    int start = 0, end = n - 1;

    while (start <= end) {
        int mid = (start + end) / 2;
        // check if mid+1 is pivot
        if (mid < n - 1 && array[mid] > array[mid + 1]) {
            return (mid + 1);
        } else if (array[start] <= array[mid]) {
            // If array[start] <= array[mid],
            // it means from start to mid, all elements are in sorted order,
            // so pivot will be in second half
            start = mid + 1;
        } else {
            // else pivot lies in the first half, so we find the pivot in the first half
            end = mid - 1;
        }
    }

    return 0;
}

int main() {
    int array[] = {5, 4};
    int n = sizeof(array) / sizeof(array[0]);
    findPivotBinarySearchTest(array, n);
    return 0;
}

void findPivotLinearTest(int array[], int n) {
    int index = findPivotLinear(array, n);
    cout << "Pivot " << (index >= 0 ? ("found at index " + to_string(index)) : "not found!") << endl;
}

void findPivotBinarySearchTest(int array[], int n) {
    int index = findPivotBinarySearch(array, n);
    cout << "Pivot " << (index >= 0 ? ("found at index " + to_string(index)) : "not found!") << endl;
}



//113. KTH ELEMENT OF 2 SORTED ARRAY                                                     
//BRUTE FORCE                                                                          {T. C= O(N+M), S.C = O(N+M)}
class Solution{
    public:
    int kthElement(int arr1[], int arr2[], int n, int m, int k)
    {
        vector<int>arr3;
        int i = 0;
        int j = 0;
        
        while(i < n && j < m){
            if(arr1[i] < arr2[j]){
                arr3.push_back(arr1[i]);
                i++;
            }else{
                arr3.push_back(arr2[j]);
                j++;
            }
        }
        //if arr1 size is big / element is left in arr1
        while(i < n ){
            arr3.push_back(arr1[i]);
            i++;
        }
        while(j < m){
            arr3.push_back(arr2[j]);
            j++;
        }
        
        return arr3[k-1];
    }
};

//OPTIMIZED APPROACH                                                                         {T.C = O(LOG(min(N, M))), S.C = O(1)}
class Solution{
    public:
    int kthElement(int arr1[], int arr2[], int n, int m, int k)
    {
        if(n > m){
            return kthElement(arr2, arr1, m , n , k);
        }
        
        int low = max(0, k-m), high = min(k, n);
        
        while(low <= high){
            int cut1 = (low+high)/2;
            int cut2 = k-cut1;
            int l1 = cut1 == 0 ? INT_MIN : arr1[cut1 - 1];
            int l2 = cut2 == 0 ? INT_MIN : arr2[cut2 - 1];
            int r1 = cut1 == n ? INT_MAX : arr1[cut1];
            int r2 = cut2 == m ? INT_MAX : arr2[cut2];
            
            if(l1 <= r2 && l2 <= r1){
                return max(l1, l2);
            }
            else if(l1 > r2){
                high = cut1 - 1;
            }
            else{
                low = cut1 + 1;
            }
        }
        return 1;
    }
};
/*
Input:
arr1[] = {2, 3, 6, 7, 9}
arr2[] = {1, 4, 8, 10}
k = 5
Output:
6
Explanation:
The final sorted array would be -
1, 2, 3, 4, 6, 7, 8, 9, 10
The 5th element of this array is 6.
*/


//114. AGGRESIVE COW                     {max(min) pattern}                                              {T.C = O(N*LOG(MAX_DIST)), S.C = O(1)}
// Function to check if it is possible to place 'cow' number of cows with a minimum distance 'dist' between them.
bool canWePlace(vector<int>& stalls, int dist, int cow){
    int cowCnt = 1; // Counter to track the number of cows placed.
    int last = stalls[0]; // Variable to store the position of the last placed cow.

    // Iterate through the stalls to check if 'cow' cows can be placed with distance 'dist' between them.
    for(int i = 1 ; i < stalls.size(); i++){
        if(stalls[i] - last >= dist){
            cowCnt++;
            last = stalls[i];
        }
        if(cowCnt >= cow){ // If 'cow' cows have been placed, return true.
            return true;
        }
    }

    // If it's not possible to place 'cow' cows with distance 'dist', return false.
    return false;
}

// Function to find the maximum distance among all minimum distances for placing 'k' cows in 'stalls'.
int aggressiveCows(vector<int> &stalls, int k)
{
    int n = stalls.size();
    sort(stalls.begin(), stalls.end()); // Sort the stalls in ascending order.

    int low = 1 , high = stalls[n-1] - stalls[0]; // Set the search range for the minimum distance.
    
    // Binary search to find the maximum distance among all minimum distances.
    while(low <= high){
        int mid = low + (high-low)/2;
        if(canWePlace(stalls, mid, k) == true){
            low = mid + 1; // If 'k' cows can be placed with distance 'mid', search for higher distances.
        } else {
            high = mid - 1; // If 'k' cows cannot be placed with distance 'mid', search for lower distances.
        }
    }

    // Return the maximum distance among all minimum distances for placing 'k' cows in 'stalls'.
    return high;
}
/*
Sample Input 1 :
6 4
0 3 4 7 10 9
Sample Output 1 :
3
*/


//115. ALLOCATE MINIMUM NUMBER OF PAGES      {min(max) pattern}                                                {T.C = O(N*LOGN), S.C = O(1)}
/*Allocate the book to m students such that Maximum no. of pages assigned to a student is minimum value*/
bool isPossible(vector<int> a, int n, int m, int mid) {
    int studentCount = 1;
    int pageSum = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] > mid) {
            return false; // The current book's pages exceed the 'mid' value, which is not allowed.
        }
        if (pageSum + a[i] <= mid) {
            pageSum += a[i];
        } else {
            studentCount++;
            if (studentCount > m) {
                return false; // The required number of students is greater than 'm'.
            }
            pageSum = a[i];
        }
    }
    return true;
}

int findPages(vector<int>&a ,int n ,int m){
    int s = 0;
    int sum = 0;
    for(int i = 0 ; i < n; i++){
        sum += a[i];
    }
    int e = sum;
    int ans = -1;
    int mid = s + (e - s)/2;
    while(s <= e){
        if(isPossible(a , n , m , mid)){
            ans = mid;
            e  = mid - 1;
        }
        else{
            s = mid + 1;
        }
        mid = s + (e - s)/2;
    }
    if(m > n){
        return -1;
    }
    return ans;
}
/*
Input:
N = 4
A[] = {12,34,67,90}
M = 2
Output:113
Explanation:Allocation can be done in 
following ways:
{12} and {34, 67, 90} Maximum Pages = 191
{12, 34} and {67, 90} Maximum Pages = 157
{12, 34, 67} and {90} Maximum Pages =113.
Therefore, the minimum of these cases is 113,
which is selected as the output.
*/


//116. EKO EKO                                                                                    {T.C = O(N*LOGN), S.C = O(1)}
bool solve(int *arr, int n , int m, int mid ){
	int sum = 0;
	for(int i = 0 ; i < n ; i++){
		if(arr[i] > mid){
			sum += arr[i]-mid;
		}
	}
	if(sum >= m){
		return true;
	}
	return false;
}
int main() {
	int n , m ;                          //n = size of array , m = min lenght required of wood
	cin>>n>>m;
	
	int arr[n];
	
	for(int i = 0 ; i < n ; i++){
		cin>>arr[i];
	}
	
	int lb = 0;
	int ub = *max_element(arr, arr+n);
	int ans = 0;
	
	while(lb <= ub){
		int mid = lb + (ub-lb)/2;
		if(solve(arr, n , m , mid)){
			ans = mid;
			lb = mid+1;                 //neglect left elements                  
		}
		else{
			ub = mid-1;                 //neglect right elements
		}
	}
	cout<<ans;
}
/*
Input:
4 7
20 15 10 17
Output:
15
*/


//117. MAXIMUM PROFIT IN JOB SCHEDULING                                                          {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    static bool comp(vector<int>a, vector<int>b){
        return a[1] < b[1];
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>>v(n);
        for(int i = 0 ; i < n ; i++){
            int x = startTime[i];
            int y = endTime[i];
            int p = profit[i];

            v[i] = {x, y, p};
        }

        sort(v.begin(), v.end(), comp);              //sort on the basis of ending time
        vector<int>dp(n);

        dp[0] = v[0][2];

        for(int i = 1 ; i < n ; i++){
            int incl = v[i][2];
            int last = -1;
            int low = 0;
            int high = i-1;
            while(low <= high){
                int mid = low + (high-low)/2;
                if(v[mid][1] <= v[i][0]){
                    last = mid;
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
            if(last != -1){
                incl += dp[last];
            }
            int excl = dp[i-1];
            dp[i] = max(incl,  excl);
        }
        return dp[n-1];
    }
};
/*
Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job. 
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
*/


//118. ARITHMETIC NUMBER                                                                {T.C = O(1), S.C = O(1)}
class Solution {
public:
    int inSequence(int A, int B, int C) {
        //using formula = An = A + (n-1)D => n = (An - A)/D + 1       
        //An == B, A == A , D == C
        
        if(C == 0){
            if(A == B){
                return 1;
            }else{
                return 0;
            }
        }
        else{
            if((B-A)/C < 0){                       //check -ve
                return 0;
            }else{
                if((B-A)%C == 0){
                    return 1;
                }else{
                    return 0;
                }
            }
        }
    }
};
/*
Input: A = 1, B = 3, C = 2
Output: 1
Explaination: 3 is the second term of the 
sequence starting with 1 and having a common 
difference 2.
*/


//finding total number of trailing zeroes
/*
int sum = 0;
while(n/5 > 0){
    sum += n/5;
    n = n/5;
}
return sum;
*/
//119. SMALLEST FACTORIAL NUMBER                                                                         {T.C = O(LOG5(N)), S.C = O(1)}
class Solution {
public:
    int countTrailingZeros(int n) {
        int count = 0;
        while (n > 0) {
            n /= 5;
            count += n;
        }
        return count;
    }

    int findNum(int n) {
        int lo = 0, hi = 5 * n;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int zeros = countTrailingZeros(mid);
            if (zeros >= n) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
};
/*
Input:
n = 1
Output: 5
Explanation : 5! = 120 which has at
least 1 trailing 0.
*/


//120. PAINTERS PARTITION PROBLEM
//same as book allocation


//121. ROTI PARATHA
bool solve(int *a, int n , int par , int mid){
	int time = 0;
	int paratha = 0;
	for(int i = 0 ; i < n ; i++){
		time = a[i];
		int j = 2;
		while(time <= mid){
			paratha++;
			time = time + a[i]*j;
			j++;
		}
		if(paratha >= par){
			return 1;
		}
	}
	return 0;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int par;
		cin>>par;
		int n;
		cin>>n;
		int a[n];
		for(int i = 0 ; i < n ; i++){
			cin>>a[i];
		}

		int lb = 0;
		int ub = 1e8;                 //can use 1e9 every binary search
		int ans = 0 ;
		while(lb <= ub){
			int mid = lb + (ub-lb)/2;
			if(solve(a, n , par, mid)){
				ans = mid;
				ub = mid-1;
			}else{
				lb = mid+1;
			}
		}
        cout<<ans<<endl;
	}
}
/*
Input:
3
10
4 1 2 3 4
8
1 1
8
8 1 1 1 1 1 1 1 1

Output:
12
36
1
*/


//122. DOUBLE HELIX                                                                              {T.C = O(N), S.C = O(1)}
int main(){
	int n;
	cin>>n;
	while(true){
		if(n == 0){
			break;
		}
		else{
			int a[n];
			for(int i = 0 ; i < n ; i++){
				cin>>a[i];
			}
			int m;
			int b[m];
			for(int j = 0 ; j < m ; j++){
				cin>>b[j];
			}

			int s1 = 0, s2 = 0;                     //temporary sum between two common bridge
			int i = 0, j = 0;                       //each initial pointer to both array
			int ma = 0;                             //merge array sum
			while(i < n && j < m){
				if(a[i] < b[j]){
					s1 += a[i++];
				}
				else if(b[j] < a[i]){
					s2 += b[j++];
				}
				else{
					ma = ma + max(s1, s2) + a[i];
					s1 = s2 = 0;
					i++;
					j++;
				}
			}
			while(i < n){
				s1 += a[i++];
			}
			while(j < m){
				s2 += b[j++];
			}
			ma = ma + max(s1, s2);
			cout<<ma<<endl;
		}
	}

	return 0;
}
/*
Input:
13 3 5 7 9 20 25 30 40 55 56 57 60 62
11 1 4 7 11 14 25 44 47 55 57 100
4 -5 100 1000 1005
3 -12 1000 1001
0
Output:
450
2100
*/


//123. SUBSETS SUMS                                                                             {T.C = O(EXP), S.C = O(N)}
void solve(int *arr, int start, int end , vector<int>&v){
	int s = 0;
	int n =  end-start + 1;
	for(int i = 0 ;  i < (1<<n) ; i++){
		s = 0;
		int j = start;
		int x = i;
		while(x){
			int l = x&1;
			if(l){
				s += arr[j];
				j++;
				x = x>>1;
			}
			v.push_back(s);
		}
	}
}
int main(){
	int n, a, b;
	cin>>n>>a>>b;
	int arr[n];
	for(int i = 0 ; i < n ; i++){
		cin>>arr[i];
	}
	vector<int>v1, v2;
	solve(arr, 0, (n/2)-1, v1);
	solve(arr, (n/2), n-1 , v2);
	sort(v2.begin(), v2.end());
	int count = 0;
	for(int i = 0 ; i < v1.size(); i++){
		int low = lower_bound(v2.begin(), v2.end(), a-v1[i]) - v2.begin();
		int high = upper_bound(v2.begin(), v2.end(),b-v1[i]) - v2.begin();
		count += high-low;
	}
	cout<<count;

	return 0;
}
/*
Input:
3 -1 2
1
-2
3
Output:
5
*/


//124. COUNT INVERSIONS                                                                                {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    long long int merge(long long arr[], long long low, long long mid, long long high) {
        long long temp[high - low + 1];
        long long left = low;
        long long right = mid + 1;
        long long cnt = 0;
        long long k = 0;

        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp[k++] = arr[left++];
            } else {
                temp[k++] = arr[right++];
                cnt += (mid - left + 1);
            }
        }

        while (left <= mid) {
            temp[k++] = arr[left++];
        }

        while (right <= high) {
            temp[k++] = arr[right++];
        }

        // Copy the elements back to the original array
        for (long long i = low, j = 0; i <= high; i++, j++) {
            arr[i] = temp[j];
        }

        return cnt;
    }

    long long int mS(long long arr[], long long low, long long high) {
        long long cnt = 0;
        if (low < high) {
            long long mid = (low + high) / 2;
            cnt += mS(arr, low, mid);
            cnt += mS(arr, mid + 1, high);
            cnt += merge(arr, low, mid, high);
        }

        return cnt;
    }

    long long int inversionCount(long long arr[], long long N) {
        return mS(arr, 0, N - 1);
    }
};
/*
Input: N = 5, arr[] = {2, 4, 1, 3, 5}
Output: 3
Explanation: The sequence 2, 4, 1, 3, 5 
has three inversions (2, 1), (4, 1), (4, 3).
*/


//125. IN PLACE MERGE SORT / MERGE SORT                                                               {T.C = O(N*LOGN), S.C = O(N)}
class Solution
{
    public:
    void merge(int arr[], int l, int m, int r)
    {
       //l = starting index of 1st array , m = ending index of first array 
       //m+1 = starting index of 2nd array , r = ending index of second array
       int n1 = m-l+1;                   //length of 1st array
       int n2 = r-m;                     //length of 2nd array
       
       int *a = new int[n1];
       int *b = new int[n2];
       
       for(int i = 0 ; i<n1 ; i++){
           a[i] = arr[l+i];
       }
       
       for(int i = 0 ; i<n2 ; i++){
           b[i] = arr[m+1 + i];
       }

       int i = 0 , j = 0 , k=l;
       
       while(i<n1 && j<n2){
           
           if(a[i] < b[j]){
                arr[k++] = a[i++];
                /*or
                arr[k] = a[i];
                k++;
                i++
                */
           }
           else{
                arr[k++] = b[j++];
           }
       }
       //1st array elements left
       while(i<n1){
           arr[k++] = a[i++];
       }
       //2nd array elements left
       while(j < n2){
           arr[k++] = b[j++]; 
       }
    }
    
    
    void mergeSort(int arr[], int l, int r)
    {
        if(l<r){
            int mid = (l+r)/2;
            mergeSort(arr , l , mid);
            mergeSort(arr , mid+1 , r);
            merge(arr , l , mid , r);
        }
    }
};
/*
Input:
N = 5
arr[] = {4 1 3 9 7}
Output:
1 3 4 7 9
*/


//126. PARTITIONING AND SORTING ARRAYS WIHT MANY REPEATED ENTRIES


/*--------------------------------------------------------    THE END     --------------------------------------------------------------------*/