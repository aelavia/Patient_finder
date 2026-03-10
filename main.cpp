#include <iostream>
#include <string>

using namespace std;

    const int ROOMS = 5;
    const int beds = 3;


    //func. prototype
    void design();
    void searchRoom(string roomBed[][beds], int room[]);
     string searchName(string roomBed[][beds], int room[]);



int main()

{
   // Static patient data
    string roomBed[ROOMS][beds] = {
        {"Maria Santos", "Juan Cruz", ""},
        {"Ana Reyes", "", "Pedro Garcia"},
        {"Sofia Lopez", "Carlos Mendoza", "Luisa Torres"},
        {"", "Miguel Ramos", "Elena Flores"},
        {"Diego Morales", "", "Carmen Silva"}
    };

    int room[ROOMS] = {101, 102, 103, 104, 105};

    int choice;


    design();

    do{
        cout << "\n[1] search patient\n";
        cout << "[0] Exit\n";

        cout << "\nEnter number of option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n[1] search by name\n";
            cout << "[2] search by room number\n";
            int pinili;
            cout << "\nEnter number: ";
            cin >> pinili;
                if (pinili == 1) {
                    searchName(roomBed, room);
                } else if (pinili == 2) {
                searchRoom(roomBed, room);
                } else {
                cout << "Invalid Input.";
                }

        } else if (choice == 0) {
            cout << "Program ended.\n";
        }
        else {
            cout << "Invalid input.\n";
        }

    } while (choice != 0);

    cout << "Thank you for using this program\n";



    return 0;
}

//func. definition

    void design() {
    cout << "-------------------------------\n";
    cout << "|                              |\n";
    cout << "|  Hospital room designation   |\n";
    cout << "|                              |\n";
    cout << "-------------------------------\n";
    }


// search by name using SEQUENCIAL SEARCH
    string searchName(string roomBed[][beds], int room[]) {
        string name;

        cout << "Enter Patiet name to search: ";
        cin.ignore();
        getline(cin, name);

        bool found = false;
        for (int r = 0; r < ROOMS; r++) {
            for (int c = 0; c < beds; c++) {
                if (roomBed[r][c]== name) {
                    cout << "\nPatient Found!";
                    cout << "\nName: " << name;
                    cout << "\nRoom: " << room[r];
                    cout << "\nBed: " << c + 1 << endl;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "Patient not found.\n";
        }
    }

//search by room bumber using BINARY SEARCH
    void searchRoom(string roomBed[][beds], int room[]) {
    int roomNo;


    cout << "Enter room number (101-105): ";
    cin >> roomNo;

    int low = 0;
    int high = ROOMS - 1;
    int index = -1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (room[mid] == roomNo) {
            index = mid;
            break;
        } else if (roomNo < room[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    if(index == -1) {
        cout << "Room not found.\n";
        return;
    }

    cout << "\nPatients in Room " << roomNo << ":\n";
    for(int i = 0; i < beds; i++) {
        if(roomBed[index][i] != "")
            cout << "Bed " << i + 1 << ": " << roomBed[index][i] << endl;
        else
            cout << "Bed " << i + 1 << ": Empty\n";
    }
}
