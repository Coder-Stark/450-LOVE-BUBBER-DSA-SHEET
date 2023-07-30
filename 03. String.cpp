//STRINGS
//subsequence(2^n) = take - no take , substring = 2 nested for loops
/*store
key && value                             => unordered_map<char, int>mp;
key                                      => unordered_set<int/ char>set;
value => frequency array / vector        => vector<int>freq(256, 0);
*/

#include<bits/stdc++.h>
using namespace std;

//47. REVERSE THE STRING                                                       {T.C = O(N), S.C = O(1)}
class Solution {
public:
    void reverseString(vector<char>& s) {
        int start = 0;
        int end = s.size()-1;
        while(start < end){
            char temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++;
            end--;
        }
    }
};
/*
Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
*/


//48. PALINDROME STRING                                               {T.C = O(N), S.C = O(1)}
class Solution{
public:	
	int isPalindrome(string s)
	{
	    int n = s.length();
	    int start = 0;
	    int end = n-1;
	    
	    while(start < end){
	        if(s[start] != s[end]){
	            return 0;
	        }
	        start++;
	        end--;
	    }
        return 1;
	}
};
/*
Input: S = "abba"
Output: 1
Explanation: S is a palindrome
*/


//49. PRINT ALL THE DUPLICATES IN THE INPUT STRING                                  {T.C = O(N), S.C = O(M)=no. of unique char}
void printDuplicate(string &s){
    int n = s.length();
    
    //create a unordered map to store key & val
    unordered_map<char, int>mp;
    //put string element into map
    for(int i = 0 ; i < n ; i++){
        mp[s[i]]++;
    }
    
    //traverse on map
    for(auto it : mp){
        if(it.second > 1){
            cout<<it.first<<" "<<it.second<<endl;
        }
    }
}
int main(){
    string s = "addaccged";
    printDuplicate(s);
    return 0;
}
/*
output
c 2
d 3
a 2
*/


//50. WHY JAVA STRINGS ARE IMMUTABLE
/*
Java strings are immutable, meaning once a string object is created, its value cannot be changed.
This design decision was made for several reasons:

String Pooling: 
Java uses a special memory area called the "string pool" to store string literals. When you create a string literal 
(e.g., "hello"), Java checks the string pool first. If a string with the same value already exists, it returns a 
reference to that existing string instead of creating a new one. This reduces memory consumption and improves 
performance since many strings can be shared.

Thread-Safety: 
Because strings are immutable, they are inherently thread-safe. Multiple threads can safely use and 
share the same string object without the risk of concurrent modification issues.

Caching Hashcode: 
The immutable nature allows Java to cache the hashcode of a string when it is first calculated. 
Since the hashcode of a string never changes, it can be safely cached and used in hash-based data structures like 
HashMap, HashSet, etc.

Security: 
String immutability is vital for security, particularly in scenarios like storing sensitive information
like passwords. Immutable strings prevent potential data tampering or manipulation after creation.

String Interning: 
String interning is the process of storing unique string literals in the string pool. Java ensures
that identical string literals are not duplicated in memory, saving space and optimizing memory usage.

Consistency: 
Immutability ensures that a string's value remains constant throughout its lifetime. This consistency makes 
code more predictable and easier to reason about.

Despite their immutability, you can perform various string manipulation operations in Java using methods like concat, 
substring, replace, etc. However, these methods do not modify the original string but instead create new string objects with the desired modifications.
*/


//51. CHECK IF ONE STRING IS ROTATION OF ANOTHER STRING
//USING STL                                                                   {T.C = O(N^2), S.C = O(N)}
int isCyclicRotation(string &p, string &q) 
{
    string temp = p+p;
    if(temp.find(q) != string::npos){
        return 1;
    }
    return 0;
}

//another approach                                                            {T.C = O(N^2), S.C = O(N)}
int isCyclicRotation(string &p, string &q) {
    if (p == q) {
        return 1; // If p and q are equal, q is a cyclic rotation of p
    }

    string x = p; // Create a copy of string p

    char ch = x[x.size() - 1]; // Store the last character of x
    x.erase(x.size() - 1, 1); // Remove the last character from x
    x.insert(0, 1, ch); // Insert the last character at the beginning of x

    while (x != p) { // Continue until x becomes equal to p again
        if (x == q) {
            return 1; // If x is equal to q, q is a cyclic rotation of p
        }

        char ch = x[x.size() - 1]; // Store the last character of x
        x.erase(x.size() - 1, 1); // Remove the last character from x
        x.insert(0, 1, ch); // Insert the last character at the beginning of x
    }

    return 0; // q is not a cyclic rotation of p
}

/*
Sample Input 1:
abac
baca
Sample Output 1:
1
*/


//52. CHECK IF THE GIVEN STRING IS SHUFFLED SUBSTRING OF ANOTHER STRING               {T.C = O(N) , S.C = O(1)}
int main(){                                                                  
    string s1, s2, res;
    cin>>s1>>s2>>res;
    int l1 = s1.length();
    int l2 = s2.length();
    int lr = res.length();
    
    if(l1+l2 != lr){
        cout<<"No";
    }
    else{
        int flag = 0;
        int i = 0, j = 0, k = 0;
        while(k < lr){
            if(i < lr && s1[i] == res[k]){
                i++;
            }
            else if(j < l2 && s2[j] == res[k] ){
                j++;
            }
            else{
                flag = 1;
                break;
            }
            k++;
        }
        if(i < l1 || j < l2){
            cout<<"No";
        }
        else{
            cout<<"Yes";
        }
    }
    return 0;
}
/*
input
xy
12
x12y
output
Yes
*/


//53. COUNT AND SAY                                                                {T.C = O(N^2) , S.C = O(N)}
class Solution {
public:
    string countAndSay(int n) {
        if(n==1){
            return "1";
        }
        if(n==2){
            return "11";
        }
        string s = "11";
        for(int i = 3 ; i <= n ;i++){
            string t = "";
            s = s+'%';                     //put any extra character at last
            int count = 1;
            for(int j = 1 ; j < s.length() ; j++){     //if j = 0  then underflow (j-1)
                if(s[j] != s[j-1]){
                    t = t+ to_string(count);           //count, add to string
                    t = t+s[j-1];                      //say, add to string
                    count = 1;                         //reset count
                }
                else{
                    count++;
                }
            }
            s = t;
        }
        return s;
    }
};
/*
Input: n = 4
Output: "1211"
Explanation:
countAndSay(1) = "1"
countAndSay(2) = say "1" = one 1 = "11"
countAndSay(3) = say "11" = two 1's = "21"
countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"
*/


