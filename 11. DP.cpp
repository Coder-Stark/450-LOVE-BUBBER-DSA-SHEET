//DP (DYANAMIC PROGRAMMING)

#include<bits/stdc++.h>
using namespace std;


//320. COIN CHANGE
//RECURSION   (TLE)                                                               {T.C = O(EXP), S.C = O(1)}
class Solution {
  public:
    long long int solve(int coins[], int i, int sum){
        if(sum == 0){
            return 1;
        }
        if(sum < 0 || i < 0){
            return 0;
        }
        long long int incl = solve(coins, i, sum-coins[i]);           
        long long int excl = solve(coins, i-1, sum);                 //i-1 => reverse traversal
        return incl + excl;
    }
    long long int count(int coins[], int N, int sum) {
        return solve(coins, N-1, sum);                      //last index
    }
};

//RECURSION + MEMOIZATION                                                        {T.C = O(N*SUM), S.C = O(N*SUM)}
class Solution {
  public:
    long long int solveMem(int coins[], int i, int sum, vector<vector<long long>>&dp){
        //base case
        if(sum == 0){
            return 1;                                     //just not include any thing(coin)
        }
        if(sum < 0 || i < 0){
            return 0;
        }
        
        //step3 if answer present return it
        if(dp[i][sum] != -1){
            return dp[i][sum];
        }
        
        long long int incl = solveMem(coins, i, sum-coins[i], dp);           
        long long int excl = solveMem(coins, i-1, sum, dp);                 //i-1 => reverse traversal
        dp[i][sum] = incl + excl;
        return dp[i][sum];
    }
    long long int count(int coins[], int N, int sum) {
        //step1 create dp vector
        vector<vector<long long>>dp(N+1, vector<long long>(sum+1, -1));
        return solveMem(coins, N-1, sum, dp);                      //reverse traversal {sort(highest denomination[coin types])}
    }
};
/*
Input:
N = 4, Sum = 10
coins = {2,5,3,6}
Output: 5
Explanation: Five Possible ways are: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}.
*/


//321. 0-1 KNAPSACK PROBLEM                                                           {T.C = O(N*M), S.C = O(N*M)}
class Solution
{
    public:
    int solveMem(int W, int wt[], int val[], int n, int i, vector<vector<int>>&dp){
        //base case
        if(i == n){
            return 0;
        }
        
        //step3 if answer already present return it
        if(dp[i][W] != -1){
            return dp[i][W];
        }
        
        int incl = 0;
        int excl = 0;
        if(W >= wt[i]){
            incl = val[i] + solveMem(W-wt[i], wt, val, n, i+1, dp);
        }
        excl = 0 + solveMem(W, wt, val, n, i+1, dp);
        
        //step2 store ans in dp
        dp[i][W] = max(incl, excl);
        return dp[i][W];
    }
    int knapSack(int W, int wt[], int val[], int n) 
    { 
       //step1 create a dp vector
       vector<vector<int>>dp(n+1, vector<int>(W+1, -1));
       return solveMem(W,wt, val, n, 0, dp);                         //forward traversal
    }
};
/*
Input:
N = 3
W = 4
values[] = {1,2,3}
weight[] = {4,5,1}
Output: 3
Explanation: Choose the last item that weighs 1 unit and holds a value of 3. 
*/


//322. nCr
//RECURSION
class Solution{
public:
    int nCr(int n, int r){
        int mod = 1e9+7;
        if(n == r || r == 0){                         //nCn == nC0 == 1
            return 1;
        }
        return (nCr(n-1, r-1) + nCr(n-1, r))% mod;     //nCr = (n-1)C(r-1) + (n-1)C(r)
    }
};

//RECURSION + MEMOIZATION                                                       {T.C = O(N*M), S.C = O(N*M)}
class Solution{
public:
        int mod = 1e9+7;
    int solveMem(int n, int r, vector<vector<int>>&dp){
        //base case
        if (r > n || r < 0) {
            return 0;
        }
        if(r == n || r == 0){
            return 1;
        }
        
        //step3 if answer is already present return it
        if(dp[n][r] != -1){
            return dp[n][r];
        }
        
        int ans = (solveMem(n-1, r-1, dp) + solveMem(n-1, r, dp))%mod;
        
        //step2 store ans in dp
        dp[n][r] = ans;
        return dp[n][r];
    }
    int nCr(int n, int r){
        //step1 create a dp vector
        vector<vector<int>>dp(n+1, vector<int>(r+1, -1));
        return solveMem(n, r, dp);
    }
};
/*
Input: n = 3, r = 2
Output: 3
Explaination: 3C2 = 3. 
*/

//323. nPr or CALCULATE THE COEFFICIENT
//RECURSION
class Solution{
    public:
    int permutationCoeff(int n, int r){
        if (r > n || r < 0) {
            return 0;
        }
        if(r == 0){                                                         //nP0 == nPn == 1
            return 1;
        }
        return (r*permutationCoeff(n-1, r-1) + permutationCoeff(n-1, r));   //nPr = r * (n-1)P(r-1) + (n-1)P(r)
    }
};

//RECURSTION (WORKING)
class Solution{
    public:
    int mod = 1e9+7;
    long long solve(int n, int k){
        //base case
        if(k == 0){
            return 1;
        }
        return (n*solve(n-1, k-1))%mod;                        //nPr = n* (n-1)P(r-1)
    }
    int permutationCoeff(int n, int k){
        return solve(n, k);
    }
};

//RECURSION + MEMOIZATION
class Solution{
    public:
    int mod = 1e9 + 7;
    long long int solveMem(int n, int r, vector<vector<int>>&dp){
        //base case
        if(r > n || r < 0){
            return 0;
        }
        if(r == 0){
            return 1;
        }
        
        //step3 if answer already present return it
        if(dp[n][r] != -1){
            return dp[n][r];
        }
        
        int ans = (r * solveMem(n-1, r-1, dp) + solveMem(n-1, r, dp) ) % mod;
        //step2 store ans in dp
        dp[n][r] = ans;
        return dp[n][r];
    }
    int permutationCoeff(int n, int r){
        //step1 create a dp vector
        vector<vector<int>>dp(n+1,vector<int>(r+1, -1));
        return solveMem(n, r, dp);
    }
};

//OPTIMIZED APPROACH
/*
Input: n = 10, k = 2
Output: 90
Explanation: For first case:
Ans = 10! / (10 - 2)! = 10! / 8!
10! is 8!*9*10 and 8! is 8!
Ans = 9*10 = 90
*/


//324. NTH CATALAN NUMBER                                                          {T.C = O(N^2), S.C = O(N)}
//TABULATION METHOD
class Solution
{
    public:
    int findCatalan(int n) 
    {
        long long mod = 1e9 + 7;  
        //step1 create a dp vector 0
        vector<long long>dp(n+1, 0);
        
        //step2 analyze base case
        dp[0] = 1;
        dp[1] = 1;
        
        //step3 loop
        for(int i = 2 ; i <= n ; i++){
            for(int j = 0 ; j < i ; j++){
                dp[i] += dp[j]*dp[i-j-1];            //i = j*i-j-1
                dp[i] %= mod;
            }
        }
        return dp[n];
    }
};
/*
Input:
N = 5
Output: 42
*/


//325. MATRIX CHAIN MULTIPLICATION                                                
//RECURSION                                                                     {T.C = O(EXP), S.C = O(1)}
class Solution{
public:
    int solve(int arr[], int i, int j){
        //base case
        if(i == j){
            return 0;
        }
        int mini = INT_MAX;
        for(int k = i ; k < j ; k++){              //k -> i-> j-1
            int steps = arr[i-1]*arr[k]*arr[j] + solve(arr, i, k) + solve(arr, k+1, j);
            mini = min(mini, steps);
        }
        return mini;
    }
    int matrixMultiplication(int N, int arr[])
    {
        return solve(arr, 1, N-1);                //i = 1, j = n-1   {i-1 == use in k}
    }
};

//RECURSION + MEMOIZATION                                                        {T.C = O(N^2), S.C = O(N)}
class Solution{
public:
    int solveMem(int arr[], int i, int j, vector<vector<int>>&dp){
        //base case
        if(i == j){
            return 0;
        }
        int mini = INT_MAX;
        
        //step3 if answer already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        for(int k = i ; k < j ; k++){              //k -> i-> j-1
            int steps = arr[i-1]*arr[k]*arr[j] + solveMem(arr, i, k, dp) + solveMem(arr, k+1, j, dp);
            mini = min(mini, steps);
        }
        
        //step2 store answer in dp
        dp[i][j] = mini;
        return dp[i][j];
    }
    int matrixMultiplication(int N, int arr[])
    {
        //step1 create a dp vector
        vector<vector<int>>dp(N+1, vector<int>(N+1, -1));
        return solveMem(arr, 1, N-1, dp);                //i = 1, j = n-1   {i-1 == use in k}
    }
};
/*
Input: N = 5
arr = {40, 20, 30, 10, 30}
Output: 26000
Explanation: There are 4 matrices of dimension 
40x20, 20x30, 30x10, 10x30. Say the matrices are 
named as A, B, C, D. Out of all possible combinations,
the most efficient way is (A*(B*C))*D. 
The number of operations are -
20*30*10 + 40*20*10 + 40*10*30 = 26000.
*/


//326. EDIT DISTANCE                                                            {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int solve(int i, int j, string &a, string &b, vector<vector<int>>& dp) {
        //base case
        if (i == a.length()) {           //n < m (n = a.length, m = b.length)
            return b.length() - j;
        }

        if (j == b.length()) {
            return a.length() - i;
        }

        //step3 if answer already present return it
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int ans;
        if (a[i] == b[j]) {
            ans = solve(i + 1, j + 1, a, b, dp);
        } else {
            int insertAns = 1 + solve(i, j + 1, a, b, dp);
            int deleteAns = 1 + solve(i + 1, j, a, b, dp);
            int replaceAns = 1 + solve(i + 1, j + 1, a, b, dp);
            ans = min(insertAns, min(deleteAns, replaceAns));
        }

        //step2 store answer in dp
        dp[i][j] = ans;
        return ans;
    }

    int editDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        //step1 create a dp vector
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, word1, word2, dp);
    }
};
/*
Input: 
s = "geek", t = "gesek"
Output: 1
Explanation: One operation is required 
inserting 's' between two 'e's of s.
*/


