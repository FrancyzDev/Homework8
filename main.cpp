#include <iostream>
#include <stdexcept>

// TEMPLATE QUEUE
template <typename T>
class Queue {
private:
    class Node
    {
    private:
        T data;
        Node* next;
        Node* prev;
    public:
        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
        T& GetData()
        {
            return data;
        }
        void SetData(T data)
        {
            this->data = data;
        }
        Node* GetNext() const
        {
            return next;
        }
        void SetNext(Node* next)
        {
            this->next = next;
        }
        Node* GetPrev() const
        {
            return prev;
        }
        void SetPrev(Node* prev)
        {
            this->prev = prev;
        }
    };
    Node* front;
    Node* rear;
    size_t size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    ~Queue() {
        while (!isEmpty()) {
            DequeueFront();
        }
    }
    void EnqueueBack(const T& value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->SetNext(newNode);
            newNode->SetPrev(rear);
            rear = newNode;
        }
        ++size;
    }

    void EnqueueFront(const T& value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = newNode;
            rear = newNode;
        }
        else {
            newNode->SetNext(front);
            front->SetPrev(newNode);
            front = newNode;
        }
        ++size;
    }

    T& Front() {
        if (front == nullptr) {
            throw std::runtime_error("Queue is empty!");
        }
        return front->GetData();
    }

    T Front() const {
        return Front();
    }

    T& Back() {
        if (rear == nullptr) {
            throw std::runtime_error("Queue is empty!");
        }
        return rear->GetData();
    }

    T Back() const {
        return Back();
    }

    void DequeueFront() {
        if (front == nullptr) {
            return;
        }
        Node* temp = front;
        front = front->GetNext();
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
    }

    void DequeueBack() {
        if (rear == nullptr) {
            return;
        }
        Node* temp = rear;
        rear = rear->GetPrev();
        if (rear == nullptr) {
            front = nullptr;
        }
        delete temp;
        size--;
    }

    bool isEmpty() const { return size == 0; }
    size_t Size() const { return size; }
};


template<typename T>
class Stack {
private:
    class Node
    {
    private:
        T data;
        Node* next;
    public:
        Node(T data) : data(data), next(nullptr) {}
        T& GetData()
        {
            return data;
        }
        void SetData(T data)
        {
            this->data = data;
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
    Node* top;
    size_t size;
public:
    Stack() : top(nullptr), size(0) {}
    size_t GetSize() const {
        return size;
    }
    void Push(T data) {
        Node* newNode = new Node(data);
        newNode->SetNext(top);
        top = newNode;
        size++;
    }

    T& Peek() {
        if (top == nullptr) {
            throw std::runtime_error("Stack is empty!");
        }
        return top->GetData();
    }
    const T Peek() const {
        return Peek();
    }
    void Pop() {
        if (top == nullptr) {
            throw std::runtime_error("Stack is empty");
        }
        Node* temp = top;
        top = top->GetNext();
        delete temp;
        size--;
    }
    ~Stack() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->GetNext();
            delete temp;
        }
    }
};


int main() {
    Queue<int> queue;
    queue.EnqueueBack(9);
    queue.EnqueueBack(1);
    queue.EnqueueBack(5);
    queue.EnqueueBack(7);
    queue.EnqueueBack(3);

    for (size_t i = queue.Size(); i > 0; --i) {
        std::cout << queue.Front() << std::endl;
        queue.DequeueFront();
    }
    std::cout << std::endl;

    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(6);
    stack.Push(9);
    stack.Push(123);
    while (stack.GetSize() != 0) {
        std::cout << stack.Peek() << std::endl;
        stack.Pop();
    }

    return 0;
}
