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

//struct for orders and mapapasa and magagamit to sa pag gegenerate ng receipt
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
vector <orders> order; //pangstore ng order ng mga customer
orders temp;
string customerName;
vector <string> customerList;
loginCredentials login;

//===============================[Helper Functions]================================== 

void loadExistingProducts(); // Line 192 - if deretso na agad sa search, update, etc. eto muna magrurun
void loadOrder(string a); // Line 204 - may condition to since same same lang ung operations and vector arraypero different files lang naman
void receipt(string a, string b, int c, double d, double e, double f, double g); // Line 229 - helper function para sa pag generate ng receipts sa mga transactions
void loadAdmin(); // Line 247 - pangload ng admin info sa file
void loadCustomer(); // Line 259 - need natin to pag bumabalik ng program pang check kung nakaorder na dito already ung customer
string toLower(string s); // Line 273 - Reason na magiging case-insensitive ung program.

//================================[Customer Menu]=================================== 

void orderProduct();// Line 281 - Main ordering system, dito mag oorder ang mga customer.
void displayMenu(); // Line 463 - Ipapakita lahat nung nilagay na products doon sa addProduct function.
void searchProduct(); // Line 503 - dito naman pag gusto ng user na mag search ng specific product
string changeCustomer(); // Line 556 - Eto para mag palit ng name ng customer without the need na tapusin ung program

//==============================[Admin Menu]=================================

void addProduct(); // Line 569 - Mag aadd ng product dun sa program and sa file.
void deleteProduct(); // Line 595 - Dito yung part kung san magdedelete ka ng products. 
void updateProduct(); // Line 633 - dito mag uupdate ng ating mga current products
void viewTransactions(); // Line 757 - Function para makita ang transaction history
void viewPreOrder(); // Line 784 - Para makita ng mga admin ung mga pre orders
void viewCustomOrders(); // Line 811 - para makita ung mga custom orders sa mga cakes and makita din if may candle ding kasama
void changeLogInfo(); // Line 876 - If admin gusto paltan ung either username or password
void addOrRemoveAdmin();//Line 954 - Para magdagdag ng admin //Para magtanggal ng admin

//================================[Main Function]==================================== 

