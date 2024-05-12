#include <iostream>
#include <Windows.h>
#include <math.h>
#include <fstream>
#include <vector>
#define nullptr NULL
#include <conio.h>
#include <map>
#include <bits/stdc++.h>a
#include <iterator>

using namespace std;

vector <string> linesRead;

template <class X>
class queueNode
{
public:
    X data;
    queueNode *next;
    queueNode<X>(X data)
    {
        next = nullptr;
        this->data = data;
    }
};

template <class X>
class Queue
{
    queueNode<X> *front;
    queueNode<X> *rear;

public:
    Queue<X>()
    {
        front = rear = nullptr;
    }

    bool isEmpty() { return (front == nullptr); }

    void enqueue(X element)
    {
        if (front == nullptr)
        {
            front = rear = new queueNode<X>(element);
        }
        else
        {
            queueNode<X> *temp = new queueNode<X>(element);
            rear->next = temp;
            rear = temp;
        }
    }

    X dequeue()
    {
        if (!isEmpty())
        {
            queueNode<X> *temp = front;
            front = front->next;
            X data = temp->data;
            delete temp; 
            return data;
        }
        else
        {
            cout << "Queue empty" << endl;
            return X();
        }
    }

    void display()
    {
        queueNode<X> *temp = front;
        while (temp != nullptr)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};

Queue < string > userHistory;

string toupper(string text)
{
	for(int i = 0; i < text.length(); i++)
	{
		if(text[i] >= 'a' && text[i] <= 'z') text[i] -= 'a' - 'A';
	}
	return text;
}

string mapUserchoice(char choice)
{
	if(choice=='1') return "Searched using hash table";
	else if(choice=='2') return "Attempted to edit the text searched";
	else if(choice=='3') return "Attempted to remove data from the file";
	else if(choice=='4') return "Pressed undo,to undo search";
	else if(choice=='5') return "Pressed Redo";
	else if(choice=='6') return "Sorted the data in file";
	else if(choice=='7') return "Looked up using postfix/prefix";
	else if(choice=='8') return "Attempted to add new data to file";
	else if(choice=='9') return "Exited the editor";
	else return "Invalid input";
	
}

char menu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,4);
	char x;
	cout << "\n\t\t\t\t\t||Text Editor System||" << endl;
	cout << "\n\t\t\tPress 1 to search. " << endl;
	cout << "\t\t\tPress 2 to edit the searched text." << endl;
	cout << "\t\t\tPress 3 to remove data from file." << endl;
	cout << "\t\t\tPress 4 to go back(undo) to previously searched text." << endl;
	cout << "\t\t\tPress 5 to go forward (redo/if pressed undo previously)." << endl;
	cout << "\t\t\tPress 6 to sort the data in file." << endl;
	cout << "\t\t\tPress 7 to lookup data in the file using regular expressions(postfix and prefix/please use capital letters)." << endl;
	cout << "\t\t\tPress 8 to enter new data to file." << endl;
	cout << "\t\t\tPress 9 to exit the editor."<< endl;
	cout << "\t\t\tEnter here: ";
	cin >> x;
	string action=mapUserchoice(x);
	userHistory.enqueue(action);
	return x;
}


void displayActions(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 8);
	system("cls");
	cout<<"\n\t\t\t\t\t\t\t\t\t***History of actions taken upon this launch";
	while(!userHistory.isEmpty()){
		string x=userHistory.dequeue();
		cout<<"\n\t\t\t\t\t\t\t\t\t***"<<x;
	}
	cout<<"\n\t\t\t\t\t\t\t\t\t\t***GOODBYE"<<endl;
	SetConsoleTextAttribute(hConsole, 4);
}

template < class X > class Node
{
	public: X data;
	Node * next;
	Node < X > (X data)
	{
		next = nullptr;
		this-> data = data;
	}
};


