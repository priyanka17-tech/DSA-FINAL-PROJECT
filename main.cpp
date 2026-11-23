
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#define SIZE 10
#define MAX 100

struct Order {
    int id;
    string name, food, status;
    int price;
    bool paid;
};

class Canteen {
    Order orders[MAX];
    int queue[SIZE];
    int history[MAX];

    int front = -1, rear = -1;
    int count = 0, total = 0;
    int historyCount = 0;

    Order newOrder;
    bool draft = false;
    int current = -1;

public:

    void menu() {
        cout << "\n========== FOOD MENU ==========\n";
        cout << "1. Sandwich       Rs. 40\n";
        cout << "2. Burger         Rs. 60\n";
        cout << "3. Dosa           Rs. 50\n";
        cout << "4. Tea            Rs. 15\n";
        cout << "5. Coffee         Rs. 30\n";

        cout << "\n========== COMBO OFFERS ==========\n";
        cout << "6. Sandwich + Tea   Rs. 55\n";
        cout << "7. Burger + Coffee Rs. 90\n";
    }

    int getFoodPrice(int choice) {
        switch (choice) {
            case 1: return 40;
            case 2: return 60;
            case 3: return 50;
            case 4: return 15;
            case 5: return 30;
            case 6: return 55;
            case 7: return 90;
            default: return 0;
        }
    }

    string getFoodName(int choice) {
        string foods[] = {
            "", "Sandwich", "Burger", "Dosa",
            "Tea", "Coffee", "Sandwich + Tea",
            "Burger + Coffee"
        };

        return foods[choice];
    }

    int findOrder(int id) {
        for (int i = 0; i < total; i++) {
            if (orders[i].id == id)
                return i;
        }
        return -1;
    }

    // 1. Food Menu
    void showMenu() {
        menu();
    }

