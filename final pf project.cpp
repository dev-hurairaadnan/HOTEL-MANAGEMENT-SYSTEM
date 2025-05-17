
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;


void cancel_booking();
void cancel_booking2(const string& cnic_to_cancel);
void sign_up(string &name, string &password);
bool check(string &username, string &password);
void login_page(string &name, string &password);
void front_page(string &name, string &password);
bool room_availibility(string &room_type, string &room_num);
void store_guest_details(string& sirName, string& cnic, string& phoneNo, string& checkInDate, string& checkOutDate, string &room_num, string &price);
void input_guest_details();
void guest_data_display();
void room_status_display();
void display_data_base();
string trim(const string& str);
void front_office();
void menu();
void addNewDishes();
void change_quantity();
bool isRoomOccupied(string& room_no);
bool isDishAvailable(string& dishName, int quantity, double& price, int& availableQuantity);
void updateMenuFile(string& dishName, int newQuantity);
void recordOrder(string& room_no, string& dishName, int quantity, double totalExpense);
void take_order();
void kitchen();
void gym_registeration();
void gym_checkout();
void GYM();
bool change_status_pool(string& timeb, string& room_number);
void prebook();
bool check_pool_is_booked(string& room_number);
void check_in_pool(string& room_number);
void check_out_pool(string& room_number);
void display_pool_status_file();
void swimming_pool();
bool isFileAccessible(const string& file_name);
void checkout();
void show_main_menu() {
    cout << "----------- Main Menu -----------" << endl;
    cout << "1. Front Office (Room Booking & Check-Ins)" << endl;
    cout << "2. Kitchen (Food Orders and Charges)" << endl;
 cout << "3. GYM" << endl;
    cout << "4. Swimming Pool (Charges for Pool Usage)" << endl;
        cout << "5. CHECK-OUT" << endl;
    cout << "6. Log-out" << endl;
    int choice;
    cout << "Enter your choice: ";
    cin>>choice;
     cout << "You selected option " << choice << "." << endl;
     switch (choice) {
            case 1:
                front_office();
                break;
            case 2:
                kitchen();
                break;
            case 3:
            GYM();
                break;
            case 4:
                swimming_pool();
                break;
            case 5:
                checkout();
            case 6:
                cout << "Exiting system. Goodbye!" << endl;
                break;



}
}


void cancel_booking2( string& cnic_to_cancel) {
    string sirName, cnic, phoneNo, checkInDate, checkOutDate, room_num, price;
    bool found = false;

    cout << "Canceling booking for CNIC: " << cnic_to_cancel << endl;


    ifstream guest_file("guest_data.txt");
    if (!guest_file) {
        cout << "Could not open the guest data file." << endl;
        return;
    }

    vector<string> guest_lines;
    while (guest_file >> sirName >> cnic >> phoneNo >> checkInDate >> checkOutDate >> price >> room_num) {
        if (cnic == cnic_to_cancel) {
            found = true;
            cout << "Booking found for CNIC: " << cnic_to_cancel << endl;
            continue;
        } else {
            guest_lines.push_back(sirName + " " + cnic + " " + phoneNo + " " + checkInDate + " " + checkOutDate + " " + price + " " + room_num);
        }
    }
    guest_file.close();

    if (!found) {
        cout << "No booking found for CNIC: " << cnic_to_cancel << endl;
        return;
    }

    // Write updated guest data back (removes the canceled booking)
    ofstream guest_file_out("guest_data.txt");
    if (!guest_file_out) {
        cout << "Could not open the guest data file for writing." << endl;
        return;
    }
    for (const string& data : guest_lines) {
        guest_file_out << data << endl;
    }
    guest_file_out.close();


    ifstream room_file("room_status.txt");
    if (!room_file) {
        cout << "Could not open the room status file." << endl;
        return;
    }

    vector<string> room_lines;
    string room_type, room_number, room_status;
    while (room_file >> room_type >> room_number >> room_status) {
        if (room_number == room_num) {
            room_status = "empty";
        }
        room_lines.push_back(room_type + " " + room_number + " " + room_status);
    }
    room_file.close();


    ofstream room_file_out("room_status.txt");
    if (!room_file_out) {
        cout << "Could not open the room status file for writing." << endl;
        return;
    }
    for (const string& line : room_lines) {
        room_file_out << line << endl;
    }
    room_file_out.close();

    cout << "Booking canceled and room status updated to empty successfully!" << endl;
}
void sign_up(string &name,string &password){
 cout<<"-----------Hotel Management System-------------"<<endl;
cout<<"-----------Sign up page-------------"<<endl;
    cout<<"Enter user name(eg ):"<<endl;
    cin>>name;
    cout<<"Enter New password:"<<endl;
cin>>password;

    ofstream input("login.txt",ios::app);

  input << name << " " << password << endl;
    input.close();

    cout << "Sign Up Successful!" << endl;
}
bool check(string &username,  string &password)
{


string stored_name,stored_password;
    ifstream input("login.txt");
if(!input)
{
    cout<<"Error:Data file can not be open"<<endl;
    return false;
}


    while(input>>stored_name>>stored_password)               //here the loop will run until all values stored in variable and check if match or not
    {
        if(stored_name==username&&stored_password==password){
            return true;

        }


}

        {          input.close();

          return false;
  }
}
void login_page(string &name ,string &password){
    cout<<"-----------Hotel Management System-------------"<<endl;   //login first interface
    cout<<"------------------LOGIN PAGE------------------"<<endl;
     cout<<"Enter User-Name:"<<endl;
    cin>>name;
    cout<<"Enter password:"<<endl;
    cin>>password;

}
void front_page(string &name,string &password){
    cout<<"-----------Hotel Management System-------------"<<endl;
    cout<<"1.login "<<endl;
    cout<<"2.sign up"<<endl;
    int choice;
    cout<<"Enter choice:"<<endl;
    cin>>choice;
    switch(choice)

{



    case 1:
    login_page(name ,password);
    break;
    case 2:
    sign_up(name,password);
    break;
}
}


