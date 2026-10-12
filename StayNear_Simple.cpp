/*
 * ====================================================================================
 *   Project Name : StayNear - Bhimtal Student PG Management System
 *   Description  : A Beginner-Friendly Object-Oriented Programming (OOP) C++ Project
 *                  Specially designed for College / University Evaluation & Viva
 *   
 *   OOP Concepts Demonstrated:
 *      1. Encapsulation  - Private & protected attributes with public getters/setters
 *      2. Inheritance    - Person (Base) -> Student & Owner (Derived)
 *      3. Polymorphism   - Virtual display() method overridden in child classes
 *      4. Composition    - Room HAS-A Students; PG HAS-A Owner and Rooms
 *      5. Dynamic Memory - std::vector for safe, modern list management
 *
 *   How to Compile and Run:
 *      g++ -std=c++17 StayNear_Simple.cpp -o StayNear_Simple.exe
 *      .\StayNear_Simple.exe
 * ====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// ====================================================================================
// SECTION 1: BASE CLASS - Person
// OOP Concept: ENCAPSULATION & BASE OF INHERITANCE
// ====================================================================================
class Person
{
protected:
    // Protected variables: Accessible by child classes (Student, Owner)
    // but hidden from outside functions.
    string name;
    string phone;

public:
    // Default Constructor: Sets default empty values
    Person()
    {
        name = "";
        phone = "";
    }

    // Parameterized Constructor: Sets name and phone
    Person(const string &name, const string &phone)
    {
        this->name = name;
        this->phone = phone;
    }

    // Virtual Destructor: Ensures proper cleanup when deleting derived objects
    virtual ~Person() = default;

    // Takes common personal details from the user
    void inputPerson()
    {
        cout << "Enter Name: ";
        getline(cin >> ws, name); // Discards leading whitespace

        cout << "Enter Phone Number: ";
        getline(cin >> ws, phone);
    }

    // Virtual Display method: Demonstrates Runtime Polymorphism
    virtual void display() const
    {
        cout << "Name  : " << name << endl;
        cout << "Phone : " << phone << endl;
    }

    // Getters: Read-only access to protected data
    string getName() const { return name; }
    string getPhone() const { return phone; }

    // Setters: Controlled modification of protected data
    void setName(const string &n) { name = n; }
    void setPhone(const string &p) { phone = p; }
};

// ====================================================================================
// SECTION 2: DERIVED CLASS - Student
// OOP Concept: INHERITANCE (Student IS-A Person) & POLYMORPHISM (Method Overriding)
// ====================================================================================
class Student : public Person
{
private:
    string course; // e.g. "B.Tech CSE", "BCA"
    int year;      // Academic year (1, 2, 3, or 4)

public:
    // Default Constructor: Calls base class default constructor
    Student() : Person()
    {
        course = "";
        year = 0;
    }

    // Parameterized Constructor: Passes (name, phone) to Person constructor
    Student(const string &name, const string &phone, const string &course, int year)
        : Person(name, phone)
    {
        this->course = course;
        this->year = year;
    }

    // Input method: Reuses base class inputPerson(), then asks student details
    void input()
    {
        inputPerson(); // Reusing Base Class method
        cout << "Enter Course (e.g. B.Tech CSE / BCA): ";
        getline(cin >> ws, course);
        cout << "Enter Year of Study (1-4): ";
        cin >> year;
    }

    // Overridden display method: Shows student information cleanly
    void display() const override
    {
        cout << "    - Student: " << name 
             << " | Phone: " << phone 
             << " | Course: " << course 
             << " | Year: " << year << endl;
    }

    // Getters and Setters
    string getCourse() const { return course; }
    int getYear() const { return year; }
    void setCourse(const string &c) { course = c; }
    void setYear(int y) { year = y; }
};

// ====================================================================================
// SECTION 3: DERIVED CLASS - Owner
// OOP Concept: INHERITANCE (Owner IS-A Person) & POLYMORPHISM (Method Overriding)
// ====================================================================================
class Owner : public Person
{
private:
    string email; // Owner contact email

public:
    // Default Constructor
    Owner() : Person()
    {
        email = "";
    }

    // Parameterized Constructor: Passes (name, phone) to Person constructor
    Owner(const string &name, const string &phone, const string &email)
        : Person(name, phone)
    {
        this->email = email;
    }

    // Input method: Reuses base class inputPerson(), then asks for email
    void input()
    {
        cout << "\n--- Enter PG Owner Details ---\n";
        inputPerson(); // Reusing Base Class method
        cout << "Enter Owner Email: ";
        getline(cin >> ws, email);
    }

    // Overridden display method: Shows owner information cleanly
    void display() const override
    {
        cout << "\nOwner Name    : " << name;
        cout << "\nOwner Contact : " << phone;
        cout << "\nOwner Email   : " << email << endl;
    }

    // Getters and Setters
    string getEmail() const { return email; }
    void setEmail(const string &e) { email = e; }
};

// ====================================================================================
// SECTION 4: CLASS - Room
// OOP Concept: COMPOSITION (Room HAS-A collection of Students)
// ====================================================================================
class Room
{
private:
    int roomNumber;
    int totalBeds;
    int occupiedBeds;
    vector<Student> students; // Composition: List of students residing in this room

public:
    // Default Constructor
    Room()
    {
        roomNumber = 0;
        totalBeds = 0;
        occupiedBeds = 0;
    }

    // Parameterized Constructor
    Room(int roomNumber, int totalBeds)
    {
        this->roomNumber = roomNumber;
        this->totalBeds = totalBeds;
        this->occupiedBeds = 0;
    }

    // Input room details and all its student occupants
    void input()
    {
        cout << "\nEnter Room Number: ";
        cin >> roomNumber;
        cout << "Enter Total Beds: ";
        cin >> totalBeds;
        cout << "Enter Occupied Beds: ";
        cin >> occupiedBeds;

        // Validation check
        if (occupiedBeds > totalBeds)
        {
            cout << "Occupied beds cannot exceed total capacity. Setting occupied to " << totalBeds << endl;
            occupiedBeds = totalBeds;
        }

        students.clear();
        for (int i = 0; i < occupiedBeds; i++)
        {
            cout << "\n--- Student " << (i + 1) << " in Room #" << roomNumber << " ---\n";
            Student s;
            s.input();
            students.push_back(s);
        }
    }

    // Displays room status and occupants
    void display() const
    {
        cout << "\n  Room #" << roomNumber 
             << " | Total Beds: " << totalBeds 
             << " | Occupied: " << occupiedBeds 
             << " | Available: " << getAvailableBeds() << endl;

        for (size_t i = 0; i < students.size(); i++)
        {
            students[i].display();
        }
    }

    // Getters
    int getRoomNumber() const { return roomNumber; }
    int getTotalBeds() const { return totalBeds; }
    int getOccupiedBeds() const { return occupiedBeds; }
    int getAvailableBeds() const { return totalBeds - occupiedBeds; }
    const vector<Student>& getStudents() const { return students; }

    // Adds a student to room if a bed is available
    bool addStudent(const Student &s)
    {
        if (occupiedBeds >= totalBeds)
        {
            return false; // Room full
        }
        students.push_back(s);
        occupiedBeds++;
        return true;
    }
};

// ====================================================================================
// SECTION 5: CLASS - PG (Paying Guest Accommodation)
// OOP Concept: COMPOSITION (PG HAS-A Owner and PG HAS-A Rooms)
// ====================================================================================
class PG
{
private:
    string pgName;
    string collegeName;
    string location;
    string pgType; // "Boys", "Girls", "Co-Ed"
    int rent;      // Monthly rent in INR
    float rating;  // Rating out of 5.0

    Owner owner;         // Composition: Owner instance inside PG
    vector<Room> rooms;  // Composition: Vector of Room objects inside PG

public:
    // Default Constructor
    PG()
    {
        pgName = "";
        collegeName = "Graphic Era Hill University Bhimtal";
        location = "Bhimtal, Uttarakhand";
        pgType = "Boys";
        rent = 0;
        rating = 0.0f;
    }

    // Parameterized Constructor
    PG(string name, string college, string loc, string type, int rentVal, float ratingVal)
    {
        pgName = name;
        collegeName = college;
        location = loc;
        pgType = type;
        rent = rentVal;
        rating = ratingVal;
    }

    // Takes input for PG details, Owner, and all Rooms
    void input()
    {
        cout << "\nEnter PG Name: ";
        getline(cin >> ws, pgName);

        cout << "Enter Nearby College (e.g. Graphic Era Hill University Bhimtal): ";
        getline(cin >> ws, collegeName);

        cout << "Enter Location in Bhimtal (e.g. Bhowali Road / June Estate): ";
        getline(cin >> ws, location);

        cout << "Enter PG Type (Boys / Girls / Co-Ed): ";
        getline(cin >> ws, pgType);

        cout << "Enter Monthly Rent per bed (in Rs): ";
        cin >> rent;

        cout << "Enter Rating (0.0 to 5.0): ";
        cin >> rating;

        // Input Owner details
        owner.input();

        // Input Room details
        int roomCount;
        cout << "\nEnter Total Number of Rooms in PG: ";
        cin >> roomCount;

        rooms.clear();
        for (int i = 0; i < roomCount; i++)
        {
            cout << "\n=== ROOM " << (i + 1) << " ===\n";
            Room r;
            r.input();
            rooms.push_back(r);
        }
    }

    // Displays all details of the PG, its owner, and rooms
    void display() const
    {
        cout << "\n==========================================";
        cout << "\nPG Name       : " << pgName;
        cout << "\nCollege       : " << collegeName;
        cout << "\nLocation      : " << location;
        cout << "\nPG Type       : " << pgType;
        cout << "\nMonthly Rent  : Rs. " << rent;
        cout << "\nRating        : " << rating << " / 5.0";

        owner.display();

        cout << "\nTotal Rooms   : " << rooms.size();
        cout << "\nAvailable Beds: " << getAvailableBedsCount() << endl;

        for (size_t i = 0; i < rooms.size(); i++)
        {
            rooms[i].display();
        }
        cout << "==========================================\n";
    }

    // Getters
    string getPGName() const { return pgName; }
    string getCollegeName() const { return collegeName; }
    string getLocation() const { return location; }
    string getPGType() const { return pgType; }
    int getRent() const { return rent; }
    float getRating() const { return rating; }

    // Aggregate bed calculations
    int getAvailableBedsCount() const
    {
        int count = 0;
        for (size_t i = 0; i < rooms.size(); i++)
            count += rooms[i].getAvailableBeds();
        return count;
    }

    int getTotalBedsCount() const
    {
        int count = 0;
        for (size_t i = 0; i < rooms.size(); i++)
            count += rooms[i].getTotalBeds();
        return count;
    }

    int getOccupiedBedsCount() const
    {
        int count = 0;
        for (size_t i = 0; i < rooms.size(); i++)
            count += rooms[i].getOccupiedBeds();
        return count;
    }

    int getTotalRooms() const { return static_cast<int>(rooms.size()); }
    const vector<Room>& getRooms() const { return rooms; }
    const Owner& getOwner() const { return owner; }

    // Setters
    void setOwner(const Owner &o) { owner = o; }
    void addRoom(const Room &r) { rooms.push_back(r); }
};

// ====================================================================================
// SECTION 6: SAMPLE DATA PRE-LOADER
// Helper function to pre-load sample Bhimtal PGs for quick testing & demonstration
// ====================================================================================
void seedSampleData(vector<PG> &pgList)
{
    // 1. Himalayan Breeze PG (Near Graphic Era Bhimtal)
    PG pg1("Himalayan Breeze PG", "Graphic Era Hill University Bhimtal", "Bhowali Road, Bhimtal", "Boys", 5500, 4.6f);
    pg1.setOwner(Owner("Rajesh Joshi", "+91 9876543210", "rajesh.joshi@email.com"));

    Room r1(101, 2);
    r1.addStudent(Student("Rahul Sharma", "9876500001", "B.Tech CSE", 2));
    pg1.addRoom(r1);

    Room r2(102, 3);
    r2.addStudent(Student("Amit Verma", "9876500002", "BCA", 1));
    r2.addStudent(Student("Rohit Singh", "9876500003", "B.Tech ME", 3));
    pg1.addRoom(r2);

    Room r3(103, 2); // 2 beds available
    pg1.addRoom(r3);
    pgList.push_back(pg1);

    // 2. Pine Crest Girls PG (Near Graphic Era Bhimtal)
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

    // 3. Lake View Residency (Near BIAS Bhimtal)
    PG pg3("Lake View Residency", "Birla Institute of Applied Sciences (BIAS)", "Mallital, Bhimtal", "Co-Ed", 7000, 4.5f);
    pg3.setOwner(Owner("Mahesh Tiwari", "+91 9755544433", "mahesh.tiwari@email.com"));

    Room r6(301, 2);
    r6.addStudent(Student("Karan Negi", "9755500001", "MCA", 2));
    pg3.addRoom(r6);

    Room r7(302, 2); // 2 beds available
    pg3.addRoom(r7);
    pgList.push_back(pg3);
}

// ====================================================================================
// SECTION 7: MAIN PROGRAM - Interactive Console Menu
// ====================================================================================
int main()
{
    vector<PG> pgList;
    seedSampleData(pgList); // Pre-load demo PGs so testing is immediate

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

        // Safe integer input handling
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 7.\n";
            continue;
        }

        switch (choice)
        {
        // 1. Add New PG
        case 1:
        {
            cout << "\n--- Enter Details for New PG ---\n";
            PG newPg;
            newPg.input();
            pgList.push_back(newPg);
            cout << "\n[SUCCESS] PG Added Successfully!\n";
            break;
        }

        // 2. Display All PGs
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

        // 3. Search PG by College Name
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

        // 4. Filter PGs by Rent Budget
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

        // 5. View Bed Availability Tracker
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

        // 6. Inspect Rooms & Students in a selected PG
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

        // 7. Exit
        case 7:
            cout << "\nThank you for using StayNear System! Exiting.\n";
            break;

        default:
            cout << "\nInvalid Choice! Please enter a number between 1 and 7.\n";
        }

    } while (choice != 7);

    return 0;
}
