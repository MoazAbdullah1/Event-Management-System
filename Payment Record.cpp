#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class PaymentMethod
{
public:
    virtual void makePayment(int amount) = 0;
    virtual void refund(int amount) = 0;
    virtual void display() const = 0;
    virtual string getPaymentDetails(const string& name, int amount) const = 0;
};


class CreditCard : public PaymentMethod
{
private:
    string cardNumber;

public:
    CreditCard(const string& number) : cardNumber(number) {}

    string getCardNumber() const
    {
        return cardNumber;
    }

    void setCardNumber(const string& number)
    {
        cardNumber = number;
    }

    void makePayment(int amount) override
    {
        cout << "Paid $" << amount << " using credit card ending in " << cardNumber << endl;
    }

    void refund(int amount) override
    {
        cout << "Refunded $" << amount << " to credit card ending in " << cardNumber << endl;
    }

    void display() const override
    {
        cout << "Credit Card: " << cardNumber << endl;
    }

    string getPaymentDetails(const string& name, int amount) const override
    {
        return name + " - Credit Card: " + cardNumber + " - Amount: $" + to_string(amount);
    }
};


class Cash : public PaymentMethod
{
public:
    void makePayment(int amount) override
    {
        cout << "Paid $" << amount << " in cash" << endl;
    }

    void refund(int amount) override
    {
        cout << "Refunded $" << amount << " in cash" << endl;
    }

    void display() const override
    {
        cout << "Cash" << endl;
    }

    string getPaymentDetails(const string& name, int amount) const override
    {
        return name + " - Cash - Amount: $" + to_string(amount);
    }
};


class PaymentHistory
{
public:
    vector<PaymentMethod*> paymentMethods;

public:
    void addPaymentMethod(PaymentMethod* method)
    {
        paymentMethods.push_back(method);
    }

    void displayHistory() const
    {
        cout << "Payment History:" << endl;
        for (const auto& method : paymentMethods)
        {
            method->display();
        }
    }

    void saveToFile(const string& customerName) const
{
    ofstream file("customer_payment_history.txt", ios::app);
    if (file.is_open())
    {
        for (const auto& method : paymentMethods)
        {
            int amount = 0;  // This line initializes the amount to 0
            method->makePayment(amount);  // Use makePayment to get the actual amount
            file << method->getPaymentDetails(customerName, amount) << endl;
        }

        file.close();
        cout << "Payment history saved to file." << endl << endl;
    }
    else
    {
        cerr << "Unable to open file for writing." << endl;
    }
}


    void readFromFile(const string& customerName)
    {
        ifstream file("customer_payment_history.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                PaymentMethod* method = new CreditCard("");
                paymentMethods.push_back(method);
            }

            file.close();
            cout << "Payment history read from file." << endl << endl;
        }
        else
        {
            cerr << "Unable to open file for reading." << endl;
        }
    }

    ~PaymentHistory()
    {
        for (auto method : paymentMethods)
        {
            delete method;
        }
    }
};


class Customer
{
public:
    string name;
    PaymentHistory paymentHistory;
    int totalAmountSpent;

public:
    Customer(const string& customerName) : name(customerName), totalAmountSpent(0) {}

    void makePayment(PaymentMethod* method, int amount)
    {
        method->makePayment(amount);
        paymentHistory.addPaymentMethod(method);
        totalAmountSpent += amount;
    }

    void refundPayment(PaymentMethod* method, int amount)
    {
        method->refund(amount);
        paymentHistory.addPaymentMethod(method);
        totalAmountSpent -= amount;
    }

    void displayPaymentHistory() const
    {
        cout << "Customer: " << name << endl;
        paymentHistory.displayHistory();
    }

    void savePaymentHistoryToFile() const
    {
        paymentHistory.saveToFile(name);
    }

    void readPaymentHistoryFromFile()
    {
        paymentHistory.readFromFile(name);
    }

    void displayProfitAndLoss() const
    {
        cout << "Profit and Loss for " << name << ": $" << totalAmountSpent << endl;
    }
};


class User
{
public:
    string userName;
    string password;

    User(string uN, string Pswd) : userName(uN), password(Pswd) {}

    bool check(const string& uN, const string& Pswd) const
    {
        return (userName == uN && password == Pswd);
    }

