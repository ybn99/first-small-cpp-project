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
        std::string getAge;
        double balance = 0.0;
        int depositAmount = 0;             
        int withdrawAmount = 0;
        int result = 0;

    public:

    Customer() : fullName(""), email(""), password(""), balance(0.0), 
                depositAmount(0), withdrawAmount(0), result(0), getAge("") {}

    void createAccount(bool& isAccountCreated) {
        
        std::cout << "\nAre you an adult? (Yes or No): ";
        std::cin >> getAge;
        if (getAge != "Yes" && getAge != "yes") {
            std::cout << "\nYou are not old enough to procceed. Please try again.";
            return;
        } else {
            std::cout << "\n=== CREATING NEW ACCOUNT ===\n";
            std::cout << "\nFull Name: ";
            std::cin.ignore();
            std::getline(std::cin, fullName);
            std::cout << "Email: ";
            std::cin >> email;
            std::cout << "Set a Password: ";
            std::cin >> password;
            isAccountCreated = true;
        }
        
    }

    void viewAccount(bool& isAccountCreated) {      
        if (!isAccountCreated) {
            notCreatedAccount();
        } else {
            std::cout << "\n=== YOUR ACCOUNT ===";
            std::cout << "\n1. Your FULL NAME: " << Customer::fullName;
            std::cout << "\n2. Your EMAIL: " << Customer::email;
            std::cout << "\n3. Your BALANCE: $" << Customer::balance;
        }
    }

    void viewDepositHistory() const{
        if (depositHistory.empty()) {
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

    void viewWithdrawHistory() const{        
        if (withdrawHistory.empty()) {
            std::cout << "\nNo withdraws have been made.";
        } else {
            std::cout << '\n';
            for (int withdrawTimes : withdrawHistory) {
            std::cout << "Withdrawn: $" << withdrawTimes << '\n';
            }
        }
    }
    // Withdraws funds from balance.
    void withdrawFromBalance(){         
        if (withdrawAmount > balance) {
            std::cout << "\nWithdraw is bigger than the balance, no changes made.";
            withdrawAmount = 0;
        } else {
            (result = (balance -= withdrawAmount));
            withdrawHistory.push_back(withdrawAmount);
            std::cout << "New balance: $" << result;
        }
    }   
    // Checks if the user has created an account and can access the withdraw history function.
    void checkAccessWithdrawHistory(bool& isAccountCreated){        
        if (!isAccountCreated){
            notCreatedAccount();
        } else {
            viewWithdrawHistory();
        }
    }
    // Checks if the user has created an account and can access the deposit function.
    void checkAccessDepositHistory(bool& isAccountCreated){         
        if (!isAccountCreated) {
            notCreatedAccount();
        } else {
            viewDepositHistory();
        }
    }
    // Used oftenly for when the customer has not made an account.
    void notCreatedAccount() {      
        std::cout << "\nYou have not created an account.";
    }
};

// This function simply shows the menu of actions that the user can make
void showMenu() {       
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

// This function basically handles the user's input and executes accordingly.
void handleMenu(int customerChoice, Customer& customer1, bool& isAccountCreated) {    
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
    Customer customer1;

    do {
        // Calls the showMenu function
        showMenu();        
        // The user's input is stored inside of this variable and then
        std::cin >> customerChoice;    
        // the user is redirected inside the handleMenu function
        handleMenu(customerChoice, customer1, isAccountCreated);     
    } while (customerChoice != 0);      

    return 0;
}