bool room_availibility( string &room_type,string &room_num){
    string room_types,room_number,status;
    bool found=false;
      vector<string> lines;
ifstream in("room_status.txt");
    if (!in) {
        cout << "Error: Unable to open file for reading!" << endl;
        return false;
    }
 while (in >> room_types >> room_number >> status) {



if (room_type == room_types && status == "empty"&&!found) {

    lines.push_back(room_types + " " + room_number + " " + "occupied");
    room_num=room_number;
    found=true;

    }
    else
    {
        lines.push_back(room_types + " " + room_number + " " + status);
    }
 }
if(!found)
{
    cout<<"Sorry!No room is Available "<<room_type<<endl;
    return false;
}

 in.close();
    ofstream inpu("room_status.txt");
    if(!inpu)
    { cout << "Error: Unable to open file for reading!" << endl;
        return false;

    }

    for(int i=0;i<lines.size();i=i+1)
    {
        inpu<<lines[i]<<endl;
    }
 inpu.close();

return true;
}

void store_guest_details( string& sirName,  string& cnic,  string& phoneNo,  string& checkInDate,  string& checkOutDate,string &room_num,string &price)
                          {
cout<<"Your room no is:" << room_num << endl;

 ofstream file("guest_data.txt" ,ios::app);
 file << sirName << " " << cnic << " " << phoneNo << " " << checkInDate << " " << checkOutDate<<" "<<price<<" "<<room_num<<"\n";
    file.close();
}
void input_guest_details(){
    string sirName, cnic, phoneNo, checkInDate, checkOutDate,room_type,room_num,price;
     cout<<"-----------Hotel Management System-------------"<<endl;
cout<<"Enter type of room (sweet,single,double):"<<endl;
cin>>room_type;
if( room_availibility(room_type,room_num))
{


    cout << "Enter Guest's Sir Name (e.g., asim.irshad): ";
cin>>sirName;
    cout << "Enter Guest's CNIC: ";
cin>> cnic;
    cout << "Enter Guest's Phone Number: ";
cin>> phoneNo;
    cout << "Enter Check-In Date (YYYY-MM-DD): ";
cin>>checkInDate;
    cout << "Enter Check-Out Date (YYYY-MM-DD): ";
cin>>checkOutDate;
cout<<"Enter Price:";
cin>>price;
    store_guest_details( sirName, cnic, phoneNo, checkInDate, checkOutDate,room_num,price);
    cout<<"Data stored successfully!!"<<endl;


    }
    else
    {
        cout<<"not available"<<endl;
    }
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}
void guest_data_display(){
    string sirName,cnic,phoneNo,checkInDate,checkOutDate,room_num,price;
    fstream file("guest_data.txt");
        cout<<"Name\tCNIC\tPhone-NO\tCheck-InDate\tCheck-OutDate\tprice\troom-no"<<endl;
        while(file>>sirName>>cnic>>phoneNo>>checkInDate>>checkOutDate>>price>>room_num)
        {
            cout<<sirName<<"\t";
            cout<<cnic<<"\t";
            cout<<phoneNo<<"\t";
        cout<<checkInDate<<"\t";
            cout<<checkOutDate<<"\t";
            cout<<price<<"\t";
            cout<<room_num<<"\t"<<endl;
        }
    file.close();
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}
void room_status_display(){
string room_type,room_number,room_status;
fstream in("room_status.txt");
while(in>>room_type>>room_number>>room_status)
{
    cout<<room_type<<"\t"
    <<room_number<<"\t"
    <<room_status<<"\t"<<endl;
}
in.close();
cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}
void display_data_base(){
     cout<<"-----------Hotel Management System-------------"<<endl;

    cout<<"1.Guest Details"<<endl;
    cout<<"2.Room status"<<endl;
    cout<<"3.log-out"<<endl;
    int choice;
    cout<<"Enter choice:"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        guest_data_display();
        break;
    case 2:
         room_status_display();
         break;
    case 3:
        break;


    }
}
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos) ? "" : str.substr(first, (last - first + 1));
}

