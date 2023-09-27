#include <iostream>

class MyFILE{
    public:
    // define file
        FILE* file;
        MyFILE(const char* filename, const char* mode) {
            file = fopen(filename, mode);
        }

        //define a function that read from file
        int read(char* buffer, int length) {
            return fread(buffer, 1, length, file);
        }

        //define a function that write to file
        int write(const char* buffer, int length) {
            return fwrite(buffer, 1, length, file);
        }

        ~MyFILE() {
            if (file != nullptr) {
                fclose(file);
            }
        }
        MyFILE(MyFILE&&) = delete;
        MyFILE& operator=(MyFILE&&) = delete;
};

int main(){
    MyFILE file("test.txt", "w");
    // write to file "hello"
    file.write("Hello", 5);

    // read from file
    char buffer[6];
    file.read(buffer, 5);
    buffer[5] = '\0';
    std::cout <<"readed text" << buffer << std::endl;

    fprintf(file.file, "Hello World!\n");
    return 0;
}