class HeapSort
{
	private:
	void heapify(int index)
	{
		int smallest = index;
		int left = (2 * index) + 1;
		int right = (2 * index) + 2;
		if(left < linesRead.size() && linesRead[smallest].compare(linesRead[left]) > 0) swap(smallest, left);
		if(right < linesRead.size() && linesRead[smallest].compare(linesRead[right]) > 0) swap(smallest, right);
		if(smallest != index)
		{
			swap(linesRead[smallest], linesRead[index]);
			heapify(index);
		}
	}
	
	void copyToFile()
	{
		fstream file;
		file.open("input.txt", ios::out);
		for(int i = 0; i < linesRead.size(); i++)
		{
			file << linesRead[i] << endl;
		}
		file.close();
	}
	
	public: 
	void heapSort()
	{
		int startIndex = linesRead.size() / 2 - 1;
		for(int i = startIndex; i >= 0; i--) heapify(i);
		for(int i = linesRead.size() - 1; i >= 0; i--) swap(linesRead[0], linesRead[i]);
		heapify(0);
		copyToFile();
	}
	
};

template < class X > class Stack
{
	Node < X > * top;
	public: Stack < X > ()
	{
		top = nullptr;
	}
	bool isEmpty() { return (top == nullptr); }
	
	void push(X element)
	{
		if(top == nullptr)
		{
			top = new Node < X > (element);
		}
		else
		{
			Node < X > * temp = new Node < X > (element);
			temp -> next = top;
			top = temp;
		}
	}
	
	X pop()
	{
		if(!isEmpty())
		{
			Node < X > * temp = top;
			Node < X > * next = top -> next;
			top = nullptr;
			top = next;
			return temp -> data;
		}
		else cout << "Stack empty" << endl;
		return 0;
	}
	
	void display()
	{
		Node < X > * temp = top;
		while(temp != nullptr)
		{
			cout << temp -> data << endl;
			temp = temp -> next;
		}
	}

};

bool Match(char * array1, char * array2, int k)
{
	if( * (array1 + k) == 0 && * (array2 + k) == 0) return true;
	if( * (array1 + k) == '*' && * (array1 + k + 1) != 0 && * (array2 + k) == 0) // if input is * this will check charcters after *
		return false;
	// If the first string contains '.', any single alphabet is possible at place
	// of '.' OR if both characters matched
	if(( * (array1 + k) == '.') || * (array1 + k) == * (array2 + k)) return Match(array1, array2, k + 1);
	if( * (array1 + k) == '*' && Match(array1 + 1, array2, k) || * (array1 + k) == '*' && Match(array1, array2 + 1, k)) return true;
	return false;
}

class TrieNode
{
	public: map < char,TrieNode * > child;
	bool isWord; // ISword is False for all the characters except the last charcter of the string
	int prefixes;
	TrieNode(): isWord(false),
	prefixes(0) {}
};

class Trie
{
	public: TrieNode * root;
	int count;
	
	Trie()
	{
		root = new TrieNode(); // Initializing root node
		count = 0;
	}
	
	Trie(Trie & obj) { root = obj.root; }
	
	Trie & operator = (Trie & obj)
	{
		if(this != & (obj))
		{
			root = 0;
			delete root;
			root = obj.root;
		}
	}
	
	~Trie()
	{
		if(root != 0) root = 0;
		delete root;
	}
	
	void insert(string str)
	{
		int i;
		TrieNode * temp = root;
		for(i = 0; i < str.length(); i++)
		{
			char ch = str[i];
			TrieNode * node = temp -> child[ch];
			if(!node) // if ch is not present in the trie then new trienode will be
			// created
			{
				node = new TrieNode();
				temp -> child[ch] = node;
			}
			temp = node;
			temp -> prefixes++;
		}
		temp -> isWord = true; // at the end of the word Isword is initialized to TRUE
	}
    
