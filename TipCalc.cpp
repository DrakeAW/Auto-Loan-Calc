// Title: Tip Calculator
//  Name: Drake Walsh
// Class: COP 3530
//  Desc: A program to prompt and calculate a user for tips
//---------------------------------------------------------
#include <iostream>
#include <iomanip>

//Structs
//---------------------------------------------------------
struct billOfSale {      //Represents a bill of sale for our purchase
    float subTotal;
    float total;
    int decision;
    float tipPercent;
    float tipAmount;
};

// Function Declarations
//---------------------------------------------------------
void printContract (billOfSale);


int main() {
    char again;

    do {
        billOfSale customerContract = billOfSale{0};

        std::cout << "Please enter total:" << std::endl;            //Prompt the User for the total
        std::cin >> customerContract.subTotal;
        std::cout << "Enter (1) for tip percent, or (2) for tip amount:" << std::endl;
        std::cin >> customerContract.decision;                                       // a tip percent or a tip amount


        if (customerContract.decision == 1) {                                         // If user chooses tip percentage
            std::cout << "Enter tip percentage" << std::endl;
            std::cin >> customerContract.tipPercent;
            float tipPercentage;


            tipPercentage = (customerContract.tipPercent) / 100.f;               // Calculate tip percentage as a float
            customerContract.tipAmount = customerContract.subTotal * tipPercentage;

            customerContract.total = customerContract.tipAmount + customerContract.subTotal;
            printContract(customerContract);


        } else {                                                                // If user chooses tip amount
            std::cout << "Enter tip amount" << std::endl;
            std::cin >> customerContract.tipAmount;                             //Enter and calculate tip amount/percent
            customerContract.tipPercent = (customerContract.tipAmount / customerContract.subTotal) * 100;


            customerContract.total = customerContract.tipAmount + customerContract.subTotal;
            printContract(customerContract);
        }


        std::cout << "Enter another Y/N?" << std::endl;
        std::cin >> again;                                                  // Determines if we will rerun program
    } while (again == 'y' || again == 'Y');

    return 0;
}

//Function definitions
//---------------------------------------------------------
void printContract (billOfSale customerContract){               // Contract printing
    std::cout << std::endl << std::fixed << std::setprecision(2);
    std::cout << "Receipt             :" <<std::setw(12) <<std::endl;
    std::cout << "Subtotal            :" <<std::setw(12);
    std::cout << "$"<< customerContract.subTotal << std::endl;
    std::cout << "Tip (" <<customerContract.tipPercent<< "%)        :"
    << std::setw(12) << "$" << customerContract.tipAmount<<std::endl<<std::setw(12);
    std::cout << std::setw(39) << "------------" << std::endl << std::setw(12);
    std::cout << "Total               :" << std::setw(12);
    std::cout << "$" << customerContract.total << std::endl << std::endl;
}