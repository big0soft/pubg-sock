//
// Created by day on 13/08/2022.
//

#ifndef DCHEATS_PUBGMX_SUPPORT_H
#define DCHEATS_PUBGMX_SUPPORT_H
#include "socket.h"
#include "KernelDrivers.hpp"

ssize_t process_v(pid_t __pid, const struct iovec *__local_iov, unsigned long __local_iov_count,
				  const struct iovec *__remote_iov, unsigned long __remote_iov_count,
				  unsigned long __flags, bool iswrite)
{
	return syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), __pid,
				   __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}


bool pvm(void *address, void *buffer, size_t size, bool iswrite)
{
	struct iovec local[1];
	struct iovec remote[1];
	local[0].iov_base = buffer;
	local[0].iov_len = size;
	remote[0].iov_base = address;
	remote[0].iov_len = size;
	if (pid < 0)
	{
		return false;
	}
	ssize_t bytes = process_v(pid, local, 1, remote, 1, 0, iswrite);
	return bytes == size;
}



template<typename T>
T Read(uintptr_t address) {
    T data{};
    KernelDrivers->readMemory(address, reinterpret_cast<void*>(&data), sizeof(data));
    
    return data;
}

bool vm_readv(unsigned long address, void *buffer, size_t size)
{
	return KernelDrivers->readMemory(address, buffer, size);
}

bool vm_writev(unsigned long address, void *buffer, size_t size)
{
	return KernelDrivers->writeMemory(address, buffer, size);
}

template<typename T>
void Writes(unsigned long address, T data) {
    KernelDrivers->writeMemory(address, reinterpret_cast<void*>(&data), sizeof(T));
}




#if defined(__aarch64__)
   	
    int isValid(uintptr_t addr) {
    if (addr < 0x1000000000 || addr>0xefffffffff || addr % SIZE != 0)
        return 0;
    return 1;
	}
	
    #else

    int isValid(uintptr_t addr) {
    if (addr < 0x10000000 || addr>0xefffffff || addr % SIZE != 0)
        return 0;
    return 1;
	}
    
    #endif



int isValidPlayer(int oType) {
	if (oType == 0x3ec2a00 || oType == 0x3ec2800)
		return 1;
    return 0;
}

float getF(uintptr_t address)
{
	float buff;
	vm_readv(address, &buff, 4);
	return buff;
}

uintptr_t getA(uintptr_t address)
{
	uintptr_t buff;
    vm_readv(address, &buff, SIZE);
    return buff;
}

int getI(uintptr_t address)
{
	int buff;
	vm_readv(address, &buff, 4);
	return buff;
}


enum type {
	TYPE_DWORD,
	TYPE_FLOAT
};

void WriteDword(uintptr_t address, int value) {
	KernelDrivers->writeMemory(address, reinterpret_cast<void*>(&value), sizeof(int));
}

void WriteFloat(uintptr_t address, float value) {
	KernelDrivers->writeMemory(address, reinterpret_cast<void*>(&value), sizeof(float));
}

void Write(uintptr_t address, const char *value, type TYPE) {
    switch (TYPE) {
        case TYPE_DWORD:
            WriteDword(address, atoi(value));
            break;
        case TYPE_FLOAT:
            WriteFloat(address, atof(value));
            break;
    }
}

template<typename T>
void Write2(uintptr_t addr, T value) {
	KernelDrivers->writeMemory(addr, reinterpret_cast<void*>(&value), sizeof(T));
}


Vector3 Multiply_VectorFloat(const Vector3& Vec, float Scale)
{
    Vector3 multiply = {Vec.X * Scale, Vec.Y * Scale, Vec.Z * Scale};
    return multiply;
}

Vector3 Add_VectorVector(struct Vector3 Vect1, struct Vector3 Vect2)
{
    Vector3 add;
    add.X = Vect1.X + Vect2.X;
    add.Y = Vect1.Y + Vect2.Y;
    add.Z = Vect1.Z + Vect2.Z;
    return add;
}

Vector3 getVec3(uintptr_t addr) {
    Vector3 vec;
    vm_readv(addr, &vec, sizeof(vec));
    return vec;
}

#include "UE4.h"


float get_3D_Distance(float Self_x, float Self_y, float Self_z, float Object_x, float Object_y, float Object_z)
{
	float x, y, z;
	x = Self_x - Object_x;
	y = Self_y - Object_y;
	z = Self_z - Object_z;
	return (float)(sqrt(x * x + y * y + z * z));
}


uintptr_t getBase(){
	    FILE *fp;
    uintptr_t addr = 0;
    char filename[32], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    fp = fopen(filename, "rt");
    if (fp != nullptr) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, "libUE4.so")) {
#if defined(__LP64__)
                sscanf(buffer, "%lx-%*s", &addr);
#else
                sscanf(buffer, "%x-%*s", &addr);
#endif
                break;
            }
        }
        fclose(fp);
    }
    return addr;

}


pid_t getPID(char *PackageName) {
	DIR *dir = NULL;
	struct dirent *ptr = NULL;
	FILE *fp = NULL;
	char filepath[256];	
	char filetext[128];
	dir = opendir("/proc");
	if (NULL != dir) {
		while ((ptr = readdir(dir)) != NULL) {
			if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
				continue;
			if (ptr->d_type != DT_DIR)
				continue;
			sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
			fp = fopen(filepath, "r");
			if (NULL != fp) {
				fgets(filetext, sizeof(filetext), fp);
				if (strcmp(filetext, PackageName) == 0) {
					break;
				}
				fclose(fp);
			}
		}
	}
	if (readdir(dir) == NULL) {
		return 0;
	}
	closedir(dir);
	return atoi(ptr->d_name);
}


char* getText(uintptr_t addr) {
	static char txt[42];
	memset(txt, 0, 42);
	char buff[41];
	vm_readv(addr + 4+SIZE, &buff, 41);
	int i;
	for (i = 0; i < 41; i++) {
		if (buff[i] == 0)
			break;

		txt[i] = buff[i];

		if (buff[i] == 67 && i > 10)
			break;

	}
	txt[i + 1] = '\0';
	return txt;
}


float GetPitch(float Fov,float compe,float dist) {
    if ((int) Fov == 70) // no scope
    {
        return ((30.0f / 30) * compe) + dist;
    } else if ((int) Fov == 55) // redot
    {
		return ((33.75f / 30) * compe) + dist;
		
	} else if ((int) Fov == 44) //x2
	{
        return ((45.0f / 30) * compe) + dist;
		
	} else if ((int) Fov == 26) //x3
	{
		return ((60.0f / 30) * compe) + dist;
		
	} else if ((int) Fov == 20)// x4
	{
		return ((86.25f / 30) * compe) + dist;
		
	} else if ((int) Fov == 13)// x6
	{
	    return ((112.5f / 30) * compe) + dist;
		
    } else { // no open scope and x8
		return ((12.0f / 30) * compe) + dist;
	}
    
}

#endif //DCHEATS_PUBGMX_SUPPORT_H

