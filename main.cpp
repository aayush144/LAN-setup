#include <bits/stdc++.h>
using namespace std;

// coordinate class
class coor{
public:
	double x, y;
	coor(){}
	void input(){
		cin >> x >> y ;
	}

	friend double dist(coor A, coor B);
};


double dist(coor A, coor B){
	return sqrt((pow(A.x - B.x,2) + pow(A.y - B.y,2)));
}


int find(int x, int dsu[]){
	if(dsu[x] < 0)return x;
	return dsu[x] = find(dsu[x], dsu);
}

void merge(int x, int y, int dsu[]){
	x = find(x, dsu);
	y = find(y, dsu);
	if(x == y)return;
	dsu[x] = y;
}

vector<pair<coor,coor>> kruskal(coor points[], int n){
	int dsu[n];
	memset(dsu, -1, sizeof(dsu));
	vector<pair<double, pair<int,int>>> g;

	// Making of the complete Graph
	for(int i = 0; i<n; i++){
		for(int j = i + 1; j<n; j++){
			g.push_back({dist(points[i], points[j]), {i,j}});
		}
	}


	// Applying krushal's Algorithm
	sort(g.begin(), g.end());
	vector<pair<coor,coor>> edges;

	for(auto i : g){
		int u = i.second.first;
		int v = i.second.second;

		u = find(u, dsu);
		v = find(v, dsu);
		if(u == v)continue;
		edges.push_back({points[u], points[v]});
		merge(u, v, dsu);
	}

	return edges;


}



int main(){
	int n;
	double cost;
	double total_cost = 0;

	vector<pair<coor,coor>> edges;


	cout << "Enter no of points " << endl;
	cin >> n;

	coor points[n];
	for(int i = 0; i<n; i++){
		points[i].input();
	}
	cout << "Enter cost of LAN wire per meter" << endl;
	
	cin >> cost;


	edges = kruskal(points, n);


	for(auto edge : edges){
	total_cost += cost * (dist(edge.first, edge.second));
	}

	cout << "Min cost of laying the LAN wire = " << total_cost << endl << endl;
	cout << "The points should be connected as follows to get the minmun totalcost " << endl;
	for(auto edge : edges){
		coor u = edge.first, v = edge.second;
		cout << "{" << u.x << ", " << u.y << "} <--> {" << v.x << ", " << v.y << "}" << endl;
	}
}
