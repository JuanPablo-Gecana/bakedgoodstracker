#include <iostream>
#include <iomanip> //Might use para sa generation ng recipt ng customer or baka sa design ng program itself
#include <string> //Personally di ko pa nakikita relevancy neto pero itetest ko pa
#include <vector> //Needed to para makapagstore ng as many products as we can without limitations
#include <fstream> //pang save ng inventory sa file and possibly ng transaction history ng bawat customers
#include <algorithm> //way para maging case insensitive ung mga icocompare na input later
#include <chrono> //For date related tasks sa program, primarily for pre ordering
#include <format> //to change calendar dates to strings with string library help
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
};

struct orders {
    string customer;
    string productName;
    int quantity;
    double price;
    double paid;
    double change;
    string date;
    string writing;
    string candle;
};

//=========================[Important Struct Variables]==============================

vector <bakedProduct> menu; //pang lagay ng mga items na ibebenta and ididisplay later sa display function
bakedProduct existProduct; //useful sa pagloload sa vector galing sa txt file
vector <loginCredentials> logInfo; //pang store ng login credentials ng mga admin
loginCredentials logCred; //pangload sa vector para may ma compare later
vector <orders> order;
orders temp;
string customerName;
vector <string> customerList;

//===============================[Helper Functions]================================== 

void loadExistingProducts(); //if deretso na agad sa search, update, etc. eto muna magrurun
void loadOrder(string a);
void receipt(string a, string b, int c, double d, double e, double f, double g);
void loadAdmin(); //pangload ng admin info sa file
void loadCustomer(); //need natin to pag bumabalik ng program pang check kung nakaorder na dito already ung customer
string toLower(string s); // Reason na magiging case-insensitive ung program.

//================================[Core Functions]=================================== 

/*itong addProduct kasama ung displayMenu function ang reason na matatandaan lahat ng program ung 
ininput natin na Products*/
void orderProduct();//Main ordering system, dito mag oorder ang mga customer.
void addProduct(); // Mag aadd ng product dun sa program and sa file.
void displayMenu(); //Ipapakita lahat nung nilagay na products doon sa addProduct function.
void deleteProduct(); // Dito yung part kung san magdedelete ka ng products. 
void updateProduct(); //dito mag uupdate ng ating mga current products
void searchProduct(); //dito naman pag gusto ng user na mag search ng specific product

//==============================[Features Functions]=================================

void changeLogInfo(); //If admin gusto paltan ung either username or password
void addOrRemoveAdmin();//Para magdagdag ng admin //Para magtanggal ng admin
string changeCustomer();
void viewPreOrder();
void viewTransactions();
void viewCustomOrders();

//================================[Main Function]==================================== 

int main() {
    choiceInputs choice;
    bool found = false;
    
    do{
        cout<<"Enter your name: ";
        getline(cin, customerName);
        cout<<endl;

        if(customerName.empty()){
            cout <<"Name cannot be empty, Please try again.\n" << endl;
        }
    } while (customerName.empty());

    loadCustomer();

    //Do-while para paulit ulit and para wala nang initialization ng value ung choice variable
    do {
        for (int i=0; i<customerList.size(); ++i){
            if (customerName == customerList[i]){
                cout << "========MULING PAGBATI, "<< customerName 
                     <<"! SA PANADERYA NI HUWAN PABLO========" << endl;
                found = true;
                break;
            } 
        }
        
        if (!found){
            cout << "========PAGBATI, "<< customerName 
                 <<"! SA PANADERYA NI HUWAN PABLO========" << endl;
        }
        
        cout << "1. Order a Product" << endl
             << "2. Search for a Product" << endl
             << "3. Display All Products" << endl
             << "4. Switch Customer" << endl
             << "5. Exit" << endl
             << "Enter your choice: ";
        cin >> choice.code; //string muna here since mag eeror sya pag int tas "ADMIN" nilagay ko

        //Prolly di na hahaba ung 4 conditions since ayan lang naman ung walang editing na mangyayari sa pov ng customer
        if (choice.code == "1" || choice.code == "2" || choice.code == "3" || choice.code == "4" || choice.code == "5") {
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
                    changeCustomer();
                    break;
                case 5:
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
                        << "4. View Transaction History" << endl
                        << "5. View Pre-orders" << endl
                        << "6. View Custom Orders" << endl
                        << "7. Change Username/Password" << endl
                        << "8. Add or Remove an Admin" << endl
                        << "9. Back" << endl
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
                                viewTransactions();
                                break;
                            case 5:
                                viewPreOrder();
                                break;
                            case 6:
                                viewCustomOrders();
                                break;
                            case 7:
                                changeLogInfo();
                                break;
                            case 8:
                                addOrRemoveAdmin();
                                break;
                            case 9:
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                    } while (choice.numCode !=9);
                } else {
                    cout << "\nUsername and Password don't match.\n" << endl;
            
                }
            }
        } else {
            cout << "\nInvalid choice. Please try again.\n" << endl;
        }
    } while (choice.numCode != 5);
    return 0;
}

