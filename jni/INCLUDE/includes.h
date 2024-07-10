//
// Created by day on 13/08/2022.
//


#ifndef DCHEAT_PUBGMX_INCLUDES_H
#define DCHEAT_PUBGMX_INCLUDES_H

#include <sys/uio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <sys/un.h>
#include <time.h>
#include <ctype.h>
#include <iostream>
#include <vector>
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "obfuscate.h"

#if defined(__arm__)
int process_vm_readv_syscall = 376;
int process_vm_writev_syscall = 377;
#elif defined(__aarch64__)
int process_vm_readv_syscall = 270;
int process_vm_writev_syscall = 271;
#elif defined(__i386__)
int process_vm_readv_syscall = 347;
int process_vm_writev_syscall = 348;
#else
int process_vm_readv_syscall = 310;
int process_vm_writev_syscall = 311;
#endif

#define LEN sizeof(struct MAPS)

/*
struct D2DVector
{
    float X;
    float Y;
};
*/
struct Vector4 {
    float X;
	float Y;
	float Z;
	float W;
};

Vector4 rot;
Vector3 scale, tran;
int handle = 0;
int height = 1080;
int width = 2340;
//int pid = 0;
pid_t pid = -1;
struct MAPS {
    long int fAddr;
    long int lAddr;
    struct MAPS* next;
};

struct Ulevel {
    uintptr_t addr;
    int size;
};

typedef struct MAPS* PMAPS;

	bool isPlayer(char *name){
		if(strstr(name, OBFUSCATE("BP_PlayerPawn"))) return true;
		if(strstr(name, OBFUSCATE("BP_PlayerCharacter"))) return true;
	//	if(strstr(name, OBFUSCATE("PlanET_FakePlayer"))) return true;
	//	if(strstr(name, OBFUSCATE("BP_PlayerCharacter_PlanX_C"))) return true;
	//	if(strstr(name, OBFUSCATE("PlanX_PlayerCharacter_AI_C"))) return true;
	//	if(strstr(name, OBFUSCATE("BP_PlayerCharacter_Egypt2"))) return true;
	//	if(strstr(name, OBFUSCATE("BP_STPlayer"))) return true;
	return false;

}

bool IsPlayerPawn(char *classname) {
    if (strstr(classname, OBFUSCATE("PlayerPawn")) || strstr(classname, OBFUSCATE("PlayerCharacter")) || strstr(classname, OBFUSCATE("CharacterModelTaget")))
          return true;
    return false;
}


bool IsLootBoxItemsPawn(char *classname){
	if (strstr(classname, OBFUSCATE("PickUpListWrapperActor")) || strstr(classname, OBFUSCATE("AirDropBox"))) return true;
	return false;
}

bool IsVehiclesPawn(char *classname){
	if (strstr(classname, OBFUSCATE("VH")) || (strstr(classname, OBFUSCATE("PickUp_")) && !strstr(classname, OBFUSCATE("BP"))) || strstr(classname, OBFUSCATE("Rony")) || strstr(classname, OBFUSCATE("Mirado")) || strstr(classname, OBFUSCATE("LadaNiva")) || strstr(classname, OBFUSCATE("AquaRail"))) return true;
	return false;	
}


int GrenadesSpawn(char *classname) {
    if (strstr(classname, OBFUSCATE("BP_Grenade_Shoulei_C"))) {
        return 1;
    }
    if (strstr(classname, OBFUSCATE("BP_Grenade_Burn_C"))) {
        return 2;
    }
    if (strstr(classname, OBFUSCATE("BP_Grenade_Stun_C"))) {
        return 3;
    }
    if (strstr(classname, OBFUSCATE("BP_Grenade_Smoke_C"))) {
        return 4;
    }
    return 0; // Return 0 for an unknown type or no match
}

bool IsRedZoneSpawn(char *classname){
	if (strstr(classname, OBFUSCATE("AirAttackBomb"))) return true;
	return false;
}

bool IsItemsPawn(char *classname){
    if (strstr(classname, OBFUSCATE("Pickup_C")) || strstr(classname, OBFUSCATE("PickUp")) || strstr(classname, OBFUSCATE("BP_Ammo")) || strstr(classname, OBFUSCATE("BP_QK")) || strstr(classname, OBFUSCATE("Wrapper"))) return true;
    return false;
}


bool isGrenade(char *name) {
	if (strstr(name, OBFUSCATE("BP_Grenade_Smoke_C"))) return true;
	if (strstr(name, OBFUSCATE("BP_Grenade_Burn_C"))) return true;
	if (strstr(name, OBFUSCATE("BP_Grenade_Stun_C"))) return true;
	if (strstr(name, OBFUSCATE("BP_Grenade_Shoulei_C"))) return true;
	return false;
}

bool isItems(char *name) {
	if (strstr(name, OBFUSCATE("BP_Rifle_AKM_Wrapper_C"))) return true;
	if (strstr(name, OBFUSCATE("BP_Rifle_M416_Wrapper_C"))) return true;
	if (strstr(name, OBFUSCATE("BP_Rifle_SCAR_Wrapper_C"))) return true;
	if (strstr(name, OBFUSCATE("BP_Rifle_M16A4_Wrapper_C"))) return true;
	if (strstr(name, OBFUSCATE("BP_Rifle_M762_Wrapper_C"))) return true;
	if (strstr(name, OBFUSCATE("Helmet_Lv3_C"))) return true;
	if (strstr(name, OBFUSCATE("Armor_Lv3_C"))) return true;
	if (strstr(name, OBFUSCATE("Bag_Lv3"))) return true;
	return false;
}

#define SIZE sizeof(uintptr_t)

#endif //DCHEAT_PUBGMX_INCLUDES_H
