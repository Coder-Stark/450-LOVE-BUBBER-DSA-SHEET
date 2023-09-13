//GRAPH
//MINIMUM DISTANCE FINDING ALGORITHM
/*
1. DIJKSTRA'S ALGO                  {not work for -ve weighted graph}
2. BELLMANFORD ALGO                 {work for -ve weighted graph}
3. FLOYD WARSHALL ALGO              {brute force algo}
*/
//MINIMUM SPANNING TREE ALGORITHM
/*
1. KRUSKAL'S ALGO          {intermediate result may be or may be not connected}
2. PRIM'S ALGO             {intermediate result always connected} 
*/
#include<bits/stdc++.h>
using namespace std;


//276. CREATING AND PRINTING GRAPH                                                     {T.C = O(N*M), S.C = O(N^2)}
vector < vector < int >> printAdjacency(int n, int m, vector < vector < int >> & edges) {
    
    //stores all adjacent nodes corresponding index
    vector<int>ans[n];
    for(int i = 0 ; i < m ; i++){
        int u = edges[i][0];
        int v = edges[i][1];

        ans[u].push_back(v);
        ans[v].push_back(u);                   //undirected graph
    }
    
    //print
    vector<vector<int>>adj(n);
    for(int i = 0 ; i < n ; i++){
        adj[i].push_back(i);

        //entring neighbour
        for(int j = 0 ; j < ans[i].size(); j++){
            adj[i].push_back(ans[i][j]);
        }
    }
    return adj;
}
/*
Sample Input 1:
4 3
1 2
0 3
2 3
Sample Output 1:
0 3
1 2
2 1 3
3 0 2
*/


//277. BFS OF GRAPH                                                                      {T.C = O(V+E), S.C = O(V)}
class Solution {
  public:
    void bfs(int node, vector<int>adj[], vector<int>&ans, vector<int>&vis){
        queue<int>q;
        
        q.push(node);                                   //step1
        vis[node] = 1;                                  //step2
        while(!q.empty()){
            int frontNode = q.front();                  //step3
            q.pop();
            ans.push_back(frontNode);                   //step4
            for(auto it : adj[frontNode]){
                if(!vis[it]){
                    q.push(it);
                    vis[it] = 1;
                }
            }
            
        }
    }
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        //3 data structures required (queue)
        vector<int>ans;
        vector<int>vis(V, 0);                            // frequency array/vector

        bfs(0, adj, ans, vis);                               //0 = starting index or node
        return ans;
    }
};

//another approach (creating adjacency list)
void prepareAdjList(unordered_map<int,set<int>>&adjList,vector<pair<int, int>> &edges){
    for(int i = 0 ; i < edges.size() ; i++){
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].insert(v);
        adjList[v].insert(u);
    }
}
void bfs(unordered_map<int,set<int>>&adjList,unordered_map<int,bool>&visited,vector<int>&ans,int node){
    queue<int>q;
    q.push(node);
    visited[node] = 1;

    while(!q.empty()){
        int frontNode = q.front();
        q.pop();

        //store frontNode into ans
        ans.push_back(frontNode);

        //traverse all neighbours of frontNode
        for(auto i: adjList[frontNode]){
            if(!visited[i]){
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}
vector<int> BFS(int vertex, vector<pair<int, int>> edges)
{
    unordered_map<int,set<int>>adjList;
    vector<int>ans;
    unordered_map<int,bool>visited;

    prepareAdjList(adjList,edges);

    //traverse all component of graph
    for(int i = 0 ; i < vertex ; i++){
        if(!visited[i]){
            bfs(adjList,visited,ans,i);
        }
    }
    return ans;
}
/*
Input
V = 3, E = 2
edges = {(0,1),(0,2)}
Output: 
0 1 2
Explanation:
0 is connected to 1 , 2.
so starting from 0, it will go to 1 then 2,
thus bfs will be 0 1 2. 
*/


//278. DFS OF A GRAPH                                                                    {T.C = O(V+E), S.C = O(V)}
class Solution {
  public:
    void dfs(int node, vector<int>adj[], vector<int>&ans, vector<int>&vis){
        vis[node] = 1;
        ans.push_back(node);
        //traverse all neightbour from adjacency list
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(it, adj, ans, vis);
            }
        }
    }
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        //2 data structure is needed
        vector<int>ans;
        vector<int>vis(V, 0);
        
        //handle disconnected components
        for(int i = 0 ; i < V ; i++){
            dfs(0, adj, ans, vis);                                  //0 = starting index or node
        }
        return ans;
    }
};

//another approach(creating adjacency list)
void dfs(unordered_map<int,list<int>>&adj, unordered_map<int,bool>&visited, vector<int>&component, int node){
    //ans store
    component.push_back(node);
    visited[node] = 1;

    //every connected node make recursive call
    for(auto i: adj[node]){
        if(!visited[i]){
            dfs(adj, visited, component, i);
        }
    }
}
vector<vector<int>> depthFirstSearch(int V, int E, vector<vector<int>> &edges)
{
    //prepare adjList
    unordered_map<int , list<int>>adj;
    for(int i = 0 ; i < edges.size() ; i++){
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>>ans;
    unordered_map<int,bool>visited;

    //traverse all component of graph
    for(int i = 0 ; i < V ; i++){
        if(!visited[i]){
            vector<int>component;
            dfs(adj, visited,component,i);
            ans.push_back(component);
        }
    }
    return ans;
}
/*
Input: V = 5 , adj = [[2,3,1] , [0], [0,4], [0], [2]]
Output: 0 2 4 3 1
Explanation: 
0 is connected to 2, 3, 1.
1 is connected to 0.
2 is connected to 0 and 4.
3 is connected to 0.
4 is connected to 2.
so starting from 0, it will go to 2 then 4,
and then 3 and 1.
Thus dfs will be 0 2 4 3 1.
*/


//279. DETECT CYCLE IN DIRECTED GRAPH                                                {T.C = O(V+E), S.C = O(V)}
//USING BFS (Topological sort {kahn's algo})
class Solution {
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        // 3 data structures required = adj, indegree, queue
        vector<int>inDegree(V, 0);
        
        //calculate all indegree's of each node
        for(int i = 0 ; i < V ; i++){
            for(auto it : adj[i]){
                inDegree[it]++;
            }
        }
        
        queue<int>q;
        //push 0 indegree's nodes in queue
        for(int i = 0 ; i < V ; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        
        int count = 0;
        //do bfs
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            
            count++;
            
            //reduce indegree of adjacent nodes after disconnection of node
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0){
                    q.push(it);
                }
            }
        }
        
        if(count == V){               //valid topological = not cycle
            return false;
        }
        return true;                  //invalid topological = cyclic
    }
};


//USING DFS
class Solution {
  public:
    bool isDFSCyclic(vector<int>adj[], vector<int>&vis, vector<int>&dfsVis, int node){
        vis[node] = 1;
        dfsVis[node] = 1;
        
        for(auto it : adj[node]){
            if(!vis[it]){
                bool ans = isDFSCyclic(adj, vis, dfsVis, it);
                if(ans){
                    return true;
                }
            }else if(dfsVis[it]){                   //if vis && dfsVis
                return true;
            }
        }
        dfsVis[node] = 0;                                 //backtrack mark dfsVis = 0 for next iteration
        return false;
    }
    bool isCyclic(int V, vector<int> adj[]) {
        //3 data structures required= adj, vis, dfsVis, 
        vector<int>vis(V, 0);
        vector<int>dfsVis(V, 0);
        //call dfs for all nodes(disconnected graph also)
        for(int i = 0 ; i < V ; i++){
            if(!vis[i]){
                bool ans = isDFSCyclic(adj, vis, dfsVis, i);
                if(ans){
                    return true;
                }
            }
        }
        return false;
    }
};
/*
For Input: 
4 4
0 1
1 2
2 3
3 3
Your Output: 
1
Expected Output: 
1
*/


