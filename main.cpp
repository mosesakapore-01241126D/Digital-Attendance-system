#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    string indexNumber;

    Student(string n, string i) {
        name = n;
        indexNumber = i;
    }
};

#include <map>

class AttendanceSession {
public:
    string courseCode;
    string date;
    string startTime;
    int duration;

    map<string, string> attendance;

    AttendanceSession(string code, string d, string time, int dur) {
        courseCode = code;
        date = d;
        startTime = time;
        duration = dur;
    }
};
vector<Student> students;
void saveStudentsToFile() {
    ofstream file("students.txt");

    for (int i = 0; i < students.size(); i++) {
        file << students[i].name << ","
             << students[i].indexNumber << endl;
    }

    file.close();
}
vector<AttendanceSession> sessions;

void addStudent() {
    string name;
    string index;

    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Index Number: ";
    getline(cin, index);

    students.push_back(Student(name, index));
saveStudentsToFile();

cout << "Student added successfully!\n";
}   

void loadStudentsFromFile() {
    ifstream file("students.txt");
    string name, index;

    while (getline(file, name, ',') && getline(file, index)) {
        students.push_back(Student(name, index));
    }

    file.close();
}

void viewStudents() {
    cout << "\nRegistered Students:\n";

    for (int i = 0; i < students.size(); i++) {
        cout << students[i].name << " - "
             << students[i].indexNumber << endl;
    }
}
int main() {
    loadStudentsFromFile();

    int choice;


    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while(choice != 3);

    return 0;
}

