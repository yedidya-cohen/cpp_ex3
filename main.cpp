#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "Controller.h"
#include "Model.h"
#include "Port.h"

using namespace std;



int main(int argc, char** argv) {

   Model& m = Model::get_instance();

    cout << "=====================================================" << endl;
    cout << "--- Step 1: Initialization ---" << endl;

    // יצירת 3 נמלים על ציר X
    m.create_port("P1", Point(10.0, 0.0), 5000.0, 50000.0);
    m.create_port("P2", Point(20.0, 0.0), 5000.0, 50000.0);
    m.create_port("P3", Point(30.0, 0.0), 5000.0, 50000.0);

    // יצירת ספינת סיור (Patrol) בנקודה (0,0)
    // פרמטרים: Data, fuel, max_fuel, consumption, resistance
    Ship::Data pdata{"PatrolX", 0.0, 0.0, 15.0, Point(0.0, 0.0), ShipState::STOPPED};
    m.create_patrol_ship(pdata, 2000.0, 2000.0, 10.0, 5.0);

    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- Step 2: Seeding Initial Destination ---" << endl;
    string p = "P1";
    // פוקדים על ה-Patrol לנסוע ל-P1 במהירות 10
    // זה נותן לו "דחיפה ראשונה" שממנה הוא יתחיל את סבב הסיור
    m.destination("PatrolX", p, 10.0);
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 1: Moving to P1 ---" << endl;
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 2: Arriving at P1 (Should Dock) ---" << endl;
    // הספינה ב(10,0) -> עוגנת.
    // Patrol::update אמור להכניס אותה ל-DOCKED ולשנות מצב פנימי ל-REFUEL
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 3: Executing REFUEL Step ---" << endl;
    // הספינה ב-DOCKED, אמורה להפעיל my_3_steps
    // הסטטוס הפנימי REFUEL יבקש לתדלק. ייתכן שתראה אותה ב-WREFUELING או חזרה ב-DOCKED
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 4: Executing DOCK Step ---" << endl;
    // הסטטוס הפנימי מתחלף ל-DOCK
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 5: Executing DEST Step (Finding Next Port) ---" << endl;
    // הסטטוס הפנימי ב-DEST: פה היא מפעילה next_step!
    // היא אמורה למצוא את P2 (הקרוב ביותר שלא בוקר) ולהתחיל לנוע אליו
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 6: Moving to P2 ---" << endl;
    // כאן היא צריכה לחזור להיות MOVING לכיוון P2
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 7: Moving to P2 ---" << endl;
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 8: Arriving at P2 (Should Dock) ---" << endl;
    // כאן היא מגיעה ל-P2 ונכנסת ל-DOCKED, והכל מתחיל מחדש
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 9: Executing REFUEL Step ---" << endl;
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 10: Executing DOCK Step ---" << endl;
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 11: Executing DEST Step (Finding Next Port) ---" << endl;
    // פה היא מפעילה next_step ומוצאת את P3
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;


    cout << "--- TICK 12: Moving to P3 ---" << endl;
    m.update();
    m.describe();
    cout << "=====================================================\n" << endl;



    // if (argc!=2) {
    //     cerr <<"Usage:"<<argv[0] << " <file_ports> "<<endl;
    //     return 1;
    // }
    //
    // const View v(25,2.0,{0,0}); //for AI - not writtem
    // Controller c(v);
    // try {
    //     c.file_read_ports(argv[1]);
    //     c.simulate();
    // }
    // catch (exception& e) {
    //     cerr << e.what() << endl;
    //     return 1;
    // }
    //
    return 0;
}