void cancel_booking() {
    string cnic_to_cancel, sirName, cnic, phoneNo, checkInDate, checkOutDate, room_num, price;
    bool found = false;

    cout << "Enter the CNIC of the guest whose booking you want to cancel: ";
    cin >> cnic_to_cancel;

    // Read guest data
    ifstream guest_file("guest_data.txt");
    if (!guest_file) {
        cout << "Could not open the guest data file." << endl;
        return;
    }

    vector<string> guest_lines;
    while (guest_file >> sirName >> cnic >> phoneNo >> checkInDate >> checkOutDate >> price >> room_num) {
        if (cnic == cnic_to_cancel) {
            found = true;
            cout << "Booking found for CNIC: " << cnic_to_cancel << endl;
            continue;
        } else {
            guest_lines.push_back(sirName + " " + cnic + " " + phoneNo + " " + checkInDate + " " + checkOutDate + " " + price + " " + room_num);
        }
    }
    guest_file.close();

    if (!found) {
        cout << "No booking found for CNIC: " << cnic_to_cancel << endl;
        return;
    }

    // Write updated guest data back
    ofstream guest_file_out("guest_data.txt");
    if (!guest_file_out) {
        cout << "Could not open the guest data file for writing." << endl;
        return;
    }
    for ( string& data : guest_lines) {
        guest_file_out << data << endl;
    }
    guest_file_out.close();

    // Update the room status
    ifstream room_file("room_status.txt");
    if (!room_file) {
        cout << "Could not open the room status file." << endl;
        return;
    }

    vector<string> room_lines;
    string room_type, room_number, room_status;
    while (room_file >> room_type >> room_number >> room_status) {
        string trimmed_room_num = trim(room_num);
        string trimmed_room_number = trim(room_number);

        if (trimmed_room_number == trimmed_room_num) {
            room_status = "empty";

        }
        room_lines.push_back(room_type + " " + room_number + " " + room_status);
    }
    room_file.close();

    ofstream room_file_out("room_status.txt");
    if (!room_file_out) {
        cout << "Could not open the room status file for writing." << endl;
        return;
    }
    for (const string& line : room_lines) {
        room_file_out << line << endl;
    }
    room_file_out.close();

    cout << "Booking canceled and room status updated successfully!" << endl;
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}


void front_office() {
    cout << "-----------Front Office section-----------" << endl;   //front-office
    cout << "1.Here you can manage room bookings and check-ins/check-outs." << endl;
    cout<<"2.Cancel Booking"<<endl;
    cout<<"3.Display Inventery"<<endl;
    cout<<"4.Log-out "<<endl;
    int choice;
    cout<<"Enter choice:"<<endl;
    cin>>choice;
    switch(choice)
    {

    case 1:
    input_guest_details();
    break;
    case 2:
       cancel_booking();


    case 3:
        display_data_base();
        break;
    case 4:

        break;
    }
}

