#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

using namespace std;

    const int COL = 3;

//func. prototype
    void header();
    int menu();
    void displayPatients(int roomBed[][COL], string name[][COL], int id[][COL], int row, int col);
    int searchByRoom(int roomBed[][COL], int row, int col, int searchBed);
    int searchByName(string name[][COL], int row, int col, string searchName);
    int searchByID(int id[][COL], int row, int col, int searchID, bool sortedByID);
    void displayResult(int roomBed[][COL], string name[][COL], int id[][COL], int col, int result);

int main(){
    const int ROOMS = 5;
    const int BEDS  = 3;
    int roomBed[ROOMS][BEDS] = {{101, 102, 103},
                                {201, 202, 203},
                                {301, 302, 303},
                                {401, 402, 403},
                                {501, 502, 503}};
    string patientName[ROOMS][BEDS] = {{"Maria Clara", "Juanito",    "Theresa"},
                                       {"Blessilda",   "Jose",       "Christine"},
                                       {"Joy",         "Rogelio",    "Baby"},
                                       {"Rafael",      "Luningning", "Jeff"},
                                       {"Marites",     "Maria",      "Junjun"}};
    int patientID[ROOMS][BEDS] = {{305, 112, 408},
                                  {207, 501, 103},
                                  {404, 216, 310},
                                  {502, 109, 413},
                                  {201, 315, 406}};
    int choice, result;
    int total = ROOMS * BEDS;
    bool sortedByID = false;
    char again;

    do {
        header();
        choice = menu();

        switch(choice){
            case 1:
                displayPatients(roomBed, patientName, patientID, ROOMS, BEDS);
                break;

            case 2:
                do {
                    int searchRoom, searchBedSlot;
                    cout << "------------------------------" << endl;
                    cout << "Search Patient by Room/Bed" << endl;
                    cout << "\nRoom No.: ";
                    cin >> searchRoom;
                    cout << "Bed No. (1-" << BEDS << "): ";
                    cin >> searchBedSlot;
                    cin.ignore();

                    int searchBed = searchRoom * 100 + searchBedSlot;
                    result = searchByRoom(roomBed, ROOMS, BEDS, searchBed);
                    displayResult(roomBed, patientName, patientID, BEDS, result);

                    cout << "Do you want to search again? (Y/N): ";
                    cin >> again;
                    cin.ignore();
                    system("cls");
                } while(again == 'Y' || again == 'y');
                break;

            case 3:
                do {
                    string searchName;
                    cout << "------------------------------" << endl;
                    cout << "Search Patient by Name" << endl;
                    cout << "\nEnter Patient Name: ";
                    getline(cin, searchName);

                    result = searchByName(patientName, ROOMS, BEDS, searchName);
                    displayResult(roomBed, patientName, patientID, BEDS, result);

                    cout << "Do you want to search again? (Y/N): ";
                    cin >> again;
                    cin.ignore();
                    system("cls");
                } while(again == 'Y' || again == 'y');
                break;

            case 4:
                do {
                    int searchID;
                    cout << "------------------------------" << endl;
                    cout << "Search Patient by ID" << endl;
                    cout << "\nEnter Patient ID: ";
                    cin >> searchID;
                    cin.ignore();

                    result = searchByID(patientID, ROOMS, BEDS, searchID, sortedByID);
                    displayResult(roomBed, patientName, patientID, BEDS, result);

                    cout << "Do you want to search again? (Y/N): ";
                    cin >> again;
                    cin.ignore();
                    system("cls");
                } while(again == 'Y' || again == 'y');
                break;

            case 5:
                sortedByID = true;
                for(int i = 0; i < total - 1; i++){
                    for(int j = 0; j < total - 1 - i; j++){
                        int r1 = j / BEDS,     c1 = j % BEDS;
                        int r2 = (j+1) / BEDS, c2 = (j+1) % BEDS;

                        if(patientID[r1][c1] > patientID[r2][c2]){
                            string tempName     = patientName[r1][c1];
                            patientName[r1][c1] = patientName[r2][c2];
                            patientName[r2][c2] = tempName;

                            int tempID        = patientID[r1][c1];
                            patientID[r1][c1] = patientID[r2][c2];
                            patientID[r2][c2] = tempID;

                            int tempBed     = roomBed[r1][c1];
                            roomBed[r1][c1] = roomBed[r2][c2];
                            roomBed[r2][c2] = tempBed;
                        }
                    }
                }
                cout << "\nPatients sorted by ID successfully." << endl;
                break;

            case 6:
                cout << "\nThank you for using Patient Finder." << endl;
                break;

            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }

    } while(choice != 6);

    return 0;
}

// func. def

void header(){
    cout << "===============================================" << endl;
    cout << "-------         PATIENT FINDER           ------" << endl;
    cout << "===============================================" << endl;
}

int menu(){
    cout << "[1] View Patients List"          << endl;
    cout << "[2] Search Patient by Room/Bed"  << endl;
    cout << "[3] Search Patient by Name"      << endl;
    cout << "[4] Search Patient by ID"        << endl;
    cout << "[5] Sort Patients by ID"         << endl;
    cout << "[6] Exit"                        << endl;

    int choice = 0;
    cout << "\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    return choice;
}

void displayPatients(int roomBed[][COL], string name[][COL], int id[][COL], int row, int col){
    cout << "------------------------------" << endl;
    cout << "View Patients List" << endl;
    cout << "\n========================================" << endl;
    cout << left << setw(6) << "ID" << setw(17) << "Name" << setw(11) << "Room No." << "Bed No." << endl;
    cout << "----------------------------------------" << endl;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << left << setw(6) << id[i][j] << setw(20) << name[i][j] << setw(10) << roomBed[i][j] / 100 << roomBed[i][j] << endl;
        }
    cout << "----------------------------------------" << endl;

    }
    cout << endl;
}
// seq. search
int searchByRoom(int roomBed[][COL], int row, int col, int searchBed){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(roomBed[i][j] == searchBed)
                return i * col + j;
        }
    }
    return -1;
}

// seq. search
int searchByName(string name[][COL], int row, int col, string searchName){
    int searchLen = searchName.size();
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int nameLen = name[i][j].size();
            if(nameLen == searchLen && name[i][j] == searchName)
                return i * col + j;
        }
    }
    return -1;
}

// seq/binary search
int searchByID(int id[][COL], int row, int col, int searchID, bool sortedByID){
    if(sortedByID){
        // Binary search - only valid when sorted by ID
        int total = row * col;
        int low = 0, high = total - 1;

        while(low <= high){
            int mid = (low + high) / 2;
            int r = mid / col, c = mid % col;

            if(id[r][c] == searchID){
                return mid;
            } else if(id[r][c] < searchID){
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    } else {
        // Sequential search
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                if(id[i][j] == searchID)
                    return i * col + j;
            }
        }
    }
    return -1;
}

void displayResult(int roomBed[][COL], string name[][COL], int id[][COL], int col, int result){
    if(result != -1){
        int r = result / col, c = result % col;
        cout << "\nPatient Found!" << endl;
        cout << "Name: "      << name[r][c]           << endl;
        cout << "ID: "        << id[r][c]              << endl;
        cout << "Room No.: "  << roomBed[r][c] / 100   << endl;
        cout << "Bed No.: "   << roomBed[r][c]          << endl;
    } else {
        cout << "\nNo patient found." << endl;
    }
    cout << endl;
}