//54. LONGEST PALINDROME IN A STRING                                              {T.C = O(N^2), S.C = O(1)}
class Solution {
  public:
    string longestPalin (string s) {
        int l;
        int h;
        int start = 0;
        int end = 1;

        //for even length of strings
        for(int i = 1 ; i < s.length() ; i++){                //i = 1 overome underlfow
            l = i-1;
            h = i;                                           //pointer consecutive char
            while(l >= 0 && h < s.length() && s[l] == s[h] ){
                if(h-l+1 > end){
                    start = l;
                    end = h-l+1;
                }
                l--;
                h++;
            }
        }
        
        //for odd length of strings
        for(int i = 1 ; i < s.length() ; i++){
            l = i-1;
            h = i+1;                                       //pointer alternate char
            while(l >= 0 && h < s.length() && s[l] == s[h]){
                if(h-l+1 > end){
                    start = l;
                    end = h-l+1;
                }
                l--;
                h++;
            }
        }
        
        return s.substr(start,end);
    }
};
/*
Input:
S = "aaaabbaa"
Output: aabbaa
Explanation: The longest Palindromic
substring is "aabbaa".
*/




//56. LONGEST REPEATING SUBSEQUENCE                                                     {T.C = O(N^2), S.C = O(N^2)}
class Solution { 
	public:
	    int helper(string &str, int n1 , int n2 , vector<vector<int>>&dp){
	        //base case
	        if(n1 == 0 || n2 == 0){
	            return 0;
	        }
	        
	        //step-3 if answer already present return it
	        if(dp[n1][n2] != -1){
	            return dp[n1][n2];
	        }
	        
	        //character match or not
	        int ans = 0;
	        if(str[n1-1] == str[n2-1] && n1 != n2){
	            ans = 1 + helper(str, n1-1 , n2-1, dp);
	        }
	        else{
	            ans = max(helper(str, n1-1, n2, dp), helper(str, n1, n2-1,dp));
	        }
	        
	        //step-2 store answer in dp
	        dp[n1][n2] = ans;
	        return dp[n1][n2];
	        
	    }
		int LongestRepeatingSubsequence(string str){
		    int n = str.length();
		    //step-1 create a dp vector
		    vector<vector<int>>dp(n+1,vector<int>(n+1, -1));
		    return helper(str, n , n , dp);
		}

};
/*
Input:
str = "axxzxy"
Output: 2
Explanation:
The given array with indexes looks like
a x x z x y 
0 1 2 3 4 5
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
2 4  <-- index of str 

We are able to use character 'x' 
(at index 2 in str) in both subsequences
as it appears on index 1 in subsequence A 
and index 0 in subsequence B.
*/


//57. PRINT ALL SUBSEQUENCE OF STRING
//RECURSION                                                           {T.C = O(EXP) , S.C = O(N)}
class Solution {
	public:
	    void helper(string &str, string temp , int i){
	        //base case
	        if(i== str.length()){
	            cout<<temp<<" ";
	            return; 
	        }
	        
	        //take
	        helper(str, temp+str[i],i+1);
	        
	        //no take
	        helper(str, temp, i+1);                         //(str, temp+0, i+1)
	        
	        return;
	    }
		int subsequence(string str){
		    helper(str,"", 0);
		    
		    return 0;
		}
};
/*
For Input: 
axxxy
Your Recursion Output: 
axxxy axxx axxy axx axxy axx axy ax axxy axx axy ax axy ax ay a xxxy xxx xxy xx xxy xx xy x xxy xx xy x xy x y  0
*/

//RECURSION + MEMOIZATION                                                    {T.C = O(EXP), S.C = O(N)}
//REDUNDANT ELEMENT ELIMINATES
class Solution {
	public:
    void helper(string& str, string temp, int i, vector<vector<int>>& dp) {
        // Base case
        if (i == str.length()) {
            cout << temp << " ";
            return;
        }

        // Check if answer already present in dp
        if (dp[i][temp.length()] != -1) {
            cout << temp + str.substr(i) << " ";
            return;
        }

        // Take
        helper(str, temp + str[i], i + 1, dp);

        // No take
        helper(str, temp, i + 1, dp);

        // Store the answer in dp
        dp[i][temp.length()] = i;
    }

    int LongestRepeatingSubsequence(string str) {
        vector<vector<int>> dp(str.length() + 1, vector<int>(str.length() + 1, -1));
        helper(str, "", 0, dp);
        return 0;
    }
};
/*
For Input: 
axxxy

Your DP output
axxxy axxx axxy axx axxy axy ax axxy axy ay a xxxy xxy xy y  0
*/


//58. PERMUTIONS OF A GIVEN STRING                                                                     {T.C = O(N!) , S.C = O(N)}
//not handle duplicates        (error)
class Solution
{
	public:
	    void solve(vector<string>&ans, string &s, int index){
	        int n = s.length();
	        //base case
	        if(index >= n){
	            ans.push_back(s);
	        }
	        
	        for(int i = index ; i < n ; i++ ){
	            swap(s[index], s[i]);
	            solve(ans, s, index+1);
	            //backtrack
	            swap(s[index],s[i]);
	        }
	    }
		vector<string>find_permutation(string s)
		{
		    vector<string>ans;
		    solve(ans, s, 0);
		    return ans;
		}
};
//handle duplicates (using map)
class Solution {
public:
    set<string> st;
    string s;

    void rec(int i) {
        if (i == s.size()) {
            st.insert(s);
        } else {
            for (int j = i; j < s.size(); j++) {
                swap(s[i], s[j]);
                rec(i + 1);                            //RECURSIVE CALL
                //backtrack
                swap(s[i], s[j]);
            }
        }
    }

    vector<string> find_permutation(string S) {
        s = S;
        rec(0);
        vector<string> ans(st.begin(), st.end());
        return ans;
    }
};
/*
Input: ABC
Output:
ABC ACB BAC BCA CAB CBA
Explanation:
Given string ABC has permutations in 6 
forms as ABC, ACB, BAC, BCA, CAB and CBA .
*/


//59. SPLIT BINARY STRING                                                               {T.C = O(N), S.C = O(1)}
int splitString(string &str)  
{
    int n = str.length();
    int x = 0;
    int y = 0;
    int count = 0;
    for(int i = 0 ; i < n ; i++){
        if(str[i] == '0'){
            x++;
        }
        else if(str[i] == '1'){
            y++;
        }

        if(x == y){
            count++;
        }
    }
    if(x != y){
        return -1;
    }
    return count;
}
/*
Sample Input 1 :
2
10101100
11111111
Sample Output 1 :
3
-1
*/