void menu(){
    string dish_name,dish_price,dish_quantity;

    ifstream file("menu.txt");
      if (!file) {
        cout << " Could not open the file." <<endl;
        return;
    }

    cout << "Dish Name\tPrice\tQuantity\n";
    while(file>>dish_name>>dish_price>>dish_quantity)
    {
        cout << dish_name << "\t\t" << dish_price << "\t" << dish_quantity << endl;
    }
file.close();
cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice1;
    cout<<"Enter your choice:";
    cin>>choice1;
    switch(choice1)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}

void addNewDishes() {
    int choice;
    ofstream file("menu.txt", ios::app);

    if (!file) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    do {
        string dishName;
        string dishPrice;
        string dishQuantity;


        cout << "Enter the name of the dish: ";
        cin >>dishName;

        cout << "Enter the price of the dish: ";
        cin >> dishPrice;

        cout << "Enter the quantity of the dish: ";
        cin >> dishQuantity;


        file << dishName << " " << dishPrice << " " << dishQuantity << endl;
        cout << "Dish added successfully!\n";

        cout << "Do you want to add another dish: ";
                cout<<"Yes"<<endl;
                cout<<"No"<<endl;
                cin >> choice;

    } while (choice ==1);
    if(choice==2)
    {
        cout<<"You do not want to add another dish:"<<endl;
    }
    file.close();
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice1;
    cout<<"Enter your choice:";
    cin>>choice1;
    switch(choice1)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}

void change_quantity()
{
    string dishName,dishPrice,dishQuantity;
    bool dishFound;

string targetDish;
string new_quantity;

cout<<"Enter the name of dish:"<<endl;
cin>>targetDish;

cout<<"Enter New Quantity:"<<endl;
cin>>new_quantity;
vector <string> filein;

ifstream file("menu.txt");
    if (!file) {
        cout << "Could not open the file." << endl;
        return;
    }

    string line;
    while (file>> dishName >> dishPrice >> dishQuantity) {



        if (dishName == targetDish) {
            dishFound = true;
            filein.push_back(dishName + " " + dishPrice + " " +new_quantity);
        } else {
            filein.push_back(dishName + " " + dishPrice + " " +dishQuantity);
        }
    }

    file.close();

    if (!dishFound) {
        cout << "Dish not found in the menu.\n";
        return;
    }


    ofstream Fileinn("menu.txt");
    if (!Fileinn) {
        cout << "Error: Could not open the file for writing." << endl;
        return;
    }
for (int i = 0; i < filein.size(); i++) {
    Fileinn << filein[i] << endl;
}

    Fileinn.close();
    cout << "Quantity of the dish has been updated successfully.\n";
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }


}

bool isRoomOccupied( string& room_no) {
    ifstream roomFile("room_status.txt");
    if (!roomFile) {
        cout << "Error: Could not open room_status.txt." << endl;
        return false;
    }

    string type, no, status;
    while (roomFile >> type >> no >> status) {
        if (no == room_no && status == "occupied") {
            return true;
        }
    }

    return false;
}


bool isDishAvailable( string& dishName, int quantity, double& price, int& availableQuantity) {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Error: Could not open menu.txt." << endl;
        return false;
    }

    string menuDish;
    while (menuFile >> menuDish >> price >> availableQuantity) {
        if (menuDish == dishName) {
            return availableQuantity >= quantity;
        }
    }

    return false;
}


void updateMenuFile( string& dishName, int newQuantity) {
    ifstream menuFile("menu.txt");
    vector<string> updatedMenu;
    string menuDish;
    double price;
    int availableQuantity;

    while (menuFile >> menuDish >> price >> availableQuantity) {
        if (menuDish == dishName) {
            updatedMenu.push_back(menuDish + " " + to_string(price) + " " + to_string(newQuantity));
        } else {
            updatedMenu.push_back(menuDish + " " + to_string(price) + " " + to_string(availableQuantity));
        }
    }

    menuFile.close();

    ofstream menuOutFile("menu.txt");
    for (const string& line : updatedMenu) {
        menuOutFile << line << endl;
    }
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}


