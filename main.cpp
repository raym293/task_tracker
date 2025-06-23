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

// TODO
// Add error handeling
struct Task {
    std::string description;
    std::string status;
    time_t timeCreated;
    time_t timeUpdated;
    Task(json obj) : description(obj["description"]),
     status(obj["status"]),
     timeCreated(std::stoll((std::string)obj["date created"])),
     timeUpdated(std::stoll((std::string)obj["date updated"])) {} 
    Task(std::string description) : description(description), status("todo") {
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
    std::vector<Task> tasks;
    int numberOfTasks;
    json data;
    if(f) {
        data = json::parse(f);
        numberOfTasks = data.size();
        for(int i = 1; i <= numberOfTasks; i++) {
            tasks.push_back(Task(data[std::to_string(i)]));
        }
    }
    // std::cout << data.dump(4) << "\n\n\n";
    if(argc == 1 || (std::string)argv[1] == "view") {
        int counter = 1;
        for(auto i:tasks)
        {
            std::cout << counter++ << ". ";
            i.Print();
        }
    } 
    else if((std::string)argv[1] == "add") {
        std::string desc = argv[2];
        for(int i = 3; i < argc; i++) {
            desc+=" "+(std::string)argv[i];
        }
        tasks.push_back(Task(desc));
        std::cout << "Successfully added new task\n";
        tasks.back().Print();
    }
    else if((std::string)argv[1] == "delete") {
        int index = atoi(argv[2]);
        if(index>0 && index<=(int)tasks.size())
        {
            std::cout << "Deleting task: " << index <<"...\n";
            tasks[index-1].Print();
            tasks.erase(tasks.begin()+index-1);
            std::cout << "Deleted!\n\n";
        }
        else std::cout << "Error: out of bounds there are only " << tasks.size() << " notes\n";
        for(auto i:tasks) i.Print();
    }
    else if((std::string)argv[1] == "update") {
        int index = atoi(argv[2]);
        if(index>0 && index<=(int)tasks.size())
        {
            std::cout << "Updating task: " << index <<"...\n";
            
            std::string description = (std::string)argv[3];
            for(int i = 3; i < argc; i++) {
                description+=" "+(std::string)argv[i];
            }
            tasks[index].description = description;
            std::cout << "Updated!\n\n";
        }
        else std::cout << "Error: out of bounds there are only " << tasks.size() << " notes\n";
        for(auto i:tasks) i.Print();

    }

    // write to json
    json output;
    int counter = 1;
    // "date created": "",
    // "date updated": "",
    // "description": "Task three",
    // "status": "in_progress"
    for(auto i:tasks) {
        output[std::to_string(counter++)] = {
            {"date created", std::to_string(i.timeCreated)},
            {"date updated",std::to_string(i.timeUpdated)},
            {"description",i.description},
            {"status",i.status}
        };
    }
    std::ofstream o("data.json");
    // std::cout << output.dump(4);
    o << output.dump(4);
    return 0;
}
