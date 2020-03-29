#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

template<class T>
class List
{
public:
	List();
	~List();
	void push_back(T data);
	int getSize() const { return Size; }
	void pop_front();
	void clear();
	T& operator[](const int index);
	T& find(const T& key);

private:
	template<class L>
	class Node
	{
	public:
		Node* pNext;//????????? ?? ????????? ???????
		L data;//??????, ??????? ????????

		Node(L data = L(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}


	};

	Node<T>* head;//?????? ??????? ??????
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
	clear();
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
	Node<T>* temp = head;//???????? ?????????? ??? ???????? ?????? ?????????? ????????

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
T& List<T>::find(const T & key) {
	Node<T>* tmp = this->head;
	bool found = false;
	while (tmp != nullptr) {
		if (tmp->data == key) {
			found = true;
			//break;
			return tmp->data;
		}
		tmp = tmp->pNext;
	}
	if (!found) {
		cout << "Error: no such object!" << std::endl;
	}
	
	
}

struct DictPair {
	string request;
	string response;
	
	bool operator==(const DictPair& other)
	{
		return request == other.request;
	}
};

typedef List<DictPair> PairList;

class DictionaryHash {
public:
	DictionaryHash();
	~DictionaryHash();
	int hashFunc(string str);
	string& operator[](const string& request);
	void enlarge();
	void push_back(DictPair pair);	
	
private:
	int size;
	int occupiedSize;
	PairList * list;
};

DictionaryHash::DictionaryHash()
{
	size = 10;
	occupiedSize = 0;
	list = new PairList[size];
}

DictionaryHash::~DictionaryHash()
{
	delete[] list;
}

int DictionaryHash::hashFunc(string str)
{
	int key = 0;
    long long temp1 = 0;
    long long temp2 = 0;
    char cast;
    int ascii;
    for (int i = 0; i < str.length(); i++) {
        if (str.length() - (i + 1) > 8) {
            temp1 = pow(26, 8);
        }
        else {
            temp1 = pow(26, (str.length() - (i + 1)));
        }
        if (str[i] != '-' && str[i] != ' ') {
            cast = str[i];
            ascii = (int)cast - 65;
        }
        else {
            ascii = 1;
        }
        temp1 *= ascii;
        temp2 += temp1;
    }
    temp2 %= size;
    key = temp2;
    return key;
}

void DictionaryHash::enlarge()
{
	occupiedSize = 0;
	PairList * tmp = list;
	size *= 2;
	list = new PairList[size];
	
	for (int i = 0; i < size/2; i++) {
        for (int j = 0; j < tmp[i].getSize(); j++) {
            push_back(tmp[i][j]);
        }
    }
    delete[] tmp;
}

void DictionaryHash::push_back(DictPair pair)
{
	if (occupiedSize + 1 > size * 0.8)
	{
		enlarge();
	}
	list[hashFunc(pair.request)].push_back(pair);
	occupiedSize++;
}

string& DictionaryHash::operator[](const string& request)
{
	DictPair pair;
	pair.request = request;
	list[hashFunc(request)].find(pair);
}

void parse(DictionaryHash& table, const string & filename)
{
    ifstream in;
    in.open(filename);
    if(in.is_open()) {
        while(in.eof() != true) {
        	DictPair dPair;
            getline(in, dPair.request, ';');
            getline(in, dPair.response, '\n');
            table.push_back(dPair);
        }
        in.close();
    }
    else {
        cout << "Error: no file" << endl;
        exit(1);
    }
}

void upperCase(vector<string>& word) {
    for(int i = 0; i < word.size(); i++) {
        for(int j = 0; j < word[i].length(); j++) {
            if (word[i][j] != '-' && word[i][j] != ' ') {
                word[i][j] = toupper(word[i][j]);
            }
        }
    }
}

vector<string> beatByWords(string & request)
{
	vector<string> words;
	request += " ";
	string buf;
	
	for(int i = 0; i < request.length(); ++i)
	{
		if(request[i] == ' ')
		{
			if(buf.length() != 0)
			{
				words.push_back(buf);
				buf = "";
			}
		}
		else
		{
			buf += request[i];
		}
	}
	return words;
}

void menu(DictionaryHash & table)
{
	string request;
	for(;;)
	{
		cout << "Put your word(s) to describe it or 0 to exit: ";
		getline(cin, request, '\n');
		
		if (request == "0") break;
		
		cout << endl;
		
		vector<string> words = beatByWords(request);
		
		for(int i = 0; i < words.size(); ++i)
		{
			cout << words[i] << " ";
		}
		
		upperCase(words);
				
		for (int i = 0; i < words.size(); i++) {
            cout << words[i] << " - " << table[words[i]] << endl << endl;
        }
	}
}

int main() {
	
	DictionaryHash table;
	parse(table, "dictionary.txt");
	menu(table);
	return 0;
}
