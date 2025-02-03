#include <iostream>
#include <vector>
#include <memory>
#include <string>

// TASK1
class Person 
{
public:
    virtual void info() const = 0;
    virtual ~Person() = default;
};

class Student : public Person 
{
    std::string name;
public:
    Student(const std::string& name) : name(name) {}
    void info() const override 
    {
        std::cout << "Student: " << name << std::endl;
    }
};

class Teacher : public Person 
{
    std::string name;
public:
    Teacher(const std::string& name) : name(name) {}
    void info() const override 
    {
        std::cout << "Teacher: " << name << std::endl;
    }
};

class School {
    std::vector<Person*> people;
public:
    void addPerson(Person* person) 
    {
        people.push_back(person);
    }

    void listPeople() const 
    {
        for (const auto& person : people) 
        {
            if (dynamic_cast<Student*>(person)) 
            {
                person->info();
            }
            else if (dynamic_cast<Teacher*>(person)) 
            {
                person->info();
            }
        }
    }
};

// TASK2
class SmartSchool 
{
    std::vector<std::shared_ptr<Person>> people;
public:
    void addPerson(std::shared_ptr<Person> person) 
    {
        people.push_back(person);
    }

    void listPeople() const 
    {
        for (const auto& person : people)
        {
            if (dynamic_cast<Student*>(person.get())) 
            {
                person->info();
            }
            else if (dynamic_cast<Teacher*>(person.get())) 
            {
                person->info();
            }
        }
    }
};

// TASK3
class Engine 
{
public:
    virtual void details() const = 0;
    virtual ~Engine() = default;
};

class PetrolEngine : public Engine 
{
    int power;
public:
    PetrolEngine(int power) : power(power) {}
    void details() const override 
    {
        std::cout << "Petrol Engine power: " << power << " HP" << std::endl;
    }
};

class ElectricEngine : public Engine 
{
    int power;
public:
    ElectricEngine(int power) : power(power) {}
    void details() const override 
    {
        std::cout << "Electric Engine, Power: " << power << " HP" << std::endl;
    }
};

class Car 
{
    std::shared_ptr<Engine> engine;
    std::string name;
    int serialNumber;
public:
    Car(std::shared_ptr<Engine> eng, const std::string& name, int sn) : engine(eng), name(name), serialNumber(sn) {}
    void info() const 
    {
        std::cout << "Car: " << name << ", Serial: " << serialNumber << std::endl;
        engine->details();
    }
    std::shared_ptr<Engine> getEngine() const 
    {
        return engine;
    }
};

class Company 
{
    std::vector<std::shared_ptr<Car>> cars;
    const size_t maxSize = 5;
public:
    void addCar(std::shared_ptr<Car> car) 
    {
        if (cars.size() < maxSize)
        {
            cars.push_back(car);
        }
        else
        {
            std::cout << "Car park is full!" << std::endl;
        }
    }

    void listCars() const 
    {
        for (const auto& car : cars) 
        {
            car->info();

            if (dynamic_cast<PetrolEngine*>(car->getEngine().get()))
            {
                std::cout << " - Petrol Engine detected." << std::endl;
            }
            else if (dynamic_cast<ElectricEngine*>(car->getEngine().get())) 
            {
                std::cout << " - Electric Engine detected." << std::endl;
            }

            auto baseEngine = static_cast<Engine*>(car->getEngine().get());
            baseEngine->details();
        }
    }
};

int main() {
    std::cout << "TASK1" << std::endl;
    School school;
    Student* s1 = new Student("Alice");
    Teacher* t1 = new Teacher("Mr. Smith");
    school.addPerson(s1);
    school.addPerson(t1);
    school.listPeople();

    Person* basePerson = static_cast<Person*>(s1);
    basePerson->info();

    delete s1;
    delete t1;

    std::cout << "TASK2" << std::endl;
    SmartSchool smartSchool;
    smartSchool.addPerson(std::make_shared<Student>("Bob"));
    smartSchool.addPerson(std::make_shared<Teacher>("Ms. Johnson"));
    smartSchool.listPeople();

    std::cout << "TASK3" << std::endl;
    Company company;
    auto car1 = std::make_shared<Car>(std::make_shared<PetrolEngine>(150), "Ford", 1234);
    auto car2 = std::make_shared<Car>(std::make_shared<ElectricEngine>(200), "Tesla", 5678);
    company.addCar(car1);
    company.addCar(car2);
    company.listCars();

    return 0;
}
