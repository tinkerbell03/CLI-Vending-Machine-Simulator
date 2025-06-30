#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iomanip>
#include <cctype>

using namespace std;

struct Customer {
    string name;
    string mobileNumber;
    int customerId;
    double loyaltyPoints;
    int rating;
    string feedbackMessage;
};


struct Item {
    string name;
    double price;
    string id;
};

int currentCustomerId = 0;
vector<Customer> customers;
map<string, Item> items;
vector<Item> createItems() {
  vector<Item> items = {
    {"Vanila Flavored Yogurt drink", 160.00, "A1"}, {"Mango Flavored Yogurt drink ", 160.00, "A2"}, {"Mixed Berry Flavored Yogurt drink ", 160.00, "A3"},
    {"Strawberry milk ", 140.00, "A4"}, {"Vanila milk ", 140.00, "A5"}, {"Chocolate milk", 140.00, "B1"},
    {"Oreo milk ", 140.00, "B2"}, {"Set Yogurt", 80.00, "B3"}, {"Strawberry Yogurt ", 80.00, "B4"},
    {"Yogurt with jelly ", 120.00, "B5"}, {"Cheese", 560.00, "C1"}, {"Chirpy Chips Salted", 300.00, "C2"},
    {"Crunchy Wafer", 100.00, "C3"}, {"Carol cookies ", 100.00, "C4"}, {"Cadbury Chococake Cookies", 550.00, "C5"},
    {"Oats Biscuits", 400.00, "D1"}, {"Olo Strawberry Biscuits", 280.00, "D2"}, {"Stix Rolled Wafer", 120.00, "D3"},
    {"Milk Biscuits ", 300.00, "D4"}, {"Chick bits", 190.00, "D5"}, {"Oreo Biscuits", 420.00, "E1"},
    {"Onion Biscuits", 380.00, "E2"}, {"Dairy milk (small)", 250.00, "E3"}, {"Dairy milk (medium)", 550.00, "E4"},
    {"Ferrero Rocher", 1500.00, "E5"}, {"M &M large", 1200.00, "F1"}, {"Peanut Milk Choco", 120.00, "F2"},
    {"Kitkat Caramel", 700.00, "F3"}, {"Kitkat Dark", 650.00, "F4"}, {"Water Bottle (500ml)", 300.00, "F5"},
    {"Water Bottle (1 L)", 600.00, "G1"}, {"Vanila Donut", 280.00, "G2"}, {"Chocolate Donut", 300.00, "G3"},
    {"Strawberry Donut", 300.00, "G4"}, {"Iced tea (250ml)", 480.00, "G5"}, {"Iced coffee (250ml)", 500.00, "H1"},
    {"Latte milk coffee", 550.00, "H2"}, {"Nescafe", 150.00, "H3"}, {"Cassava Chips  salted", 165.00, "H4"},
    {"Cassava Chips Hot & Spicy", 165.00, "H5"}, {"Rancrisp Potato Chips", 330.00, "I1"}, {"Nuts & Pistachios", 750.00, "I2"},
    {"Almonds", 550.00, "I3"}, {"Fudge", 450.00, "I4"}, {"Coffee Cupcake", 400.00, "I5"},
    {"Ice cream cubes", 200.00, "J1"}, {"Necto 1L", 300.00, "J2"}, {"Cream Soda 1L", 300.00, "J3"},
    {"EGB 1L", 300.00, "J4"}, {"Pepsi (500ml)", 150.00, "J5"}
  };
  return items;
}

// Function to display items 
void displayItems(const vector<Item>& items) {
  cout << setw(10) << "ID" << setw(40) << "Item Name" << setw(30) << "Price" << endl;
  cout << "---------------------------------------------------------------------------------------------" << endl;

  for (const Item& item : items) {
    cout << setw(10) << item.id << setw(40) << item.name << setw(30)  << item.price  << endl;
  }
}

bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

bool isValidMobileNumber(const string& mobileNumber) {
    if (mobileNumber.length() != 10) {
        return false;
    }

    for (char c : mobileNumber) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}


void createCustomerProfile() {

    Customer newCustomer;
    bool isValid = false;

    // Get name 
    while (!isValid)
    {
      cout << "Enter your name: " << endl;
      cin >> newCustomer.name;
      if (!isValidName(newCustomer.name)) {
            cout << "Invalid name. Please enter letters only." << endl;
        } else {
            isValid = true;
        }
    }
    
    while (!isValid)
    {
      cout << "Enter your mobile number: " << endl;
      cin >> newCustomer.mobileNumber;
      if (!isValidName(newCustomer.mobileNumber)) {
            cout << "Invalid mobile number. Please enter 10 digits." << endl;
        } else {
            isValid = true;
        }
    }

    cout << "Enter your mobile number: ";
    cin >> newCustomer.mobileNumber;

    // Assign a unique ID
    newCustomer.customerId = customers.size() + 1;

    customers.push_back(newCustomer);

    cout << "Profile created successfully! Your customer ID is: " << newCustomer.customerId << endl;
}

void loadCustomerData() {
    ifstream infile("customers.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            Customer customer;
            stringstream save(line);
            getline(save, customer.name, ',');
            getline(save, customer.mobileNumber, ',');
            save >> customer.customerId;
            save >> customer.loyaltyPoints;
            customers.push_back(customer);
        }
        infile.close();
        //cout << "Customer data loaded successfully." << endl;
    } else {
        //cout << "Customer data file not found." << endl;
    }
}