//60. WORD WRAP                                                                   {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[505][2005];
    int solve(int i, int rem,vector<int>& arr, int &k) {        //k= maximum line length , rem = k-length(already placed words in curr line)
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
Input: nums = {3,2,2}, k = 4
Output: 5
Explanation: Given a line can have 4 
characters,
Line number 1: From word no. 1 to 1
Line number 2: From word no. 2 to 2
Line number 3: From word no. 3 to 3
Same explaination as above total cost
= (4 - 3)2 + (4 - 2)2 = 5.
*/


//61. EDIT DISTANCE 
//RECURSION + MEMOIZATION                                                           {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int solve(int i, int j, string &a, string &b, vector<vector<int>>& dp) {
        //Base case: If we reach the end of string 'a'/'b', return the remaining length of string 'b'/'a'
        if (i == a.length()) {
            return b.length() - j;      //remaining length from j to b.length()
        }
        if (j == b.length()) {
            return a.length() - i;      //remaining length from i to a.length()
        }

        //step-3 if answer already present return it
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int ans;
        // If the characters at indices 'i' and 'j' are the same, move to the next characters
        if (a[i] == b[j]) {
            ans = solve(i + 1, j + 1, a, b, dp);
        } else {       // Calculate the minimum edit distance for three possible operations: insert, delete, and replace
            int insertAns = 1 + solve(i, j + 1, a, b, dp);     //solve(1, 2, "abc", "axbc", dp)
            int deleteAns = 1 + solve(i + 1, j, a, b, dp);     //solve(2, 1, "abcd", "acd", dp)
            int replaceAns = 1 + solve(i + 1, j + 1, a, b, dp);//solve(2, 2, "abc", "axc", dp)
            ans = min(insertAns, min(deleteAns, replaceAns));
        }

        //step-2 store ans in dp
        dp[i][j] = ans;
        return ans;
    }

    int editDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        //step-1 create a dp vector
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, word1, word2, dp);
    }
};

//SPACE OPTIMIZATION METHOD                                                           {T.C = O(N*M), S.C = O(M)}
class Solution {
public:
    int solveSO(string &a, string &b){
        //step-1 create dp vector initialize 0
        int n = a.length();
        int m = b.length();

        vector<int>curr(m+1, 0);
        vector<int>next(m+1, 0);

        //step-2 analyze base case
        for(int j = 0 ; j < b.length() ; j++){
            next[j] = b.length() - j;
        }

        //step-3 loop
        for(int i = a.length()-1 ; i >= 0 ; i--){
            for(int j = b.length()-1 ; j >= 0 ; j--){

                //catche here from base case
                curr[b.length()] = a.length() - i;

                int ans = 0;
                if(a[i] == b[j]){
                    ans = next[j+1];
                }
                else{
                    //insert
                    int insertAns = 1 + curr[j+1];

                    //delete
                    int deleteAns = 1 + next[j];

                    //replace
                    int replaceAns = 1 + next[j+1];

                    ans = min(insertAns, min(deleteAns, replaceAns));
                }
                curr[j] = ans;
            }
            next = curr;
        }
        return next[0];
    }
    int editDistance(string word1, string word2) {
        if(word1.length() == 0){
            return word2.length();
        }
        if(word2.length() == 0){
            return word1.length();
        }
        return solveSO(word1, word2);                            //i = 0 , j = 0
    }
};
/*
Input: 
s = "geek", t = "gesek"
Output: 1
Explanation: One operation is required 
inserting 's' between two 'e's of s.
*/


//62. NEXT PERMUTATION         
//using STL                                                                             {T.C = O(N), S.C = O(1)}
class Solution{
public:
    vector<int> nextPermutation(int N, vector<int> arr){
        next_permutation(arr.begin(), arr.end());
        return arr;
    }
};

//OPTIMAL OPPROACH WITHOUT STL                                                            {T.C = O(N), S.C = O(1)}
class Solution{
public:
    vector<int> nextPermutation(int n, vector<int> arr){
        int index = -1;
        //finding break point
        for(int i = n-2 ; i >= 0 ; i--){
            if(arr[i] < arr[i+1]) {
                index = i;
                break;
            }
        }
        // if no break point found , simply just reverse it
        if(index == -1){
            reverse(arr.begin(), arr.end());
            return arr;
        }
        // find somevalue greater than break point but the smallest one so that you stay close
        for(int i=n-1;i>=index;i--){
            if(arr[i]>arr[index]){
                swap(arr[i],arr[index]);
                break;
            }
        }
        reverse(arr.begin() + index + 1, arr.end());
        
        return arr;
    }
};
/*
Input: N = 6
arr = {1, 2, 3, 6, 5, 4}
Output: {1, 2, 4, 3, 5, 6}
Explaination: The next permutation of the 
given array is {1, 2, 4, 3, 5, 6}.
*/


