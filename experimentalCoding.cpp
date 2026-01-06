#include <iostream>
#include <string>
#include <vector>

class Customer {
    private:
        std::vector<double> depositHistory;
        std::vector<double> withdrawHistory;  
        std::string fullName;
        std::string email;
        std::string password;
        std::string isAdult;
        double balance = 0.0;
        double depositAmount = 0.0;             
        double withdrawAmount = 0.0;
        double result = 0.0;

    // Accounts Section
    public:
    Customer() : fullName(""), email(""), password(""), balance(0.0), 
                depositAmount(0), withdrawAmount(0), result(0), isAdult("") {}

    void createAccount(bool& isAccountCreated) {
        
        std::cout << "\nAre you an adult? (Yes or No): ";
        std::cin >> isAdult;
        if (isAdult != "Yes" && isAdult != "yes") {
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

    void removeAccount(){
        std::cout << "This is a message";
        fullName = "";
        email =  "";
        password = "";
        isAdult = "";
        balance = 0.0;
        withdrawAmount = 0.0;
        depositAmount = 0.0;
    }

    void accountRemovalChoice(){
        std::string wantToDelete;
    
        std::cout << "\nWant to remove your account?: ";
        std::cin >> wantToDelete;
        if (wantToDelete == "Yes" || wantToDelete == "yes"){
            std::cout << "\nYour account is being deleted...";
            removeAccount();
        } else if (wantToDelete == "No" || wantToDelete == "no"){
            std::cout << "\nYour account has not been deleted. Returning to main menu...";
        } else {
        std::cout << "\nInvalid input, try again.";
        }
    }

    void notCreatedAccount() {      
        std::cout << "\nYou have not created an account.";
    }

    // Deposit Section
    public:
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

    void customerDeposit(bool& isAccountCreated) {
        if (!isAccountCreated) {
            notCreatedAccount();
        } else {
        std::cout << "\nHow much would you like to deposit?: $";
        std::cin >> depositAmount;
        std::cout << "\nNew balance: $" << (balance += depositAmount);
        depositHistory.push_back(depositAmount);
        }
}
    // Withdraw Section
    public:
    // checks balance once called (balance ≠ 0 in order to withdraw) and then redirects to withdraw function
    void getCustomerWithdrawAmount() {
        if (!balance) {
            std::cout << "\nPlease deposit first.";
        } else {
        std::cout << "\nHow much would you like to withdraw?: $";
        customerWithdraw();
    }
}

    void viewWithdrawHistory() const{        
        if (withdrawHistory.empty()) {
            std::cout << "\nNo withdraws have been made.";
        } else {
            std::cout << '\n';
            for (int withdrawTimes : withdrawHistory) {
            std::cout << "Money Withdrawn: $" << withdrawTimes << '\n';
            }
        }
    }

    void customerWithdraw(){     
        std::cin >> withdrawAmount;
        if (withdrawAmount > balance) {
            std::cout << "\nInvalid amount, your balance remains at: $" << balance;
        } else {
            (result = (balance -= withdrawAmount));
            withdrawHistory.push_back(withdrawAmount);
            std::cout << "New balance: $" << result;  
        }
    }
};

// the menu where the user types a number according to the action they want to take place
void showMenu() {       
    std::cout << "\n\n=== MAIN MENU ===\n";
    std::cout << "1. Create Account.\n";
    std::cout << "2. View Account.\n";
    std::cout << "3. Deposit.\n";
    std::cout << "4. View Deposit History.\n";
    std::cout << "5. Withdraw.\n";
    std::cout << "6. View Withdraw History.\n";
    std::cout << "7. Delete Account.\n";
    std::cout << "0. Exit.\n";
    std::cout << "Choice: ";
};

// handles the customer's input and executes according action
void handleMenu(int customerChoice, Customer& customer1, bool& isAccountCreated) {    
    switch (customerChoice) {
        case 1:
            customer1.createAccount(isAccountCreated);
            break;
        case 2:
            customer1.viewAccount(isAccountCreated);
            break;
        case 3:
            customer1.customerDeposit(isAccountCreated);
            break;
        case 4: if (!isAccountCreated) {
            customer1.notCreatedAccount();
            } else {
                customer1.viewDepositHistory();
            }
            break;
        case 5: if (!isAccountCreated) {
            customer1.notCreatedAccount();
            }
            else {
                customer1.getCustomerWithdrawAmount();
            }
            break;
        case 6: if (!isAccountCreated) {
            customer1.notCreatedAccount();
            } else {
                customer1.viewWithdrawHistory();
            }
            break;
        case 7: if (!isAccountCreated) {
            std::cout << "\nNo account exists to delete.";
        } else {
            customer1.accountRemovalChoice();
        }
            break;
        case 0: std::exit(0);
    };
};

int main() {
    int customerChoice = 0;
    bool isAccountCreated = false;
    Customer customer1;

    do {
        showMenu();        
        std::cin >> customerChoice;    
        // the user is redirected inside the handleMenu function
        handleMenu(customerChoice, customer1, isAccountCreated);     
    } while (customerChoice != 0);      

    return 0;
}

