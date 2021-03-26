#ifndef MPQ_H_
#define MPQ_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

template<class Comparable>
struct MPQ_info
{
	string label;// build_num in the MPQ
	Comparable value;//the items can be compared to each other just as in a priority queue.
	MPQ_info<Comparable> (){};
	MPQ_info<Comparable> (const MPQ_info<Comparable> &i);
	MPQ_info<Comparable> operator=(const MPQ_info<Comparable> & i){
		this->label= i.label;
		this->value= i.value;
		return *this;
	}
};
template<class Comparable>
MPQ_info<Comparable>::MPQ_info(const MPQ_info<Comparable> &i)
{
	label=i.label;
	value=i.value;
}

template<class Comparable>
class MPQ
{
private:

	// keep location of the building in heap
	vector<MPQ_info<Comparable>>Heap; // heap
	int currentSize;
	int capacity;
	//void makeEmpty( MPQ<Comparable> * & t ) const;
public:
	unordered_map<string, int> index;
	unordered_map<string, int> order_of_block;
	MPQ(){};
	MPQ(int size);
	void  insert( const Comparable & value, string label);// This method inserts an item with the given value and label into the MPQ.
	Comparable Remove(string label);// This method removes the value with this label and returns it.
	Comparable GetMax();// This method returns the maximum value that is currently stored.
	string GetBlock();
	Comparable GetValue(string);
	bool IsEmpty(); //check if it is empty, using the function
	bool IsFull();
	void percolateDown( int hole );
	//void makeEmpty( );
	//const MPQ & operator=( const MPQ<Comparable>  & rhs );
	//MPQ<Comparable> * clone( MPQ<Comparable> *t ) const;
	//~MPQ();
};

template <class Comparable>
MPQ<Comparable>::MPQ(int cap): Heap(cap)
{//constructor
	currentSize=0;
	capacity=cap;
};

template <class Comparable>
void MPQ<Comparable>::insert( const Comparable & x, string label ) //insert the new element to heap
{
	if( IsFull())
		return;		

	int hole=++ currentSize;

	for(; hole > 1 && x >= Heap[ hole / 2 ].value   ; hole /= 2 )
	{
		if ( x == Heap[ hole / 2 ].value &&order_of_block[label]< order_of_block[Heap[hole/2].label])
		{Heap[ hole ] = Heap[ hole / 2 ];
		index[Heap[hole].label]=hole; }  //yazsam da yazmasam da deðiþiyor mu bak
		if (x >= Heap[ hole / 2 ].value)
		{Heap[ hole ] = Heap[ hole / 2 ];
		index[Heap[hole].label]=hole; }
	}
	Heap[hole].value = x;
	Heap[hole].label=label;
	index[label]=hole;
}

template <class Comparable>
Comparable MPQ<Comparable>::Remove(string label) // remove the element from the heap
{
	int pos = index[label];
	Comparable delete_info = Heap[pos].value;
	Heap[pos] = Heap[currentSize--];
	index[label]=-1; // boþ koltuk sayýsý deðiþtiðinde silme yapýyorum, daha sonra tekrar insert edince deðiþecek arada baþka bir þey yapmadýðým iin bu olmasa da olabilir
	index[Heap[pos].label] = pos;
	percolateDown(pos);
	return delete_info;
}

template <class Comparable>
void MPQ<Comparable>::percolateDown( int hole )
{
	int child;
	Comparable tmp = Heap[hole].value;
	string tmp2 = Heap[hole].label;
	bool t = false;
	for( ; hole * 2 <= currentSize ; hole = child )
	{
		child = hole * 2;
		if( child != currentSize && Heap[child + 1].value > Heap[child].value )
			child++;
		if( Heap[child].value >= tmp )
		{  
			Heap[hole] = Heap[ child ];
			index[Heap[child].label]=hole; // emþn deðilim
			if(Heap[child+1].value >= tmp && child+1 <= currentSize)
			{
				int h= Heap[child+1].value;
				Heap[child].label=Heap[child+1].label;
				Heap[child].value=h;
				index[Heap[child].label]= child;
				t=true;
			}
		}
		else
			break;
	}
	if(t)
		hole++;
	Heap[ hole ].value = tmp;
	Heap[hole].label= tmp2;
	index[Heap[hole].label]=hole;
}

template <class Comparable>
Comparable MPQ<Comparable>::GetMax() // retýrn the max that is first element of the heap
{
	return (Heap[1].value);
}

template <class Comparable>
string MPQ<Comparable>::GetBlock() // retýrn the max that is first element of the heap
{
	return (Heap[1].label);
}
template <class Comparable>
Comparable MPQ<Comparable>::GetValue(string blkname) // retýrn the max that is first element of the heap
{
	return (Heap[index[blkname]].value);
}

template <class Comparable>
bool MPQ<Comparable>::IsEmpty() 
{
	if(currentSize == 0)
		return true;
	else
		return false;
}
template <class Comparable>
bool MPQ<Comparable>::IsFull()
{//simple isfull func to stop insert
	if((this->currentSize)==(this->capacity))
		return true;
	else 
		return false;
}

//template <class Comparable>
//void MPQ<Comparable>::makeEmpty( MPQ<Comparable> * & t ) const
//{
//	if( !t.IsEmpty() )
//	{
//		delete [] t;
//	}
//	t = NULL;
//}
//
//template <class Comparable>
//MPQ<Comparable> * MPQ<Comparable>::clone( MPQ<Comparable> * t ) const
//{
//	if( t.IsEmpty )
//		return NULL;
//	else
//		return new MPQ<Comparable>( t->label, t->value);
//}
//
//template <class Comparable>
//MPQ<Comparable>::~MPQ()
//{//destructor
//	if(!IsEmpty()){
//
//		delete [] Heap;
//	//	delete [] index;
//
//	}
//};


//template <class Comparable>
//const MPQ<Comparable> & MPQ<Comparable>::operator=( const MPQ<Comparable>  & rhs )
//{
//	/*if( this != &rhs )
//	{
//		makeEmpty();
//		Heap = clone( rhs.Heap );
//	}
//	return *this;*/
//	delete[] Heap;
// 
//    // because m_length is not a pointer, we can shallow copy it
//    index = rhs.index;
// 
//    // m_data is a pointer, so we need to deep copy it if it is non-null
//    if (rhs.Heap)
//    {
//        // allocate memory for our copy
//        Heap = new MPQ_info<Comparable>[capacity];
// 
//        // do the copy
//		for (int i=0; i < capacity; i++)
//            Heap[i] = rhs.Heap[i];
//    }
//	return *this;
//};

//template <class Comparable>
//void MPQ<Comparable>::makeEmpty( )
//{
//	makeEmpty(Heap);
//}
#endif