	bool Search(string str)
	{
		int i;
		TrieNode * temp = root;
		for(i = 0; i < str.length(); i++)
		{
			char ch = str[i];
			TrieNode * node = temp -> child[ch];
			if(!node)
			{ // When current character node is not present in the trie
				// FALSE is returned
				cout << "No such word exists in the file." << endl;
				return false;
			}
			temp = node; // temp = temp->next
		}
		return temp -> isWord; // LAST character of the SEARCHED word will be TRUE
	}
	
	bool isEmpty(TrieNode* node) 
	{
       return (node != nullptr) && (node->child.empty());
    }

    bool isEmpty() 
	{
       return isEmpty(this->root);
    }
    
	TrieNode * getNode(string str)
	{ // GETNODE of the last character in STR
		int i;
		TrieNode * temp = root;
		for(i = 0; i < str.length(); i++)
		{
			char ch = str[i];
			TrieNode * node = temp -> child[ch];
			if(!node)
			{
				return nullptr;
			}
			temp = node; // temp = temp->next
		}
		return temp;
	}
	
	void DisplayTrie(map < char, TrieNode * > temp, char arr[], int level, TrieNode * node, int rev) // Display without comparisions
	{
		count++;
		for(map < char, TrieNode * > ::iterator it = temp.begin(); it != temp.end(); ++it)
		{
			arr[level] = it -> first;
			node = it -> second;
			if(node -> isWord)
			{
				level++;
				arr[level] = '\0';
				if(rev != 1) cout << endl << "\t\t\t" << arr;
				else
				{
					cout << endl << "\t\t\t" << strrev(arr);
					strrev(arr);
				}
				level--;
			}
			DisplayTrie(it -> second -> child, arr, level + 1, node, rev); // second(value) is node and goes to that node's child
		}
	}
    
    void sortAlphabeticallyUtility(TrieNode *currentNode, char arr[], int level)
    {
        if (currentNode->isWord)
        {
            arr[level] = '\0'; // Null-terminate the string
           // cout << arr << endl;
            string t(arr);
            linesRead.push_back(t);
        }

        for (map<char, TrieNode *>::iterator it = currentNode->child.begin(); it != currentNode->child.end(); ++it)
        {
            char ch = it->first;
            TrieNode *childNode = it->second;

            arr[level] = ch;
            sortAlphabeticallyUtility(childNode, arr, level + 1);
        }
    }
    
	void RegularDisplay(char * str, char * expression, map < char, TrieNode * > temp, TrieNode * node, int level, bool rev)
	{
		for(map < char, TrieNode * > ::iterator it = temp.begin(); it != temp.end();++it)
		{
			str[level] = it -> first;
			node = it -> second;
			if(node -> isWord == true && rev == false)
			{
				level++;
				int i = 0;
				for(int i = level; i < 20; i++)
				{
					str[i] = ' ';
				}
				str[level] = '\0';
				if(Match(expression, str, 0))
				{
					cout << endl << "\t\t\t" << str;
					count++;
				}
				level--;
			}
			if(node -> isWord == true && rev == true)
			{
				level++;
				for(int i = level; i < 20; i++)
				{
					str[i] = ' ';
				}
				str[level] = '\0';
				strrev(str);
				if(Match(expression, str, 0))
				{
					cout << endl << "\t\t\t" << str;
					count++;
				}
				strrev(str);
				level--;
			}
			RegularDisplay(str, expression, it -> second -> child, node, level + 1, rev); // second(value) is node and goes to that node's child
		}
	}

	void InsertNormal()
	{
		fstream file;
		file.open("input.txt", ios::in);
		string a;
		while(getline(file, a))
		{
			string temp= toupper(a);
			insert(temp);
		}
		file.close();
	}
	
	void InsertReverse()
	{
		fstream file;
		file.open("input.txt", ios::in);
		string a;
		while(getline(file, a))
		{
			string temp=toupper(a);
			reverse(temp.begin(), temp.end());
			insert(temp);
		}
		file.close();
	}
	
	void sortAlphabetically()
    {
    	linesRead.clear();//clear the linesRead vector
        char arr[100]; // Assuming a maximum word length of 100 characters
        sortAlphabeticallyUtility(root, arr, 0);
    }
	
};