//327. PARTITION EQUAL SUBSET SUM                                                {T.C = O(N*M), S.C = O(N*M)}
class Solution{
public:
    bool solveMem(int arr[], int i ,int n, int target, vector<vector<int>>&dp){
        //base case
        if(i >= n || target < 0){
            return 0;
        }
        if(target == 0){
            return 1;
        }
        //step 3: check if the answer is found, return it
        if(dp[i][target] != -1){
            return dp[i][target];
        }
        
        bool incl = solveMem(arr, i+1, n, target-arr[i], dp);
        bool excl = solveMem(arr, i+1, n , target, dp);
        
        //step2 store ans in dp
        dp[i][target] = incl or excl;
        return dp[i][target];
    }
    int equalPartition(int N, int arr[])
    {
        int total = 0;
        for(int i = 0 ; i < N ; i++){
            total += arr[i];
        }
        if(total & 1){
            return 0;
        }
        int target = total/2;
        
        //step1 create dp vector
        vector<vector<int>>dp(N+1, vector<int>(target+1, -1));
        return solveMem(arr, 0, N, target, dp);
    }
};
/*
Input: N = 4
arr = {1, 5, 11, 5}
Output: YES
Explanation: 
The two parts are {1, 5, 5} and {11}.
*/


//328. FRIENDS PAIRING PROBLEM                                                 {T.C = O(N), S.C = O(N)}
class Solution
{
public:
    int countFriendsPairings(int n) 
    { 
        int mod = 1e9 + 7;
        //step1 create a dp vector 0
        vector<long>dp(n+1, 0);                    //use long not int
        
        //step2 analyze base case
        dp[1] = 1;                        //1 person
        dp[2] = 2;                        //2 person (single, mingle)
        
        //loop
        for(int i = 3 ; i <= n ; i++){
            dp[i] = dp[i-1] + (i-1)*dp[i-2];      //single + paired(accecpt single * pairing)  //not i*dp[i-1] + iC2*dp[i-2]   {internal permutaion}
            dp[i] %= mod;
        }
        return dp[n] % mod;
    }
};  
/*
Input:N = 3
Output: 4
Explanation:
{1}, {2}, {3} : All single
{1}, {2,3} : 2 and 3 paired but 1 is single.
{1,2}, {3} : 1 and 2 are paired but 3 is single.
{1,3}, {2} : 1 and 3 are paired but 2 is single.
Note that {1,2} and {2,1} are considered same.
*/


//329. GOLD MINE 


//330. PROBLEM ASSEMBLY LINE SCHEDULING PROBLEM                                                       {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int carAssembly(vector<vector<int>>& a, vector<vector<int>>& T, vector<int>& e, vector<int>& x) {
        int prev1 = e[0] + a[0][0];
        int prev2 = e[1] + a[1][0];
      
        int curr1, curr2;
        int n = a[0].size(); 
        for (int i = 1; i < n; i++) {                               //the 0th station is the entry point
            curr1 = min(prev1, prev2 + T[1][i]) + a[0][i];          //min(same line, another's line) + curr element
            curr2 = min(prev2, prev1 + T[0][i]) + a[1][i];
            prev1 = curr1;
            prev2 = curr2;
        }
        return min(curr1 + x[0], curr2 + x[1]);                     //currsum + last element
    }
};
/*
Input: N = 4
a[2][] = {{4, 5, 3, 2}, 
          {2, 10, 1, 4}
         }
T[2][] = {{0,7, 4, 5},
          {0,9, 2, 8}}
e[2] = {10,12}, x[2] = {18,7}

Output: 35
Explanation: 
So the minimum time taken by the car is 35.
*/


//331. PAINTING THE FENCE                                                    {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    long long solveMem(int n, int k , vector<int>&dp){
        int mod = 1e9 + 7;
        //base case
        if(n == 1){
            // return k;                            //1 post can be fill by any color (k)
            return k % mod;
        }
        if(n == 2){
            // return k + k*(k-1);
            return (k + ( (1ll * k *(k-1)) % mod ) )%mod;
        }
        
        //step3 if answer already present return it
        if(dp[n] != -1){
            return dp[n];
        }
        
        // long long ans = (k-1)*solveMem(n-2, k, dp) + (k-1)*solveMem(n-1, k, dp);   //same + different
        long long ans = ( ( 1LL * (k - 1) * solveMem(n - 2, k, dp) % mod ) + ( 1LL * (k - 1) * solveMem(n - 1, k, dp) % mod ) ) % mod; // Same + Different

        //step2 store ans in dp
        dp[n] = ans;
        return dp[n];
        
    }
    long long countWays(int n, int k){
        //step1 create a dp vector
        vector<int>dp(n+1, -1);
        return solveMem(n, k, dp);
    }
};
/*
Input:
N=2,  K=4
Output: 16
*/


//332. MAXIMIZE THE CUT SEGMENTS                                                 {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    int solveMem(int n, int x, int y, int z, vector<int>&dp){
        //base case
        if(n == 0){                                          //length = 0
            return 0;
        }
        
        if(n < 0){
            return INT_MIN;
        }
        //step3 if answer already present return it
        if(dp[n] != -1){
            return dp[n];
        }
        
        int a = solveMem(n-x, x, y, z, dp);
        int b = solveMem(n-y, x, y, z, dp);
        int c = solveMem(n-z, x, y, z, dp);
        
        int ans = 1 + max({a, b, c});                        //1 = current cut + rest 
        
        //step2 store ans in dp
        dp[n] = ans;
        return dp[n];
    }
    int maximizeTheCuts(int n, int x, int y, int z)
    {
        //step1 create a dp vector
        vector<int>dp(n+1, -1);
        int res =  solveMem(n, x, y, z, dp);
        if(res < 0){
            return 0;
        }
        return res;
    }
};
/*
Input:
N = 4
x = 2, y = 1, z = 1
Output: 4
Explanation:Total length is 4, and the cut
lengths are 2, 1 and 1.  We can make
maximum 4 segments each of length 1.
*/


//333. LONGEST COMMON SUBSEQUENCE                                                    {T.C = O(N*M), S.C = O(N*M)}
class Solution
{
    public:
     int solveMem(string& a, string& b, int i, int j, vector<vector<int>> &dp){

        // Base Case
        if(i == a.length() || j == b.length()){
           return 0; 
        }

        //step3 if ans already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
    
        int ans = 0;
        if(a[i] == b[j]){
            ans = 1 + solveMem(a, b, i+1, j+1, dp);                             //curr char(1) + rest
        }else{
            ans = max(solveMem(a, b, i+1, j, dp), solveMem(a, b, i, j+1, dp));
        }

        //step2 store ans in dp
        return dp[i][j] = ans;
    }
    int lcs(int n, int m, string s1, string s2)
    {
        //step1 create a dp vector
        vector<vector<int>>dp(n+1, vector<int>(m+1, -1));
        return solveMem(s1, s2, 0, 0, dp);                 //i = 0, j = 0;
    }
};
/*
Input:
A = 6, B = 6
str1 = ABCDGH
str2 = AEDFHR
Output: 3
Explanation: LCS for input strings “ABCDGH” and “AEDFHR” is “ADH” of length 3.
*/


//334. LONGEST REPEATES SUBSEQUENCE                                                  {T.C = O(N^2), S.C = O(N^2)}
//same as above(logest common subsequence) {just take 2 string and neglect to update on same index}
class Solution {
	public:
	    int solveMem(string str, int i, int j, vector<vector<int>>&dp){
	        //base case
	        if(i == str.length() || j == str.length()){
	            return 0;
	        }
	        
	        //step3 if ans is already present return it
	        if(dp[i][j] != -1){
	            return dp[i][j];
	        }
	        
	        int ans = 0;
	        if(str[i] == str[j] && i != j){                     //i != j all same like common subsequence
	            ans = 1 + solveMem(str, i+1, j+1, dp);
	        }else{
	            ans = max(solveMem(str, i+1, j, dp), solveMem(str, i, j+1, dp));
	        }
	        
	        //step2 store ans in dp
	        return dp[i][j] = ans;
	    }
		int LongestRepeatingSubsequence(string str){
		    int n = str.length();
		    //step1 create dp vector
		    vector<vector<int>>dp(n+1, vector<int>(n+1, -1));
		    return solveMem(str, 0, 0, dp);
		}
};
/*
Input:
str = "axxxy"
Output: 2
Explanation:
The given array with indexes looks like
a x x x y 
0 1 2 3 4

The longest subsequence is "xx". 
It appears twice as explained below.

subsequence A
x x
0 1  <-- index of subsequence A
------
1 2  <-- index of str 


subsequence B
x x
0 1  <-- index of subsequence B
------
2 3  <-- index of str 

We are able to use character 'x' 
(at index 2 in str) in both subsequences
as it appears on index 1 in subsequence A 
and index 0 in subsequence B.
*/


//335. LONGEST INCREASING SUBSEQUENCE                                                 
//RECURSION                                                                     {T.C = O(EXP), S.C = O(1)}
class Solution
{
    public:
    int solve(int a[], int n , int currIdx, int preIdx){
        //base case
        if(currIdx == n){
            return 0;
        }
        
        int incl=0, excl=0;
        if(preIdx == -1 || a[currIdx] > a[preIdx]){
            incl = 1 + solve(a, n, currIdx+1, currIdx);       //curr++ , prev = curr
        }
        excl = 0 + solve(a, n, currIdx+1, preIdx);
        
        int ans = max(incl, excl);
        return ans;
    }
    int longestSubsequence(int n, int a[])
    {
       return solve(a, n, 0, -1);                    //0 = index, -1 = prev index
    }
};