int main() {
    choiceInputs choice;
    bool found = false;
    
    do{
        cout<<"Ilagay ang iyong pangalan: ";
        getline(cin, customerName);
        cout<<endl;

        if(customerName.empty()){
            cout <<"Hindi maaaring walang lamang ang pangalan. Pakisubukan muli.\n" << endl;
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
        
        cout << "1. Mag-order ng Produkto" << endl
             << "2. Maghanap ng Produkto" << endl
             << "3. Ipakita ang Lahat ng Produkto" << endl
             << "4. Palitan ang Pangalan ng Customer" << endl
             << "5. Lumabas" << endl
             << "Ilagay ang iyong pinili: ";
        cin >> choice.code; //string muna here since mag eeror sya pag int tas "ADMIN" nilagay ko

        //Prolly di na hahaba ung 4 conditions since ayan lang naman ung walang editing na mangyayari sa pov ng customer
        if (choice.code == "1" || choice.code == "2" || choice.code == "3" || choice.code == "4" || choice.code == "5") {
            choice.numCode = stoi(choice.code); //stoi para maging int sya pag nag switch na
            switch (choice.numCode) {
                case 1: orderProduct(); break;
                case 2: searchProduct(); break;
                case 3: displayMenu(); break;  
                case 4: changeCustomer(); break;
                case 5: cout << "\nSalamat at bumalik kayo ulit!" << endl; break;
                default: cout << "Maling pinili. Pakisubukan muli." << endl;     
            }
        } else if (choice.code == "ADMIN") { //What if ADMIN na, eto mangyayari
            
            cout << "\n=======================ADMIN LOGIN=======================\n";
            cout << "Username: ";//Needed nya na mag input ng username and password
            cin >> login.username;
            cout << "Password: ";
            cin >> login.password;
            cout << "========================================================\n";

            loadAdmin();

            //If magmatch... welcome sa bagong ui natin for admin, dito nakalagay ung mga revision sa menu ng products natin
            for (int i=0; i < logInfo.size() ; ++i) {
                if (logInfo[i].username == login.username && logInfo[i].password == login.password) {
                    cout<<endl;
                    do{
                        cout << "========Maligayang Pagdating Admin "<< logInfo[i].username << "!========" << endl
                        << "1. Magdagdag ng Produkto" << endl
                        << "2. Magtanggal ng Produkto" << endl
                        << "3. I-update ang Produkto" << endl
                        << "4. Tingnan ang Kasaysayan ng Transaksyon" << endl
                        << "5. Tingnan ang mga Pre-order" << endl
                        << "6. Tingnan ang mga Custom Order" << endl
                        << "7. Palitan ang Username/Password" << endl
                        << "8. Magdagdag o Magtanggal ng Admin" << endl
                        << "9. Bumalik" << endl
                        << "Ilagay ang iyong pinili: ";
                        cin >> choice.numCode;

                        switch (choice.numCode) {
                            case 1: addProduct(); break;
                            case 2: deleteProduct(); break;
                            case 3: updateProduct(); break;
                            case 4: viewTransactions(); break;
                            case 5: viewPreOrder(); break;
                            case 6: viewCustomOrders(); break;
                            case 7: changeLogInfo(); break;
                            case 8: addOrRemoveAdmin(); break;
                            case 9: break; 
                            default: cout << "Maling pinili. Pakisubukan muli." << endl;
                        }
                    } while (choice.numCode !=9);
                } else {
                    cout << "\nHindi tugma ang Username at Password.\n" << endl;
                }
            }
        } else {
            cout << "\nMaling pinili. Pakisubukan muli.\n" << endl;
        }
    } while (choice.numCode != 5);
    return 0;
}

//===============================[Helper Functions]================================== 

void loadExistingProducts(){
     if (menu.empty()) { //checheck muna if empty otherwise, ignored to
        ifstream file("../bakedgoodstracker/file/Menu.txt"); //read nya ung txt
            if (file.is_open()){ //check if open
                while(file >> existProduct.name >> existProduct.price >> existProduct.quantity){ //kukunin sa file ung name price and quantity nung product
                    menu.push_back(existProduct); //ipupushback ung tatlo dito sa menu
                }
            file.close(); //icloclose ung file
        	}
    }
}

void loadOrder(string a) {
    if (a == "pre"){
        order.clear();
        ifstream file("../bakedgoodstracker/file/Pre-orders.txt");
            while (file >> temp.customer >> temp.productName >> temp.quantity >> temp.price >> temp.paid >> temp.change >> temp.date) {
                order.push_back(temp);
            }
        file.close();
    } else if (a == "trans"){
        order.clear();
        ifstream file("../bakedgoodstracker/file/Transaction.txt");
            while (file >> temp.customer >> temp.productName >> temp.quantity >> temp.price >> temp.paid >> temp.change >> temp.date) {
                order.push_back(temp);
            }
        file.close();
    } else {
        order.clear();
        ifstream file("../bakedgoodstracker/file/Custom Order.txt");
            while (file >> temp.customer >> temp.productName >> temp.writing >> temp.candle) {
                order.push_back(temp);
            }
        file.close();
    }
}

void receipt(string a, string b, int c, double d, double e, double f, double g) {
    cout<<"Pangalan ng Customer: "<< a << endl;
    cout<<left<<setw(30)<<"PANGALAN NG PRODUKTO"
        <<right<<setw(0)<<"KANTIDAD"
        <<right<<setw(30)<<"PRESYO"<<endl;
                            
    cout<<setfill('-')<<setw(75)<<"-"<<endl;
	cout<<setfill(' ');
    
    cout<<left<<setw(30)<<b
        <<right<<setw(4)<<c
        <<right<<setw(32)<<d<<endl;

    cout<<"\nKabuuang Halaga: "<< e << endl;
    cout<<"Halagang Binayad: "<< f <<endl;
    cout<<"Sukli: "<< g <<endl;
}

void loadAdmin(){
     if (logInfo.empty()) {//checheck muna if empty otherwise, ignored to
        ifstream file("../bakedgoodstracker/file/Admin.txt"); //read nya ung txt
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
        ifstream file("../bakedgoodstracker/file/Transaction.txt"); //open ung transaction history
         if(file.is_open()){ //check if open
            while(file >> tempCustomerName) {//kukunin ung mga name ng mga customer na nag order in the past
                customerList.push_back(tempCustomerName); //ilalagay na sya sa vector
            }
		 file.close(); //icloclose ung file
         }
     }
}

string toLower(string s) {
    //transform(startPOS, endPOS, startPOSngoutput, ung gagawin)
    transform(s.begin(), s.end(), s.begin(), ::tolower); 
    return s;
}

//================================[Customer Menu]=================================== 

void orderProduct() {
    loadExistingProducts();

    if (menu.empty()) { //checheck if empty ung menu
        cout << "\nPaumanhin, walang laman ang menu sa kasalukuyan. Walang maiorder.\n" << endl; //then ito lalabas pag wala talagang laman
    } else {
        string orderName;
        int orderQty;
        bool productFound = false;
        double payment;
        double totalCost;
        double change = 0;
        string date;
        char response;

        cout<<"\n================PAG-OORDER NG PRODUKTO===================";
        cin.ignore();
        cout << "\nIlagay ang pangalan ng produktong gustong iorder: ";
        getline(cin, orderName);
        cout << "Ilagay kung ilan ang gustong bilhin: ";
        cin >> orderQty;

        replace(orderName.begin(), orderName.end(), ' ', '_');

        //ichecheck muna if ung inorder is cake
        for (int i=0; i<menu.size(); ++i){
            //hahanapin nya basta na may word na cake and check if that cake is meron sa menu
            if (toLower(menu[i].name).find("cake") != string::npos && toLower(menu[i].name) == toLower(orderName)) {
                string writing;
                cout<<"\nNais mo bang gumawa ng custom na sulat sa cake?(y/n): ";
                cin>>response;
                if (response == 'y'){
                    cin.ignore();
                    cout<<"\nI-type ang iyong custom na sulat dito: ";
                    getline(cin, writing);

                    replace(writing.begin(), writing.end(), ' ', '_'); //para maging isang string ung message and para mabasa ni program ung buong message
                } 

                //mag aask naman sya kung may kasamang kandila regardless kung may writing o wala
                cout<<"\nGusto mo ba ng libreng kandila para sa cake?(y/n): ";
                cin>>response;
                ofstream file("../bakedgoodstracker/file/Custom Order.txt", ios::app);
                file << customerName << "  "
                     << menu[i].name << "  "
                     << writing << "  ";
                if (response == 'y'){
                    file << "w_Candle" << endl;
                } else {
                    file << "w/o_Candle" << endl;
                } file.close();
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
                            cout<<"Ang halaga ng " << orderName << " ay " << totalCost << "." << endl;
                            cout<<"Pakilagay ang iyong bayad: ";
                            cin>>payment;

                            if (payment >= totalCost) {
                                change = payment - totalCost;
                                cout << "\nMatagumpay na naiorder!\n" << endl;
                            } else {
                                cout << "\nKulang ang iyong bayad.\n" << endl;
                            }
                        } while (payment < totalCost);
                        
                        receipt(customerName, menu[i].name, orderQty, menu[i].price, totalCost,  payment, change);

                        //chrono para makuha ung system clock date galing mismo sa device mo
                        chrono::sys_days today = chrono::time_point_cast<chrono::days>(chrono::system_clock::now());
                        chrono::year_month_day calendarDate{today};
                        
                        //Pag-save sa .txt file ng mga transactions
                        ofstream tFile("../bakedgoodstracker/file/Transaction.txt", ios::app);
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
                            cout << "\nNagkaroon ng hindi inaasahang error habang isinasave ang mga rekord ng transaksyon.\n";

                        // Pag-rewrite sa .txt file para synchronize ang binawas na stock
                        ofstream file("../bakedgoodstracker/file/Menu.txt");
                        if (file.is_open()) {
                            for (int j = 0; j < menu.size(); ++j) {
                                file << menu[j].name << "  " 
                                     << menu[j].price << "  " 
                                     << menu[j].quantity << endl;
                            }
                                file.close();
                        }
                    } else {
                        //pag wala ung product currently pwede mag restock
                        cout << "\nKulang ang stock! Gusto mo bang mag-pre-order?(y/n): ";
                        cin >> response;

                        if (response == 'y'){
                            totalCost = menu[i].price * orderQty;

                            //if mag prepre order, proceed sya sa normal transactions
                           do {
                            cout<<"Ang halaga ng " << orderName << " ay " << totalCost << "." << endl;
                            cout<<"Pakilagay ang iyong bayad: ";
                            cin>>payment;

                            if (payment >= totalCost) {
                                change = payment - totalCost;
                                cout << "\nMatagumpay na naiorder!\n" << endl;
                            } else {
                                cout << "\nKulang ang iyong bayad\n" << endl;
                            }
                        } while (payment < totalCost);
                        
                        //chrono para makuha ung system clock date galing mismo sa device mo
                        chrono::sys_days today = chrono::time_point_cast<chrono::days>(chrono::system_clock::now());
                        chrono::year_month_day calendarDate{today};

                        //format para maging string and comparable sya later pag kailan kukunin
                        string currentDate = format("{}", calendarDate);

                          do {
                            cout<<"Kailan mo gusto kunin ang item pagkatapos itong ma-restock (YYYY-MM-DD): ";
                            cin>>date;

                            //di nya iaacept if kahapon either ngayon or sa susunod na araw base din sa device mo
                            if (date >= currentDate) {
                                //and then isasave na sya sa file
                                ofstream file("../bakedgoodstracker/file/Pre-orders.txt", ios::app);
                                file << customerName << "  "
                                     << menu[i].name << "  "
                                     << orderQty << "  "
                                     << totalCost << "  "
                                     << payment << "  "
                                     << change << "  "
                                     << date << endl;
                                file.close();
                                
                                cout<<endl;

                                //and mag gegenerate ng resibo
                                receipt(customerName, menu[i].name, orderQty, menu[i].price, totalCost,  payment, change);

                                cout<<"\nMatagumpay na naiPre-Order\n"<<endl;
                            } else {
                                cout<<"\n Hindi Available ang Petsa\n"<<endl;
                            }
                          } while (date <= currentDate);   
                        } else {
                            cout<<"\nKinansela ang Pre-order.\n"<<endl;
                        }
                    }
                            break; 
                }
            }

            if (!productFound) {
                cout << "\nWalang nahanap na produkto sa menu.\n" << endl;
            }
    }
}

