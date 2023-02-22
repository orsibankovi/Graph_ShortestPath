//
// Created by levib on 2022. 10. 30..
//

#ifndef HF2_MAPAPI_HPP
#define HF2_MAPAPI_HPP
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

/**
txt format:
N,start,goal
[connections from node 0]
[connections from node 1]
.
.
    -format:
    target_node_id1:distance1,target_node_id2:distance2,...;
.
.
[connections from node  N-1]
*/
class MapApi{
private:
    bool verbose;
    std::string mapname;
    int ctr_la;
    int ctr_g;
    int ctr_travel;
    std::vector<int> path = {};
    int N;
    int position;
    int startId;
    int goalId;
    std::map<int,std::map<int,int>> adjacency= {};
    bool travelInvalidDestinationFlag=false;
    int checkPathWithLength(std::vector<int> pathToGoal);
public:
    MapApi(std::string path,std::string filename,bool verbose,int v);
    bool isTravelInvalidDestinationFlag() const;
    inline bool checkPath(std::vector<int> pathToGoal);
    inline bool checkShortest(std::vector<int> pathToGoal);


    int getN() const;
    int getStartId() const;
    std::map<int, int> lookAround();/// returns the reachable node ids with distances
    int travelTo(int id);///moves the current position to the new id (if it is reachable), returns the cost of travel (0 if not reachable)
    bool isGoal();

};

MapApi::MapApi(std::string path,std::string filename,bool verbose, int v):verbose(verbose) {
    mapname = filename;
    std::ifstream input;
    input.open(path + mapname, std::ios::in);
    char drain;
    std::string line;
    if (v == 0) {
        if (input.good()) {
            input >> N >> drain >> startId >> drain >> goalId;
            std::getline(input, line);
        }
        for (int i = 0; i < N; i++) {
            std::getline(input, line);
            std::stringstream ss;
            ss << line;
            while (ss.good() && drain != ';') {
                int tmp_id = -1;
                int tmp_dist = -1;
                ss >> tmp_id >> drain >> tmp_dist >> drain;
                adjacency[i].emplace(tmp_id, tmp_dist);
            }
            drain = '.';
        }
        input.close();
        position = startId;
        ctr_la = 0;
        ctr_g = 0;
        ctr_travel = 0;
    }
    else{
        while(input.good()){
            std::getline(input,line);
            std::stringstream ss;
            ss << line;
            int from_id,to_id,weight;
            ss>>from_id>>to_id>>weight;
            adjacency[from_id-1].emplace(to_id-1, weight);
            adjacency[to_id-1].emplace(from_id-1, weight);
        }
        input.close();
        N=adjacency.size();
        startId=0;
        if(mapname=="s3.txt"){
            goalId=13248;
        }else {
            goalId = adjacency.cend()->first;
        }
        position = startId;
        ctr_la = 0;
        ctr_g = 0;
        ctr_travel = 0;
    }
}

std::map<int, int> MapApi::lookAround(){
    ++ctr_la;
    if(verbose) {
        std::cout << "lookAround() at: " << position << "    ---    lookAround() calls counter: "<<ctr_la<<std::endl;
    }

    return adjacency.find(position)->second;
}

int MapApi::travelTo(int id) {
    if(adjacency[position].contains(id)){
        int dist = adjacency[position][id];
        ++ctr_travel;
        if(verbose) {
            std::cout << "travel from: " << position << " to "<<id <<"    ---    travelTo() calls counter: "<<ctr_travel<<std::endl;
        }
        position = id;
        path.push_back(position);
        return dist;
    }else{
        travelInvalidDestinationFlag = true;
        return 0;
    }
}

bool MapApi::isGoal(){
    ctr_g++;
    if(verbose) {
        std::cout << "isGoal() at: " << position << "    ---    isGoal() calls counter: "<<ctr_g<<std::endl;
    }

    return (position==goalId);
}

int MapApi::getStartId() const {
    return startId;
}

int MapApi::getN() const {
    return N;
}

bool MapApi::checkPath(std::vector<int> pathToGoal) {
    position=startId;
    for(int id:pathToGoal){
        travelTo(id);
    }
    bool res = isGoal();
    if(verbose){
        std::cout<< "checking validity of path: ";
        for (const auto &item : pathToGoal){
            std::cout<<item<<" ";
        }
        std::cout<<"result: " <<res<<std::endl;
    }
    return res;
}

bool MapApi::checkShortest(std::vector<int> pathToGoal) {
    if(mapname=="s3.txt"){
        if(checkPathWithLength(pathToGoal)==7)
            return true;
    }
    if(mapname=="s2.txt"){
        if(checkPathWithLength(pathToGoal)==193)
            return true;
    }
    if(mapname=="s1.txt"){
        if(checkPathWithLength(pathToGoal)==4)
            return true;
    }
    if(mapname=="long.txt"){
        if(checkPathWithLength(pathToGoal)==26)
            return true;
    }
    if(mapname=="demo.txt"){
        if(checkPathWithLength(pathToGoal)==5)
            return true;
    }
    if(mapname=="interconnected.txt"){
        if(checkPathWithLength(pathToGoal)==8)
            return true;
    }
    if(mapname=="medium.txt"){
        if(checkPathWithLength(pathToGoal)==6)
            return true;
    }
    return false;
}

int MapApi::checkPathWithLength(std::vector<int> pathToGoal) {
    position=startId;
    int sum=0;
    for(int id:pathToGoal){
        if(id != startId)
            sum+=travelTo(id);
    }
    bool res = isGoal();
    if(verbose){
        std::cout<< "checking validity of path: ";
        for (const auto &item : pathToGoal){
            std::cout<<item<<" ";
        }
        std::cout<<"result: " <<res<<std::endl;
    }
    if(res)
        return sum;
    return -1;
}

bool MapApi::isTravelInvalidDestinationFlag() const {
    return travelInvalidDestinationFlag;
}

#endif //HF2_MAPAPI_HPP