void recordOrder( string& room_no,  string& dishName, int quantity, double totalExpense) {
    ofstream orderFile("orders.txt", ios::app);
    if (!orderFile) {
        cout << "Error: Could not open orders.txt." << endl;
        return;
    }
    orderFile << room_no << " " << dishName << " " << quantity << " " << totalExpense << endl;
}


void take_order() {
    string dishName, room_no;
    int quantity;
    double totalExpense = 0;

    cout << "Enter the room number: ";
    cin >> room_no;

    if (!isRoomOccupied(room_no)) {
        cout << "Room is not booked!" << endl;
        cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
        return;
    }
    menu();

    cout << "Enter the name of the dish: ";
    cin >> dishName;
    cout << "Enter the quantity: ";
    cin >> quantity;

    double price;
    int availableQuantity;
    if (!isDishAvailable(dishName, quantity, price, availableQuantity)) {
        cout << "Dish not found in the menu or insufficient quantity available." << endl;
        return;
    }

    availableQuantity -= quantity;
    totalExpense = price * quantity;
    updateMenuFile(dishName, availableQuantity);
    recordOrder(room_no, dishName, quantity, totalExpense);

    cout << "Order placed successfully! Total expense: Rs. " << totalExpense << endl;

cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }

}
void kitchen() {
    cout << "-----------Kitchen section-----------" << endl;  //kitchen
    cout << "Here you can manage food orders and charges." << endl;
    cout<<"1.Take Order"<<endl;
    cout<<"2.View Kitchen Inventory"<<endl;
    cout<<"3.Add New Things to Menu"<<endl;
    cout<<"4.Update Quantity in Menu:"<<endl;
    cout<<"5.Log-out"<<endl;

int choice;
cout<<"Enter your choice"<<endl;
cin>>choice;
switch(choice)
{



case 1:
     take_order();
      break;


case 2:


    menu();
  break;

case 3:
          addNewDishes();

    break;

case 4:
             change_quantity();

      break;

case 5:
    break;


}
}
void gym_registeration()
{
    ofstream file("gym.txt",ios::app);
    string room_no,check_in;
    int peson_number,price;
    cout<<"Enter Room-no"<<endl;
    cin>>room_no;
 if (!isRoomOccupied(room_no)) {
        cout << "Room is not booked!" << endl;
        cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
        return;
    }
    cout<<"Enter no of person that use gym:"<<endl;
    cin>>peson_number;
    cout<<"Enter Check-in Time:"<<endl;
    cin>>check_in;
    price=500*peson_number;
    file<<room_no<<" "<<peson_number<<" "<<check_in<<" "<<price<<endl;
    cout<<"Your registeration for gym is completed "<<endl;

    file.close();
cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }

}
void gym_checkout()
{
    string room_no, check_in, roomno, check_out;
    int person_number, price;
    bool found = false;

    cout << "Enter Room no:" << endl;
    cin >> roomno;

    ifstream inputFile("gym.txt");
    ofstream tempFile("temp.txt", ios::app);

    if (!inputFile || !tempFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    while (inputFile >> room_no >> person_number >> check_in >> price) {
        if (roomno == room_no) {
            cout << "Enter time of check-out:" << endl;
            cin >> check_out;


            tempFile << room_no << " " << person_number << " " << check_in << " "<< price << " " << check_out << endl;
            found = true;
        }
    }

    inputFile.close();
    tempFile.close();


    remove("gym.txt");
    rename("temp.txt", "gym.txt");

    if (!found) {
        cout << "Room not found!" << endl;
    } else {
        cout << "Check-out time updated successfully." << endl;
    }
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}


void GYM() {
    cout << "-----------GYM section-----------" << endl;
    cout << "Here you can manage GYM services and charges." << endl;
    cout<<" 1.registration"<<endl;
    cout<<"2.Check-out"<<endl;
    cout<<"3.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:"<<endl;
    cin>>choice;

    switch(choice)
    {
    case 1:
     gym_registeration();
     break;
    case 2:
        gym_checkout();
        break;
    case 3:
        cout<<"logging out ..........."<<endl;
        break;

    }
}

bool change_status_pool(string& timeb, string& room_number) {
    string slot_stored, time, status, price;
    bool found = false;
    vector<string> lines;

    ifstream in("pool status.txt");
    if (!in) {
        cout << "Error: Unable to open file for reading!" << endl;
        return false;
    }

    while (in >> slot_stored >> time >> price >> status) {
        string trimmed_room_number = trim(room_number); // Assuming trim is a function to remove leading/trailing spaces
        if (timeb == time && status == "not-booked") {
            lines.push_back(slot_stored + " " + time + " " + trimmed_room_number + " booked");
            found = true;
        } else {
            lines.push_back(slot_stored + " " + time + " " + price + " " + status);
        }
    }

    in.close();

    if (!found) {
        cout << "Sorry! The selected slot is unavailable." << endl;
        return false;
    }

    ofstream inpu("pool status.txt");
    if (!inpu) {
        cout << "Error: Unable to open file for writing!" << endl;
        return false;
    }

    for (const auto& line : lines) {
        inpu << line << endl;
    }

    inpu.close();
    return true;
}

void prebook() {
    string room_no, time_slot;

    cout << "Enter the room number: ";
    cin >> room_no;

    if (!isRoomOccupied(room_no)) {
        cout << "Room is not booked!" << endl;
        return;
    }

    cout << "Enter the desired time slot (e.g. 4:00): ";
    cin >> time_slot;

    if (!change_status_pool(time_slot, room_no)) {
            cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }

    }


    cout<<"you have booked the slot!!"<<endl;
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }

}