//280. DETECT CYCLE IN UNDIRECTED GRAPH                                              {T.C = O(V+E), S.C = O(V)}
//USING BFS
class Solution {
  public:
    bool isBFSCyclic(vector<int>adj[], vector<int>&vis, int &node){
        unordered_map<int, int>parent;
        parent[node] = -1;
        
        queue<int>q;
        q.push(node);
        vis[node] = 1;
        
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            
            for(auto it : adj[frontNode]){
                //condition of skip element (vis & parent)
                if(vis[it] && it != parent[frontNode]){
                    return true;
                }else if(!vis[it]){             //normal condition
                    q.push(it);
                    vis[it] = 1;
                    parent[it] = frontNode;
                }
            }
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<int>vis(V, 0);
        
        //handle diconnected graph case
        for(int i = 0 ; i < V ; i++){
            if(!vis[i]){
                bool ans = isBFSCyclic(adj, vis, i);
                if(ans == true){
                    return true;
                }
            }
        }
        return false;
    }
};

//USING DFS                                                              
class Solution {
public:
    bool isDFSCyclic(vector<int> adj[], vector<int>& vis, int node, int parent) {
        vis[node] = 1;

        for (auto it : adj[node]) {
            if (!vis[it]) {
                bool cycleDetected = isDFSCyclic(adj, vis, it, node);
                if (cycleDetected) {
                    return true;
                }
            } else if (it != parent) { // Check for back edge to an ancestor in the DFS tree
                return true;
            }
        }
        return false;
    }

    bool isCycle(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);

        // Handle disconnected graph case
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                bool ans = isDFSCyclic(adj, vis, i, -1);
                if (ans == true) {
                    return true;
                }
            }
        }
        return false;
    }
};
/*
Input:  
V = 5, E = 5
adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}} 
Output: 1
Explanation: 

1->2->3->4->1 is a cycle.
*/


//281. RAT IN A MAZE PROBLEM                                                  {T.C = O(N^2)^4 , S.C = O(N^2)}
//DFS
class Solution{
    public:
    void dfs(vector<vector<int>>&m, int n , vector<string>&ans, vector<vector<int>>&vis, const string &s, int i , int j){
        //base case
        if(i < 0 || j < 0 || i >= n || j >= n){
            return;
        }
        if(m[i][j] == 0 || vis[i][j] == 1){
            return;
        }
        
        if(i == n-1 && j == n-1){
            ans.push_back(s);
            return;
        }
        vis[i][j] = 1;                                      //1st time visit any element mark as 1
        
        //recursive calls in 4 directions
        dfs(m, n, ans, vis, s +'U', i-1, j);
        dfs(m, n, ans, vis, s +'D', i+1, j);
        dfs(m, n, ans, vis, s +'L', i, j-1);
        dfs(m, n, ans, vis, s +'R', i, j+1);
        
        vis[i][j] = 0;                                     //marks 0 after 1 path to again search new path
        
    }
    vector<string> findPath(vector<vector<int>> &m, int n) {
        vector<string>ans;
        vector<vector<int>>vis(n, vector<int>(n, 0));
        string s = "";
        dfs(m, n, ans, vis, s, 0, 0);            //0 = i, j
        sort(ans.begin(), ans.end());
        
        return ans ;
    }
};
/*
Input:
N = 4
m[][] = {{1, 0, 0, 0},
         {1, 1, 0, 1}, 
         {1, 1, 0, 0},
         {0, 1, 1, 1}}
Output:
DDRDRR DRDDRR
Explanation:
The rat can reach the destination at 
(3, 3) from (0, 0) by two paths - DRDDRR 
and DDRDRR, when printed in sorted order 
we get DDRDRR DRDDRR.
*/


//282. STEPS BY KNIGHT                                                     {T.C = O(N^2), S.C = O(N^2)}
//BFS
class Solution 
{
    public:
    bool isValid(int i , int j , int n, vector<vector<int>>&vis){
        if(i < n && j < n && i >= 0 && j >= 0 && vis[i][j] == 0){
            return true;
        }
        return false;
    }
	int minStepToReachTarget(vector<int>&KnightPos,vector<int>&TargetPos,int n)
	{
	    int tx = TargetPos[0]-1, ty = TargetPos[1]-1;       //-1 for converting 1 based indexing to 0
	    int x = KnightPos[0]-1,  y = KnightPos[1]-1;
	    
	    //base case
	    if(x == tx && y == ty){
	        return 0;                       //0 steps needed
	    }
	    
	    vector<vector<int>>vis(n, vector<int>(n, 0));
	    queue<pair<int, int>>q;
	    q.push({x, y});
	    vis[x][y] = 1;
	    int count = 0;
	    
	    while(!q.empty()){
	        int sz = q.size();
	        count++;
	        while(sz){
	            pair<int, int>frontNode = q.front();
	            q.pop();
	            
	            int xx = frontNode.first;
	            int yy = frontNode.second;
	            
	            //all possible position knight can move
	            int ax[8] = {1, 1, -1, -1, 2, -2, 2, -2};
	            int ay[8] = {2, -2, 2, -2, 1, 1, -1, -1};
	            
	            for(int i = 0 ; i < 8 ; i++){
	                int nx = xx + ax[i];
	                int ny = yy + ay[i];
	                
	                //if we find answer after instant pushing element
	                if(nx == tx && ny == ty){
	                    return count;
	                }
	                if(isValid(nx, ny, n, vis)){
	                    vis[nx][ny] = 1;
	                    q.push({nx, ny});
	                }
	            }
	            sz--;
	        }
	    }
	    return count;
	}
};
/*
Input:
N=6
knightPos[ ] = {4, 5}
targetPos[ ] = {1, 1}
Output:
3
Explanation:
Knight takes 3 step to reach from 
(4, 5) to (1, 1):
(4, 5) -> (5, 3) -> (3, 2) -> (1, 1).
*/


//283. FLOOD FILL ALGORITHM                                                     {T.C = O(N*M), S.C = O(N*M)}
//DFS
class Solution {
public:
    void dfs(vector<vector<int>>&image, int row, int col, int newColor, vector<vector<int>>&ans, int iniClr, int delRow[], int delCol[]){
        
        ans[row][col] = newColor;
        int n = image.size();
        int m = image[0].size();
        
        for(int i = 0 ; i < 4 ; i++){
            int nRow = row + delRow[i];
            int nCol = col + delCol[i];
            
            if(nRow < n && nRow >= 0 && nCol < m && nCol >= 0 && image[nRow][nCol] == iniClr && ans[nRow][nCol] != newColor){
                dfs(image, nRow, nCol, newColor, ans, iniClr, delRow, delCol);
            }
        }
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        vector<vector<int>>ans = image;
        int initialColor = image[sr][sc];
        
        int delRow[] = {-1, 0,+1, 0};
        int delCol[] = {0, +1, 0, -1};
        
        dfs(image, sr, sc, newColor, ans, initialColor, delRow, delCol);
        
        return ans;
    }
};
/*
Input: image = {{1,1,1},{1,1,0},{1,0,1}},
sr = 1, sc = 1, newColor = 2.
Output: {{2,2,2},{2,2,0},{2,0,1}}
Explanation: From the center of the image 
(with position (sr, sc) = (1, 1)), all 
pixels connected by a path of the same color
as the starting pixel are colored with the new 
color.Note the bottom corner is not colored 2, 
because it is not 4-directionally connected to 
the starting pixel.
*/


class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
//284. CLONE A GRAPH                                                         {T.C = O(V+E), S.C = O(V)}
class Solution {
public:
    void dfs(Node* node, vector<Node*>&vis, Node* copy){
        vis[copy->val] = copy;
        for(auto it : node->neighbors){                  //traverse in adjacency list
            if(!vis[it->val]){
                Node* newNode = new Node(it->val);
                copy->neighbors.push_back(newNode);
                dfs(it, vis, newNode);
            }else{
                copy->neighbors.push_back(vis[it->val]);
            }
        }
    }
    Node* cloneGraph(Node* node) {
        //base case
        if(node == NULL){
            return NULL;
        }

        vector<Node* > vis(1000, NULL);
        Node* copy = new Node(node->val);
        dfs(node, vis, copy);

        return copy;
    }
};
/*
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
*/


