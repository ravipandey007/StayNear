/*
 * ====================================================================================
 *   Project Name : StayNear - Bhimtal Student PG Management System
 *   File Name    : main.cpp (Modular Project Entry Point)
 *   Description  : Demonstrates full OOP in C++ by connecting Person, Student, Owner,
 *                  Room, and PG classes together with an interactive console menu.
 * ====================================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "PG.h"

using namespace std;

// Helper function to pre-load sample Bhimtal PGs for testing
void seedSampleData(vector<PG> &pgList)
{
    // PG 1: Himalayan Breeze PG (Near Graphic Era Bhimtal)
    PG pg1("Himalayan Breeze PG", "Graphic Era Hill University Bhimtal", "Bhowali Road, Bhimtal", "Boys", 5500, 4.6f);
    pg1.setOwner(Owner("Rajesh Joshi", "+91 9876543210", "rajesh.joshi@email.com"));

    Room r1(101, 2);
    r1.addStudent(Student("Rahul Sharma", "9876500001", "B.Tech CSE", 2));
    pg1.addRoom(r1);

    Room r2(102, 3);
    r2.addStudent(Student("Amit Verma", "9876500002", "BCA", 1));
    r2.addStudent(Student("Rohit Singh", "9876500003", "B.Tech ME", 3));
    pg1.addRoom(r2);

    Room r3(103, 2); // 2 empty beds
    pg1.addRoom(r3);
    pgList.push_back(pg1);

    // PG 2: Pine Crest Girls PG (Near Graphic Era Bhimtal)
    PG pg2("Pine Crest Girls PG", "Graphic Era Hill University Bhimtal", "June Estate, Bhimtal", "Girls", 6500, 4.8f);
    pg2.setOwner(Owner("Sunita Bisht", "+91 9812345678", "sunita.bisht@email.com"));

    Room r4(201, 2);
    r4.addStudent(Student("Priya Mehra", "9812300001", "B.Tech CSE", 3));
    r4.addStudent(Student("Ananya Arya", "9812300002", "BBA", 2));
    pg2.addRoom(r4);

    Room r5(202, 2);
    r5.addStudent(Student("Divya Pant", "9812300003", "B.Tech AI", 1));
    pg2.addRoom(r5);
    pgList.push_back(pg2);

    // PG 3: Lake View Residency (Near BIAS Bhimtal)
    PG pg3("Lake View Residency", "Birla Institute of Applied Sciences (BIAS)", "Mallital, Bhimtal", "Co-Ed", 7000, 4.5f);
    pg3.setOwner(Owner("Mahesh Tiwari", "+91 9755544433", "mahesh.tiwari@email.com"));

    Room r6(301, 2);
    r6.addStudent(Student("Karan Negi", "9755500001", "MCA", 2));
    pg3.addRoom(r6);

    Room r7(302, 2); // 2 empty beds
    pg3.addRoom(r7);
    pgList.push_back(pg3);
}

int main()
{
    vector<PG> pgList;
    seedSampleData(pgList); // Pre-load sample data for quick demonstration

    int choice;

    do
    {
        cout << "\n=============================================\n";
        cout << "   StayNear - Student PG Management System   \n";
        cout << "          (Bhimtal, Uttarakhand)             \n";
        cout << "=============================================\n";
        cout << "1. Add New PG\n";
        cout << "2. Display All PGs\n";
        cout << "3. Search PG by College Name\n";
        cout << "4. Filter PGs by Rent Budget\n";
        cout << "5. View Bed Availability Tracker\n";
        cout << "6. Inspect Rooms & Students in a PG\n";
        cout << "7. Exit\n";
        cout << "=============================================\n";
        cout << "Enter Choice (1-7): ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 7.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            cout << "\n--- Enter Details for New PG ---\n";
            PG newPg;
            newPg.input();
            pgList.push_back(newPg);
            cout << "\n[SUCCESS] PG Added Successfully!\n";
            break;
        }

        case 2:
        {
            if (pgList.empty())
            {
                cout << "\nNo PGs registered yet.\n";
            }
            else
            {
                cout << "\n--- Displaying All " << pgList.size() << " Registered PGs ---\n";
                for (size_t i = 0; i < pgList.size(); i++)
                {
                    cout << "\n[PG #" << (i + 1) << "]";
                    pgList[i].display();
                }
            }
            break;
        }

        case 3:
        {
            if (pgList.empty())
            {
                cout << "\nNo PGs registered to search.\n";
                break;
            }

            string searchCollege;
            cout << "\nEnter College Name to Search (e.g. Graphic Era / GEHU / BIAS): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchCollege);

            bool found = false;
            cout << "\n--- Search Results for: \"" << searchCollege << "\" ---\n";
            for (size_t i = 0; i < pgList.size(); i++)
            {
                if (pgList[i].getCollegeName().find(searchCollege) != string::npos)
                {
                    pgList[i].display();
                    found = true;
                }
            }

            if (!found)
            {
                cout << "No PGs found near college: \"" << searchCollege << "\"\n";
            }
            break;
        }

        case 4:
        {
            if (pgList.empty())
            {
                cout << "\nNo PGs registered to filter.\n";
                break;
            }

            int maxRent;
            cout << "\nEnter Maximum Monthly Rent Budget (Rs): ";
            cin >> maxRent;

            bool found = false;
            cout << "\n--- PGs within Budget Rs. " << maxRent << " ---\n";
            for (size_t i = 0; i < pgList.size(); i++)
            {
                if (pgList[i].getRent() <= maxRent)
                {
                    pgList[i].display();
                    found = true;
                }
            }

            if (!found)
            {
                cout << "No PGs found within budget Rs. " << maxRent << "\n";
            }
            break;
        }

        case 5:
        {
            int totalBeds = 0;
            int occupiedBeds = 0;
            int availableBeds = 0;

            for (size_t i = 0; i < pgList.size(); i++)
            {
                totalBeds += pgList[i].getTotalBedsCount();
                occupiedBeds += pgList[i].getOccupiedBedsCount();
                availableBeds += pgList[i].getAvailableBedsCount();
            }

            cout << "\n=============================================\n";
            cout << "       Bhimtal Bed Tracker Summary           \n";
            cout << "=============================================\n";
            cout << "Total Registered PGs : " << pgList.size() << "\n";
            cout << "Total Beds           : " << totalBeds << "\n";
            cout << "Occupied Beds        : " << occupiedBeds << "\n";
            cout << "Available Beds       : " << availableBeds << "\n";
            cout << "=============================================\n";
            break;
        }

        case 6:
        {
            if (pgList.empty())
            {
                cout << "\nNo PGs registered.\n";
                break;
            }

            cout << "\nSelect PG to Inspect:\n";
            for (size_t i = 0; i < pgList.size(); i++)
            {
                cout << (i + 1) << ". " << pgList[i].getPGName() << " (" << pgList[i].getLocation() << ")\n";
            }
            cout << "Enter Choice (1-" << pgList.size() << "): ";
            size_t sel;
            cin >> sel;

            if (sel >= 1 && sel <= pgList.size())
            {
                const PG &pg = pgList[sel - 1];
                cout << "\n--- Rooms in " << pg.getPGName() << " ---\n";
                const auto &rooms = pg.getRooms();
                for (size_t r = 0; r < rooms.size(); r++)
                {
                    rooms[r].display();
                }
            }
            else
            {
                cout << "Invalid selection.\n";
            }
            break;
        }

        case 7:
            cout << "\nThank you for using StayNear System! Exiting.\n";
            break;

        default:
            cout << "\nInvalid Choice! Please enter a number between 1 and 7.\n";
        }

    } while (choice != 7);

    return 0;
}
