#include <iostream>
#include <iomanip> //Might use para sa generation ng recipt ng customer or baka sa design ng program itself
#include <string> //Personally di ko pa nakikita relevancy neto pero itetest ko pa
#include <vector> //Needed to para makapagstore ng as many products as we can without limitations
#include <fstream> //pang save ng inventory sa file and possibly ng transaction history ng bawat customers
#include <algorithm> //way para maging case insensitive ung mga icocompare na input later
using namespace std;

//==================================[Structures]===================================== 

//Structure para malagay natin ung mga products and info nila sa vector as one 
struct bakedProduct {
    string name;
    double price;
    int quantity;
};

//struct para sa mga inputs natin sa main with a secret passcode syempre
struct choiceInputs {
    string code;
    int numCode;
};

//login credentials para sa admin
struct loginCredentials {
    string username;
    string password;
    string customerName;
};

//=========================[Important Struct Variables]==============================

vector <bakedProduct> menu; //pang lagay ng mga items na ibebenta and ididisplay later sa display function
bakedProduct existProduct; //useful sa pagloload sa vector galing sa txt file
vector <loginCredentials> logInfo; //pang store ng login credentials ng mga admin
loginCredentials logCred; //pangload sa vector para may ma compare later

//===============================[Helper Functions]================================== 

void loadExistingProducts(); //if deretso na agad sa search, update, etc. eto muna magrurun
string toLower(string s); // Reason na magiging case-insensitive ung program.
void loadAdmin(); //pangload ng admin info sa file

//================================[Core Functions]=================================== 

/*itong addProduct kasama ung displayMenu function ang reason na matatandaan lahat ng program ung 
ininput natin na Products*/
void orderProduct();
void addProduct(); // Mag aadd ng product dun sa program and sa file.
void displayMenu(); //Ipapakita lahat nung nilagay na products doon sa addProduct function.
void deleteProduct(); // Dito yung part kung san magdedelete ka ng products. 
void updateProduct(); //dito mag uupdate ng ating mga current products
void searchProduct(); //dito naman pag gusto ng user na mag search ng specific product

//==============================[Features Functions]=================================

void changeLogInfo();
void addAdmin();
void removeAdmin();

//================================[Main Function]==================================== 