//285. MAKING WIRED CONNECTIONS / NUMBER OF OPERATIONS TO MAKE CONNECTION        {T.C = O(V+E), S.C = (V)}
class Solution {
public:
    void dfs(vector<int>adj[], vector<int>&vis, int node){
        vis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, it);
            }
        }
    }
    int makeConnected(int n, vector<vector<int>>& connections) {
        vector<int>adj[n];
        int m = connections.size();             //edges
        if(m < n-1){                            //n components require n-1 edges 
            return -1;
        }
        for(int i = 0 ; i < m ; i++){
            int u = connections[i][0];
            int v = connections[i][1];

            adj[u].push_back(v);
            adj[v].push_back(u);                //undirected graph
        }

        vector<int>vis(n, 0);
        int count = 0;
        //handle all components
        for(int i = 0 ; i  < n ; i++){
            if(!vis[i]){
                count++;
                dfs(adj, vis, i);
            }
        }
        return count-1;                         //minimum numbers of additional edges need
    }
};
/*
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
Output: 2
*/


//286. WORD LADDER                                                          {T.C = O(N^2*N), S.C = O(M*N)}
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string,int>> q;
        q.push({beginWord,1});
        unordered_set<string> st(wordList.begin(),wordList.end());      //insert all elements in set
        st.erase(beginWord);
        while(!q.empty()){
            pair<string,int> frontNode=q.front();
            string word=frontNode.first;
            int steps=frontNode.second;
            q.pop();

            //check for destination 
            if(word==endWord)
                return steps;
            for(int i=0;i<word.length();i++){
                char orig=word[i];
                for(char ch='a';ch<='z';ch++){
                    word[i]=ch;
                    if(st.find(word)!=st.end()){
                        q.push({word,steps+1});
                        st.erase(word);
                    }
                }
                word[i]=orig;                                    // Revert back for the next iteration call
            }
        }
        return 0;                                                //Transformation not possible
    }
};
/*
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
*/


//287. IMPLEMENTING DIJKSTRA ALGORITM                                          {T.C = O(V^2), S.C = O(V^2)}
//NOT APPLICABLE FOR NEGATIVE WEIGHT CYCLE (similar to BFS)
/*ALGORITHM
1. Create minHeap.
2. find shortest distance of each node from current node.
*/
class Solution
{
	public:
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        //{node, minDist}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;       //minheap
        vector<int>minDist(V, INT_MAX);
        
        minDist[S] = 0;                         //first node minDistance = 0
        pq.push({S, 0});
        
        while(!pq.empty()){
            pair<int,int>topNode = pq.top();
            int node = topNode.first;
            int dis = topNode.second;
            pq.pop();
            
            for(auto it : adj[node]){
                int adjNode = it[0];
                int edgeWeight = it[1];
                
                if(dis + edgeWeight < minDist[adjNode]){
                    minDist[adjNode] = dis + edgeWeight;
                    pq.push({adjNode, minDist[adjNode]});
                }
            }
        }
        return minDist;
    }
};
/*
Input:
V = 3, E = 3
adj = {{{1, 1}, {2, 6}}, {{2, 3}, {0, 1}}, {{1, 3}, {0, 6}}}
S = 2
Output:
4 3 0
Explanation:

For nodes 2 to 0, we can follow the path-
2-1-0. This has a distance of 1+3 = 4,
whereas the path 2-0 has a distance of 6. So,
the Shortest path from 2 to 0 is 4.
The shortest distance from 0 to 1 is 1 .
*/ 


//288. TOPOLOGICAL SORT                                                          {T.C = O(V+E), S.C = O(V)}
//linear ordering of vertices such that every edge u-v, u is always before v (in adjacency list)
//USING BFS(KAHN'S ALGO)      / works only in directed acyclic graph(DAG)
class Solution
{
	public:
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    //4 data structures required =adj, indegree, queue, ans
	    vector<int>ans;
	    vector<int>inDegree(V, 0);
	    
	    //calculate all indegrees for each node
	    for(int i = 0 ; i < V ; i++){
	        for(auto it : adj[i]){
	            inDegree[it]++;
	        }
	    }
	    
	    queue<int>q;
	    //push 0 indegree's nodes in queue
	    for(int i = 0 ; i < V ; i++){
	        if(inDegree[i] == 0){
	            q.push(i);
	        }
	    }
	    
	    //do bfs
	    while(!q.empty()){
	        int frontNode = q.front();
	        q.pop();
	        ans.push_back(frontNode);
	        
	        //reduce indegree of ajacent nodes after disconnection of node
	        for(auto it : adj[frontNode]){
	            inDegree[it]--;
	            if(inDegree[it] == 0){
	                q.push(it);
	            }
	        }
	    }
	    return ans;
	}
};

//USING DFS
class Solution
{
	public:
	void dfsTopoSort(vector<int>adj[], vector<int>&vis, int &node , stack<int>&s){
	    vis[node] = 1;
	    
	    for(auto it : adj[node]){
	        if(!vis[it]){
	            dfsTopoSort(adj, vis, it, s);
	        }
	    }
	    s.push(node);                       //push backtrack node
	}
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    //4 datastructures required = adjlist, vis, stack, ans
	    vector<int>ans;
	    vector<int>vis(V, 0);
	    stack<int>s;
	    
	    for(int i = 0 ; i < V ; i++){
	        if(!vis[i]){
	            dfsTopoSort(adj, vis, i, s);
	        }
	    }
	    
	    while(!s.empty()){
	        ans.push_back(s.top());
	        s.pop();
	    }
	    return ans;
	}
};
/*
For Input: 
3 4
3 0
1 0
2 0
Output:
1
Explanation:
The output 1 denotes that the order is
valid. So, if you have, implemented
your function correctly, then output
would be 1 for all test cases.
One possible Topological order for the
graph is 3, 2, 1, 0.
*/


//289. MINIMUM TIME TO TAKEN BY EACH JOB TO BE COMPLETED GIVEN BY A DIRECTED ACYCLIC GRAPH(DAG)       {T.C = O(V+E), S.C = O(V) }
//ERROR
class Solution{
    public:
        vector<int> minimumTime(int n,vector<vector<int>> &edges,int m)
        {
            vector<int>ans(n+1);
            //create ajacancy list
            vector<vector<int>>adj(n+1);                    //1 based indexng
            for(int i = 0 ; i < edges.size() ; i++){
                int u = edges[i][0];
                int v = edges[i][1];
                
                adj[u].push_back(v);                        //directed graph
            }
            
            vector<int>inDegree(n+1, 0);
            //calculate all indegree for each vector
            for(int i = 1 ; i <= n ; i++){
                for(auto it : adj[i]){
                    inDegree[it]++;
                }
            }
            
            queue<int>q;
            //push 0 indegree's nodes in queue
            for(int i = 1 ; i <= n ; i++){
                if(inDegree[i] == 0){
                    q.push(i);
                    ans[i] = 1;              // Initialize nodes with no incoming edges to 1
                }
            }
            
            //do dfs
            while(!q.empty()){
                int frontNode = q.front();
                q.pop();
                
                //reduce indegree of ajacent nodes after disconnection of node
                for(auto it : adj[frontNode]){
                    inDegree[it]--;
                    if(inDegree[it] == 0){
                        ans[it] = ans[frontNode] + 1;
                        q.push(it);
                    }
                }
            }
            return ans;
        }
};
/*
Input:
N=10
M=13
edges[]={{1,3},{1,4},{1,5},{2,3},{2,8},{2,9},{3,6},{4,6},{4,8},{5,8},{6,7},{7,8},{8,10}}
OUTPUT
0 1 1 2 2 2 3 4 5 2 6
Output:
time[]={1,1,2,2,2,3,4,5,2,6 }
Explanation:
Start jobs 1 and 2 at the beginning and complete them at 1 unit of time. 
Since, all the jobs on which need to be completed before the jobs 3, 4, 5, and 9 are completed. So, we can start these jobs at 1st unit of time and complete these at 2nd unit of time after the completion of the dependent Job.
Similarly, 
Job 6 can only be done after the 3rd and 4th jobs are done. So, start it at the 2nd unit of time and complete it at the 3rd unit of time.
Job 7 can only be done after job 6 is done. So, you can start it at the 3rd unit of time and complete it at the 4th unit of time.
Job 8 can only be done after the 4th, 5th, and 7th jobs are done. So, start it at the 4th unit of time and complete it at the 5th unit of time.
Job 10 can only be done after the 8th job is done. So, start it at the 5th unit of time and complete it at the 6th unit of time.
*/


