//LINKED LIST

#include<bits/stdc++.h>
using namespace std;

//for singly linkded list
class Node{
public:
    int data;
    Node * next;

    Node(int data){
        this->data = data;
        this->next = NULL;
    }
};
//127. REVERSE A LINKED LIST
//ITERATIVE (POINTER APPROACH)                                                       {T.C = O(N), S.C = O(1)}
class Solution
{
    public:
    struct Node* reverseList(struct Node *head)
    {
        if(head == NULL || head->next == NULL){
            return head;
        }
        
        Node * prev = NULL;
        Node * curr = head;
        Node * forward = NULL;
        
        while(curr != NULL){
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
        }
        return prev;
    } 
};
//RECURSIVE APPROACH                                                           {T.C = O(N), S.C = O(1)}
class Solution
{
    public:
    void reverse(Node * &head , Node * curr , Node * prev){
    	//base condition
    	if(curr == NULL){
    		head = prev;
    		return;
    	}
    	Node * forward = curr->next;
    	curr->next = prev;
    	reverse(head , forward , curr);
    }
    struct Node* reverseList(struct Node *head)
    {
        Node * prev = NULL;
	    Node * curr = head;
	    reverse(head , curr , prev);
	    return head;
    }
    
};
/*
Input:
LinkedList: 1->2->3->4->5->6
Output: 6 5 4 3 2 1
Explanation: After reversing the list, 
elements are 6->5->4->3->2->1.
*/


class node{
public:
    int data;
    node * next;

    node(int data){
        this->data = data;
        this->next = NULL;
    }
};
//128. REVERSE A LINKED LIST IN GROUPS OF GIVEN SIZE K                                        {T.C = O(N), S.C = O(1)}
class Solution
{
    public:
    struct node *reverse (struct node *head, int k)
    { 
        //base case
        if(head == NULL){
            return head;
        }
        
        node * prev = NULL;
        node * curr = head;
        node * forward = NULL;
        int count = 0;
        while(curr != NULL && count < k){
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
            count++;
        }
        
        //recursion handle
        if(forward != NULL){
            head->next = reverse(forward, k);
        }
        
        return prev;
    }
};
/*
Input:
LinkedList: 1->2->2->4->5->6->7->8
K = 4
Output: 4 2 2 1 8 7 6 5 
Explanation: 
The first 4 elements 1,2,2,4 are reversed first 
and then the next 4 elements 5,6,7,8. Hence, the 
resultant linked list is 4->2->2->1->8->7->6->5.
*/


//129. DETECT LOOP IN A LINKED LIST                                                  {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    bool detectLoop(Node* head)
    {
        if(head == NULL){
            return false;
        }
        
        unordered_map<Node*, bool>mp;
        
        Node *temp = head;
        while(temp != NULL){
            if(mp[temp] == true){
                return true;
            }
            mp[temp] = true;
            temp = temp->next;
        }
        return false;
    }
};

//USING FLOYD'S CYCLE                                                             {T.C = O(N), S.C = O(1)}
class Solution
{
    public:
    //Function to check if the linked list has a loop.
    bool detectLoop(Node* head)
    {
        if(head == NULL){
            return false;
        }
        
        Node* slow = head;
        Node* fast = head;
        
        while(slow != NULL && fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast){
                return true;
            }
        }
        return false;
    }
};
/*
Input:
N = 3
value[] = {1,3,4}
x(position at which tail is connected) = 2
Output: True
Explanation: In above test case N = 3.
The linked list with nodes N = 3 is
given. Then value of x=2 is given which
means last node is connected with xth
node of linked list. Therefore, there
exists a loop.
*/


//130. REMOVE LOOP IN LINKED LIST                                                        {T.C = O(N), S.C = O(1)}
class Solution
{
public:
    // Function to remove a loop in the linked list.
    void removeLoop(Node* head)
    {
        Node* slow = head;
        Node* fast = head;
        Node* loopNode = NULL;
        
        // Detect the loop using Floyd's cycle detection algorithm.
        while(slow != NULL && fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast){
                loopNode = slow;
                break;
            }
        }
        
        // If no loop is found, simply return.
        if (loopNode == NULL) {
            return;
        }
        
        Node* startNode = head;
        while(startNode != loopNode){
            startNode = startNode->next;
            loopNode = loopNode->next;
        }
        
        Node* lastNode = loopNode;
        while(lastNode->next != loopNode){
            lastNode = lastNode->next;
        }
        
