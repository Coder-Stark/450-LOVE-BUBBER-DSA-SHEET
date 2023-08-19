//STACKS AND QUEUES
#include<bits/stdc++.h>
using namespace std;


//163. IMPLEMENT STACK FROM SCRATCH                                                                  {T.C = O(1) , S.C = O(N)}
class Stack{
public:
    int *arr;
    int size;
    int top;

    //creatng stack
    Stack(int size){
        arr = new int[size];
        this->size = size;
        top = -1;
    }

    //push
    void push(int element){
        if(top == size-1){
            cout<<"Stack is overflow"<<endl;
            return;
        }
        top++;
        arr[top] = element;
    }

    //pop
    void pop(){
        if(top == -1){
            cout<<"No element to pop"<<endl;
        }
        top--;
    }

    //top/peek
    int peek(){
        if(top == -1){
            cout<<"No element in stack "<<endl;
        }
        return arr[top];
    }

    //empty
    bool empty(){
        if(top == -1){
            return true;
        }
        return false;
    }
};
/*
int main(){
    
    Stack st(4);
    
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);

    cout<<st.peek()<<endl;
    st.pop();

    cout<<st.peek()<<endl;
    st.pop();

    cout<<st.peek()<<endl;
    st.pop();

    cout<<st.peek()<<endl;
    st.pop();

    cout<<st.empty()<<endl;

    return 0;
}
*/
/*
output
4
3
2
1
1
*/


//164. IMPLEMENT QUEUE FROM SCRATCH 
class Queue{
public:
    int *arr;
    int size;
    int front;
    int rear;

    //creating queue
    Queue(int size){
        arr = new int[size];
        this->size = size;
        front = rear = -1;
    }

    //Enqueue / push
    void enqueue(int element){
        if(rear == size-1){
            cout<<"Queue is overflow"<<endl;
            return;
        }
        rear++;
        arr[rear] = element;

        //inserting 1st element only
        if(front == -1){
            front++;
        }
    }

    //Dequeue / pop
    void dequeue(){
        //check for empty
        if(front == -1 || front > rear){
            cout<<"Queue is empty"<<endl;
            return;
        }

        front++;
    }

    //Peek / top
    int peek(){
        //check of empty
        if(front == -1 || front > rear){
            cout<<"Queue is empty"<<endl;
            return -1;
        }

        return arr[front];
    }

    //Empty
    bool empty(){
        //check of empty
        if(front == -1 || front > rear){
            cout<<"Queue is empty"<<endl;
            return true;
        }
        return false;
    }
};

int main(){
    
    Queue q(4);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);

    cout<<q.peek()<<endl;
    q.dequeue();

    cout<<q.peek()<<endl;
    q.dequeue();

    cout<<q.peek()<<endl;
    q.dequeue();

    cout<<q.peek()<<endl;
    q.dequeue();

    cout<<q.empty()<<endl;

    return 0;
}
/*
output
1
2
3
4
Queue is empty
1
*/


//165. IMPLEMENT TWO STACKS IN AN ARRAY                                           {T.C = O(1), S.C = O(1)}
//1st stack push or pop from beginning and , 2nd stack is push or pop from end
class twoStacks
{
    int *arr;
    int size;
    int top1, top2;
    public:
    
    twoStacks(int n=100)
    {
        size = n; 
        arr = new int[n]; 
        top1 = -1; 
        top2 = size;
    }
 
    //Function to push an integer into the stack1.
    void push1(int x)
    {
        top1++;
        arr[top1] = x;
    }
    
    //Function to push an integer into the stack2.
    void push2(int x)
    {
       top2--;
       arr[top2] = x;
    }
    
    //Function to remove an element from top of the stack1.
    int pop1()
    {
        if(top1 == -1){
            return -1;
        }
        return arr[top1--];
    }
    
    //Function to remove an element from top of the stack2.
    int pop2()
    {
       if(top2 == size){
           return -1;
       }
       return arr[top2++];
    }
};
/*
Input:
push1(2)
push1(3)
push2(4)
pop1()
pop2()
pop2()
Output:
3 4 -1
Explanation:
push1(2) the stack1 will be {2}
push1(3) the stack1 will be {2,3}
push2(4) the stack2 will be {4}
pop1()   the poped element will be 3 from stack1 and stack1 will be {2}
pop2()   the poped element will be 4 from stack2 and now stack2 is empty
pop2()   the stack2 is now empty hence returned -1.
*/



//166a. FIND THE MIDDLE ELEMENT OF A STACK                                                               {T.C = O(1), S.C = O(1)}
//USING DOUBLY LINKED LIST
class Node{
public:
    int data;
    Node* next;
    Node* prev;
    
    Node(int data){
        this->data = data;
        next = NULL;
        prev = NULL;
    }
};

Node* dummy = new Node(-1);
Node* head = dummy;
Node* mid = dummy;
int cnt = 0;

void push(int x){
    Node* curr = new Node(x);
    curr->prev = NULL;
    curr->next = head;       //connect curr to dummy
    cnt++;
    
    head->prev = curr;       //connect dummy to curr
    head = curr;
    if(cnt == 1){            //1st node insert
        mid = curr; 
    }else if(cnt % 2 == 0){  //push (even = prev , odd = no operation)
        mid = mid->prev;
    }
}
int pop(){
    if(cnt == 0){
        cout<<"Stack is empty"<<endl;
        return -1;
    }
    Node* temp = head;
    int x = head->data;
    head = head->next;
    if(head != NULL){
        head->prev = NULL;
    }
    cnt--;
    if(cnt & 1){            //pop (even = no operation , odd = next)
        mid = mid->next;
    }
    free(temp);
    return x;
}
int middle(){
    if(cnt == 0){
        cout<<"Stack is empty"<<endl;
        return -1;
    }
    return mid->data;
}

