//MATRIX

#include<bits/stdc++.h>
using namespace  std;

//37. SPIRALLY TRAVERSAL OF MATRIX                                               {T.C = O(N), S.C = O(N)}
class Solution
{   
    public: 
    //Function to return a list of integers denoting spiral traversal of matrix.
    vector<int> spirallyTraverse(vector<vector<int> > matrix, int r, int c) 
    {
        vector<int>ans;
        
        int left = 0;
        int right = c-1;                                   //r = mat.size() , c = mat[0].size();
        int top = 0;
        int bottom = r-1;
        
        //flow of traversal == right->bottom->left->top
        while(left <= right && top <= bottom){
            //right
            for(int i = left ; i <= right ; i++ ){
                ans.push_back(matrix[top][i]);
            }
            top++;
            //bottom
            for(int i = top ; i <= bottom ; i++){
                ans.push_back(matrix[i][right]);
            }
            right--;
            //left
            if(top <= bottom){
                for(int i = right ; i >= left ; i--){
                    ans.push_back(matrix[bottom][i]);
                }
                bottom--;
                
            }
            //top
            if(left <= right){
                for(int i = bottom ; i >= top ; i--){
                    ans.push_back(matrix[i][left]);
                }
                left++;
            }
        }
        return ans;
    }
};
/*
Input:
r = 4, c = 4
matrix[][] = {{1, 2, 3, 4},
           {5, 6, 7, 8},
           {9, 10, 11, 12},
           {13, 14, 15,16}}
Output: 
1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10
*/


//38. SEARCH ELEMENT IN A 2D MATRIX                                        {T.C = O(LOG(N*M)), S.C = O(1)}
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        int col = matrix[0].size();

        int s = 0;
        int e = row * col - 1;

        int mid = s + (e-s)/2;                   //mid = (s+e)/2

        while(s <= e){
            int element = matrix[mid/col][mid%col];               //mid/col == row , mid%col == column
            if(element == target){
                return 1;
            }
            else if(element < target){
                s = mid + 1;
            }
            else{
                e = mid - 1;
            }
            mid = s + (e - s)/2;
        }
        return 0;
    }
};
/*
Input: matrix = [[1,3,5,7],
                 [10,11,16,20],
                 [23,30,34,60]], 
                target = 3
Output: true
*/


//39. MEDIAN IN A ROW WISE SORTED MATRIX
#include<bits/stdc++.h>
using namespace std;

class Solution{   
public:
    int median(vector<vector<int>> &m, int r, int c){
        int mini = INT_MAX;
        int maxi = INT_MIN;
        
        for(int i = 0 ; i < r ; i++){
            //finding the minimum element
            if(m[i][0] < mini){
                mini = m[i][0];
            }
            //finding the maximum element
            if(m[i][c-1] > maxi){
                maxi = m[i][c-1];
            }
        }
        int desired = (r*c + 1)/2;                            //odd
        while(mini < maxi){
            int mid = mini + (maxi-mini)/2;
            int place = 0;
            
            //find count of elements smaller then mid
            for(int i = 0 ; i < r ; i++){
                place += upper_bound(m[i].begin(), m[i].end(), mid) - m[i].begin();
            }
            if(place < desired){
                mini = mid+1;
            }
            else{
                maxi = mid;
            }
        }
        return mini;
    }
};
/*
Input:
R = 3, C = 3
M = [[1, 3, 5], 
     [2, 6, 9], 
     [3, 6, 9]]
Output: 5
Explanation: Sorting matrix elements gives 
us {1,2,3,3,5,6,6,9,9}. Hence, 5 is median. 
*/


//40. ROW WITH MAX 1'S
//BRUTE FORCE APPROACH                                                       {T.C = O(N*M), S.C = O(1)}
class Solution{
public:
	int rowWithMax1s(vector<vector<int> > arr, int n, int m) {
	    int maxCount = 0;                        
	    int maxRow = -1;                           //row index
	    
	    for(int i = 0 ; i < n ; i++){
	        int count = 0;                         //count of 1's
	        for(int j = 0 ; j < m ; j++){
	            if(arr[i][j] == 1){
	                count++;
	            }
	        }
    	    if(count > maxCount){
    	        maxCount = count;
    	        maxRow = i;
    	    }
	    }
        return maxRow;  
	}
};