        // Break the loop by updating the last node's next pointer.
        lastNode->next = NULL;
    }
};
/*
Input:
N = 3
value[] = {1,3,4}
X = 2
Output: 1
Explanation: The link list looks like
1 -> 3 -> 4
     ^    |
     |____|    
A loop is present. If you remove it 
successfully, the answer will be 1. 
*/


//131. FIND THE FIRST NODE OF LOOP IN LINKED LIST                                                     {T.C = O(N), S.C = O(1)}
class Solution
{
    public:
     //Function to find first node if the linked list has a loop.
    int findFirstNode(Node* head)
    {
        if(head == NULL){
            return -1;
        }
        Node* slow = head;
        Node* fast = head;
        
        //checks loop is present or not
        while(slow != NULL && fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast){
                break;
            }
        }
        
        //search for first node of loop
        if(slow != fast){                     //fast pointer remain unchange / in loop
            return -1;
        }
        
        slow = head;                          //again point to head
        while( slow != fast){
            slow = slow->next;
            fast = fast->next;
        }
        return slow->data;
    }   
};
/*
Output: 3
Explanation:
We can see that there exists a loop 
in the given linked list and the first
node of the loop is 3.
*/


//132. REMOVE DUPLICATE ELEMENT FROM SORTED LINKED LIST                                                        {T.C = O(N), S.C = O(1)}
Node *removeDuplicates(Node *head)
{
    if(head == NULL || head->next == NULL){
        return head;
    }
    
    Node * first = head;
    Node * second = head->next;
    
    while(second != NULL){
        if(first->data == second->data){
            first->next = second->next;                   //skip duplicate node
            second = second->next;                        //move pointer
        }
        else{
            first = first->next;
            second = second->next;
        }
    }
    return head;
}
/*
Input:
LinkedList: 2->2->4->5
Output: 2 4 5
Explanation: In the given linked list 
2 ->2 -> 4-> 5, only 2 occurs more 
than 1 time. So we need to remove it once.
*/


//133. REMOVE DUPLICATES FROM AN UNSORTED LINKED LIST                                             {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    //Function to remove duplicates from unsorted linked list.
    Node * removeDuplicates( Node *head) 
    {
        if(head == NULL || head->next == NULL){
            return head;
        }
        unordered_map<int, bool>mp;
        
        Node* temp = head;                           //pointer for traverse ll
        Node* prev = NULL;                           //pointer to keep track of previous node

        while(temp != NULL){
            if(mp.find(temp->data) != mp.end()){
                prev->next = temp->next;                       //skip duplicate 
            }
            else{
                mp[temp->data] = true;              //if encounter 1st time mark true
                prev = temp;                        //update prev node to curr node
            }
            temp = temp->next;
        }
        return head;
    }
};
/*
Input:
N = 4
value[] = {5,2,2,4}
Output: 5 2 4
Explanation:Given linked list elements are
5->2->2->4, in which 2 is repeated only.
So, we will delete the extra repeated
elements 2 from the linked list and the
resultant linked list will contain 5->2->4
*/


class ListNode{
public:
    int data;
    ListNode * next;

    ListNode(int data){
        this->data = data;
        this->next = NULL;
    }
};
//134. MOVE LAST ELEMENT TO FRONT OF A LINKED LIST                                                    {T.C = O(N), S.C = O(1)}
class Solution{
public:
    ListNode *moveToFront(ListNode *head){
        if(head == NULL || head->next == NULL){
            return head;
        }
        
        ListNode* temp = head;
        ListNode* prev = NULL;
        while(temp->next != NULL){
            prev = temp;
            temp = temp->next;
            
        }
        prev->next = NULL;
        temp->next = head;
        head = temp;
        
        return head;
    }
};
/*
Input:
N = 5
List = {2,5,6,2,1}
Output:
{1,2,5,6,2}
Explanation:
In the given linked list, the last element is 1,
after moving the last element to the front the
linked list will be {1,2,5,6,2}.
*/


//135. ADD 1 TO A NUMBER REPRESENTED A LINKED LIST                                                          {T.C = O(N), S.C =  O(1)}
class Solution {
public:
    Node* reverse(Node* head) {
        Node* prev = NULL;
        Node* curr = head;
        Node* forward = NULL;

        while (curr != NULL) {
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
        }
        return prev;
    }

    Node* addOne(Node* head) {
        // Reverse the linked list
        head = reverse(head);
        Node* curr = head;
        bool carry = true; // Initialize carry

        while (curr != NULL && carry) {
            if (curr->next == NULL && curr->data == 9) {
                curr->data = 1;
                Node* temp = new Node(0);
                temp->next = head;
                head = temp;
                carry = false; // No more carry needed
            } 
            else if (curr->data == 9) {
                curr->data = 0;
                curr = curr->next;
            } 
            else {
                curr->data = curr->data + 1;
                carry = false; // No more carry needed
            }
        }

        // Reverse the linked list again to get the correct order
        head = reverse(head);
        return head;
    }
};
/*
Input:
LinkedList: 4->5->6
Output: 457
Explanation: 4->5->6 represents 456 and when 1 is added it becomes 457. 
*/