void printData(){
    Node* curr = head;
    if(cnt == 0){
        cout<<"Stack is empty"<<endl;
        return;
    }
    for(int i = 0 ; i < cnt ; i++){
        cout<<curr->data<<" ";
        curr = curr->next;
    }
    cout<<endl;
}

int main(){
    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    
    printData();
    cout<<"Middle is -> "<<middle()<<endl;
    
    cout<<"Deleted Element is -> "<<pop()<<endl;
    printData();
    cout<<"Middle is -> "<<middle()<<endl;
}
/*
5 4 3 2 1 
Middle is -> 3
Deleted Element is -> 5
4 3 2 1 
Middle is -> 3
*/

//166b. DELETE THE MIDDLE NODE                                                                        {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    void solve(stack<int>&s,int count , int size){
       //base case
       if(count == size/2){
          s.pop();
          return;
       }
    
       //if count is not in middle then it pop element and store the elements
       int num = s.top();
       s.pop();
    
       //recursive call
       solve(s , count+1 , size);
       s.push(num);                               //push back the store's element to stack
    }
    void deleteMid(stack<int>&s, int sizeOfStack)
    {
        int count = 0;
        solve(s,count,sizeOfStack);
    }
};
/*
Input: 
Stack = {10, 20, 30, 40, 50}
Output:
ModifiedStack = {10, 20, 40, 50}
Explanation:
If you print the stack the bottom-most element will be 10 and the top-most element will be 50. Middle element will be element at 
index 3 from bottom, which is 30. Deleting 30, stack will look like {10 20 40 50}.
*/


//167. N STACK IN AN ARRAY                                                      (T.C == O(N) , S.C == O(N + S)
class NStack
{
    int *arr;
    int *top;
    int *next;
    int n , s;
    int freespot;
public:
    // Initialize your data structure.
    //arr(actual arr), next(stores position) , freespot(store temp ans)
    NStack(int N, int S)
    {
        n = N;         //no. of stacks
        s = S;         //size of array

        arr = new int[s];
        top = new int[n];
        next = new int[s];

        //top initialize with -1
        for(int i = 0 ; i < n ; i++){
            top[i] = -1;
        }

        //next initialize
        for(int i = 0 ; i < s; i++){
            next[i] = i+1;
        }
        //update last index value to -1
        next[s-1] = -1;

        //freespot initialize
        freespot = 0;
    }

    // Pushes 'X' into the Mth stack. Returns true if it gets pushed into the stack, and false otherwise.
    bool push(int x, int m)
    {
        //check for overflow
        if(freespot == -1){
            return false;
        }
        //find index
        int index = freespot;

        //update freespot
        freespot = next[index];

        //insert element into array
        arr[index] = x;

        //update next
        next[index] = top[m-1];

        //update top
        top[m-1] = index;

        return true;
    }

    // Pops top element from Mth Stack. Returns -1 if the stack is empty, otherwise returns the popped element.
    int pop(int m)
    {
        //reverse of push exactly
        //check underflow
        if(top[m-1] == -1){
            return -1;
        }

        int index = top[m-1];

        top[m-1] = next[index];

        next[index] = freespot;

        freespot = index;

        return arr[index];
    }
};
/*
Sample Input 1 :
3 6 5           query(1 == push, 2 == pop)
1 10 1          //push(10, 1)    //push 10 in 1st stack
1 20 1
1 30 2
2 1             //pop(1)         //pop from 1st stack
2 2
Sample Output 1 :
True 
True
True
20
30
*/


