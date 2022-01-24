#include<iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include<vector>
using namespace std;
struct HuffNode {
	int data;
	char symbol;
	HuffNode *leftChild;
	HuffNode *rightChild;
	vector<int>code;
};
template <class T>
class MinHeap {
public:
	MinHeap(int theCapacity)
	{
		if (theCapacity < 1)
		{
			cout << "capacity must>=1\n";
		}
		capacity = theCapacity;
		heapSize = 0;
		heap = new T[capacity + 1];
	};
	bool IsEmpty()
	{
		if (heapSize == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	const T& Top()
	{
		return heap[1];
	};
	void Push(T& e)
	{
		if (heapSize == capacity)
		{
			ChangeSizeD(heap, capacity, 2 * capacity);
			capacity *= 2;
		}
		int currentNode = ++heapSize;
		while (currentNode != 1 && heap[currentNode / 2].data > e.data)//不是第一個，且根大於它
		{//推上去
			heap[currentNode] = heap[currentNode / 2];
			currentNode /= 2;
		}
		heap[currentNode] = e;
		//cout << "heap[" << currentNode << "].data =" << heap[currentNode].data<<endl;
	};
	HuffNode Pop()
	{
		HuffNode temp_H;
		if (IsEmpty() == true)
		{
			"tree is empty ,cant POP\n";
		}
		else
		{
			temp_H.data = heap[1].data;
			temp_H.symbol = heap[1].symbol;
			temp_H.leftChild = heap[1].leftChild;
			temp_H.rightChild = heap[1].rightChild;
			heap[1].~T();
			T lastE = heap[heapSize--];
			//乾坤大挪移
			int currentNode = 1;
			int child = 2;
			while (child <= heapSize)
			{
				if (child < heapSize&&heap[child].data > heap[child + 1].data)//右子樹比較小的話
				{
					child++;//變到右子樹
				}
				if (lastE.data <= heap[child].data)//根最小的話
				{
					break;//就能離開while去放值了
				}
				heap[currentNode] = heap[child];
				currentNode = child;
				child *= 2;
			}
			heap[currentNode] = lastE;
		}
		return temp_H;
	};
	void ChangeSizeD(T *a, const int oldSize, const int newSize)
	{
		if (newSize < 0)
		{
			cout << "new length must>0\n";
		}
		T*temp = new T[newSize];
		int number = min(oldSize, newSize);
		for (int i = 0; i < number; i++)
		{
			temp[i] = a[i];
		}
		delete[]a;
		a = temp;
	};
	// ChangeSizeD 在課本第130⾴
	void print_tree()
	{
		int lv = 0;
		int now = 1;
		for (int n = 0; now < heapSize + 1; n++)
		{
			for (int i = 0; i < pow(2, n); i++)
			{
				if (now < heapSize + 1)
				{
					cout << heap[now].data << "__";
					now++;
				}
			}
			cout << endl;
			if (now < heapSize + 1)
			{
				lv++;
			}
		}
		cout << "max_level:" << lv << endl;
		cout << endl << "============================================" << endl;
	}
	int getHeapSize()
	{
		return heapSize;
	}
	void newTop(HuffNode h)
	{
		heap[1].data = h.data;
		heap[1].symbol = h.symbol;
		heap[1].leftChild = h.leftChild;
		heap[1].rightChild = h.rightChild;
	}
private:
	T *heap; // element array
	int heapSize; // number of elements in heap
	int capacity; // size of the array heap*/
};
void makeHufftree(MinHeap<HuffNode>& min_heap)//造霍夫曼樹
{
	while (min_heap.getHeapSize()>1)
	{
		HuffNode *h1 = new HuffNode; //讓位置不同
		HuffNode h11 = min_heap.Pop();
		h1->data = h11.data;
		h1->symbol = h11.symbol;
		h1->leftChild = h11.leftChild;
		h1->rightChild = h11.rightChild;
		//cout << "h1=" << h1 << endl;
		HuffNode *h2 = new HuffNode;
		HuffNode h22 = min_heap.Pop();
		h2->data = h22.data;
		h2->symbol = h22.symbol;
		h2->leftChild = h22.leftChild;
		h2->rightChild = h22.rightChild;
		HuffNode *r=new HuffNode;
		//cout << "r=" << r << endl;
		r->data = h1->data + h2->data;
		r->symbol = ' ';
		//cout << h1->data << "+" << h2->data << "=" << r->data << endl;
		if (h1->data >= h2->data)
		{
			r->leftChild = h1;
			r->rightChild = h2;
		}
		else
		{
			r->leftChild = h2;
			r->rightChild = h1;
		}
		min_heap.Push(*r);////////////////////////////
		if (min_heap.getHeapSize() == 1)
		{
			min_heap.newTop(*r);
		}
	}
}
int maxLv = 0;
int nowLv = 0;
int NofNode = 0;
void preorder(HuffNode heap)//順便算maxLevel、NumberOfNode跟編碼
{
	cout << heap.data << " ";
	NofNode++;
	if (heap.leftChild != nullptr)
	{
		nowLv++;
		if (nowLv > maxLv)
		{
			maxLv = nowLv;
		}
		//cout << "\nnowLV=" << nowLv << endl;
		preorder(*heap.leftChild);
	}
	if (heap.rightChild != nullptr)
	{
		nowLv++;
		if (nowLv > maxLv)
		{
			maxLv = nowLv;
		}
		//cout << "\nnowLV=" << nowLv << endl;
		preorder(*heap.rightChild);
	}
	nowLv--;
	//cout << "\nnowLV=" << nowLv << endl;
	return;
}
void inorder(HuffNode heap)
{
	if (heap.leftChild != nullptr)
	{
		inorder(*heap.leftChild);
	}
	cout << heap.data << " ";
	if (heap.rightChild != nullptr)
	{
		inorder(*heap.rightChild);
	}
	else
	{
		return;
	}
}
vector<int>temp_code(1);//編碼從第一格開始
void Hcoding(HuffNode heap)//利用preorder來coding
{
	if (heap.leftChild != nullptr)
	{
		temp_code.push_back(1);
		Hcoding(*heap.leftChild);
	}
	if (heap.rightChild != nullptr)
	{
		temp_code.push_back(0);
		Hcoding(*heap.rightChild);
	}
	heap.code = temp_code;
	temp_code.pop_back();
	if (heap.symbol != ' ')
	{
		cout << heap.symbol << ":";
		for (int i = 1; i < heap.code.size(); i++)//編碼從第一格開始
		{
			cout << heap.code[i];
		}
		cout << endl;
	}
	return;
}
void Hdecoding(HuffNode heap ,string code)//利用preorder來decoding
{
	HuffNode *find;
	find = &heap;
	int x = 0;
	//cout << "code.size()=" << code.size() << endl;
	while (x<=code.size())
	{
		if (code[x] == '1')//往左邊找
		{
			if (find->leftChild != nullptr)
			{
				find = find->leftChild;
			}
			else
			{
				cout << find->symbol;
				find = &heap;//回頭找
				x--;
			}
		}
		else if (code[x] == '0')
		{
			if (find->rightChild != nullptr)
			{
				find = find->rightChild;
			}
			else
			{
				cout << find->symbol;
				find = &heap;//回頭找
				x--;
			}
		}
		else//最後一個
		{
			cout << find->symbol;
		}
		x++;
	}
	return;
}
int main() {
	string inp;
	cout << "Input your string:";
	cin >> inp;
	char count[26] = { 0 };
	for (int i = 0; i < inp.size(); i++)
	{
		count[inp[i] - 'a']++;
	}
	int size = 0;
	for (int i = 0; i < 26; i++)//算size
	{
		if (count[i] != 0)
		{
			size++;
		}
	}
	char *arr = new char[size + 1];//從1開始計算
	int *freq = new int[size + 1];
	int z = 1;//有幾個變數
	for (int i = 0; i < 26; i++)//塞arr跟freq
	{
		if (count[i] != 0)
		{
			arr[z] = i + 'a';
			//cout << "arr[" << z << "]=" << arr[z] << endl;
			freq[z] = count[i];
			z++;
		}
	}
	cout << "your input size is:" << size << endl;
	cout << "your input symbol:";
	for (int i = 1; i < z; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\nyour input frequency:";
	for (int i = 1; i < z; i++)
	{
		cout << freq[i] << " ";
	}
	cout << "\n";
	//////////////////////////////////////////////////////第一題
	/*int size;
	cout << "Input size:";
	cin >> size;
	char *arr = new char[size + 1];//從1開始計算
	int *freq = new int[size + 1];
	cout << "Input symbol:";
	string tem_arr;
	cin.get();
	getline(cin, tem_arr);
	int k = 1;
	for (int i = 0; i < size * 2; i += 2)
	{
		arr[k] = tem_arr[i];
		k++;
	}
	cout << "input frequency:";
	string tem_freq;
	getline(cin, tem_freq);
	k = 1;
	for (int i = 0; i < size * 2; i += 2)
	{
		freq[k] = tem_freq[i] - '0';
		k++;
	}*/
	////////////////////////////////////////////////////////////第一題
	////////////////////////////////////////現在我有從1開始的freq跟arr
	MinHeap<HuffNode> min_heap(size);
	// Initalize the leaf node
	for (int i = 1; i <= size; i++) {
		HuffNode leaf_node;
		leaf_node.data = freq[i];
		leaf_node.symbol = arr[i];
		leaf_node.leftChild = leaf_node.rightChild = nullptr;
		min_heap.Push(leaf_node);
	}
	cout  << "============================================" << endl;
	cout << "Minheap Tree:\n";
	min_heap.print_tree();
	makeHufftree(min_heap);//造霍夫曼樹
	//cout << min_heap.Top().rightChild ->rightChild->rightChild->data << endl;
	cout << "Huffman Tree\nPreorder:";
	preorder(min_heap.Top());
	cout << "\nInorder:";
	inorder(min_heap.Top());
	cout << "\nMax level:" << maxLv << endl;
	cout << "Number Of Node:" << NofNode;
	cout << endl << "============================================" << endl;
	cout << "Huffman Coding:\n";
	Hcoding(min_heap.Top());
	cout <<"============================================" << endl;
	string code;
	cout << "Input sequence for decode:";
	cin >> code;
	cout << "\nDecoded Huffman Data:\n";
	Hdecoding(min_heap.Top(),code);
	cout << endl;
	system("pause");
	return 0;
}