//RECURSION + MEMOIZATION (TLE)                                                      {T.C = O(N^2), S.C = O(N^2)}
class Solution
{
    public:
    int solveMem(int a[], int n , int currIdx, int preIdx, vector<vector<int>>&dp){
        //base case
        if(currIdx == n){
            return 0;
        }
        
        //step3 if ans already present return it
        if(dp[currIdx][preIdx+1] != -1){
            return dp[currIdx][preIdx+1];
        }
        int incl=0, excl=0;
        if(preIdx == -1 || a[currIdx] > a[preIdx]){
            incl = 1 + solveMem(a, n, currIdx+1, currIdx, dp);       //curr++ , prev = curr
        }
        excl = 0 + solveMem(a, n, currIdx+1, preIdx, dp);            //curr++, prev same
        
        int ans = max(incl, excl);
        //step2 store ans in dp
        return dp[currIdx][preIdx+1] = ans;
    }
    int longestSubsequence(int n, int a[])
    {
       //step1 create a dp vector
       vector<vector<int>>dp(n+1, vector<int>(n+2, -1));      //n+2 = shifting prevIndx -1 to 1
       return solveMem(a, n, 0, -1, dp);                    //0 = index, -1 = prev index
    }
};
/*
Input:
N = 16
A = {0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15}
Output: 
6
Explanation:
There are more than one LIS in this array. One such Longest increasing subsequence is {0,2,6,9,13,15}.
*/


//336. SPACE OPTIMIZATION SOLUTION OF LCS


//337. LCS OF THREE STRINGS                                                         {T.C = O(N1*N2*N3), S.C = O(N1*N2*N3)}
int solveMem(string a, string b, string c, int i, int j , int k, vector<vector<vector<int>>>&dp){
    //base case
    if(i == a.length() || j == b.length() || k == c.length()){
        return 0;
    }
    
    //step3 if ans already present return it
    if(dp[i][j][k] != -1){
        return dp[i][j][k];
    }
    
    int ans = 0;
    if(a[i] == b[j] && b[j] == c[k]){
        ans = 1 + solveMem(a, b, c, i+1, j+1, k+1, dp);
    }else{
        ans = max({solveMem(a, b, c, i+1, j, k, dp), solveMem(a, b, c, i+1, j+1, k, dp), solveMem(a, b, c, i+1, j , k+1, dp),
                   solveMem(a, b, c, i, j+1, k, dp), solveMem(a, b, c, i, j+1, k+1, dp), solveMem(a, b, c, i, j, k+1, dp)
                 });                                                                                    
    }
    
    //step2 store ans in dp
    return dp[i][j][k] = ans;
    
}
int LCSof3 (string A, string B, string C, int n1, int n2, int n3)
{
    //step1 create a dp vector
    vector<vector<vector<int>>>dp(n1+1, vector<vector<int>>(n2+1, vector<int>(n3+1, -1)));
    // or  dp[n1+1][n2+1][n3+1];
    
    return solveMem(A, B, C, 0, 0, 0, dp);
}
/*
Input:
A = "geeks", B = "geeksfor", 
C = "geeksforgeeks"
Output: 5
Explanation: "geeks"is the longest common
subsequence with length 5.
*/


//338. MAXIMUM SUM INCREASING SUBSEQUENCE                                                           {T.C = O(N^2), S.C = O(N)}
//(TLE)
class Solution{
	int solveMem(int arr[], int n, int currIdx, int prevIdx, vector<vector<int>>&dp){
	    //base case
	    if(currIdx == n) {
	        return 0;
	    }
	    
	    //step3 if ans already present return it
	    if(dp[currIdx][prevIdx +1] != -1){
	        return dp[currIdx][prevIdx+1];
	    }
	    
	    int inclSum = 0;
	    if(prevIdx == -1 || arr[currIdx] > arr[prevIdx]){
	        inclSum = arr[currIdx] + solveMem(arr, n, currIdx+1, currIdx, dp);  //prevIdx = currIdx , add currelement
	    }
	    int exclSum = 0 + solveMem(arr, n, currIdx+1, prevIdx, dp);              //prevIdx is same
	    
	    //step2 store ans in dp
	    return dp[currIdx][prevIdx+1] = max(inclSum, exclSum);
	}
	public:
	int maxSumIS(int arr[], int n)  
	{  
	    vector<vector<int>>dp(n+1, vector<int>(n+2, -1));       //n+2 => shifting preIdx -1 to 0
	    return solveMem(arr, n, 0, -1, dp);                     //0 = currIdx, -1 = preIdx
	}  
};
/*
Input: 
N = 5, arr[] = {1, 101, 2, 3, 100} 
Output: 
106
Explanation:
The maximum sum of a increasing sequence is obtained from {1, 2, 3, 100},
*/


//339. COUNT THE SUBARRAYS HAVING PRODUCT LESS THAN K                                           {T.C = O(N), S.C = O(1)}
class Solution{
  public:
    int countSubArrayProductLessThanK(const vector<int>& a, int n, long long k) {
        long long pro = 1;
        int l = 0;
        int r = 0;
        int count = 0;
        
        while(r < n){
            pro = pro * a[r];
            while(l < n && pro >= k){
                pro = pro/a[l];
                l++;
            }
            if(pro < k){
                count = count + (r-l+1);
            }
            r++;
        }
        return count;
    }
};
/*
Input : 
n = 4, k = 10
a[] = {1, 2, 3, 4}
Output : 
7
Explanation:
The contiguous subarrays are {1}, {2}, {3}, {4} 
{1, 2}, {1, 2, 3} and {2, 3}, in all these subarrays
product of elements is less than 10, count of
such subarray is 7.
{2,3,4} will not be a valid subarray, because 
2*3*4=24 which is greater than 10.
*/


//340. LONGEST SUBSEQUENCE 1                                                     {T.C = O(N^2), S.C = O(N)}
class Solution{
public:
    int longestSubsequence(int N, int A[])
    {
        //step1 create a dp vector 0
        vector<int>dp(N, 1);                      //always 1 is answer
        
        //step2 analyze base case
        dp[0] = 1;
        
        //step3 loop
        for(int i = 1 ; i < N ; i++){
            for(int j = 0 ; j < i ; j++){
                if(abs(A[i]-A[j]) == 1){
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }
        int maxi = 0;
        for(int i = 0 ; i < N ; i++){
            maxi = max(maxi, dp[i]);
        }
        return maxi;
        
    }
};
/*
Input: N = 7
A[] = {10, 9, 4, 5, 4, 8, 6}
Output: 3
Explaination: The three possible subsequences 
{10, 9, 8} , {4, 5, 4} and {4, 5, 6}.
*/


//341. MAXIMUM SUBSEQUENCE SUM SUCH THAT NO THREE ARE CONSECUTIVE                {T.C = O(N), S.C = O(N)}
#include <bits/stdc++.h> 
int solveMem(vector<int>&a, int n, vector<int>&dp){
	//base case
	if(n < 0){
		return 0;
	}
	if(n == 0){
		return a[0];
	}
	if(n == 1){
		return a[1]+a[0];
	}

	//step3 if answer already present return it
	if(dp[n] != -1){
		return dp[n];
	}

	int option1 = solveMem(a, n - 1, dp);
    int option2 = solveMem(a, n - 2, dp) + a[n];
    int option3 = solveMem(a, n - 3, dp) + a[n] + a[n - 1];

    int ans = max({option1, option2, option3});

	//step2 store ans in dp
	return dp[n] = ans;
}
int maxSum(vector<int> &a, int n) 
{
	//step1 create a dp vector
	vector<int>dp(n+1, -1);
	return solveMem(a, n-1, dp);         //n-1 last index      
}
/*
Input: arr[] = {3000, 2000, 1000, 3, 10}
Output: 5013 
3000 + 2000 + 3 + 10 = 5013
*/


//342. EGG DROPPING PUZZLE
//RECURSION                                                                    {T.C = O(EXP), S.C = O(1)}
class Solution
{
    public:
    int eggDrop(int e, int f) 
    {
        //base case
        if(f == 0 || f == 1){
            return f;
        }
        if(e == 1){
            return f;
        }
        
        int mini = INT_MAX;
        for(int i = 1 ; i <= f ; i++){
            int temp = 1 + max(eggDrop(e-1, i-1), eggDrop(e, f-i));
            mini = min(mini, temp);
        }
        return mini;
        
    }
};

//RECURSION + MEMOIZATION                                                     {T.C = O(N*K^2), S.C = O(N*K)} //N == E, K == F
class Solution
{
    public:
    int solveMem(int e, int f , vector<vector<int>>&dp){
        //base case
        if(f == 0 || f == 1){
            return f;
        }
        if(e == 1){
            return f;
        }
        
        //step3 if ans already present return it
        if(dp[e][f] != -1){
            return dp[e][f];
        }
        
        int mini = INT_MAX;
        for(int i = 1 ; i <= f ; i++){
            int temp = 1 + max(solveMem(e-1, i-1, dp), solveMem(e, f-i, dp));         //max == worst case
            mini = min(mini, temp);
        }
        
        //step2 store ans in dp
        return dp[e][f] = mini;
    }
    int eggDrop(int e, int f) 
    {
        //step1 create a dp vector
        vector<vector<int>>dp(e+1, vector<int>(f+1, -1));
        return solveMem(e, f, dp);
    }
};
/*
Input:
N = 1, K = 2
Output: 2
Explanation: 
1. Drop the egg from floor 1. If it 
   breaks, we know that f = 0.
2. Otherwise, drop the egg from floor 2.
   If it breaks, we know that f = 1.
3. If it does not break, then we know f = 2.
4. Hence, we need at minimum 2 moves to
   determine with certainty what the value of f is.
*/


struct val{
	int first;
	int second;
};
//343. MAX LENGTH CHAIN                                                     {T.C = O(N*LOGN), S.C = O(N / 1)}
//similar to MINIMUM NUMBER OF ARROWS TO BURST BALLOONS  
bool comp(pair<int, int>a , pair<int, int>b){
    return a.second < b.second;
}
class Solution{
public:
    int maxChainLen(struct val p[],int n){
        vector<pair<int, int>>v;
        //push all val in vector pairs
        for(int i = 0 ; i < n ; i++){
            v.push_back( {p[i].first , p[i].second} );
        }
        
        sort(v.begin(), v.end(), comp);
        int ans = 1;                                  //atleast 1 is ans
        int end = v[0].second;                        //upper limit of first interval
        
        for(int i = 0 ; i < v.size() ; i++){
            if(v[i].first > end){
                ans++;
                end = v[i].second;
            }
        }
        return ans;
    }
};
/*
Input:
N = 5
P[] = {5  24 , 39 60 , 15 28 , 27 40 , 50 90}
Output: 3
Explanation: The given pairs are { {5, 24}, {39, 60},
{15, 28}, {27, 40}, {50, 90} },the longest chain that
can be formed is of length 3, and the chain is
{{5, 24}, {27, 40}, {50, 90}}
*/


//344. LARGEST SQUARE FORMED IN A MATRIX                                            {T.C = O(N*M), S.C = O(N*M)}
class Solution{
public:
    int solveMem(vector<vector<int>>&mat, int i , int j , int &maxi, vector<vector<int>>&dp){
        //base case
        if(i >= mat.size() || j >= mat[0].size()){
            return 0;
        }
        
        //step-3 if ans already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        int right = solveMem(mat, i, j+1, maxi, dp);
        int diagonal = solveMem(mat, i+1, j+1, maxi, dp);
        int down = solveMem(mat, i+1, j, maxi, dp);
        
        //step-2 store ans in dp
        if(mat[i][j] == 1){
            dp[i][j] = 1 + min({right, diagonal, down});                                //min = for wrost case
            maxi = max(maxi, dp[i][j]);
            return dp[i][j];
        }
        else{
            return dp[i][j] = 0;
        }
    }
    int maxSquare(int n, int m, vector<vector<int>> mat){
        
        //step-1 creat a dp array
        int maxi = 0;
        vector<vector<int>>dp(n, vector<int>(m , -1));
        solveMem(mat, 0, 0, maxi, dp);
        return maxi;
    }
};
/*
Input: n = 2, m = 2
mat = {{1, 1}, 
       {1, 1}}
Output: 2
Explaination: The maximum size of the square
sub-matrix is 2. The matrix itself is the 
maximum sized sub-matrix in this case.
*/


//345. PAIRS WITH CERTAIN DIFFERENCE                                                       {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
    public:
    int solveMem(int arr[], int n, int k, int currIdx, int prevIdx, vector<vector<int>>&dp){
        //base case
        if(currIdx >= n){
            return 0;
        }
        
        //step3 if ans already present return it
        if(dp[currIdx][prevIdx] != -1){
            return dp[currIdx][prevIdx];
        }
        
        int incl = 0;
        if(arr[currIdx]-arr[prevIdx] < k){
            incl = arr[currIdx] + arr[prevIdx] +  solveMem(arr, n, k, currIdx+2, currIdx+1, dp);  //curr+2, prev = curr++
            
        }
        int excl = 0 + solveMem(arr, n, k, currIdx+1, currIdx, dp);             //curr++, prev = curr
        
        int ans = max(incl, excl);
        //step2 store ans in dp
        return dp[currIdx][prevIdx] = ans;
    }
    int maxSumPairWithDifferenceLessThanK(int arr[], int n, int k)
    {
        //step1 create a dp vector
        vector<vector<int>>dp(n+1, vector<int>(n+1, -1));  
        sort(arr, arr+n);
        return solveMem(arr, n, k, 1, 0, dp);                 //1 = currIndex, 2 = prevIndex
    }
};
/*
Input  : 
arr[] = {3, 5, 10, 15, 17, 12, 9}
K = 4
Output : 
62
Explanation :
Then disjoint pairs with difference less
than K are, (3, 5), (10, 12), (15, 17)
max sum which we can get is 
3 + 5 + 10 + 12 + 15 + 17 = 62
Note that an alternate way to form 
disjoint pairs is,(3, 5), (9, 12), (15, 17)
but this pairing produces less sum.
*/


//346. MAXIMUM PATH SUM IN MATRIX                                                         {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    int solveMem(int n, vector<vector<int>>& mat, int i, int j, vector<vector<int>>& dp) {
        // Base case
        if (i < 0 || i >= n || j < 0 || j >= n) {
            return 0;
        }

