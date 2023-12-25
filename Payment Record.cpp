#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class PaymentMethod {
public:
    virtual void makePayment(int amount) = 0;
    virtual void refund(int amount) = 0;
    virtual void display() const = 0;
    virtual string getPaymentDetails(const string& name, int amount) const = 0;
};

class CreditCard : public PaymentMethod {
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

class Cash : public PaymentMethod {
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
        ofstream file("payment_history.txt", ios::app);
        if (file.is_open()) {
            for (const auto& method : paymentMethods) {
                int amount;
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
    int totalAmountSpent;
    
public:
    Customer(const string& customerName) : name(customerName), totalAmountSpent(0) {}

    void makePayment(PaymentMethod* method, int amount) {
        method->makePayment(amount);
        paymentHistory.addPaymentMethod(method);
        totalAmountSpent += amount;
    }

    void refundPayment(PaymentMethod* method, int amount) {
        method->refund(amount);
        totalAmountSpent -= amount;
    }

    void displayPaymentHistory() const {
        cout << "Customer: " << name << endl;
        paymentHistory.displayHistory();
    }

    void savePaymentHistoryToFile() const {
        paymentHistory.saveToFile(name);
    }

    void displayProfitAndLoss() const {
        cout << "Profit and Loss for " << name << ": $" << totalAmountSpent << endl;
    }
};

class User
{
	public:
	string userName;
	string password;
	
	User(string uN,string Pswd ):userName(uN),password(Pswd){};
	    
		bool check(const string& uN,const string& Pswd) const {
		return (userName == uN && password == Pswd );
	}
	
	string get(){
		return userName;
	}
	
};

int main() {
	cout<<"**************************************************************************************************************"<<endl
	<<"                     			WelCome To BOOKING SIDE Of Our System							" <<endl<<endl<<endl
	<< "                			<<< We Create And You Celebrate >>>                  "<<endl
	<<"*************************************************************************************************************"<<endl<<endl;
	
	cout<<"              		<<To Check Payment Details of Customer you need to login First>>                     "<<endl 
	<<"*************************************************************************************************************"<<endl<<endl;
	
	string userName;
	string password;
	
	cout<<"						Manager Name : ";
	cin>>userName;
	
	cout<<"					  Enter Admin password : ";
	cin>>password;
	
	User U1("MOAZ", "moaz123"), U2("AHMER", "ahmer123");
	
	string Password;
	if (U1.check(userName,password))
	{
		cout<<endl<<"					  Login Succesfully welcome "<<U1.get() <<endl<<endl;
	}
	else if (U2.check(userName, password)){
		cout<<endl<<"					  Login Succesfully welcome "<<U2.get()<<endl<<endl;
	}
	else{ 
		cout<<endl<<"					  login unsuccessfull Plz Check you Entered Details Again... "<<endl;
	}
	
	cout<<"=========================================================================================================="<<endl<<endl;
	
    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Make a Payment" << endl;
        cout << "2. Display Payment History" << endl;
        cout << "3. Save Payment History to File" << endl;
        cout << "4. Process Refund" << endl;
        cout << "5. Display Profit and Loss" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter customer name: ";
                string customerName;
                cin.ignore();
                getline(cin, customerName);

                Customer customer(customerName);

                cout << "Choose payment method (1 for Credit Card, 2 for Cash): ";
                int paymentChoice;
                cin >> paymentChoice;

                PaymentMethod* paymentMethod;
                if (paymentChoice == 1) {
                    string cardNumber;
                    cout << "Enter credit card number: ";
                    cin >> cardNumber;
                    paymentMethod = new CreditCard(cardNumber);
                } else if (paymentChoice == 2) {
                    paymentMethod = new Cash();
                } else {
                    cerr << "Invalid choice. Exiting." << endl;
                    return 1;
                }

                int amount;
                cout << "Enter payment amount: $";
                cin >> amount;

                customer.makePayment(paymentMethod, amount);
                delete paymentMethod;
                break;
            }
            case 2: {
                cout << "Enter customer name: ";
                string customerName;
                cin.ignore();
                getline(cin, customerName);

                Customer customer(customerName);
                customer.displayPaymentHistory();
                break;
            }
            case 3: {
                cout << "Enter customer name: ";
                string customerName;
                cin.ignore();
                getline(cin, customerName);

                Customer customer(customerName);
                customer.savePaymentHistoryToFile();
                break;
            }
            case 4: {
                cout << "Enter customer name: ";
                string customerName;
                cin.ignore();
                getline(cin, customerName);

                Customer customer(customerName);

                cout << "Choose payment method for refund (1 for Credit Card, 2 for Cash): ";
                int refundChoice;
                cin >> refundChoice;

                PaymentMethod* paymentMethod;
                if (refundChoice == 1) {
                    string cardNumber;
                    cout << "Enter credit card number: ";
                    cin >> cardNumber;
                    paymentMethod = new CreditCard(cardNumber);
                } else if (refundChoice == 2) {
                    paymentMethod = new Cash();
                } else {
                    cerr << "Invalid choice. Exiting." << endl;
                    return 1;
                }

                int refundAmount;
                cout << "Enter refund amount: $";
                cin >> refundAmount;

                customer.refundPayment(paymentMethod, refundAmount);
                delete paymentMethod;
                break;
            }
            case 5: {
                cout << "Enter customer name: ";
                string customerName;
                cin.ignore();
                getline(cin, customerName);

                Customer customer(customerName);
                customer.displayProfitAndLoss();
                break;
            }
            case 0:
                cout << "Exiting the program." << endl;
                break;
            default:
                cerr << "Invalid choice. Try again." << endl;
        }
        
    } while (choice != 0);
    
    cout<<endl<<" ******************************************************************************************************************* "<<endl;

    return 0;
}