//290. PREREQUISITE TASKS / FIND WHETHER IT IS POSSIBLE TO FINISH ALL TASKS OR NOT FROM GIVEN DEPENDENCIES  {T.C = O(N+P), S.C = O(N+P)}
class Solution {
public:
    bool isPossible(int n, int p, vector<pair<int, int>>& prerequisites) {
        vector<int> ans;
        // Create adjacency list
        vector<vector<pair<int, int>>> adj(n); 
        //or
        //vector<list<pair<int,int>>adj(n);

        for (int i = 0; i < p; i++) {
            int u = prerequisites[i].first;
            int v = prerequisites[i].second;

            adj[u].push_back({u, v});
        }

        vector<int> inDegree(n, 0);
        // Calculate all indegree of each node
        for (int i = 0; i < n; i++) {
            for (auto it : adj[i]) {
                inDegree[it.second]++;
            }
        }

        queue<int> q;
        // Push 0 indegree's nodes in queue
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int count = 0;
        // Do BFS
        while (!q.empty()) {
            int frontNode = q.front();
            q.pop();
            count++;

            // Reduce indegree of adjacent nodes after disconnection of graph
            for (auto it : adj[frontNode]) {
                inDegree[it.second]--;
                if (inDegree[it.second] == 0) {
                    q.push(it.second);
                }
            }
        }

        if (count == n) { // Valid topological sort, so cycle not present
            return true;
        }
        return false;
    }
};
/*
Input: 
N = 4, P = 3
prerequisites = {{1,0},{2,1},{3,2}}
Output:
Yes
Explanation:
To do task 1 you should have completed
task 0, and to do task 2 you should 
have finished task 1, and to do task 3 you 
should have finished task 2. So it is possible.
*/


//291. FIND THE NUMBER OF ISLANDS                                            {T.C = O(N*M), S.C = O(N*M)}
class Solution {
  public:
    void bfs(vector<vector<char>>&grid, vector<vector<int>>&vis, int i, int j, int n, int m){
        vis[i][j] = 1;
        queue<pair<int, int>>q;
        q.push({i, j});
        
        while(!q.empty()){
            pair<int,int>frontNode = q.front();
            int row = frontNode.first;
            int col = frontNode.second;
            q.pop();
            
            //traverse in the neighbour and mark if it is island
            for(int delRow = -1 ; delRow <= 1; delRow++){
                for(int delCol = -1 ; delCol <= 1 ; delCol++){
                    int nRow = row + delRow;
                    int nCol = col + delCol;
                    
                    if(nRow >= 0 && nRow < n && nCol  >= 0 && nCol < m && grid[nRow][nCol] == '1' && !vis[nRow][nCol]){
                        vis[nRow][nCol] = 1;
                        q.push({nRow, nCol});
                    }
                }
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<int>>vis(n, vector<int>(m, 0));
        
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(!vis[i][j] && grid[i][j] == '1'){
                    count++;
                    bfs(grid, vis, i, j, n, m);
                }
            }
        }
        return count;
    }
};
/*
Input:
grid = {{0,1,1,1,0,0,0},{0,0,1,1,0,1,0}}
Output:
2
Expanation:
The grid is-
0 1 1 1 0 0 0
0 0 1 1 0 1 0 
There are two islands :- one is colored in blue 
and other in orange.
*/


//292. ALIEN DICTIONARY                                                                            {T.C = O(N*S), S.C = O(K)}
//USING topological sort
class Solution{
    public:
    vector<int>topoSort(int V , vector<int>adj[]){
        vector<int>ans;
        vector<int>inDegree(V, 0);
        
        //calculate indegrees for each nodes
        for(int i = 0 ; i < V ; i++){
            for(auto it : adj[i]){
                inDegree[it]++;
            }
        }
        
        queue<int>q;
        //push 0 indegree's in queue
        for(int i = 0 ; i < V ; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        
        //do dfs
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            
            //reduce indegree of adjacent nodes after disconnection of node
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0){
                    q.push(it);
                }
            }
        }
        return ans;
    }
    string findOrder(string dict[], int n, int k) {
        
        //create adjacency list
        vector<int>adj[k];
        for(int i = 0 ; i < n-1 ; i++){             //compare till second last elemenent is possible
            string s1 = dict[i];
            string s2 = dict[i+1];
            int len = min(s1.size(), s2.size());
            for(int j = 0 ; j < len ; j++){
                if(s1[j] != s2[j]){
                    adj[s1[j]-'a'].push_back(s2[j]-'a');
                    break;
                }
            }
        }
        
        vector<int>topo = topoSort(k, adj);
        string ans = "";
        for(auto it : topo){
            ans = ans + char(it + 'a');
        }
        return ans;
    }
};
/*
Input: 
N = 5, K = 4
dict = {"baa","abcd","abca","cab","cad"}
Output:
1
Explanation:
Here order of characters is 
'b', 'd', 'a', 'c' Note that words are sorted 
and in the given language "baa" comes before 
"abcd", therefore 'b' is before 'a' in output.
Similarly we can find other orders.
*/


/*---------------------------------------------SHORTEST DISTANCE FINDING ALGORGITHMS----------------------------------*/
//293a. DISJOINT SET                                                             {T.C = O(N), S.C = O(1)}                         
//find = findParent
int find(int a[],int u){                       //u = node
    if(a[u] == u){
        return u;
    }
    return a[u] = find(a, a[u]); 
}
void unionSet(int a[],int u,int v){
    
    int x = find(a, u);
    int z = find(a, v);
    
    if(x == z){
        return;
    }
    a[x] = z;
    /* in next question
	u = find(a, u);                            //a = parent
	v = find(a, v);
	
	if(rank[u] < rank[v]){
	    a[u] = v;
	}
	else if(rank[u] > rank[v]){
	    a[v] = u;
	}else{
	    a[v] = u;
	    rank[u]++;
	}
	*/
}
/*
Input:
N = 5, K = 4
queries[] = {{find 4},
             {find 1},
             {unionSet 3 1},
             {find 3}}
Output:
4 1 1
Explanation:
1. The parent of 4 is 4. Hence the output is 4.
2. The parent of 1 is 1. Hence the output is 1.
3. After performing unionSet 3 1, parent of 3 becomes 1,
   since, parent of 1 is currently 1 itself.
4. The parent of 3 is now 1. Hence, the output is 1.
*/

/*STRIVERS CODE FOR DISJOINT SET
class DisjointSet {
    vector<int> rank, parent, size; 
public: 
    DisjointSet(int n) {
        rank.resize(n+1, 0); 
        parent.resize(n+1);
        size.resize(n+1); 
        for(int i = 0;i<=n;i++) {
            parent[i] = i; 
            size[i] = 1; 
        }
    }

    int findUPar(int node) {
        if(node == parent[node])
            return node; 
        return parent[node] = findUPar(parent[node]); 
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u); 
        int ulp_v = findUPar(v); 
        if(ulp_u == ulp_v) return; 
        if(rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v; 
        }
        else if(rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u; 
        }
        else {
            parent[ulp_v] = ulp_u; 
            rank[ulp_u]++; 
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u); 
        int ulp_v = findUPar(v); 
        if(ulp_u == ulp_v) return; 
        if(size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v; 
            size[ulp_v] += size[ulp_u]; 
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v]; 
        }
    }
}; 
int main() {
    DisjointSet ds(7);
    ds.unionBySize(1, 2); 
    ds.unionBySize(2, 3); 
    ds.unionBySize(4, 5); 
    ds.unionBySize(6, 7); 
    ds.unionBySize(5, 6); 
    // if 3 and 7 same or not 
    if(ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n"; 
    }
    else cout << "Not same\n"; 

    ds.unionBySize(3, 7); 

    if(ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n"; 
    }
    else cout << "Not same\n"; 
	return 0;
}
*/


//293b. MINIMUM SPANNING TREE / KRUSKAL'S ALGORITHM (UNION-SET, RANK)          {T.C = O(E*LOGV), S.C = O(V^2)}
//not required adjacency list 
//required = makeset, findparent, unionset
//edge based algo 
/*ALGORITHM
1. Construct Min heap / disjoint set with 'e' edges
2. Take 1-by-1 edge and add in spanning tree (cycle should not be created)
3. Intermediate result can be disconnected
*/
class Solution
{
	public:
	void makeSet(vector<int>&parent, vector<int>&rank, int n){
	    for(int i = 0 ; i < n ; i++){
	        parent[i] = i;
	        rank[i] = 0;
	    }
	}
	
