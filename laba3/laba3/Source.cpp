#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;
template<class T>
class List;

#define HashSize 1000

template<class T>
class HashTable
{
public:
	HashTable();
	~HashTable();
	void SetData(string FileName);
	void GetData(string Sentence);



private:
	int KeyFuncion(string word);
	List<string>* Hash = new List<T>[HashSize];

};

template<class T>
HashTable<T>::HashTable()
{

}

template<class T>
HashTable<T>::~HashTable()
{
}

template<class T>
void HashTable<T>::SetData(string FileName)
{
	string temp;
	string key_word;
	string definition;
	ifstream File(FileName);
	while (!File.eof())
	{
		key_word = ""; definition = ""; temp = "";
		getline(File, temp);
		key_word = temp.substr(0, temp.find(';'));
		definition.insert(0, temp, temp.find(';') + 1);
		int key = KeyFuncion(key_word);

		Hash[key].push_back(key_word);
		Hash[key].push_back(definition);
	}

}

template<class T>
void HashTable<T>::GetData(string Sentence)
{
	transform(Sentence.begin(), Sentence.end(), Sentence.begin(), ::toupper);
	string delim(" ");
	Sentence.insert(Sentence.size(), " ");
	int prev = 0;
	int next;
	string word;
	int key;

	while ((next = Sentence.find(delim, prev)) != string::npos)
	{
		word = "";
		word = Sentence.substr(prev, next - prev);
		key = KeyFuncion(word);

		for (int i = 0; i < Hash[key].GetSize(); i++)
		{
			if (word == Hash[key][i])
			{
				cout << word << ":" << endl;
				Hash[key].ShowData(i + 1);
			}
		}



		prev = next + 1;
	}

}



template<class T>
int HashTable<T>::KeyFuncion(string word)
{
	return 0;
}


template<class T>
class List
{
	friend HashTable<T>;
public:
	List();
	~List();
	void push_back(T data);
	int GetSize() { return Size; }
	void  pop_front();
	void clear();
	T& operator[](const int index);

private:
	template<class T>
	class Node
	{
	public:
		Node* pNext;//указатель на следующий елемент
		T data;//данные, которые передаем

		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}


	};

	Node<T>* head;//первый елемент списка
	int Size;
	void ShowData(int index);
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
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
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
	Node<T>* temp = head;//времення переменная для хранение адреса уделяемого елемента

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
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}


}

template<class T>
void List<T>::ShowData(int index)
{
	Node<T>* temp = this->head;

	for (int i = 0; i < index; i++)
	{
		temp = temp->pNext;
	}
	cout << temp->data << endl;



}









int main(int argc, char* argv[])
{
	string Data;
	cout << "Enter your sentence: ";
	getline(cin, Data);
	HashTable<string> Sentence;
	Sentence.SetData("data.txt");
	Sentence.GetData(Data);


}