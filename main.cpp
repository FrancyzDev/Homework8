#include <iostream>
#include <string>
class Customer;
class RoomBooking {
private:
	int roomNumber;
	int* daysBooked;
	size_t daysCount;
	Customer* customer;
public:
	RoomBooking(int newRoomNumber, int* newDaysBooked, size_t newDaysCount, Customer* newCustomer)
		: roomNumber(newRoomNumber), daysBooked(newDaysBooked), daysCount(newDaysCount), customer(newCustomer) {}
	RoomBooking(int newRoomNumber, int* newDaysBooked, size_t newDaysCount) : roomNumber(newRoomNumber), daysBooked(newDaysBooked), daysCount(newDaysCount) {}
	RoomBooking() : RoomBooking(0, nullptr, 0, nullptr) {};
	RoomBooking(const RoomBooking & obj) {
		roomNumber = obj.roomNumber;
		daysCount = obj.daysCount;
		daysBooked = new int[daysCount];
		for (size_t i = 0; i < daysCount; ++i) {
			daysBooked[i] = obj.daysBooked[i];
		}
		customer = obj.customer;
	};
	RoomBooking(RoomBooking&& obj) noexcept
		: roomNumber(obj.roomNumber), daysBooked(obj.daysBooked),
		daysCount(obj.daysCount), customer(obj.customer) {
		obj.daysBooked = nullptr;
		obj.customer = nullptr;
		obj.daysCount = 0;
	}

	~RoomBooking() {
		delete[] daysBooked;
	}

	void addDay(int day) {
		int* newDays = new int[daysCount + 1];
		for (size_t i = 0; i < daysCount; ++i) {
			newDays[i] = daysBooked[i];
		}
		newDays[daysCount] = day;
		delete[] daysBooked;
		daysBooked = newDays;
		daysCount += 1;
	}
	void removeDay(int day) {
		size_t index = -1;
		for (size_t i = 0; i < daysCount; ++i) {
			if (daysBooked[i] == day) {
				index = i;
				break;
			}
		}
		if (index == -1) return;
		int* newDays = new int[daysCount - 1];
		for (size_t i = 0, j = 0; i < daysCount; ++i) {
			if (i != index) {
				newDays[j] = daysBooked[i];
				j++;
			}
		}
		delete[] daysBooked;
		daysBooked = newDays;
		daysCount -= 1;
	}

	void printBooking() {
		std::cout << "Room Number: " << roomNumber << std::endl << "Days Booked: ";
		for (size_t i = 0; i < daysCount; ++i) {
			std::cout << daysBooked[i] << " ";
		}
	}

	RoomBooking& operator=(const RoomBooking& obj) {
		if (this == &obj) return *this;
		delete[] daysBooked;
		roomNumber = obj.roomNumber;
		daysCount = obj.daysCount;
		daysBooked = new int[daysCount];
		for (size_t i = 0; i < daysCount; ++i) {
			daysBooked[i] = obj.daysBooked[i];
		}
		customer = obj.customer;
		return *this;
	}
	RoomBooking& operator=(RoomBooking&& obj) noexcept {
		if (this == &obj) return *this;
		delete[] daysBooked;
		roomNumber = obj.roomNumber;
		daysBooked = obj.daysBooked;
		daysCount = obj.daysCount;
		customer = obj.customer;
		obj.daysBooked = nullptr;
		obj.customer = nullptr;
		obj.daysCount = 0;
		return *this;
	}
	RoomBooking operator+(const RoomBooking& obj) {
		if (customer != obj.customer) {
			std::cout << "Can't assign booking day to another customer";
		}
		int* newDays = new int[daysCount + obj.daysCount];
		for (size_t i = 0; i < daysCount; ++i) {
			newDays[i] = daysBooked[i];
		}
		for (size_t i = 0; i < obj.daysCount; ++i) {
			newDays[daysCount + i] = obj.daysBooked[i];
		}
		return RoomBooking(roomNumber, newDays, daysCount + obj.daysCount, customer);
	}
	friend std::ostream& operator<<(std::ostream& stream, const RoomBooking& obj);
};
std::ostream& operator<<(std::ostream& stream, const RoomBooking& obj) {
	stream << "Room Number: " << obj.roomNumber << std::endl << "Days Booked: ";
	for (size_t i = 0; i < obj.daysCount; ++i) {
		stream << obj.daysBooked[i] << " ";
	}
	return stream;
}

class Customer {
private:
	std::string name;
	int customerID;
	RoomBooking* currentBooking;
public:
	Customer(std::string newName, int newCustomerID) : name(newName), customerID(newCustomerID), currentBooking(nullptr) {}

	Customer(const Customer & obj) : name(obj.name), customerID(obj.customerID), currentBooking(obj.currentBooking) {}
	Customer() : name("None"), customerID(0), currentBooking(nullptr) {};
	~Customer() {
		delete currentBooking;
	}
	void makeBooking(RoomBooking * booking) {
		if (currentBooking != nullptr) {
			delete currentBooking;
		}
		currentBooking = booking;
	}
	void cancelBooking() {
		delete currentBooking;
		currentBooking = nullptr;
	}
	void printCustomerInfo() {
		std::cout << "Customer Name: " << name << std::endl << "Customer ID: " << customerID;
		if (currentBooking) {
			std::cout << std::endl << "Current Booking: " << std::endl << *currentBooking;
		}
		else {
			std::cout << std::endl << "No current booking";
		}
	}
	friend std::ostream& operator<< (std::ostream& stream, const Customer& obj);
};


std::ostream& operator<< (std::ostream& stream, const Customer& obj) {
	return stream << "Name: " << obj.name << std::endl << "Customer ID: " << obj.customerID;
}

#include <iostream>
#include <string>


int main() {
	Customer customer1("Artem", 228);
	Customer customer2("Test2", 1337);
	int* days1 =  new int [3] { 1, 2, 3 };
	int * days2 = new int[2] { 4, 5 };
	int* days3 = new int[2] { 7, 11 };
	RoomBooking booking1(101, days1, 3, &customer1);
	RoomBooking booking2(102, days2, 2, &customer2);
	booking1.printBooking();
	std::cout << std::endl;
	booking2.printBooking();
	std::cout << std::endl << "Adding and removing days: " << std::endl;
	booking1.addDay(4);
	booking1.removeDay(2);
	booking1.printBooking();
	std::cout << std::endl << "Assigning booking to customer: " << std::endl;
	Customer customer3("Test3", 12);
	customer3.makeBooking(new RoomBooking(105, days3, 2, &customer3));
	customer3.printCustomerInfo();
	std::cout << std::endl << "Canceling booking: " << std::endl;
	customer1.cancelBooking();
	customer1.printCustomerInfo();
	return 0;
}