Trie obj;
Trie rev;
	
void RegularPrint(char * str) // OBJ object is for normal TRIE and REV is for Reverse TRIE(WORDS ARE INSERTED IN REVERSE ORDER)
{   
 
	obj.InsertNormal();
	rev.InsertReverse();
	char str1[20]; // str1 is for storing only alphabets from STR
	int index = 0, i = 1;
	bool flag = false;
	int len = strlen(str) - 1;
	if(str[0] != '.' && str[0] != '*') // for FORWARD ( ABC* , ABC*ABC ETC )  POSTFIX
	{
		for(index = 0; index < strlen(str); index++)
		{
			if(str[index] == '.' || str[index] == '*') // IF * OR . IS IN BETWEEN TOO
				break;
			else str1[index] = str[index];
		}
		str1[index] = '\0';
		TrieNode * temp = obj.getNode(str1); // LAST CHARACTER NODE OF STR1 IS RETURNED FROM GETNODE
		if(temp == nullptr)
		{
			cout << "No Such Possible Word Exist.";
			return;
		}
		map < char, TrieNode * > temp_map = temp -> child;
		if(index + 1 == strlen(str) && str[index] != '.')
		{
			obj.DisplayTrie(temp_map, str1, index, temp, 0);
		}
		else obj.RegularDisplay(str1, str, temp_map, temp, index, 0);
	}
	
	else if((str[0] == '.' || str[0] == '*') && (str[len] != '*' && str[len] != '.'))
	{ // PREFIX (REVERSE) (*ABC ETC)
		i = 0;
		rev.count = 1;
		for(index = strlen(str) - 1; index >= 0; index--)
		{
			if(str[index] == '.' || str[index] == '*') // IF * OR . IS IN BETWEEN TOO
				break;
			else
			{
				str1[i] = str[index];
				i++;
			}
		}
		str1[i] = '\0';
		TrieNode * temp = rev.getNode(str1);
		if(temp == nullptr)
		{
			cout << "\n\t\t\tNo Such Possible Word Exist.";
			return;
		}
		map < char, TrieNode * > temp_map = temp -> child;
		if(index == 0 && str[index] != '.')
		{
			rev.DisplayTrie(temp_map, str1, i, temp, 1); // for *abc no comparision
		}
		else rev.RegularDisplay(str1, str, temp_map, temp, i, 1);
	}
	else
	{ // * or . is B/W BOTH START AND END
		i = 0;
		obj.count = 1;
		map < char, TrieNode * > temp_map = obj.root -> child; // check if correct
		obj.RegularDisplay(str1, str, temp_map, obj.root, i, 0);
	}
	if((obj.count == 0) && (rev.count == 0)) cout << "No such word exist in Record ." << endl;
}

class DoublyNode
{
	public: DoublyNode * next;
	DoublyNode * prev;
	int index;
	DoublyNode(int index)
	{
		this -> index = index;
		next = prev = nullptr;
	}
};

class DLL
{
	DoublyNode * head;
	DoublyNode * tail;
	DoublyNode * current;
	public: DLL() { head = tail = current = nullptr; }
	
	void addSearchedIndex(int index)
	{
		if(head == nullptr)
		{
			head = tail = new DoublyNode(index);
			current = head;
		}
		else
		{
			DoublyNode * newnode = new DoublyNode(index);
			tail -> next = newnode;
			newnode -> prev = tail;
			tail = tail -> next;
			current = tail;
		}
	}
	
	bool searchIFcurrent(int index)
	{
		DoublyNode * temp = head;
		while(temp != nullptr)
		{
			if(temp -> index == index && temp == current) return true;
			temp = temp -> next;
		}
		return false;
	}
	
	bool undo()
	{
		if(current -> prev == nullptr) return false;
		current = current -> prev;
		return true;
	}
	
	bool redo()
	{
		if(current -> next == nullptr) return false;
		current = current -> next;
		return true;
	}
	
