#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Student {
public:
    string name;
    int roll;
    float marks;

    void input() {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter roll number: ";
        cin >> roll;
        cout << "Enter marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "Name: " << name << "\nRoll: " << roll << "\nMarks: " << marks << "\n";
    }

    // Save to file
    void save(ofstream& outFile) const {
        outFile << name << "\n" << roll << "\n" << marks << "\n";
    }

    // Load from file
    static Student load(ifstream& inFile) {
        Student s;
        getline(inFile, s.name);
        inFile >> s.roll >> s.marks;
        inFile.ignore();  // consume newline after marks
        return s;
    }
};

// Menu-driven student manager
void studentManager() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n📘 Student Management Menu:\n";
        cout << "1. Add Student\n2. Display All\n3. Save to File\n4. Load from File\n5. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    Student s;
                    s.input();
                    students.push_back(s);
                    break;
                }
                case 2:
                    for (const auto& s : students) {
                        s.display();
                        cout << "------------\n";
                    }
                    break;

                case 3: {
                    ofstream outFile("students.txt");
                    if (!outFile) throw runtime_error("Error opening file to write.");
                    for (const auto& s : students)
                        s.save(outFile);
                    outFile.close();
                    cout << "✅ Data saved to students.txt\n";
                    break;
                }

                case 4: {
                    ifstream inFile("students.txt");
                    if (!inFile) throw runtime_error("Error opening file to read.");
                    students.clear();
                    while (!inFile.eof()) {
                        string check;
                        getline(inFile, check);
                        if (check.empty()) break;
                        inFile.seekg(-check.length() - 1, ios::cur);
                        Student s = Student::load(inFile);
                        students.push_back(s);
                    }
                    inFile.close();
                    cout << "✅ Data loaded from students.txt\n";
                    break;
                }

                case 5:
                    cout << "👋 Exiting...\n";
                    break;

                default:
                    cout << "❌ Invalid choice.\n";
            }
        } catch (const exception& e) {
            cerr << "⚠️ Error: " << e.what() << endl;
        }

    } while (choice != 5);
}

int main() {
    studentManager();
    return 0;
}
