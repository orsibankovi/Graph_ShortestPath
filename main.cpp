#include "solver.hpp"
#include "woodpecker.hpp"

static bool verbose = false;
static std::string path = "../";

///find one path
TEST("demo find one",1){
    MapApi *mapper = new MapApi(path,"demo.txt",verbose,0);
    Solver solver(mapper);
    CHECK_EQ(true,(bool)mapper->checkPath(solver.findPathToGoal()));
    CHECK_EQ(false, (bool) mapper->isTravelInvalidDestinationFlag());
    delete mapper;
}

TEST("medium find one",1){
    MapApi *mapper = new MapApi(path,"medium.txt",verbose,0);
    Solver solver(mapper);
    CHECK_EQ(true, (bool) mapper->checkPath(solver.findPathToGoal()));
    CHECK_EQ(false, (bool) mapper->isTravelInvalidDestinationFlag());
    delete mapper;
}
TEST("interconnected find one",1){
    MapApi *mapper = new MapApi(path,"interconnected.txt",verbose,0);
    Solver solver(mapper);
    CHECK_EQ(true,(bool)mapper->checkPath(solver.findPathToGoal()));
    CHECK_EQ(false, (bool) mapper->isTravelInvalidDestinationFlag());
    delete mapper;
}
TEST("long find one",1){
    MapApi *mapper = new MapApi(path,"long.txt",verbose,0);
    Solver solver(mapper);
    CHECK_EQ(true,(bool)mapper->checkPath(solver.findPathToGoal()));
    CHECK_EQ(false, (bool) mapper->isTravelInvalidDestinationFlag());
    delete mapper;
}

///shortest paths
TEST("demo shortest",1){
    MapApi *mapper = new MapApi(path,"demo.txt",verbose,0);
    Solver solver(mapper);
    CHECK_EQ(true,(bool)mapper->checkShortest(solver.findShortestPath()));
    CHECK_EQ(false, (bool) mapper->isTravelInvalidDestinationFlag());
    delete mapper;
}
TEST("medium shortest",1){
    MapApi *mapper = new MapApi(path,"medium.txt",verbose,0);
    Solver solver(mapper);
    CHECK_EQ(true,(bool)mapper->checkShortest(solver.findShortestPath()));
    CHECK_EQ(false, (bool) mapper->isTravelInvalidDestinationFlag());
    delete mapper;
}
TEST("interconnected shortest",1){
    MapApi *mapper = new MapApi(path,"interconnected.txt",verbose,0);
    Solver solver(mapper);
    CHECK_EQ(true,(bool)mapper->checkShortest(solver.findShortestPath()));
    CHECK_EQ(false, (bool) mapper->isTravelInvalidDestinationFlag());
    delete mapper;
}


TEST("long shortest",1){
    MapApi *mapper = new MapApi(path,"long.txt",verbose,0);
    Solver solver(mapper);
    CHECK_EQ(true,(bool)mapper->checkShortest(solver.findShortestPath()));
    CHECK_EQ(false, (bool) mapper->isTravelInvalidDestinationFlag());
    delete mapper;
}
///server timed tests///

WOODPECKER_TEST_MAIN(-1, -1)