void displayMenu() {
    menu.clear(); //Icleclear na to kase ung laman neto is nailagay naman sa file so redundant na
    ifstream file("../bakedgoodstracker/file/Menu.txt"); //Babasahin na nya ung file
    if (file.is_open()){
        /*Hahanapin na nya sa file ung needed na info based sa data type*/
        while(file >> existProduct.name >> existProduct.price >> existProduct.quantity){ 
            menu.push_back(existProduct); //And ipupush na nya sa menu vector na kakaclear lang kanina
        }
        file.close();//and then isasara ung file
        
        if (menu.empty()){
            cout<<"\nWalang nakalistang produkto sa menu.\n";
        } else {
            //ung na pushback ni menu vector is ilalabas na dito
            cout<<"\n"<<endl;
		    cout<<left<<setw(30)<<"PANGALAN"
		        <<right<<setw(17)<<"KATAYUAN"
		        <<right<<setw(29)<<"DAMI"
                <<right<<setw(30)<<"PRESYO"<<endl;

		    cout<<setfill('-')<<setw(110)<<"-"<<endl;
		    cout<<setfill(' ');

            for (int i=0; i<menu.size(); ++i){
			    cout<<left<<setw(25)<<menu[i].name;
			    if (menu[i].quantity > 0){//may if dito kung available or not ba ung product 
                    cout << right << setw(23) << "May Stock";
                    cout<<right<<setw(26)<<menu[i].quantity
                        <<right<<setw(30)<<"PHP "<<menu[i].price<<endl;
                } else {
                    cout << right << setw(26) << "Walang Stock";
                    cout<<right<<setw(23)<<menu[i].quantity
                        <<right<<setw(30)<<"PHP "<<menu[i].price<<endl;
                } 
            }
        }
    } 
    cout << endl;
}
void searchProduct() {
    string name;
    
    cout<<"\n================PAG-HAHANAP NG PRODUKTO===================";
    cout << "\nIlagay ang produktong gusto mong hanapin: "; //Enter mo dito ung sinearch mo
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
	    cout<<left<<setw(30)<<"PANGALAN"
		    <<left<<setw(0)<<"KATAYUAN"
		    <<right<<setw(30)<<"DAMI"
            <<right<<setw(30)<<"PRESYO"<<endl;

		cout<<setfill('-')<<setw(110)<<"-"<<endl;
		cout<<setfill(' ');
        
        for (int i=0; i<menu.size(); ++i){
            if (toLower(menu[i].name).find(searchWord) != string::npos) {
			    cout<<left<<setw(14)<<menu[i].name;
			    if (menu[i].quantity > 0){
                    cout << right << setw(24) << "May Stock";
                    cout<<right<<setw(25)<<menu[i].quantity
                        <<right<<setw(32)<<"₱"<<menu[i].price<<endl;
                } else {
                    cout << right << setw(26) << "Walang Stock";
                    cout<<right<<setw(23)<<menu[i].quantity
                        <<right<<setw(32)<<"₱"<<menu[i].price<<endl;
                }
            }
        } 
    } else {
        cout << "\nWalang Natagpuang Produkto.\n";
    }
    cout << endl;
}

