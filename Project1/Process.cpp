//
//  process.h
//  programAssignment1
//
//  Created by SYJ on 9/20/16.
//  Copyright © 2016 SunYijie. All rights reserved.
//

#include "Event.h"
#include <iostream>
#include <vector>
#include <queue>
#ifndef process_h
#define process_h

using namespace std;

class Process{
public:
    string name;
    queue<Event*> process;
    queue<Event*> process_Display;
    vector<int> result;
    // int LC = 0;
    // int breakIndex = 0; since we use queue we dont need the breakIndex anymore
    Process(string name, vector<string> process_list);
    void Assign_LC();
    void Display_Process();
    void Display_LC();
    bool is_finished();
};

Process::Process(string name, vector<string> process_list){
    this->name = name;
    for(int i = 0; i<process_list.size(); i++){
        //cout << process_list[i] << endl;
        this->process.push(new Event(process_list[i]));
    }
    process_Display = process;
    //Assign_LC();
}

void Process::Display_Process(){
    unsigned long size = process_Display.size();
    cout << name << ": ";
    for(int i = 0; i < size; i++){
        cout << process_Display.front()->name << " " ;
        process_Display.pop();
    }
    cout << endl;
}

void Process::Display_LC(){
    unsigned long size = this->result.size();
    cout << name << ": ";
    for(int i = 0; i < size; i++){
        cout << result[i] << " " ;
        //process_Display.pop();
    }
    cout << endl;
}




#endif /* Process_h */