	bool checkifEmpty()
	{
		return head==nullptr;
	}
	
	int getCurrentKey() { return current -> index; }
	
	void remove(int key)
	{
		DoublyNode * temp = head;
		if(temp -> next == nullptr)
		{
			delete head;
		}
		else if(head -> index == key)
		{
			delete head;
			head = temp -> next;
		}
		else if(tail -> index == key)
		{
			temp = tail -> prev;
			delete tail;
			temp -> next = nullptr;
			tail = temp;
		}
	}
	

};

DLL searchHistory;
Stack < int > keystack;
Stack < string > textstack;

class Hashing
{
	string * table;
	int capacity;
	int added;
	
	public: 
	Hashing()
	{
		capacity = 50;
		added = 0;
		table = new string[capacity];
		for(int i = 0; i < capacity; i++) table[i] = " ";
	}
	
	float getLoadFactor() { return (float) added / capacity; }
	
	void reHash()
	{
		string * newtable = new string[capacity * 2];
		for(int i = 0; i < capacity * 2; i++)
		{
			if(i <= capacity - 1)
			{
				newtable[i] = table[i];
			}
			else newtable[i] = " ";
		}
		delete[] table;
		table = newtable;
		capacity *= 2;
	}
	
	// uses mid square method
	int hashFunction(string line)
	{
		string temp = toupper(line);
		int asciiSUM = 0;
		for(int i = 0; i < temp.length(); i++) asciiSUM += temp[i];
		int square = asciiSUM * asciiSUM;
		int k = 0, i = 1;
		int * digits = (int * ) calloc(i, sizeof(int));
		while(square > 0)
		{
			digits[k] = square % 10;
			square /= 10;
			k++;
			i++;
			digits = (int * ) realloc(digits, i * sizeof(int));
		}
		int mid = i / 2;
		int key = digits[mid];
		delete[] digits;
		return key;
	}
	
	void createTable()
	{
		fstream fileptr;
		fileptr.open("input.txt", ios::in);
		if(!fileptr)
		{
			cout << "Error opening file" << endl;
			return;
		}
		string line;
		while(getline(fileptr, line))
		{
			linesRead.push_back(line);
			int key = hashFunction(line);
			if(table[key] == " ")
			{
				table[key] = line;
				added++;
			}
			else
			{
				// check for rehashing
				if(getLoadFactor() >= 0.75) reHash();
				// quadratic probing
				int probe = 1;
				while(key + (probe * probe) < capacity)
				{
					if(table[key + (probe * probe)] == " ")
					{
						table[key + (probe * probe)] = line;
						added++;
						break;
					}
					probe++;
				}
			}
		}
		fileptr.close();
	}
	
	bool Search(string text)
	{
		int key = hashFunction(text);
		string temp = toupper(table[key]);
		if(temp == toupper(text))
		{
			searchHistory.addSearchedIndex(key);
			return true;
		}
		else
		{
			int probe = 1;
			while(key + (probe * probe) < capacity)
			{
				temp = toupper(table[key + (probe * probe)]);
				if(temp == toupper(text))
				{
					searchHistory.addSearchedIndex(key + (probe * probe));
					return true;
				}
				else probe++;
			}
		}
		return false;
	}
	
