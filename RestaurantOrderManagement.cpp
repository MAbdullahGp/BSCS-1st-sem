#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct MenuItem {
    int id;
    string name;
    double price;
    string description;
};

struct Table {
    int tableNumber;
    bool isAvailable;
    int capacity;
};

struct Order {
    int orderId;
    int tableNumber;
    vector<pair<int, int>> itemQuantities;
    double totalAmount;
};

struct Feedback {
    int tableNumber;
    string comments;
    int rating;
};

void adminPanel(vector<MenuItem>& menu);
void customerSide(vector<Table>& tables, vector<MenuItem>& menu, vector<Order>& orders, vector<Feedback>& feedbacks);
void addMenuItem(vector<MenuItem>& menu);
void updateMenuItem(vector<MenuItem>& menu);
void removeMenuItem(vector<MenuItem>& menu);
void displayMenu(const vector<MenuItem>& menu);
void displayTables(const vector<Table>& tables);
void reserveTable(vector<Table>& tables);
void placeOrder(vector<Order>& orders, const vector<MenuItem>& menu);
void processPayment(vector<Order>& orders);
void leaveFeedback(vector<Feedback>& feedbacks);
void viewFeedback(const vector<Feedback>& feedbacks);
void saveOrdersToFile(const vector<Order>& orders);
void loadOrdersFromFile(vector<Order>& orders);

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "password";

