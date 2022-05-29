#include "Network.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define COMMAND_DELIM ' '

using namespace std;

void Network::run(){
    string command,args;
    stringstream command_stream;
    vector<string> arg_list;
    while(getline(cin,command)){

        command_stream=stringstream(command);
        getline(command_stream,command,COMMAND_DELIM);
        getline(command_stream,args);
        if(command=="topology"){
            graph=new Graph(args);
        }else if(command=="lsrp"){
            arg_list=splitByDelim(args,'-');
            graph->link_state(stoi(args));
        }else if(command=="dvrp"){
            arg_list=splitByDelim(args,'-');
            graph->distance_vector(stoi(args));
        }else if(command=="show"){
            graph->show();
        }else if(command=="modify"){
            arg_list=splitByDelim(args,'-');
            graph->modify_edge(stoi(arg_list[0]),stoi(arg_list[1]),stoi(arg_list[2]));
        }else if(command=="remove"){
            arg_list=splitByDelim(args,'-');
            graph->delete_edge(stoi(arg_list[0]),stoi(arg_list[1]));
        }else{
            cout<<"Error: Unknown Command"<<endl;
        }
    }
}