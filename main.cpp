#include <iostream>
#include <string>
#include "PG.h"

using namespace std;

int main()
{
    // Array of PG objects (Max 20 PGs)
    PG pgList[20];
    int totalPG = 0;
    int choice;

    do
    {
        cout << "\n=============================================\n";
        cout << "   StayNear System (Bhimtal)\n";
        cout << "=============================================\n";
        cout << "1. Add New PG\n";
        cout << "2. Display All PGs\n";
        cout << "3. Search PG by College Name\n";
        cout << "4. Filter PGs by Rent Budget\n";
        cout << "5. Exit\n";
        cout << "=============================================\n";
        cout << "Enter Choice (1-5): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (totalPG < 20)
            {
                cout << "\n--- Enter Details for PG #" << (totalPG + 1) << " ---\n";
                pgList[totalPG].input();
                totalPG++;
                cout << "\nPG Added Successfully!\n";
            }
            else
            {
                cout << "\nMaximum PG Limit (20) Reached.\n";
            }
            break;

        case 2:
            if (totalPG == 0)
            {
                cout << "\nNo PGs Registered in Bhimtal Yet.\n";
            }
            else
            {
                cout << "\n--- Displaying All " << totalPG << " PGs in Bhimtal ---\n";
                for (int i = 0; i < totalPG; i++)
                {
                    cout << "\nPG Details #" << (i + 1) << endl;
                    pgList[i].display();
                }
            }
            break;

        case 3:
            if (totalPG == 0)
            {
                cout << "\nNo PGs Registered to Search.\n";
            }
            else
            {
                string searchCollege;
                cout << "\nEnter College Name to Search (e.g. Graphic Era / GEHU Bhimtal): ";
                getline(cin >> ws, searchCollege);

                bool found = false;
                cout << "\n--- Search Results for College: " << searchCollege << " ---\n";

                for (int i = 0; i < totalPG; i++)
                {
                    // Check if college name matches or contains keyword
                    if (pgList[i].getCollegeName().find(searchCollege) != string::npos)
                    {
                        pgList[i].display();
                        found = true;
                    }
                }

                if (!found)
                {
                    cout << "No PGs found near college: " << searchCollege << endl;
                }
            }
            break;

        case 4:
            if (totalPG == 0)
            {
                cout << "\nNo PGs Registered to Filter.\n";
            }
            else
            {
                int maxRent;
                cout << "\nEnter Maximum Rent Budget (Rs): ";
                cin >> maxRent;

                bool found = false;
                cout << "\n--- PGs within Budget Rs. " << maxRent << " ---\n";

                for (int i = 0; i < totalPG; i++)
                {
                    if (pgList[i].getRent() <= maxRent)
                    {
                        pgList[i].display();
                        found = true;
                    }
                }

                if (!found)
                {
                    cout << "No PGs found within budget Rs. " << maxRent << endl;
                }
            }
            break;

        case 5:
            cout << "\nThank You for Using StayNear System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Please enter a choice from 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}