#include <iostream>
#include <string>
using namespace std;

// TASK1
class Person {
private:
	string name;
	int age;
public:
	Person(string name, int age) : name(name), age(age) {}
	virtual ~Person() {}
	virtual string getInfo() {
		return "Name: " + name + ", Age: " + to_string(age);
	}
};

class Child : public Person {
private:
	string parentName;
public:
	Child(string name, int age, string parentName) : Person(name, age), parentName(parentName) {}
	string getInfo() {
		return Person::getInfo() + ", Parent: " + parentName;
	}
};

//TASK2
class Vehicle {
private:
	string brand;
	int year;
public:
	Vehicle(string brand, int year) : brand(brand), year(year) {};
	virtual string getDescription() {
		return "Brand: " + brand + ", Year" + to_string(year);
	}
	virtual ~Vehicle() {}
};

class Car : public Vehicle {
private:
	string model;
	int mileage;
public:
	Car(string brand, int year, string model, int mileage) : Vehicle(brand, year), model(model), mileage(mileage) {}
	~Car() {}
	string getDescription() {
		return Vehicle::getDescription() + ", Model: " + model + ", Mileage: " + to_string(mileage) + "km";
	}
};

//TASK3
class Employee {
private:
	string name;
	string position;
	double salary;
public:
	Employee(string name, string postion, double salary) : name(name), position(position), salary(salary) {}
	virtual ~Employee() {}
	virtual string getDetails() {
		return "Name: " + name + ", Position: " + position + ", Salary: " + to_string(salary);
	}
};

class Manager : public Employee {
private:
	string department;
public:
	Manager(string name, string position, double salary, string department) : Employee(name, position, salary), department(department) {};
	~Manager() {}
	string getDetails() {
		return Employee::getDetails() + ", Department: " + department;
	}
};

int main() {
	//TASK1
	Person Test1Person("Testik", 32);
	Child Test1Child("Test1", 12, "Tetsik");
	cout << Test1Person.getInfo() << endl << Test1Child.getInfo() << endl;
	//TASK2
	Vehicle Test1Vehicle("BMW", 2022);
	Car Test1Car("BMW", 2022, "IX8700", 400);
	cout << Test1Vehicle.getDescription() << endl << Test1Car.getDescription() << endl;
	//TASK3
	Employee Test1Employee("Alice", "Developer", 50000.00);
	Manager Test1Manager("Alice", "Developer", 50000.00, "IT");
	cout << Test1Employee.getDetails() << endl << Test1Manager.getDetails() << endl;
	return 0;
}