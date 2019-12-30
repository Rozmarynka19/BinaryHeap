#include "DynamicArray.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <ctime>
#define CHAR ((char)(rand() % 25+97))
#define INT ((rand()<<15)+rand()) //lub mniej elegancko rand()*rand() - ale wtedy elementy nie sa rozlozone rownomiernie
//#define INT (rand()%10001)

template <class T>
class BinaryHeap
{
	//maximum
	Dynamic_Array<T>* dynamicArray;

	int GetParentIndex(int index) { if(index > 0) return floor((index - 1) / 2); }
	int GetLeftChildIndex(int index) { return (2 * index + 1); }
	int GetRightChildIndex(int index) { return (2 * index + 2); }
	bool isLeaf(int index) { if (2 * index + 2 > dynamicArray->currentSize) return true; else return false; }
	void HipUp(int index)
	{
		while ((dynamicArray->getData(index) > dynamicArray->getData(GetParentIndex(index))) && index > 1)
		{
			dynamicArray->Swap(index, GetParentIndex(index));
			index = GetParentIndex(index);
		}
	}
	void HipDown(int index)
	{
		int greater;

		while(!isLeaf(index))
		{
			if (dynamicArray->getData(GetLeftChildIndex(index)) > dynamicArray->getData(GetRightChildIndex(index))) greater = GetLeftChildIndex(index);
			else greater = GetRightChildIndex(index);


			if(dynamicArray->getData(greater) > dynamicArray->getData(index))
				dynamicArray->Swap(index, greater);

			index = greater;
		}
	}
public:
	BinaryHeap() { dynamicArray = new Dynamic_Array<T>; }
	~BinaryHeap(){ dynamicArray->~Dynamic_Array(); }
	void Push(T data)
	{
		dynamicArray->addElement(data);

		HipUp((dynamicArray->currentSize) - 1);
	}
	T Pop()
	{
		if ((dynamicArray->currentSize) > 0)
		{
			T temp = dynamicArray->getData(0);
			dynamicArray->Swap(0, (dynamicArray->currentSize) - 1);
			dynamicArray->currentSize = (dynamicArray->currentSize) - 1;

			HipDown(0);

			return temp;
		}
	}
	
	string ToString(){ return dynamicArray->toString(); }
	string ToString(int numberOfElements){ return dynamicArray->toString(numberOfElements);	}
};

int main()
{
	BinaryHeap<int>* binaryHeap;
/*
	binaryHeap->Push(5);
	binaryHeap->Push(2);
	binaryHeap->Push(10);
	binaryHeap->Push(7);
	binaryHeap->Push(234);
	binaryHeap->Push(523);
	binaryHeap->Push(236);
	binaryHeap->Push(34);

	cout << binaryHeap->ToString();
	cout << binaryHeap->Pop()<<endl;
	cout << binaryHeap->ToString();*/

	const int MAX_INDEX = 7; 
	cout.precision(numeric_limits<double>::max_digits10);

	for (int i = 1; i <= MAX_INDEX; i++)
	{
		binaryHeap = new BinaryHeap<int>();

		const int SIZE = pow(10, i);

		clock_t start = clock();
		for (int i = 0; i < SIZE; i++) {
			binaryHeap->Push(INT);
		}
		clock_t stop = clock();

		double result = (stop - start) / (double)CLOCKS_PER_SEC;

		cout << binaryHeap->ToString(10);
		cout << "Time: " << result << "s\nTime per operation: " << result / (double)SIZE << endl << endl;;
		//*************************************************************************************************

		start = clock();
		for (int i = 0; i < SIZE; i++) 
		{
			binaryHeap->Pop();
		}
		stop = clock();

		result = (stop - start) / (double)CLOCKS_PER_SEC;
		
		cout << binaryHeap->ToString(); //pusty kopiec
		cout << "Time: " << result << "s\nTime per operation: " << result / (double)SIZE << endl << endl;

		cout << "*************************************************************************************************" << endl;
		delete binaryHeap;
		getchar();
	}
	return 0;

}