    string get() const
    {
        return userName;
    }
};


int main()
{
    cout << "**************************************************************************************************************" << endl
    
         << "                     			WelCome To BOOKING SIDE Of Our System							" << endl
         
         << endl
         << endl
         << "                			<<< We Create And You Celebrate >>>                  " << endl
         << "*************************************************************************************************************" << endl
         << endl
         << "              		<<< To Check Payment Details of Customer you need to login First >>>                     " << endl <<endl
         << "*************************************************************************************************************" << endl
         << endl;

int loginAttempts = 0;
const int maxLoginAttempts = 3;

while (loginAttempts < maxLoginAttempts) {
    string userName;
    string password;

    cout << "						  Manager Name: ";
    cin >> userName;

    cout << "					     Enter Admin password: ";
    cin >> password;

    User U1("MOAZ", "moaz123"), U2("AHMER", "ahmer123");

    if (U1.check(userName, password))
    {
        cout << endl << "					   Login Successfully >>> welcome " << '"' << U1.get() << '"' << endl << endl;
        break;
    }
    else if (U2.check(userName, password))
    {
        cout << endl << "Login Successfully, welcome " << U2.get() << endl << endl;
        break;
    }
    else
    {
        cout << endl << "			Login unsuccessful. Please check your entered details and try again." << endl << endl;
        loginAttempts++;
    }
}

if (loginAttempts == maxLoginAttempts) {
    cout << "			Maximum login attempts reached. Exiting the program." << endl;
    return 1;
}


    cout << "============================================================================================================" << endl
         << endl;

    int choice;
    Customer customer("Umer");
    PaymentMethod* paymentMethod = nullptr;

    customer.readPaymentHistoryFromFile();

    do
{
    cout << "Menu:" << endl;
    cout << "1. Make a Payment" << endl;
    cout << "2. Display Payment History" << endl;
    cout << "3. Save Payment History to File" << endl;
    cout << "4. Process Refund" << endl;
    cout << "5. Display Profit and Loss" << endl;
    cout << "0. Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        int paymentChoice;

        while (true)
        {
            cout << "Enter payment choice (1 for Credit Card, 2 for Cash): ";
            cin >> paymentChoice;

            if (paymentChoice == 1)
            {
                string cardNumber;
                cout << "Enter credit card number: ";
                cin >> cardNumber;
                paymentMethod = new CreditCard(cardNumber);
                break;
            }
            else if (paymentChoice == 2)
            {
                paymentMethod = new Cash();
                break;
            }
            else
            {
                cerr << "Invalid choice. Please enter 1 or 2." << endl;
            }
        }

        int amount;
        cout << "Enter payment amount: $";
        cin >> amount;

        customer.makePayment(paymentMethod, amount);
        break;
        
    }
    case 2:
        customer.displayPaymentHistory();
        break;
        
    case 3:
        customer.savePaymentHistoryToFile();
        break;
        
    case 4:
    {
        int refundChoice;
        PaymentMethod* refundMethod = nullptr;
        cout << "Choose payment method for refund (1 for Credit Card, 2 for Cash): ";
        cin >> refundChoice;

        if (refundChoice == 1)
        {
            string cardNumber;
            cout << "Enter credit card number: ";
            cin >> cardNumber;
            refundMethod = new CreditCard(cardNumber);
        }
        else if (refundChoice == 2)
        {
            refundMethod = new Cash();
        }
        else
        {
            cerr << "Invalid choice. Please Enter 1 OR 2." << endl;
            break;
        }

        int refundAmount;
        cout << "Enter remaining amount to return to the customer: $";
        cin >> refundAmount;

        customer.refundPayment(refundMethod, refundAmount);
        break;
        
    }
    
    case 5:
        customer.displayProfitAndLoss();
        break;
        
    case 0:
        cout << "Exiting the program." << endl;
        break;
        
    default:
        cerr << "Invalid choice. Please Enter Valid Option..." << endl;
    }

	} while (choice != 0);

    
    cout<<endl;
    customer.paymentHistory.readFromFile("customer_payment_history.txt");


    cout << endl
         << " *********************************************************************************************************" << endl
         << "					Thank You For using Our Services" << endl;

    return 0;
    
}