	int findParent(vector<int>&parent, int node){
	    if(parent[node] == node){
	        return node;
	    }
	    return parent[node] = findParent(parent, parent[node]);           //store -> parent[node] called rank compression
	}
	
	void unionSet(vector<int>&parent, vector<int>&rank , int u, int v){
	    u = findParent(parent, u);
	    v = findParent(parent, v);
	    
	    if(rank[u] < rank[v]){
	        parent[u] = v;                               //connect small tree to big tree
	    }
        else if(rank[u] > rank[v]){
            parent[v] = u;
        }else{  //rank[u] == rank[v]
            parent[v] = u;
            rank[u]++;                                   //increament rank of rightside / parentnode
        }
	}
	
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        //extract edges from adjacent list
        vector<vector<int>>edges;
        for(int i = 0 ; i < V ; i++){
            for(auto it : adj[i]){
                edges.push_back({i, it[0], it[1]});      //starting vertex, destination vertex, weight
            }
        }
        
        //lamda function to sort on the basis of weights (index 2)
        sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
        });
        vector<int>parent(V);
        vector<int>rank(V);
        makeSet(parent, rank, V);
        
        int minWeight = 0;
        
        for(int i = 0 ; i < edges.size() ; i++){
            int u = findParent(parent, edges[i][0]);
            int v = findParent(parent, edges[i][1]);
            int wt = edges[i][2];
            
            if(u != v){
                minWeight += wt;
                unionSet(parent, rank, u, v);
            }
        }
        return minWeight;
    }
};
/*
Input:
3 3
0 1 5
1 2 3
0 2 1
Output:
4
Explanation:
The Spanning Tree resulting in a weight
of 4 is shown above.
*/


//294. PRIM'S ALORITHM                                                                {T.C = O(E*LOGV), S.C = O(V^2)}
//required adjacency list
//vertex based
//Data Structures = key(n, INT_MAX), mst(n, false), parent(n, -1)
/*ALGORITHM
1. Choose any vertex
2. Take minimum weight path.
3. Take care of previous paths as well.
4. Cycle should not be created.
5. Intermediate result is always connected
*/
vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>> &g)
{
    //create adjacancy list
    unordered_map<int,list<pair<int,int>>>adj;
    for(int i = 0 ; i < g.size() ; i++){
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;

        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    //create require datastructures with initialization
    vector<int>key(n+1, INT_MAX);
    vector<bool>mst(n+1, false);
    vector<int>parent(n+1, -1);

    //main algo
    key[1] = 0;
    parent[1] = -1;

    for(int i = 1 ; i < n ; i++){
        int mini = INT_MAX;
        int u;

        //find mini node
        for(int v = 1; v <= n; v++){
            if(mst[v] == false && key[v] < mini){
                u = v;
                mini  = key[v];
            }
        }

        //mark mini node as true
        mst[u] = true;

        //check its adjacent node
        for(auto i : adj[u]){
            int v = i.first;
            int w = i.second;

            if(mst[v] == false && w < key[v]){
                parent[v] = u;
                key[v] = w;
            }
        }
    }

    //create ans/result
    vector<pair<pair<int, int>, int>>result;
    for(int i = 2 ; i <= n ; i++){
        result.push_back({{parent[i],i},key[i]});
    }

    return result;
}
/*
Sample Input 1 :
1
5 14
1 2 2
1 4 6
2 1 2
2 3 3
2 4 8
2 5 5
3 2 3
3 5 7
4 1 6
4 2 8
4 5 9
5 2 5
5 3 7
5 4 9
Sample Output 1 :
1 2 2
1 4 6
2 3 3
2 5 5
*/


//295. TOTAL NUMBER OF SPANNING TREES IN A GRAPH
//if complete graph then spanning trees = N^(N-2){CAYLEY'S FORMULA}


//296. NEGATIVE WEIGHT CYCLE / IMPLEMENT BELLMAN FORD ALGORITHM                      {T.C = O(N*M), S.C = O(N)}
/*ALGORTIHM
1. Relax every edges - (v-1)times
2. Relax one more time for check -ve cycle present or not
*/
class Solution {
public:
    int isNegativeWeightCycle(int n, vector<vector<int>>& edges) {
        vector<int> minDist(n, 1e8);               //INT_MAX throughs error
        minDist[0] = 0;

        // n-1 times
        for (int i = 0; i < n; i++) {
            // Traverse the edges using loop variable 'j'
            for (int j = 0; j < edges.size(); j++) {
                int u = edges[j][0];
                int v = edges[j][1];
                int w = edges[j][2];

                if (minDist[u] != INT_MAX && minDist[u] + w < minDist[v]) {
                    minDist[v] = minDist[u] + w;
                }
            }
        }

        // 1 more time for checking negative cycle
        for (int j = 0; j < edges.size(); j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];

            if (minDist[u] != INT_MAX && minDist[u] + w < minDist[v]) {
                return 1; // Negative cycle present
            }
        }
        return 0; // Negative cycle not present
    }
};
/*
Input: n = 3, edges = {{0,1,-1},{1,2,-2},
{2,0,-3}}
Output: 1
Explanation: The graph contains negative weight
cycle as 0->1->2->0 with weight -1,-2,-3.
*/


//297. FLOYD WARSHALL ALGORTITHM / BRUTE FORCE ALGO                             {T.C = O(N^3), S.C = O(1)}                    
class Solution {
  public:
	void shortest_distance(vector<vector<int>>&matrix){
	    int n = matrix.size();
	    
	    //reset -1 to INT_MAX 
	    for(int i = 0 ; i <  n ; i++){
	        for(int j = 0 ; j < n ; j++){
	            if(matrix[i][j] == -1){
	                matrix[i][j] = 1e9;                    //INT_MAX through error
	            }
	            if(i == j){
	                matrix[i][j] = 0;
	            }
	        }
	    }
	    
	    //main algo
	    for(int k = 0 ; k < n ; k++){
	        for(int i = 0 ; i < n ; i++){
	            for(int j = 0 ; j < n ; j++){
	                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
	            }
	        }
	    }
	    
	    //reset INT_MAX to  -1 (question requirements)
	    for(int i = 0 ; i < n ; i++){
	        for(int j = 0 ; j < n ; j++){
	            if(matrix[i][j] == 1e9){
	                matrix[i][j] = -1;
	            }
	        }
	    }
	}
};
/*
Input: matrix = {{0,1,43},{1,0,6},{-1,-1,0}}
Output: {{0,1,7},{1,0,6},{-1,-1,0}}
Explanation: We can reach 2 from 0 as 0->1->2
and the cost will be 1+6=7 which is less than 
43.
*/

/*--------------------------------------------------------------------------------------------------------------------*/


//298. TRAVELLING SALESMAN PROBLEM


//299. M-COLORING PROBLEM                                                            {T.C = O(M^N), S.C = O(N)}   
class Solution {
public: 
    bool isSafe(bool graph[101][101], int m, int n, vector<int>& vis, int node, int c) {
        for (int i = 0; i < n; i++) {
            if (node != i && graph[node][i] && vis[i] == c) {
                // If the current node is connected to another node (graph[node][i] is true)
                // and both nodes have the same color (vis[i] == c), it's not safe.
                return false;
            }
        }
        return true;
    }

    bool dfs(bool graph[101][101], int m, int n, vector<int>& vis, int node) {
        if (node == n) {                            //reached the end of the graph
            return true;
        }

        for (int c = 1; c <= m; c++) {
            vis[node] = c; // Mark the node with the current color.
            
            if (isSafe(graph, m, n, vis, node, c)) {
                if (dfs(graph, m, n, vis, node + 1)) {
                    return true;
                }
            }
        }
        vis[node] = 0; // Backtrack by resetting the color of the current node.
        return false;
    }

    bool graphColoring(bool graph[101][101], int m, int n) {
        vector<int> vis(n, 0);           // Initialize a vector to store node colors, initially all set to 0 (no color).
        return dfs(graph, m, n, vis, 0); // Start DFS from the first node (index 0).
    }
};

/*
Input:
N = 4
M = 3
E = 5
Edges[] = {(0,1),(1,2),(2,3),(3,0),(0,2)}
Output: 1
Explanation: It is possible to colour the
given graph using 3 colours.
*/