string changeCustomer() {
    cout<<"\n================PAG-PAPALIT NG PANGALAN===================";
    cin.ignore(); //para di mag error ung user input
    cout<<endl;
    cout<<"Ilagay ang iyong pangalan: ";
    getline(cin, customerName); //getline para maacomodate ung may spaces (like Juan Pablo)
    cout<<endl;
    return customerName;
}

//==============================[Admin Menu]=================================

/*Dito lahat ilalagay ung mga products na ibebenta and ung mga relevant info nila */
void addProduct() {  
    cin.ignore();
    bakedProduct newProduct;

    cout<<"\n================PAG-DAGDAG NG PRODUKTO===================";
    cout << "\nIlagay ang pangalan ng produkto: "; //ilalagay yung pangalan ng product
    getline(cin, newProduct.name);
    cout << "Ilagay ang presyo ng produkto: "; // presyo nya
    cin >> newProduct.price;
    cout << "Ilagay kung gaano karami ang produkto: "; // and gaano kadami ung stock 
    cin >> newProduct.quantity;

    replace(newProduct.name.begin(), newProduct.name.end(), ' ', '_');

    //After malagay lahat ng relevant info, ilalagay na nya muna sa file
    ofstream file("../bakedgoodstracker/file/Menu.txt", ios::app);
    if (file.is_open()){
        file << newProduct.name << "  "
             << newProduct.price << "  "
             << newProduct.quantity << endl;
        file.close();
    }

    cout << "\nMatagumpay na naidagdag ang produkto!\n" << endl;
}