void loadExistingProducts(){
     if (menu.empty()) { //checheck muna if empty otherwise, ignored to
            ifstream file("Menu.txt"); //read nya ung txt
                if (file.is_open()){ //check if open
                    while(file >> existProduct.name >> existProduct.price >> existProduct.quantity){ //kukunin sa file ung name price and quantity nung product
                    menu.push_back(existProduct); //ipupushback ung tatlo dito sa menu
                }
                file.close(); //icloclose ung file
            }
        }
}

void loadAdmin(){
     if (logInfo.empty()) {//checheck muna if empty otherwise, ignored to
            ifstream file("Admin.txt"); //read nya ung txt
                if (file.is_open()){//check if open
                    while(file >> logCred.username >> logCred.password){ //kukunin sa file ung username and password ng admin
                    logInfo.push_back(logCred); //ipupushback na ito sa vector
                }
                file.close();//icloclose ung file
            }
        }
}

void loadCustomer() {
    string tempCustomerName; //temp baka mag overwrite kase sa current customer

     if (customerList.empty()){ //check if empty otherwise, ignored
        ifstream file("Transaction.txt"); //open ung transaction history
         if(file.is_open()){ //check if open
            while(file >> tempCustomerName) {//kukunin ung mga name ng mga customer na nag order in the past
                customerList.push_back(tempCustomerName); //ilalagay na sya sa vector
            }
		 file.close(); //icloclose ung file
         }
     }
}

void receipt(string a, string b, int c, double d, double e, double f, double g) {
    cout<<"Customer Name: "<< a << endl;
    cout<<left<<setw(30)<<"PRODUCT NAME"
        <<right<<setw(0)<<"QUANTITY"
        <<right<<setw(30)<<"PRICE"<<endl;
                            
    cout<<setfill('-')<<setw(75)<<"-"<<endl;
	cout<<setfill(' ');
    
    cout<<left<<setw(30)<<b
        <<right<<setw(4)<<c
        <<right<<setw(32)<<d<<endl;

    cout<<"\nTotal cost: "<< e << endl;
    cout<<"Amount Paid: "<< f <<endl;
    cout<<"Change: "<< g <<endl;
}

void loadOrder(string a) {
    if (a == "pre"){
        order.clear();
        ifstream file("Pre-orders.txt");
            while (file >> temp.customer >> temp.productName >> temp.quantity >> temp.price >> temp.paid >> temp.change >> temp.date) {
                order.push_back(temp);
            }
        file.close();
    } else if (a == "trans"){
        order.clear();
        ifstream file("Transaction.txt");
            while (file >> temp.customer >> temp.productName >> temp.quantity >> temp.price >> temp.paid >> temp.change >> temp.date) {
                order.push_back(temp);
            }
        file.close();
    } else {
        order.clear();
        ifstream file("Custom Order.txt");
            while (file >> temp.customer >> temp.productName >> temp.writing >> temp.candle) {
                order.push_back(temp);
            }
        file.close();
    }
}

string toLower(string s) {
    //transform(startPOS, endPOS, startPOSngoutput, ung gagawin)
    transform(s.begin(), s.end(), s.begin(), ::tolower); 
    return s;
}

