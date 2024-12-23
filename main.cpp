#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Engine {
private:
    double volume;
    string fuelType;
    int horsepower;
public:
    Engine(double volume, string fuelType, int horsepower) : volume(volume), fuelType(fuelType), horsepower(horsepower) {}
    double getVolume() const { return volume; }
    string getFuelType() const { return fuelType; }
    int getPower() const { return horsepower; }
    void displayDetails() const {
        cout << "Engine:\nVolume = " << volume << "L\nFuel Type = " << fuelType << "\nPower = " << horsepower << "HP\n";
    }
    bool operator==(const Engine& other) const {
        return volume == other.volume && fuelType == other.fuelType && horsepower == other.horsepower;
    }
};


class Transmission {
private:
    string type;
public:
    Transmission(string type) : type(type) {}
    string getType() const { return type; }
    void displayDetails() const {
        cout << "Transmission Type = " << type << "\n";
    }
    bool operator==(const Transmission& other) const {
        return type == other.type;
    }
};


class Vehicle {
protected:
    string type;
    string brand;
    string model;
    int year;
    double price;
    Engine engine;
    Transmission transmission;

public:
    Vehicle(string type, string brand, string model, int year, double price, Engine engine, Transmission transmission) : type(type), brand(brand), model(model), year(year), price(price), engine(engine), transmission(transmission) {}
    virtual ~Vehicle() {}
    string getTypeVehicle() const { return type; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    Engine getEngine() const { return engine; }
    Transmission getTransmission() const { return transmission; }
    virtual void displayDetails() const {
        cout << "Vehicle Type = " << type << ", Brand = " << brand << ", Model = " << model << ", Year = " << year << ", Price = " << price << "$\n";
        engine.displayDetails();
        transmission.displayDetails();
    }
};


class Sedan : public Vehicle {
private:
    bool hatch;
public:
    Sedan(string brand, string model, int year, double price, Engine engine, Transmission transmission, bool hatch) : Vehicle("Sedan", brand, model, year, price, engine, transmission), hatch(hatch) {}
    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Hatch: " << (hatch ? "Yes" : "No") << "\n";
    }
};


class Truck : public Vehicle {
private:
    float weight_power;
public:
    Truck(string brand, string model, int year, double price, Engine engine, Transmission transmission, float weight_power) : Vehicle("Truck", brand, model, year, price, engine, transmission), weight_power(weight_power) {}
    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Weight power: " << weight_power << " tons\n";
    }
};


class Motorcycle : public Vehicle {
private:
    double fuel_waste;

public:
    Motorcycle(string brand, string model, int year, double price, Engine engine, Transmission transmission, double fuel_waste) : Vehicle("Motorcycle", brand, model, year, price, engine, transmission), fuel_waste(fuel_waste) {}

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Fuel Consumption: " << fuel_waste << " L/100km\n";
    }
};


class Moped : public Vehicle {
private:
    double max_speed;

public:
    Moped(string brand, string model, int year, double price, Engine engine, Transmission transmission, double max_speed)
        : Vehicle("Moped", brand, model, year, price, engine, transmission), max_speed(max_speed) {}

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Max Speed: " << max_speed << " km/h\n";
    }
};


Vehicle** SearchByType(Vehicle** vehicles, int size, const string& type, int& resultSize) {
    Vehicle** results = new Vehicle * [size];
    resultSize = 0;
    for (int i = 0; i < size; ++i) {
        if (vehicles[i]->getTypeVehicle() == type) {
            results[resultSize++] = vehicles[i];
        }
    }
    Vehicle** resizedResults = new Vehicle * [resultSize];
    for (int i = 0; i < resultSize; ++i) {
        resizedResults[i] = results[i];
    }
    delete[] results;
    return resizedResults;
}


