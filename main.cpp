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
    if((std::string)argv[1] == "add") {
        std::string desc = argv[2];
        for(int i = 3; i < argc; i++) {
            desc+=" "+(std::string)argv[i];
        }
        tasks.push_back(Task(desc));
        std::cout << "Successfully added new task\n";
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
            tasks[index-1].description = description;
            std::cout << "Updated!\n\n";
        }
        else std::cout << "Error: out of bounds there are only " << tasks.size() << " notes\n";
    }
    else if((std::string)argv[1] == "mark-in-progress") {
        int index = atoi(argv[2]);
        if(index>0 && index<=(int)tasks.size())
        {
            tasks[index-1].status = "in-progress";
        }
        else std::cout << "Error: out of bounds there are only " << tasks.size() << " notes\n";
    }
    else if((std::string)argv[1] == "mark-done") {
        int index = atoi(argv[2]);
        if(index>0 && index<=(int)tasks.size())
        {
            tasks[index-1].status = "done";
        }
        else std::cout << "Error: out of bounds there are only " << tasks.size() << " notes\n";
    }
    // print all tasks
    int counter = 1;
    std::string op = argv[1];
    if(op == "update" || (op == "list" && argc == 2) || op == "delete" || op == "add")
    {   
        for(auto i:tasks)
        {
            std::cout << counter++ << ". ";
            i.Print();
        }
    }
    else if(op == "list" && argc == 3) {
        for(auto i:tasks)
        {
            if(i.status == std::string(argv[2]))
            {
                std::cout << counter << ". ";
                i.Print();
            }
            counter++;
        }
        
    }
    
    // write to json
    json output;
    counter = 1;
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
