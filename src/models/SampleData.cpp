#include "SampleData.h"

// Keep example data in one place so the GUI can display it at startup.
std::vector<PG> createSamplePgs()
{
    std::vector<PG> pgs;

    PG himalayanBreeze(
        "Himalayan Breeze PG",
        "Graphic Era Hill University Bhimtal",
        "Bhowali Road, Bhimtal",
        "Boys",
        5500,
        4.6f
    );
    himalayanBreeze.setOwner(
        Owner("Rajesh Joshi", "+91 9876543210", "rajesh.joshi@email.com")
    );

    Room room101(101, 2);
    room101.addStudent(Student("Rahul Sharma", "9876500001", "B.Tech CSE", 2));
    himalayanBreeze.addRoom(room101);

    Room room102(102, 3);
    room102.addStudent(Student("Amit Verma", "9876500002", "BCA", 1));
    room102.addStudent(Student("Rohit Singh", "9876500003", "B.Tech ME", 3));
    himalayanBreeze.addRoom(room102);

    himalayanBreeze.addRoom(Room(103, 2));
    pgs.push_back(himalayanBreeze);

    PG pineCrest(
        "Pine Crest Girls PG",
        "Graphic Era Hill University Bhimtal",
        "June Estate, Bhimtal",
        "Girls",
        6500,
        4.8f
    );
    pineCrest.setOwner(
        Owner("Sunita Bisht", "+91 9812345678", "sunita.bisht@email.com")
    );

    Room room201(201, 2);
    room201.addStudent(Student("Priya Mehra", "9812300001", "B.Tech CSE", 3));
    room201.addStudent(Student("Ananya Arya", "9812300002", "BBA", 2));
    pineCrest.addRoom(room201);

    Room room202(202, 2);
    room202.addStudent(Student("Divya Pant", "9812300003", "B.Tech AI", 1));
    pineCrest.addRoom(room202);
    pgs.push_back(pineCrest);

    PG lakeView(
        "Lake View Residency",
        "Birla Institute of Applied Sciences (BIAS)",
        "Mallital, Bhimtal",
        "Co-Ed",
        7000,
        4.5f
    );
    lakeView.setOwner(
        Owner("Mahesh Tiwari", "+91 9755544433", "mahesh.tiwari@email.com")
    );

    Room room301(301, 2);
    room301.addStudent(Student("Karan Negi", "9755500001", "MCA", 2));
    lakeView.addRoom(room301);
    lakeView.addRoom(Room(302, 2));
    pgs.push_back(lakeView);

    return pgs;
}