Vehicle** SearchByYearProd(Vehicle** vehicles, int size, int year, int& resultSize) {
    Vehicle** results = new Vehicle* [size];
    resultSize  = 0;
    for (int i = 0; i < size; ++i) {
        if (vehicles[i]->getYear() == year) {
            results[resultSize++] = vehicles[i];
        }
    }
    Vehicle** resizedResults = new Vehicle* [resultSize];
    for (int i = 0; i < resultSize; ++i) {
        resizedResults[i] = results[i];
    }
    delete[] results;
    return resizedResults;
}


Vehicle** SearchByPrice(Vehicle** vehicles, int size, double minPrice, double maxPrice, int& resultSize) {
    Vehicle** results = new Vehicle * [size];
    resultSize = 0;
    for (int i = 0; i < size; ++i) {
        double vehicle_price = vehicles[i]->getPrice();
        if (vehicle_price >= minPrice && vehicle_price <= maxPrice) {
            results[resultSize++] = vehicles[i];
        }
    }
    Vehicle** resizedResults = new Vehicle * [resultSize];
    for (int i = 0; i < resultSize; ++i) {
        resizedResults[i] = results[i];
    }
    delete[] results;
    return resizedResults;
}


Vehicle** SearchBySeveralParameters(Vehicle** vehicles, int size, const string& brand, const string& model, int year, int& resultSize) {
    Vehicle** results = new Vehicle * [size];
    resultSize = 0;
    for (int i = 0; i < size; ++i) {
        if (vehicles[i]->getBrand() == brand && vehicles[i]->getModel() == model && vehicles[i]->getYear() == year) {
            results[resultSize++] = vehicles[i];
        }
    }
    Vehicle** resizedResults = new Vehicle * [resultSize];
    for (int i = 0; i < resultSize; ++i) {
        resizedResults[i] = results[i];
    }
    delete[] results;
    return resizedResults;
}


int main() {
    int size = 4;
    Vehicle** vehicles = new Vehicle * [size];
    vehicles[0] = new Sedan("Toyota", "Camry", 2020, 30000, Engine(2.5, "Petrol", 203), Transmission("Automatic"), true);
    vehicles[1] = new Truck("Ford", "F-150", 2018, 40000, Engine(3.5, "Diesel", 375), Transmission("Manual"), 5.0);
    vehicles[2] = new Motorcycle("Yamaha", "MT-07", 2021, 7500, Engine(0.7, "Petrol", 74), Transmission("Manual"), 4.5);
    vehicles[3] = new Moped("Honda", "Dio", 2019, 1500, Engine(0.1, "Petrol", 8), Transmission("Automatic"), 90);
    for (int i = 0; i < size; ++i) {
        vehicles[i]->displayDetails();
    }
    int sedansResultSize = 0;
    Vehicle** sedans = SearchByType(vehicles, size, "Sedan", sedansResultSize);
    cout << "\nSedans:\n";
    for (int i = 0; i < sedansResultSize; ++i) {
        sedans[i]->displayDetails();
    }
    int yearResultSize = 0;
    Vehicle** year2021 = SearchByYearProd(vehicles, size, 2021, yearResultSize);
    cout << "\nVehicles from 2021:\n";
    for (int i = 0; i < yearResultSize; ++i) {
        year2021[i]->displayDetails();
    }
    int priceResultSize = 0;
    Vehicle** priceRange = SearchByPrice(vehicles, size, 2000, 35000, priceResultSize);
    cout << "\nVehicles priced between $2000 and $35000:\n";
    for (int i = 0; i < priceResultSize; ++i) {
        priceRange[i]->displayDetails();
    }
    int advanceSearchingResultSize = 0;
    Vehicle** advanceSearching = SearchBySeveralParameters(vehicles, size, "Ford", "F-150", 2018, advanceSearchingResultSize);
    cout << "\nVehicles  advance searching:\n";
    for (int i = 0; i < advanceSearchingResultSize; ++i) {
        advanceSearching[i]->displayDetails();
    }
    for (int i = 0; i < size; ++i) {
        delete vehicles[i];
    }
    delete[] vehicles;

    return 0;
}