//OPTIMIZED APPROACH (BINARY SEARCH)                                                     {T.C = O(N*M) , S.C = O(1)}
class Solution{
public:
	int rowWithMax1s(vector<vector<int> > arr, int n, int m) {
	    int maxRow = -1;
	    int maxCount = 0;
	    int j = m-1;
	    
	    //traverse each row
	    for(int i = 0 ; i < n ; i++){
	        //move left until we find the last occurance of 1 in the current row
    	    while(j >= 0 && arr[i][j] == 1){
    	        j--;
    	    }
    	    //check if the count of 1's in this row is higher than the current maximum
    	    if(m-1-j > maxCount){
    	        maxCount = m-1-j;
    	        maxRow = i;
    	    }
	    }
	    return maxRow;
	}
};
/*
Input: 
N = 4 , M = 4
Arr[][] = {{0, 1, 1, 1},
           {0, 0, 1, 1},
           {1, 1, 1, 1},
           {0, 0, 0, 0}}
Output: 2
Explanation: Row 2 contains 4 1's (0-based
indexing).
*/


//41. SORTED MATRIX                                                                       {T.C = O(N^2 LOGN), S.C = O(N^2)}
class Solution {
  public:
    vector<vector<int>> sortedMatrix(int n, vector<vector<int>> mat) {
        vector<int>ans;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ;j++){
                ans.push_back(mat[i][j]);
            }
        }
        sort(ans.begin(), ans.end());
        //till now we got a single sorted array
        
        //creating a 2d matrix and push again in mat
        int index = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                mat[i][j] = ans[index];
                index++;
            }
        }
        return mat;
    }
};
/*
Input:
N=4
Mat=[[10,20,30,40],
[15,25,35,45] 
[27,29,37,48] 
[32,33,39,50]]
Output:
10 15 20 25 
27 29 30 32
33 35 37 39
40 45 48 50
Explanation:
Sorting the matrix gives this result.
*/


