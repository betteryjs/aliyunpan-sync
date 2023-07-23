#include <iostream>
#include <string>

#include <nlohmann/json.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <experimental/filesystem>


using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

json dict;

vector<string>  removeDirs{".xmake"};


void filestat(const char *filepath, struct stat *buf) {

    if (stat(filepath, buf) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
    cout << "size : " << buf->st_size << endl;
    struct timespec ts = buf->st_mtim;
    // long int ts.tv_nsec
    cout << ts.tv_nsec << endl;
    cout << ts.tv_sec << endl;
}


void checkAllDir(const fs::path &dirs) {
    fs::directory_iterator dictsIterator(dirs);
    for (fs::directory_entry dir:dictsIterator)
    {

        if (fs::is_directory(dir) && std::find(removeDirs.begin(), removeDirs.end(), dir.path().filename()) == removeDirs.end()){
            cout << dir.path()<<endl;
            dict[dir.path().string()] = true;
        }



    }
    fstream jsonDirs;
    jsonDirs.open("oldDirs.json",ios::out);
    jsonDirs<< dict;
    jsonDirs.close();





}


int main(int argc, char **argv) {
//    struct stat sb;
//
    string path{"/home/yjs"};
//    filestat(path.c_str(), &sb);
    fs::path p1(path);

    checkAllDir(path);
    cout << dict<<endl;

    return 0;
}