//300. SNAKE AND LADDER GAME                                                   {T.C = O(N^N), S.C = O(N^N)}
//USING BFS
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        vector<vector<int>>vis(n, vector<int>(n, 0));
        queue<int>q;
        q.push(1);
        vis[n-1][0] = 1;
        int move = 0;

        while(!q.empty()){
            int sz = q.size();
            for(int i = 0 ; i < sz ; i++){
                int frontNode = q.front();
                q.pop();
                //base case
                if(frontNode == n*n){
                    return move;
                }
                for(int j = 1 ; j <= 6 ; j++){
                    int nextCell = frontNode + j;
                    if(nextCell > n*n){
                        break;
                    }

                    int nextRow = n-1 - (nextCell - 1)/n;
                    int nextCol = (nextCell-1) % n;

                    if(nextRow % 2 == n % 2){
                        nextCol = n-nextCol-1;
                    }

                    if(!vis[nextRow][nextCol]){
                        vis[nextRow][nextCol] = 1;
                        if(board[nextRow][nextCol] != -1){       // If it's a ladder r snake cell:
                            q.push(board[nextRow][nextCol]);     // Move to the cell indicated by the ladder or snake
                        }else{
                            q.push(nextCell);
                        }
                    }
                }
            }
            move++;
        }
        return -1;
    }
};
/*
Input: board = [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
Output: 4
Explanation: 
In the beginning, you start at square 1 (at row 5, column 0).
You decide to move to square 2 and must take the ladder to square 15.
You then decide to move to square 17 and must take the snake to square 13.
You then decide to move to square 14 and must take the ladder to square 35.
You then decide to move to square 36, ending the game.
This is the lowest possible number of moves to reach the last square, so return 4.
*/


//301a. BRIDGE EDGE IN A GRAPH /CHECK BRIDGE OR NOT                                           {T.C = O(V+E), S.C = O(V)}      
//USING BFS
class Solution
{
	public:
    int isBridge(int V, vector<int> adj[], int c, int d) 
    {
        //removing edge connection between c and d
        adj[c].erase(find(adj[c].begin(), adj[c].end(), d));
        adj[d].erase(find(adj[d].begin(), adj[d].end(), c));
        
        //simple BFS
        vector<bool>vis(V, false);
        queue<int>q;
        q.push(c);
        vis[c] = true;
        
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            
            for(auto it : adj[frontNode]){
                if(!vis[it]){
                    vis[it] = true;
                    q.push(it);
                }
            }
        }
        if(vis[d]){                       //after removing edge visit d it means that is not bridge edge
            return 0;
        }
        return 1;
    }
};
/*
Input:
c = 1, d = 2
Output:
1
Explanation:
From the graph, we can clearly see that
blocking the edge 1-2 will result in 
disconnection of the graph. So, it is 
a Bridge and thus the Output 1.
*/


//301b. FINDING ALL BRIDGES IN A GRAPH / CRITICAL CONNECTIONS IN A NETWORK              {T.C = O(V+E), S.C = O(V+E)}  
//USING DFS
class Solution {
public:
    void dfs(vector<vector<int>>& adj, int& timer, vector<int>& disc, vector<int>& low, vector<int>& vis, int parent, vector<vector<int>>& ans, int node) {
        vis[node] = 1;
        disc[node] = low[node] = timer++;

        for (auto it : adj[node]) {
            if (it == parent) {
                continue;
            }
            if (!vis[it]) {
                dfs(adj, timer, disc, low, vis, node, ans, it); // Pass 'node' as the parent
                low[node] = min(low[node], low[it]);

                // Check if the edge is a bridge or not
                if (low[it] > disc[node]) { // This is a bridge edge
                    vector<int> temp;
                    temp.push_back(node);
                    temp.push_back(it);
                    ans.push_back(temp);
                }
            }
            else { // Back edge (node already visited)
                low[node] = min(low[node], disc[it]);
            }
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Create adjacency list
        vector<vector<int>> adj(n);

        for (auto& conn : connections) {
            int u = conn[0];
            int v = conn[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Initialize data structures
        int timer = 0;
        vector<int> disc(n, -1);
        vector<int> low(n, -1);
        vector<int> vis(n, 0);

        vector<vector<int>> ans;
        // Simple DFS
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(adj, timer, disc, low, vis, -1, ans, i); // Pass -1 as the parent for the initial node
            }
        }
        return ans;
    }
};
/*
Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
*/


//302. STRONGLY CONNECTED COMPONENTS / KOSARAJU'S ALGO                       {T.C = O(V+E), S.C = O(V+E)}
//ALGORITHM
/*
1. Sort the adjacency list using topological sort
2. create a transpose graph
3. dfs call on basis of above ordering (reverse dfs)
*/
class Solution
{
	public:
	void dfs(vector<vector<int>>&adj, vector<int>&vis, stack<int>&s, int node){
	    vis[node]  = 1;
	    
	    for(auto it : adj[node]){
	        if(!vis[it]){
	            dfs(adj, vis, s, it);
	        }
	    }
	    //topo sort logic
	    s.push(node);
	}
	void revDFS(vector<vector<int>>&transpose, vector<int>&vis, int node){
	    vis[node] = 1;
	    
	    for(auto it : transpose[node]){
	        if(!vis[it]){
	            revDFS(transpose, vis, it);
	        }
	    }
	}
    int kosaraju(int V, vector<vector<int>>& adj)
    {
        //step1 sort the adjacency list using topological sort
        vector<int>vis(V, 0);
        stack<int>s;
        for(int i = 0 ; i < V ; i++){
            if(!vis[i]){
                dfs(adj, vis, s, i);
            }
        }
        
        //step2 create a transpose graph
        vector<vector<int>>transpose(V);
        for(int i = 0 ; i < V ; i++){
            vis[i] = 0;                                    //reinitialize visited array
            for(auto it : adj[i]){
                transpose[it].push_back(i);
            }
        }
        
        //step3 dfs call on basis of above ordering (reverse dfs)
        int count = 0;
        while(!s.empty()){
            int top = s.top();
            s.pop();
            if(!vis[top]){
                count++;
                revDFS(transpose, vis, top);
            }
        }
        return count;
    }
};
/*
For Input: 
5 5
1 0
0 2
2 1
0 3
3 4
Your Output: 
3
*/


//303. BIPARTITE GRAPH                                                         {T.C = O(V+E), S.C = O(V)}
//The given graph can be colored in two colors so, it is a bipartite graph.
class Solution {
public:
    bool bfs(vector<int> adj[], vector<int>& clr, int node) {
        queue<int> q;
        q.push(node);
        clr[node] = 0; // marked with color 0; another color is 1

        while (!q.empty()) {
            int frontNode = q.front();
            q.pop();

            for (auto it : adj[frontNode]) {
                if (clr[it] == -1) {                          // if adjacent node is not filled
                    clr[it] = 1 - clr[frontNode];             // Alternate between colors 0 and 1
                    q.push(it);
                } else if (clr[it] == clr[frontNode]) {       // adjacent color match not bipartite
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite(int V, vector<int> adj[]) {
        vector<int> clr(V, -1);
        // handle disconnected components
        for (int i = 0; i < V; i++) {
            if (clr[i] == -1) {
                if (!bfs(adj, clr, i)) {
                    return false;
                }
            }
        }
        return true;
    }
};
/*
For Input: 
4 4
0 2
0 3
1 3
2 3
Your Output: 
0
*/

//304. NEGATIVE WEIGHT CYCLE / IMPLEMENT BELLMAN FORD ALGORITHM                      {T.C = O(N*M), S.C = O(N)}
//same as 296
/*ALGORTIHM
1. Relax every edges - (v-1)times
2. Relax one more time for check -ve cycle present or not
*/
class Solution {
public:
    int isNegativeWeightCycle(int n, vector<vector<int>>& edges) {
        vector<int> minDist(n, 1e8);               //INT_MAX throughs error
        minDist[0] = 0;

        // n-1 times
        for (int i = 0; i < n; i++) {
            // Traverse the edges using loop variable 'j'
            for (int j = 0; j < edges.size(); j++) {
                int u = edges[j][0];
                int v = edges[j][1];
                int w = edges[j][2];

                if (minDist[u] != INT_MAX && minDist[u] + w < minDist[v]) {
                    minDist[v] = minDist[u] + w;
                }
            }
        }

        // 1 more time for checking negative cycle
        for (int j = 0; j < edges.size(); j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];

            if (minDist[u] != INT_MAX && minDist[u] + w < minDist[v]) {
                return 1; // Negative cycle present
            }
        }
        return 0; // Negative cycle not present
    }
};
/*
Input: n = 3, edges = {{0,1,-1},{1,2,-2},
{2,0,-3}}
Output: 1
Explanation: The graph contains negative weight
cycle as 0->1->2->0 with weight -1,-2,-3.
*/


//305. LONGEST PATH IN A DIRECTED ACYCLIC GRAPH                                     {T.C = O(V+E), S.C = O(V)}
//USING BFS (SIMILAR TO DIJKSTRA'S BUT DIFFERENT)
class Solution
{
    public:
    vector <int> maximumDistance(vector<vector<int>> edges,int v,int e,int src)
    {
        //create adjacency list (u, v, w)
        vector<vector<vector<int>>>adj(v);
        
        for(auto it : edges){
            adj[it[0]].push_back({it[1], it[2]});
        }
        
        //BFS
        queue<vector<int>>q;                   //node, weight/dist
        q.push({src, 0});
        vector<int>maxDist(v, INT_MIN);
        maxDist[src] = 0;
        vector<int>vis(v, 0);
        vis[src] = 1;
        
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            
            for(auto it : adj[frontNode[0]]){
                if(maxDist[it[0]] < maxDist[frontNode[0]] + it[1]){             //it[1] == weight
                    maxDist[it[0]] = maxDist[frontNode[0]] + it[1];
                    q.push({it[0], maxDist[it[0]]});
                }
            }
            /*or
            for (auto it : adj[frontNode[0]]) {
                int neighbor = it[0];
                int weight = it[1];
                int newDistance = maxDist[frontNode[0]] + weight;

                if (maxDist[neighbor] < newDistance) {
                    maxDist[neighbor] = newDistance;
                    q.push({ neighbor, newDistance });
                }
            }
            */
        }
        return maxDist;
    }
};
/*
Input:
N=6
M=10
SRC=1
edges[]={{0,1,5},{0,2,3},{1,3,6},{1,2,2},{2,4,4},{2,5,2},{2,3,7},{3,5,1},{3,4,-1},{4,5,-2}}
Output:
distance[]={INF,0,2,9,8,10}
Explanation:
The vertex zero is not reachable from vertex 1 so its distance is INF, for 2 it is 2, for 3 it is 9, the same goes for 4 and 5.
*/


//306. JOURNEY TO THE MOON                                                   {T.C = O(V+E), S.C = O(V)}
void dfs(vector<vector<int>>& adj, vector<int>& vis, int& counter, int node) {
    vis[node] = 1;
    counter++;
    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs(adj, vis, counter, it);
        }
    }
}

int journeyToMoon(int n, vector<vector<int>>& astronaut) {
    // Create adjacency list
    vector<vector<int>> adj(n);
    for (int i = 0; i < astronaut.size(); i++) {
        int u = astronaut[i][0];
        int v = astronaut[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // DFS
    vector<int> vis(n, 0);
    vector<int> components; // Store the sizes of connected components

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int counter = 0;
            dfs(adj, vis, counter, i);
            components.push_back(counter);
        }
    }

    int val = n * (n - 1) / 2; // nC2 (2 person move on moon at a time)
    for (int i = 0; i < components.size(); i++) {
        int x = (components[i] * (components[i]-1)) / 2;        //same component's element not count eg = nC2 - iC2
        val = val-x;
    }

    return val;
}
/*
Sample Input 0

5 3
0 1
2 3
0 4
Sample Output 0
6
*/


//307. CHEAPEST FLIGHTS WITH IN A 'K' STEPS                                        {T.C = O(E), S.C = O(V)}
//doesn't matter cyclic or not
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        //create adjacency list

