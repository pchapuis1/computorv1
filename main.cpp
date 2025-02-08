#include <iostream>

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Only one arguments needed!" << std::endl;
        return 0;
    }
    (void)argv;

    return 0;
}