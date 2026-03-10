#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX = 1000;

string patientNames[MAX];
int patientRooms[MAX];
int patientBeds[MAX];
int patientCount = 0;

void clearScreen() {
    system("cls");
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void design() {
    cout << "-------------------------------\n";
    cout << "|                             |\n";
    cout << "|  Hospital Room Designation  |\n";
    cout << "|                             |\n";
    cout << "-------------------------------\n";
}

// Add patient
void addPatient() {
    if(patientCount >= MAX) {
        cout << "Hospital is full!\n";
        return;
    }

    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, patientNames[patientCount]);
    cout << "Enter room number: ";
    cin >> patientRooms[patientCount];
    cout << "Enter bed number: ";
    cin >> patientBeds[patientCount];

    patientCount++;
    cout << "\nPatient added successfully!\n";
}

// Display all
void displayAll() {
    cout << "\n===== All Patients =====\n";
    if(patientCount == 0) {
        cout << "No patients found.\n";
        return;
    }

    for(int i = 0; i < patientCount; i++) {
        cout << i + 1 << ". " << patientNames[i]
             << " - Room " << patientRooms[i]
             << ", Bed " << patientBeds[i] << endl;
    }
}

// Linear search by name
void searchByName() {
    string name;
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, name);

    for(int i = 0; i < patientCount; i++) {
        if(patientNames[i] == name) {
            cout << "\nPatient found!\n";
            cout << "Name: " << patientNames[i] << endl;
            cout << "Room: " << patientRooms[i] << endl;
            cout << "Bed: " << patientBeds[i] << endl;
            return;
        }
    }
    cout << "Patient not found.\n";
}

// Binary search by room number
void searchByRoom() {
    int searchRoom;
    cout << "Enter room number to search: ";
    cin >> searchRoom;

    //sort by room (required for binary search)
    // Create temporary sorted arrays
    string tempNames[MAX];
    int tempRooms[MAX];
    int tempBeds[MAX];

    // Copy data to temp arrays
    for(int i = 0; i < patientCount; i++) {
        tempNames[i] = patientNames[i];
        tempRooms[i] = patientRooms[i];
        tempBeds[i] = patientBeds[i];
    }

    // Bubble sort by room
    for(int i = 0; i < patientCount - 1; i++) {
        for(int j = 0; j < patientCount - i - 1; j++) {
            if(tempRooms[j] > tempRooms[j + 1]) {
                // Swap rooms
                int tRoom = tempRooms[j];
                tempRooms[j] = tempRooms[j + 1];
                tempRooms[j + 1] = tRoom;

                // Swap names
                string tName = tempNames[j];
                tempNames[j] = tempNames[j + 1];
                tempNames[j + 1] = tName;

                // Swap beds
                int tBed = tempBeds[j];
                tempBeds[j] = tempBeds[j + 1];
                tempBeds[j + 1] = tBed;
            }
        }
    }

    // Binary search on sorted temp arrays
    int low = 0;
    int high = patientCount - 1;
    bool found = false;

    while(low <= high) {
        int mid = (low + high) / 2;

        if(tempRooms[mid] == searchRoom) {
            // Found! Display all patients in this room
            cout << "\n===== Patients in Room " << searchRoom << " =====\n";

            // Display all patients in this room
            int count = 0;
            for(int i = 0; i < patientCount; i++) {
                if(tempRooms[i] == searchRoom) {
                    cout << "- " << tempNames[i]
                         << " (Bed " << tempBeds[i] << ")\n";
                    count++;
                }
            }

            if(count == 0) {
                cout << "No patients in this room.\n";
            }

            found = true;
            break;
        }
        else if(searchRoom < tempRooms[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    if(!found) {
        cout << "\nRoom " << searchRoom << " not found.\n";
    }
}

// Bubble sort by room number
void sortByRoom() {
    for(int i = 0; i < patientCount - 1; i++) {
        for(int j = 0; j < patientCount - i - 1; j++) {
            if(patientRooms[j] > patientRooms[j + 1]) {
                // Swap room numbers
                int tempRoom = patientRooms[j];
                patientRooms[j] = patientRooms[j + 1];
                patientRooms[j + 1] = tempRoom;

                // Swap names
                string tempName = patientNames[j];
                patientNames[j] = patientNames[j + 1];
                patientNames[j + 1] = tempName;

                // Swap beds
                int tempBed = patientBeds[j];
                patientBeds[j] = patientBeds[j + 1];
                patientBeds[j + 1] = tempBed;
            }
        }
    }
    cout << "\nSorted by room number!\n";
    displayAll();
}

int main() {
    int choice;

    do {
        clearScreen();
        design();
        cout << "[1] Add Patient\n";
        cout << "[2] Display All Patients\n";
        cout << "[3] Search by Name\n"; //linear search
        cout << "[4] Search by Room\n"; //binary search
        cout << "[5] Sort by Room Number\n";
        cout << "[0] Exit\n";
        cout << "\nEnter the number option: ";
        cin >> choice;

        clearScreen();

        switch(choice) {
            case 1:
                addPatient();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                searchByName();
                break;
            case 4:
                searchByRoom();
                break;
            case 5:
                sortByRoom();
                break;
            case 0:
                cout << "Program ended. Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

        if(choice != 0) pause();

    } while(choice != 0);

    return 0;
}