bool check_pool_is_booked( string& room_number) {
    string slot, time, status, room_no;
    ifstream file("pool status.txt");

    if (!file) {
        cout << "Error: Unable to open file for reading!" << endl;
        return false;
    }

    while (file >> slot >> time >> room_no >> status) {

        if (room_number == room_no && status == "booked") {
            file.close();
            return true;
        }
    }

    file.close();
                return false;


}

void check_in_pool(string& room_number) {
    string check_in_time;
    int price = 500;

    if (!check_pool_is_booked(room_number)) {
        cout << "The room has not booked a pool slot!" << endl;
        return;
    }

    cout << "Enter check-in time (e.g., 4:00): ";
    cin >> check_in_time;

    ofstream file("pool_database.txt", ios::app);
    if (!file) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }

    file << room_number << " " << price << " " << check_in_time << endl;
    file.close();
    cout << "Room " << room_number << " checked in successfully!" << endl;
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}

void check_out_pool(string& room_number) {
    string slot, time, status, room_no;
    vector<string> lines;
    bool found=false;

    ifstream file("pool status.txt");
    if (!file) {
        cout << "Error: Unable to open file for reading!" << endl;
        return;
    }

    while (file >> slot >> time >> room_no >>status) {
        if (room_no == room_number && status == "booked") {
            lines.push_back(slot + " " + time + " "+ "000"+" not-booked ");
            found=true;
        } else {
            lines.push_back(slot + " " + time + " " + room_no+" "+ status  );
        }
    }

    file.close();

    if (found) {
        ofstream file_out("pool status.txt");
        if (!file_out) {
            cout << "Error: Unable to open file for writing!" << endl;
            return;
        }

        // Using an index-based loop to write lines back to the file
        for (int i = 0; i < lines.size(); ++i) {
            file_out << lines[i] << endl; // Write each line back to the file
        }

        file_out.close(); // Close the output file
        cout << "Room " << room_number << " checked out and pool slot marked as not-booked." << endl;
        cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
    }
     else {
        cout << "No booking found for room " << room_number << "." << endl;
    }
}
void display_pool_status_file() {
    string slot, time, status, room_no;
    ifstream file("pool status.txt");
    cout << "SLOT\tTIME\tROOM-NO\tSTATUS" << endl;

    while (file >> slot >> time >> room_no >> status) {
        cout << slot << "\t" << time << "\t" << room_no << "\t" << status << endl;
    }

    file.close();
    cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }
}

void swimming_pool() {
    cout << "-----------Swimming Pool section-----------" << endl;  //swimming pool
    cout << "Here you can manage charges and booking for pool usage." << endl;
    cout<<"1.Pre-booking"<<endl;
    cout<<"2.Check-in"<<endl;
    cout<<"3.Check-out"<<endl;
    cout<<"4.Display pool status file"<<endl;
    int choice;
    cout<<"Enter your choice:"<<endl;
    cin>>choice;

  string room_number;
   switch(choice)
   {


   case 1:
        prebook();
       break;
   case 2:
         cout << "Enter the room number: ";
    cin >> room_number;

       check_in_pool( room_number);
       break;
       case 3:
           cout << "Enter the room number: ";
    cin >> room_number;

            check_out_pool(room_number);
     break;
     case 4:
         display_pool_status_file();

    break;
   }
}



