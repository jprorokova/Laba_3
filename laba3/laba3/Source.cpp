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
		Node* pNext;//указатель на следующий елемент
		T data;//данные, которые передаем

		Node(T data=T(), Node* pNext=nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	

	};

	Node<T>*head;//первый елемент списка
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





int main()
{

	List<int> lst;
	lst.push_back(5);
	lst.push_back(50);
	cout << lst[1];
	lst.clear();
	cout<<lst.GetSize();

}