        vector<pair<int,int>>adj[n];
        //or
        // vector<vector<pair<int,int>>>adj(n);

        for(auto it : flights){
            adj[it[0]].push_back({it[1] ,it[2]});
        }

        //BFS/DIJKSTRA'S on basis of stop without priorityqueue
        queue<pair<int, pair<int,int>>>q;
        //stops, node, price/cost
        q.push({0, {src, 0}});
        vector<int>minPrice(n, INT_MAX);
        minPrice[src] = 0;

        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();

            int stops = frontNode.first;
            int node = frontNode.second.first;
            int cost = frontNode.second.second;

            if(stops > k){
                continue;
            }
            for(auto it : adj[node]){         //node not frontNode
                int adjNode = it.first;
                int edWeight = it.second;

                if(minPrice[adjNode] > cost + edWeight && stops <= k){
                    minPrice[adjNode] = cost + edWeight;
                    q.push({stops + 1, {adjNode, cost+edWeight}});
                }
            }
        }
        if(minPrice[dst] == INT_MAX){
            return -1;
        }
        return minPrice[dst];
    }
};
/*
Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
Output: 700
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
*/


//308. OLIVER AND THE GAME / EULER TIMER ALGO                                  {T.C = O(V+E), S.C = O(V+E)}
vector<int> inTime;
vector<int> ouTime;
int timer = 1;

void resize(int n) {
    inTime.resize(n + 1);
    ouTime.resize(n + 1);
}

void dfs(vector<int> adj[], int src, int parent) {
    inTime[src] = timer++;
    for (auto it : adj[src]) {
        if (it != parent) {
            dfs(adj, it, src); // You should pass `it` as the source and `src` as the parent
        }
    }
    ouTime[src] = timer++;
}

bool checkSubtree(int x, int y) {
    return (inTime[x] < inTime[y] && ouTime[x] > ouTime[y]);
}