int main() {
    vector<Table> tables = {{1, true, 4}, {2, true, 4}, {3, true, 6}, {4, true, 2}};
    vector<MenuItem> menu = {{1, "Pizza", 12.99, "Cheese and tomato"}, 
                             {2, "Pasta", 8.99, "Creamy Alfredo sauce"},
                             {3, "Burger", 9.49, "Beef patty with fries"},
                             {4, "Salad", 6.99, "Fresh vegetables"}};
    vector<Order> orders;
    vector<Feedback> feedbacks;

    loadOrdersFromFile(orders);

    int choice;
    do {
        cout << "\n--- Welcome to the Restaurant Management System ---\n";
        cout << "1. Admin Panel\n";
        cout << "2. Customer Side\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                adminPanel(menu);
                break;
            case 2:
                customerSide(tables, menu, orders, feedbacks);
                break;
            case 3:
                cout << "Exiting the system. Goodbye!\n";
                saveOrdersToFile(orders);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

void adminPanel(vector<MenuItem>& menu) {
    string username, password;
    cout << "\n--- Admin Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        int choice;
        do {
            cout << "\n--- Admin Panel ---\n";
            cout << "1. Add Menu Item\n";
            cout << "2. Update Menu Item\n";
            cout << "3. Remove Menu Item\n";
            cout << "4. View Menu\n";
            cout << "5. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addMenuItem(menu);
                    break;
                case 2:
                    updateMenuItem(menu);
                    break;
                case 3:
                    removeMenuItem(menu);
                    break;
                case 4:
                    displayMenu(menu);
                    break;
                case 5:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    } else {
        cout << "Invalid credentials. Access denied.\n";
    }
}

void addMenuItem(vector<MenuItem>& menu) {
    MenuItem newItem;
    cout << "Enter item ID: ";
    cin >> newItem.id;
    cout << "Enter item name: ";
    cin.ignore();
    getline(cin, newItem.name);
    cout << "Enter item price: ";
    cin >> newItem.price;
    cout << "Enter item description: ";
    cin.ignore();
    getline(cin, newItem.description);

    menu.push_back(newItem);
    cout << "Menu item added successfully.\n";
}

void updateMenuItem(vector<MenuItem>& menu) {
    int id;
    cout << "Enter item ID to update: ";
    cin >> id;

    for (auto& item : menu) {
        if (item.id == id) {
            cout << "Enter new name (current: " << item.name << "): ";
            cin.ignore();
            getline(cin, item.name);
            cout << "Enter new price (current: " << item.price << "): ";
            cin >> item.price;
            cout << "Enter new description (current: " << item.description << "): ";
            cin.ignore();
            getline(cin, item.description);

            cout << "Menu item updated successfully.\n";
            return;
        }
    }
    cout << "Item with ID " << id << " not found.\n";
}

void removeMenuItem(vector<MenuItem>& menu) {
    int id;
    cout << "Enter item ID to remove: ";
    cin >> id;

    for (auto it = menu.begin(); it != menu.end(); ++it) {
        if (it->id == id) {
            menu.erase(it);
            cout << "Menu item removed successfully.\n";
            return;
        }
    }
    cout << "Item with ID " << id << " not found.\n";
}

void displayMenu(const vector<MenuItem>& menu) {
    cout << "\nMenu:\n";
    for (const auto& item : menu) {
        cout << item.id << ". " << item.name << " - $" << item.price << " (" << item.description << ")\n";
    }
}

void customerSide(vector<Table>& tables, vector<MenuItem>& menu, vector<Order>& orders, vector<Feedback>& feedbacks) {
    int choice;
    do {
        cout << "\n--- Customer Side ---\n";
        cout << "1. View Table Availability\n";
        cout << "2. Reserve a Table\n";
        cout << "3. View Menu\n";
        cout << "4. Place an Order\n";
        cout << "5. Make a Payment\n";
        cout << "6. Leave Feedback\n";
        cout << "7. View Feedback\n";
        cout << "8. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayTables(tables);
                break;
            case 2:
                reserveTable(tables);
                break;
            case 3:
                displayMenu(menu);
                break;
            case 4:
                placeOrder(orders, menu);
                break;
            case 5:
                processPayment(orders);
                break;
            case 6:
                leaveFeedback(feedbacks);
                break;
            case 7:
                viewFeedback(feedbacks);
                break;
            case 8:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

void displayTables(const vector<Table>& tables) {
    cout << "\nTable Availability:\n";
    for (const auto& table : tables) {
        cout << "Table " << table.tableNumber << " (Capacity: " << table.capacity << "): ";
        cout << (table.isAvailable ? "Available" : "Occupied") << "\n";
    }
}

void reserveTable(vector<Table>& tables) {
    int tableNum;
    cout << "Enter table number to reserve: ";
    cin >> tableNum;

    for (auto& table : tables) {
        if (table.tableNumber == tableNum) {
            if (table.isAvailable) {
                table.isAvailable = false;
                cout << "Table " << tableNum << " reserved successfully.\n";
            } else {
                cout << "Table " << tableNum << " is already occupied.\n";
            }
            return;
        }
    }
    cout << "Invalid table number.\n";
}

void placeOrder(vector<Order>& orders, const vector<MenuItem>& menu) {
    Order newOrder;
    cout << "Enter table number: ";
    cin >> newOrder.tableNumber;

    newOrder.totalAmount = 0.0;

    char choice;
    do {
        displayMenu(menu);
        int itemId, quantity;
        cout << "Enter menu item ID: ";
        cin >> itemId;
        cout << "Enter quantity: ";
        cin >> quantity;

        bool itemFound = false;
        for (const auto& item : menu) {
            if (item.id == itemId) {
                newOrder.itemQuantities.push_back({itemId, quantity});
                newOrder.totalAmount += item.price * quantity;
                itemFound = true;
                cout << "Added " << item.name << " (" << quantity << "x) to order.\n";
                break;
            }
        }

        if (!itemFound) {
            cout << "Invalid menu item ID.\n";
        }

        cout << "Add another item? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    newOrder.orderId = orders.size() + 1;
    orders.push_back(newOrder);

    cout << "Order placed! Total: $" <<

 newOrder.totalAmount << "\n";
}

void processPayment(vector<Order>& orders) {
    int orderId;
    cout << "Enter order ID to process payment: ";
    cin >> orderId;

    for (auto& order : orders) {
        if (order.orderId == orderId) {
            cout << "Order ID " << orderId << " - Total Amount: $" << order.totalAmount << "\n";
            cout << "Payment processed. Thank you!\n";
            return;
        }
    }
    cout << "Order ID not found.\n";
}

void leaveFeedback(vector<Feedback>& feedbacks) {
    Feedback newFeedback;
    cout << "Enter your table number: ";
    cin >> newFeedback.tableNumber;
    cout << "Leave your comments: ";
    cin.ignore();
    getline(cin, newFeedback.comments);
    cout << "Rate us (1-5): ";
    cin >> newFeedback.rating;

    feedbacks.push_back(newFeedback);
    cout << "Thank you for your feedback!\n";
}

void viewFeedback(const vector<Feedback>& feedbacks) {
    cout << "\nCustomer Feedback:\n";
    for (const auto& feedback : feedbacks) {
        cout << "Table " << feedback.tableNumber << ": " << feedback.comments << " (Rating: " << feedback.rating << ")\n";
    }
}

void saveOrdersToFile(const vector<Order>& orders) {
    ofstream outFile("orders.txt");
    if (outFile.is_open()) {
        for (const auto& order : orders) {
            outFile << order.orderId << " " << order.tableNumber << " " << order.totalAmount << "\n";
        }
        outFile.close();
        cout << "Orders saved to file.\n";
    } else {
        cout << "Failed to save orders to file.\n";
    }
}

void loadOrdersFromFile(vector<Order>& orders) {
    ifstream inFile("orders.txt");
    if (inFile.is_open()) {
        Order order;
        while (inFile >> order.orderId >> order.tableNumber >> order.totalAmount) {
            orders.push_back(order);
        }
        inFile.close();
        cout << "Orders loaded from file.\n";
    } else {
        cout << "Failed to load orders from file.\n";
    }
}