//168. CHECK THE EXPRESSION HAS VALID OR BALANCED PARANTHESIS OR NOT                                                            {T.C = O(N), S.C = O(N)}
#include<stack>
class Solution
{
    public:
    //Function to check if brackets are balanced or not.
    bool ispar(string x)
    {
        stack<char>st;
        for(int i = 0 ; i < x.size() ; i++){
            if(x[i] == '[' || x[i] == '{' || x[i] == '('){
                st.push(x[i]);
            }
            else{
                if(!st.empty()){
                    if((st.top() == '[' && x[i] == ']')|| (st.top() == '{' && x[i] == '}') || (st.top() == '(' && x[i] == ')')){
                        st.pop();
                    }
                    else{
                        return false;
                    }
                }else{
                    return false;
                }
            }
        }
        if(st.empty()){
            return true;
        }
        return false;
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


//169. REVERSE A STRING USING STACK                                                                         {T.C = O(N), S.C = O(N)}
char* reverse(char *s, int n)
{
    stack<char>st;
    
    char* ans = new char[n+1];
    
    for(int i = 0 ; i < n ; i++){
        st.push(s[i]);
    }
    
    for(int i = 0 ; i < n ; i++){
        ans[i] = st.top();
        st.pop();
    }
    return ans;
}
/*
Input: S="GeeksforGeeks"
Output: skeeGrofskeeG
*/


//170. SPECIAL STACK / DESIGN A STACK THAT SUPPORTS GETMIN() IN O(1) TIME AND O(1) EXTRA SPACE       {T.C = O(1) , S.C = O(1)}
//APPROACH 1
int mini;
void push(stack<int>& s, int curr){
	if(s.empty()){
	    s.push(curr);
	    mini = curr;
	}else{
	    if(curr < mini){
	        int val = 2*curr - mini;
	        s.push(val);
	        mini = curr;
	    }else{
	        s.push(curr);
	    }
	}
}

bool isFull(stack<int>& s,int n){
	if(s.size() == n){
	    return true;
	}
	return false;
}

bool isEmpty(stack<int>& s){
	return s.empty();
}

int pop(stack<int>& s){
	if(s.empty()){
	    return -1;
	}else{
	    int curr = s.top();
	    s.pop();
	    if(curr > mini){
	        return curr;
	    }else{
	        int prevMini = mini;
	        int val = 2*mini - curr;
	        mini = val;
	        
	        return prevMini;
	    }
	}
}

int getMin(stack<int>& s){
	if(s.empty()){
	    return -1;
	}
	return mini;
}

//APPROACH 2                                                                                   {T.C = O(1) & GETIN(T.C = O(N)) , S.C = O(1)}
void push(stack<int>& s, int a){
	s.push(a);
}

bool isFull(stack<int>& s,int n){
	if(s.size() == n)
	    return true;
	return false;
}

bool isEmpty(stack<int>& s){
	if(s.size()==0)
	    return true;
	return false;
}

int pop(stack<int>& s){
	int t = s.top();
	s.pop();
	return t;
}

int getMin(stack<int>& s){
    int ans = 1e5;
	while(s.size()!=0)
	{
	    ans = min(ans,s.top());
	    s.pop();
	}
	return ans;
	
}
/*
Input:
Stack: 18 19 29 15 16
Output: 15
Explanation:
The minimum element of the stack is 15.
*/


//171. NEXT GREATER ELEMENT
//BRUTE FORCE                                                                                     {T.C = O(N^2), S.C = O(N)}
class Solution
{
    public:
    vector<long long> nextLargerElement(vector<long long> arr, int n){
        
        vector<long long>ans;
        for(int i = 0 ; i < n ; i++){
            bool found = false;
            for(int j = i+1 ; j < n ; j++){
                if(arr[j] > arr[i]){
                    ans.push_back(arr[j]);
                    found = true;
                    break;
                }
            }
            if(!found){
                ans.push_back(-1);
            }
        }
        return ans;
    }
};

//OPTIMIZED APPROACH                                                                          {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    vector<long long> nextLargerElement(vector<long long> arr, int n){
        stack<long long>st;
        st.push(-1);
        
        vector<long long> ans(n, -1);
        
        for(int i = n-1 ; i >= 0 ; i--){
            while(!st.empty() && st.top() != -1 && arr[i] >= st.top()){
                st.pop();
            }
            ans[i] = st.top();
            st.push(arr[i]);                          //add curr element of array to stack
        }
        return ans;
    }
};
/*
Input: 
N = 4, arr[] = [1 3 2 4]
Output:
3 4 4 -1
Explanation:
In the array, the next larger element 
to 1 is 3 , 3 is 4 , 2 is 4 and for 4 ? 
since it doesn't exist, it is -1.
*/


//172. CELEBRITY PROBLEM                                                                             {T.C = O(N), S.C = O(N)}
class Solution 
{
    private:
    bool knows(vector<vector<int> >& M,int a , int b, int n){
        if(M[a][b] == 1){
            return true;
        }
        else{
            return false;
        }
    }
    public:
    int celebrity(vector<vector<int> >& M, int n) 
    {
        stack<int>s;
        
        //put all elements in stack
        for(int i = 0 ; i < n ; i++){
            s.push(i);
        }
        
        //get 2 person and compare them
        while(s.size() > 1){
            int a = s.top();
            s.pop();
            
            int b = s.top();
            s.pop();
            
            if(knows(M,a,b,n)){           //a knows b , so a is not celebrity
                s.push(b);
            }
            else{                        //b knows a , so b is not celebrity
                s.push(a);
            }
        }
        
        //(potential candidate left) single element left verify it , as a celebraty 
        int validCandidate = s.top();
        
        //row check
        bool rowCheck = false;
        int zeroCount = 0;
        for(int i = 0 ; i < n ; i++){
            if(M[validCandidate][i] == 0){            //checking row
                zeroCount++;
            }
        }
        
        //all zero
        if(zeroCount == n){
            rowCheck = true;
        }
        
        //column check
        bool colCheck = false;
        int oneCount = 0;
        for(int i = 0 ; i < n ; i++){
            if(M[i][validCandidate] == 1){             //checking col
                oneCount++;
            }
        }
        
        //allone
        if(oneCount == n-1 ){           //except digonal all 1
            colCheck = true;
        }
        
        
        if(rowCheck == true && colCheck == true){
            return validCandidate;
        }
        else{
            return -1;
        }
    }
};
/*
Input:
N = 3
M[][] = {{0 1 0},
         {0 0 0}, 
         {0 1 0}}
Output: 1
Explanation: 0th and 2nd person both
know 1. Therefore, 1 is the celebrity. 
*/


//173. ARITHMETIC EXPRESSION EVALUATION
/*
    infix notation:  A + B
    Polish notation (prefix notation): +AB
    Reverse Polish notation (postfix notation): AB+

    There are 3 levels of precedence for 5 binary operators as given below:
        Highest: Exponentiation (^)
        Next highest: Multiplication (*) and division (/)
        Lowest: Addition (+) and Subtraction (-)
*/


//174. EVALUATION OF POSTFIX EXPRESSION                                                                       {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    //Function to evaluate a postfix expression.
    int evaluatePostfix(string s)
    {
        stack<int>st;
        
        for(int i = 0 ; i < s.length() ; i++){
            if(s[i] >= '0' && s[i] <= '9'){                 //operands
                st.push(s[i]-'0');
            }else{                                          //operator
                int op2 = st.top();                         //1st pop element is op2
                st.pop();
                int op1 = st.top();                        //2nd pop element is op1
                st.pop();
                
                switch(s[i]){
                    case '+':
                        st.push(op1 + op2);
                        break;
                        
                    case '-':
                        st.push(op1 - op2);
                        break;
                        
                    case '*':
                        st.push(op1 * op2);
                        break;
                    
                    case '/':
                        st.push(op1 / op2);
                        break;
                }
            }
        }
        return st.top();
    }
};
/*
Input: S = "231*+9-"
Output: -4
Explanation:
After solving the given expression, 
we have -4 as result.
*/


