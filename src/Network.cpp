#include "Network.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define COMMAND_DELIM ' '

using namespace std;

void Network::run(){
    string command;
    stringstream command_stream;
    while(getline(cin,command)){
        
        command_stream=stringstream(command);
        getline(command_stream,command,COMMAND_DELIM);

        if(command=="topology"){

        }else if(command=="lsrp"){

        }else if(command=="dvrp"){

        }else if(command=="show"){

        }else if(command=="modify"){

        }else if(command=="remove"){

        }else{
            cout<<"Error: Unknown Command"<<endl;
        }
    }
}