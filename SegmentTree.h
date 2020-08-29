#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H
#define left(i) (2*i + 1)
#define right(i) (2*i + 2)
#define parent(i) ((i-1)/2)
#include <vector>

template<class T>
class SegmentTree
{
    public:
        //tree constructors.
        SegmentTree(std::vector<T> data, T value, T (*combine)(T obj1, T obj2));
        SegmentTree(T ar[], int n, T value, T (*combine)(T obj1, T obj2));
        
        //query the range l to r, 0 based array indexing.
        T query(int l, int r);
        
        //update the element at index idx to val.
        void update(int idx, T val,vector<T> &data);
        ///TODO lazy propagation
    private:
        //represents the segment tree.
        vector<T>tree;
    
        //builds the segment tree.
        void buildTree(std::vector<T> data,int start,int end,int curr_ind);
        
        //size of the segment tree array.
        int segTreeSize;
    
        //extra nodes must be added to array to make its size a power of 2
        //this is the value to be filled for the those nodes.
        T valueForExtraNodes;
    
        //specifies how to combine child node results to form parent node result.
        T (*combine)(T obj1, T obj2);
    
        //used to calculate the size of array needed to store the tree.
        //int calculateSize(int n);
    
        //helps to solve a range query.
        T queryHelper(int l,int r, int st, int ed, int node);
        void updateHelper(int idx,int val,int st,int ed,int node,vector<T> &data);
};

template<class T> SegmentTree<T>::SegmentTree(std::vector<T> data,
                                                T value, T (*combine)(T obj1, T obj2))
{
   this->combine = combine;
   valueForExtraNodes = value;
   //segTreeSize = calculateSize(data.size());
   segTreeSize =4*data.size();
   //tree.push_back(0);
   tree.resize(segTreeSize,0);
   buildTree(data,0,data.size()-1,0);
}

template<class T> SegmentTree<T>::SegmentTree(T ar[], int n,
                                            T value, T (*combine)(T obj1, T obj2))
{
   this->combine = combine;
   valueForExtraNodes = value;
   //segTreeSize = calculateSize(n);
   segTreeSize =4*n;
   //tree.push_back(0);
   tree.resize(segTreeSize);
   std::vector<T> data;
   for(int i = 0; i < n; i++)
         data.push_back(ar[i]);

   buildTree(data,0,data.size()-1,0);
}

template<class T> T SegmentTree<T>::query(int l, int r)
{
	//for(int i=0;i<segTreeSize;i++)cout<<tree[i]<<" ";
    int start = 0, end = (segTreeSize/4)-1;
    return queryHelper(l, r, start, end, 0);
}

template<class T> T SegmentTree<T>::queryHelper(int left,int right, int start, int end, int ind)
{
	if(right<start || left>end || left>right)return valueForExtraNodes;
	if(start>=left && end<=right)return tree[ind];
	int mid=(start+end)/2;
	T left_ans=queryHelper(left,right,start,mid,2*ind+1);
	T right_ans=queryHelper(left,right,mid+1,end,2*ind+2);
	return combine(left_ans, right_ans);
}

template<class T> void SegmentTree<T>::buildTree(std::vector<T> data,int start,int end,int ind)
{
	if(start==end){
		tree[ind]=data[start];
		//cout<<data[start]<<" ";
		return;
	}
	int mid=(start+end)/2;
	buildTree(data,start,mid,2*ind+1);
	buildTree(data,mid+1,end,2*ind+2);
	tree[ind]=combine(tree[2*ind+1],tree[2*ind+2]);
	return;
}

template<class T> void SegmentTree<T>::update(int idx, T val,vector<T>&data)
{
	 int start = 0, end = (segTreeSize/4)-1;
    return updateHelper(idx, val, start, end, 0,data);
}

template<class T> void SegmentTree<T>::updateHelper(int idx,int value, int start, int end, int node,vector<T>&data)
{
	if(start==end){
		data[start]=value;
		tree[node]=value;
		return;
	}
    int mid=(start+end)/2;
	if(idx<=mid && idx>=start){
		updateHelper(idx,value,start,mid,2*node+1,data);
	}
	else{
		updateHelper(idx,value,mid+1,end,2*node+2,data);
	}
	tree[node]=combine(tree[2*node+1],tree[2*node+2]);
	return;
}


#endif // SEGMENTTREE_H
