#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Event {
public:
    string type;
    double basePrice;

    Event(const string& eventType, double eventPrice)
        : type(eventType), basePrice(eventPrice) {}

    virtual double calculateTotalPrice() const {
        return basePrice;
    }
};

class Package {
public:
    string name;
    double discount;
    double priceRangeMin;
    double priceRangeMax;

    Package(const string& packageName, double packageDiscount, double minPrice, double maxPrice)
        : name(packageName), discount(packageDiscount), priceRangeMin(minPrice), priceRangeMax(maxPrice) {}
};

class Booking {
public:
    Event event;
    Package package;
    string venue;
    double totalPrice;

    Booking(const Event& bookedEvent, const Package& bookedPackage, const string& bookedVenue)
        : event(bookedEvent), package(bookedPackage), venue(bookedVenue) {
        totalPrice = event.calculateTotalPrice() * (1 - package.discount);
    }

    void displayBookingDetails() const {
        cout << "Booking Details:\n";
        cout << "Event Type: " << event.type << "\n";
        cout << "Venue: " << venue << "\n";
        cout << "Package: " << package.name << "\n";
        cout << "Total Price: $" << totalPrice << "\n";
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "Event Type: " << event.type << "\n";
            outFile << "Venue: " << venue << "\n";
            outFile << "Package: " << package.name << "\n";
            outFile << "Total Price: $" << totalPrice << "\n";
            outFile.close();
            cout << "Booking details saved to " << filename << "\n";
        } else {
            cerr << "Unable to open file for writing.\n";
        }
    }
};

int main() {
    string eventType;
    double eventPrice;
    string venueType;
    string packageName;

    cout << "Enter the type of event: ";
    cin >> eventType;

    cout << "Enter the price range for the event: $";
    cin >> eventPrice;

    Event selectedEvent(eventType, eventPrice);

    cout << "Is the event indoor or outdoor? ";
    cin >> venueType;

    cout << "Choose a package (VIP1, VIP2, VIP3): ";
    cin >> packageName;

    double discount;
    double minPrice;
    double maxPrice;

    if (packageName == "VIP1") {
        discount = 0.1;
        minPrice = 500.0;
        maxPrice = 1000.0;
    } else if (packageName == "VIP2") {
        discount = 0.15;
        minPrice = 1001.0;
        maxPrice = 2000.0;
    } else if (packageName == "VIP3") {
        discount = 0.2;
        minPrice = 2001.0;
        maxPrice = 5000.0;
    } else {
        cerr << "Invalid package choice.\n";
        return 1;
    }

    Package selectedPackage(packageName, discount, minPrice, maxPrice);
    Booking customerBooking(selectedEvent, selectedPackage, venueType);
    customerBooking.displayBookingDetails();
    customerBooking.saveToFile("booking_details.txt");

    return 0;
}
// Online reg or physical
// cancel event
// feedback

