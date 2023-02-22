#ifndef HF2_SOLVER_HPP
#define HF2_SOLVER_HPP

#include "mapApi.hpp"
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <utility>
#include <random>
#include <algorithm>

class Solver {
private:
    MapApi *mapapi;
    std::unordered_set<int> bejart_csucsok; //O(1)
    std::vector<int> ut;
    std::unordered_map<int, std::map<int, int>> ossz_szomszed{}; //O(1)
    std::random_device rnd_device{};
    std::mt19937 generator{rnd_device()};
    std::unordered_map<int, int> tavolsagok;
    std::unordered_map<int, int> elozo_csucs; //honnan ertuk el az adott csucsot
    std::unordered_set<int> megnezendo;
    void clear();
public:
    Solver(MapApi *mapApi);

    std::vector<int> findShortestPath();
    std::vector<int> findPathToGoal();
};

Solver::Solver(MapApi *mapApi) {
    mapapi = mapApi;
}

void Solver::clear() {
    ut.clear();
    bejart_csucsok.clear();
    ossz_szomszed.clear();
    tavolsagok.clear();
    elozo_csucs.clear();
}

std::vector<int> Solver::findPathToGoal() {
    clear();

    int aktualis = mapapi->getStartId();
    bejart_csucsok.insert(aktualis);
    ut.push_back(aktualis);

    while (!mapapi->isGoal()) {
        std::map<int, int> szomszedok;
        if(ossz_szomszed.contains(aktualis)){
            szomszedok = ossz_szomszed.at(aktualis);
        } else {
            szomszedok = mapapi->lookAround();
            ossz_szomszed[aktualis] = szomszedok;
        }
        std::vector<int> valaszthato{};
        for (const std::pair<const int, int> &szomszed: szomszedok) {
            if (!bejart_csucsok.contains(szomszed.first)) {
                valaszthato.push_back(szomszed.first);
            }
        }
        if (valaszthato.empty()) {
            aktualis = ut[ut.size() - 2];
            ut.pop_back();
            ut.pop_back();
        } else if (valaszthato.size() == 1) {
            aktualis = valaszthato[0];
        } else {
            std::uniform_int_distribution<int> distribution{0, static_cast<int>(valaszthato.size() - 1)};
            aktualis = valaszthato[distribution(rnd_device)];
        }
        mapapi->travelTo(aktualis);
        ut.push_back(aktualis);
        bejart_csucsok.insert(aktualis);
    }
    ut.erase(ut.begin());
    return ut;
}


std::vector<int> Solver::findShortestPath() {
    clear();
    int goal = -1;
    std::vector<int>min_ut_;
    int aktualis = mapapi->getStartId();
    elozo_csucs.insert(std::pair(aktualis, -1));
    tavolsagok.insert(std::pair(aktualis, 0));
    megnezendo.insert(aktualis);
    ut.push_back(aktualis);

    while (!megnezendo.empty()) {
        megnezendo.erase(aktualis);
        std::map<int, int> szomszedok;
        std::pair<int, int>kov_csucs {-1, -1};
        if(ossz_szomszed.contains(aktualis)){
            szomszedok = ossz_szomszed.at(aktualis);
        } else {
            szomszedok = mapapi->lookAround();
            ossz_szomszed[aktualis] = szomszedok;
        }
        if (!mapapi->isGoal()) {
            for (const std::pair<const int, int> &szomszed: szomszedok) {
                if (!bejart_csucsok.contains(szomszed.first)) {
                    megnezendo.insert(szomszed.first);
                    if (kov_csucs.first == -1 or kov_csucs.second > szomszed.second) {
                        kov_csucs = szomszed;
                    }
                }

                if (!tavolsagok.contains(szomszed.first) or tavolsagok[aktualis] + szomszed.second < tavolsagok[szomszed.first]) {
                    tavolsagok[szomszed.first] = tavolsagok[aktualis] + szomszed.second;
                    elozo_csucs[szomszed.first] = aktualis;
                }
            }
        }
        bejart_csucsok.insert(aktualis);
        if (kov_csucs.first == -1) {
            aktualis = ut[ut.size()-2];
            if(aktualis == mapapi->getStartId()){
                ut.clear();
            } else {
                ut.pop_back();
            }
        } else {
            aktualis = kov_csucs.first;
            ut.push_back(aktualis);
        }
        mapapi->travelTo(aktualis);

        if (mapapi->isGoal()){
            goal = aktualis;
        }
    }

    aktualis = goal;
    while(aktualis != mapapi->getStartId()){
        min_ut_.push_back(aktualis);
        aktualis = elozo_csucs.at(aktualis);
    }
    std::reverse(min_ut_.begin(), min_ut_.end());

    return min_ut_;
}

#endif //HF2_SOLVER_HPP