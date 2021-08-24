//MST.cpp file
//Description: This program finds mst from a file in which edges of a graph are given
//Author: Aaryan Gupta
//Creation Date: July 22, 2021

#include<iostream>
#include<vector>
#include<fstream>
#include<stack>

using namespace std;

//Edge class that corresponds to the edge of the vertices
class Edge{
	public:

		Edge(){

		}
		~Edge(){
			
		}
		int city1, city2, dist;
};


//this method checks if a graph is still connected if a node is removed
bool isConnected(vector<Edge> v, bool* arr, int pos, int n){

	for(int i = 0; i < n; i++){
		arr[i] = false;
	}

	stack<int> s;
	s.push(0);

	while(!s.empty()){

		int node = s.top();
		s.pop();

		if(arr[node] != true){
			for(int i = 0; i < (int)v.size(); i++){
				if(i != pos){
					if(v[i].city1 == node){
						s.push(v[i].city2);
					}
					else if(v[i].city2 == node){
						s.push(v[i].city1);
					}
				}
			}
			arr[node] = true;
		}

	}

	for(int i = 0; i < n; i++){
		if(arr[i] == false){
			return false;
		}
	}

	return true;



}



//reverse kruskal method which creates a minimum spanning tree by removing max nodes one by one.
void reverseKruskal(vector<Edge> v, int n){

	int i = 0;
	bool* arr = new bool[n];


	while(i < (int)v.size()){

		Edge tmp = v[i];

		if(isConnected(v, arr, i, n)){
			v.erase(v.begin()+i);
			
			//print this edge as it is removed
			cout << tmp.city1 << " " << tmp.city2 << " " << tmp.dist << endl;
		} 
		else{
			i++;
		}
	}

	int sum = 0;
	cout << endl;
	cout << "MST:" << endl;

	for(int j = 0; j < (int)v.size(); j++){
		cout << v[j].city1 << " " << v[j].city2 << " " << v[j].dist << endl;
		sum += v[j].dist;
	}

	cout << "Total distance: " << sum << endl;




}




//this function reads the file and call other functions
int main(){

	vector<Edge> v;
	int n;

	//reading the edges from the text file
	ifstream in;
	in.open("sparce7.txt");
	if(in.is_open()){
		in >> n;
		while(!in.eof()){
			Edge tmp;
			in >> tmp.city1;
			in >> tmp.city2;
			in >> tmp.dist;

			//inserting the edge in a sorted order
			bool done = false;
			if(v.size() == 0){
				v.push_back(tmp);
			}
			else{
				for(int i = 0; i < (int)v.size(); i++){
					if(tmp.dist >= v[i].dist){
						v.insert(v.begin() + i, tmp);
						done = true;
						break;
					}
				}
				if(!done){
					v.push_back(tmp);
				}
				done = true;
			}
		}
	}

	reverseKruskal(v, n);

}