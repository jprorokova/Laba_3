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
		Node* pNext;//óêàçàòåëü íà ñëåäóþùèé åëåìåíò
		T data;//äàííûå, êîòîðûå ïåðåäàåì

		Node(T data=T(), Node* pNext=nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	

	};

	Node<T>*head;//ïåðâûé åëåìåíò ñïèñêà
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
	Node<T>* temp = head;//âðåìåííÿ ïåðåìåííàÿ äëÿ õðàíåíèå àäðåñà óäåëÿåìîãî åëåìåíòà

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
/*
template<class T>
class Hash
{
	int BUCKET;    // êîëè÷åñòâî ñåãìåíòîâ
	int size;
	// óêàçàòåëü íà ìàññèâ ñîäåðæàùèé ñåãìåíòû
	List<T>* table;
public:
	Hash(int V);  // Constructor 

	// âñòàâëÿåò êëþ÷ â õýø òàáëèöó 
	void insertItem(int x);

	// óäàëÿåò êëþ÷è èç õýø òàáëèöû
	void deleteItem(int key);

	// õýø ôóíêöèÿ äëÿ ñîïîñòàâëåíèé çíà÷åíèé ñ êëþ÷åì
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
	// ïîëó÷èòü õýø èíäåêñ êëþ÷à 
	int index = hashFunction(key);

	// íàéòè êëþ÷ è (èíäåêñíîì)ñïèñêå 
	List <T> ::iterator;T i;
	for (i = table[index].begin();
		i != table[index].end(); i++) {
		if (*i == key)
			break;
	}

	// åñëè êëþ÷ íàéäåí â õýø òàáëèöå , óäàëèòü åãî 
	if (i != table[index].end())
		table[index].erase(i);
}

//  ô-ÿ îòîáðàæàþùàÿ õýø òàáëèöó
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
*/
typedef int T;
typedef int hashTableIndex;
struct Node
{
	int data;
	Node* next; //покажчик на след элемент
};
typedef Node* PNode;
class Hash
{
	PNode* hashTable; // хэш таблица
	int hashTableSize;
public:
	Hash():hashTable(NULL),hashTableSize(0){}
	hashTableIndex myHash(T);// определение хэш значения
	void insertNode(T);//вставка элемента в хэш таблицу
	void createHashTable();//создание хэш таблицы
	void createFileHash();//создание файла с хэш таблицей
};
//создание файла ключей
void createFileKey();



void createFileKey() {
	int n;// no. of keys
	
	
}
void Hash::createHashTable()
{
	hashTable = new Node * [hashTableSize];
	for (int i = 0; i < hashTableSize; i++) {
		hashTable[i] = nullptr;
	}
	int n;
}
void Hash::insertNode(T key)
{
	PNode p, po;
	int h = myHash(key);
	p = new Node;
	po = hashTable[h];
	hashTable[h] = p;
	p->next = po;
	p->data = key;
}
int Hash::myHash(T key1) {
	return(key1 % hashTableSize);
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
