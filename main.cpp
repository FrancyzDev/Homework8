#include <iostream>
#include <stdexcept>

// TEMPLATE QUEUE
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };
    Node* front;
    Node* rear;
    size_t size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (rear) {
            rear->next = newNode;
        }
        else {
            front = newNode;
        }
        rear = newNode;
        ++size;
    }
    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty";
        }
        Node* temp = front;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        delete temp;
        --size;
    }
    T peek() const {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
        }
        return front->data;
    }
    bool isEmpty() const { return size == 0; }
    size_t getSize() const { return size; }
};

// TEMPLATE TWO LINKED LIST
template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void ShowList() const {
        Node* temp = head;
        std::cout << "Show list:" << std::endl;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        if (head) {
            head->prev = newNode;
        }
        else {
            tail = newNode;
        }
        head = newNode;
        ++size;
    }
    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        newNode->prev = tail;
        if (tail) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        ++size;
    }
    void popFront() {
        if (!head) {
            std::cout << "List is empty";
        }
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        --size;
    }
    void popBack() {
        if (!tail) {
            std::cout << "List is empty";
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        --size;
    }
    bool isEmpty() const { return size == 0; }
    size_t getSize() const { return size; }
};

// TEMPLATE SINGLE LIST
template <typename T>
class SingleLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };
    Node* head;
    size_t size;

public:
    SingleLinkedList() : head(nullptr), size(0) {}

    ~SingleLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void ShowList() const {
        Node* temp = head;
        std::cout << "Show single list:" << std::endl;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        ++size;
    }

    void popFront() {
        if (!head) {
            std::cout << "List is empty" << std::endl;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        --size;
    }
    bool isEmpty() const { return size == 0; }
    size_t getSize() const { return size; }
};

int main() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    std::cout << "Queue front: " << q.peek() << std::endl;
    std::cout << "Dequeue" << std::endl;
    q.dequeue();
    std::cout << "Now queue front: " << q.peek() << std::endl;
    std::cout << "Create double list" << std::endl;
    LinkedList<int> dll;
    std::cout << "Fill double list" << std::endl;
    dll.pushFront(10);
    dll.pushBack(20);
    dll.ShowList();
    std::cout << "popFront method called" << std::endl;
    dll.popFront();
    dll.ShowList();
    std::cout << "Create single list" << std::endl;
    SingleLinkedList<int> sll;
    sll.pushFront(5);
    std::cout << "pushFront 5" << std::endl;
    sll.ShowList();
    std::cout << "popFront method called" << std::endl;
    sll.popFront();
    sll.ShowList();
    return 0;
}
