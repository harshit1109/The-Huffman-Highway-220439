#include <iostream>
#include <string>
#include <memory>

using namespace std;

class StudentRecord {
public:
    int roll_number;
    string full_name;
    string department;
    int total_marks;
    shared_ptr<StudentRecord> next;

    StudentRecord(int roll_number, const string& full_name, const string& dept, int marks) :
        roll_number(roll_number), full_name(full_name), department(dept), total_marks(marks), next(nullptr) {}
};

shared_ptr<StudentRecord> list_head = nullptr;

bool recordExists(int roll_number)
{
    auto current = list_head;
    while (current) {
        if (current->roll_number == roll_number) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void addRecord(int roll_number, const string& full_name, const string& dept, int marks)
{
    if (recordExists(roll_number)) {
        cout << "Oops! A student with roll number " << roll_number << " already exists in the system.\n";
        return;
    }

    auto new_record = make_shared<StudentRecord>(roll_number, full_name, dept, marks);
    if (!list_head || list_head->roll_number >= new_record->roll_number) {
        new_record->next = list_head;
        list_head = new_record;
    } else {
        auto current = list_head;
        while (current->next && current->next->roll_number < new_record->roll_number) {
            current = current->next;
        }
        new_record->next = current->next;
        current->next = new_record;
    }

    cout << "Record added successfully!\n";
}

void findRecord(int roll_number)
{
    auto current = list_head;
    while (current) {
        if (current->roll_number == roll_number) {
            cout << "Found record for roll number: " << current->roll_number << "\n";
            cout << "Name: " << current->full_name << "\n";
            cout << "Dept: " << current->department << "\n";
            cout << "Marks: " << current->total_marks << "\n";
            return;
        }
        current = current->next;
    }
    cout << "No record found for roll number " << roll_number << ".\n";
}

void removeRecord(int roll_number)
{
    if (!list_head) {
        cout << "No records available to delete.\n";
        return;
    }

    if (list_head->roll_number == roll_number) {
        list_head = list_head->next;
        cout << "Record for roll number " << roll_number << " has been deleted.\n";
        return;
    }

    auto current = list_head;
    while (current->next && current->next->roll_number != roll_number) {
        current = current->next;
    }

    if (current->next) {
        current->next = current->next->next;
        cout << "Successfully deleted the record for roll number " << roll_number << ".\n";
    } else {
        cout << "No record found for roll number " << roll_number << " to delete.\n";
    }
}

void showAllRecords()
{
    if (!list_head) {
        cout << "No records are currently available.\n";
        return;
    }

    auto current = list_head;
    cout << "RollNo\tName\tDepartment\tMarks\n";
    while (current) {
        cout << current->roll_number << "\t" << current->full_name << "\t" << current->department << "\t" << current->total_marks << "\n";
        current = current->next;
    }
}

int main()
{
    int choice;
    while (true) {
        cout << "\nWelcome to the Student Record Management System\n";
        cout << "1. Add new student record\n";
        cout << "2. Delete a student record\n";
        cout << "3. Find a student record\n";
        cout << "4. Show all records\n";
        cout << "5. Exit\n";
        cout << "Please enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string full_name, dept;
            int roll_number, marks;
            cout << "Enter student's full name: ";
            cin >> full_name;
            cout << "Enter student's roll number: ";
            cin >> roll_number;
            cout << "Enter student's department: ";
            cin >> dept;
            cout << "Enter student's total marks: ";
            cin >> marks;
            addRecord(roll_number, full_name, dept, marks);
        } else if (choice == 2) {
            int roll_number;
            cout << "Enter roll number of the student to delete: ";
            cin >> roll_number;
            removeRecord(roll_number);
        } else if (choice == 3) {
            int roll_number;
            cout << "Enter roll number of the student to find: ";
            cin >> roll_number;
            findRecord(roll_number);
        } else if (choice == 4) {
            showAllRecords();
        } else if (choice == 5) {
            cout << "Exiting the system. Have a great day!\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