bool isFileAccessible(const string& file_name) {
    ifstream file(file_name);
    return file.is_open();
}

void checkout() {
    string room_no;
    double room_price = 0, food_expenses = 0, gym_expenses = 0, pool_expenses = 0, total_expenses = 0;

    cout << "Enter the room number: ";
    cin >> room_no;

    if (!isRoomOccupied(room_no)) {
        cout << "Room is not booked!" << endl;
        return;
    }

    // Check if the files are accessible before opening
    if (!isFileAccessible("guest_data.txt")) {
        cout << "Error: guest_data.txt not found or unable to open!" << endl;
        return;
    }

    ifstream guest_file("guest_data.txt");
    string sirName, cnic, phoneNo, checkInDate, checkOutDate, room_num;
    double temp_price;
    if (guest_file.is_open()) {
        while (guest_file >> sirName >> cnic >> phoneNo >> checkInDate >> checkOutDate >> temp_price >> room_num) {
            if (room_num == room_no) {
                room_price = temp_price;
                break;
            }
        }
        guest_file.close();
    } else {
        cout << "Error: Unable to open guest data file!" << endl;
        return;
    }


    if (!isFileAccessible("orders.txt")) {
        cout << "Error: order_data.txt not found or unable to open!" << endl;
        return;
    }

    ifstream order_file("orders.txt");
    string temp_item, order_room_no;
    double temp_item_price;
    if (order_file.is_open()) {
        while (order_file >> order_room_no >> temp_item >> temp_item_price) {
            if (order_room_no == room_no) {
                food_expenses += temp_item_price;
            }
        }
        order_file.close();
    } else {
        cout << "Error: Unable to open order data file!" << endl;
        return;
    }


    if (!isFileAccessible("gym.txt")) {
        cout << "Error: gym_data.txt not found or unable to open!" << endl;
        return;
    }

    ifstream gym_file("gym.txt");
    string person_number, check_in, gym_room_no;
    double temp_gym_expense;
    if (gym_file. is_open()) {
        while (gym_file >> gym_room_no >> person_number >> check_in >> temp_gym_expense) {
            if (gym_room_no == room_no) {
                gym_expenses = temp_gym_expense;
                break;
            }
        }
        gym_file.close();
    } else {
        cout << "Error: Unable to open gym data file!" << endl;
        return;
    }


    if (!isFileAccessible("pool_database.txt")) {
        cout << "Error: pool_data.txt not found or unable to open!" << endl;
        return;
    }

    ifstream pool_file("pool_database.txt ");
    string pool_room_no;
    double temp_pool_expense;
    if (pool_file.is_open()) {
        while (pool_file >> pool_room_no >> temp_pool_expense) {
            if (pool_room_no == room_no) {
                pool_expenses = temp_pool_expense;
                break;
            }
        }
        pool_file.close();
    } else {
        cout << "Error: Unable to open pool data file!" << endl;
        return;
    }

    total_expenses = room_price + food_expenses + gym_expenses + pool_expenses;

    cout << "-----------Bill-----------" << endl;
    cout << "Room Price: " << room_price << endl;
    cout << "Food Expense: " << food_expenses << endl;
    cout << "Gym Expense: " << gym_expenses << endl;
    cout << "Swimming Pool Expense: " << pool_expenses << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Total: " << total_expenses << endl;
 cancel_booking2( cnic);
      cout<<"Bill is genrerated and room status is alo changed to empty";
      cout<<"1.Main menu"<<endl;
    cout<<"2.Log-out"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        show_main_menu();
        break;
        case 2:
            cout<<"logging out"<<endl;
            return;
    }

}


int main()
{
       string name,password;

  front_page(name,password);

    if (check(name,password))
    {
        cout<< "Login successful!" <<endl; // call chek function

    }
    else

    {
      cout<<"Invalid username or password"<<endl;
      return 0;


    }

show_main_menu();


return 0;
}