        // Step 3: If the answer is already present in the DP array, return it
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // Explore down, left, and right directions
        int down = mat[i][j] + solveMem(n, mat, i + 1, j, dp);
        int left = mat[i][j] + solveMem(n, mat, i + 1, j - 1, dp);
        int right = mat[i][j] + solveMem(n, mat, i + 1, j + 1, dp);

        // Calculate the maximum path
        int ans = max({down, left, right});

        // Step 2: Store the answer in the DP array
        return dp[i][j] = ans;
    }

    int maximumPath(int n, vector<vector<int>>& Matrix) {
        // Step 1: Create a DP vector with dimensions n x n
        vector<vector<int>> dp(n, vector<int>(n, -1));
        int maxSum = 0;
        //we start the recursion from the first row and explore all columns to find the maximum path.
        for (int j = 0; j < n; j++) {
            maxSum = max(maxSum, solveMem(n, Matrix, 0, j, dp));
        }

        return maxSum;
    }
};
/*
Input: N = 2
Matrix = {{348, 391},
          {618, 193}}
Output: 1009
Explaination: The best path is 391 -> 618. 
It gives the sum = 1009.
*/


//347. MAXIMUM DIFFERENCE OF ZEROES AND ONES IN BINARY STRING                              {T.C = O(N), S.C = O(1)}
//using kadane's algo (contiguous subarray sum)
class Solution{
public:	
	int maxSubstring(string s)
	{
	    int tempMax = 0;
	    int maxi = INT_MIN;
	    
	    for(int i = 0 ; i < s.length() ; i++){
	        int x = (s[i] == '0') ? 1 : -1;
	        tempMax = max(x, tempMax + x);
	        maxi = max(maxi, tempMax);
	    }
	    return maxi;
	}
};
/*
Input : S = "11000010001" 
Output : 6 
Explanatio: From index 2 to index 9, 
there are 7 0s and 1 1s, so number 
of 0s - number of 1s is 6. 
*/


//348. MINIMUM NUMBER OF JUMPS                                                       {T.C = O(N), S.C = O(1)}
class Solution{
  public:
    int minJumps(int arr[], int n){
        int far = 0;                    //dist covered by current index
        int curr = 0;                   //curr index
        int jumps = 0;
        
        for(int i = 0 ; i < n-1 ; i++){   //check till second last index {This is because if we're at the last index (i.e., i == n-1), we don't need to jump from there; we have already reached the end.}
            far = max(far, i+arr[i]);     //jump = curr element + index/ position
            if(curr == i){
                jumps++;
                curr = far;
            }
        }
        if(curr < n-1){
            return -1;
        }
        return jumps;
    }
};
/*
Input:
N = 11 
arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9} 
Output: 3 
Explanation: 
First jump from 1st element to 2nd 
element with value 3. Now, from here 
we jump to 5th element with value 9, 
and from here we will jump to the last. 
*/


// 349. MINIMUM COST TO FILL GIVEN WEIGHT IN A BAG                                {T.C = O(N*W), S.C = O(N*W)}
//ERROR
class Solution{
	int solveMem(int cost[], int i , int n, int w, vector<vector<int>>&dp){
	    //base case
	    if(w == 0){
	        return 0;
	    }
	    if(i >= n){
	        return INT_MAX;
	    }
	    
	    //step3 if ans already present return it
	    if(dp[i][w] != -1){
	        return dp[i][w];
	    }
	    
	    int incl = 0;
	    if(w - (i+1) >= 0 && cost[i] != -1){
	        incl = cost[i] + solveMem(cost, i, n, w-(i+1), dp);
	    }
	    int excl = 0 + solveMem(cost, i+1, n, w, dp);
	    
	    int ans = min(incl, excl);
	    //step2 store ans in dp
	    return dp[i][w] = ans;
	}
	public:
	int minimumCost(int cost[], int N, int W) 
	{ 
        //step1 create a dp vector
        vector<vector<int>>dp(N+1, vector<int>(W+1, -1));
        int ans = solveMem(cost,0, N, W, dp);                //0 = currIndex
        return ans==INT_MAX?-1 : ans;
	} 
};
/*
Input: N = 5, arr[] = {20, 10, 4, 50, 100}
W = 5
Output: 14
Explanation: choose two oranges to minimize 
cost. First orange of 2Kg and cost 10. 
Second orange of 3Kg and cost 4. 
*/


//350. ARRAY REMOVALS                                                                 {T.C = O(N^2), S.C = O(N^2)}
class Solution{
    public:
    int solveMem(vector<int>&arr, int k, int i , int j , int count , vector<vector<int>>&dp){
        //base case
        if((arr[j] - arr[i]) <= k){                      //ans found
            return count;
        }
        
        //step3 if ans already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        int removeFirst = solveMem(arr, k, i+1, j,count+1,  dp);
        int removeLast = solveMem(arr, k, i, j-1,count+1, dp);
        
        int ans = min(removeFirst, removeLast);
        
        //step2 store ans in dp
        return dp[i][j] = ans;
    }
    int removals(vector<int>& arr, int k){
        int n = arr.size();
        sort(arr.begin(), arr.end());
        //step1 create a dp vector
        vector<vector<int>>dp(n+1, vector<int>(n+1, -1));
        return solveMem(arr, k, 0, n-1, 0,  dp);               //0 = first index, n-1 = last index , 0 = count
    }
};

//OPTIMIZED APPROACH                                                            {T.C = O(N*LOGN), S.C = O(1)}
class Solution{
    public:
    int removals(vector<int>& arr, int k){
        sort(arr.begin(), arr.end());
        int n = arr.size();
        int mini = INT_MAX;
        for(int i = 0 ; i < n ; i++){
            int rightMost = upper_bound(arr.begin(), arr.end(), arr[i]+k) - arr.begin();   //ub(start, end, finding_element)
            int diff = n-(rightMost-i);
            mini = min(mini, diff);
        }
        return mini;
    }
};
/*
Input: N = 9, K = 4  
arr[] = {1,3,4,9,10,11,12,17,20}
Output: 5
Explanation: Remove 1, 3, 4 from beginning
and 17, 20 from the end.
*/


