//include necessary libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Structure for Task
struct Task {
    string description;
    bool completed;
};

// Vector to store tasks
vector<Task> tasks;
// File name to store tasks
const string FILENAME = "tasks.txt";

// Function to save tasks to a file
void saveTasks() {
    //Open file for writing
    ofstream file(FILENAME);
    for (const auto& task : tasks) {//Loop through the tasks
        file << task.description << "|" << task.completed << endl;
    }
    file.close();
}

// Function to load tasks from a file
void loadTasks() {
    ifstream file(FILENAME);  //Open file for reading
    tasks.clear();  //Clear the current tasks vector
    string description;
    bool completed;
    while (getline(file, description, '|') && file >> completed) { // Read tasks line by line
        file.ignore(); //ignore newline character
        tasks.push_back({description, completed}); //Add task to the vector
    }
    file.close();
}

void addTask() {
    cout << "Enter task description: "; //Prompt user for task input
    string desc;
    cin.ignore();
    getline(cin, desc); //Get multiple words from user input
    tasks.push_back({desc, false}); //add the task to the vector
    saveTasks(); //Update tasks on file.
}

void deleteTask() {
    int index;
    cout << "Enter task number to delete: ";
    cin >> index; //Get a number(index) form user input
    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1); //Delete a task from the vector
        saveTasks(); //Update tasks on file.
    } else {
        cout << "Invalid task number." << endl;
    }
}

void markComplete() {
    int index;
    cout << "Enter task number to mark as complete: ";
    cin >> index;
    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true; // Change the completed stats of the task
        saveTasks(); // Update task on the file
    } else {
        cout << "Invalid task number." << endl;
    }
}

void listTasks(bool completedOnly = false) {
    if (tasks.empty()) { // If the vector was empty
        cout << "No tasks available." << endl;
        return;
    }
    int count = 1;
    for (const auto& task : tasks) { //Loop for tasks vector
        if (!completedOnly || task.completed) {
            //Display the description and status
            cout << count << ". " << task.description << " [" << (task.completed ? "Completed" : "Pending") << "]" << endl;
        }
        count++;
    }
}

int main() {
    loadTasks();
    int choice;
    //Infinite loop until user selects "0"
    do {
        cout << "\nTo-Do ++" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Delete Task" << endl;
        cout << "3. Mark Task Complete" << endl;
        cout << "4. List All Tasks" << endl;
        cout << "5. List Completed Tasks" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: deleteTask(); break;
            case 3: markComplete(); break;
            case 4: listTasks(); break;
            case 5: listTasks(true); break;
            case 0: cout << "Exiting..." << endl; break;
            default: cout << "Invalid option! Try again." << endl;
        }
    } while (choice != 0);
    
    return 0;
}
