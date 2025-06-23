#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <ctime>
using json = nlohmann::json;

// @brief
// each task should have
// id: A unique identifier for the task
// description: A short description of the task
// status: The status of the task (todo, in-progress, done)
// createdAt: The date and time when the task was created
// updatedAt: The date and time when the task was last updated

typedef struct {
    std::string description;
    std::string status;


}Task;

int main(int argc, char *argv[]) {
    // if(argc == 1) {
    //     std::cout << "Please add an argument\n";
    //     return 0;
    // }
    time_t t;
    time(&t);
    std::cout << ctime(t) << '\n';
    return 0;
}