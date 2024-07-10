#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctime>

class c_driver {
private:
    int fd;
    pid_t pid;
    std::ofstream log;

    typedef struct _COPY_MEMORY {
        pid_t pid;
        uintptr_t addr;
        void* buffer;
        size_t size;
    } COPY_MEMORY, *PCOPY_MEMORY;

    typedef struct _MODULE_BASE {
        pid_t pid;
        char* name;
        uintptr_t base;
    } MODULE_BASE, *PMODULE_BASE;

    enum OPERATIONS {
        OP_INIT_KEY = 0x800,
        OP_READ_MEM = 0x801,
        OP_WRITE_MEM = 0x802,
        OP_MODULE_BASE = 0x803,
    };

    bool isSymbolFile(const std::string &filename) {
        bool hasLower = false, hasUpper = false, hasSymbol = false, hasDigit = false;
        for (char ch : filename) {
            if (islower(ch)) {
                hasLower = true;
                log << ch << " is a lowercase character\n";
            } else if (isupper(ch)) {
                hasUpper = true;
                log << ch << " is an uppercase character\n";
            } else if (ispunct(ch)) {
                hasSymbol = true;
                log << ch << " is a symbol\n";
            } else if (isdigit(ch)) {
                hasDigit = true;
                log << ch << " is a digit\n";
            }
        }
        log << "Filename: " << filename << " -> ";
        if (hasLower && !hasUpper && !hasSymbol && !hasDigit) {
            log << "Symbol file\n";
        } else {
            log << "Not a symbol file\n";
        }
        return hasLower && !hasUpper && !hasSymbol && !hasDigit;
    }

    std::string findDriverPath() {
        const char *devPath = "/dev";
        DIR *dir = opendir(devPath);
        if (dir == nullptr) {
            std::cerr << "Unable to open /dev directory\n";
            log << "Unable to open /dev directory\n";
            exit(EXIT_FAILURE);
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

            std::string filePath = std::string(devPath) + "/" + entry->d_name;
            struct stat fileInfo;
            if (stat(filePath.c_str(), &fileInfo) < 0) continue;

            if (strstr(entry->d_name, "gpiochip") != nullptr) continue;

            if ((S_ISCHR(fileInfo.st_mode) || S_ISBLK(fileInfo.st_mode))
                && strchr(entry->d_name, '_') == nullptr && strchr(entry->d_name, '-') == nullptr && strchr(entry->d_name, ':') == nullptr) {
                if (strcmp(entry->d_name, "stdin") == 0 || strcmp(entry->d_name, "stdout") == 0 || strcmp(entry->d_name, "stderr") == 0) continue;

                if (isSymbolFile(entry->d_name)) {
                    if ((fileInfo.st_mode & S_IFMT) == S_IFCHR && fileInfo.st_size == 0
                        && fileInfo.st_gid == 0 && fileInfo.st_uid == 0 && strlen(entry->d_name) <= 7) {
                        closedir(dir);
                        return filePath;
                    }
                }
            }
        }
        closedir(dir);
        std::cerr << "Driver file not found in /dev\n";
        log << "Driver file not found in /dev\n";
        exit(EXIT_FAILURE);
    }

public:
    c_driver() {
        log.open("/data/local/kernellog.log");
        std::string deviceName = findDriverPath();
        fd = open(deviceName.c_str(), O_RDWR);
        if (!log.is_open() || fd == -1) {
            std::cerr << "Failed to open log file: /data/local/kernellog.log or driver file: " << deviceName << "\n";
            exit(EXIT_FAILURE);
        }
    }

    ~c_driver() {
        if (fd > 0) close(fd);
        log.close();
    }

    void initialize(pid_t pid) {
        this->pid = pid;
    }

    int32_t getFD() const {
        return fd;
    }

    bool initKey(const std::string &key) {
        if (key.length() != 16) {
            std::cerr << "Invalid key length. Key must be 16 characters long.\n";
            log << "Invalid key length. Key must be 16 characters long.\n";
            return false;
        }

        std::cout << "Initializing key: " << key << "\n";
        log << "Initializing key: " << key << "\n";

        char buf[0x100];
        strncpy(buf, key.c_str(), sizeof(buf));
        if (ioctl(fd, OP_INIT_KEY, buf) != 0) {
            std::cerr << "Failed to initialize key. Make sure the device is properly connected.\n";
            log << "Failed to initialize key. Make sure the device is properly connected.\n";
            return false;
        }

        std::cout << "Key initialized successfully.\n";
        log << "Key initialized successfully.\n";

        return true;
    }

    bool readMemory(uintptr_t addr, void *buffer, size_t size) {
        COPY_MEMORY cm{this->pid, addr, buffer, size};
        if (ioctl(fd, OP_READ_MEM, &cm) != 0) {
            std::cerr << "Failed to read memory at address: " << addr << "\n";
            log << "Failed to read memory at address: " << addr << "\n";
            return false;
        } else {
                   std::cout << "Successfully read " << size << " bytes from address " << addr << ":\n";
        log << "Successfully read " << size << " bytes from address " << addr << ":\n";
        unsigned char *data = static_cast<unsigned char*>(buffer);
        std::cout << "Data: ";
        log << "Data: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << std::hex << static_cast<int>(data[i]) << " ";
            log << std::hex << static_cast<int>(data[i]) << " ";
        }
        std::cout << std::endl;
        log << std::endl;
    }
    return true;
}

bool writeMemory(uintptr_t addr, const void *buffer, size_t size) {
    COPY_MEMORY cm{this->pid, addr, const_cast<void*>(buffer), size};

    std::cout << "Writing memory at address: 0x" << std::hex << addr << ", Size: " << size << " bytes\n";
    log << "Writing memory at address: 0x" << std::hex << addr << ", Size: " << size << " bytes\n";

    if (ioctl(fd, OP_WRITE_MEM, &cm) != 0) {
        std::cerr << "Failed to write memory at address: 0x" << std::hex << addr << "\n";
        log << "Failed to write memory at address: 0x" << std::hex << addr << "\n";
        return false;
    } else {
        std::cout << "Memory write successful at address: 0x" << std::hex << addr << "\n";
        log << "Memory write successful at address: 0x" << std::hex << addr << "\n";
        return true;
    }
}

uintptr_t getModuleBase(const std::string &name) {
    char buf[0x100];
    strncpy(buf, name.c_str(), sizeof(buf));
    MODULE_BASE mb{this->pid, buf};

    std::cout << "Requesting base address for module: " << name << "\n";
    log << "Requesting base address for module: " << name << "\n";

    if (ioctl(fd, OP_MODULE_BASE, &mb) != 0) {
        std::cerr << "Failed to get module base address for: " << name << "\n";
        log << "Failed to get module base address for: " << name << "\n";
        return 0;
    } else {
        std::cout << "Module base address found for: " << name << "\n";
        std::cout << "Base Address: 0x" << std::hex << mb.base << "\n";
        log << "Module base address found for: " << name << "\n";
        log << "Base Address: 0x" << std::hex << mb.base << "\n";
        return mb.base;
    }
}

};

static c_driver *KernelDrivers = new c_driver();