//136. ADD 2 NUMBERS REPRESENTED BY LINKED LIST                                                    {T.C = O(N), S.C = O(max(N, M))}
class Solution
{
    public:
    Node* reverse(Node* head){
        Node* prev = NULL;
        Node* curr = head;
        Node* forward = NULL;
        
        while(curr != NULL){
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
        }
        return prev;
    }
    struct Node* addTwoLists(struct Node* first, struct Node* second)
    {
        first = reverse(first);
        second = reverse(second);
        Node* dummy = new Node(NULL);
        Node* temp = dummy;
        int carry = 0;
        
        while(first != NULL ||  second != NULL || carry) {
            int sum = 0;
            if(first != NULL){
                sum += first->data;
                first = first->next;
            }
            if(second != NULL){
                sum += second->data;
                second = second->next;
            }
            sum += carry;
            carry = sum/10;
            Node* extra = new Node(sum % 10);
            temp->next = extra;
            temp = temp->next;
        }
        return reverse(dummy->next);
    }
};
/*
Input:
N = 2
valueN[] = {4,5}
M = 3
valueM[] = {3,4,5}
Output: 3 9 0  
Explanation: For the given two linked
list (4 5) and (3 4 5), after adding
the two linked list resultant linked
list will be (3 9 0).
*/


