#include <iostream>
#include <string>
#include <vector>

class Customer {
    private:
        std::vector<int> depositHistory;
        std::vector<int> withdrawHistory;
        std::string fullName;
        std::string email;
        std::string password;
        int balance = 0.0;
        int depositAmount = 0;             
        int age = 0;
        int withdrawAmount = 0;
        int result = 0;

    public:

    Customer(std::string& fn, int a, std::string ml, std::string& pass) : fullName(fn), age(a), password(pass), email(ml) {}

    void createAccount(bool& isAccountCreated) {
        std::cout << "\n=== CREATING NEW ACCOUNT ===\n";
        std::cout << "\nYour FULL NAME: ";
        std::cin.ignore();
        std::getline(std::cin, fullName);
        do{
        std::cout << "Your AGE (only 18+): ";
        std::cin >> age;
        }while (age < 18);
        std::cout << "Your E-MAIL: ";
        std::cin >> email;
        std::cout << "Your NEW PASSWORD: ";
        std::cin >> password;
        isAccountCreated = true;
    }

    void viewAccount(bool& isAccountCreated) {      
        if (!isAccountCreated) {
            notCreatedAccount();
        } else {
            std::cout << "\n=== YOUR ACCOUNT ===";
            std::cout << "\n1. Your FULL NAME: " << Customer::fullName;
            std::cout << "\n2. Your E-MAIL: " << Customer::email;
            std::cout << "\n3. Your BALANCE: $" << Customer::balance;
        }
    }

    void viewDepositHistory() {
        if (depositAmount <= 0) {
            std::cout << "\nNo deposits have been made.";
        } else {
        std::cout << '\n';
        for (int depositTimes : depositHistory) {
            std::cout << "Deposited: $" << depositTimes << '\n';
            }
        }
    }

    void getDepositAmount(bool& isAccountCreated) {
        if (!isAccountCreated) {
            notCreatedAccount();
        } else {
        std::cout << "\nHow much would you like to deposit?: $";
        std::cin >> depositAmount;
        std::cout << "\nNew balance: $" << (balance += depositAmount);
        depositHistory.push_back(depositAmount);
        }
    }

    

    void getWithdrawAmountFunc(bool& isAccountCreated) {        
        if (!isAccountCreated) {
            notCreatedAccount();
        } else if (isAccountCreated && balance > 10){
            std::cout << "\nHow much would you like to withdraw?: $";
            std::cin >> withdrawAmount;
            withdrawFromBalance();
        } else {
            std::cout << "\nUnable to withdraw. Balance is too low (min. $10+).";
        } 
}

    void viewWithdrawHistory() {        // 
        if (withdrawHistory.empty()) {
            std::cout << "\nNo withdraws have been made.";
        } else {
            std::cout << '\n';
            for (int withdrawTimes : withdrawHistory) {
            std::cout << "Withdrawn: $" << withdrawTimes << '\n';
            }
        }
    }

    void withdrawFromBalance(){         // Withdraws funds from balance.
        if (withdrawAmount > balance) {
            std::cout << "\nWithdraw is bigger than the balance, no changes made.";
            withdrawAmount = 0;
        } else {
            (result = (balance -= withdrawAmount));
            withdrawHistory.push_back(withdrawAmount);
            std::cout << "New balance: $" << result;
        }
    }   

    void checkAccessWithdrawHistory(bool& isAccountCreated){        // Checks if the user has created an account and can access the withdraw history function.
        if (!isAccountCreated){
            notCreatedAccount();
        } else {
            viewWithdrawHistory();
        }
    }

    void checkAccessDepositHistory(bool& isAccountCreated){         // Checks if the user has created an account and can access the deposit function.
        if (!isAccountCreated) {
            notCreatedAccount();
        } else {
            viewDepositHistory();
        }
    }

    void notCreatedAccount() {      // Used oftenly for when the customer has not made an account.
        std::cout << "\nYou have not created an account.";
    }
};

void showMenu() {       // This function simply shows the menu of actions that the user can make
    std::cout << "\n\n=== MAIN MENU ===\n";
    std::cout << "1. Create Account.\n";
    std::cout << "2. View Account.\n";
    std::cout << "3. Deposit.\n";
    std::cout << "4. View Deposit History.\n";
    std::cout << "5. Withdraw.\n";
    std::cout << "6. View Withdraw History.\n";
    std::cout << "0. Exit.\n";
    std::cout << "Choice: ";
};

void handleMenu(int customerChoice, Customer& customer1, bool& isAccountCreated) {     // This function basically handles the user's input and executes accordingly.
    switch (customerChoice) {
        case 1:
            customer1.createAccount(isAccountCreated);
            break;
        case 2:
            customer1.viewAccount(isAccountCreated);
            break;
        case 3:
            customer1.getDepositAmount(isAccountCreated);
            break;
        case 4: customer1.checkAccessDepositHistory(isAccountCreated);
            break;
        case 5: customer1.getWithdrawAmountFunc(isAccountCreated);
            break;
        case 6: customer1.checkAccessWithdrawHistory(isAccountCreated);
            break;
        case 0: std::exit(0);
    };
};

int main() {
    int customerChoice = 0;
    bool isAccountCreated = false;
    std::string empty = "";
    Customer customer1(empty, 0, empty, empty);

    do {
        showMenu();        // Calls the showMenu function
        std::cin >> customerChoice;     // The user's input is stored inside of this variable and then
        handleMenu(customerChoice, customer1, isAccountCreated);     // the user is redirected inside the handleMenu function
    } while (customerChoice != 0);      // All of the above happen unless this variable takes the 0 value

    return 0;
}

