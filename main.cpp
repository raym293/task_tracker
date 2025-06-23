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

struct Task {
    std::string description;
    std::string status;
    time_t timeCreated;
    time_t timeUpdated;
    Task(json obj) : description(obj["description"]), status(obj["status"]) {
        time_t temp;
        time(&temp);
        timeCreated = timeUpdated = temp;
    } 
    void Print() {
        std::cout << description << '\n';
        std::cout << status << '\n';
        std::cout << ctime(&timeCreated);
        std::cout << ctime(&timeUpdated) << '\n';
    }
};

int main(int argc, char *argv[]) {
    std::ifstream f("data.json");
    json data = json::parse(f);
    int numberOfTasks = data.size();
    std::vector<Task> tasks;
    for(int i = 1; i <= numberOfTasks; i++) {
        tasks.push_back(Task(data[std::to_string(i)]));
    }
    if(argc == 1 || (std::string)argv[1] == "view") {
        for(auto i:tasks) i.Print();
    }
    return 0;
}