void orderProduct() {
    loadExistingProducts();

    if (menu.empty()) { //checheck if empty ung menu
        cout << "\nSorry, the menu is currently empty. No items to order.\n" << endl; //then ito lalabas pag wala talagang laman
    } else {
        string orderName;
        int orderQty;
        bool productFound = false;
        double payment;
        double totalCost;
        double change = 0;
        string date;
        char response;

        cout << "\nEnter product name to order: ";
        getline(cin, orderName);
        cout << "Enter quantity: ";
        cin >> orderQty;

        replace(orderName.begin(), orderName.end(), ' ', '_');

        for (int i=0; i<menu.size(); ++i){
            if (toLower(menu[i].name).find("cake") != string::npos && toLower(menu[i].name) == toLower(orderName)) {
                string writing;
                cout<<"\nWould you like to create a custom writing on the cake?(y/n): ";
                cin>>response;
                if (response == 'y'){
                    cin.ignore();
                    cout<<"\nType your custom writing here: ";
                    getline(cin, writing);

                    replace(writing.begin(), writing.end(), ' ', '_');
                        
                    cout<<"\nWould you like a candle for the cake for free?(y/n): ";
                    cin>>response;
                    ofstream file("Custom Order.txt", ios::app);
                    file << customerName << "  "
                         << menu[i].name << "  "
                         << writing << "  ";
                    if (response == 'y'){
                        file << "w_Candle" << endl;
                    } else {
                        file << "w/o_Candle" << endl;
                    } file.close();
                } else {
                    break;
                }
            }
        }

        // reiterate hanggang magmatch sa file ung product na hinahanap ng customer
            for (int i = 0; i < menu.size(); ++i) {
                if (toLower(menu[i].name) == toLower(orderName)) {
                    productFound = true;

                    // Validation check para sa stock availability
                    if (menu[i].quantity >= orderQty) {
                        // Automatic inventory deduction sa active running vector
                        menu[i].quantity -= orderQty;
                        
                    //eto ung receipt sa transaction
                        totalCost = menu[i].price * orderQty;
                        
                        do {
                            cout<<"The cost of " << orderName << " is " << totalCost << "." << endl;
                            cout<<"Please enter your payment: ";
                            cin>>payment;

                            if (payment >= totalCost) {
                                change = payment - totalCost;
                                cout << "\nOrder successful!\n" << endl;
                            } else {
                                cout << "\nInsufficient Funds\n" << endl;
                            }
                        } while (payment < totalCost);
                        
                        receipt(customerName, menu[i].name, orderQty, menu[i].price, totalCost,  payment, change);

                        chrono::sys_days today = chrono::time_point_cast<chrono::days>(chrono::system_clock::now());
                        chrono::year_month_day calendarDate{today};
                        
                        //Pag-save sa .txt file ng mga transactions
                        ofstream tFile("Transaction.txt", ios::app);
                        if (tFile.is_open()) {
                            tFile << customerName << "  "
                                  << menu[i].name << "  "
                                  << orderQty << "  "
                                  << totalCost << "  "
                                  << payment << "  "
                                  << change << "  "
                                  << calendarDate << endl;
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
                        cout << "\nInsufficient stock! Would you like to pre-order?(y/n): ";
                        cin >> response;

                        if (response == 'y'){
                            totalCost = menu[i].price * orderQty;

                           do {
                            cout<<"The cost of " << orderName << " is " << totalCost << "." << endl;
                            cout<<"Please enter your payment: ";
                            cin>>payment;

                            if (payment >= totalCost) {
                                change = payment - totalCost;
                                cout << "\nOrder successful!\n" << endl;
                            } else {
                                cout << "\nInsufficient Funds\n" << endl;
                            }
                        } while (payment < totalCost);
                            
                        chrono::sys_days today = chrono::time_point_cast<chrono::days>(chrono::system_clock::now());
                        chrono::year_month_day calendarDate{today};
                        string currentDate = format("{}", calendarDate);

                          do {
                            cout<<"What date do you want to claim the item when it restocks (YYYY-MM-DD): ";
                            cin>>date;

                            if (date > currentDate) {
                                ofstream file("Pre-orders.txt", ios::app);
                                file << customerName << "  "
                                     << menu[i].name << "  "
                                     << orderQty << "  "
                                     << totalCost << "  "
                                     << payment << "  "
                                     << change << "  "
                                     << date << endl;
                                file.close();
                                
                                cout<<endl;

                                receipt(customerName, menu[i].name, orderQty, menu[i].price, totalCost,  payment, change);

                                cout<<"\nPre-Ordered Successfuly\n"<<endl;
                            } else {
                                cout<<"\n Date is not Available\n"<<endl;
                            }
                          } while (date <= currentDate);   
                        } else {
                            cout<<"\nPre-ordering aborted.\n"<<endl;
                        }
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
    getline(cin, newProduct.name);
    cout << "Enter the price of the product: ";
    cin >> newProduct.price;
    cout << "Enter the quantity of the product: ";
    cin >> newProduct.quantity;

    replace(newProduct.name.begin(), newProduct.name.end(), ' ', '_');

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
        /*Hahanapin na nya sa file ung needed na info based sa data type*/
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
			    if (menu[i].quantity > 0){//may if dito kung available or not ba ung product 
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
    getline(cin, name);
    cin.ignore();
    
    replace(name.begin(), name.end(), ' ', '_');

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
    bool found = false;

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
                            found = true;
                            break;
                        }
                        case 2: {
                            cout << "\nEnter your updated quantity of " << menu[i].name << ": ";
                            cin >> menu[i].quantity;

                            loadOrder("pre");

                            for (int j=0; j<order.size(); ++j){
                                if (menu[i].name == order[j].productName && menu[i].quantity >= order[j].quantity){
                                    cout<<"\nYou have a pre-order for this product for customer "<< order[j].customer<<"! Automatically deducting... \n" << endl;
                                    menu[i].quantity -= order[j].quantity;

                                    ofstream file("Transaction.txt", ios::app);
                                        file << order[j].customer << "  " 
                                             << order[j].productName << "  " 
                                             << order[j].quantity << "  "
                                             << order[j].price << "  "
                                             << order[j].paid << "  "
                                             << order[j].change << "  "
                                             << order[j].date << endl;
                                    file.close();

                                    order.erase(order.begin() + j);

                                    for (int k=0; k<order.size(); ++k){
                                        ofstream pfile("Pre-orders.txt");
                                        pfile << order[j].customer << "  " 
                                             << order[j].productName << "  " 
                                             << order[j].quantity << "  "
                                             << order[j].price << "  "
                                             << order[j].paid << "  "
                                             << order[j].change << "  "
                                             << order[j].date << endl;
                                        file.close();
                                    }

                                        ofstream mfile("Menu.txt");
                                        for (int l=0 ; l < menu.size(); ++l){
                                            mfile << menu[l].name << "  " 
                                                 << menu[l].price << "  " 
                                                 << menu[l].quantity << endl;
                                        }
                                        file.close();

                                        cout<<"The updated quantity of "<< menu[i].name << " is " << menu[i].quantity << "!\n" << endl;
                                } else {
                                     /* rewriting na sa file ung specific product na gusto natin iupdate same case
                                    sa lahat ng cases dito sa function nato, its either price or quantity lang */
                                    ofstream file("Menu.txt");
                                        for (int i=0 ; i < menu.size(); ++i){
                                            file << menu[i].name << "  " 
                                                 << menu[i].price << "  " 
                                                 << menu[i].quantity << endl;
                                        }
                                    file.close();

                                    cout << "\nQuantity Updated!\n" << endl;
                                }
                            }
                            found = true;
                            break;
                        }
                        case 3:
                            cout << endl;
                            break;
                        default:
                         cout << "Invalid choice. Please try again." << endl;
                    }
                } while (choice !=3);
        } 
        if (found) {
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
    
    bool isFound = true; //boolean ginamit ko rito para madali, di na natin need ng failcount
        //mag rereiterate sya hanggang mag match

    for (int i=0; i<menu.size(); ++i){
        if (toLower(menu[i].name).find(searchWord) == string::npos) {
                //pag wala talaga ung "Product" na yun sa mga paninda na nailagay na sa vector, edi product not found
                isFound = false; 
        }       
    } 

    //pag may na-search, magiging true, which means merong product na nahanap.
    if (!isFound) { 
        cout<<endl;
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
            }
        } 
    } else {
        cout << "\nProduct not Found.\n";
    }
    cout << endl;
}

void changeLogInfo() { 
    int choice;
    bool logError = true;
    loginCredentials newInfo;

    cout<<"\nWhat credential do you like to change?"<<endl //bibigyan ng option si admin kung ano papaltan
        <<"1. Change Username"<<endl
        <<"2. Change Password"<<endl
        <<"3. Back"<<endl
        <<"Enter your choice: ";
        cin>>choice;
    
        loadAdmin(); //iloload ung current admin info

        switch (choice) {
            case 1:
                cout<<"\nEnter your password for confirmation: "; //mandatory to sa lahat ng admin action regarding pag aadd pagreremove and pag palit ng info ng admin
                cin>>newInfo.password;
                for (int i=0; i < logInfo.size(); ++i){
                    if (newInfo.password == logInfo[i].password) { //check muna if may mag match
                        cout<<"Enter your new username: "; //papainputin 
                        cin>>logInfo[i].username;

					//then iooverwrite ung buong txt file with ung bagong updated username
                    ofstream file("Admin.txt"); 
                        for (int i=0 ; i < logInfo.size(); ++i){
                            file << logInfo[i].username << "  " 
                                 << logInfo[i].password << endl;
                        }
                    file.close();
                    cout<<"\nUsername Successfuly Changed!\n"<<endl;

                    } else {
                        logError=false;
                    }
                if (!logError) {
                    cout<<"\nPassword doesn't match.\n"<<endl;
                }
            }
                break;
            case 2: //might update later
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
                        logError=false;
                    }
                if (!logError) {
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

void addOrRemoveAdmin() {
    int choice;
    loginCredentials delUser;
    loginCredentials veriPass;
    loginCredentials newUser;
    loadAdmin();
    bool isFound=false;

    do{
        cout<<"\n===========ADD OR DELETE ADMIN===========" << endl
            <<"1. Add Admin" << endl
            <<"2. Delete Admin" << endl
            <<"3. Back" << endl
            <<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Confirm Password: ";//need ng confirmation ng current admin
                cin>>veriPass.password;
                cout<<endl;

                for (int i=0; i<logInfo.size(); ++i){
                    if (veriPass.password==logInfo[i].password) { //checheck if may mag match
                        cout<<"===========CREATE NEW ADMIN===========" << endl;
                        cout<<"Add Username: ";
                        cin>>newUser.username;
            
                        do {
                            cout<<"Add Password (Should be atleast 8 characters): "; //need 8 characters minimun, uulit yan pag di nameet 
                            cin>>newUser.password;

				            //and then if ok na, isasama na sya sa file and sa current vector
                            if (newUser.password.size() == 8) {
                                ofstream file("Admin.txt", ios::app);
                                    file << newUser.username << "  " 
                                         << newUser.password << endl;
                                file.close();

                                logInfo.push_back(newUser);
                                cout<<"\nAdmin Successfuly Added!\n"<<endl;
                                isFound=true;
                            } else {
                                cout<<"\nPassword too short.\n"<<endl;
                            }
                        } while (newUser.password.size() < 8);
                    }
                }
            if (!isFound){
                cout<<"\nPassword doesn't match.\n"<<endl;
            }
            break;

            case 2:
            cout<<"\nConfirm Password: "; //need ulit confirmation ng current admin
            cin>>veriPass.password;
            cout<<endl;

            for (int i=0; i<logInfo.size(); ++i){ //ichecheck if may magmatch
                if (veriPass.password==logInfo[i].password) {
                    cout<<"===========DELETE ADMIN===========" << endl;
                    cout<<"Enter Admin Username to Delete: "; //ieenter na dito ung ireremove na admin
                    cin>>delUser.username;
                    loadAdmin();
                    for (int j=0; j<logInfo.size(); ++j){
                        if (toLower(delUser.username)==toLower(logInfo[j].username)){
                            logInfo.erase(logInfo.begin() + j); //if may existing admin na same username, tatanggalin na yon sa vector 
                            isFound=true;
                        }
                    }
                } 

                if (isFound){
                    ofstream file("Admin.txt");// and sa file ng admin mismo
                    file << logInfo[i].username << "  " 
                         << logInfo[i].password << endl;
                    file.close();

                    cout<<"\nAdmin Successfuly Deleted!\n"<<endl;
                }           
            }
            if (!isFound){
                cout<<"\nPassword doesn't match.\n"<<endl;
            }
            break;

            case 3:
            break;

            default:
            cout << "Invalid choice. Please try again." << endl;
        }   
    } while (choice != 3);
}

string changeCustomer() {
    cin.ignore(); //para di mag error ung user input
    cout<<endl;
    cout<<"Enter your name: ";
    getline(cin, customerName); //getline para maacomodate ung may spaces (like Juan Pablo)
    cout<<endl;
    return customerName;
}

void viewPreOrder() {
    cout<<endl;
    loadOrder("pre");
    for(int i=0; i<order.size(); i++) {
        cout<<"Customer Name: "<< order[i].customer << "\n" << endl;
        cout<<left<<setw(30)<<"PRODUCT NAME"
            <<right<<setw(0)<<"QUANTITY"
            <<right<<setw(30)<<"DATE TO BE CLAIMED"<<endl;
                            
        cout<<setfill('-')<<setw(75)<<"-"<<endl;
	    cout<<setfill(' ');
    
        cout<<left<<setw(30)<< order[i].productName
            <<right<<setw(4)<< order[i].quantity
            <<right<<setw(30)<< order[i].date <<endl;

        cout<<setfill('-')<<setw(75)<<"-"<<endl;
	    cout<<setfill(' ');
        cout<<endl;
    }
}

void viewTransactions() {
    loadOrder("trans");
    cout<<endl;
    for(int i=0; i<order.size(); i++) {
        cout<<"Customer Name: "<< order[i].customer << "\n" << endl;
        cout<<left<<setw(30)<<"PRODUCT NAME"
            <<right<<setw(0)<<"QUANTITY"
            <<right<<setw(30)<<"DATE OF TRANSACTION"<<endl;
                            
        cout<<setfill('-')<<setw(75)<<"-"<<endl;
	    cout<<setfill(' ');
    
        cout<<left<<setw(30)<< order[i].productName
            <<right<<setw(4)<< order[i].quantity
            <<right<<setw(30)<< order[i].date <<endl;

        cout<<setfill('-')<<setw(75)<<"-"<<endl;
	    cout<<setfill(' ');
        cout<<endl;
    }
}

void viewCustomOrders() {
    loadOrder("custom");
    int number;
    int choice;
    do{
        cout<<endl;
        for(int i=0; i<order.size(); i++) {
            cout<<"Custom Order No."<<i+1<<endl;
            cout<<"Customer Name: "<< order[i].customer << "\n" << endl;
            cout<<left<<setw(30)<<"PRODUCT NAME"
                <<right<<setw(0)<<"MESSAGE"
                <<right<<setw(30)<<"CANDLE"<<endl;
                            
            cout<<setfill('-')<<setw(75)<<"-"<<endl;
	        cout<<setfill(' ');
    
            cout<<left<<setw(30)<< order[i].productName
                <<right<<setw(2)<< order[i].writing
                <<right<<setw(26)<< order[i].candle <<endl;
    
            cout<<setfill('-')<<setw(75)<<"-"<<endl;
	        cout<<setfill(' ');
            cout<<endl;
        }

        cout << "\n1. Remove a Custom Order" <<endl
            << "2. Back" << endl
            << "Enter your choice: ";
        cin>>choice;
        cin.ignore();

        switch(choice){
            case 1: {
                cout<<"Enter the Custom Order No. to Delete: ";
                cin>>number;

                order.erase(order.begin() + (number-1));

                ofstream dfile("Custom Order.txt");
                for (int i=0; i<order.size(); ++i){
                    dfile << order[i].customer << "  "
                      << order[i].productName << "  "
                      << order[i].writing << "  "
                      << order[i].candle << endl;
                dfile.close();
                }

                cout<<"\nCustom Order successfully deleted\n" << endl;
                break;
            }
            case 2:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 2);
}