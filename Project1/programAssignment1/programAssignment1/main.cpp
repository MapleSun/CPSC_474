//
//  main.cpp
//  programAssignment1
//
//  Created by SYJ on 9/20/16.
//  Copyright © 2016 SunYijie. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Event.h"
#include "Process.h"
//#include "srTable.h
#include <map>
#include <sstream>
using namespace std;

void Display_All_Process(vector<Process*> process_table){
    for(int i = 0; i<process_table.size(); i++){
        process_table[i]->Display_Process();
    }
}

void Display_All_LC(vector<Process*> process_table){
    for(int i = 0; i<process_table.size(); i++){
        process_table[i]->Display_LC();
    }
}




bool is_finished(vector<Process*> process_table){
    for(int i = 0; i<process_table.size(); i++){
        if(!process_table[i]->process.empty()){
            return false;
        }
    }
    return true;
}


int main(int argc, const char * argv[]) {
    map<int, int> srMap;
    //vector<int> indexBreak;
    int GLC = 1;
    int numProcess ;
    int numEvent ;
    fstream file;
    string fn = argv[1];
    file.open(fn, fstream::in);
    string line;
    vector<Process*> process_table;
    int i = 0;
    while (std::getline(file, line) )
    {
        //cout << line;
        std::stringstream iss(line);
        
        string temp;
        //cout << temp;
        vector<string> tempProcess;
        while(iss.good()){
            getline(iss, temp, ' ');
            tempProcess.push_back(temp);
        }
        string processName = "p" + to_string(i);
        process_table.push_back(new Process(processName, tempProcess));
        i++;
    }
    
    file.close();
    
    do{
        for(int j = 0; j<process_table.size(); j++){
            Event* curEvent = process_table[j]->process.front();
            // internal and send event
            if(curEvent!=NULL){
                if(curEvent->type != type::recv){
                    curEvent->logic_clock = GLC;
                    if(curEvent->type == type::send){
                        srMap[curEvent->numEvent] = curEvent->logic_clock;
                    }
                    process_table[j]->result.push_back(curEvent->logic_clock);
                    process_table[j]->process.pop();
                }else{
                    // receive event
                    map<int,int>::iterator it = srMap.find(curEvent->numEvent);
                    // check is the pair send event already happen.
                    if(it != srMap.end() && srMap[curEvent->numEvent] + 1 == GLC){
                        // recv lc = max{send lc, GLC} + 1
                        curEvent->logic_clock = GLC;
                        process_table[j]->result.push_back(curEvent->logic_clock);
                        process_table[j]->process.pop();
                    }
                }
            }
        }
        GLC++;  // increase the globe logic clock
    }while(!is_finished(process_table));
    
    Display_All_Process(process_table);
    Display_All_LC(process_table);
    
    
}

