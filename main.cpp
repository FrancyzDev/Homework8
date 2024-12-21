#include <iostream>
#include <string>
#include <random>
using namespace std;

//TASK1
class Shape {
private:

public:
	virtual ~Shape() = default;
	virtual double CalculateArea() = 0;
	virtual void Print() = 0;
};

class Rectangle : public Shape {
private:
	double height;
	double width;
public:
	Rectangle(double height, double width) :height(height), width(width) {}
	
	double CalculateArea() 
	{
		return height * width;
	}

	void Print() 
	{
		std::cout << "Type: Rectangle" << "\nHeight: " << height << "\nWidth: " << width << "\nArea: " << CalculateArea() << endl;
	}
};


class Circle : public Shape {
private:
	double radius;
public:
	Circle(double radius) : radius(radius) {}

	double CalculateArea()
	{
		return 3.14 * (radius * radius);
	}

	void Print()
	{
		std::cout << "Type: Circle" << "\nRadius: " << radius << "\nArea: " << CalculateArea() << endl;
	}
};


class Triangle : public Shape {
private:
	double height;
	double osnova;
public:
	Triangle(double height, double osnova) : height(height), osnova(osnova) {}

	double CalculateArea()
	{
		return height * osnova / 2;
	}

	void Print()
	{
		std::cout << "Type: Triangle" << "\nHeight: " << height << "\nOsnova: " << osnova << "\nArea: " << CalculateArea() << endl;
	}
};



//TASK2
class Animal {
private:

public:
	virtual ~Animal() = default;
	virtual void MakeSound() = 0;
	virtual void PrintInfo() = 0;
};

class Dog : public Animal {
public:
	void MakeSound()
	{
		std::cout << "Gav!" << std::endl;
	}

	void PrintInfo()
	{
		std::cout << "This is a dog" << endl;
	}
};


class Cat : public Animal {
public:
	void MakeSound()
	{
		std::cout << "Meow!" << std::endl;
	}

	void PrintInfo()
	{
		std::cout << "This is a cat" << endl;
	}
};


class Bird : public Animal {
public:
	void MakeSound()
	{
		std::cout << "Cvirin'!" << std::endl;
	}

	void PrintInfo()
	{
		std::cout << "This is a bird" << endl;
	}
};


//TASK3
class Account {
protected:
	double balance;
public:
	virtual ~Account() = default;
	virtual void CalculateInterest() = 0;
	virtual void Deposit(double amount) {
		if (amount > 0) balance += amount;
		else std::cout << "Deposit must be positive value" << endl;
	}
};

class SavingsAccount : public Account {
public:
	void CalculateInterest()
	{
		std::cout << "Start balance: " << balance << endl;
		balance *= 1.05;
		std::cout << "Balance aftert calculation: " << balance << endl;
	}
};

class CheckingAccount : public Account {
public:
	void CalculateInterest()
	{
		std::cout << "Start balance: " << balance << endl;
		balance *= 0.98;
		std::cout << "Balance aftert calculation: " << balance << endl;
	}
};

class FixedDepositAccount : public Account {
public:
	void CalculateInterest()
	{
		std::cout << "Start balance: " << balance << endl;
		if (rand() % 2)
		{
			balance *= 1.10;
			std::cout << "Balance aftert calculation: " << balance << endl;
		}
		else {
			std::cout << "Error it is fixed deposit account, you can't calculate interest now, try later" << endl;
		}
	}
};



int main() {
	srand(time(0));
	//TASK1
	Shape* arr[3];
	arr[0] = new Rectangle(5.0, 3.0);
	arr[1] = new Circle(4.0);
	arr[2] = new Triangle(6.0, 2.5);
	for (int i = 0; i < 3; ++i) {
		arr[i]->Print();
		delete arr[i];
	}
	//TASK2
	Animal* arr1[3];
	arr1[0] = new Dog();
	arr1[1] = new Cat();
	arr1[2] = new Bird();
	for (int i = 0; i < 3; ++i) {
		arr1[i]->MakeSound();
		arr1[i]->PrintInfo();
		delete arr1[i];
	}
	//TASK3
	Account* arr2[3];
	arr2[0] = new SavingsAccount();
	arr2[1] = new CheckingAccount();
	arr2[2] = new FixedDepositAccount();
	for (int i = 0; i < 3; ++i) {
		arr2[i]->Deposit(100);
		arr2[i]->CalculateInterest();
		delete arr2[i];
	}
	return 0;
}