int main() {
    int n;
    cin >> n;
    timer = 1;
    resize(n);
    vector<int> adj[n + 1];
    for (int i = 0; i < n - 1; i++) { // n-1 = edges
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(adj, 1, 0); // 1 = src, 0 = parent
    int queries;
    cin >> queries;
    for (int i = 0; i < queries; i++) {
        int type, x, y; // type(1 = away, 0 = toward king), oliver(culprit), bob(finder)
        cin >> type >> x >> y; // Initialize type, x, and y from input
        if (type == 0) {
            if (checkSubtree(x, y)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if (type == 1) {
            if (checkSubtree(y, x)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}
/*
Input
9
1 2
1 3
2 6
2 7
6 9
7 8
3 4
3 5
5
0 2 8
1 2 8
1 6 5
0 6 5
1 9 1
Output
YES
NO
NO
NO
YES
*/


//309 / 310. WATER AND JUG PROBLEM                                                   {T.C = O(d), s.c = o(1)}
class Solution {
public:
    bool canMeasureWater(int m, int n, int d) {     //m = jug1Capacity, n = jug2Capacity, d = targetCapacity
        //base case
	    if(m + n < d){
	        return false;
	    }

	    vector<int>delAmount = {m, -m, n, -n};
	    set<int>vis;
	    queue<int>q;
	    q.push(0);
	    vis.insert(0);
	    
	    while(!q.empty()){
	        int frontNode = q.front();
	        q.pop();
	        for(auto it : delAmount){
	            int total = frontNode + it;
	            if(total == d){
	                return true;
	            }
	            if(total < 0 || total > m + n){
	                continue;
	            }
	            if(vis.find(total) == vis.end()){
	                q.push(total);
	                vis.insert(total);
	            }
	        }
	    }
	    return false;
    }
};
/*
Input: jug1Capacity = 2, jug2Capacity = 6, targetCapacity = 5
Output: false
*/


//311. PATH OF GREATER THAN EQUAL TO K LENGTH                                      {T.C = O(V+E), S.C = O(V+E)}
//USING DFS
class Solution {
public:
    bool dfs(vector<pair<int, int>>adj[], vector<int>&vis, int k , int node, int len){
        if(len >= k){
            return true;
        }
        
        vis[node] = 1;
        
        for(auto it : adj[node]){
            if(!vis[it.first]){
                bool tempAns = dfs(adj, vis, k, it.first, len+it.second);
                if(tempAns){
                    return true;
                }
            }
        }
        vis[node] = 0;                           //backtrack
        return false;
    }
    bool pathMoreThanK(int V, int E, int k, int *a) 
    { 
        //create adjacency list
        vector<pair<int, int>>adj[V];
        for(int i = 0 ; i < 3*E ; i += 3){
            int src = a[i];
            int dst = a[i+1];
            int wgt = a[i+2];
            
            adj[src].push_back({dst, wgt});
            adj[dst].push_back({src, wgt});      //undirected graph
        }
        
        vector<int>vis(V, 0);
        bool ans = dfs(adj, vis, k, 0, 0);             //0 = node, 0 = length
        if(ans){
            return true;
        }
        return false;
    } 
};
/*
Input:
V = 4 , E = 3 and K = 8
A[] = [0, 1, 5, 1, 2, 1, 2, 3, 1]
Output: 0
Explanation:
There exists no path which has a distance 
of 8. 
*/


//312. M-COLORING PROBLEM                                                           {T.C = O(M^N), S.C = O(N)}
//same as (299)
class Solution {
public:
    bool isSafe(bool graph[101][101], int m, int n, vector<int>& vis, int node, int c) {
        for (int i = 0; i < n; i++) {
            if (node != i && graph[node][i] && vis[i] == c) {
                return false;
            }
        }
        return true;
    }

    bool dfs(bool graph[101][101], int m, int n, vector<int>& vis, int node) {
        if (node == n) {
            return true;
        }
        
        for (int c = 1; c <= m; c++) {
            vis[node] = c;
            if (isSafe(graph, m, n, vis, node, c)) {
                if (dfs(graph, m, n, vis, node + 1)) {
                    return true;
                }
            }
        }
        vis[node] = 0; // Backtrack
        return false;
    }

    bool graphColoring(bool graph[101][101], int m, int n) {
        vector<int> vis(n, 0);
        return dfs(graph, m, n, vis, 0); // 0 == starting index
    }
};
/*
Input:
N = 4
M = 3
E = 5
Edges[] = {(0,1),(1,2),(2,3),(3,0),(0,2)}
Output: 1
Explanation: It is possible to colour the
given graph using 3 colours.
*/


//313. MINIMUM EDGES                                                               {T.C = O(E*LOGV), S.C = O(E+V)}
class Solution{
    public:
        int minimumEdgeReversal(vector<vector<int>> &edges,int n,int src,int dst)
        {
            vector <vector <vector<int>>> adj(n+1);
            for(auto i:edges){
                adj[i[0]].push_back({i[1],0});
                adj[i[1]].push_back({i[0],1});
            }
            //apply dijkstra's algo
            priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
            pq.push({0,src});
            vector <int> vis(n+1);
            while(!pq.empty()){
                int node = pq.top().second,cost = pq.top().first;
                pq.pop();
                if(node == dst) return cost;
                if(vis[node]) continue;
                vis[node] = 1;
                for(auto it:adj[node]){
                    int next = it[0],nc = cost+it[1];
                    if(!vis[next])
                        pq.push({nc,next});
                }
            }
            return -1;
        }
};
/*
Input:
N=3
M=2
edges[][]={{1,2},{3,2}}
src=1
dst=3
Output:
1
Explanation:
Reverse the edge 3->2.
*/


//314. PATHS TO TRAVEL EACH NODES USING EACH EDGE(SEVEN BRIDGES)


//315. VERTEX COVER PROBLEM


//EULER CIRCUIT
/*
walk = any random traversal in a graph (V, E can be repeated)
trail = a walk in which no E repeated ( V can be repeated)

Euler Circuit-
A trail starts and ends at same vertex.
    condition
        1. start node == ending node
        2. every edge must be visited only once
Euler Graph-
Follows properties of euler circuit
    1. All edges in a graph must be present in single component (more component vailid but all edges in 1 component only) 
    
An undirected and connected graph has Eulerian cycle if “all vertices have even degree“.

Eulerian Path / or Semi-Eulerian 
An Eulerian path is a path in a graph that visits every edge exactly once. It does not necessarily have to start and end at the same vertex.

*/


//316. CHINESE POSTMAN OR ROUTE INSPECTION / EULER CIRCUIT AND PATH                                                   {T.C = O(V), S.C = O(1)}
class Solution {
public:
	int isEularCircuit(int V, vector<int>adj[]){
	    int count = 0;
	    //check indegree of each vertex
	    for(int i = 0 ; i < V ; i++){
	        if(adj[i].size() % 2 != 0){        //adj[i].size = no. of edges connected to a vertex (indegree)
	            count++;                       //count odd indegree of total
	        }
	    }
	    if(count == 0){                        //0 vertexes with odd indegrees (Eulerian circuit)
	        return 2;
	    }
	    else if(count == 2){                   //2 vertexes with odd indegrees (Eulerian paht/semi Eulerian)
	        return 1; 
	    }else{
	        return 0;
	    }
	}
};
/*
For Input: 
3 3 
0 1 
0 2 
1 2
Your Output: 
2
*/


//317. NUMBER OF TRIANGLES IN DIRECTED AND UNDIRECTED GRAPH                     {T.C = O(V^3), S.C = O(V^2)}
vector<int> countTriangles(int v1, vector<vector<int>>& edgeListOfDirectedGraph, int v2,
			vector<vector<int>>& edgeListOfUnDirectedGraph) {
	
	//creating adjacency list of both directed and undirected
	vector<vector<int>>adjDr(v1, vector<int>(v1, 0));
	vector<vector<int>>adjUn(v1, vector<int>(v1, 0));

	//now create single adjacency matrix by both adjacency list
	for(auto it : edgeListOfUnDirectedGraph){
		adjDr[it[0]][it[1]] = 1;
		
		adjUn[it[0]][it[1]] = 1;
		adjUn[it[1]][it[0]] = 1;
	}

	int drTr = 0;
	int unTr = 0;
	
	for(int i = 0 ; i < v1 ; i++){
		for(int j = 0 ; j < v1 ;j++){
			for(int k = 0 ; k < v1 ; k++){
				if(adjDr[i][j] && adjDr[j][k] && adjDr[k][i]){
					drTr++;
				}
				if(adjUn[i][j] && adjUn[j][k] && adjUn[k][i]){
					unTr++;
				}
			}
		}
	}
	return {drTr/3, unTr/6};            //from 1 triangle 3 directed & 6 undirected triangle can form
}
/*
Sample Input 1 :
1
4 5
0 1 
1 2
2 0
0 3
3 2
4 5
0 1 
1 2
2 0
0 3
3 2
Sample Output 1 :
2 2
*/


//318. MINIMISE THE CASHFLOW AMONG A GIVEN SET OF FRIENDS WHO HAVE BORROWED MONEY FROM EACH OTHER


//319. TWO CLIQUE PROBLEM                                                             {T.C = O(V+E), S.C = O(V)}  
//error
bool bfs(vector<vector<int>>& adj, vector<int>& vis, int node) {
    queue<int> q;
    q.push(node);
    vis[node] = 0;  // marked with 0, another color is 1

    while (!q.empty()) {
        int frontNode = q.front();
        q.pop();

        for (auto it : adj[frontNode]) {
            if (!vis[it]) {
                vis[it] = 1 - vis[frontNode];
                q.push(it);
            } else if (vis[it] == vis[frontNode]) {
                return false;
            }
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>>& adj, int n) {
    vector<int> vis(n, -1);

    // Handle disconnected graph
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (!bfs(adj, vis, i)) {
                return 0;
            }
        }
    }
    return 1;
}

bool twoCliques(int n, vector<vector<int>>& edgeList) {
    // Create adjacency list
    vector<vector<int>> adj(n);

    for (int i = 0; i < edgeList.size(); i++) {
        int u = edgeList[i][0];
        int v = edgeList[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Create reverse adjacency list
    vector<vector<int>> revAdj(n);

    for (int u = 0; u < n; u++) {
        for (int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];

            revAdj[v].push_back(u);
        }
    }

    return isBipartite(revAdj, n);
}
/*
Sample Input 1 :
2
4 2
0 1
2 3
5 4
0 1
0 2
0 3
2 4
Sample Output 1 :
1
0
*/


/*------------------------------------------------------  THE END   ---------------------------------------------------*/