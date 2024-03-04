// File: AutoLoan.cpp
// Dev: Drake Walsh
// Org: FGCU COP 3003 202308 80602
// Desc: Main application file for an Auto Loan calculator
//---------------------------------------------------------
#include <cmath>
#include <iostream>
#include <iomanip>

// Constants
//---------------------------------------------------------
const float TAX = .065;
const float TITLE_FEE = 75.25;
const float TRANSFER_FEE = 7.85;
const float REGISTRATION_FEE = 14.50;

//Structs
//---------------------------------------------------------
struct BillOfSale{              //represents the cost of the car with sales tax and fees.
    float vehiclePrice;
    float discount;
    float taxAmount;
    float fees;
    float unpaidTotal;
};

struct Loan {                   //represents financing if there are payments made to dealer
    float principle;
    float APR;
    int months;
    float payment;
    float interest;
    float totalPayments;
};

struct Contract {              //Organized Struct of both Loan and BillOfSale
    BillOfSale sale;
    char financed;
    Loan loan;
};

//Functions Declarations
//---------------------------------------------------------
BillOfSale getBillOfSale();
Loan getLoan(float loanAmount);
float calculatePayment(float principle, float rate, int months);
int calculateMonths(float principle, float rate, float payment);
void printContract(Contract);




int main() {

    char again;                                                            //Condition for do-while loop

    do {
        Contract customerContract{0};
        customerContract.sale = getBillOfSale();

        std::cout << "Do they need finance? (Y/N)";
        std::cin >> customerContract.financed;                             //If not needed, BillOfSale will only print

        if (customerContract.financed == 'y' || customerContract.financed == 'Y'){
            customerContract.loan = getLoan(customerContract.sale.unpaidTotal);

        }

        printContract(customerContract);


    } while (again == 'y' || again == 'Y');

    return 0;
}




//Function Definitions
//---------------------------------------------------------
BillOfSale getBillOfSale(){
    BillOfSale sale {0};
    std::cout << "Sales Price  : ";
    std::cin >> sale.vehiclePrice;
    std::cout << "Discount     : ";
    std::cin >> sale.discount;
    sale.taxAmount = (sale.vehiclePrice - sale.discount) * TAX;                       //Calculating tax amount
    sale.fees = TITLE_FEE + TRANSFER_FEE + REGISTRATION_FEE;                          //Calculating total fees
    sale.unpaidTotal = sale.vehiclePrice - sale.discount + sale.taxAmount + sale.fees;//Calculating Loan amount
  return sale;
}


Loan getLoan(float loanAmount){
    Loan customerLoan {0};
    customerLoan.principle = loanAmount;
    std::cout << "APR: ";
    std::cin >>customerLoan.APR;
    std::cout << "Enter 1)Months 2)Payment";
    int monthsOrPayment;
    std::cin >> monthsOrPayment;

    if (monthsOrPayment == 1) {                           //Selection for if they prefer to have set number of months
        std::cout << "Amount of months:";
        std::cin >> customerLoan.months;
        customerLoan.payment = calculatePayment(customerLoan.principle, float (customerLoan.APR/1200.0) , customerLoan.months);
        customerLoan.totalPayments = float(customerLoan.months) * customerLoan.payment;
        customerLoan.interest = customerLoan.totalPayments - customerLoan.principle;
    } else {                                             //Selection for if they prefer to have set number for a payment
        std::cout << "Payment amount:";
        std::cin >> customerLoan.payment;
        customerLoan.months = calculateMonths(customerLoan.principle, float(customerLoan.APR/1200.0), customerLoan.payment);
        customerLoan.totalPayments = float(customerLoan.months) * customerLoan.payment;
        customerLoan.interest = customerLoan.totalPayments - customerLoan.principle;
    }
    return customerLoan;
}


float calculatePayment(float principle, float rate, int months){        //Calculates payment if given months
    float payment = ((rate * principle)/(1.0-(std::pow((1.0 + rate), -months))));
    return payment;
}

int calculateMonths(float principle, float rate, float payment){        //Calculates months if given payment
    int months = std::log (payment/(payment-(rate * principle)))/(std::log (rate + 1.0));
    return months;
}

void printContract(Contract bill){                                      //Prints Bill Of Sale
    std::cout << std::endl << std::fixed << std::setprecision(2);
    std::cout << "Sales Price          :" << std::setw(12);
    std::cout << bill.sale.vehiclePrice << std::endl;
    std::cout << "Discount             :" << std::setw(12);
    std::cout << bill.sale.discount << std::endl;
    std::cout << "Tax                  :" << std::setw(12);
    std::cout << bill.sale.taxAmount << std::endl;
    std::cout << "Fees                 :" << std::setw(12);
    std::cout << bill.sale.fees << std::endl;
    std::cout << std::setw(34);
    std::cout << "------------" << std::endl;
    std::cout << "Unpaid Balance       :" << std::setw(12);
    std::cout << bill.sale.unpaidTotal << std::endl << std::endl;

                                                                      //Prints Loan Information if needed
    if (bill.financed == 'y' || bill.financed == 'Y'){
        std::cout <<"Months               :" << std::setw(12);
        std::cout << bill.loan.months << std::endl;
        std::cout <<"Payment              :" << std::setw(12);
        std::cout << bill.loan.payment << std::endl;
        std::cout <<"APR                  :" << std::setw(11);     //Has 11 to include % symbol
        std::cout << bill.loan.APR << '%' << std::endl;
        std::cout <<"Total of Payments    :" << std::setw(12);
        std::cout << bill.loan.totalPayments << std::endl;
        std::cout <<"Interest Paid        :" << std::setw(12);
        std::cout << bill.loan.interest << std::endl << std::endl;


    }
}