void deleteProduct(){ 
    string name;
    cin.ignore();

    cout<<"\n================PAG-TANGGAL NG PRODUKTO===================";
    cout << "\nIlagay ang produktong gustong tanggalin: "; //ilalagay dito ung gustong tanggalin
    getline(cin, name);
    
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
        ofstream file("../bakedgoodstracker/file/Menu.txt");
            for (int i=0 ; i < menu.size(); ++i){
                file << menu[i].name << "  " 
                     << menu[i].price << "  " 
                     << menu[i].quantity << endl;
        }
        file.close();

        cout<<"\nNatanggal ang produktong '"<< name << "'.\n" << endl;
    } else {
        cout << "Hindi natagpuan ang produkto.\n" << endl;
    }
}

void updateProduct(){
    string name;
    bool found = false;
    bool updated = false;

    cout<<"\n================PAG-UUPDATE NG PRODUKTO===================";
    cin.ignore();
    cout<<"\nAling produkto ang gusto mong i-update: ";
    getline(cin, name);

    replace(name.begin(), name.end(), ' ', '_');

    //if deretso agad
    loadExistingProducts();

    //magrereiterate kung may mag match and iaanounce naman agad ni program yan
    for (int i=0; i<menu.size(); ++i){
        if (toLower(menu[i].name) == toLower(name)) {
                cout << "\nMatagumpay na nakita ang produkto.\n" << endl;
                int choice;
                do { // mag aask na si program ano ung iuupdate
                    cout<< "Aling impormasyon ng "<< menu[i].name << " ang nais mong i-update?" << endl
                        << "1. I-update ang Presyo" << endl
                        << "2. I-update ang Dami" << endl
                        << "3. Bumalik" << endl
                        << "Ilagay ang iyong pinili: "; //input ng gagawin mo
                    cin >> choice;
                    switch (choice) {
                        case 1: {//maglalagay na ng bagong presyo
                            cout << "\nIlagay ang bagong presyo ng " << menu[i].name << ": ";
                            cin >> menu[i].price;
                            
                            /* rewriting na sa file ung specific product na gusto natin iupdate same case
                             sa lahat ng cases dito sa function nato, its either price or quantity lang */
                            ofstream file("../bakedgoodstracker/file/Menu.txt");
                            for (int i=0 ; i < menu.size(); ++i){
                                file << menu[i].name << "  " 
                                     << menu[i].price << "  " 
                                     << menu[i].quantity << endl;
                            }
                                file.close();

                            cout << "\nNa-update ang Presyo!\n" << endl;
                            found = true;
                            break;
                        }
                        case 2: {//maglalagay na sya ng bagong quantity
                            cout << "\nIlagay ang bagong dami ng " << menu[i].name << ": ";
                            cin >> menu[i].quantity;

                            loadOrder("pre");
                            
                            //check if may naka pre order sa product na yun after mag re stock
                            for (int j=0; j<order.size(); ++j) {
                                if (menu[i].name == order[j].productName && menu[i].quantity >= order[j].quantity){
                                    //automatically ibabawas ung na stock sa pre order and ilalagay na sya sa transaction records natin
                                    cout<<"\nMay pre-order ka sa produktong ito para kay customer "<< order[j].customer<<"! Awtomatikong ibabawas... \n" << endl;
                                    menu[i].quantity -= order[j].quantity;

                                    ofstream file("../bakedgoodstracker/file/Transaction.txt", ios::app);
                                        file << order[j].customer << "  " 
                                             << order[j].productName << "  " 
                                             << order[j].quantity << "  "
                                             << order[j].price << "  "
                                             << order[j].paid << "  "
                                             << order[j].change << "  "
                                             << order[j].date << endl;
                                    file.close();

                                    //tatanggalin na sya sa pre order files and irerewrite sa current pre order file
                                    order.erase(order.begin() + j);

                                    for (int k=0; k<order.size(); ++k){
                                        ofstream pfile("../bakedgoodstracker/file/Pre-orders.txt");
                                        pfile << order[k].customer << "  " 
                                             << order[k].productName << "  " 
                                             << order[k].quantity << "  "
                                             << order[k].price << "  "
                                             << order[k].paid << "  "
                                             << order[k].change << "  "
                                             << order[k].date << endl;
                                        file.close();

                                        // and pag na settle na un iuupdate na sa menu ung updated stock after nung pre order
                                        ofstream mfile("../bakedgoodstracker/file/Menu.txt");
                                        for (int l=0 ; l < menu.size(); ++l){
                                            mfile << menu[l].name << "  " 
                                                 << menu[l].price << "  " 
                                                 << menu[l].quantity << endl;
                                        }
                                        file.close();

                                        updated = true;

                                        cout<<"Ang bagong dami ng "<< menu[i].name << " ay " << menu[i].quantity << "!\n" << endl;
                                    }
                                }
                            }
                                    
                            if (!updated) {
                                 /* rewriting na sa file ung specific product na gusto natin iupdate same case
                                    sa lahat ng cases dito sa function nato, its either price or quantity lang */
                                    ofstream file("../bakedgoodstracker/file/Menu.txt");
                                        for (int i=0 ; i < menu.size(); ++i){
                                            file << menu[i].name << "  " 
                                                 << menu[i].price << "  " 
                                                 << menu[i].quantity << endl;
                                        }
                                    file.close();

                                    cout << "\nNa-update ang dami!\n" << endl;
                                    found = true;
                            }       
                            break;
                        }
                        case 3:
                            cout << endl;
                            break;
                        default:
                         cout << "Maling pinili. Pakisubukan muli." << endl;
                    }
                } while (choice !=3);
        } 
        if (found) {
            cout << "\nHindi natagpuan ang produkto.\n" << endl;
        }
    }
}

