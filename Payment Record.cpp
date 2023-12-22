#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class PaymentMethod {
public:
    virtual void makePayment(int amount) = 0;
    virtual void display() const = 0;
    virtual string getPaymentDetails(const string& name, int amount) const = 0;
};

class CreditCard : public PaymentMethod {
private:
    string cardNumber;

public:
    CreditCard(const string& number) : cardNumber(number) {}

    void makePayment(int amount) override {
        cout << "Paid $" << amount << " using credit card ending in " << cardNumber << endl;
    }

    void display() const override {
        cout << "Credit Card: " << cardNumber << endl;
    }

    string getPaymentDetails(const string& name, int amount) const override {
        return name + " - Credit Card: " + cardNumber + " - Amount: $" + to_string(amount);
    }
};

class Cash : public PaymentMethod {
public:
    void makePayment(int amount) override {
        cout << "Paid $" << amount << " in cash" << endl;
    }

    void display() const override {
        cout << "Cash" << endl;
    }

    string getPaymentDetails(const string& name, int amount) const override {
        return name + " - Cash - Amount: $" + to_string(amount);
    }
};

class PaymentHistory {
private:
    vector<PaymentMethod*> paymentMethods;

public:
    void addPaymentMethod(PaymentMethod* method) {
        paymentMethods.push_back(method);
    }

    void displayHistory() const {
        cout << "Payment History:" << endl;
        for (const auto& method : paymentMethods) {
            method->display();
        }
    }

    void saveToFile(const string& customerName) const {
        ofstream file("payment_history.txt", ios::app); // Open in append mode
        if (file.is_open()) {
            for (const auto& method : paymentMethods) {
                int amount = 0; // You may want to modify this based on your actual use case
                file << method->getPaymentDetails(customerName, amount) << endl;
            }
            file.close();
            cout << "Payment history saved to file." << endl;
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }
};

class Customer {
private:
    string name;
    PaymentHistory paymentHistory;

public:
    Customer(const string& customerName) : name(customerName) {}

    void makePayment(PaymentMethod* method, int amount) {
        method->makePayment(amount);
        paymentHistory.addPaymentMethod(method);
    }

    void displayPaymentHistory() const {
        cout << "Customer: " << name << endl;
        paymentHistory.displayHistory();
    }

    void savePaymentHistoryToFile() const {
        paymentHistory.saveToFile(name);
    }
};

int main() {
    cout << "Enter customer name: ";
    string customerName;
    getline(cin, customerName);

    Customer customer(customerName);

    cout << "Choose payment method (1 for Credit Card, 2 for Cash): ";
    int choice;
    cin >> choice;

    PaymentMethod* paymentMethod;
    if (choice == 1) {
        string cardNumber;
        cout << "Enter credit card number: ";
        cin >> cardNumber;
        paymentMethod = new CreditCard(cardNumber);
    } else if (choice == 2) {
        paymentMethod = new Cash();
    } else {
        cerr << "Invalid choice. Exiting." << endl;
        return 1;
    }

    int amount;
    cout << "Enter payment amount: $";
    cin >> amount;

    customer.makePayment(paymentMethod, amount);
    customer.displayPaymentHistory();
    customer.savePaymentHistoryToFile();

    return 0;
}
//  budget 
