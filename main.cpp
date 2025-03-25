#include <iostream>
#include <memory>
#include <stdexcept>
#include <exception>
#include <string>

using namespace std;

// TODO: Define custom exception classes here
// - NegativeDepositException (for negative deposit attempts)
// - OverdrawException (for withdrawing more than the balance)
// - InvalidAccountOperationException (for transactions on a closed account)

class CustomException : public exception
{

private:
    string message;

public:
    CustomException(const string& msg) : message(msg) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

//NegativeDepositException class
class NegativeDepositException : public CustomException
{

public:
    NegativeDepositException(double amount) : CustomException("Cannot deposit a negative amount " + to_string(amount)) {}

};


//OverdrawException class
class OverdrawException : public CustomException
{

public:
    OverdrawException() : CustomException("Cannot withdraw over the balance amount") {}

};

//InvalidAccountOperationException class
class InvalidAccountOperationException : public CustomException
{

public:
    InvalidAccountOperationException() : CustomException("Account is closed.") {}
};



class BankAccount {
private:
    string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        // TODO: Implement exception handling for negative deposits
        if (isActive == false)
        {
            throw InvalidAccountOperationException();
        }
        else if (amount < 0)
        {
            throw NegativeDepositException(amount);
        }
        else
        {
            balance += amount;
        }
    }

    // Withdraw method
    void withdraw(double amount) {
        // TODO: Implement exception handling for overdrawing and closed accounts
        if (isActive == false)
        {
            throw InvalidAccountOperationException();
        }
        else if (amount > balance)
        {
            throw OverdrawException();
        }
        else
        {
            balance -= amount;
        }

    }

    // Method to get current balance
    double getBalance() const
    {
        if (isActive == false)
        {
            throw InvalidAccountOperationException();
        }

        return balance;
    }

    // Method to close the account
    void closeAccount() {
        // TODO: Prevent further transactions when the account is closed
        isActive = false;
        cout << "\n[Bank] Account is closed successfully.\n" << endl;
    }
};

//display menu function
void bankMenu()
{
    cout << "\n[Bank System]\n";
    cout << "1. Deposit Money\n";
    cout << "2. Withdraw Money\n";
    cout << "3. Check Balance\n";
    cout << "4. Close Account\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

int main()
{

    //temp variables
    string name;
    double initialBalance = 0;
    double input = 0;
    int choice = 0;

    BankAccount test(name, initialBalance);

    //creates initial account
    cout << "Create an account with us, please enter initial balance: ";
    cin >> initialBalance;
    auto account = make_unique<BankAccount>("123456", initialBalance);
    cout << "Bank Account Created: #" << "123456" << endl;


    while (true)
    {

        try {

            bankMenu(); //starting menu 

            cin >> choice;

            switch (choice)
            {
            case 1: // deposit money 
                cout << "\nDepositing: $";
                cin >> input;
                account->deposit(input);
                cout << "\n[Bank] Depositing: $" << input << "..." << endl;
                break;
            case 2: // withdraw money 
                cout << "\nWithdrawing: $";
                cin >> input;
                account->withdraw(input);
                cout << "\n[Bank] Withdrawing: $" << input << "..." << endl;
                break;
            case 3: // check balance
                cout << "\n[Bank] Current Balance: $" << account->getBalance() << endl;
                break;
            case 4: // closes account
                account->closeAccount();
                break;
            case 5: // exit program
                cout << "\nGood bye!\n";
                return 0;
            default:
                cout << "\n Try again buddy!\n";
            }
            // catches each type of error
        }
        catch (const NegativeDepositException& e)
        {
            cerr << "\n[Bank] Error: " << e.what() << endl;
        }
        catch (const OverdrawException& e)
        {
            cerr << "\n[Bank] Error: " << e.what() << endl;
        }
        catch (const InvalidAccountOperationException& e)
        {
            cerr << "\n[Bank] Error: " << e.what() << endl;
        }
    }
    return 0;


}