    // 2. New Order
    void newOrderEntry() {
        if (draft) {
            cout << "\nPlease place the previous order first!\n";
            return;
        }

        if (total == MAX) {
            cout << "\nOrder storage is full!\n";
            return;
        }

        if (count == SIZE) {
            cout << "\nQueue is Full! Cannot add order.\n";
            return;
        }

        cout << "\nEnter Order ID: ";
        cin >> newOrder.id;

        if (findOrder(newOrder.id) != -1) {
            cout << "\nOrder ID already exists!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, newOrder.name);

        menu();

        int choice;
        cout << "\nSelect Food Item: ";
        cin >> choice;

        newOrder.price = getFoodPrice(choice);

        if (newOrder.price == 0) {
            cout << "\nInvalid Food Choice!\n";
            return;
        }

        newOrder.food = getFoodName(choice);
        newOrder.status = "New Order";
        newOrder.paid = false;

        draft = true;

        cout << "\nOrder Details Saved Successfully!\n";
    }

    // 3. Place Order - Enqueue
    void placeOrder() {
        if (!draft) {
            cout << "\nPlease create a New Order first!\n";
            return;
        }

        if (count == SIZE) {
            cout << "\nQueue is Full!\n";
            return;
        }

        orders[total] = newOrder;

        if (count == 0)
            front = 0;

        rear = (rear + 1) % SIZE;
        queue[rear] = total;

        total++;
        count++;
        draft = false;

        cout << "\nOrder Placed Successfully!\n";
        cout << "Order ID: " << newOrder.id << endl;
    }

    // 4. Generate Receipt
    void receipt() {
        int id;
        cout << "\nEnter Order ID: ";
        cin >> id;

        int i = findOrder(id);

        if (i == -1) {
            cout << "\nOrder Not Found!\n";
            return;
        }

        cout << "\n========== RECEIPT ==========\n";
        cout << "Order ID : " << orders[i].id << endl;
        cout << "Student  : " << orders[i].name << endl;
        cout << "Food     : " << orders[i].food << endl;
        cout << "Amount   : Rs. " << orders[i].price << endl;
        cout << "Payment  : "
             << (orders[i].paid ? "Paid" : "Pending") << endl;
        cout << "=============================\n";
    }

    // 5. Payment
    void payment() {
        int id;
        cout << "\nEnter Order ID: ";
        cin >> id;

        int i = findOrder(id);

        if (i == -1) {
            cout << "\nOrder Not Found!\n";
            return;
        }

        if (orders[i].paid) {
            cout << "\nPayment Already Completed!\n";
            return;
        }

        cout << "\nAmount: Rs. " << orders[i].price << endl;
        cout << "1. Cash\n2. UPI\n3. Card\n";
        cout << "Select Payment Method: ";

        int choice;
        cin >> choice;

        if (choice < 1 || choice > 3) {
            cout << "\nInvalid Payment Method!\n";
            return;
        }

        orders[i].paid = true;
        cout << "\nPayment Successful!\n";
    }

    // 6. Order Tracking
    void tracking() {
        int id;
        cout << "\nEnter Order ID: ";
        cin >> id;

        int i = findOrder(id);

        if (i == -1) {
            cout << "\nOrder Not Found!\n";
            return;
        }

        cout << "\nOrder ID: " << orders[i].id;
        cout << "\nFood: " << orders[i].food;
        cout << "\nStatus: " << orders[i].status << endl;
    }

    // 7. Start Preparing - Dequeue
    void prepareOrder() {
        if (current != -1) {
            cout << "\nComplete the current order first!\n";
            return;
        }

        if (count == 0) {
            cout << "\nQueue is Empty! No Pending Orders.\n";
            return;
        }

        current = queue[front];

        front = (front + 1) % SIZE;
        count--;

        if (count == 0) {
            front = -1;
            rear = -1;
        }

        orders[current].status = "Preparing";

        cout << "\nPreparing Order: "
             << orders[current].id << endl;
        cout << "Student: " << orders[current].name << endl;
        cout << "Food: " << orders[current].food << endl;
    }

    // 8. Pending Orders
    void pendingOrders() {
        if (count == 0) {
            cout << "\nNo Pending Orders!\n";
            return;
        }

        cout << "\n========== PENDING ORDERS ==========\n";

        for (int i = 0; i < count; i++) {
            int index = queue[(front + i) % SIZE];

            cout << "\nOrder ID: " << orders[index].id;
            cout << "\nStudent: " << orders[index].name;
            cout << "\nFood: " << orders[index].food;
            cout << "\nStatus: " << orders[index].status << endl;
        }
    }

    // 9. Mark Order as Ready
    void markReady() {
        if (current == -1) {
            cout << "\nNo Order is Being Prepared!\n";
            return;
        }

        orders[current].status = "Ready";

        cout << "\nOrder "
             << orders[current].id
             << " is Ready!\n";
    }

    // 10. Complete Order
    void completeOrder() {
        if (current == -1) {
            cout << "\nNo Active Order!\n";
            return;
        }

        if (orders[current].status != "Ready") {
            cout << "\nMark the Order as Ready First!\n";
            return;
        }

        if (!orders[current].paid) {
            cout << "\nPayment is Pending! Complete Payment First.\n";
            return;
        }

        orders[current].status = "Completed";
        history[historyCount++] = current;

        cout << "\nOrder Completed Successfully!\n";

        current = -1;
    }

    // 11. Order History
    void orderHistory() {
        if (historyCount == 0) {
            cout << "\nNo Completed Orders!\n";
            return;
        }

        cout << "\n========== ORDER HISTORY ==========\n";

        for (int i = 0; i < historyCount; i++) {
            int index = history[i];

            cout << "\nOrder ID: " << orders[index].id;
            cout << "\nStudent: " << orders[index].name;
            cout << "\nFood: " << orders[index].food;
            cout << "\nStatus: " << orders[index].status << endl;
        }
    }

    // 12. Exit
    void run() {
        int choice;

        do {
            cout << "\n====================================\n";
            cout << "   COLLEGE CANTEEN MANAGEMENT SYSTEM\n";
            cout << "====================================\n";

            cout << "\n1. Food Menu & Combo Offers";
            cout << "\n2. New Order";
            cout << "\n3. Place Order";
            cout << "\n4. Generate Receipt";
            cout << "\n5. Payment";
            cout << "\n6. Order Tracking";
            cout << "\n7. Start Preparing Order";
            cout << "\n8. Pending Orders";
            cout << "\n9. Mark Order as Ready";
            cout << "\n10. Complete Order";
            cout << "\n11. Order History";
            cout << "\n12. Exit";

            cout << "\n\nEnter Your Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: showMenu(); break;
                case 2: newOrderEntry(); break;
                case 3: placeOrder(); break;
                case 4: receipt(); break;
                case 5: payment(); break;
                case 6: tracking(); break;
                case 7: prepareOrder(); break;
                case 8: pendingOrders(); break;
                case 9: markReady(); break;
                case 10: completeOrder(); break;
                case 11: orderHistory(); break;
                case 12:
                    cout << "\nThank You! Visit Again.\n";
                    break;
                default:
                    cout << "\nInvalid Choice!\n";
            }

        } while (choice != 12);
    }
};

int main() {
    Canteen c;
    c.run();

    return 0;
}
