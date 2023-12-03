#include <stdio.h>

#ifdef _WIN32
    const char* os = "Windows";
#elif __linux__
    const char* os = "Linux";
#elif __APPLE__
    const char* os = "MacOS";
#else
    const char* os = "Unknown";
#endif

int main() {
    printf("Операционная система: %sn", os);
    
     if (strcmp(os, "Linux") == 0) {
        system("./path/to/binary"); 
    }

    return 0;
}
