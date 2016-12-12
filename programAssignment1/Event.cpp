//
//  event.h
//  programAssignment1
//
//  Created by SYJ on 9/20/16.
//  Copyright © 2016 SunYijie. All rights reserved.
//

#include <iostream>
#include <String>

#ifndef Event_h
#define Event_h
using namespace std;
enum type {internal = 0, send, recv};

class Event{
public:
    string name;
    int type;
    int numEvent;
    int logic_clock = -1;
    Event(string str);
    
};

Event::Event(string str){
    name = str;
    if(str.size() == 1){
        type = type::internal;
        numEvent = -1;
    }else if(str[0] == 's'){
        type = type::send;
        //cout << str[1] << endl;
        numEvent = atoi(str.substr(1,2).c_str());
        //cout << numEvent << endl;
    }else{
        type = type::recv;
        numEvent = atoi(str.substr(1,2).c_str());
    }
}

#endif /* Event_h */
