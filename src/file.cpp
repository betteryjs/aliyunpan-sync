#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>




using namespace std;


void filestat(const char * filepath, struct stat *buf ){

    if (stat(filepath,buf) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
    cout << "size : "<<buf->st_size<<endl;
    struct timespec ts=buf->st_mtim;
    // long int ts.tv_nsec
    cout << ts.tv_nsec<<endl;
    cout << ts.tv_sec<<endl;
}

void  checkAllDir(){



}





int main(int argc, char** argv)
{
    struct stat sb;

    string path{"/home/yjs/CPP/aliyunpan-sync-xmake/src/files.json"};
    filestat(path.c_str(), &sb);
    return 0;
}
