#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "Controller.h"
#include "Model.h"
#include "Port.h"

using namespace std;

int main(int argc, char** argv) {
    //check to see if file was given
    if (argc!=2) {
        cerr <<"Usage:"<<argv[0] << " <file_ports> "<<endl;
        return 1;
    }
    //inizilaize view to attach to controller
    const View v(25,2.0,{0,0});
    Controller c(v);

    try {
        c.file_read_ports(argv[1]); //we read the ports and inizalize
        c.simulate(); //start the simulate
    }

    //if there is exception we catch it
    catch (exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}