//63. PARENTHISIS CHECKER                                                                 {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    //Function to check if brackets are balanced or not.
    bool ispar(string x)
    {
        stack<char>st;
        for(int i = 0 ; i < x.size() ; i++){
            if(x[i] == '(' || x[i] == '[' || x[i] == '{'){
                st.push(x[i]);
            }
            else{
                if(!st.empty()){
                    if((st.top() == '(' && x[i] == ')') ||(st.top() == '[' && x[i] == ']') || (st.top() == '{' && x[i] == '}')){
                        st.pop();
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
        }
        if(st.empty()){
            return true;
        }else{
            return false;
        }
    }
};
/*
Input:
{([])}
Output: 
true
Explanation: 
{ ( [ ] ) }. Same colored brackets can form 
balanced pairs, with 0 number of 
unbalanced bracket.
*/


//64. WORD BREAK
//RECURSION                                                                              {T.C = O(EXP) , S.C = O(N)}
class Solution
{
public:
    int help(int index , string &a, unordered_set<string>&st){
        if(index == a.size()){
            return 1;
        }
        string temp;
        for(int i = index ; i < a.size() ; i++){
            temp += a[i];
            if(st.find(temp) != st.end()){
                if(help(i+1, a, st)){
                    return 1;
                }
            }
        }
        return 0;
    }
    int wordBreak(string a, vector<string> &b) {
        unordered_set<string>st;
        for(auto it : b){
            st.insert(it);
        }
        return help(0, a, st);                      //index = 0 , string = a , set = st
    }
};

//RECURSTION + MEMOIZATION                                                             {T.C = O(N), S.C = O(N)}
class Solution
{
public:
    int help(int index, string &a, unordered_set<string> &st, vector<int> &dp)
    {
        if (index == a.size()){
            return 1;
        }

        //step-3 if answer already exists, return it
        if (dp[index] != -1){
            return dp[index];
        }

        string temp;
        for (int i = index; i < a.size(); i++){
            temp += a[i];
            if (st.find(temp) != st.end()){
                if (help(i + 1, a, st, dp)){
                    return dp[index] = 1;
                }
            }
        }

        //step-2 store ans in dp
        dp[index] = 0;
        return dp[index];
    }

    int wordBreak(string a, vector<string> &b)
    {
        unordered_set<string> st;

        //step-1 create a dp vector
        vector<int> dp(a.size() + 1, -1);
        for (auto it : b)
        {
            st.insert(it);
        }
        return help(0, a, st, dp); //index = 0 , string = a , set = st
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


//65. ROBIN CARP ALGORITHM
//PRE - REQUISITES (STRING HASHING)
//finding unique number of strings in a set of strings                                   {T.C = O(N*MLOGN), S.C = O(1)} //M = 1 STRING LENGTH
int main(){
    vector<string>strings = {"aa", "ab", "aa", "bc", "cc", "aa", "bc"};
    sort(strings.begin(), strings.end());
    int distinct = 0;
    for(int i= 0 ; i < strings.size() ; i++){
        if(i == 0 || strings[i] != strings[i-1]){
            distinct++;
        }
    }
    cout<<distinct;
}
/*
output
4
*/


//66. LONGEST PREFIX SUFFIX  / KMP ALGO
class Solution {
public:
    int lps(string s) {
        int n = s.length();
        vector<int> lpsArr(n, 0);
        int prevLen = 0;

        for (int i = 1; i < n;) {
            if (s[i] == s[prevLen]) {
                prevLen++;
                lpsArr[i] = prevLen;
                i++; // Increment 'i' here to move to the next character
            } else {
                if (prevLen != 0) {
                    prevLen = lpsArr[prevLen - 1];
                } else {
                    lpsArr[i] = 0;
                    i++; // Increment 'i' here to move to the next character
                }
            }
        }

        return lpsArr[n - 1];
    }
};
/*
Input: s = "aaaa"
Output: 3
Explanation: "aaa" is the longest proper 
prefix and suffix. 
*/


//67. Convert a Sentence into its equivalent mobile numeric keypad sequence.                                        {T.C = O(N), S.C = O(N)}
string printSequence(string s)
{
    string ans = "";
    string arr[] = {"2", "22", "222", "3", "33", "333", "4", "44", "444", "5", "55", "555", "6", "66", "666", "7", "77", "777", "7777", "8", "88", "888", "9", "99", "999", "9999"};   
    
    for(int i = 0 ; i < s.length() ; i++){
        if(s[i] == ' '){                            //for space add 0
            ans += "0";
        }
        else{
            ans += arr[s[i]-'A'];                  //map to arr and gives index 
        }
    }
    return ans;
}
/*
Input:
S = "HEY U"
Output: 4433999088
Explanation: For 'H' press '4' two times.
For 'E' press '3' two times. For 'Y' press '9' 
three times. For white space press '0' one time.
For 'U' press '8' two times.
*/

//68. COUNT THE REVERSALS                                                                                 {T.C = O(N), S.C = O(N)}
int countRev (string s)
{
    int n = s.length();
    int ans = 0;
    if(n&1){
        return -1;
    }
    else{
        stack<char>st;
        int clBrCount = 0;                          //closing bracket count
        int opBrCount = 0;                          //opening bracket count
        
        for(int i = 0 ; i < n ; i++){
            char ch = s[i];
            if(ch == '{'){
                st.push(ch);
                opBrCount++;
            }
            else if(ch == '}' && !st.empty() && st.top() == '{'){
                st.pop();
                opBrCount--;
            }
            else{        //stack is empty
                st.push(ch);
                clBrCount++;
            }
        }
        
        // }}} {{{{{
        if(clBrCount & 1){     //odd
            clBrCount = clBrCount/2 + 1;
        }
        else{  //even
            clBrCount = clBrCount/2;
        }
        
        if(opBrCount & 1){  //odd
            opBrCount = opBrCount/2 + 1;
        }
        else{
            opBrCount = opBrCount/2;
        }
        ans = opBrCount+clBrCount;
    }
    
    return ans;
}
/*
S = "}{{}}{{{"
Output: 3
Explanation: One way to balance is:
"{{{}}{}}". There is no balanced sequence
that can be formed in lesser reversals.
*/


//69. COUNT PALINDROMIC SUBSEQUENCES
//RECURSION + MEMOIZATION                                                                        {T.C = O(N^2), S.C = O(N^2)}
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

//BOTTOM UP APPROACH                                                               {T.C = O(N^2), S.C = O(N)}
class Solution{
public:
    /* You are required to complete the below method which counts the number of palindromic subsequences in a given string. */
    long long int countPS(string A) {
        // Your code here
        
        // Define the modulo value to avoid integer overflow.
        int MOD = 1000000007;
        
        // Create a copy of the input string and reverse it to find palindromic subsequences easily.
        string a = A;
        reverse(A.begin(), A.end());
        string b = A;
        
        // 'n' represents the length of the input string.
        int n = a.length();
        
        // Initialize a vector 'dp' to store the counts of palindromic subsequences ending at index 'j'.
        vector<long long int> dp(n+1, 0);
        
        // Initialize a vector 'next' to keep track of the counts for the next iteration.
        vector<long long int> next(n+1, 0);
        
        // Loop from the end of the string to the beginning, to calculate the counts of palindromic subsequences.
        for(int i = n-1; i >= 0; i--) {
            for(int j = i; j < n; j++) {
                if (i == j)
                    dp[j] = 1; // For a single character, there is only one palindromic subsequence.
                else if (a[i] == a[j])
                    dp[j] = (next[j] + dp[j - 1] + 1) % MOD; // Characters at 'i' and 'j' are the same, add new palindromic subsequences.
                else
                    dp[j] = ((next[j] + dp[j - 1] - next[j - 1]) % MOD + MOD) % MOD; // Characters at 'i' and 'j' are different, avoid overcounting.
            }
            
            // Update 'next' with the values of 'dp' for the next iteration.
            next = dp;
        }
        
        // The final answer is stored in 'next[n-1]', which represents the count of palindromic subsequences in the original string.
        return next[n-1];
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


//70. Count of number of given string in 2D character array                                       {T.C = O(N) , S.C = O(N)}
int solve(int i, int j, string &s, char ch[6][6], int size, int index) {
    int found = 0;
    if (i >= 0 && j >= 0 && i < 6 && j < 6 && s[index] == ch[i][j]) {
        char temp = s[index];     
        ch[i][j] = 0; // after track put 0 on place
        index++;
        if (index == size) {
            found = 1;
        } else {
            found += solve(i + 1, j, s, ch, size, index);
            found += solve(i - 1, j, s, ch, size, index);
            found += solve(i, j + 1, s, ch, size, index);
            found += solve(i, j - 1, s, ch, size, index);
        }
        ch[i][j] = temp; // backtrack revert 0
    }
    return found;
}

int main() {
    string s = "GEEKS";
    
    char ch[6][6] = {{'D', 'D', 'D', 'G', 'D', 'D'},
                     {'B', 'B', 'D', 'E', 'B', 'S'},
                     {'B', 'S', 'K', 'E', 'B', 'K'},
                     {'D', 'D', 'D', 'D', 'D', 'E'},
                     {'D', 'D', 'D', 'D', 'D', 'E'},
                     {'D', 'D', 'D', 'D', 'D', 'G'}
                    };
                    
    int ans = 0;
    int size = 5;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            ans += solve(i, j, s, ch, size, 0); // 0 is index
        }
    }
    cout << ans;
}
/*output
2
*/


//71. FIND THE STRING IN GRID                                                                             {T.C = O(N*M*K), S.C = O(1)}
class Solution {
public:
	vector<vector<int>>searchWord(vector<vector<char>>grid, string word){
	    vector<vector<int>>ans;
	    int n = grid.size();             //row size
	    int m = grid[0].size();          //col size
	    
	    for(int i = 0 ; i < n  ; i++){
	        for(int j = 0 ; j < m ; j++){
	            if(grid[i][j] == word[0]){                 //starting char match
	                bool found = false;
                    //for all direction coorditantes (-1, 1)
	                for(int k1 = -1 ; k1 <= 1 ; k1++){
	                    for(int k2 = -1 ; k2 <= 1; k2++){
	                        if(found){
	                            break;
	                        }
	                        else if(k1 == 0 && k2 == 0){
	                            continue;
	                        }else{
	                            int tempi = i;
	                            int tempj = j;
	                            int l;
	                            for(l = 0 ; l < word.size() ; l++){
	                                if(tempi >= 0 && tempj >= 0 && tempi < n && tempj < m && grid[tempi][tempj] == word[l]){
	                                    tempi += k1;
	                                    tempj += k2;
	                                }else{
	                                    break;
	                                }
	                            }
	                            if(l == word.size()){
	                                found = true;
	                                ans.push_back({i, j});
	                            }
	                        }
	                    }
	                }
	                
	            }
	        }
	    }
	    sort(ans.begin(), ans.end());
	    return ans;
	}
};
/*
Input: grid = {{a,b,c},{d,r,f},{g,h,i}},
word = "abc"
Output: {{0,0}}
Explanation: From (0,0) one can find "abc"
in horizontally right direction.
*/

//72. BOYER-MOORE ALGORITHM FOR PATTERN SEARCHING                                                      {T.C = OMEGA(N) , S.C = O(M)}
/*
The Boyer-Moore algorithm is a powerful string-searching algorithm that efficiently finds occurrences of a pattern within a larger text. 
It was developed by Robert S. Boyer and J Strother Moore in 1977. The algorithm takes advantage of two main heuristics: the Bad Character 
Heuristic and the Good Suffix Heuristic. These heuristics allow the algorithm to skip comparisons and significantly reduce the number of 
character comparisons needed during the search.

1. Bad Character Heuristic:
   This heuristic focuses on the last occurrence of a character in the pattern. When a mismatch occurs at a certain position in the pattern, 
   we check the text character aligned with that position. If this character exists in the pattern, we can shift the pattern to align it with 
   the rightmost occurrence of that character in the pattern. This shift helps us to skip more characters and quickly move to a new possible 
   matching position.

2. Good Suffix Heuristic:
   This heuristic deals with the matching suffix of the pattern (a suffix that matches a suffix in the text). When a mismatch happens, we look 
   for a matching suffix of the pattern in the text. If such a matching suffix exists, we can align the pattern to that position, which allows 
   us to skip more characters and improve the search efficiency.

The combination of these heuristics enables Boyer-Moore to achieve sublinear average-case time complexity for pattern searching.

Here's the C++ code for the Boyer-Moore algorithm with comments:
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to create a bad character table for the pattern
void createBadCharacterTable(const string& pattern, vector<int>& badCharTable) {
    int m = pattern.length();

    // Initialize all occurrences as -1
    for (int i = 0; i < 256; i++) {
        badCharTable[i] = -1;
    }

    // Fill the actual occurrences of characters in the pattern
    for (int i = 0; i < m; i++) {
        badCharTable[pattern[i]] = i;
    }
}

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to perform the Boyer-Moore pattern search
void boyerMooreSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> badCharTable(256);
    createBadCharacterTable(pattern, badCharTable);

    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;

        // Keep matching the pattern from right to left
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            // Pattern found at this shift
            cout << "Pattern found at index: " << shift << endl;
            
            // Move the pattern to the right to find other occurrences
            shift += (shift + m < n) ? m - badCharTable[text[shift + m]] : 1;
        } else {
            // Mismatch occurred, calculate the shift based on bad character and good suffix heuristics
            int badCharShift = max(1, j - badCharTable[text[shift + j]]);
            int goodSuffixShift = 0;

            // Check if there's a good suffix
            if (j < m - 1) {
                // Calculate the shift using good suffix heuristics
                // Note: This part can be further optimized for specific cases.
                int k = m - 1;
                while (k > j && pattern[k] == pattern[k - j - 1]) {
                    k--;
                }
                goodSuffixShift = j - k;
            }

            // Take the maximum of bad character and good suffix shifts
            shift += max(badCharShift, goodSuffixShift);
        }
    }
}

int main() {
    string text = "ABAAABCDABABCDABCD";
    string pattern = "ABCD";

    boyerMooreSearch(text, pattern);

    return 0;
}
/*
In this code, `boyerMooreSearch` is the main function that performs the Boyer-Moore pattern search. The `createBadCharacterTable`
function constructs the bad character table, and `max` function is a utility function to find the maximum of two integers. The algorithm
starts searching the pattern from the end and shifts the pattern based on the heuristics to efficiently find all occurrences of the pattern
in the given text.*/


//73. ROMAN NUMBER TO INTEGER                                                                         {T.C = O(N), S.C = O(N)}
class Solution {
  public:
    int romanToDecimal(string &str) {
        unordered_map<char, int>mp;
        mp['I'] = 1;
        mp['V'] = 5;
        mp['X'] = 10;
        mp['L'] = 50;
        mp['C'] = 100;
        mp['D'] = 500;
        mp['M'] = 1000;
        
        int ans = 0;
        for(int i = 0 ; i < str.size() ; i++){
            if(mp[str[i]] < mp[str[i+1]]){
                ans -= mp[str[i]];                    //subtract if starting element small
            }else{
                ans += mp[str[i]];                    //add if starting element is big
            }
        }
        return ans;
    }
};
/*
Input:
s = V
Output: 5
*/


//74. LONGEST COMMON PREFIX                                                          {T.C = O(N*M*LOGN) , S.C = O(N)}
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        
        sort(strs.begin(), strs.end());
        int n = strs.size();

        string a = strs[0];
        string b = strs[n-1];
        string ans = "";

        //traverse each character in particular string
        for(int i = 0 ; i < a.size() ; i++){
            if(a[i] == b[i]){
                ans += a[i];
            }else{
                break;
            }
        }
        return ans;
    }
};
/*
Input: strs = ["flower","flow","flight"]
Output: "fl"
*/


//75. MINIMUM NUMBER OF FLIPS                                                           {T.C = O(N), S.C = O(1)}
int minFlips (string s)
{
    int n = s.length();
    int a = 0 , b = 0;
    
    for(int i = 0 ; i < n ; i++){
        s[i] = s[i] - '0';                         //0-0 = 0 (even) , 1-0 = 1 (odd)
        
        if(i % 2 != s[i]){                         //not even
            a++;
        }
        if((i+1) % 2 != s[i]){                     //not odd
            b++;
        }
    }
    return min(a, b);                              //flip requireds
}
/*
Input:
S = "0001010111" 
Output: 2
Explanation: We can flip the 1st and 8th bit 
bit to have "0101010101"
101.
*/


//76a. MOST REPEATING STRING IN A SEQUENCE                                                                {T.C = O(N), S.C = O(N)}
class Solution
{
  public:
    string secFrequent (string arr[], int n)
    {
        unordered_map<string, int>mp;
        for(int i = 0 ; i < n ; i++){
            mp[arr[i]]++;
        }
        
        string ans = "";
        int maxFrequency = 0;
        for(auto it : mp){
            if(it.second > maxFrequency){
                maxFrequency = it.second;
                ans = it.first;
            }
        }
        return ans;
    }
};
/*
Input:
N = 6
arr[] = {aaa, bbb, ccc, bbb, aaa, aaa}
Output: aaa
Explanation: "aaa" is the most 
occurring string with frequency 3.
*/


//76b. SECOND MOST REPEATING STRING IN A SEQUENCE                                                               {T.C = O(N) ,S.C = O(N)}
class Solution
{
  public:
    string secFrequent (string arr[], int n)
    {
        unordered_map<string, int>mp;
        for(int i = 0 ; i < n ; i++){
            mp[arr[i]]++;
        }
        
        string mostRepeatedString = "";
        string secondMostRepeatedString = "";
        int maxFrequency = 0;
        int secondMaxFrequency = 0;
        for(auto it : mp){
            if(it.second > maxFrequency){
                secondMaxFrequency = maxFrequency;
                maxFrequency = it.second;
                secondMostRepeatedString = mostRepeatedString;
                mostRepeatedString = it.first;
            }else if(it.second > secondMaxFrequency && it.second != maxFrequency){
                secondMaxFrequency = it.second;
                secondMostRepeatedString = it.first;
            }
        }
        return secondMostRepeatedString;
    }
};
/*
Input:
N = 6
arr[] = {aaa, bbb, ccc, bbb, aaa, aaa}
Output: bbb
Explanation: "bbb" is the second most 
occurring string with frequency 2.
*/


//77. MINIMUM SWAPS FOR BRACKET BALANCING                                                              {T.C = O(N), S.C = O(1)}
class Solution{   
public:
    int minimumNumberOfSwaps(string s){
        int n = s.length();
        int opBrac = 0, clBrac = 0, unBalanced = 0, swap = 0;
        
        for(int i = 0 ; i < n ; i++){
            char ch = s[i];
            if(ch == '['){
                opBrac++;
                if(unBalanced > 0){
                    swap += unBalanced;
                    unBalanced--;
                }
            }else{
                clBrac++;
                unBalanced = clBrac - opBrac;
            }
        }
        return swap;
    }
};
/*
Input  : []][][
Output : 2
Explanation :
First swap: Position 3 and 4
[][]][
Second swap: Position 5 and 6
[][][]
*/


//78. LONGEST COMMON SUBSEQUENCE
//RECURSION + MEMOIZATION (TLE)                                                     {T.C = O(N*M), S.C = O(N*M)}
class Solution
{
    public:
    //Function to find the length of longest common subsequence in two strings.
    int lcs(int n, int m, string s1, string s2)
    {
        //step-1 create a dp vector
        vector<vector<int>>dp(n+1, vector<int>(m+1, -1));
        
        //base case
        if(n == 0 || m == 0){
            return 0;
        }
        
        //step-3 if answer already present return it
        if(dp[n][m] != -1){
            return dp[n][m];
        }
        
        int ans;
        if(s1[n-1] == s2[m-1]){
            ans = 1 +  lcs(n-1, m-1, s1 , s2);
        }else{
            ans = 0 + max(lcs(n-1, m , s1, s2), lcs(n, m-1, s1, s2));
        }
        
        //step-2 store ans in dp
        dp[n][m] = ans;
        
        return dp[n][m];
        
    }
};

//BOTTOM UP APPROACH                                                                {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int lcs(int n, int m, string s1, string s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[n][m];
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


//79. PROGRAM TO GENERATE ALL POSSIBLE VALID IP ADDRESSES FROM GIVEN STRING
bool isValidIPv4(string ipAddress) {
    int x = 0;
    int dotCount = 0;
    for(int i = 0 ; i < ipAddress.size() ; i++){
        if(ipAddress[i] != '.' && isdigit(ipAddress[i])){
            x = x*10 + (ipAddress[i] - '0');
        }
        else if(ipAddress[i] == '.'){
            if(x > 255){
                return false;
            }
            dotCount++;
            x = 0;
        } 
        else{
            return false;
        }
    }
    if(dotCount < 3 || dotCount > 3){
        return false;
    }
    return true;
}
/*
Sample Input 1:
4
123.111.12.k
122.0.330.0
1.1.1.250
1.0.0.0.1
Sample Output 1:
False
False
True
False
*/


//80. SMALLEST DISTINCT WINDOW                                                    {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    int findSubString(string str)
    {
        int n = str.size();
        int ans = str.size();                //all distinct
        unordered_set<char>st;                         //give unique char   /*not set (TLE)*/
        for(auto c : str){
            st.insert(c);
        }
        
        int m = st.size(); 
        
        unordered_map<char , int>mp;
        int i = 0;                           //starting pointer
        int j = 0;                           //ending pointer
        
        while(j < n){
            mp[str[j]]++;
            if(mp.size() == m){
                while(mp[str[i]] > 1){
                    mp[str[i]]--;                        //matching element remove 
                    i++;
                }
                ans = min(ans, j-i+1);                 //j-i+1 = length
            }
            j++;
        }
        return ans;
    }
};
/*
Input : "AABBBCBBAC"
Output : 3
Explanation : Sub-string -> "BAC"
*/


//81. REORGANIZE STRING / REARRANGE CHARACTER IN A STRING SUCH THAT NO ADJACENT CHARACTER SAME   {T.C = O(N), S.C = O(1)}
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


//82. MINIMUM CHARACTERS TO BE ADDED AT FRONT TO  MAKE STRING PALINDROME                                      {T.C = O(N), S.C = O(N)}
//USING LPS (LONGEST PROPER PREFIX & SUFFIX)
class Solution {
public:
    vector<int>computeLps(string s){
        int n = s.length();
        vector<int>lps(n);
        
        lps[0] = 0;                         //1st value is always 0 in lps array
        int len = 0;                        //length of previous lps 
        int i = 1;
        while(i < n ){
            if(s[i] ==  s[len]){
                len++;
                lps[i] = len;
                i++;
            }
            else{
                if(len != 0){
                    len = lps[len-1];
                }
                else{ //len == 0
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }
    int minChar(string str){
        string rev = str;
        reverse(rev.begin(), rev.end());
        
        string c = str + "$" + rev;
        vector<int>lps = computeLps(c);
        
        int ans = str.length()-lps.back();        //length of string - last element of lps array
        return ans;
    }
};
/*
Input:
S = "abc"
Output: 2
Explanation: 
Add 'b' and 'c' at front of above string to make it
palindrome : "cbabc"
*/


//83. PRINT ANAGRAMS TOGETHER                                                                         {T.C = O(N*M*LOGM), S.C = O(N*M)}
class Solution{
  public:   
    vector<vector<string> > Anagrams(vector<string>& string_list) {
        vector<vector<string>>ans;
        
        unordered_map<string, vector<string>>mp;
        
        for(auto it : string_list){
            string temp = it;                              //stor particular string in a list
            sort(it.begin(), it.end());                    //sort each string in a list
            mp[it].push_back(temp);                        //push string to map
        }
        
        for(auto x : mp){
            ans.push_back(x.second);
        }
        return ans;
    }
};
/*
Input:
N = 5
words[] = {act,god,cat,dog,tac}
Output:
act cat tac 
god dog
Explanation:
There are 2 groups of
anagrams "god", "dog" make group 1.
"act", "cat", "tac" make group 2.
*/


//84. SMALLEST WINDOW IN A STRING CONTAINING ALL THE CHARACTERS OF ANOTHER STRING
//not optimized approach (unordered_map)                                                         {T.C = O(N^2), S.C = O(N)}
class Solution
{
public:
    string smallestWindow(string s, string p)
    {
        if (p.size() > s.size()){
            return "-1";
        }
        
        int i = 0;
        int j = 0;
        int start = 0;
        int minlen = INT_MAX;
        int count = 0;
        
        unordered_map<char, int> mp;
        
        for (char ch : p) {
            mp[ch]++;
        }

        count = mp.size(); // Count of unique characters in string p.
        
        while (j < s.size()) {
            // Modify the unordered map for the current character at index j.
            if (mp.find(s[j]) != mp.end()) {
                mp[s[j]]--;
                if (mp[s[j]] == 0) {
                    count--;
                }
            }

            // If all characters in p are found in the window [i, j], try to minimize it.
            while (count == 0) {
                if (minlen > j - i + 1) {
                    minlen = j - i + 1;
                    start = i;
                }
                
                // Move the window's left boundary to the right to minimize the window.
                // Update the unordered map accordingly.
                if (mp.find(s[i]) != mp.end()) {
                    mp[s[i]]++;
                    if (mp[s[i]] > 0) {
                        count++;
                    }
                }
                
                i++;
            }
            
            j++;
        }
        
        if (minlen == INT_MAX)
            return "-1";
        return s.substr(start, minlen);
    }
};

//optimized approach  (vector, 2 pointer)                                                              {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    string smallestWindow (string s, string p)
    {
        if(p.size()>s.size()){
            return "-1";
        } 
        int i=0;
        int j=0;
        int start=0;
        int minlen=INT_MAX;
        int count=0;
        vector<int>mp(26,0);
        for(int i=0;i<p.size();i++){
            if(mp[p[i]-'a']==0){
                count++;
            }
            mp[p[i]-'a']++;
            
        }
        
        while(j<s.size()){
            mp[s[j]-'a']--;
            if(mp[s[j]-'a']==0){
                count--;
            }
        
            if(count==0){
            while( count==0){
                   mp[s[i]-'a']++;
                   if(mp[s[i]-'a']==1){
                       count++;
                   }
                   if(minlen>j-i+1){
                        minlen=j-i+1;
                        start=i;
                    }
              
                i++;
            }


            }
            j++;
        }
        if(minlen==INT_MAX){
            return "-1";
        } 
        return s.substr(start, minlen);
    }
};
/*
Input:
S = "zoomlazapzo"
P = "oza"
Output: 
apzo
Explanation: "apzo" is the smallest 
substring in which "oza" can be found.
*/


//85. REMOVE CONSECUTIVE CHARACTERS                                                                       {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    string removeConsecutiveCharacter(string s)
    {
        int n = s.size();
        string ans = "";
        for(int i = 0 ; i < n ;i++){
            if(s[i] != s[i+1]){
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};
/*
Input:
S = aabb
Output:  ab 
Explanation: 'a' at 2nd position is
appearing 2nd time consecutively.
Similiar explanation for b at
4th position.
*/


//86. WILD CARD STRING MATCHING
//RECURSION                                                                                             {T.C = O(EXP), S.C = O(N+M)}

class Solution{
    public:

    bool solve(string &s, string &p, int i , int j){
        //base case
        if(i < 0 && j < 0){                                         //both string exhaust
            return true;
        }
        if(i >= 0 && j < 0){                                        //pattern string exhaust
            return false;
        }
        if(i < 0 && j >= 0){                                        //sample string exhaust
            for(int k = 0 ; k <= j ; k++){
                if(p[k] != '*'){
                    return false;                                   //remain pattern contain another char
                }
            }
            return true;                                            //remain pattern contain *
        }

        //match
        if(s[i] == p[j] || p[j] == '?'){
            return solve(s, p, i-1, j-1);
        }
        else if(p[j] == '*'){   //2 cases
              //matches 1 or more char       //matches 0 char
            return (solve(s, p, i-1, j) || solve(s, p, i, j-1));
        }
        
        return false;
    }
    bool match(string wild, string pattern) {
        int n = pattern.size();                    //actually a string
        int m = wild.size();                       //actually a pattern
        return solve(pattern, wild,n-1, m-1);               //reverse traversal
        //recturn sovle(string , pattern , n-1, m-1)  //acutally (leetcode) (n <-> m)
    }
};

//(LEETCODE)
//RECURSION                                                                                        {T.C = O(EXP), S.C = O(N+M)}
class Solution {
public:
    bool solve(string &s, string &p, int i , int j){
        //base case
        if(i < 0 && j < 0){                                         //both string exhaust
            return true;
        }
        if(i >= 0 && j < 0){                                        //pattern string exhaust
            return false;
        }
        if(i < 0 && j >= 0){                                        //sample string exhaust
            for(int k = 0 ; k < j ; k++){
                if(p[k] != '*'){
                    return false;
                }
            }
            return true;
        }

        //match
        if(s[i] == p[j] || p[j] == '?'){
            return solve(s, p, i-1, j-1);
        }
        else if(p[j] == '*'){
            //2 case
            return (solve(s, p, i-1, j) || solve(s, p, i, j-1));
        }
        else{
            return false;
        }
    }
    bool isMatch(string s, string p) {
        return solve(s, p, s.length()-1, p.length()-1);               //reverse traversal
    }
};

//RECURSION + MEMOIZATION                                                                      {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    bool solveMem(string &s, string &p, int i , int j, vector<vector<int>>&dp){
        //base case
        if(i < 0 && j < 0){                                         //both string exhaust
            return true;
        }
        if(i >= 0 && j < 0){                                        //pattern string exhaust
            return false;
        }
        if(i < 0 && j >= 0){                                        //sample string exhaust
            for(int k = 0 ; k <= j ; k++){
                if(p[k] != '*'){
                    return false;
                }
            }
            return true;
        }

        //step-3 if ans already present return it
        if(dp[i][j] != -1){
            return dp[i][j];
        }

        //match                         //step-2 store ans in dp
        if(s[i] == p[j] || p[j] == '?'){
            return dp[i][j] = solveMem(s, p, i-1, j-1, dp);
        }
        else if(p[j] == '*'){
            //2 case
            return dp[i][j] = (solveMem(s, p, i-1, j, dp) || solveMem(s, p, i, j-1, dp));
        }
        else{
            return false;
        }
    }
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        //step-1 create dp vector
        vector<vector<int>>dp(n, vector<int>(m, -1));

        return solveMem(s, p, s.length()-1, p.length()-1 , dp);               //reverse traversal
    }
};

/*
Input: wild = ge?ks*
       pattern = geeksforgeeks
Output: Yes
Explanation: Replace '?' and '*' in wild string with
'e' and 'forgeeks' respectively to obtain pattern 
"geeksforgeeks"
*/


//87. COUNT CUSTOMERS WHO DID NOT GET A COMPUTER                                                      {T.C = O(N), S.C = O(N)}
int countCustomers(vector<int> &arr, int k) {                                                          
    int n = arr.size();               // Number of customers
    vector<int> assign(n + 1);
    int availableComputers = k;       // Number of available computers
    int unsatisfiedCount = 0;         // Counter for unsatisfied customers

    for (auto i : arr) {
        if (assign[i] == 0) {
            if (availableComputers < 1) {
                // No available computers for the current customer, mark as unsatisfied.
                assign[i]--;
            } else {
                // Assign a computer to the current customer and decrease the available computers count.
                assign[i]++;
                availableComputers--;
            }
        } else if (assign[i] == 1) {
            // The customer already has a computer, release the computer and increase the available count.
            assign[i] = -1;
            availableComputers++;
        } else {
            // The customer has not been assigned any computer and is already marked as unsatisfied.
            unsatisfiedCount++;
        }
    }

    return unsatisfiedCount;
}
/*
Sample Input 1:
2
2 2
1 2 2 1
3 2 
1 3 2 1 2 3
Sample Output 1:
0
1
*/


//88. TRANSFORM STRING
//unordered map                                                                            {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    int transform (string A, string B)
    {
        int n = A.length();
        int m = B.length();
        if(n != m){
            return -1;
        }
        
        unordered_map<char , int>mp;
        for(auto c : A){
            // mp[A[c]]++;                       //in case of for loop
            mp[c]++;
        }
        
        for(auto d : B){
            // mp[B[d]]--;                      //in case of for loop
            mp[d]--;
        }
        
        for(auto it : mp){
            if(it.second != 0){
                return -1;
            }
        }
        
        
        int i = n-1;
        int j = m-1;
        int count = 0;
        while(i >= 0){
            if(A[i] == B[j]){
                i--;
                j--;
            }else{
                count++;
                i--;
            }
        }
        return count;
    }
};
//frequency array / vector                                                                                   {T.C = O(N), S.C = O(1)}
class Solution
{
    public:
    int transform (string A, string B)
    {
        int n = A.length();
        int m = B.length();
        if(n != m){
            return -1;
        }
        
        vector<int>freq(256, 0);
        for(auto c : A){
            freq[c]++;
        }
        
        for(auto d : B){
            freq[d]--;
        }
        
        for(auto f : freq){
            if(f != 0){
                return -1;
            }
        }
        
        
        int i = n-1;
        int j = m-1;
        int count = 0;
        while(i >= 0){
            if(A[i] == B[j]){
                i--;
                j--;
            }else{
                count++;
                i--;
            }
        }
        return count;
    }
};
/*
Input:
A = "GeeksForGeeks"
B = "ForGeeksGeeks"
Output: 3
Explanation: The conversion can take
place in 3 operations:
Pick 'r' and place it at the front.
A = "rGeeksFoGeeks"
Pick 'o' and place it at the front.
A = "orGeeksFGeeks"
Pick 'F' and place it at the front.
A = "ForGeeksGeeks"
*/


//89. ISOMORPHIC STRING                                                        {T.C = O(N), S.C = O(N)}
class Solution 
{
public:
    // Function to check if two strings are isomorphic.
    bool areIsomorphic(string s, string t)
    {
        if(s.length() != t.length()){
            return false;
        }
        // Create an unordered map to store character mappings from 's' to 't'.
        unordered_map<char, char> charMappingMap;
        // Create an unordered set to keep track of characters that have been used as replacements in 't'.
        unordered_set<char> usedReplacements;

        // Iterate through each character in 's' and its corresponding character in 't'.
        for (int i = 0; i < s.length(); i++) {
            char original = s[i];      // Get the current character from 's'.
            char replacement = t[i];   // Get the corresponding character from 't'.

            // If 'original' is not already present in the map.
            if (charMappingMap.find(original) == charMappingMap.end()) {
                // Check if the 'replacement' character is also not present in the map and not already used.
                // If so, add the mapping 'original' -> 'replacement' to the map and mark 'replacement' as used.
                // Else, return false, as two different characters from 's' cannot be mapped to the same character in 't'.
                if (usedReplacements.find(replacement) == usedReplacements.end()) {
                    charMappingMap[original] = replacement;
                    usedReplacements.insert(replacement);
                }
                else
                    return false;
            }
            else {
                // 'original' is already present in the map.
                char mappedCharacter = charMappingMap[original];
                // If the mapped character is not equal to the 'replacement', return false.
                // This means the current character in 's' is mapped to a different character in 't'.
                if (mappedCharacter != replacement)
                    return false;
            }
        }
        // If all conditions are satisfied, the strings are isomorphic, so return true.
        return true;
    }
};
/*
Input:
str1 = aab
str2 = xxy
Output: 1
Explanation: There are two different
charactersin aab and xxy, i.e a and b
with frequency 2and 1 respectively.
*/


//90. RECURSIVELY PRINT ALL SENTENCES THAT CAN BE FORMED FROM LIST OF WORD LISTS                             {T.C = O(M^N), S.C = O(M^N)}
class Solution{
    public:
    void solve(vector<vector<string>>&list, vector<vector<string>>&ans, vector<string>&curr, int i){
        //base case
        if(i == list.size()){
            ans.push_back(curr);
            return;
        }
        
        for(auto it : list[i]){                         //traverse each string of list
            curr.push_back(it);
            solve(list, ans, curr, i+1);
            curr.pop_back();
        }
    }
    vector<vector<string>> sentences(vector<vector<string>>&list){
        vector<vector<string>>ans;                    //store acutal ans
        vector<string>curr;                           //store curr string
        solve(list, ans, curr, 0);                     //i = 0
        return ans;
    }
};
/*
L = {{"you", "we"},
     {"have", "are"},
Output: 
{{you have}
{you are}
{we have}
{we are}}
Explanation:
Consider every every word from the list and form
sentences with every other words, taking one word from a list .
*/


/*-----------------------------------------------------   THE END    -----------------------------------------------------------------------*/