#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>   // added for timestamp
using namespace std;

// =====================
// PERSON CLASS
// =====================
class Person {
public:
    string name;
    int age;

    Person(string n, int a) {
        name = n;
        age = a;
    }
};

// =====================
// CASE CLASS
// =====================
class Case {
public:
    string caseID;
    string FIR;
    string type;

    vector<Person> victims;
    vector<Person> suspects;
    vector<string> evidence;

    Person officer = Person("None", 0);

    // Constructor
    Case(string id, string fir, string t) {
        caseID = id;
        FIR = fir;
        type = t;
    }

    void addVictim(string name, int age) {
        victims.push_back(Person(name, age));
    }

    void addSuspect(string name, int age) {
        suspects.push_back(Person(name, age));
    }

    void addEvidence(string e) {
        evidence.push_back(e);
    }

    void assignOfficer(string name, int age) {
        officer = Person(name, age);
    }

    // Generate Report
    void generateReport() {
        ofstream file("Report_" + caseID + ".txt");

        // timestamp added
        time_t now = time(0);
        char* dt = ctime(&now);

        // dramatic header added
        file << "===== POLICE INVESTIGATION REPORT =====\n";
        file << "Date: " << dt;

        file << "Case ID: " << caseID << endl;
        file << "FIR: " << FIR << endl;
        file << "Type: " << type << endl;

        file << "\nVictims:\n";
        for (auto v : victims)
            file << v.name << " (" << v.age << ")\n";

        file << "\nSuspects:\n";
        for (auto s : suspects)
            file << s.name << " (" << s.age << ")\n";

        file << "\nEvidence:\n";
        for (auto e : evidence)
            file << e << endl;

        file << "\nOfficer:\n";
        file << officer.name << " (" << officer.age << ")\n";

        file.close();
    }
};

// =====================
// MAIN FUNCTION
// =====================
int main() {
    string id, fir, type;

    cout << "Enter Case ID: ";
    getline(cin, id);

    cout << "Enter FIR: ";
    getline(cin, fir);

    cout << "Enter Type: ";
    getline(cin, type);

    Case c(id, fir, type);

    int n;

    cout << "Number of victims: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name;
        int age;
        cout << "Name: ";
        cin >> name;
        cout << "Age: ";
        cin >> age;
        c.addVictim(name, age);
    }

    cout << "Number of suspects: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name;
        int age;
        cout << "Name: ";
        cin >> name;
        cout << "Age: ";
        cin >> age;
        c.addSuspect(name, age);
    }

    cin.ignore();

    cout << "Number of evidence: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string e;
        cout << "Evidence: ";
        getline(cin, e);
        c.addEvidence(e);
    }

    string officerName;
    int officerAge;

    cout << "Officer name: ";
    getline(cin, officerName);

    cout << "Officer age: ";
    cin >> officerAge;

    c.assignOfficer(officerName, officerAge);

    c.generateReport();

    cout << "Report Generated!\n";

    return 0;
}
