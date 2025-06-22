#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>



int main(int argc, char *argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cerr << "Logs from your program will appear here!\n";

    if (argc < 2) {
        std::cerr << "No operations provided\n";
        return EXIT_FAILURE;
    }
    std::string command = argv[1];
    std::cerr << command << std::endl;
    if (command == "init") {

        if (argc == 3) {
            // when path is given
            std::string path = argv[2];
            std::cerr << path << std::endl;
            try {
                //need to create git directories
                if (path[path.length()-1] == '/') {
                    path.pop_back();
                }
                std::filesystem::create_directories(path+"/.git");
                std::filesystem::create_directory(path+"/.git/objects");
                std::filesystem::create_directory(path+"/.git/refs");
            } catch (const std::filesystem::filesystem_error& error) {
                std::cerr << error.what() << "\n";
                return EXIT_FAILURE;
            }

            std::ofstream headFile(path+"/.git/HEAD.txt");
            if (headFile.is_open()) {
                headFile << "ref: refs/heads/master" << std::endl;
                headFile.close();
            }else {
                std::cerr << "Failed to create HEAD file" << std::endl;
                return EXIT_FAILURE;
            }

        }else if (argc < 3) {
            // when path is not given, create at the current directory
            try {
                //need to create git directories
                // std::string path = std::filesystem::current_path();
                // std::string home = std::getenv("HOME") ? std::getenv("HOME") : "";
                //
                // if (home.empty()) {
                //     std::cerr << "Could not determine home directory\n";
                //     return EXIT_FAILURE;
                // }


                std::filesystem::create_directory("/.git");
                std::filesystem::create_directory("/.git/objects");
                std::filesystem::create_directory("/.git/refs");

                std::ofstream headFile("/.git/HEAD.txt");
                if (headFile.is_open()) {
                    headFile << "ref: refs/heads/main" << std::endl;
                    headFile.close();
                }else {
                    std::cerr << "Failed to create HEAD file" << std::endl;
                    return EXIT_FAILURE;
                }

            } catch (const std::filesystem::filesystem_error& error) {
                std::cerr << error.what();
                return EXIT_FAILURE;
            }
        }


    }else if (command == "cat-file") {
        std::string flag = argv[2];
        std::string hash = argv[3];



    }else {
        std::cerr << "Unknown command" << std::endl;
        return EXIT_FAILURE;
    }



    return EXIT_SUCCESS;
}