//351. LONGEST COMMON SUBSTRING                                                    {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int longestCommonSubstr(string s1, string s2, int n, int m) {
        //step1 create a dp vector 0
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int maxLen = 0;

        //loop
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    maxLen = max(maxLen, dp[i][j]);
                } else {
                    dp[i][j] = 0;  // Reset to 0 if characters don't match
                }
            }
        }

        return maxLen;
    }
};
/*
Input: S1 = "ABCDGH", S2 = "ACDGHR", n = 6, m = 6
Output: 4
Explanation: The longest common substring
is "CDGH" which has length 4.
*/


//352. REACH A GIVEN SCORE                                                                 {T.C = O(N), S.C = O(N)}
long long int count(long long int n)
{
	long long int dp[n+1],i;
	memset(dp, 0, sizeof(dp));
    //We have 1 way to reach a score of 0 with scoring nothing at all.
	dp[0]=1;                
	
	for(int i = 3 ; i <= n ; i++){                                //By scoring 3's only we can reach total of 3, 6, 9 and 12 
	    dp[i] += dp[i-3];
	}
	for(int j = 5 ; j <= n ; j++){                                //By scoring 5's only we can reach 5 and 10
	    dp[j] += dp[j-5];
	}
	for(int k = 10 ; k <= n ; k++){                               //By scoring a 10 we can get to 10 Combining it with what we already havE 3+10 = 13
	    dp[k] += dp[k-10];
	}
	
	return dp[n];
}
/*
Input
3
8
20
13
Output
1
4
2
Explanation
For 1st example when n = 8
{ 3, 5 } and {5, 3} are the 
two possible permutations but 
these represent the same 
cobmination. Hence output is 1.
*/


//353. BBT COUNTER                                                                 {T.C = O(H), S.C = O(H)}
class Solution {
  public:
    long long int solveMem(int h, vector<int>&dp){
    int mod = 1e9+7;
        //base case
        if(h < 2){                                 //for h = 0, 1 = 1 binary tree possible
            return 1;                      
        }
        
        //step3 if ans already present return it
        if(dp[h] != -1){
            return dp[h];
        }
        
        
        long long ans = ( solveMem(h-1, dp) * (2*solveMem(h-2, dp) + solveMem(h-1, dp)) ) %mod;
        
        //step2 store ans in dp
        return dp[h] = ans;
    }
    long long int countBT(int h) { 
        //step1 create a dp vector
        vector<int>dp(h+1, -1);
        return solveMem(h, dp);
    }
};
/*
Input: h = 3
Output: 15
Explanation: The maximum number of balanced
binary trees possible with height 3 is 15. 
*/


//354. KADANE'S ALGORITHM (LARGEST SUM CONTIGUOUS ARRAY)                                  {T.C = O(N), S.C = O(1)}
class Solution{
    public:
    long long maxSubarraySum(int arr[], int n){
        long long sum = 0;
        long long maxi = arr[0];
        for(int i = 0 ; i < n ; i++){
            sum += arr[i];
            maxi = max(maxi, sum);
            // sum = max(0, sum);                if sum is also int     
            if(sum < 0){
                sum = 0;
            }
        }
        return maxi;
    }
};
/*
Input:
N = 5
Arr[] = {1,2,3,-2,5}
Output:
9
Explanation:
Max subarray sum is 9
of elements (1, 2, 3, -2, 5) which 
is a contiguous subarray.
*/


//355. KADANE'S ALGORITHM (SMALLEST SUM CONTIGUOUS ARRAY)                                  {T.C = O(N), S.C = O(1)}
class Solution{
    public:
    int smallestSumSubarray(vector<int>& a){
        int sum = 0;
        int mini = INT_MAX;
        for(int i = 0 ; i  < a.size() ; i++){
            sum += a[i];
            mini = min(mini, sum);
            sum = min(0, sum);
        }
        return mini;
    }
};
/*
Input: 
arr[] = {3,-4, 2,-3,-1, 7,-5}
Output: -6
Explanation: sub-array which has smallest 
sum among all the sub-array is {-4,2,-3,-1} = -6
*/


//356. KNAPSACK WITH DUPLICATE ITEMS                                                  
//Tabulation method                                                                       {T.C = O(N*W), S.C = O(N*W)}
class Solution {
public:
    int knapSack(int N, int W, int val[], int wt[])
    {
        // code here
        vector<vector<int>> arr(N, vector<int>(W + 1, 0));
        
        for(int i=0;i<N;i++){
            for(int j=1;j<=W;j++) {
                int pick = 0, notPick = 0;
                if(wt[i]<=j) {
                    pick  = val[i] + arr[i][j-wt[i]];
                }
                if(i>0) notPick = arr[i-1][j];

                arr[i][j] = max(pick,notPick);
            }
        }
        return arr[N-1][W];
    }
};

//SPACE OPTIMIZATION                                                                {T.C = O(N*W), S.C = O(W)}
class Solution{
public:
    int knapSack(int N, int W, int val[], int wt[])
    {
        vector<int>v(W+1, 0);
        for(int i = 0 ; i < N ; i++){
            for(int j = wt[i] ; j <= W ; j++){
                v[j] = max(v[j], v[j-wt[i]] + val[i]);
            }
        }
        return *max_element(v.begin(), v.end());
    }
};
/*
Input: 
N = 4
W = 8
val[] = {6, 1, 7, 7}
wt[] = {1, 3, 4, 5}
Output: 
48
Explanation: 
The optimal choice is to pick the 1st element 8 times.
*/


//357. WORD BREAK                                                                     {T.C = O(N^2), S.C = O(N)}
class Solution
{
public:
    int solveMem(string a, int i, unordered_set<string>& st, vector<int>& dp) {
        // Base case
        if (i == a.length()) {
            return 1;
        }

        // Step 3: If the answer is already present, return it
        if (dp[i] != -1) {
            return dp[i];
        }

        string temp;
        for (int j = i; j < a.length(); j++) {
            temp += a[j];
            if (st.find(temp) != st.end() && solveMem(a, j + 1, st, dp)) {
                return dp[i] = 1;
            }
        }

        // If the string does not match
        return dp[i] = 0;
    }

    int wordBreak(string A, vector<string> &B) {
        int n = A.size();
        // Step 1: Create a DP vector
        vector<int> dp(n + 1, -1);
        unordered_set<string> st;

        for (auto word : B) {
            st.insert(word);
        }

        return solveMem(A, 0, st, dp); // Start with 'i' as 0
    }
};
/*
Input:
n = 12
B = { "i", "like", "sam",
"sung", "samsung", "mobile",
"ice","cream", "icecream",
"man", "go", "mango" }
A = "ilike"
Output:
1
Explanation:
The string can be segmented as "i like".
*/


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
//358. LARGEST INDEPENDENT SET PROBLEM                                             {T.C = O(N), S.C = O(H)}
pair<int, int> solve(Node* root){
    if(!root){
        return {0, 0};
    }
    // Recursively calculate LIS sizes for the left and right subtrees
    auto left = solve(root->left);
    auto right = solve(root->right);
    
    int incl = 1+left.second+right.second;
    int excl = max({
        left.first+right.first, left.first+right.second, left.second+right.first
        });
    
    return {incl, excl};
}
int LISS(Node *root)
{
    pair<int, int>p = solve(root);
    return max(p.first, p.second);
}
/*
Input:
10 20 30 40 50 N 60 N N 70 80

Output:
5
Explanation: LIS of the above 
tree will be [10,40, 60, 70,80]
*/


//359. PARTITION EQUAL SUBSET SUM                                                           {T.C = O(N*T), S.C = O(N*T)}
class Solution{
public:
    bool solveMem(int arr[], int i ,int n, int target, vector<vector<int>>&dp){
        //base case
        if(i >= n || target < 0){
            return 0;
        }
        if(target == 0){                            //not taking any element
            return 1;
        }
        //step 3: check if the answer is found, return it
        if(dp[i][target] != -1){
            return dp[i][target];
        }
        
        bool incl = solveMem(arr, i+1, n, target-arr[i], dp);
        bool excl = solveMem(arr, i+1, n , target, dp);
        
        //step2 store ans in dp
        dp[i][target] = incl or excl;
        return dp[i][target];
    }
    int equalPartition(int N, int arr[])
    {
        int total = 0;
        for(int i = 0 ; i < N ; i++){
            total += arr[i];
        }
        if(total & 1){                                         //if odd partition not possible
            return 0;
        }
        int target = total/2;
        
        //step1 create dp vector
        vector<vector<int>>dp(N+1, vector<int>(target+1, -1));
        return solveMem(arr, 0, N, target, dp);                  //i = 0
    }
};
/*
Input: N = 4
arr = {1, 5, 11, 5}
Output: YES
Explanation: 
The two parts are {1, 5, 5} and {11}.
*/


//360. LONGEST PALINDROMIC SUBSEQUENCE                                                      {T.C = O(N^2), S.C = O(N^2)}
class Solution{
  public:
    int solveMem(string a, string r , int i, int j, vector<vector<int>>&dp){
        //base case
        if(i == a.length() || j == r.length()){
            return 0;
        }
        
        //step3 if ans already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        if(a[i] == r[j]){
            return dp[i][j] = 1 + solveMem(a, r, i+1, j+1, dp);
        }
        return dp[i][j] = max(solveMem(a, r, i+1, j, dp), solveMem(a, r, i, j+1, dp));
    }
    int longestPalinSubseq(string A) {
        int n = A.size();
        string rev = A;
        reverse(rev.begin(), rev.end());
        //step1 create a dp vector
        vector<vector<int>>dp(n+1, vector<int>(n+1, -1));
        return solveMem(A, rev, 0, 0, dp);
    }
};
/*
Input:
S = "bbabcbcab"
Output: 7
Explanation: Subsequence "babcbab" is the
longest subsequence which is also a palindrome.
*/


//361. COUNT PALINDROMIC SUBSEQUENCES                                                    {T.C = O(N^2), S.C = O(N^2)}
class Solution{
    public:
    