//175. INSERT AN ELEMENT AT THE BOTTOM                                                                      {T.C = O(N), S.C = O(N)}
class Solution{
public:
    void solve(stack<int>&st, int x){
        //base case
        if(st.size() == 0){
            st.push(x);
            return ;
        }
        
        int val = st.top();
        st.pop();
        
        //recursive call
        solve(st, x);
        st.push(val);                      //push all elements
    }
    stack<int> insertAtBottom(stack<int> St,int X){
        solve(St, X);
        return St;
    }
};
/*
Input:
N = 5
X = 2
St = {4,3,2,1,8}
Output:
{2,4,3,2,1,8}
Explanation:
After insertion of 2, the final stack will be {2,4,3,2,1,8}.
*/


//176. REVERSE A STACK                                                                   {T.C = O(N^2), S.C = O(1)}
class Solution{
public:
    void insertAtBottom(stack<int>&st, int x){
        //base case
        if(st.empty()){
            st.push(x);
            return;
        }
        
        int num = st.top();
        st.pop();
        
        //recursive call
        insertAtBottom(st, x);
        st.push(num);
    }
    void Reverse(stack<int> &st){
        //base case
        if(st.empty()){
            return;
        }
        
        int num = st.top();
        st.pop();
        
        //recursive call
        Reverse(st);
        insertAtBottom(st, num);
    }
};
/*
Input:
St = {3,2,1,7,6}
Output:
{6,7,1,2,3}
Explanation:
Input stack after reversing will look like the stack in the output.
*/


class SortedStack{
public:
	stack<int> s;
	void sort();
};
//177. SORT A STACK                                                                                {T.C = O(N^2), S.C = O(N)}
void insertAtBottom(stack<int>&s, int x){
    if(s.empty() || x > s.top()){
        s.push(x);
        return;
    }
    
    int num = s.top();
    s.pop();
    insertAtBottom(s, x);
    s.push(num);
}
void SortedStack :: sort()
{
    if(s.empty()){
        return;
    }
    
    int num = s.top();
    s.pop();
    
    //recursive call
    sort();                                                
    insertAtBottom(s, num);
}
/*
Input:
Stack: 11 2 32 3 41
Output: 41 32 11 3 2
*/


//178. MERGE OVERLAPPING INTERVALS                                                {T.C = O(NLOGN), S.C = O(N)}
vector<vector<int>> mergeIntervals(vector<vector<int>> intervals)
{
    vector<vector<int>>ans;                                  //store final merged intervals

    //base case
    if(intervals.size() == 0){
        return ans;
    }

    sort(intervals.begin(), intervals.end());
    vector<int>temp = intervals[0];                          //stores temporary answer
    for( auto i : intervals){
        if(i[0] <= temp[1]){
            temp[1] = max(temp[1], i[1]);
        }else{
            ans.push_back(temp);
            temp = i;
        }
    }
    ans.push_back(temp);

    return ans;
}
/*
Sample Input 2:
3
5
1 3 6 8 10
4 5 8 9 12
10
1 2 3 1 9 5 11 7 12 14
3 7 5 8 10 11 12 10 12 17
7
1 4 2 5 6 2 8
2 6 7 6 9 11 12
Sample Output 2:
1 5
6 9
10 12
1 12
14 17
1 12
*/


//179. MAXIMUM RECTANGULAR AREA IN A HISTOGRAM                                                                  {T.C = O(N), S.C = O(N)}
class Solution {
private:
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
public:
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
};
/*
Input:
N = 7
arr[] = {6,2,5,4,5,1,6}
Output: 12
Explanation: In this example the largest area would be 12 of height 4 and width 3. We can achieve this 
area by choosing 3rd, 4th and 5th bars.
*/


//180. VALID SUBSTRING                                                                             {T.C = O(N), S.C = O(M)}
class Solution {
  public:
    int findMaxLen(string s) {
        stack<int>st;
        int maxVal = 0;
        st.push(-1);
        for(int i = 0 ; i < s.length() ; i++){
            if(s[i] == '('){
                st.push(i);
            }else{
                st.pop();
                
                if(st.empty()){
                    st.push(i);
                }else{
                    maxVal = max(maxVal, i-st.top());
                }
            }
        }
        return maxVal;
    }
};


//181. EXPRESSION CONTAINS REDUNDANT BRACKET OR NOT                                                             {T.C = O(N), S.C = O(N)}
class Solution {
  public:
    int checkRedundancy(string s) {
        stack<char>st;
    
        for(int i = 0 ; i < s.length();i++){
            char ch = s[i];
            if(ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/'){
                st.push(ch);
            }
            else{
                if(ch == ')'){
                    bool isRedundant = true;
                    while(st.top() != '('){
                        char top = st.top();
                        if(top == '+' || top == '-' || top == '*' || top == '/'){
                            isRedundant = false;
                        }
                        st.pop();
                    }
                    if(isRedundant == true){
                        return true;
                    }
                    st.pop();
                }
            }
        }
        return false;
    }
};
/*
Input:
exp = (a+b+(c+d))
Output:
No
Explanation:
(a+b+(c+d)) doesn't have any redundant or multiple
brackets.
*/


class QueueStack{
private:
    queue<int> q1;
    queue<int> q2;
public:
    void push(int);
    int pop();
};
//182a. IMPLEMENT STACK USING 2 QUEUES                                                  {T.C = O(N), S.C = O(1)}
void QueueStack :: push(int x)
{
    q1.push(x);
    while(!q2.empty()){
        q1.push(q2.front());
        q2.pop();
    }
    swap(q1, q2);
}

int QueueStack :: pop()
{
    int ans;
    if(q2.empty()){
        ans = -1;
    }else{
        ans = q2.front();
        q2.pop();
    }
    return ans;
}

