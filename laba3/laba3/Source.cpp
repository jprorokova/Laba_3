#include<iostream>
#include<vector>

using namespace std;

template<class T>
class List
{
public:
	List();
	~List();
	void push_back(T data);
	T GetSize() { return Size; }
	void pop_front();
	void clear();
	T& operator[](const int index);

private:
	template<class T>
	class Node
	{public:
		Node* pNext;//��������� �� ��������� �������
		T data;//������, ������� ��������

		Node(T data=T(), Node* pNext=nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	

	};

	Node<T>*head;//������ ������� ������
	int Size;
};

template<class T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}
template<class T>
List<T>::~List()
{
}

template<class T>
void List<T>::push_back(T data)
{
	if (head==nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;
		while (current->pNext!=nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
	Size++;
}

template<class T>
void List<T>::pop_front()
{
	Node<T>* temp = head;//�������� ���������� ��� �������� ������ ���������� ��������

	head = head->pNext;
	delete temp;
	Size--;


}

template<class T>
void List<T>::clear()
{
	while (Size)pop_front();
}

template<class T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current!=nullptr)
	{
		if (counter==index)
		{
			return current->data;
		}
		current =current->pNext;
		counter++;
	}
	
}
///////////////////////////////-----------HASH-------------------////////////////////////////////////////////////////////////////////////////////
template<class T>
class Hash
{
	int BUCKET;    // ���������� ���������
	int size;
	// ��������� �� ������ ���������� ��������
	List<T>* table;
public:
	Hash(int V);  // Constructor 

	// ��������� ���� � ��� ������� 
	void insertItem(int x);

	// ������� ����� �� ��� �������
	void deleteItem(int key);

	// ��� ������� ��� ������������� �������� � ������
	int hashFunction(int x) {
		return (x % BUCKET);
	}
	void changeSize();

	void displayHash();
};
template<class T>
Hash<T>::Hash(int size)
{
	this->BUCKET = size;
	table = new List[BUCKET];
}
template<class T>
void Hash<T>::insertItem(int key)
{
	int index = hashFunction(key);
	table[index].push_back(key);
}
template<class T>
void Hash<T>::deleteItem(int key)
{
	// �������� ��� ������ ����� 
	int index = hashFunction(key);

	// ����� ���� � (���������)������ 
	List <T> ::iterator;T i;
	for (i = table[index].begin();
		i != table[index].end(); i++) {
		if (*i == key)
			break;
	}

	// ���� ���� ������ � ��� ������� , ������� ��� 
	if (i != table[index].end())
		table[index].erase(i);
}

//  �-� ������������ ��� �������
template<class T>
void Hash<T>::displayHash() {
	for (int i = 0; i < BUCKET; i++) {
		cout << i;
		for (auto x : table[i])
			cout << " --> " << x;
		cout << endl;
	}
}
template<class T>
void Hash<T>::changeSize()
{
	size *= 2;
	List* tmp = table;
}

int main()
{

	List<int> lst;
	lst.push_back(5);
	lst.push_back(50);
	cout << lst[1];
	lst.clear();
	cout<<lst.GetSize();

}