	void display()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for(int i = 0; i < capacity; i++)
		{
			if(table[i] != " ")
			{
				if(searchHistory.searchIFcurrent(i))
				{
					SetConsoleTextAttribute(hConsole, 9);
				}
				else SetConsoleTextAttribute(hConsole, 4);
				cout << "\t\t\t" << table[i] << endl;
			}
		}
		SetConsoleTextAttribute(hConsole, 4);
	}
	
	string getText(int key) { return table[key]; }
	
	void updateTable(string text, int defaultkey = -1)
	{
		if(defaultkey == -1)
		{
			int key = searchHistory.getCurrentKey();
			table[key] = " ";
			searchHistory.remove(key);
		}
		else table[defaultkey] = " ";
		int newkey = hashFunction(text);
		if(table[newkey] == " ")
		{
			table[newkey] = text;
		}
		else
		{
			// check for rehashing
			if(getLoadFactor() >= 0.75) reHash();
			// quadratic probing
			int probe = 1;
			while(newkey + (probe * probe) < capacity)
			{
				if(table[newkey + (probe * probe)] == " ")
				{
					table[newkey + (probe * probe)] = text;
					newkey = newkey + (probe * probe);
					break;
				}
				probe++;
			}
		}
		keystack.push(newkey); // stores the key of edited text incase user wishes to update
		searchHistory.addSearchedIndex(newkey);//edited text is replaced with searched text 
	}
	
    void addtoTable(string text)
	{
		int key = hashFunction(text);
		if(table[key] == " ")
		{
			table[key] = text;
			added++;
		}
		else
		{
			// check for rehashing
			if(getLoadFactor() >= 0.75) reHash();
			// quadratic probing
			int probe = 1;
			while(key + (probe * probe) < capacity)
			{
				if(table[key + (probe * probe)] == " ")
				{
					table[key + (probe * probe)] = text;
					added++;
					break;
				}
				probe++;
			}
		}
	}
	
	
	void deleteFromTable(string text)
	{
		int key = hashFunction(text);
		string temp = toupper(table[key]);
		if(temp == toupper(text))
		{
			table[key] = " ";
			return;
		}
		else
		{
			int probe = 1;
			while(key + (probe * probe) < capacity)
			{
				temp = toupper(table[key + (probe * probe)]);
				if(temp == toupper(text))
				{
					table[key + (probe * probe)] = " ";
				    return;
				}
				else probe++;
			}
		}
	}
};

class TextEditor
{
	Hashing table;
	public: 
	TextEditor() { table.createTable(); }
	
	void searchUsingHash()
	{
		string text;
		//	system("CLS");
		cout << "\n\t\t\tEnter text to search in file: ";
		cin.ignore();
		getline(cin, text);
		if(table.Search(text))
		{
			cout << "\n\t\tSearch results: " << endl;
			table.display();
			cout << endl;
		}
		else cout << "\n\t\tSorry,not found in file." << endl;
	}
	
	void undoSearch()
	{
		if(searchHistory.undo()) table.display();
		else cout << "\t\t\tCannot undo searches (any further)." << endl;
	}
	
	void redoSearch()
	{
		if(searchHistory.redo()) table.display();
		else cout << "\t\t\tCannot redo searches (any further)" << endl;
	}
	
    void updateFile(int k = 1)
	{
		fstream newfile;
		if(k == 1)
		{
			newfile.open("input.txt", ios::out);
			for(int i = 0; i < linesRead.size(); i++)
			{
				newfile << linesRead[i] << endl;
			}
			newfile.close();
		}
		else if(k == 0)
		{
			newfile.open("input.txt", ios::app);
			newfile << linesRead[linesRead.size() - 1] << endl;
			newfile.close();
		}
	}
	
	void editSearchedText()
	{   
	    if(!searchHistory.checkifEmpty())
		{
	    		int key = searchHistory.getCurrentKey();
		
		cout << "\n\n\t\t\tYour most recent searched text is: ";
		cout << table.getText(key) << endl;
		textstack.push(table.getText(key));
		cout << "\n\t\t\tEnter updated text to replace this with: ";
		string updated;
		cin.ignore();
		getline(cin, updated);
		// search in linesRead vector
		for(int i = 0; i < linesRead.size(); i++)
		{
			if(linesRead[i] == table.getText(key))
			{
				linesRead[i] = updated;
				cout << "\n\t\tUpdated successfully!" << endl;
				updateFile();
				table.updateTable(updated);
				break;
			}
		}
		}
	    else cout<<"\n\t\tYou haven't made any searches YET!"<<endl;

	}
	