//182b. using 1 queue                                                                 {T.C = O(N), S.C = O(1)}
void QueueStack :: push(int x)
{
    q1.push(x);
    int sz = q1.size()-1;
    while(sz--){
        q1.push(q1.front());
        q1.pop();
    }
}
int QueueStack :: pop()
{
    int ans;
    if(q1.empty()){
        ans = -1;
    }else{
        ans = q1.front();
        q1.pop();
    }
    return ans;
}
/*
Input:
push(2)
pop()
pop()
push(3)
Output: 2 -1
*/


//183. IMPLEMENT STACK USING DEQUE                                                             {T.C = O(1), S.C = O(1)}
class Stack
{
    int sz;
    deque<int>dq;
public:
    // Initialize your data structure.
    Stack()
    {
        sz = 0;
    }

    // Pushes 'X' into the stack. Returns true if it gets pushed into the stack, and false otherwise.
    bool push(int x)
    {
        dq.push_back(x);
        sz++;
        return true;
    }

    // Pops top element from Stack. Returns -1 if the stack is empty, otherwise returns the popped element.
    int pop()
    {
        if(isEmpty()){
            return -1;
        }
        int element = dq.back();
        dq.pop_back();
        sz--;
    
        return element;
    }

    // Returns the topmost element of the stack. In case the stack is empty, it returns -1.
    int top()
    {
        if(isEmpty()){
            return -1;
        }
        return dq.back();
    }

    // Returns true if the stack is empty, otherwise false.
    bool isEmpty()
    {
        if(sz == 0){
            return true;
        }
        return false;
    }

    // Returns the number of elements currently present in the stack.
    int size()
    {
        return sz;
    }
};
/*
Sample Input 1 :
6
4
1 10
1 20
5
2
3
Sample Output 1 :
True 
True
True
2
20
10
*/


//184. STACK PERMUTATION                                                                  {T.C = O(N^2), S.C = O(N)}
class Solution{
public:
    int isStackPermutation(int N,vector<int> &a,vector<int> &b){
        stack<int>st;
        int i = 0; 
        int j = 0;
        
        while(i < N ){
            st.push(a[i]);
            while(j < N && !st.empty() && b[j] == st.top()){
                st.pop();
                j++;
            }
            i++;
        }
        return st.empty();
    }
};
/*
Input:
N = 3
A = {1,2,3}
B = {2,1,3}
Output:
1
Explanation:
1. push 1 from A to stack
2. push 2 from A to stack
3. pop 2 from stack to B
4. pop 1 from stack to B
5. push 3 from A to stack
6. pop 3 from stack to B
*/


class StackQueue{
private:   
    stack<int> s1;
    stack<int> s2;
public:
    void push(int);
    int pop();
};
//185. QUEUE USING 2 STACKS
void StackQueue :: push(int x)
{
    s1.push(x);
}

//Function to pop an element from queue by using 2 stacks.                                                          {T.C = O(N), S.C = O(1)}
int StackQueue :: pop()
{
    //if both stack are empty return -1;
    if(s1.empty() && s2.empty()){
        return -1;
    }
    
    //if 2nd stack is empty
    if(s2.empty()){
        while(!s1.empty()){
            int ele = s1.top();
            s2.push(ele);
            s1.pop();
        }
    }
    //pop from seconde stack 
    int element = s2.top();
    s2.pop();
    return element;
}
/*
Input:
5
1 2 1 3 2 1 4 2

Output: 
2 3

Explanation: 
In the first testcase
1 2 the queue will be {2}
1 3 the queue will be {2 3}
2   poped element will be 2 the queue 
    will be {3}
1 4 the queue will be {3 4}
2   poped element will be 3.
*/


//186. IMPLEMENT N OR K  QUEUE IN AN ARRAY                                                          {T.C = O(1) ,S.C = O(N+K)}
class kqueue{
    int n;
    int k ;
    int *arr;
    int *front;
    int *rear;
    int *next;
    int freeSpot;

public:
    kqueue(int n , int k){

        //initialization
        this->n = n;
        this->k = k;
        arr = new int[n];
        front = new int[k];
        rear = new int[k];

        for(int i = 0 ; i < k ; i++){
            front[i] = -1;
            rear[i] = -1;
        }

        next = new int[n];
        for(int i = 0 ; i < n ; i++){
            next[i] = i+1;
        }
        next[n-1] = -1;

        freeSpot = 0;
    }

    void enqueue(int data, int qn){
        
        //overflow
        if(freeSpot == -1){
            cout<<"No empty space to push element"<<endl;
            return;
        }

        //find first free index
        int index = freeSpot;

        //update free spot
        freeSpot = next[index];

        //check whether 1st element to insert
        if(front[qn-1] == -1){
            front[qn -1] = index;
        }
        else{
            //link new element to previous element
            next[rear[qn -1]] = index;
        }

        //update next
        next[index] = -1;

        //update rear
        rear[qn -1] = index;

        //push element
        arr[index] = data;
    }

    int dequeue(int qn){

        //underflow
        if(front[qn -1] == -1){
            cout<<"Queue is empty"<<endl;
            return -1;
        }

        //find index to pop
        int index = front[qn-1];

        //front move forward
        front[qn-1] = next[index];

        //free spot manage
        next[index] = freeSpot;
        freeSpot = index;
        
        return arr[index];
    }
};
int main(){
    
    kqueue q(10,3);
    q.enqueue(10,1);
    q.enqueue(15,1);
    q.enqueue(20,2);
    q.enqueue(25,1);

    cout<<q.dequeue(1)<<endl;
    cout<<q.dequeue(2)<<endl;
    cout<<q.dequeue(1)<<endl;
    cout<<q.dequeue(1)<<endl;
    cout<<q.dequeue(1)<<endl;
}
/*output
10
20
15
25
Queue is empty
-1
*/