    long long int rec(string &s, int i , int j , vector<vector<long long int>>&dp){
        //base case
        int mod = 1e9 + 7; 
        
        if(i == j){
            return 1;
        }
        if(i > j){
            return 0;
        }
        
        //step-3 if answer already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        long long int ans;
        if(s[i] == s[j]){
            ans = (1 + rec(s, i+1, j, dp) + rec(s, i, j-1, dp)) %  mod;
        }else{
            ans = ((rec(s, i+1, j, dp) + rec(s, i, j-1, dp) - rec(s, i+1, j-1, dp)) % mod + mod) % mod;
        }
        
        //step-2 store answer in dp
        dp[i][j] = ans;
        return dp[i][j];
    }
    long long int  countPS(string str)
    {
       int n = str.length();
       //step-1 create a dp vector
       vector<vector<long long int>>dp(n, vector<long long int>(n, -1));
       return rec(str, 0 , n-1 , dp);
    }
};
/*
Input: 
Str = "aab"
Output: 
4
Explanation:
palindromic subsequence are :"a", "a", "b", "aa"
*/


//362. LONGEST PALINDROMIC SUBSTRING
class Solution {
public:
    string expandFromCenter(string &s, int left, int right){
        while(left >= 0 && right < s.length() && s[left] == s[right]){
            left--;
            right++;
        }
        return s.substr(left+1, right-left-1);          //(starting index, length)
    }
    string longestPalindrome(string s) {
        int n = s.length();

        //base case
        if(s.length() <= 1){
            return s;
        };

        string maxStr = s.substr(0, 1);                 //(starting index, length)
        for(int i = 0 ; i < n-1 ; i++){
            string odd = expandFromCenter(s, i, i);     //partition on char
            string eve = expandFromCenter(s, i, i+1);   //partition in between char

            if(odd.length() > maxStr.length()){
                maxStr = odd;
            }
            if(eve.length() > maxStr.length()){
                maxStr = eve;
            }
        }
        return maxStr;
    }
};
/*
Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"
*/


//363. LONGEST INCREASING SUBSEQUENCE                                                 {T.C = O(N), S.C = O(1)}
//finding peaks(increasing , decreasing )
class Solution {
	public:
	int AlternatingaMaxLength(vector<int>&nums){
	    //if only 1 element we cant say it is increasing or decreasing
	    int increasing = 1;
	    int decreasing = 1;
	    
	    for(int i = 1 ; i < nums.size() ; i++){
	        if(nums[i] > nums[i-1]){
	            increasing = decreasing+1;
	        }else if(nums[i] < nums[i-1]){
	            decreasing = increasing+1;
	        }
	    }
	    return max(increasing , decreasing);
	}
};
/*
Input: nums = {1,17,5,10,13,15,10,5,16,8}
Output: 7
Explanation: There are several subsequences
that achieve this length. 
One is {1,17,10,13,10,16,8}.
*/


struct Job 
{ 
    int id;	 // Job Id 
    int dead; // Deadline of job 
    int profit; // Profit if job is over before or on deadline 
};
//364. JOB SEQUENCING PROBLEM                                                   {T.C = O(N*LOGN), S.C = O(N)}
bool comp(Job a, Job b){
    return (a.profit > b.profit);
}
class Solution 
{
    public:
    //Function to find the maximum profit and the number of jobs done.
    vector<int> JobScheduling(Job arr[], int n) 
    { 
        sort(arr, arr+n, comp);    //sort in decreasing order of profit
        vector<bool>done(n, 0);    // Initialize a boolean array to keep track of jobs that are done.
        
        int day = 0, profit = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = min(n, arr[i].dead-1) ; j >= 0 ; j--){            //dead-1 == 0 based indexing
                if(done[j] == false){
                    day += 1;
                    profit += arr[i].profit;
                    done[j] = true;
                    break;
                }
            }
        }
        return {day, profit};
    } 
};
/*
Input:
N = 4
Jobs = {(1,4,20),(2,1,10),(3,1,40),(4,1,30)}
Output:
2 60
Explanation:
Job1 and Job3 can be done with
maximum profit of 60 (20+40).
*/


//365. COIN GAME WINNER WHERE EVERY PLAYER HAS THREE CHOICES                   {T.C = O(N), S.C = O(N)}
//approach = we have 3 choices 1, x , y . A starts first so dp will manage true for a (wins) if previous false(b)
//that means next player is a who wins the game
bool coinGameWinner(int n, int x, int y) {
    vector<bool> dp(n + 1, false);

    dp[0] = false;  // B
    dp[1] = true;   // A

    for (int i = 2; i <= n; i++) {
        if (i - 1 >= 0 && !dp[i - 1]) {
            dp[i] = true;  // A can win by taking 1 coin
        } else if (i - x >= 0 && !dp[i - x]) {
            dp[i] = true;  // A can win by taking x coins
        } else if (i - y >= 0 && !dp[i - y]) {
            dp[i] = true;  // A can win by taking y coins
        }
    }

    return dp[n];
}
/*
Sample Input 1:
2
5 3 4
4 2 3
Sample Output 1:
1
0
Explanation for Sample Input 1:
For the first test case, There are 5 coins, every player can pick 1 or 3 or 4 coins on his/her turn. X picks 3 coins in the first turn, now the remaining coins are 2, Y can only pick 1 coin. So, X wins by picking the last coin.

For the second test case, No, matter what coins X picks, Y always wins.
*/


//366. COUNT DERANGEMENTS (PERMUTAION SUCH THAT NO ELEMENT APPPEARS IN ITS ORIGINAL POSITION) {T.C = O(N), S.C = O(N)}
#define MOD 1000000007
#include<vector>
//RECURSION + MEMOIZATION
long long int solveMem(int n, vector<long long int>&dp){
    //base case
    if(n == 1){
        return 0;
    }
    if(n == 2){
        return 1;
    }

    //step-3
    if(dp[n] != -1){
        return dp[n];
    }

    // step-2 store ans in dp array
    // ans = total possibilities * {subProblem} == (not swap(diffrent position +
    // swap conditon) dp[n] = (n-1) + (solveMem(n-1,dp) + solveMem(n-2, dp))
    dp[n] = (((n-1)%MOD) * ((solveMem(n-1, dp)%MOD) + (solveMem(n-2,dp)%MOD)))%MOD;

    return dp[n];
}
long long int countDerangements(int n){

    //step-1 create dp array
    vector<long long int>dp(n+1, -1);

    return solveMem(n, dp);
}
/*
Input: n = 3
Output: 2
For three elements say {0, 1, 2}, there are two 
possible derangements {2, 0, 1} and {1, 2, 0}

Input: n = 4
Output: 9
For four elements say {0, 1, 2, 3}, there are 9
possible derangements {1, 0, 3, 2} {1, 2, 3, 0}
{1, 3, 0, 2}, {2, 3, 0, 1}, {2, 0, 3, 1}, {2, 3,
1, 0}, {3, 0, 1, 2}, {3, 2, 0, 1} and {3, 2, 1, 0}
*/


//367. BUY AND SELL STOCKS PROBLEMS
//1. BUY ON ONE DAY SELL ON ANOTHER DAY                                       {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mini = prices[0];
        int maxPft = 0;

        for(int i = 1 ; i < prices.size() ; i++){
            int profit = prices[i] - mini;
            maxPft = max(maxPft, profit);
            mini = min(mini, prices[i]);                //for updating mini element
        }
        return maxPft;
    }
};
/*
Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
*/


//2. BUY/SELL ON SAME DAY WITH HOLIDING ATMOST 1 STOCK AT A TIME             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int solveMem(vector<int>&prices, int idx, int buy, vector<vector<int>>&dp){
        //base case
        if(idx == prices.size()){
            return 0;
        }
        
        //step3 if answer exist return it
        if(dp[idx][buy] != -1){
            return dp[idx][buy];
        }

        int profit = 0;
        if(buy){          //buy == 1  allowed
            int buyKaro = -prices[idx] + solveMem(prices, idx+1, 0, dp);        //0 for next buy / buy not allowed 
            int skipKaro = 0 + solveMem(prices, idx+1, 1, dp);
            profit = max(buyKaro, skipKaro);
        }else{            //buy == 0   not allowed
            int sellKaro = +prices[idx] + solveMem(prices, idx+1, 1, dp);       //1 for next buy / buy allowed
            int skipKaro = 0 + solveMem(prices, idx+1, 0, dp);
            profit = max(sellKaro, skipKaro);
        }

        //step2 store ans in dp
        dp[idx][buy] = profit;
        return dp[idx][buy];
    }
    int maxProfit(vector<int>& prices) {
        int n =  prices.size();
        //step1 create a dp vector
        vector<vector<int>>dp(n, vector<int>(2, -1));          //col = 0 or 1
        return solveMem(prices, 0, 1, dp);                     //0 = index, 1 = buy(allowed{bool value})
    }
};


//3. BUY/SELL ON SAME DAY WITH HOLIDING ATMOST 2 STOCK AT A TIME             {T.C = O(N), S.C = O(N)}
//RECURSION + MEMOIZATION
class Solution {
public:
    int solveMem(vector<int>&prices, int index, int buy, int limit ,vector<vector<vector<int>>>&dp){
        //base case
        int n = prices.size();
        if(index == n || limit == 0){
            return 0;
        }

        //step-3 if ans already present print it
        if(dp[index][buy][limit] != -1){
            return dp[index][buy][limit];
        }

        int profit = 0;
        if(buy){
            int buyKaro = -prices[index] + solveMem(prices, index+1, 0, limit, dp);
            int skipKaro = 0 + solveMem(prices, index+1, 1, limit, dp);
            profit = max(buyKaro, skipKaro);
        }
        else{
            int sellKaro = +prices[index] + solveMem(prices, index+1, 1, limit-1, dp);
            int skipKaro = 0 + solveMem(prices, index+1, 0, limit, dp);
            profit = max(sellKaro , skipKaro);
        }

        //step-2 store ans in dp
        dp[index][buy][limit] = profit;
        return dp[index][buy][limit];
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        //step-1 create dp vector
        vector<vector<vector<int>>>dp(n , vector<vector<int>>(2, vector<int>(3, -1)));      //row = n , col = 2  , entry (limit) = 3 (at most 2 = 0 , 1 , 2)
        return solveMem(prices, 0, 1, 2, dp);                  //index = 0 , buy = 1, limit = 2
    }
};
/*
Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.

Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.
*/


