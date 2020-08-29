//EXAMPLE IMPLEMENTATION

#include<iostream>
using namespace std;
#include <vector>
#include"SegmentTree.h"

int small(int x,int y){return min(x,y);}

int main(){
	int n,q;
	cin>>n>>q;
	vector<int>dataVector(n);
	for(int i=0;i<n;i++){
		cin>>dataVector[i];
	}
   SegmentTree < int > rangeSumQueries(dataVector,INT_MAX,small);
   while(q--){
   	int a,b,type;
   	cin>>type;
   	cin>>a>>b;
   	a--;b--;
   	if(type==2){
   	    cout<<rangeSumQueries.query(a,b)<<endl;
	   }
	else{
		b++;
		rangeSumQueries.update(a,b,dataVector);
	}
   }
}
