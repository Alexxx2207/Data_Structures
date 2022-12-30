#include <iostream>
#include <vector>

using namespace std;

const int arr_max_size = 1000;

int arr_size;

int sumTree[2*arr_max_size];

void printArray(vector<int> arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void printTree()
{
	cout << "Tree: ";

	for (int i = 1; i < arr_size * 2; i++)
	{
		cout << sumTree[i] << " ";
	}
	cout << endl;
}

void buildTree(vector<int> arr)
{ 
	if (arr_size & 1)
	{
		arr.insert(arr.begin(), 0);
		arr_size++;

		cout << "New array: ";
		printArray(arr, arr_size);
	}

	for (int i = 0; i < arr_size; i++)
	{
		sumTree[arr_size + i] = arr.at(i);
	}

	for (int i = arr_size - 1; i > 0; i--)
	{
		sumTree[i] = sumTree[i << 1] + sumTree[i << 1 | 1];
	}
}

void updateParent(int index, int newValue)
{
	sumTree[index] += newValue;

	if (index <= 2)
	{
		sumTree[1] += newValue;
		return;
	}
	updateParent(ceil(index >> 2) - 1, newValue);
}	

void update(int index, int newValue)
{
	int delta = newValue - sumTree[arr_size + index];
	sumTree[arr_size + index] = newValue;

	updateParent(ceil((arr_size + index) / 2.0) - 1, delta);
}

int query(int l, int r, int lc, int rc, int i)
{   
	if (l > r)
	{
		l = l + r;
		r = l - r;
		l = l - r;
	}

	if (l == r)
	{
		return sumTree[arr_size + l];
	}

	int current = 0;

	if (r < lc || l > rc) return 0;
	if (l <= lc && r >= rc) return sumTree[i];
	
	int mid = (lc + rc) / 2;
	return query(l, r, lc, mid, i * 2) + query(l, r, mid+1, rc, i * 2 + 1);
}

int querySum(int l, int r)
{
	return query(l, r, 0, arr_size, 1);
}

int main()
{
	vector<int> t = { 5, -2, 4,3,2 };
	arr_size = t.size();

	buildTree(t);
	printTree();
	cout << "Query sum: " <<querySum(1, 3) << endl;
	update(1, 10);
	printTree();
}