	void undomostRecentEdit()
	{
		string original = textstack.pop();
		int keyofupdated = keystack.pop();
		string updatedtext = table.getText(keyofupdated);
		cout << "\n\n\t\tYour most recent edit was [" << original << "] replaced with [" << updatedtext << "]" << endl;
		for(int i = 0; i < linesRead.size(); i++)
		{
			if(linesRead[i] == updatedtext)
			{
				linesRead[i] = original;
				cout << "\n\t\tMost recent edit undo-ed successfully!" << endl;
				updateFile();
				table.updateTable(original, keyofupdated);
				break;
			}
		}
	}
	
	void sortData()
    {
	char sortChoice;
	cout << "\n\t\t\tEnter 1 to sort data the lexicographically.";
	cout << "\n\t\t\tEnter any key to sort data the alphabetically.";
	cout << "\n\t\t\tEnter here: ";
	cin >> sortChoice;
	if(sortChoice == '1')
	{
		HeapSort sort;
		sort.heapSort();
		cout << "\n\n\tData sorted lexicographically \n";
		for(int i = 0; i < linesRead.size(); i++) cout << "\n\t\t\t" << linesRead[i];
	}
	else
	{
		if(obj.isEmpty())
		{
			cout << "\n\t\tThe trie is empty!search a lookup and then try again" << endl;
			return;
		}
		obj.sortAlphabetically(); //this is the original trie object(not reversed) used to update the vector of linesRead
		fstream file("input.txt", ios::out);
		cout<<"\n\t\tFile sorted alphabetically using trie"<<endl;
		for(int i = 0; i < linesRead.size(); i++)
		{
			cout << "\n\t\t"<<linesRead[i] << endl;
			file << linesRead[i] << endl;
		}
		file.close();
	}
    }
	
	void expressionLookup()
	{
		cout << "\n\t\tEnter a Regular Expression(postfix or prefix include '*' or '.' only) : ";
		char*b=new char[20];
		cin >> b;
		for(int i=0;i<strlen(b);i++)
		{
			if(b[i]>='	a' && b[i]<='z')
			b[i]-='a'-'A';
		}
		
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "\n\n\t\tLookup results:";
		SetConsoleTextAttribute(hConsole, 9);
		RegularPrint(b);
		SetConsoleTextAttribute(hConsole, 4);
	}
	
    void deleteData()
	{
		vector<string>::iterator it;
		string datatoremove;
		cout << "\n\t\tEnter data to remove from file: ";
		cin.ignore();
		getline(cin, datatoremove);
		//search if data is present in the hashtable
		if(table.Search(datatoremove))
		{
		    it = find(linesRead.begin(), linesRead.end(), datatoremove);
			if(it != linesRead.end())
			{
				linesRead.erase(it);
			}
			table.deleteFromTable(datatoremove);
			updateFile();
			cout<< "\n\t\t[" << datatoremove <<"] removed from file" <<endl;
		}
		else cout<< "\n\t\t[" <<datatoremove <<"] not found in the file" <<endl;
		
	}
	
	void enterData()
	{
		string datatoenter;
		cout << "\n\t\tEnter data to add to file: ";
		cin.ignore();
		getline(cin, datatoenter);
		table.addtoTable(datatoenter);
		linesRead.push_back(datatoenter);
		updateFile(0);
		cout <<"\n\t\t[" << datatoenter << "] added to file" << endl;
	}
};


int main()
{
	TextEditor editor;
	char choice = menu();
	
	while(choice != '9')
	{
		if(choice == '1') editor.searchUsingHash();
		else if(choice == '2') editor.editSearchedText();
		else if(choice == '3') editor.deleteData();
		else if(choice == '4') editor.undoSearch();
		else if(choice == '5') editor.redoSearch();
		else if(choice == '6') editor.sortData();
		else if(choice == '7') editor.expressionLookup();
		else if(choice == '8') editor.enterData();
		else cout << "Invalid choice";
		cout << "\n\nPress any key to continue....";
		getch();
		system("cls");
		choice = menu();
	}
	displayActions();
}