//187. DESIGN A CIRCULAR QUEUE                                                                             {T.C = O(1), S.C = O(1)}
class MyCircularQueue {
    vector<int> q; // The array to hold the circular queue
    int front = 0, rear = 0, size = 0; // Indices and size
public:
    MyCircularQueue(int k) {
        q = vector<int>(k, -1); // Initialize the queue with -1
    }
    
    bool enQueue(int value) {
        if (size == q.size()) {
            return false; // Queue is full
        }
        if (size == 0) {
            front = rear = 0; // Set indices for the first element
        } else {
            rear = (rear + 1) % q.size(); // Increment rear and wrap around if needed
        }
        q[rear] = value; // Add the element to the queue
        size++;
        return true;
    }
    
    bool deQueue() {
        if (size == 0) {
            return false; // Queue is empty
        }
        q[front] = -1; // Remove the element by marking it as -1
        front = (front + 1) % q.size(); // Increment front and wrap around if needed
        size--;
        return true;
    }
    
    int Front() {
        if (size == 0) {
            return -1; // Queue is empty
        }
        return q[front]; // Return the front element
    }
    
    int Rear() {
        if (size == 0) {
            return -1; // Queue is empty
        }
        return q[rear]; // Return the rear element
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == q.size();
    }
};
/*
Input
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 3, true, true, true, 4]
*/


//188. LRU CACHE IMPLEMENTATION


//189. QUEUE REVERSAL                                                                                    {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    void reverse(queue<int>&q){
        if(q.empty()){
            return;
        }
        int x = q.front();
        q.pop();
        reverse(q);                 //recursive call
        q.push(x);
    }
    queue<int> rev(queue<int> q)
    {
        reverse(q);
        return q;
    }
};
/*
Input:
6
4 3 1 10 2 6
Output: 
6 2 10 1 3 4
Explanation: 
After reversing the given elements of the queue , the resultant queue will be 6 2 10 1 3 4.
*/


//190. REVERSE FIRST K ELEMENTS OF QUEUE                                                                              {T.C = O(N), S.C = O(K)}
queue<int> modifyQueue(queue<int> q, int k) {
    stack<int>s;
    //fetch 1st k elements from queue and put into stack
    for(int i = 0 ; i < k ; i++){
        int element = q.front();
        q.pop();
        s.push(element);
    }
    
    //fetch element from stack and put into queue
    while(!s.empty()){
        int element = s.top();
        s.pop();
        q.push(element);
    }
    
    //fetch n-k elements from queue and put again to queue
    int sz = q.size()-k;
    while(sz--){
        int element = q.front();
        q.pop();
        q.push(element);
    }
    return q;
}
/*
Input:
5 3
1 2 3 4 5

Output: 
3 2 1 4 5

Explanation: 
After reversing the given
input from the 3rd position the resultant
output will be 3 2 1 4 5.
*/


//191. INTERLEAVE THE FIRST HALF OF THE QUEUE WITH SECOND HALF                                         {T.C = O(N), S.C = O(N)}
class Solution{
public:
    vector<int> rearrangeQueue(queue<int> &q){
        int sz = q.size();
        int hsz = q.size()/2;
        vector<int>ans;
        
        queue<int>q1;
        queue<int>q2;
        
        int i = 0 ; 
        int j = q.size()/2;
        
        while(i < hsz){
            q1.push(q.front());
            q.pop();
            i++;
        }
        while(j < sz){
            q2.push(q.front());
            q.pop();
            j++;
        }
        
        while(!q1.empty() && !q2.empty()){
            ans.push_back(q1.front());
            ans.push_back(q2.front());
            q1.pop();
            q2.pop();
        }
        /* for odd number of element in queue
        while (!q1.empty()) {
            ans.push_back(q1.front());
            q1.pop();
        }

        while (!q2.empty()) {
            ans.push_back(q2.front());
            q2.pop();
        }
        */
        
        return ans;
    }
};
/*
Input:
N = 4
Q = {2,4,3,1}
Output:
{2,3,4,1}
Explanation:
After the mentioned rearrangement of the first half
and second half, our final queue will be {2,3,4,1}.
*/


struct petrolPump
{
    int petrol;
    int distance;
};
//192. CIRCULAR TOUR                                                                 {T.C = O(N), S.C = O(1)}
class Solution{
  public:
  
    int tour(petrolPump p[],int n)
    {
       int kami = 0;
       int start = 0;
       int balance = 0;
       
       for(int i = 0 ; i < n ; i++){
           balance += p[i].petrol - p[i].distance;   
           if(balance <  0){
               kami +=  balance;
               start = i+1;                           //start = rear+1
               balance = 0;                           //new balance 0
           }
       }
       if(kami + balance > 0){
           return start;
       }
       return -1;
    }
};
/*
Input:
N = 4
Petrol = 4 6 7 4
Distance = 6 5 3 5
Output: 1
Explanation: There are 4 petrol pumps with
amount of petrol and distance to next
petrol pump value pairs as {4, 6}, {6, 5},
{7, 3} and {4, 5}. The first point from
where truck can make a circular tour is
2nd petrol pump. Output in this case is 1
(index of 2nd petrol pump).
*/


