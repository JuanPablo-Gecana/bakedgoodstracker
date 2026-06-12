#include <iostream>
#include <iomanip> //Might use para sa generation ng recipt ng customer or baka sa design ng program itself
#include <string>
#include <vector>
#include <fstream> //pang save ng inventory sa file
using namespace std;

struct bakedProcuct {
    string name;
    double price;
    int quantity;
};

vector <bakedProcuct> menu; //pang lagay ng mga items na ibebenta

//Dito lahat ilalagay ung mga products na ibebenta and ung mga relevant info nila
void addProduct() {
    bakedProcuct newProduct;
    cout << "Enter the name of the product: ";
    cin >> newProduct.name;
    cout << "Enter the price of the product: ";
    cin >> newProduct.price;
    cout << "Enter the quantity of the product: ";
    cin >> newProduct.quantity;
    menu.push_back(newProduct);
    cout << "Product added successfully!" << endl;
}

//Ipapakita lahat nung nilagay na products doon sa addProduct function
void displayMenu() {
    cout << "Menu:" << endl;
    for (int i = 0; i < menu.size(); ++i) {
        cout << i + 1 << ". " << menu[i].name << " - ₱" << fixed << setprecision(2) 
        << menu[i].price << " (Quantity: " << menu[i].quantity << ")" << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "========PANADEYA NI HUWAN PABLO========" << endl
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