//42. MAXIMUM SIZE RECTANGLE                                                                       {T.C = O(N*M), S.C = O(M)}
class Solution {
public:
    vector<int>nextSmallerElement(vector<int>arr , int n){
        stack<int>s;
        s.push(-1);
        vector<int>ans(n);

        for(int i = n-1 ; i >= 0 ; i--){
            int curr = arr[i];
            while(s.top() != -1 && arr[s.top()] >= curr){
                s.pop();
            }
            //ans is stack's top
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }
    vector<int>prevSmallerElement(vector<int>arr , int n){
        stack<int>s;
        s.push(-1);
        vector<int>ans(n);

        for(int i = 0 ; i < n ; i++){
            int curr = arr[i];
            while(s.top() != -1 && arr[s.top()] >= curr){
                s.pop();
            }
            //ans is stack's top
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();

        vector<int>next(n);
        next = nextSmallerElement(heights , n);

        vector<int>prev(n);
        prev = prevSmallerElement(heights , n);

        int area = INT_MIN;
        for(int i = 0 ; i < n ; i++){
            int l = heights[i];
            
            if(next[i] == -1){
                next[i] = n;
            }
            int b = next[i] - prev[i] - 1;

            int newArea = l * b;
            area = max(area , newArea);
            
        }
        return area;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int maxi = 0;
        vector<int>histogram(matrix[0].size(), 0);

        for(int i =  0 ; i < matrix.size() ; i++){
            //to create histogram array
            for(int j = 0 ; j < histogram.size() ; j++){
                if(matrix[i][j] == '1'){
                    histogram[j]++;
                }
                else{
                    histogram[j] = 0;
                }
            }
            maxi = max(maxi, largestRectangleArea(histogram));
        }
        return maxi;
    }
};
//copied
/*
class Solution{
  private:
    vector<int> nextSmallerElement(int *arr, int n){
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);

        for(int i=n-1;i>=0;i--){
            int curr = arr[i];
            while(s.top() != -1 && arr[s.top()] >= curr){
                s.pop();
        }
        ans[i] = s.top();
        s.push(i);
    }
    return ans;
    }
    
    vector<int> prevSmallerElement(int *arr, int n){
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);

        for(int i=0;i<n;i++){
            int curr = arr[i];
            while(s.top() != -1 && arr[s.top()] >= curr){
                s.pop();
        }
        ans[i] = s.top();
        s.push(i);
    }
    return ans;
    }
    
    int largestRectangleArea(int *heights, int n) {
        //int n = heights.size();

        vector<int> next(n);
        next = nextSmallerElement(heights, n);

        vector<int> prev(n);
        prev = prevSmallerElement(heights, n);

        int area = INT_MIN;
        for(int i=0;i<n;i++){
            int l = heights[i];
            if(next[i] == -1){
                next[i] = n;
            }
            int b = next[i] - prev[i] -1;
            
            int newArea = l*b;
            area = max(area, newArea);
        }
        return area;
    }
  public:
    int maxArea(int M[MAX][MAX], int n, int m) {
        int area = largestRectangleArea(M[0], m);
        
        for(int i=1;i<n;i++){
            for(int j=0;j<m;j++){
                if(M[i][j] != 0)
                  M[i][j] = M[i][j] + M[i-1][j];
                else
                  M[i][j] = 0;
            }
            area = max(area, largestRectangleArea(M[i], m));
        }
        return area;
    }
};
*/
/*
Input: matrix = [["1","0","1","0","0"],
                 ["1","0","1","1","1"],
                 ["1","1","1","1","1"],
                 ["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
*/


//43. FIND SPECIFIC PAIR IN MATRIX
int findMaxValue(vector<vector<int>>& mat, int n) {
    vector<vector<int>> compute(n, vector<int>(n, 0));
    compute[n-1][n-1] = mat[n-1][n-1];  // Last row, last column

    // Traverse right to left and bottom to top
    for (int i = n - 2; i >= 0; i--) {
        compute[n-1][i] = max(compute[n-1][i+1], mat[n-1][i]);
        compute[i][n-1] = max(compute[i+1][n-1], mat[i][n-1]);
    }

    // Traverse bottom to top and right to left
    for (int j = n - 2; j >= 0; j--) {
        // Traverse matrix diagonally from top-left to bottom-right
        for (int i = j - 1; i >= 0; i--) {
            compute[i][j] = max({compute[i+1][j], compute[i][j+1], mat[i][j]});
        }
    }
    
    int ans = INT_MIN;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            ans = max(ans, compute[i+1][j+1] - mat[i][j]);
        }
    }
    return ans;
}

//dp approach
int findMaxValue(vector<vector<int>>& mat, int n) {
	int ans=INT_MIN;
	vector<vector<int>>dp=mat;
	for(int i=0;i<n;i++) {
		dp[0][i]=(i>0?min(dp[0][i-1],mat[0][i]):mat[0][i]);
	}
	for(int i=1;i<n;i++) {
		int tmp=INT_MAX;
		for(int j=0;j<n;j++) {
			tmp=min(tmp,mat[i][j]);
			dp[i][j]=min(tmp,dp[i-1][j]);
		}
	}
	for(int i=1;i<n;i++) {
		for(int j=1;j<n;j++) {
			ans=max(ans,mat[i][j]-dp[i-1][j-1]);
		}
	}
	return ans;
}
/*
Sample Input 1:
2
3
1 2 3
4 5 6
7 8 9
3
-1 -2 -3
-4 -5 -6
-7 -8 -9
Sample Output 1:
8
-4
*/


//44. ROTATE IMAGE / ROTATE MATRIX BY 90 DEGREE IN CLOCKWISE DIRECTION         {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        //transpose of matrix
        for(int i = 0 ; i < n ; i++){
            for(int j = i ; j < n ; j++){
                swap(matrix[i][j], matrix[j][i]);
            }  
        }

        //reverse each row 
        for(int i = 0 ; i < n ; i++){
            int left = 0;
            int right = n-1;
            while(left < right){       //left <= right (middle element swap no need)   
                swap(matrix[i][left], matrix[i][right]);
                left++;
                right--;
            }
        }
    }
};
/*
Input: matrix = [[5,1,9,11]
                ,[2,4,8,10],
                 [13,3,6,7],
                 [15,14,12,16]]
Output: [[15,13,2,5]
       ,[14,3,4,1],
        [12,6,8,9],
        [16,7,10,11]]
*/