//4. BUY/SELL ON SAME DAY WITH HOLIDING ATMOST K(TRANSACTION) STOCK AT A TIME             {T.C = O(N*K), S.C = O(N*K)}
//RECURSION + MEMOIZATION
class Solution {
public:
    int solveMem(vector<int>&prices, int index, int operationNo, int k , vector<vector<int>>&dp){
        int n = prices.size();
        if(index == n || operationNo == 2*k){
            return 0;
        }
        
        //step-3 if ans already present return it
        if(dp[index][operationNo] != -1){
            return dp[index][operationNo];
        }
        int profit = 0;
        if(operationNo % 2 == 0){                            //even = buy allow
            int buyKaro = -prices[index] + solveMem(prices, index+1, operationNo+1, k, dp);
            int skipKaro = 0 + solveMem(prices, index+1, operationNo, k, dp);
            profit = max(buyKaro, skipKaro);
        }
        else{                                                //odd = sell allow
            int sellKaro = +prices[index] + solveMem(prices, index+1, operationNo+1, k, dp);
            int skipKaro = 0 + solveMem(prices, index+1, operationNo , k, dp);
            profit = max(sellKaro, skipKaro);
        }

        //step-2 store ans in dp
        dp[index][operationNo] = profit;
        return dp[index][operationNo];
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        //step-1 create dp vector
        vector<vector<int>>dp(n, vector<int>(2*k, -1));             //col = operation = 2*k
        return solveMem(prices, 0, 0, k, dp);                         //index = 0, operationNo = 0
    }
};
/*
Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
*/


//368. OPTIMAL STRATEGY FOR A GAME                                           {T.C = O(N^2), S.C =  O(N^2)}
//approach - we can choose only first or last first we choose first then from rest subarray choose min + element then similar for last
class Solution{
    public:
    long long solveMem(int arr[], int i, int j, vector<vector<long long>>&dp){
        //base case
        if(i > j){
            return 0;
        }
        
        //step3 if ans already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        //if we choose first then from rest wrost case to choose min(remove last and first subproblem array) by default
        long long first = arr[i] + min(solveMem(arr, i+1, j-1, dp), solveMem(arr, i+2, j, dp));
        long long last = arr[j] + min(solveMem(arr, i, j-2, dp), solveMem(arr, i+1, j-1, dp));
        
        long long ans = max(first, last);
        
        //step2 store ans in dp
        return dp[i][j] = ans;
    }
    long long maximumAmount(int arr[], int n){
        //step1 create a dp vector
        vector<vector<long long>>dp(n+1, vector<long long>(n+1, -1));
        return solveMem(arr, 0, n-1, dp);
    }
};
/*
Example 1:
Input:
N = 4
A[] = {5,3,7,10}
Output: 15
Explanation: The user collects maximum
value as 15(10 + 5)

Example 2:
Input:
N = 4
A[] = {8,15,3,7}
Output: 22
Explanation: The user collects maximum
value as 22(7 + 15)
*/


//369. OPTIMAL BINARY SEARCH TREE                                                         {T.C = O(N^3), S.C = O(N^2)}
class Solution{
    public:
    int solveMem(int freq[], int i, int j , vector<vector<int>>&dp){
        //base case
        if(i > j){
            return 0;
        }
        
        //step3 if ans already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        int ans = INT_MAX;     //finding optimal(minimum)
        
         // Try each key as the root and calculate the cost.
        for(int key = i ; key <= j ; key++){
            int left = solveMem(freq,i, key-1, dp);                //cost of leftSubtree
            int right = solveMem(freq, key+1, j, dp);               //cost of rightSubtree
            ans = min(ans, left+right);
        }
        
        //calculate for all keys
        for(int k = i ; k <= j ; k++){
            ans += freq[k];
        }
        
        //step2 store ans in dp
        return dp[i][j] = ans;
    }
    int optimalSearchTree(int keys[], int freq[], int n)
    {
        //step1 create a dp vector
        vector<vector<int>>dp(n+1, vector<int>(n+1, -1));
        return solveMem(freq, 0, n-1, dp);                 //i = 0, j = n-1 {ranges}
    }
};
/*
Input:
N = 3
keys = {10, 12, 20}
freq = {34, 8, 50}
Output: 142
Explaination: There can be many possible BSTs
     20
    /
   10  
    \
     12  
     
Among all possible BSTs, 
cost of this BST is minimum.  
Cost of this BST is 1*50 + 2*34 + 3*8 = 142
*/