void viewTransactions() {
    loadOrder("trans"); //check and load muna ung current transactions sa vector
    cout<<endl;

    if (order.empty()) {
        cout << "Walang transaksyon sa kasulukuyan.\n" << endl;
    } else { //magshow show na sya if meron sa loob ng vector and may divider sya
        for(int i=0; i<order.size(); i++) {
            cout<<"Pangalan ng Customer: "<< order[i].customer << "\n" << endl;
            cout<<left<<setw(30)<<"PANGALAN NG PRODUKTO"
            <<right<<setw(0)<<"DAMI"
            <<right<<setw(30)<<"PETSA NG TRANSAKSYON"<<endl;
                            
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
}

void viewPreOrder() {
    cout<<endl;
    loadOrder("pre"); //loads ung mga na preorder na

    if (order.empty()) {
        cout << "Walang naka preorder sa kasalukuyan.\n" << endl;
    } else { //if merong current pre order, ipapakita rito
        for(int i=0; i<order.size(); i++) {
        cout<<"Pangalan ng Customer: "<< order[i].customer << "\n" << endl;
        cout<<left<<setw(30)<<"PANGALAN NG PRODUKTO"
            <<right<<setw(0)<<"DAMI"
            <<right<<setw(30)<<"PETSA NG PAGKUKUHA"<<endl;
                            
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
}

void viewCustomOrders() {
    loadOrder("custom"); //load lahat ng custom orders
    int number;
    int choice;
    
    if (order.empty()) {
        cout << "Walang custom na order sa kasalukuyan.\n" << endl;
    } else { //if true, lalabas lahat ng current pre order info 
        do{
            cout<<endl;
            for(int i=0; i<order.size(); i++) {
                cout<<"Custom Order No."<<i+1<<endl;
                cout<<"Pangalan ng Customer: "<< order[i].customer << "\n" << endl;
                cout<<left<<setw(30)<<"PANGALAN NG PRODUKTO"
                    <<right<<setw(0)<<"MENSAHE"
                    <<right<<setw(30)<<"KANDILA"<<endl;
                            
                cout<<setfill('-')<<setw(75)<<"-"<<endl;
	            cout<<setfill(' ');
    
                cout<<left<<setw(30)<< order[i].productName
                    <<right<<setw(2)<< order[i].writing
                    <<right<<setw(26)<< order[i].candle <<endl;
    
                cout<<setfill('-')<<setw(75)<<"-"<<endl;
	            cout<<setfill(' ');
                cout<<endl;
            }

            //magbibigay ng choice na magtanggal or babalik sa admin menu
            cout << "\n1. Magtanggal ng Custom Order" <<endl
                << "2. Bumalik" << endl
                << "Ilagay ang iyong pinili: ";
            cin>>choice;
            cin.ignore();

            switch(choice){
                case 1: {
                    cout<<"Ilagay ang Custom Order No. na Tatanggalin: ";
                    cin>>number;

                    order.erase(order.begin() + (number-1)); //para matanggal ung tatangalin sa vector

                    //ganun din sa file para ma delete sya permanently
                    ofstream dfile("../bakedgoodstracker/file/Custom Order.txt");
                    for (int i=0; i<order.size(); ++i){
                        dfile << order[i].customer << "  "
                              << order[i].productName << "  "
                              << order[i].writing << "  "
                              << order[i].candle << endl;
                    dfile.close();
                    }

                    cout<<"\nMatagumpay na Natanggal ang Custom Order\n" << endl;
                    break;
                }
                case 2:
                    break;
                default:
                    cout << "Maling pinili. Pakisubukan muli." << endl;
            }
        } while (choice != 2);
    }
}

void changeLogInfo() { 
    int choice;
    bool logError = true;
    loginCredentials newInfo;

    cout<<"\n================PAG-PAPALIT NG LOG INFO===================";
    cout<<"\nAling kredensyal ang nais mong palitan?"<<endl //bibigyan ng option si admin kung ano papaltan
        <<"1. Palitan ang Username"<<endl
        <<"2. Palitan ang Password"<<endl
        <<"3. Bumalik"<<endl
        <<"Ilagay ang iyong pinili: ";
        cin>>choice;
    
        loadAdmin(); //iloload ung current admin info

        switch (choice) {
            case 1:
                cout<<"\nIlagay ang iyong password para sa kumpirmasyon: "; //mandatory to sa lahat ng admin action regarding pag aadd pagreremove and pag palit ng info ng admin
                cin>>newInfo.password;
                for (int i=0; i < logInfo.size(); ++i){
                    if (newInfo.password == login.password && login.username == logInfo[i].username) { //check muna if may mag match
                        cout<<"Ilagay ang iyong bagong username: "; //papainputin 
                        cin>>logInfo[i].username;

                        login.username = logInfo[i].username; //eto na ung new pang greet sa admin after mag execute to

					//then iooverwrite ung buong txt file with ung bagong updated username
                    ofstream file("../bakedgoodstracker/file/Admin.txt"); 
                        for (int i=0 ; i < logInfo.size(); ++i){
                            file << logInfo[i].username << "  " 
                                 << logInfo[i].password << endl;
                        }
                    file.close();
                    cout<<"\nMatagumpay na Napalitan ang Username!\n"<<endl;

                    } else {
                        logError=false;
                    }
                if (!logError) {
                    cout<<"\nHindi tugma ang Password.\n"<<endl;
                }
            }
                break;
            case 2: //need ng confirmation ng current admin password
                cout<<"\nIlagay ang iyong lumang password para sa kumpirmasyon: ";
                cin>>newInfo.password;
                for (int i=0; i < logInfo.size(); ++i){
                    if (newInfo.password == login.password && login.username == logInfo[i].username) {
                        cout<<"Ilagay ang iyong bagong password: "; //and true ilalagay na ung bagong password
                        cin>>logInfo[i].password;

                        login.password = logInfo[i].password; //eto na ung gagamitin mong password for future changes
                        
                    // papaltan na sya at ilalagay na sya sa file 
                    ofstream file("../Admin.txt");
                        for (int i=0 ; i < logInfo.size(); ++i){
                            file << logInfo[i].username << "  " 
                                 << logInfo[i].password << endl;
                        }
                    file.close();
                    cout<<"\nMatagumpay na Napalitan ang Password!\n"<<endl;

                    } else {
                        logError=false;
                    }
                if (!logError) {
                    cout<<"\nHindi tugma ang Password.\n" <<endl;
                }
            }
                break;
            case 3:
                cout<<endl;
                break;
            default:
                 cout<<"\nMaling Pinili. Pakisubukan muli\n"<<endl;
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
        //menu para sa pagdagdag o pag tanggal ng mga admin
        cout<<"\n===========MAGDAGDAG O MAGTANGGAL NG ADMIN===========" << endl
            <<"1. Magdagdag ng Admin" << endl
            <<"2. Magtanggal ng Admin" << endl
            <<"3. Bumalik" << endl
            <<"Ilagay ang iyong pinili: ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Kumpirmahin ang Password: ";//need ng confirmation ng current admin
                cin>>veriPass.password;
                cout<<endl;

                    if (veriPass.password==login.password) { //checheck if may mag match sa current admin
                        cout<<"===========GUMAWA NG BAGONG ADMIN===========" << endl;
                        cout<<"Ilagay ang Username: ";
                        cin>>newUser.username;
            
                        do {
                            cout<<"Ilagay ang Password (Dapat hindi bababa sa 8 karakter): "; //need 8 characters minimun, uulit yan pag di nameet 
                            cin>>newUser.password;

				            //and then if ok na, isasama na sya sa file and sa current vector
                            if (newUser.password.size() == 8) {
                                ofstream file("../bakedgoodstracker/file/Admin.txt", ios::app);
                                    file << newUser.username << "  " 
                                         << newUser.password << endl;
                                file.close();

                                logInfo.push_back(newUser);
                                cout<<"\nMatagumpay na Naidagdag ang Admin!\n"<<endl;
                                isFound=true;
                            } else {
                                cout<<"\nMasyadong Maikli ang Password.\n"<<endl;
                            }
                        } while (newUser.password.size() < 8);
                    }
            if (!isFound){
                cout<<"\nHindi tugma ang Password.\n"<<endl;
            }
            break;

            case 2:
            cout<<"\nKumpirmahin ang Password: "; //need ulit confirmation ng current admin
            cin>>veriPass.password;
            cout<<endl;
                
                //ichecheck if may magmatch
                if (veriPass.password==login.password) {
                    cout<<"===========MAGTANGGAL NG ADMIN===========" << endl;
                    cout<<"Ilagay ang Username ng Admin na Tatanggalin: "; //ieenter na dito ung ireremove na admin
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
                    ofstream file("../bakedgoodstracker/file/Admin.txt");// and sa file ng admin mismo by rewriting
                    for (int i=0; i<logInfo.size(); i++){
                        file << logInfo[i].username << "  " 
                             << logInfo[i].password << endl;
                        file.close();
                    }
                    cout<<"\nMatagumpay na Natanggal ang Admin!\n"<<endl;
                }           
            
            if (!isFound){
                cout<<"\nHindi tugma ang Password.\n"<<endl;
            }
            break;

            case 3:
            break;

            default:
            cout << "Maling pinili. Pakisubukan muli." << endl;
        }   
    } while (choice != 3);
}
