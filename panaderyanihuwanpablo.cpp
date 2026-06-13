#include <iostream>
#include <iomanip> //Might use para sa generation ng recipt ng customer or baka sa design ng program itself
#include <string> //Personally di ko pa nakikita relevancy neto pero itetest ko pa
#include <vector> //Needed to para makapagstore ng as many products as we can without limitations
#include <fstream> //pang save ng inventory sa file and possibly ng transaction history ng bawat customers
using namespace std;

//Structure para malagay natin ung mga products and info nila sa vector as one 
struct bakedProcuct {
    string name;
    double price;
    int quantity;
};

vector <bakedProcuct> menu; //pang lagay ng mga items na ibebenta and ididisplay later sa display function

//Dito lahat ilalagay ung mga products na ibebenta and ung mga relevant info nila
void addProduct() {
    bakedProcuct newProduct;
    cin.ignore();
    cout << "\nEnter the name of the product: ";
    getline(cin, newProduct.name);
    cout << "Enter the price of the product: ";
    cin >> newProduct.price;
    cout << "Enter the quantity of the product: ";
    cin >> newProduct.quantity;
    /* Once tapos na malagyan ung product and ung info nila, ipupush back na dun sa vector and magiging item na sya ng tracker natin
    and pwede na sya makita and maorder ng magiging customer*/
    menu.push_back(newProduct);
    cout << "\nProduct added successfully!\n" << endl;
}

//Ipapakita lahat nung nilagay na products doon sa addProduct function
void displayMenu() {
    cout << "\nMenu:" << endl;
    for (int i = 0; i < menu.size(); ++i) {
        cout << i + 1 << ". " << menu[i].name << " - P" << fixed << setprecision(2) 
        << menu[i].price << " (Quantity: " << menu[i].quantity << ")" << endl;
    }
    cout<<endl;
}

int main() {
    int choice;
    //Do-while para paulit ulit and para wala nang initialization ng value ung choice variable
    do {
        cout << "========PANADEYA NI HUWAN PABLO========" << endl //Papaltan yang "PANADERYA NI HUWAN PABLO" kase di pwede yan HAHAHA
             << "1. Add Product" << endl
             << "2. Display All Products" << endl
             << "3. Exit" << endl
             << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayMenu();
                break;
            case 3:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
    return 0;
}