//193. ROTEN ORANGES                                                                                     {T.C = O(N*M), S.C = O(N*M)}
class Solution {
  public:
    //Function to find minimum time required to rot all oranges. 
    int orangesRotting(vector < vector < int >> & grid) {
      // figure out the grid size
      int n = grid.size();
      int m = grid[0].size();

      // store {{row, column}, time}
      queue < pair < pair < int, int > , int >> q;
      int vis[n][m];
      int cntFresh = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          // if cell contains rotten orange
          if (grid[i][j] == 2) {
            q.push({{i, j}, 0}); 
            // mark as visited (rotten) in visited array
            vis[i][j] = 2;
          }
          // if not rotten
          else {        //value = 1
            vis[i][j] = 0;
          }
          // count fresh oranges
          if (grid[i][j] == 1) cntFresh++;
        }
      }

      int tm = 0;
      // delta row and delta column
      int drow[] = {-1, 0, +1, 0};
      int dcol[] = {0, 1, 0, -1}; 
      int cnt = 0;

      // bfs traversal (until the queue becomes empty)
      while (!q.empty()) {
        int r = q.front().first.first;
        int c = q.front().first.second;
        int t = q.front().second;
        tm = max(tm, t);
        q.pop();
        // exactly 4 neighbours 
        for (int i = 0; i < 4; i++) {
          // neighbouring row and column
          int nrow = r + drow[i];
          int ncol = c + dcol[i];
          // check for valid cell and 
          // then for unvisited fresh orange
          if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
            vis[nrow][ncol] == 0 && grid[nrow][ncol] == 1) {
            // push in queue with timer increased
             q.push({{nrow, ncol}, t + 1}); 
            // mark as rotten
            vis[nrow][ncol] = 2;
            cnt++;
          }
        }
      }

      // if all oranges are not rotten
      if (cnt != cntFresh) return -1;

      return tm;

    }
};
/*
Input: grid = {{0,1,2},{0,1,2},{2,1,1}}
Output: 1
Explanation: The grid is-
0 1 2
0 1 2
2 1 1
Oranges at positions (0,2), (1,2), (2,0)
will rot oranges at (0,1), (1,1), (2,2) and 
(2,1) in unit time.
*/


//194. DISTANCE OF NEAREST CELL HAVING 1 IN A BINARY MATRIX                           {T.C = O(N*M), S.C = O(N*M)}
class Solution 
{
    public:
    //Function to find distance of nearest 1 in the grid for each cell.
	vector<vector<int>>nearest(vector<vector<int>>grid)
	{
	    int n = grid.size();
	    int m = grid[0].size();
	    
	    vector<vector<int>>vis(n, vector<int>(m, 0));
	    vector<vector<int>>dis(n, vector<int>(m, 0));
	    //{{r,c},step)
	    queue<pair<pair<int,int>,int>>q;
	    
	    for(int i = 0 ; i < n;  i++){
	        for(int j = 0 ; j < m ; j++){
	            if(grid[i][j] == 1){
	                q.push({{i, j}, 0});                      //put in queue with 0 dist
	                vis[i][j] = 1;                          //mark in vis matrix 1
	            }
	            else{
	                vis[i][j] = 0;
	            }
	        }
	    }
	    
	    int delRow[] = {-1, 0, 1, 0};                        //deltarow(change in row)
	    int delCol[] = {0 , 1, 0, -1};                       //deltacol
	    
	    while(!q.empty()){
	        int row = q.front().first.first;
	        int col = q.front().first.second;
	        int steps = q.front().second;
	        
	        q.pop();
	        dis[row][col] = steps;
	        
	        for(int i = 0 ; i < 4 ; i++){
	            int nrow = row + delRow[i];               //nrow = neighbour row
	            int ncol = col + delCol[i];               //ncol = neighbour col
	            if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && vis[nrow][ncol] == 0){
	                vis[nrow][ncol] = 1;
	                q.push({{nrow, ncol}, steps+1});       //if not vis again push in queue
	            }
	        }
	    }
	    return dis;
	}
};
/*
For Input: 
3 4 
0 1 1 0 
1 1 0 0 
0 0 1 1
Your Output: 
1 0 0 1
0 0 1 1
1 1 0 0
*/

//195. FIRST NEGAITVE INTEGER IN EVERY WINDOW OF SIZE K                                      {T.C = O(N), S.C = O(K)}
//using queue
vector<long long> printFirstNegativeInteger(long long int a[],long long int n, long long int k) {
    
    vector<long long>ans;
    queue<long long>q;
    
    for(int i = 0 ; i < k-1 ; i++){
        if(a[i] < 0){
            q.push(a[i]);
        }
    }
    
    for(int i = k-1 ; i < n ; i++){
        if(a[i] < 0){
            q.push(a[i]);
        }
        if(!q.empty()){
            ans.push_back(q.front());
            if(q.front() == a[i-k+1]){
                q.pop();
            }
        }
        else{
            ans.push_back(0);
        }
    }
    return ans;
}

//using dequeue
vector<long long> printFirstNegativeInteger(long long int A[],long long int N, long long int K) {
                                  
    deque<long long int>dq;
    vector<long long>ans;
    
    //process first window of K size
    for(int i = 0 ; i < K ; i++){
        if(A[i] < 0){
            dq.push_back(i);
        }
    }
    
    //store answer of first K size window
    if(dq.size() > 0){
        ans.push_back(A[dq.front()]);
    }
    else{
        ans.push_back(0);
    }
    
    //process for remaining window
    for(int i = K ; i < N ; i++){
        
        //removal
        if(!dq.empty() && (i-dq.front()) >= K){    //size of current window > actual size of window
            dq.pop_front();
        }
        
        //addition
        if(A[i] < 0){
            dq.push_back(i);
        }
        
        //store answer
        if(dq.size() > 0){
            ans.push_back(A[dq.front()]);
        }
        else{
            ans.push_back(0);
        }
    }
    return ans;
}
/*
Input : 
N = 5
A[] = {-8, 2, 3, -6, 10}
K = 2
Output : 
-8 0 -6 -6
Explanation :
First negative integer for each window of size k
{-8, 2} = -8
{2, 3} = 0 (does not contain a negative integer)
{3, -6} = -6
{-6, 10} = -6
*/


//196. CHECK IF  ALL LEVELS OF TWO TREES ARE ANAGRAMS OR NOT