void loadCustomerProfile() {
    string mobileNumber;
    cout << "Enter your mobile number: ";
    cin >> mobileNumber;

    bool found = false;
    for (Customer& customer : customers) {
        if (customer.mobileNumber == mobileNumber) {
            cout << "Welcome back, " << customer.name << "!" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer not found. Please create a new profile." << endl;
        createCustomerProfile();
    }
}

void saveCustomerData() {
  ofstream outfile("customers.txt");
  if (outfile.is_open()) {
    for (const Customer& customer : customers) {
      outfile << customer.name << "," << customer.mobileNumber << "," << customer.customerId << "," << customer.loyaltyPoints <<"," << customer.rating << "," << customer.feedbackMessage << endl;
    }
    outfile.close();
    //cout << "Customer data saved successfully." << endl;
  } else {
    cout << "Error saving customer data." << endl;
  }
}


void login() {
    string mobileNumber;
    bool isValid = false;

    do {
        cout << "Enter your mobile number (10 digits): ";
        cin >> mobileNumber;

        if (mobileNumber.length() == 10) {
            for (char c : mobileNumber) {
                if (!isdigit(c)) {
                    cout << "Invalid mobile number. Please enter only digits." << endl;
                    break;
                }
            }
            isValid = true;
        } else {
            cout << "Invalid mobile number. Please enter 10 digits." << endl;
        }
    } while (!isValid);

    bool found = false;
    for (int i = 0; i < customers.size(); ++i) {
        if (customers[i].mobileNumber == mobileNumber) {
            currentCustomerId = customers[i].customerId;
            cout << "Welcome back, " << customers[i].name << "!" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer not found. Please create a new profile." << endl;
        createCustomerProfile();
    }
}



void calculateLoyaltyPoints(Customer& customer, double total) {
  customer.loyaltyPoints += total * 0.01; 
}

void redeemPoints(Customer& customer, double& totalBill) {
  totalBill -= customer.loyaltyPoints;
  

  cout << "Updated total bill: LKR" << totalBill << endl;
  cout << "\nPayment method (card/cash): ";
      string paymentMethod;
      cin >> paymentMethod;
      saveCustomerData();
      
    
}

void takeOrder(const vector<Item>& items) {
  vector<Item> order;
  string itemId;

  cout << "Enter item IDs to add to your order (enter 'done' to finish):\n";
  while (true) {
    cin >> itemId;
    if (itemId == "done") {
      break;
    }

    bool found = false;
    for (const Item& item : items) {
      if (item.id == itemId) {
        order.push_back(item);
        found = true;
        break;
      }
    }

    if (!found) {
      cout << "Item ID not found. Please try again.\n";
    }
  }

  // Confirm order
  cout << "\nYour order:\n";
  double total = 0.0;
  for (const Item& item : order) {
    cout << "- " << item.name << ": LKR" << item.price << endl;
    total += item.price;
  }
  cout <<  "- "<<"Total: LKR" << total << endl;
  // Assign total to the reference argument
  double totalBill = total;

  cout << "Confirm your order? (yes/no): ";
  string confirmation;
  cin >> confirmation;

  if (confirmation == "yes") {
    // Process payment
    double totalBill = total;

    // Calculate loyalty points
    calculateLoyaltyPoints(customers[currentCustomerId - 1], totalBill);
    

    // Discount
    cout << "\nYou have a discount of LKR" << customers[currentCustomerId - 1].loyaltyPoints << endl;
    redeemPoints(customers[currentCustomerId - 1], totalBill);

    cout << "\nEZ Vendding\n";
    cout << "\nBILL:\n";
    double total = 0.0;
    cout << "----------------------------------------------" << endl;
    for (const Item& item : order) {
    
    cout << setw(30) << item.name << ": LKR" << item.price << endl;
    total += item.price;
  }
    cout << "----------------------------------------------" << endl;
    cout << "Total: LKR" << totalBill << endl;
    cout << "Thank you now come again!\n";
  } else {
    cout << "Order canceled.\n";
  }
}

void getFeedback() {
    string feedbackChoice;
    cout << "\nWould you like to provide feedback about your experience? (yes/no): ";
    cin >> feedbackChoice;

    if (feedbackChoice == "yes") {
        int rating;
        cout << "\nPlease rate our service from 1 (Terrible) to 5 (Great): ";
        cin >> rating;

        string feedbackMessage;
        cout << "\nThank you for your feedback! We appreciate it." << endl;

        cout << "Would you like to leave a detailed comment? (yes/no): ";
        cin >> feedbackChoice;
        if (feedbackChoice == "yes") {
            cout << "Enter your feedback: ";
            getline(cin, feedbackMessage); 

        }

        // Assign rating and feedback to the current customer
        customers[currentCustomerId - 1].rating = rating;
        customers[currentCustomerId - 1].feedbackMessage = feedbackMessage;
        cout << "\nThank you for your business! We hope to see you again soon." << endl;
    } else {
        cout << "\nThank you for your business! We hope to see you again soon." << endl;
    }
}

int main() {
    loadCustomerData();
    login();
    vector<Item> allItems = createItems();
    displayItems(allItems);
    takeOrder(allItems);
    getFeedback();
    saveCustomerData();
    return 0;
}