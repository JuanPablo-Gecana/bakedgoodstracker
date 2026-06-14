#include <iostream>
#include <iomanip> //Might use para sa generation ng recipt ng customer or baka sa design ng program itself
#include <string> //Personally di ko pa nakikita relevancy neto pero itetest ko pa
#include <vector> //Needed to para makapagstore ng as many products as we can without limitations
#include <fstream> //pang save ng inventory sa file and possibly ng transaction history ng bawat customers
using namespace std;

//Structure para malagay natin ung mga products and info nila sa vector as one 
struct bakedProduct {
    string name;
    double price;
    int quantity;
};

vector <bakedProduct> menu; //pang lagay ng mga items na ibebenta and ididisplay later sa display function
bakedProduct newProduct;
bakedProduct existProduct;

//itong blocks of code kasama ung displayMenu function ang reason na matatandaan lahat ng program ung ininput natin na Products
//Dito lahat ilalagay ung mga products na ibebenta and ung mga relevant info nila
void addProduct() {  
    cin.ignore();
    cout << "\nEnter the name of the product: ";
    getline(cin, newProduct.name);
    cout << "Enter the price of the product: ";
    cin >> newProduct.price;
    cout << "Enter the quantity of the product: ";
    cin >> newProduct.quantity;

    //After malagay lahat ng relevant info, ilalagay na nya muna sa file
    ofstream file("Menu.txt", ios::app);
    if (file.is_open()){
        file << newProduct.name << "  "
             << newProduct.price << "  "
             << newProduct.quantity << endl;
        file.close();
    }

    cout << "\nProduct added successfully!\n" << endl;
}

//Ipapakita lahat nung nilagay na products doon sa addProduct function 
void displayMenu() {
    menu.clear(); //Icleclear na to kase ung laman neto is nailagay naman sa file so redundant na
    ifstream file("Menu.txt"); //Babasahin na nya ung file
    if (file.is_open()){
        //Hahanapin na nya sa file ung needed na info based sa data type 
        while(file >> existProduct.name >> existProduct.price >> existProduct.quantity){ //Might change this kase di sya nagaacomodate ng may spaces (eg. Pan de Coco)
            menu.push_back(existProduct); //And ipupush na nya sa menu vector na kakaclear lang kanina
        }
        file.close();//and then isasara ung file

        //ung na pushback ni menu vector is ilalabas na dito
        cout << "\nMenu:" << endl;
        for (int i = 0; i < menu.size(); ++i) {
            cout << i + 1 << ". " << menu[i].name << " - P" 
                 << fixed << setprecision(2) << menu[i].price 
                 << " (Quantity: " << menu[i].quantity << ")" << endl;
        }
    } else {
        cout << "Unable to open Menu.txt" << endl;
    }
    cout << endl;
}

// Dito yung part kung san magdedelete ka ng products. Looking for way para di sya case sensitive (pakicheck na lang if nagana LMAO)
void deleteProduct(){ 
    string name;
    cout << "Enter product to delete: ";
    cin >> name;
    cin.ignore();
    
    for (int i = 0; i < menu.size(); ++i){
        if (menu[i].name == name){
            menu.erase(menu.begin() + i);
            cout << "The product named '" << name << "' is deleted. Thank you." << endl;
            cout << endl;
            return;
        }
        else {
            cout << "Product Not Found." << endl;
            cout << endl;
            return;
        }
    }
}

int main() {
    int choice;
    //Do-while para paulit ulit and para wala nang initialization ng value ung choice variable
    do {
        cout << "========PANADERYA NI HUWAN PABLO========" << endl //Papaltan yang "PANADERYA NI HUWAN PABLO" kase di pwede yan HAHAHA
             << "1. Add Product" << endl
             << "2. Display All Products" << endl
             << "3. Delete Product" << endl
             << "4. Exit" << endl
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
                deleteProduct();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
    return 0;
}