//197. SUM OF MINIMUM AND MAXIMUM ELEMENTS OF ALL SUBARRAYS OF SIZE 'K'
#include<bits/stdc++.h>
using namespace std;

int solve(int *arr, int n , int k){
    
    deque<int>maxi(k);
    deque<int>mini(k);

    //addition of first k size window
    for(int i = 0 ; i < k; i++){
        while(!maxi.empty() && arr[maxi.back()] <= arr[i]){
            maxi.pop_back();
        }
        while(!mini.empty() && arr[mini.back()] >= arr[i]){
            mini.pop_back();
        }
        maxi.push_back(i);
        mini.push_back(i);
    }

    int ans = 0;
    ans = ans + arr[maxi.front()] + arr[mini.front()];
    
    //for remaining windows
    for(int i = k ; i < n ; i++){
        //nextwindow
        //removal
        while(!maxi.empty() && (i-maxi.front()) >= k){
            maxi.pop_front();
        }
        while(!mini.empty() && (i-mini.front()) >= k){
            mini.pop_front();
        }

        //addition(same as above)
        while(!maxi.empty() && arr[maxi.back()] <= arr[i]){
            maxi.pop_back();
        }
        while(!mini.empty() && arr[mini.back()] >= arr[i]){
            mini.pop_back();
        }
        maxi.push_back(i);
        mini.push_back(i);
        
        ans = ans + arr[maxi.front()] + arr[mini.front()];
    }
    
    return ans;
}

int main(){
    int arr[7] = {2, 5, -1, 7, -3, -1, -2};
    int k = 4;
    cout<<solve(arr, 7, k)<<endl;

    return 0;
}
/*OUTPUT
18
*/


//198. GAME WITH STRINGS (OR)                                               {T.C = O(N*LOGN), S.C = O(N)}
//MINIMUM SUM OF SQUARES OF CHARACTER COUNTS IN A GIVEN STRING AFTER REMOVING “K” CHARACTERS.
class Solution{
public:
    int minValue(string s, int k){
        
        unordered_map<char, int>mp;
        priority_queue<int>pq;                //by default max heap
        
        for(int i = 0 ; i < s.length() ; i++){
            mp[s[i]]++;
        }
        
        for(auto it : mp){
            pq.push(it.second);
        }
        
        //heapify process to each iteration
        while(k){        //k = (k != 0)
            int x = pq.top();
            pq.pop();
            x--;                                   //decrement frequnency
            pq.push(x);                            // again push to pq and check again by heapify
            k--;
        }
        
        int sum = 0;
        while(!pq.empty()){
            int top = pq.top();
            sum += top*top;
            pq.pop();
        }
        
        return sum;
    }
};
/*
Input: s = abccc, k = 1
Output: 6
Explaination:
We remove c to get the value as 12 + 12 + 22
*/


//199. FIRST NON-REPEATING CHARACTER IN A STREAM
//USING STRINGS                                                                     {T.C = O(N), S.C = O(N)}
class Solution {
	public:
		string FirstNonRepeating(string A){
		    vector<int>vis(26, 0);                     //frequency array
		    string ans = "";
		    
		    vector<char>v;                            //maintian order array
		    int n = A.length();
		    for(int i = 0 ; i < n ; i++){
		        if(!vis[A[i]-'a']){
		            v.push_back(A[i]);
		        }
		        
		        vis[A[i]-'a']++;
		        
		        int f  = 0;
		        int m = v.size();
		        for(int j = 0 ; j < m ; j++){
		            if(vis[v[j] - 'a'] == 1){
		                ans.push_back(v[j]);
		                f = 1;
		                break;
		            }
		        }
		        
		        if(f == 0){
		            ans.push_back('#');
		        }
		    }
		    return ans;
		}

};

//USING QUEUE                                                                     {T.C = O(N), S.C = O(N)}
class Solution {
	public:
		string FirstNonRepeating(string A){
		    unordered_map<char,int>count;
		    queue<char>q;
		    string ans = "";
		    
    		for(int i = 0; i < A.length(); i++){
    		    char ch = A[i];
    		    
    		    //increasing count
    		    count[ch]++;
    		    
    		    //push element in queue
    		    q.push(ch);
    		    
    		    //q.front main algo
    		    while(!q.empty()){
    		        
    		        //repeating character
    		        if(count[q.front()] > 1){
    		            q.pop();
    		        }
    		        else{
    		            //non repeating charcter
    		            ans.push_back(q.front());
    		            break;
    		        }
    		    }
    		    //queue is empty
    		    if(q.empty()){
    		        ans.push_back('#');
    		    }
    		}
		    return ans;
		}
};
/*
Input: A = "aabc"
Output: "a#bb"
Explanation: For every ith character we will
consider the string from index 0 till index i first non
repeating character is as follow-
"a" - first non-repeating character is 'a'
"aa" - no non-repeating character so '#'
"aab" - first non-repeating character is 'b'
"aabc" - there are two non repeating characters 'b' and 'c', 
first non-repeating character is 'b' because 'b' comes before
'c' in the stream.
*/


//200. NEXT SMALLER ELEMENT                                                                             {T.C = O(N), S.C = O(N)}
vector<int> nextSmallerElement(vector<int> &arr, int n)
{
    stack<int>s;
    s.push(-1);

    vector<int>ans(n);
    for(int i = n-1 ; i >=0 ; i--){
        int curr = arr[i];
        while(s.top() >= curr){
            s.pop();
        }
        ans[i] = s.top();
        s.push(curr);
    }
    return ans;
}
/*
Sample Input 1:
2
4
2 1 4 3
3
1 3 2
Sample Output 1:
1 -1 3 -1
-1 2 -1
*/


/*-------------------------------------------------------   THE END   ---------------------------------------------------------------------------*/