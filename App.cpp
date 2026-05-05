#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// ======================================
// EMPLOYEE CLASS
// ======================================
class Employee {
private:
    int id = 0;
    string name;
    string role;
    string phone;
    string address;
    double salary = 0.0;   // FIXED

public:
    void setData(
        int i,
        string n,
        string r,
        string p,
        string a,
        double s
    ) {
        id = i;
        name = n;
        role = r;
        phone = p;
        address = a;
        salary = s;
    }

    int getID() const { return id; }
    string getName() const { return name; }
    string getRole() const { return role; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
    double getSalary() const { return salary; }

    void display() const {
        cout << left
             << setw(8)  << id
             << setw(20) << name
             << setw(18) << role
             << setw(18) << phone
             << setw(15) << fixed << setprecision(2) << salary
             << endl;
    }
};

// ======================================
// SYSTEM CLASS
// ======================================
class PersonnelSystem {

private:
    vector<Employee> employees;

public:

    // ---------- CHECK DUPLICATE ----------
    bool exists(int id) {

        for (const auto &e : employees) {
            if (e.getID() == id)
                return true;
        }

        return false;
    }

    // ---------- LOAD ----------
    void loadFromFile() {

        ifstream file("employees.txt");

        if (!file)
            return;

        employees.clear();

        while (true) {

            Employee e;

            int id;
            string name, role, phone, address;
            double salary;

            file >> id;

            if (file.fail())
                break;

            file.ignore();

            getline(file, name);
            getline(file, role);
            getline(file, phone);
            getline(file, address);

            file >> salary;

            if (file.fail())
                break;

            file.ignore();

            e.setData(
                id,
                name,
                role,
                phone,
                address,
                salary
            );

            employees.push_back(e);
        }

        file.close();
    }

    // ---------- SAVE ----------
    void saveToFile() {

        ofstream file("employees.txt", ios::trunc);

        for (const auto &e : employees) {

            file << e.getID() << endl;
            file << e.getName() << endl;
            file << e.getRole() << endl;
            file << e.getPhone() << endl;
            file << e.getAddress() << endl;
            file << e.getSalary() << endl;
        }

        file.close();
    }

    // ---------- ADD ----------
    void addEmployee() {

        Employee e;

        int id;
        string name, role, phone, address;
        double salary;

        cout << "\nEnter Employee ID: ";
        cin >> id;

        if (exists(id)) {
            cout << "❌ ID already exists.\n";
            return;
        }

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Role: ";
        getline(cin, role);

        cout << "Enter Phone: ";
        getline(cin, phone);

        cout << "Enter Address: ";
        getline(cin, address);

        cout << "Enter Salary: ";
        cin >> salary;

        e.setData(
            id,
            name,
            role,
            phone,
            address,
            salary
        );

        employees.push_back(e);

        saveToFile();

        cout << "✅ Employee Added Successfully.\n";
    }

    // ---------- VIEW ----------
    void viewEmployees() {

        if (employees.empty()) {
            cout << "\nNo employees found.\n";
            return;
        }

        cout << "\n====================================================================================\n";

        cout << left
             << setw(8)  << "ID"
             << setw(20) << "NAME"
             << setw(18) << "ROLE"
             << setw(18) << "PHONE"
             << setw(15) << "SALARY"
             << endl;

        cout << "====================================================================================\n";

        for (const auto &e : employees) {
            e.display();
        }

        cout << "====================================================================================\n";
    }

    // ---------- SEARCH ----------
    void searchEmployee() {

        int id;

        cout << "\nEnter Employee ID: ";
        cin >> id;

        for (const auto &e : employees) {

            if (e.getID() == id) {

                cout << "\nEmployee Found:\n\n";

                cout << left
                     << setw(8)  << "ID"
                     << setw(20) << "NAME"
                     << setw(18) << "ROLE"
                     << setw(18) << "PHONE"
                     << setw(15) << "SALARY"
                     << endl;

                e.display();

                return;
            }
        }

        cout << "❌ Employee not found.\n";
    }

    // ---------- UPDATE ----------
    void updateEmployee() {

        int id;

        cout << "\nEnter Employee ID: ";
        cin >> id;

        for (auto &e : employees) {

            if (e.getID() == id) {

                string name, role, phone, address;
                double salary;

                cin.ignore();

                cout << "New Name: ";
                getline(cin, name);

                cout << "New Role: ";
                getline(cin, role);

                cout << "New Phone: ";
                getline(cin, phone);

                cout << "New Address: ";
                getline(cin, address);

                cout << "New Salary: ";
                cin >> salary;

                e.setData(
                    id,
                    name,
                    role,
                    phone,
                    address,
                    salary
                );

                saveToFile();

                cout << "✏️ Employee Updated Successfully.\n";

                return;
            }
        }

        cout << "❌ Employee not found.\n";
    }

    // ---------- DELETE ----------
    void deleteEmployee() {

        int id;

        cout << "\nEnter Employee ID: ";
        cin >> id;

        for (auto it = employees.begin();
             it != employees.end();
             it++) {

            if (it->getID() == id) {

                employees.erase(it);

                saveToFile();

                cout << "🗑 Employee Deleted Successfully.\n";

                return;
            }
        }

        cout << "❌ Employee not found.\n";
    }
};

// ======================================
// MAIN
// ======================================
int main() {

    PersonnelSystem system;

    system.loadFromFile();

    int choice;

    do {

        cout << "\n";
        cout << "================================================\n";
        cout << "   SOFTWARE PERSONNEL MANAGEMENT SYSTEM\n";
        cout << "================================================\n";

        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                system.addEmployee();
                break;

            case 2:
                system.viewEmployees();
                break;

            case 3:
                system.searchEmployee();
                break;

            case 4:
                system.updateEmployee();
                break;

            case 5:
                system.deleteEmployee();
                break;

            case 6:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "❌ Invalid Choice.\n";
        }

    } while(choice != 6);

    return 0;
}