//45. KTH SMALLEST ELEMENT IN A MATRIX                                      {T.C = O(N^2 + NLOGK), S.C = O(N^2)}

//BRUTE FORCE

#define MAX 1000
int kthSmallest(int mat[MAX][MAX], int n, int k)
{
    vector<int>newArr;
    
    //2d matrix into single vector;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            newArr.push_back(mat[i][j]);
        }
    }
    
    //create max heap finding smallest element
    priority_queue<int>pq;
    
    //push k elements into max heap
    for(int i = 0 ; i < k ; i++){
        pq.push(newArr[i]);
    }
    
    //for rest of elements
    for(int i = k ; i < newArr.size(); i++){
        if(newArr[i] < pq.top()){
            pq.pop();
            pq.push(newArr[i]);
        }
    }
    
    int ans = pq.top();
    return ans;
}

//BRUTE FORCE (SIMPLE)                                                         {T.C = O(N^2LOGK) , S.C = O(K)}
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int> pq; //max heap
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size(); j++){
                pq.push(matrix[i][j]);
                if (pq.size() > k){
                    pq.pop();        
                }
                
            }
        }
        return pq.top();
    }
};
//OPTIMIZED APPROACH (UPPERBOUND)                                           {T.C = O(K*LOGN), S.C = O(1)}
int kthSmallest(int mat[MAX][MAX], int n, int k)
{
    int low = mat[0][0];
    int high = mat[n-1][n-1];
    
    while(low < high){
        int mid = low + (high-low)/2;
        int count = 0;
        
        // Iterate through the matrix and count elements less than or equal to mid
        for(int i = 0 ; i < n ; i++){
            // Convert each row into a 1D array by taking the address of the first element
            count += std::upper_bound(&mat[i][0], &mat[i][n], mid) - &mat[i][0];
        }
        
        if(count < k){
            low = mid + 1;
        }
        else{
            high = mid;
        }
    }
    return low;
}
/*
Input:
N = 4
mat[][] =     {{10, 20, 30, 40}
                   {15, 25, 35, 45}
                   {24, 29, 37, 48}
                   {32, 33, 39, 50}}
K = 7
Output: 30
Explanation: 30 is the 7th smallest element.
*/


//46. COMMON ELEMENT PRESENT IN ALL ROW OF MATRIX                            {T.C = O(M+N*M+K) , S.C = O(M)}
#include<unordered_map>
vector<int> findCommonElements(vector<vector<int>> &mat)
{
    int m = mat[0].size();               //column size
    int n = mat.size();                  //row size

    vector<int>ans;
    unordered_map<int, int>mp;                                               //T.C = O(M)
    //push 0th row elements in map and assign value 1
    for(int i = 0 ; i < m ; i++){
        mp[mat[0][i]] = 1;
    }

    //search on anothers row                                                //T.C = O(N*M)
    for(int i = 1 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            if(mp[mat[i][j]] == i){
                mp[mat[i][j]] = i+1;
            }
        }
    }

    //element push in vector
    /*
    for(auto itr = mp.begin(); itr != mp.end() ; itr++){
        if(itr->second == n){
            ans.push_back(itr->first);
        }
    } (or)
    */
    for(auto itr : mp){                                                   //T.C = O(K) (searching in constant time k elements searching taking o(k times))
        if(itr.second == n){
            ans.push_back(itr.first);
        }
    }
    return ans;
}
/*
Sample Input 1 :
2
3 4
1 4 5 6
3 4 5 6
5 6 7 2
3 2
4 6 
6 4
2 6
Sample Output 1 :
5 6
6
*/


/*------------------------------------        THE END      -------------------------------------------------------------*/