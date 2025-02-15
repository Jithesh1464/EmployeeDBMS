#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>  
#include<string>
#include<bits/stdc++.h>
#include<windows.h>

using namespace std;

// to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// to handle input from user
// prompts user for input until expected type is obtained
template <typename T>
T getInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        try {
            cin >> value;
            if (cin.fail()) {
                throw runtime_error("Invalid input. Please enter a valid value.");
            }
            clearInputBuffer();
            return value;
        } catch (const exception& e) {
            clearInputBuffer();
            cout << "Error: " << e.what() << endl;
        }
    }
}

// to check validity of input ID
bool isValidNumericId(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// to check validity of input name
bool isValidAlphabeticName(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}


class Employee 
{
    protected:
        int id;
        string name;
        double salary;
        string designation;
        string type;
        string speciality;

    public:
        Employee() {}
        Employee(int id, const string& name, double salary, const string& designation, const string& _speciality, const string& _type)
            : id(id), name(name), salary(salary), designation(designation), speciality(_speciality), type(_type) {}


        int getId() const { return id; }
        string getName() const { return name; }
        double getSalary() const { return salary; }
        string getDesignation() const { return designation; }
        string getSpeciality() const {return speciality;}


        void setName(const string& newName) { name = newName; }
        void setSalary(double newSalary) { salary = newSalary; }
        void setDesignation(const string& newDesignation) { designation = newDesignation; }
        void setSpecialization(const string& newSpecialization) { speciality = newSpecialization; }
        void setType(const string& newType) { type = newType; }


        virtual void display() const 
        {
            cout << setw(5) << left << id << setw(20) << left << name << setw(15) << left << designation << setw(15) << left << type << setw(15) << left << speciality << setw(10) << left << "Salary:" << setw(10) << left << salary << endl;
        }


        friend ostream& operator<<(ostream& os, const Employee& emp) 
        {
            os << emp.id << ',' << emp.name << ',' << emp.designation << ',' << emp.type << ',' << emp.speciality << ',' << emp.salary;
            return os;
        }
};


class Manager : public Employee 
{
private:
    string department;

public:
    Manager(int id, const string& name, double salary, const string& department, const string& designation, const string& type)
        : Employee(id, name, salary, designation, department, type), department(department) {}

    string getDepartment() const {return department;}


    void setDepartment(const string& newDepartment) { department = newDepartment; }


    void display() const override 
    {
        cout << setw(16) << left << id << setw(24) << left << name << setw(24) << left << designation << setw(8) << left << "Salary:" << setw(16) << left << salary << setw(16) << left << "Department:" << department << endl;
    }
};

class Engineer : public Employee 
{
    private:
        string specialization;

    public:

        Engineer(int id, const string& name, double salary, const string& specialization, const string& designation, const string& type)
            : Employee(id, name, salary, designation, specialization, type), specialization(specialization) {}


        string getSpecialization() const { return specialization; }


        void setSpecialization(const string& newSpecialization) { specialization = newSpecialization; }


        void display() const override 
        {
            cout << setw(16) << left << id << setw(24) << left << name << setw(24) << left << designation << setw(8) << left << "Salary:" << setw(16) << left << salary << setw(16) << left << "Specialization:" << specialization << endl;
        }
};


class Database 
{
    private:
        vector<Employee*> employees;
        string filename;

    public:
        Database(string _filename) : filename(_filename)
        {
            loadFromFile(); 
        }

        // to add a new employee data
        void addEmployee(Employee* emp) 
        {
            employees.push_back(emp);
            writeEmployee(emp);
        }

        // to check if duplicate ID exists
        bool checkDuplicateId(int id) const 
        {
            return find_if(employees.begin(), employees.end(), [id](const Employee* emp) 
            {
                return emp->getId() == id;
            }) != employees.end();
        }

        // to display all employees
        void displayAll() const 
        {   system("cls");
            cout << "**************************************************EMPLOYEES LIST**********************************************************" << endl;
            cout<<endl<<endl<<endl;
            cout << "ID\t\tNAME\t\t\tDESIGNATION\t\t\tDETAILS" << endl;
            cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
            for (const auto& emp : employees) 
            {
                emp->display();
                cout<<endl;
            }
            cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
        }

        // to search employee by ID
        void search(int id) const 
        {
            bool found = false;
            for (const auto& emp : employees) 
            {
                if (emp->getId() == id) 
                {   
                    system("cls");
                    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ EMPLOYEE FOUND  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl<<endl<<endl;
                    cout << "ID\t\tNAME\t\t\tDESIGNATION\t\t\tDETAILS" << endl;
                    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
                    emp->display();
                    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
                    found = true;
                    Sleep(3000);
                    break;
                }
            }
            if (!found) 
            {   
                system("cls");
                // cout << setw(16) << left << "NA" << setw(24) << left << "NA" << setw(24) << left << "NA" << setw(8) << left << "Salary:" << setw(16) << left << "NA" << setw(16) << left << "Specialization:" << "NA" << endl;
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  EMPLOYEE WITH ID : " << id << "  NOT FOUND  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                Sleep(3000);
            }
        }

        // to search employee by name
        void search(const string& name) const 
        {   
            system("cls");
            bool found = false;
            cout << "*********************************  EMPLOYEE WITH NAME : '" << name << "'  ********************************" << endl;
            cout<<endl<<endl<<endl;
            cout << "ID\t\tNAME\t\t\tDESIGNATION\t\t\tDETAILS" << endl;
            cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
            for (const auto& emp : employees) 
            {
                if (emp->getName() == name) 
                {
                    emp->display();
                    found = true;
                }
            }
            if (!found) 
            {   
                cout << setw(16) << left << "NA" << setw(24) << left << "NA" << setw(24) << left << "NA" << setw(8) << left << "Salary:" << setw(16) << left << "NA" << setw(16) << left << "Specialization:" << "NA" << endl;
                // cout << "No employees with Name '" << name << "' found." << endl;
            }
            cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
            Sleep(4000);
        }

        // to update employee details
        void updateEmployee(int id) 
        {
            auto it = find_if(employees.begin(), employees.end(), [id](const Employee* emp) 
            {
                return emp->getId() == id;
            });

            if (it != employees.end()) 
            {
                cout << "Employee found. Choose what you want to update:\n";
                cout << "1. Name\n";
                cout << "2. Designation\n";
                cout << "3. Salary\n";
                int choice = getInput<int> ("Enter you choice: ");
                //cin.ignore();  

                switch (choice) 
                {
                    case 1: 
                    {
                        string newName;
                        do {
                            newName = getInput<string>("Enter Employee Name (letters only): ");
                        } while (!isValidAlphabeticName(newName));
                        (*it)->setName(newName);
                        break;
                    }
                    
                    case 2: 
                    {
                        string newDesignation;
                        cout << "Enter New Designation: ";
                        getline(cin, newDesignation);
                        (*it)->setDesignation(newDesignation);
                        break;
                    }
                    
                    case 3: 
                    {
                        double newSalary = getInput<double> ("Enter new salary: ");
                        (*it)->setSalary(newSalary);
                        break;
                    }
                    
                    default:
                        cout << "Invalid choice! No updates performed." << endl;
                        return;
                }

                // truncate mode
                ofstream outputFile("employees.txt", ios::trunc);
                if (outputFile.is_open()) 
                {
                    for (const auto& emp : employees) 
                    {
                        outputFile << *emp << endl;
                    }
                    outputFile.close();
                    cout << "EMPLOYEE WITH ID " << id << " UPDATED SUCCESSFULLY" << endl;
                    Sleep(4000);
                } 
                else 
                {
                    cout << "!!!!!!!!!!!!!!!! Unable to open file for writing !!!!!!!!!!!!!!!!" << endl;
                }
            } 
            else 
            {
                cout << "EMPLOYEE WITH ID " << id << " NOT FOUND. UPDATE FAILED." << endl;
                Sleep(3000);
            }
        }

        // to delete employee by ID
        void deleteEmployee(int id) 
        {
            auto it = find_if(employees.begin(), employees.end(), [id](const Employee* emp) 
            {
                return emp->getId() == id;
            });

            if (it != employees.end()) 
            {
                delete *it; 
                employees.erase(it);

                
                ofstream outputFile("employees.txt", ios::trunc);
                if (outputFile.is_open()) 
                {
                    for (const auto& emp : employees) 
                    {
                        outputFile << *emp << endl;
                    }
                    outputFile.close();
                    cout << "EMPLOYEE WITH ID " << id << " DELETED SUCCESSFULLY." << endl;
                } 
                else 
                {
                    cout << "!!!!!!!!!!!!!!!! Unable to open file for writing !!!!!!!!!!!!!!!!" << endl;
                }
            } 
            else 
            {
                cout << "EMPLOYEE WITH ID " << id << " NOT FOUND. DELETION FAILED." << endl;
            }
        }


    private:
        // to load data from file
        void loadFromFile() 
        {
            ifstream inputFile(filename);
            if (inputFile.is_open()) 
            {
                string name, designation, _id, line, type, speciality, _salary;
                double salary;
                int id;

                
                while (getline(inputFile, line)) 
                {
                    stringstream ss(line);

                    if(getline(ss, _id, ',') &&
                        getline(ss, name, ',') &&
                        getline(ss, designation, ',') &&
                        getline(ss, type, ',') &&
                        getline(ss, speciality, ',') &&
                        getline(ss, _salary, ',')
                    )
                    {
                        id = stoi(_id);
                        salary = stoll(_salary);

                        if (type == "Manager")
                        {
                            employees.push_back(new Manager(id, name, salary, speciality, designation, "Manager"));
                        }
                        else if (type == "Engineer")
                        {
                            employees.push_back(new Engineer(id, name, salary, speciality, designation, "Engineer"));
                        }
                    }
                }
                inputFile.close();
            }
        }

        // to save data to file
        void saveToFile() const 
        {
            ofstream outputFile(filename, std::ios::app);
            if (outputFile.is_open()) 
            {
                for (const auto& emp : employees) 
                {
                    outputFile << *emp << endl;
                }
                outputFile.close();
            }
        }

        // to write the entire data onto the file
        void writeEmployee(Employee * emp)
        {
            ofstream outputFile(filename, std::ios::app);
            if (outputFile.is_open()) 
            {
                outputFile << *emp << endl;
                outputFile.close();
            }
        }
};

// menu driven user input
int getMenuChoice() 
{
    int choice;
    cout << "\n\t\t\t\tEMPLOYEE DATABASE MANAGEMENT SYSTEM\t\t\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t1. Add Employee\n";
    cout << "\t\t\t\t2. Display All Employees\n";
    cout << "\t\t\t\t3. Search Employee by ID\n";
    cout << "\t\t\t\t4. Search Employee by Name\n";
    cout << "\t\t\t\t5. Update Employee Details\n";
    cout << "\t\t\t\t6. Delete Employee\n";
    cout << "\t\t\t\t7. Exit\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;

    // cin.ignore();
    choice = getInput<int>("Enter your choice: ");
    // cin >> choice;
    return choice;
}

// main function
int main() 
{
    Database empDatabase("employees.txt");
    int choice;

    do 
    {
        choice = getMenuChoice();

        switch (choice) 
        {
            case 1: 
            {
                string idStr;
                int id;
                do {    
                        idStr = getInput<string>("Enter Employee ID (numeric only): ");
                        // system("cls");
                        if(!isValidNumericId(idStr)) cout<<"*******WARNING*******\n"<<"!!**ENTER IN VALID FORM**!!\n";
                    } while (!isValidNumericId(idStr));
                id = stoi(idStr);

                string name, designation;
                double salary;
                string empType;
                // cin.ignore();  
                
                if (empDatabase.checkDuplicateId(id)) 
                {
                    cout << "Error: Employee with ID " << id << " already exists. Cannot add duplicate IDs." << endl;
                    break;
                }

                
                do {
                    name = getInput<string>("Enter Employee Name (letters only): ");
                } while (!isValidAlphabeticName(name));
                
                cout << "Enter Employee Designation (sde etc): ";
                getline(cin, designation);
                salary = getInput<double>("Enter salary: ");
                cout << "Enter Employee Type (Manager/Engineer): ";
                cin >> empType;
                cin.ignore();  

                if (empType == "Manager") 
                {
                    string department;
                    cout << "Enter Manager Department: ";
                    getline(cin, department);
                    empDatabase.addEmployee(new Manager(id, name, salary, department, designation, "Manager"));
                } 
                else if (empType == "Engineer") 
                {
                    string specialization;
                    cout << "Enter Engineer Specialization: ";
                    getline(cin, specialization);
                    empDatabase.addEmployee(new Engineer(id, name, salary, specialization, designation, "Engineer"));
                } 
                else 
                {
                    cout << "Invalid Employee Type. Employee not added." << endl;
                }
                break;
            }
           
            case 2:
                empDatabase.displayAll();
                Sleep(4000);
                break;
            
            case 3: 
            {
                string idStr;
                int id;
                do {
                    idStr = getInput<string>("Enter Employee ID (numeric only): ");
                    } while (!isValidNumericId(idStr));
                id = stoi(idStr);
                empDatabase.search(id);
                break;
            }
            
            case 4: 
            {
                string name;
                do {
                    name = getInput<string>("Enter Employee Name (letters only): ");
                } while (!isValidAlphabeticName(name));
                empDatabase.search(name);
                break;
            }
            
            case 5: 
            {
                string idStr;
                int id;
                do {
                    idStr = getInput<string>("Enter Employee ID (numeric only): ");
                    } while (!isValidNumericId(idStr));
                id = stoi(idStr); 
                empDatabase.updateEmployee(id);
                break;
            }
            
            case 6: 
            {
                string idStr;
                int id;
                do {
                    idStr = getInput<string>("Enter Employee ID (numeric only): ");
                    } while (!isValidNumericId(idStr));
                id = stoi(idStr);
                empDatabase.deleteEmployee(id);
                break;
            }
            
            case 7:
            {   system("cls");
                cout << "Exiting program...\n";
                Sleep(2000);
                system("cls");
                break;
            }
            
            default:
            {   
                   system("cls");
                   cout << "Invalid choice! Please try again.\n";
            }
        }
    } while (choice != 7);

    return 0;
}
