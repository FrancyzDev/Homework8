#include <iostream>
using namespace std;

class MyInt
{
private:
	int value;
public:
	MyInt(int value)
	{
		this->value = value;
	}
	void SetData(int value)
	{
		this->value = value;
	}
	int GetData() const
	{
		return value;
	}
};

class Node
{
private:
	MyInt myInt;
	Node* next /*= nullptr*/;
public:
	Node(MyInt myInt) : myInt(myInt), next(nullptr) {}
	MyInt GetMyInt() const
	{
		return myInt;
	}
	void SetMyInt(MyInt myInt)
	{
		this->myInt = myInt;
	}
	Node* GetNext() const
	{
		return next;
	}
	void SetNext(Node* next)
	{
		this->next = next;
	}
};

class LinkedList
{
private:
	Node* head;
	size_t size;
public:
	LinkedList() : head(nullptr), size(0) {}
	size_t GetSize() const
	{
		return size;
	}
	void InsertAtEnd(MyInt value)
	{
		if (head == nullptr)
		{
			InsertAtBeginning(value);
			return;
		}
		Node* newNode = new Node(value);

		Node* temp = head;
		while (temp->GetNext() != nullptr)
		{
			temp = temp->GetNext();
		}
		temp->SetNext(newNode);
		size++;
	}
	void InsertAtBeginning(MyInt value)
	{
		Node* newNode = new Node(value);
		newNode->SetNext(head);
		head = newNode;
		size++;
	}
	void DeleteFromBeginning() {
		if (head == nullptr) return;
		Node* temp = head;
		head = head->GetNext();
		delete temp;
		size--;
	}

	void DeleteFromEnd() {
		if (head == nullptr) return;
		if (head->GetNext() == nullptr)
		{
			delete head;
			head = nullptr;
			size--;
			return;
		}
		Node* temp = head;
		while (temp->GetNext()->GetNext() != nullptr)
		{
			temp = temp->GetNext();
		}
		delete temp->GetNext();
		temp->SetNext(nullptr);
		size--;
	}

	const MyInt& operator[](size_t index) {
		if (index >= size) std::cout << "Index out of range" << std::endl;
		Node* temp = head;
		for (size_t i = 0; i < index; ++i)
		{
			temp = temp->GetNext();
		}
		return temp->GetMyInt();
	}
	Node * Begin() {
		return head;
	}
	~LinkedList()
	{
		while (head != nullptr)
		{
			Node* temp = head;
			head = head->GetNext();
			delete temp;
		}
	}
};

int main()
{
	LinkedList* list = new LinkedList();
	list->InsertAtBeginning(MyInt(5));
	list->InsertAtEnd(7);
	list->InsertAtEnd(4);
	list->InsertAtEnd(3);
	list->DeleteFromEnd();
	list->DeleteFromBeginning();
	std::cout << "Get element with index 1: " << list->operator[](1).GetData() << std::endl;
	std::cout << "Loop through list: " << std::endl;
	for (Node* it = list->Begin(); it != nullptr; it = it->GetNext()) {
		if (it->GetNext() == nullptr) {
			std::cout << it->GetMyInt().GetData();
		}
		else {
			std::cout << it->GetMyInt().GetData() << " ";
		}
	}
}