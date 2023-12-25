#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Event {
public:
    string type;
    double basePrice;
    bool onlineRegistration;

    Event(const string& eventType, double eventPrice, bool onlineReg = false)
        : type(eventType), basePrice(eventPrice), onlineRegistration(onlineReg) {}

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
    vector<string> services;

    Package(const string& packageName, double packageDiscount, double minPrice, double maxPrice, const vector<string>& packageServices)
        : name(packageName), discount(packageDiscount), priceRangeMin(minPrice), priceRangeMax(maxPrice), services(packageServices) {}
};

class Booking {
public:
    Event event;
    Package package;
    string venue;
    double totalPrice;
    bool isCancelled;
    string feedback;

    Booking(const Event& bookedEvent, const Package& bookedPackage, const string& bookedVenue)
        : event(bookedEvent), package(bookedPackage), venue(bookedVenue), isCancelled(false) {
        totalPrice = event.calculateTotalPrice() * (1 - package.discount);
    }

    void displayBookingDetails() const {
        cout << "Booking Details:\n";
        cout << "Event Type: " << event.type << "\n";
        cout << "Venue: " << venue << "\n";
        cout << "Package: " << package.name << "\n";
        cout << "Total Price: $" << totalPrice << "\n";
        cout << "Event " << (event.onlineRegistration ? "supports" : "does not support") << " online registration.\n";
        cout << "Services Included: ";
        for (const auto& service : package.services) {
            cout << service << ", ";
        }
        cout << "\n";
        if (isCancelled) {
            cout << "Booking has been cancelled.\n";
        }
        if (!feedback.empty()) {
            cout << "Feedback: " << feedback << "\n";
        }
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "Event Type: " << event.type << "\n";
            outFile << "Venue: " << venue << "\n";
            outFile << "Package: " << package.name << "\n";
            outFile << "Total Price: $" << totalPrice << "\n";
            outFile << (event.onlineRegistration ? "Online Registration Supported\n" : "No Online Registration\n");
            outFile << "Services Included: ";
            for (const auto& service : package.services) {
                outFile << service << ", ";
            }
            outFile << "\n";
            if (isCancelled) {
                outFile << "Booking has been cancelled.\n";
            }
            if (!feedback.empty()) {
                outFile << "Feedback: " << feedback << "\n";
            }
            outFile.close();
            cout << "Booking details saved to " << filename << "\n";
        } else {
            cerr << "Unable to open file for writing.\n";
        }
    }

    void readFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            inFile.ignore(); // Ignore the newline character left in the buffer
            getline(inFile, event.type);

            inFile >> venue;
            inFile >> package.name;
            inFile >> totalPrice;

            string onlineReg;
            getline(inFile, onlineReg);
            event.onlineRegistration = (onlineReg.find("Online Registration Supported") != string::npos);

            string servicesLine;
            getline(inFile, servicesLine);
            size_t pos = 0;
            string delimiter = ", ";
            while ((pos = servicesLine.find(delimiter)) != string::npos) {
                package.services.push_back(servicesLine.substr(0, pos));
                servicesLine.erase(0, pos + delimiter.length());
            }
            package.services.push_back(servicesLine); // Add the last service

            string cancelledLine;
            getline(inFile, cancelledLine);
            isCancelled = (cancelledLine.find("Booking has been cancelled.") != string::npos);

            getline(inFile, feedback);

            cout << "Booking details read from " << filename << "\n";
            displayBookingDetails();

            inFile.close();
        } else {
            cerr << "Unable to open file for reading.\n";
        }
    }
};

int main() {
	cout<<"*********************************************************************************"<<endl<<
	"                     	WelCome To BOOKING SIDE Our System							" <<endl<<endl<<endl
	<< "                	<<< We Create And You Celebrate >>>                  "<<endl
	<<"*********************************************************************************"<<endl<<endl;
	
    string eventType;
    double eventPrice;
    string venueType;
    string packageName;
    vector<string> services;

    cout << "Enter the type of event: ";
    cin >> eventType;

    cout << "Enter the price range for the event: $";
    cin >> eventPrice;

    Event selectedEvent(eventType, eventPrice);

    cout << "Is the event indoor or outdoor? ";
    cin >> venueType;

    cout << "Choose a package (VIP1, VIP2, VIP3): ";
    cin >> packageName;

    cout << "Enter services separated by commas (e.g., decor,photo,video,catering): ";
    string servicesInput;
    cin.ignore(); // Ignore the newline character left in the buffer
    getline(cin, servicesInput);
    size_t pos = 0;
    string delimiter = ",";
    while ((pos = servicesInput.find(delimiter)) != string::npos) {
        services.push_back(servicesInput.substr(0, pos));
        servicesInput.erase(0, pos + delimiter.length());
    }
    services.push_back(servicesInput); // Add the last service

    double discount;
    double minPrice;
    double maxPrice;

    if (packageName == "VIP3") {
        discount = 0.1;
        minPrice = 500.0;
        maxPrice = 1000.0;
    } else if (packageName == "VIP2") {
        discount = 0.15;
        minPrice = 1001.0;
        maxPrice = 2000.0;
    } else if (packageName == "VIP1") {
        discount = 0.2;
        minPrice = 2001.0;
        maxPrice = 5000.0;
    } else {
        cerr << "Invalid package choice.\n";
        return 1;
    }

    Package selectedPackage(packageName, discount, minPrice, maxPrice, services);
    Booking customerBooking(selectedEvent, selectedPackage, venueType);
    customerBooking.displayBookingDetails();
    customerBooking.saveToFile("booking_details.txt");

    Booking readBooking(selectedEvent, selectedPackage, venueType);
    readBooking.readFromFile("booking_details.txt");

    cout << "\nAdditional Features:\n";
    cout << "1. Online Registration: " << (selectedEvent.onlineRegistration ? "Supported" : "Not Supported") << "\n";
    cout << "2. Cancel the Event? (y/n): ";
    char cancelChoice;
    cin >> cancelChoice;
    if (cancelChoice == 'y' || cancelChoice == 'Y') {
        customerBooking.isCancelled = true;
        cout << "Event has been cancelled.\n";
    }

    cin.ignore();
    cout << "3. Provide Feedback (or press Enter to skip): ";
    getline(cin, customerBooking.feedback);
    if (!customerBooking.feedback.empty()) {
        cout << "Thank you for your feedback!\n";
    }

    cout << "\nUpdated Booking Details:\n";
    customerBooking.displayBookingDetails();

    return 0;
}