//137. INTERSECTION OF 2 SORTED LINKED LIST                                                          {T.C = O(min(N, k), S.C = O(K))}
Node* findIntersection(Node* l1, Node* l2)
{
    Node* head = NULL;
    Node* tail = NULL;
    
    while(l1 != NULL && l2 != NULL){
        if(l1->data < l2->data){
            l1 = l1->next;
        }
        else if(l1->data > l2->data){
            l2 = l2->next;
        }
        else{ //l1->data == l2->data
            if(head == NULL){               
                head = tail = new Node(l1->data); //first intersection create new node and store intersections
            }
            else{
                tail->next = new Node(l1->data);
                tail = tail->next;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
    }
    return head;
}
/*
Input:
L1 = 1->2->3->4->6
L2 = 2->4->6->8
Output: 2 4 6
Explanation: For the given first two
linked list, 2, 4 and 6 are the elements
in the intersection.
*/


//138. INTERSECTION POINT IN Y SHAPED LINKED LIST                                                   {T.C = O(N), S.C = O(1)}
int intersectPoint(Node* head1, Node* head2)
{
    Node* ptr1 = head1;
    Node* ptr2 = head2;
    int c1 = 0;
    int c2 = 0;
    while(ptr1){                                 //ptr1 != null
        c1++;
        ptr1 = ptr1->next;
    }
    while(ptr2){
        c2++;
        ptr2 = ptr2->next;
    }
    ptr1 = head1;
    ptr2 = head2;
    int diff = abs(c1-c2);
    if(c1 > c2){
        for(int i = 0 ;  i < diff ; i++){
            ptr1 = ptr1->next;
        }
    }
    else if(c2 > c1){
        for(int i = 0 ; i < diff; i++){
            ptr2 = ptr2->next;
        }
    }
    
    //else part (c1 == c2) searching for common point
    while(ptr1 != ptr2){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    if(ptr1){                                          //ptr1 != null
        return ptr1->data;
    }
    return -1;
}
/*
Input:
LinkList1 = 3->6->9->common
LinkList2 = 10->common
common = 15->30->NULL
Output: 15
*/


//139. MERGE SORT IN LINKED LIST                                                                        {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
  public:
    Node* findMid(Node* head){
        Node* slow = head;
        Node* fast = head->next;
        
        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
    Node* merge(Node* left, Node* right){
        if(left == NULL){
            return right;
        }
        if(right == NULL){
            return left;
        }
        
        //create node for store ans
        Node* ans = new Node(-1);
        Node* temp = ans;
        
        while(left != NULL && right != NULL){
            if(left->data < right->data){
                temp->next = left;
                temp = left;
                left = left->next;
            }
            else{
                temp->next = right;
                temp = right;
                right = right->next;
            }
        }
        while(left != NULL){
            temp->next = left;
            temp = left;
            left = left->next;
        }
        while(right != NULL){
            temp->next = right;
            temp = right;
            right = right->next;
        }
        
        ans = ans->next;
        return ans;
    }
    Node* mergeSort(Node* head) {
        if(head == NULL || head->next == NULL){
            return head;
        }
        
        //finding mid
        Node* mid = findMid(head);
        
        //break into two parts
        Node* left = head;
        Node* right = mid->next;
        mid->next = NULL;                  //for breaking link between both
        
        //recursive call
        left = mergeSort(left);
        right = mergeSort(right);
        
        Node* ans = merge(left, right);
        
        return ans;
        
    }
};
/*
Input:
N = 5
value[]  = {3,5,2,4,1}
Output: 1 2 3 4 5
Explanation: After sorting the given
linked list, the resultant matrix
will be 1->2->3->4->5.
*/


//140. QUICK SORT FOR LINKED LIST


//141. MIDDLE OF THE LINKED LIST                                                                    {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};
/*
Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.
*/


//142. CHECK IF CIRCULAR LINKED LIST                                                    {T.C = O(N), S.C = O(1)}
bool isCircular(Node *head)
{
    if(head == NULL || head->next == NULL){
        return false;
    }
    Node* slow = head;
    Node* fast = head;
   
    while(fast != NULL && fast->next != NULL){
       slow = slow->next;
       fast = fast->next->next;
       if(slow == fast){
           return true;
       }
    }
    return false;
}
/*
Input:
LinkedList: 1->2->3->4->5
(the first and last node is connected,
i.e. 5 --> 1)
Output: 1
*/


//143. SPLIT A CIRCULAR LINKED LIST INTO TWO HALVES                                                {T.C = O(N), S.C = O(1)}
void splitList(Node *head, Node **head1, Node **head2)
{
    Node* slow = head;
    Node* fast = head->next;                         //finding 1st mid element   1 2 3 4 ,mid == 2
    
    //findinng mid
    while(fast != head && fast->next != head){       //circular ll
        slow = slow->next;
        fast = fast->next->next;
    }
    
    *head1 = head;
    *head2 = slow->next;                           
    slow->next = head;                             //make circular
    
    Node* curr = *head2;
    while(curr->next != head){
        curr = curr->next;
    }
    curr->next = *head2;                           //point to head
}
/*
Input:
Circular LinkedList: 2->6->1->5
Output:
2 6
1 5
*/


//144. CHECK IF LINKED LIST IS PALINDROME                                                  {T.C = O(N), S.C = O(N)}
//BRUTE FORCE
#include<vector>
bool checkPalindrome(vector<int>&ans){
    int n = ans.size();
    int s = 0;
    int e = n-1;
    
    while(s <= e){
        if(ans[s] != ans[e]){
            return 0;
        }
        s++;
        e--;
    }
    return 1;
}
class Solution{
  public:
    //Function to check whether the list is palindrome.
    bool isPalindrome(Node *head)
    {
        vector<int>ans;
        Node* temp = head;
        while(temp != NULL){
            ans.push_back(temp->data);
            temp = temp->next;
        }
        
        return checkPalindrome(ans);
    }
};

//OPTIMIZED APPROACH                                                              {T.C = O(N), S.C = O(1)}
Node* reverse(Node* head){
    if(head == NULL || head->next == NULL){
        return head;
    }
    Node* prev = NULL;
    Node* curr = head;
    Node* forward = NULL;
    
    while(curr->next != NULL){
        forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    return prev;
}
Node* middle(Node* head){
    Node* slow = head;
    Node* fast = head;
    
    // Finding middle
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
class Solution{
  public:
    //Function to check whether the list is palindrome.
   bool isPalindrome(Node *head)
   {
        if(head == NULL || head->next == NULL){
            return true;
        }
        Node* mid = middle(head);
        Node* rev = reverse(mid);
        
        while(head != NULL && rev != NULL){
            if(head->data != rev->data){
                return false;
            }
            head = head->next;
            rev = rev->next;
        }
        return true;
    }
};
/*
Input:
N = 3
value[] = {1,2,1}
Output: 1
Explanation: The given linked list is
1 2 1 , which is a palindrome and
Hence, the output is 1.
*/


//145. DELETION FROM A CIRCULAR LINKED LIST

/*------------------------------------------------------   DOUBLY LINKED LIST -------------------------------------------------------------*/

//for doubly linked list
class Node{
public:
    int data;
    Node* next;
    Node* prev;

    Node(int data){
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};
//146. REVERSE A DOUBLY LINKED LIST                                                  {T.C = O(N), S.C = O(1)}
Node* reverseDLL(Node * head)
{
    Node* prev = NULL;
    Node* curr = head;
    Node* forward = NULL;
    
    while(curr != NULL){
        forward = curr->next;
        curr->next = prev;
        curr->prev = forward;                     //extra line for DLL
        prev = curr;
        curr = forward;
    }
    return prev;
}
/*
Input:
LinkedList: 75 <--> 122 <--> 59 <--> 196
Output: 196 59 122 75
*/


//147. FIND PAIRS WITH GIVEN SUM IN DUBBLY LINKED LIST
class Solution {
public:
    vector<pair<int, int>> findPairsWithGivenSum(Node *head, int target) {
        vector<pair<int,int>>v;
        Node*s=head;Node *e=head;
        while(e->next){
            e=e->next;
        }
        while(s->data<e->data){
           int val1=s->data,val2=e->data;
           if(val1+val2==target){
               v.push_back({s->data,e->data});
               s=s->next;
               e=e->prev;
           }
           else if(val1+val2<target){
               s=s->next;
           }
           else {
               e=e->prev;
           }
        }
        return v;
    }
};
/*
Input:  
1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9
target = 7
Output: (1, 6), (2,5)
Explanation: We can see that there are two pairs 
(1, 6) and (2,5) with sum 7.
*/


//148. COUNT TRIPLETS IN LINKED LIST                                                  {T.C = O(N^2), S.C = O(N)}
//copied
int countTriplets(struct Node* head, int x) 
{ 
   vector<int> vec;
   while(head!=NULL)
   {
       vec.emplace_back(head->data);
       head=head->next;
   }
   sort(vec.begin(),vec.end());
   int count=0;
    for(int i=vec.size()-1;i>=2;i--){
    int a=0;
    int b=i-1;
    while(a<b)
    {
        int sum=vec[a]+vec[b]+vec[i];
        if(sum==x)
        {
           count++;
            a++;
            b--;
        }
        else if(sum<x)
        a++;
        else
        b--;
    }}
   return count;
} 
/*
Input: LinkedList: 9->8->6->5->4->2->1,  X = 17
Output: 2
Explanation: Distinct triplets are (2, 6, 9) 
and (4, 5, 8) which have sum equal to X i.e 17.
*/


//149. SORT A "K" SORTED DOUBLY LINKED LIST                                               {T.C = O(N*LOGN), S.C = O(N)}
Node* sortedDll(Node* head, int k){ 
    vector<int> ans;

    // Step 1: Traverse the linked list and store data in the vector 'ans'
    while (head) {
        ans.push_back(head->data);
        head = head->next;
    }

    // Step 2: Sort the 'ans' vector
    int n = ans.size();
    sort(ans.begin(), ans.end());

    // Step 3: Create a sorted doubly linked list using the 'ans' vector
    Node* res = new Node(ans[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
        Node* temp = new Node(ans[i]);
        res->prev = temp;
        temp->next = res;
        res = temp;
    }
    return res;
}
/*
Sample Input 1 :
1
4 
6 5 3 2 8 10 9 -1
Sample Output 1 :
2 3 5 6 8 9 10 -1
*/


class DLLNode{
public:
    int data;
    DLLNode* next;
    DLLNode* prev;

    DLLNode(int data){
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};
//150. ROTATE DOUBLY LINKED LIST BY K NODES                                        {T.C = O(N), S.C = O(1)}
DLLNode* rotateDLL(DLLNode* head, int k)                                         
{
    if (k == 0 || head == NULL || head->next == NULL) {
        return head;
    }

    DLLNode* curr = head;
    int count = 1;                               //count 0 handled
    while (count < k && curr != NULL) {
        curr = curr->next;
        count++;
    }

	//extra
    // if (curr == NULL) {
    //     // Handle the case where k is larger than the length of the list
    //     return head;
    // }

    DLLNode* nthNode = curr;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = head;
    head->prev = curr;
    head = nthNode->next;
    head->prev = NULL;
    nthNode->next = NULL;

    return head;
}
/*
Sample Input 1 :
2
4 3 9 1 7 8 -1
4
1 2 3 4 5 -1
2
Sample Output 1 :
7 8 4 3 9 1 
3 4 5 1 2
*/


//151. REVERSE DOUBLY LINKED LIST NODES IN GROUPS OF K                                                           {T.C = O(N), S.C = O(1)}
Node* reverseDLLInGroups(Node* head, int k)                                                                  
{	
    //base case
	if(head == NULL){
		return head;
	}

	Node* prev = NULL;
	Node* curr = head;
	Node* forward = NULL;
	int count = 0;
	while(curr != NULL && count < k){
		forward = curr->next;
		curr->next = prev;
		curr->prev = forward;
		prev = curr;
		curr = forward;
		count++;
	}

	//recursion handle
	if(forward != NULL){
		head->next = reverseDLLInGroups(forward, k);
	}

	return prev;
}
/*
Sample Input 1:
1 
1 2 3 4 5 6 7 -1
2  
Sample Output 1:
2 1 4 3 6 5 7 -1
*/


//152. CAN WE REVERSE A LINKED LIST IN THAN O(N) ?
/*ANSWER = NO

No, it is not possible to reverse a singly linked list in less than O(n) time complexity, where n is the number of nodes
in the linked list. This is because you need to visit and modify every node in the list in order to reverse the links.

In a singly linked list, each node has a reference only to the next node, and not to the previous node. Therefore, 
you have to traverse the entire list sequentially to reverse the links between the nodes. This requires visiting each
node exactly once to update its next pointer.
*/


//153. WHY QUICKSORT IS PREFFERED FOR ARRAYS AND MERGE SORT FOR LINKED LIST
/*ANSWER

Quicksort for Arrays:
->Good for arrays due to cache efficiency.
->In-place sorting (no extra memory needed).
->Faster average-case time complexity (O(n log n)).
->Can have worst-case time complexity (O(n^2)), but can be mitigated.


Merge Sort for Linked Lists:
->Stable sorting (preserves relative order of equal elements).
->Predictable worst-case time complexity (O(n log n)).
->Efficient for linked lists (doesn't need random access).
->Consistent performance regardless of input distribution.
->Suitable for parallelization.

In essence, Quicksort works well for arrays and offers good average-case performance, while Merge Sort is preferable
for linked lists due to its stability, consistent performance, and efficiency for linked structures.
*/


class Node{
public:
	int data;
	struct Node * next;
	struct Node * bottom;
	
	Node(int x){
	    this->data = x;
	    this->next = NULL;
	    this->bottom = NULL;
	}
	
};
//154. FLATTENING A LINKED LIST                                                                    {T.C = O(N*LOGN), S.C = O(N / 1)}
Node* merge(Node* a, Node* b){
    //create node for store ans
    Node* ans = new Node(-1);
    Node* temp = ans;
    
    while(a != NULL && b != NULL){
        if(a->data < b->data){
            temp->bottom = a;
            temp = temp->bottom;
            a = a->bottom;
        }
        else{
            temp->bottom = b;
            temp = temp->bottom;
            b = b->bottom;
        }
    }
    if(a){
        temp->bottom = a;
    }else{
        temp->bottom = b;
    }
    
    ans = ans->bottom;
    return ans;
}
Node *flatten(Node *root)
{
   //base case
   if(root == NULL || root->next == NULL){
       return root;
   }
   
   //recursive call
   root->next = flatten(root->next);
   
   //merge
   root = merge(root, root->next);
   
   return root;
}
/*
Input:
5 -> 10 -> 19 -> 28
|     |     |     | 
7     20    22   35
|           |     | 
8          50    40
|                 | 
30               45
Output:  5-> 7-> 8- > 10 -> 19-> 20->
22-> 28-> 30-> 35-> 40-> 45-> 50.
Explanation:
The resultant linked lists has every 
node in a single level.
(Note: | represents the bottom pointer.)
*/


//155. SORT 0'S  1'S AND 2'S IN A LINKED LIST                                                               {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    //Function to sort a linked list of 0s, 1s and 2s.
    Node* segregate(Node *head) {
        
        int zeroCount = 0;
        int oneCount = 0;
        int twoCount = 0;
        
        Node* temp = head;
        
        while(temp != NULL){
            if(temp->data == 0){
                zeroCount++;
            }
            else if(temp->data == 1){
                oneCount++;
            }
            else{
                twoCount++;
            }
            
            temp = temp->next;
        }
        
        temp = head;
        
        while(temp != NULL){
            if(zeroCount != 0){
                temp->data = 0;
                zeroCount--;
            }
            else if(oneCount != 0){
                temp->data = 1;
                oneCount--;
            }
            else{
                temp->data = 2;
                twoCount--;
            }
            
            temp = temp->next;
        }
        
        return head;
    }
};
/*
Input:
N = 8
value[] = {1,2,2,1,2,0,2,2}
Output: 0 1 1 2 2 2 2 2
Explanation: All the 0s are segregated
to the left end of the linked list,
2s to the right end of the list, and
1s in between.
*/


class Node{
public:
    int data;
    Node* next;
    Node* arb;                                  //random pointer

    Node(int x){
        data = x;
        next = NULL;
        arb = NULL;
    }

};
//156. CLONE A LINKED LIST WITH NEXT AND RANDOM POINTER                                                  {T.C = O(N), S.C = O(N)}
//using map
class Solution
{
    private:
    void insertAtTail(Node * &head , Node* &tail , int d){
        Node* temp = new Node(d);
        if(head == NULL){
            head = temp;
            tail = temp;
            return;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
    }
    public:
    Node *copyList(Node *head)
    {
        //step1 - create a clone list
        Node* cloneHead = NULL;
        Node* cloneTail = NULL;
        Node* temp = head;
        
        while(temp != NULL){
            insertAtTail(cloneHead , cloneTail , temp->data);
            temp = temp->next;
        }
        
        //step2- create a map
        unordered_map<Node*,Node*>oldToNew;
        
        Node* originalNode = head;
        Node* cloneNode = cloneHead;
        
        while(originalNode != NULL){
            oldToNew[originalNode] = cloneNode;
            originalNode = originalNode->next;
            cloneNode = cloneNode->next;
        }
        
        //step3- set random pointer
        originalNode = head;
        cloneNode = cloneHead;
        
        while(originalNode != NULL){
            cloneNode->arb = oldToNew[originalNode->arb];
            originalNode = originalNode->next;
            cloneNode = cloneNode->next;
        }
        
        return cloneHead;
    }

};

//without using map                                                                                   {T.C = O(N), S.C = O(1)}
class Solution
{
    private:
    void insertAtTail(Node * &head , Node* &tail , int d){
        Node* temp = new Node(d);
        if(head == NULL){
            head = temp;
            tail = temp;
            return;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
    }
    public:
    Node *copyList(Node *head)
    {
        //step1 - create a clone list
        Node* cloneHead = NULL;
        Node* cloneTail = NULL;
        Node* temp = head;
        
        while(temp != NULL){
            insertAtTail(cloneHead , cloneTail , temp->data);
            temp = temp->next;
        }
        
        //step2- clonenodes add in between original list
        Node* originalNode = head;
        Node* cloneNode = cloneHead;
        
        while(originalNode != NULL){
            Node* next = originalNode->next;
            originalNode->next = cloneNode;
            originalNode = next;
            
            next = cloneNode->next;
            cloneNode->next = originalNode;
            cloneNode = next;
        }
        
        //step3- copy random pointer
        temp = head;
        while(temp != NULL){
            if(temp->arb != NULL){
                temp->next->arb = temp->arb ? temp->arb->next : temp->arb;
            }
            temp = temp->next->next;
        }
        
        //step4- revert changes done in step2
        originalNode = head;
        cloneNode = cloneHead;
        
        while(originalNode != NULL){
            originalNode->next = cloneNode->next;
            originalNode = originalNode->next;
            
            if(originalNode != NULL){
                cloneNode->next = originalNode->next;
            }
            cloneNode = cloneNode->next;
        }
        
        //step5- return ans
        return cloneHead;
    }

};
/*
Input:
N = 4, M = 2
value = {1,2,3,4}
pairs = {{1,2},{2,4}}
Output: 1
Explanation: In this test case, there
are 4 nodes in linked list.  Among these
4 nodes,  2 nodes have arbitrary pointer
set, rest two nodes have arbitrary pointer
as NULL. Second line tells us the value
of four nodes. The third line gives the
information about arbitrary pointers.
The first node arbitrary pointer is set to
node 2.  The second node arbitrary pointer
is set to node 4.
*/


//157. MERGE K SORTED LINKED LIST                                                         {T.C = O(N*LOGK), S.C = O(K)}
class compare {
public:
    // Custom comparison operator for min-heap.
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;
    }  
};

class Solution {
public:
    Node* mergeKLists(Node* arr[], int k) {
        // Create a min-heap of nodes using the custom comparator.
        priority_queue<Node*, vector<Node*>, compare> minHeap;
        
        // Step 1: Put the first node from each linked list into the min-heap.
        for(int i = 0; i < k; i++) {
            if(arr[i] != NULL) {
                minHeap.push(arr[i]);
            }
        }
        
        // Initialize pointers for the merged linked list.
        Node* head = NULL; // Pointer to the head of the merged linked list.
        Node* tail = NULL; // Pointer to the tail of the merged linked list.
        
        // Step 2: Merge the linked lists using the min-heap.
        while(!minHeap.empty()) {
            // Get the smallest node from the min-heap.
            Node* top = minHeap.top();
            minHeap.pop();
            
            // If the current node has a next element, add it to the min-heap.
            if(top->next != NULL) {
                minHeap.push(top->next);
            }
            
            // If the merged linked list is empty, initialize the head and tail.
            if(head == NULL) {
                head = top;
                tail = top;
            } else { // Insert the current node at the tail of the merged linked list.
                tail->next = top;
                tail = top;
            }
        }
        
        // Step 3: Return the head of the merged linked list.
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


//158. MULTIPLY 2 LINKED LIST                                                                      {T.C = O(N), S.C = O(1)}
long long  multiplyTwoLists (Node* l1, Node* l2)
{
  long long int num1 = 0;
  long long int num2 = 0;
  long long mod = 1e9+7;
  
  Node* first = l1;
  Node* second = l2;
  
  while(first != NULL){
      num1 = (num1*10 + first->data) % mod;
      first = first->next;
  }
  while(second != NULL){
      num2 = (num2*10 + second->data) % mod;
      second = second->next;
  }
  
  return (num1*num2)%mod;
}
/*
For Input: 
2
15
8 6 3 1 7 5 9 6 2 1 7 8 5 7 4 
22
9 5 9 7 5 3 8 8 3 1 8 9 6 4 3 3 3 8 6 0 4 8 
29
9 9 7 7 6 4 3 0 3 0 9 2 5 4 0 5 9 4 6 9 2 2 4 7 7 5 4 8 1 
23
9 9 3 6 8 0 2 1 0 5 1 1 0 8 5 0 6 4 6 2 5 8 6
Your Output: 
606331838
589998973
*/


//159. DELETE NODES HAVING GREATER VALUE ON RIGHTN                                                                {T.C = O(N), S.C = O(1)}
class Solution
{
    public:
    Node *compute(Node *head)
    {
        Node* temp = head;
        
        while(temp->next != NULL){
            if(temp->data < temp->next->data){
                temp->data = temp->next->data;
                temp->next = temp->next->next;
                temp = head;
            }
            else{
                temp = temp->next;
            }
        }
        return head;
    }
};
/*
Input:
LinkedList = 12->15->10->11->5->6->2->3
Output: 15 11 6 3
Explanation: Since, 12, 10, 5 and 2 are
the elements which have greater elements
on the following nodes. So, after deleting
them, the linked list would like be 15,
11, 6, 3.
*/


//160. SEGREGATE EVEN AND ODD IN A LINKED LIST                                                         {T.C = O(N), S.C = O(1)}
class Solution{
public:
    Node* divide(int N, Node *head){
        if(head == NULL || head->next == NULL){
            return head;
        }
        
        //create 2 ll
        Node* even = new Node(-1);
        Node* t1 = even;
        Node* odd = new Node(-1);
        Node* t2 = odd;
        
        while(head != NULL){
            if((head->data) % 2 == 0){                        //even
                t1->next = head;
                t1 = head;
            }
            else{                                             //odd
                t2->next = head;
                t2 = head;
            }
            head = head->next;
        }
        //join both lists
        t1->next = odd->next;                            //link even ll to odd ll
        t2->next = NULL;                                 //ensures ending
        head = even->next;                               //point head to starting of joined ll
        
        return head;
    }
};
/*
Input: 
N = 7
Link List:
17 -> 15 -> 8 -> 9 -> 2 -> 4 -> 6 -> NULL

Output: 8 2 4 6 17 15 9

Explaination: 8,2,4,6 are the even numbers 
so they appear first and 17,15,9 are odd 
numbers that appear later.
*/


//161. NTH NODE FROM END OF LINKED LIST                                                            {T.C = O(N), S.C = O(1)}
Node* reverse(Node* head){
    Node* prev = NULL; 
    Node* forward = NULL;
    Node* curr = head;
    
    while(curr != NULL){
        forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    return prev;
}
class Solution{
public:
    int getNthFromLast(Node *head, int n)
    {
        Node* rev = reverse(head);
        int count = 1;
        
        while(rev != NULL && count < n){
            rev = rev->next;
            count++;
        }
        if(rev == NULL){                                 //handle case count > n 
            return -1;
        }
        
        return rev->data;
    }
};
/*
Input:
N = 2
LinkedList: 1->2->3->4->5->6->7->8->9
Output: 8
Explanation: In the first example, there
are 9 nodes in linked list and we need
to find 2nd node from end. 2nd node
from end is 8.  
*/


//162. FIRST NON-REPEATING CHARACTER IN A STREAM                                                {T.C = O(N), S.C = O(N)}
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
	            if(vis[v[j] - 'a'] == 1){          //if non repeating char found
	                ans.push_back(v[j]);
	                f = 1;
	                break;
	            }
	        }
	        
	        if(f == 0){                            //if no non repeating char found
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


/*--------------------------------------------------------------   THE END   -----------------------------------------------------------------*/