int main() {
    choiceInputs choice;
    //Do-while para paulit ulit and para wala nang initialization ng value ung choice variable
    do {
        cout << "========PANADERYA NI HUWAN PABLO========" << endl //Papaltan yang "PANADERYA NI HUWAN PABLO" kase di pwede yan HAHAHA
             << "1. Order a Product" << endl
             << "2. Search for a Product" << endl
             << "3. Display All Products" << endl
             << "4. Exit" << endl
             << "Enter your choice: ";
        cin >> choice.code; //string muna here since mag eeror sya pag int tas "ADMIN" nilagay ko

        //Prolly di na hahaba ung 4 conditions since ayan lang naman ung walang editing na mangyayari sa pov ng customer
        if (choice.code == "1" || choice.code == "2" || choice.code == "3" || choice.code == "4") {
            choice.numCode = stoi(choice.code); //stoi para maging int sya pag nag switch na
            switch (choice.numCode) {
                case 1:
                    orderProduct();
                    break;
                case 2:
                    searchProduct();
                    break;
                case 3:
                    displayMenu();
                    break;
                case 4:
                    cout << "\nThank you and Please come again!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } else if (choice.code == "ADMIN") { //What if ADMIN na, eto mangyayari
            loginCredentials login;
            cout << "\nUsername: ";//Needed nya na mag input ng username and password
            cin >> login.username;
            cout << "Password: ";
            cin >> login.password;

            loadAdmin();

            //If magmatch... welcome sa bagong ui natin for admin, dito nakalagay ung mga revision sa menu ng products natin
            for (int i=0; i < logInfo.size() ; ++i) {
                if (logInfo[i].username == login.username && logInfo[i].password == login.password) {
                    do{
                        cout << "========Welcome Admin "<< logInfo[i].username << "!========" << endl
                        << "1. Add a Product" << endl
                        << "2. Delete a Product" << endl
                        << "3. Update a Product" << endl
                        << "4. Change Username/Password" << endl
                        << "5. Add an Admin" << endl
                        << "6. Remove an Admin" << endl
                        << "7. Back" << endl
                        << "Enter your choice: ";
                        cin >> choice.numCode;

                        switch (choice.numCode) {
                            case 1:
                                addProduct();
                                break;
                            case 2:
                                deleteProduct();
                                break;
                            case 3:
                                updateProduct();
                                break;
                            case 4:
                                changeLogInfo();
                                break;
                            case 5:
                                break;
                            case 6:
                                break;
                            case 7:
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                    } while (choice.numCode !=7);
                } else {
                    cout << "\nUsername and Password don't match.\n" << endl;
            
                }
            }
        } else {
            cout << "\nInvalid choice. Please try again.\n" << endl;
        }
    } while (choice.numCode != 4);
    return 0;
}

void loadExistingProducts(){
     if (menu.empty()) {
            ifstream file("Menu.txt"); 
                if (file.is_open()){
                    while(file >> existProduct.name >> existProduct.price >> existProduct.quantity){ 
                    menu.push_back(existProduct); 
                }
                file.close();
            }
        }
}

void loadAdmin(){
     if (logInfo.empty()) {
            ifstream file("Admin.txt"); 
                if (file.is_open()){
                    while(file >> logCred.username >> logCred.password){ 
                    logInfo.push_back(logCred); 
                }
                file.close();
            }
        }
}

string toLower(string s) {
    //transform(startPOS, endPOS, startPOSngoutput, ung gagawin)
    transform(s.begin(), s.end(), s.begin(), ::tolower); 
    return s;
}

void orderProduct() {
    loadExistingProducts();

    if (menu.empty()) {
        cout << "\nSorry, the menu is currently empty. No items to order.\n" << endl;
    } else {
        string orderName;
        int orderQty;
        bool productFound = false;

        cout << "\nEnter product name to order: ";
        cin >> orderName;
        cout << "Enter quantity: ";
        cin >> orderQty;

        // reiterate hanggang magmatch sa file ung product na hinahanap ng customer
            for (int i = 0; i < menu.size(); ++i) {
                if (toLower(menu[i].name) == toLower(orderName)) {
                    productFound = true;

                    // Validation check para sa stock availability
                    if (menu[i].quantity >= orderQty) {
                        // Automatic inventory deduction sa active running vector
                        menu[i].quantity -= orderQty;
                        
                    //Paki Modify nalang ito andry katulad nung sa search product and sa display product
                    //eto na kase ung receipt sa transaction T- T
                        double totalCost = menu[i].price * orderQty;
                        cout << "\nOrder successful!" << endl;
                        cout<<left<<setw(30)<<"PRODUCT NAME"
            		        <<left<<setw(0)<<"STATUS"
            		        <<right<<setw(30)<<"QUANTITY"
                            <<right<<setw(30)<<"PRICE"<<endl;
                            
                            cout<<setfill('-')<<setw(110)<<"-"<<endl;
		                    cout<<setfill(' ');
                        cout << left << setw(14)<< menu[i].name;
                        cout << right << setw(24) << "CONFIRMED";
                        cout << right << setw(25) << orderQty;
                        cout << right << setw(32) <<"₱" << totalCost << "\n\n";
                        
                        //Pag-save sa .txt file ng mga transactions
                        ofstream tFile("Transaction.txt", ios::app);
                        if (tFile.is_open()) {
                            cout << "Transaction saved." << endl;
                            tFile << menu[i].name << " "
                                  << orderQty << " "
                                  << totalCost << endl;
                                  
                                  tFile.close();
                        }
                        
                        else
                            cout << "\nUnecpected error occured while saving transaction records.\n";

                        // Pag-rewrite sa .txt file para synchronize ang binawas na stock
                        ofstream file("Menu.txt");
                        if (file.is_open()) {
                            for (int j = 0; j < menu.size(); ++j) {
                                file << menu[j].name << "  " 
                                     << menu[j].price << "  " 
                                     << menu[j].quantity << endl;
                            }
                                file.close();
                        }
                    } else {
                        cout << "\nInsufficient stock! Available quantity for '" 
                             << menu[i].name << "' is only " << menu[i].quantity << ".\n" << endl;
                    }
                            break; 
                }
            }

            if (!productFound) {
                cout << "\nProduct not found in the menu.\n" << endl;
            }
    }
}

/*Dito lahat ilalagay ung mga products na ibebenta and ung mga relevant info nila */
void addProduct() {  
    cin.ignore();
    bakedProduct newProduct;
    cout << "\nEnter the name of the product: ";
    cin >> newProduct.name;
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

void displayMenu() {
    menu.clear(); //Icleclear na to kase ung laman neto is nailagay naman sa file so redundant na
    ifstream file("Menu.txt"); //Babasahin na nya ung file
    if (file.is_open()){
        /*Hahanapin na nya sa file ung needed na info based sa data type
        Might change this kase di sya nagaacomodate ng may spaces (eg. Pan de Coco)*/ 
        while(file >> existProduct.name >> existProduct.price >> existProduct.quantity){ 
            menu.push_back(existProduct); //And ipupush na nya sa menu vector na kakaclear lang kanina
        }
        file.close();//and then isasara ung file

        if (menu.empty()){
            cout<<"\nThere is no listed products in the menu.\n";
        } else {
            //ung na pushback ni menu vector is ilalabas na dito
            cout<<"\n"<<endl;
		    cout<<left<<setw(30)<<"NAME"
		        <<left<<setw(0)<<"STATUS"
		        <<right<<setw(30)<<"QUANTITY"
                <<right<<setw(30)<<"PRICE"<<endl;

		    cout<<setfill('-')<<setw(110)<<"-"<<endl;
		    cout<<setfill(' ');

            for (int i=0; i<menu.size(); ++i){
			    cout<<left<<setw(14)<<menu[i].name;
			    if (menu[i].quantity > 0){
                    cout << right << setw(24) << "Available";
                    cout<<right<<setw(25)<<menu[i].quantity
                        <<right<<setw(32)<<"₱"<<menu[i].price<<endl;
                } else {
                    cout << right << setw(26) << "Out of Stock";
                    cout<<right<<setw(23)<<menu[i].quantity
                        <<right<<setw(32)<<"₱"<<menu[i].price<<endl;
                } 
            }
        }
    } 
    cout << endl;
}

void deleteProduct(){ 
    string name;
    cout << "Enter product to delete: ";
    cin >> name;
    cin.ignore();
    
    //gagana lang to if deretso delete agad (di muna nagdisplay bago magdelete)
    loadExistingProducts();

    //i checheck kung nandun ba sa vector ung tatanggaling product
    bool found = false;
    for (int i=0; i<menu.size(); ++i){
        if (toLower(menu[i].name) == toLower(name)) {
            menu.erase(menu.begin() + i);
            found = true;
        }
    }

    //if natanggal successfully, irerewrite ung buong .txt file except ung tinanggal
    if (found){
        ofstream file("Menu.txt");
            for (int i=0 ; i < menu.size(); ++i){
                file << menu[i].name << "  " 
                     << menu[i].price << "  " 
                     << menu[i].quantity << endl;
        }
        file.close();

        cout<<"\nProduct '"<< name << "' was deleted.\n" << endl;
    } else {
        cout << "Product not found.\n" << endl;
    }
}

void updateProduct(){
    string name;
    cout<<"\nWhat product do you want to update: ";
    cin>>name;

    //if deretso agad
    loadExistingProducts();

    //magrereiterate kung may mag match and iaanounce naman agad ni program yan
    for (int i=0; i<menu.size(); ++i){
        if (toLower(menu[i].name) == toLower(name)) {
                cout << "\nProduct found successfully.\n" << endl;
                int choice;
                do {
                    cout<< "What information of "<< menu[i].name << " do you want to update?" << endl
                        << "1. Update Price" << endl
                        << "2. Update Quantity" << endl
                        << "3. Back" << endl
                        << "Enter your choice: ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            cout << "\nEnter your updated price of " << menu[i].name << ": ";
                            cin >> menu[i].price;
                            
                            /* rewriting na sa file ung specific product na gusto natin iupdate same case
                             sa lahat ng cases dito sa function nato, its either price or quantity lang */
                            ofstream file("Menu.txt");
                            for (int i=0 ; i < menu.size(); ++i){
                                file << menu[i].name << "  " 
                                     << menu[i].price << "  " 
                                     << menu[i].quantity << endl;
                            }
                                file.close();

                            cout << "\nPrice Updated!\n" << endl;
                            break;
                        }
                        case 2: {
                            cout << "\nEnter your updated quantity of " << menu[i].name << ": ";
                            cin >> menu[i].quantity;
                            
                            ofstream file("Menu.txt");
                            for (int i=0 ; i < menu.size(); ++i){
                                file << menu[i].name << "  " 
                                     << menu[i].price << "  " 
                                     << menu[i].quantity << endl;
                            }
                                file.close();

                            cout << "\nQuantity Updated!\n" << endl;
                            break;
                        }
                        case 3:
                            cout << endl;
                            break;
                        default:
                         cout << "Invalid choice. Please try again." << endl;
                    }
                } while (choice !=3);
        } else {
            cout << "\nProduct not found.\n" << endl;
        }
    }
}

void searchProduct() {
    string name;
    
    cout << "\nEnter the product you want to search: "; //Enter mo dito ung sinearch mo
    cin.ignore(); //para di magloko yung user-input
    getline (cin, name); //getline para mabasa yung mga white spaces

    //again if deretso ko agad dito ayan muna mag rurun
    loadExistingProducts();
    string searchWord = toLower(name); //ginagawang lowercase yung input from user ara maging case insensitive
    
    bool isFound = false; //boolean ginamit ko rito para madali, di na natin need ng failcount
        //mag rereiterate sya hanggang mag match
    
    cout << endl;
    cout<<"\n"<<endl;
	cout<<left<<setw(30)<<"NAME"
		<<left<<setw(0)<<"STATUS"
		<<right<<setw(30)<<"QUANTITY"
        <<right<<setw(30)<<"PRICE"<<endl;

		    cout<<setfill('-')<<setw(110)<<"-"<<endl;
		    cout<<setfill(' ');

    for (int i=0; i<menu.size(); ++i){
        if (toLower(menu[i].name).find(searchWord) != string::npos) {

			    cout<<left<<setw(14)<<menu[i].name;
			    if (menu[i].quantity > 0){
                    cout << right << setw(24) << "Available";
                    cout<<right<<setw(25)<<menu[i].quantity
                        <<right<<setw(32)<<"₱"<<menu[i].price<<endl;
                } else {
                    cout << right << setw(26) << "Out of Stock";
                    cout<<right<<setw(23)<<menu[i].quantity
                        <<right<<setw(32)<<"₱"<<menu[i].price<<endl;
                }    
                
                isFound = true; //pag may na-search, magiging true, which means merong product na nahanap.
        } 
    }
    if (!isFound) { 
        // and then pag wala talaga ung "Product" na yun sa mga paninda na nailagay na sa vector, edi product not found
        cout << "\nProduct not Found.\n";
    } 
    cout << endl;
}

void changeLogInfo() {
    int choice;
    int logError = 0;
    loginCredentials newInfo;

    cout<<"\nWhat credential do you like to change?"<<endl
        <<"1. Change Username"<<endl
        <<"2. Change Password"<<endl
        <<"3. Back"
        <<"Enter your choice: ";
        cin>>choice;
    
        loadAdmin();

        switch (choice) {
            case 1:
                cout<<"\nEnter your password for confirmation: ";
                cin>>newInfo.password;
                for (int i=0; i < logInfo.size(); ++i){
                    if (newInfo.password == logInfo[i].password) {
                        cout<<"Enter your new username: ";
                        cin>>logInfo[i].username;
                        
                    ofstream file("Admin.txt");
                        for (int i=0 ; i < logInfo.size(); ++i){
                            file << logInfo[i].username << "  " 
                                 << logInfo[i].password << endl;
                        }
                    file.close();
                    cout<<"\nUsername Successfuly Changed!\n"<<endl;

                    } else {
                        logError++;
                    }
                if (logError == logInfo.size()) {
                    cout<<"\nPassword doesn't match.\n"<<endl;
                }
            }
                break;
            case 2:
                cout<<"\nEnter your old password for confirmation: ";
                cin>>newInfo.password;
                for (int i=0; i < logInfo.size(); ++i){
                    if (newInfo.password == logInfo[i].password) {
                        cout<<"Enter your new password: ";
                        cin>>logInfo[i].password;
                        
                    ofstream file("Admin.txt");
                        for (int i=0 ; i < logInfo.size(); ++i){
                            file << logInfo[i].username << "  " 
                                 << logInfo[i].password << endl;
                        }
                    file.close();
                    cout<<"\nPassword Successfuly Changed!\n"<<endl;

                    } else {
                        logError++;
                    }
                if (logError == logInfo.size()) {
                    cout<<"\nPassword doesn't match.\n" <<endl;
                }
            }
                break;
            case 3:
                break;
            default:
                 cout<<"\nInvalid Choice. Please try again\n"<<endl;
        }
}

void addAdmin() {
    loadAdmin();
    loginCredentials newUser;
    loginCredentials veriPass;

    cout<<"Confirm Password: ";
    cin>>veriPass.password;

    for (int i=0; i<logInfo.size(); ++i){
        if (veriPass.password==logInfo[i].password) {
            cout<<"===========CREATE NEW ADMIN===========" << endl;
            cout<<"Add Username: ";
            cin>>newUser.username;
            cout<<"Add Password: ";
            cin>>newUser.password;

            ofstream file("Admin.txt", ios::app);
            file << newUser.username << "  " 
                 << newUser.password << endl;
            file.close();

            logInfo.push_back(newUser);
        }
    }
}