//370. PALINDROMIC PARTITION
//TLE                                                                                {T.C = O(N^3), S.C = O(N^2)}
class Solution{
public:
    bool isPalindrome(string s, int i, int j) {
        while (i < j) {
            if (s[i] != s[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
    int solveMem(string str, int i, int j, vector<vector<int>>&dp){
        //base case
        if(i >= j){                    //i == j (single element already palindrome)
            return 0;
        }
        if(isPalindrome(str, i, j)){
            return 0;
        }
        
        //step3 if ans already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        int mini = INT_MAX;
        for(int k = i ; k < j ; k++){                    //check for each partition
            int temp = 1 + solveMem(str, i, k, dp) + solveMem(str, k+1, j, dp);
            mini = min(mini, temp);
        }
        
        //step2 store ans in dp
        return dp[i][j] = mini;
    }
    int palindromicPartition(string str)
    {
        int n = str.length();
        //step1 create dp vector
        vector<vector<int>>dp(n+1, vector<int>(n+1, -1));
        return solveMem(str, 0, n-1, dp);                    //i = 0, j = n-1
    }
};
/*
Example 1:

Input: str = "ababbbabbababa"
Output: 3
Explaination: After 3 partitioning substrings 
are "a", "babbbab", "b", "ababa".
Example 2:

Input: str = "aaabba"
Output: 1
Explaination: The substrings after 1
partitioning are "aa" and "abba".
*/


//371. WORD WRAP                                                                     {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    int dp[505][2005];
    int solve(int i, int rem,vector<int>& arr, int &k) {
        if(i == arr.size()){
            return 0;
        }
        // Step 3: If already calculated, return
        if (dp[i][rem] != -1) {
            return dp[i][rem];
        }

        int ans;
        if (arr[i] > rem) {
            ans = (rem + 1) * (rem + 1) + solve(i + 1, k - arr[i]-1, arr, k);
        } else {
            int choice1 = (rem + 1) * (rem + 1) + solve(i + 1, k - arr[i]-1, arr, k);
            int choice2 = 0 + solve(i + 1, rem - arr[i]-1, arr, k);
            ans = min(choice1, choice2);
        }

        // Step 2: Store ans in dp
        dp[i][rem] = ans;
        return dp[i][rem];
    }

    int solveWordWrap(vector<int>& arr, int k) {
        memset(dp, -1, sizeof(dp));
        return solve(0, k, arr, k); 
    }
};
/*
Input: nums = {3,2,2,5}, k = 6
Output: 10
Explanation: Given a line can have 6
characters,
Line number 1: From word no. 1 to 1
Line number 2: From word no. 2 to 3
Line number 3: From word no. 4 to 4
So total cost = (6-3)2 + (6-2-2-1)2 = 32+12 = 10.
As in the first line word length = 3 thus
extra spaces = 6 - 3 = 3 and in the second line
there are two word of length 2 and there already
1 space between two word thus extra spaces
= 6 - 2 -2 -1 = 1. As mentioned in the problem
description there will be no extra spaces in
the last line. Placing first and second word
in first line and third word on second line
would take a cost of 02 + 42 = 16 (zero spaces
on first line and 6-2 = 4 spaces on second),
which isn't the minimum possible cost.
*/


//372. MOBILE NUMERIC KEYPAD                                                         {T.C = O(N), S.C = O(N)}
//my approach (error) 
class Solution{
	public:
	int mat[4][3] = {
	                {1, 2, 3},
	                {4, 5, 6},
	                {7, 8, 9},
	                {-1, 0, -1}
	                };
	
	long long solveMem(int i, int j, int n, vector<vector<long long>>&dp){
	    if(n == 1){              //solo element take ownself
	        return 1;
	    }
	    //step3 if ans already present return it
	    if(dp[mat[i][j]][n] != -1){
	        return dp[mat[i][j]][n];
	    }
	    
	    long long a = solveMem(i, j, n-1, dp);          //includes ownself element
	    long long b = 0, c = 0, d = 0, e = 0;       //for 4 directions
	    if(j-1 >= 0 && mat[i][j-1] != -1){         //left
	        b = solveMem(i, j-1, n-1, dp);
	    }
	    if(j+1 < 3 && mat[i][j+1] != -1){          //right
	        c = solveMem(i, j+1, n-1, dp);
	    }
	    if(i-1 >= 0 && mat[i-1][j] != -1){          //up
	        d = solveMem(i-1, j, n-1, dp);
	    }
	    if(i+1 < 4 && mat[i+1][j] != -1){           //down
	        e = solveMem(i+1, j, n-1, dp);
	    }
	    
	    //step2 store ans in dp
	    return dp[mat[i][j]][n] = a + b + c + d + e;
	}
	long long getCount(int N)
	{
	    //step1 create a dp vector
		vector<vector<long long>>dp(4, vector<long long>(3, -1));
		long long ans = 0;
		for(int i = 0; i < 4 ; i++){             //row in numpad
		    for(int j = 0 ; j < 3 ; j++){        //col in numpad
		        if(mat[i][j] != -1){
		            return solveMem(i, j, N, dp);
		        }
		    }
		}
		return ans;
	}
};

//correct approach
class Solution{
	public:
  char keypad[4][3] = {{'1','2','3'},
                       {'4','5','6'},
                       {'7','8','9'}, 
                       {'*','0','#'}};
    int row[5] = {0, 0, -1, 0, 1};
    int col[5] = {0, -1, 0, 1, 0};
    long long dp[5][4][26];
	long long solve(int i, int j, int n)
	{
	    if(n<=0)
	    {
	        return 0;
	    }
	    if(n==1)
	    {
	        return 1;
	    }
	    if(dp[i][j][n] != -1)
	    {
	        return dp[i][j][n];
	    }
	    
	    long long ans = 0;
	    for(int k=0; k<5; k++)
	    {
	        int nx = row[k]+i;
	        int ny = col[k]+j;
	        
	        if(nx<=3 && nx>=0 && ny<=2 && ny>=0 && keypad[nx][ny]!='*' && keypad[nx][ny]!='#')
	        {
	            ans+=solve(nx, ny, n-1);
	        }
	    }
	    return dp[i][j][n] = ans;
	}
	long long getCount(int n)
	{
	    memset(dp, -1, sizeof(dp));
	    long long ans = 0;
		for(int i=0; i<4; i++)
		{
		    for(int j=0; j<3; j++)
		    {
		        if(keypad[i][j]!='*' && keypad[i][j]!='#')
		        {
		            ans+=solve(i, j, n);
		        }
		    }
		}
		return ans;
	}
 
};
/*
Example 1:
Input: 1
Output: 10
Explanation: Number of possible numbers 
would be 10 (0, 1, 2, 3, ., 9) 

Example 2:
Input: N = 2
Output: 36
Explanation: Possible numbers: 00, 08, 11,
12, 14, 22, 21, 23, 25 and so on.
If we start with 0, valid numbers 
will be 00, 08 (count: 2)
If we start with 1, valid numbers 
will be 11, 12, 14 (count: 3)
If we start with 2, valid numbers 
will be 22, 21, 23,25 (count: 4)
If we start with 3, valid numbers 
will be 33, 32, 36 (count: 3)
If we start with 4, valid numbers 
will be 44,41,45,47 (count: 4)
If we start with 5, valid numbers 
will be 55,54,52,56,58 (count: 5) 
and so on..
*/


//373. BOOLEAN PARENTHESIZATION                                                  {T.C = O(N^3), S.C = O(N^2)}
class Solution{
public:
unordered_map<string,int> mp;
int solve(string s,int i,int j,bool istrue)
{
    if(i>j){
        return false;
    }
    if(i==j){
        if(istrue==true){
            return s[i]=='T';
        }
        else{
            return s[i]=='F';
        }
    }
    string temp=to_string(i);
    temp.push_back(' ');
    temp.append(to_string(j));
    temp.push_back(' ');
    temp.append(to_string(istrue));
    if(mp.find(temp)!=mp.end()){
        return mp[temp];
    }
    int ans=0;
    for(int k=i+1;k<j;k=k+2){
        int lt=solve(s,i,k-1,true);
        int lf=solve(s,i,k-1,false);
        int rt=solve(s,k+1,j,true);
        int rf=solve(s,k+1,j,false);
        if(s[k]=='&'){
            if(istrue==true)
            ans=ans+lt*rt;
            else
            ans=ans+(lt*rf+lf*rt+lf*rf);
        }
        if(s[k]=='|'){
            if(istrue==true)
            ans+=(lt*rf+lf*rt+lt*rt);
            else
            ans+=lf*rf;
        }
        if(s[k]=='^'){
            if(istrue==true)
            ans+=lt*rf+lf*rt;
            else
            ans+=lt*rt+lf*rf;
        }
    }
    mp[temp]=ans%1003;
    return (mp[temp])%1003;
    
}
    int countWays(int n,string s){
    bool istrue=true;
    int x= solve(s,0,n-1,istrue);
    return (x%1003);
    }
};
/*
Example 1:

Input: N = 7
S = T|T&F^T
Output: 4
Explaination: The expression evaluates 
to true in 4 ways ((T|T)&(F^T)), 
(T|(T&(F^T))), (((T|T)&F)^T) and (T|((T&F)^T)).
Example 2:

Input: N = 5
S = T^F|F
Output: 2
Explaination: ((T^F)|F) and (T^(F|F)) are the 
only ways.
*/


//374. LARGEST RECTANGULAR SUB-MATRIX WHOSE SUM IS 0


//375. LARGEST AREA RECTANGULAR SUB-MATRIX WITH EQUAL NUMBER OF 1'S AND 0'S


//376. MAXIMUM SUM RECTANGLE                                                         {T.C = O(N^3), S.C = O(N)}      //N == R OR C
//APPROACH
//first convert 2D matrix to 1D then apply kadane's algo(maximum sum subarray)
class Solution {
  public:
    int kadane(vector<int>&temp, int n){
        int subArrSum = INT_MIN;            //subArrSum = maxi
        int currSum = 0;
        for(int i = 0 ; i < n ; i++){
            currSum += temp[i];
            subArrSum = max(subArrSum, currSum);
            if(currSum < 0){
                currSum = 0;
            }
        }
        return subArrSum;
    }
    int maximumSumRectangle(int R, int C, vector<vector<int>> M) {
        int maxi = INT_MIN;
        for(int i = 0 ; i < C ; i++){
            vector<int>temp(R, 0);            //store 2d elements into 1d vector
            for(int j = i ; j < C ; j++){
                for(int k = 0 ; k < R ; k++){
                    temp[k] += M[k][j];       //first add columnwise elemnt then push in vector
                }
                int sum = kadane(temp, R);
                maxi = max(maxi, sum);
            }
        }
        return maxi;
    }
};
/*
Example 1:
Input:
R=4
C=5
M=[[1,2,-1,-4,-20],
[-8,-3,4,2,1],
[3,8,10,1,3],
[-4,-1,1,7,-6]]
Output:
29
Explanation:
The matrix is as follows and the
blue rectangle denotes the maximum sum
rectangle.
*/


//377. MAXIMUM PROFIT                                                                    {T.C = O(N*K), S.C = O(N*K)}
//same as 367 buy and sell for at most k transactions
class Solution {
  public:
    int solveMem(int a[], int n, int k, int i , int o, vector<vector<int>>&dp){
        // int n = sizeof(a);               //not n = a.size();
        if(i == n || o == 2*k){
            return 0;
        }
        
        //step3 if ans alrady present return it
        if(dp[i][o] != -1){
            return dp[i][o];
        }
        
        int profit = 0;
        if(o % 2 == 0){       //even = buy allow
            int buyKaro = -a[i] + solveMem(a, n, k, i+1, o+1, dp);
            int skipKaro = 0 + solveMem(a, n, k, i+1, o, dp);
            profit = max(buyKaro, skipKaro);
        }else{
            int sellKaro = +a[i] + solveMem(a, n, k, i+1, o+1, dp);
            int skipKaro = 0 + solveMem(a, n, k, i+1, o, dp);
            profit = max(sellKaro, skipKaro);
        }
        
        //step2 store ans in dp
        return dp[i][o] = profit;
    }
    int maxProfit(int K, int N, int A[]) {
        vector<vector<int>>dp(N+1, vector<int>(2*K, -1));      //col = operation = 2*k
        return solveMem(A, N, K, 0, 0, dp);               //index = 0, operationNo = 0
    }
};
/*
Example 1:
Input: K = 2, N = 6
A = {10, 22, 5, 75, 65, 80}
Output: 87
Explaination: 
1st transaction: buy at 10 and sell at 22. 
2nd transaction : buy at 5 and sell at 80.

Example 2:
Input: K = 3, N = 4
A = {20, 580, 420, 900}
Output: 1040
Explaination: The trader can make at most 2 
transactions and giving him a profit of 1040.
*/


//378. INTERLEAVED STRINGS                                            {T.C = O(N*M), S.C = O(N*M*Z)}
//distinct charcter is not necessary (if possible we can use greedy approach)
class Solution{
  public:
    bool solveMem(string a, string b, string c, int i, int j, int k, vector<vector<vector<int>>>&dp){
        int n = a.length(), m = b.length(), z = c.length();
        //base case
        if(i == n && j == m && k == z){
            return true;
        }
        
        if(k == z){
            return false;
        }
        //step3 if ans already present return it
        if(dp[i][j][k] != -1){
            return dp[i][j][k];
        }
        
        int x = 0, y = 0;
        if(a[i] == c[k]){
            x = solveMem(a, b, c, i+1, j, k+1, dp);
        }
        if(b[j] == c[k]){
            y = solveMem(a, b, c, i, j+1, k+1, dp);
        }
        
        bool ans = x || y;
        
        //step2 store ans in dp
        return dp[i][j][k] = ans;
        
    }
    bool isInterleave(string A, string B, string C) 
    {
        int n = A.length(), m = B.length(), z = C.length();
        if(n+m != z){
            return false;
        }
        vector<vector<vector<int>>>dp(n+1, vector<vector<int>>(m+1, vector<int>(z+1, -1)));
        return solveMem(A, B, C, 0, 0, 0, dp);               //i = 0, j = 0, k = 0
    }
};
/*
Example 1:
Input:
A = YX, B = X, C = XXY
Output: 0
Explanation: XXY is not interleaving
of YX and X

Example 2:
Input:
A = XY, B = X, C = XXY
Output: 1
Explanation: XXY is interleaving of
XY and X.
*/

//379. MAXIMUM LENGTH OF PAIR CHAIN                                            {T.C = O(N*LOGN), S.C = O(1)}
//APPROACH -
//similar to 343 problem sort the vector according to upper limit then if lower limit is big then upper then make chain
bool comp(vector<int>&v1, vector<int>&v2){
    return v1[1] < v2[1];
}
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), comp);
        int prev = 0;
        int ans = 1;                                   //at least 1 is answer
        for(int i = 1 ; i < pairs.size() ; i++){
            if(pairs[i][0] > pairs[prev][1]){
                ans++;
                prev = i;
            }
        }
        return ans;
    }
};
/*
Example 1:

Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4].
Example 2:

Input: pairs = [[1,2],[7,8],[4,5]]
Output: 3
Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].
*/


/*--------------------------------------------------------------  THE END   ----------------------------------------------------------------*/