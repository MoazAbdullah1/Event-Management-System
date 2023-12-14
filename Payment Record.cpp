#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class PaymentMethod {
public:
    virtual void makePayment(double amount) = 0;
    virtual void display() const = 0;
    virtual string getPaymentType() const = 0;
    virtual ~PaymentMethod() {}
};

class CreditCard : public PaymentMethod {
private:
    string cardNumber;

public:
    CreditCard(const string& number) : cardNumber(number) {}

    void makePayment(double amount) override {
        cout << "Paid $" << amount << " using credit card ending in " << cardNumber.substr(cardNumber.length() - 4) << endl;
    }

    void display() const override {
        cout << "Credit Card: **** **** **** " << cardNumber.substr(cardNumber.length() - 4) << endl;
    }

    string getPaymentType() const override {
        return "CreditCard";
    }
};

class Cash : public PaymentMethod {
public:
    void makePayment(double amount) override {
        cout << "Paid $" << amount << " in cash" << endl;
    }

    void display() const override {
        cout << "Cash" << endl;
    }

    string getPaymentType() const override {
        return "Cash";
    }
};

class PaymentHistory {
private:
    vector<PaymentMethod*> paymentMethods;

public:
    ~PaymentHistory() {
        for (auto method : paymentMethods) {
            delete method;
        }
    }

    void addPaymentMethod(PaymentMethod* method) {
        paymentMethods.push_back(method);
    }

    void displayHistory() const {
        cout << "Payment History:" << endl;
        for (const auto& method : paymentMethods) {
            method->display();
        }
    }

    void saveToFile() const {
        ofstream file("payment_history.txt");
        if (file.is_open()) {
            for (const auto& method : paymentMethods) {
                file << method->getPaymentType() << endl;
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

    void makePayment(PaymentMethod* method, double amount) {
        method->makePayment(amount);
        paymentHistory.addPaymentMethod(method);
    }

    void displayPaymentHistory() const {
        cout << "Customer: " << name << endl;
        paymentHistory.displayHistory();
    }

    void savePaymentHistoryToFile() const {
        paymentHistory.saveToFile();
    }
};

int main() {
    Customer customer("John Doe");

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

    double amount;
    cout << "Enter payment amount: $";
    cin >> amount;

    customer.makePayment(paymentMethod, amount);
    customer.displayPaymentHistory();
    customer.savePaymentHistoryToFile();

//    delete paymentMethod;

    return 0;
}

