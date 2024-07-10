//
// Created by day on 13/08/2022.
//

#include "Offsets.h"
#include "INCLUDE/struct.h"
#include "INCLUDE/support.h"

#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
///-----------------------------------------------------------------------

uintptr_t GWorld = 0, GNames = 0;

bool india;
bool vetnam;
bool allpkgg;

#if defined(__aarch64__)
struct Actors
{
    uint64_t Enc_1, Enc_2;
    uint64_t Enc_3, Enc_4;
};

struct Chunk
{
    uint32_t val_1, val_2, val_3, val_4;
    uint32_t val_5, val_6, val_7, val_8;
};

uint64_t getActorsArray(uint64_t uLevel, int Actors_Offset, int EncryptedActors_Offset)
{
    if (uLevel < 0x10000000)
        return 0;

    if (Read<uint64_t>(uLevel + Actors_Offset) > 0)
        return uLevel + Actors_Offset;

    if (Read<uint64_t>(uLevel + EncryptedActors_Offset) > 0)
        return uLevel + EncryptedActors_Offset;

    auto AActors = Read<Actors>(uLevel + EncryptedActors_Offset + 0x10);

    if (AActors.Enc_1 > 0)
    {
        auto Enc = Read<Chunk>(AActors.Enc_1 + 0x80);
        return (((Read<uint8_t>(AActors.Enc_1 + Enc.val_1) | (Read<uint8_t>(AActors.Enc_1 + Enc.val_2) << 8)) | (Read<uint8_t>(AActors.Enc_1 + Enc.val_3) << 0x10)) & 0xFFFFFF | ((uint64_t)Read<uint8_t>(AActors.Enc_1 + Enc.val_4) << 0x18) | ((uint64_t)Read<uint8_t>(AActors.Enc_1 + Enc.val_5) << 0x20)) & 0xFFFF00FFFFFFFFFF | ((uint64_t)Read<uint8_t>(AActors.Enc_1 + Enc.val_6) << 0x28) | ((uint64_t)Read<uint8_t>(AActors.Enc_1 + Enc.val_7) << 0x30) | ((uint64_t)Read<uint8_t>(AActors.Enc_1 + Enc.val_8) << 0x38);
    }
    else if (AActors.Enc_2 > 0)
    {
        auto Lost_Actors = Read<uint64_t>(AActors.Enc_2);
        if (Lost_Actors > 0)
        {
            return (uint16_t)(Lost_Actors - 0x400) & 0xFF00 | (uint8_t)(Lost_Actors - 0x04) | (Lost_Actors + 0xFC0000) & 0xFF0000 | (Lost_Actors - 0x4000000) & 0xFF000000 | (Lost_Actors + 0xFC00000000) & 0xFF00000000 | (Lost_Actors + 0xFC0000000000) & 0xFF0000000000 | (Lost_Actors + 0xFC000000000000) & 0xFF000000000000 | (Lost_Actors - 0x400000000000000) & 0xFF00000000000000;
        }
    }
    else if (AActors.Enc_3 > 0)
    {
        auto Lost_Actors = Read<uint64_t>(AActors.Enc_3);
        if (Lost_Actors > 0)
        {
            return (Lost_Actors >> 0x38) | (Lost_Actors << (64 - 0x38));
        }
    }
    else if (AActors.Enc_4 > 0)
    {
        auto Lost_Actors = Read<uint64_t>(AActors.Enc_4);
        if (Lost_Actors > 0)
        {
            return Lost_Actors ^ 0xCDCD00;
        }
    }
    return 0;
}

   #else
   
struct Actors
{
    uint32_t Enc_1, Enc_2;
    uint32_t Enc_3, Enc_4;
};

struct Chunk
{
    uint32_t val_1, val_2;
    uint32_t val_3, val_4;
};

uint32_t getActorsArray(uint32_t uLevel, int Actors_Offset, int EncryptedActors_Offset)
{
    if (uLevel < 0x10000000)
        return 0;

    if (Read<uint32_t>(uLevel + Actors_Offset) > 0)
        return uLevel + Actors_Offset;

    if (Read<uint32_t>(uLevel + EncryptedActors_Offset) > 0)
        return uLevel + EncryptedActors_Offset;

    auto AActors = Read<Actors>(uLevel + EncryptedActors_Offset + 0x0C);

    if (AActors.Enc_1 > 0)
    {
        auto Enc = Read<Chunk>(AActors.Enc_1 + 0x80);

        return (Read<uint8_t>(AActors.Enc_1 + Enc.val_1) | (Read<uint8_t>(AActors.Enc_1 + Enc.val_2) << 8) | (Read<uint8_t>(AActors.Enc_1 + Enc.val_3) << 0x10) | (Read<uint8_t>(AActors.Enc_1 + Enc.val_4) << 0x18));
    }
    else if (AActors.Enc_2 > 0)
    {
        auto Lost_Actors = Read<uint32_t>(AActors.Enc_2);
        if (Lost_Actors > 0)
        {
            return ((unsigned short)Lost_Actors - 0x400) & 0xFF00 | (unsigned char)(Lost_Actors - 0x04) | (Lost_Actors + 0xFC0000) & 0xFF0000 | (Lost_Actors - 0x4000000) & 0xFF000000;
        }
    }
    else if (AActors.Enc_3 > 0)
    {
        auto Lost_Actors = Read<uint32_t>(AActors.Enc_3);
        if (Lost_Actors > 0)
        {
            return (Lost_Actors >> 0x18) | (Lost_Actors << (32 - 0x18));
        }
    }
    else if (AActors.Enc_4 > 0)
    {
        auto Lost_Actors = Read<uint32_t>(AActors.Enc_4);
        if (Lost_Actors > 0)
        {
            return Lost_Actors ^ 0xCDCD00;
        }
    }
    return 0;
}

 #endif


template <typename T>
struct TArray
{
    uintptr_t base;
    int32_t count;
    int32_t max;

    std::vector<T> ToVec() const
    {
        if (!IsValid())
        {
            return {};
        }
        std::vector<T> vec{};
        vec.resize(static_cast<size_t>(count));
        iovec l_iov{&vec[0], static_cast<size_t>(count) * sizeof(T)};
        iovec r_iov{reinterpret_cast<void *>(base), static_cast<size_t>(count) * sizeof(T)};
        syscall(process_vm_readv_syscall, pid, &l_iov, 1, &r_iov, 1, 0);
        return vec;
    }
    T operator[](size_t u) const
    {
        return Read<T>(base + u * sizeof(T));
    }

    bool IsValid() const
    {
        return base && count > 0 && count <= max && max > 0;
    }
};

char *getNameByte(uintptr_t address)
{
    char static lj[64];
    memset(lj, 0, 64);
    unsigned short int nameI[32];
    vm_readv(address, nameI, sizeof(nameI));
    char s[10];
    int i;
    for (i = 0; i < 32; i++)
    {
        if (nameI[i] == 0)
            break;
        sprintf(s, "%d:", nameI[i]);
        strcat(lj, s);
    }
    lj[63] = '\0';

    return lj;
}

/*
    #if defined(__aarch64__)
auto fBypassLOD = [](uintptr_t local_player_ptr,uintptr_t ps_ASTExtraCharacter_PartHitComponent,uintptr_t ps_UPartHitComponent_ConfigCollisionDistSqAngles) -> void
    {
        uintptr_t part_hit_comp_ptr =
            getA(local_player_ptr + ps_ASTExtraCharacter_PartHitComponent);
        if (!part_hit_comp_ptr)
        {
            return;
        }
        auto config_collision_dist_sq_angles = Read<TArray<uint64_t>>(
            part_hit_comp_ptr + ps_UPartHitComponent_ConfigCollisionDistSqAngles);
        if (!config_collision_dist_sq_angles.IsValid())
        {
            return;
        }
        for (size_t u = 0; u != static_cast<size_t>(config_collision_dist_sq_angles.count);
             ++u)
        {
            float value = 90.f;
            Writes<float>(config_collision_dist_sq_angles.base + u * 8 + 4,value);
        }
    };
    #else
auto fBypassLOD = [](uintptr_t local_player_ptr,uintptr_t ps_ASTExtraCharacter_PartHitComponent,uintptr_t ps_UPartHitComponent_ConfigCollisionDistSqAngles) -> void
    {
        uintptr_t part_hit_comp_ptr =
            getA(local_player_ptr + ps_ASTExtraCharacter_PartHitComponent);
        if (!part_hit_comp_ptr)
        {
            return;
        }
        auto config_collision_dist_sq_angles = Read<TArray<uint32_t>>(
            part_hit_comp_ptr + ps_UPartHitComponent_ConfigCollisionDistSqAngles);
        if (!config_collision_dist_sq_angles.IsValid())
        {
            return;
        }
        for (size_t u = 0; u != static_cast<size_t>(config_collision_dist_sq_angles.count);
             ++u)
        {
            float value = 90.f;
            Writes<float>(config_collision_dist_sq_angles.base + u * 8 + 4,value);
        }
    };
    #endif
*/
std::string GetBoxItems(int code)
{
	
if (code == 101006) return "AUG";
if (code == 101008) return "M762";
if (code == 101003) return "SCAR-L";
if (code == 101004) return "M416";
if (code == 101002) return "M16A4";
if (code == 101009) return "Mk47 Mutant";
if (code == 101010) return "G36C";
if (code == 101007) return "QBZ";
if (code == 101001) return "AKM";
if (code == 101005) return "Groza";
if (code == 102005) return "Bizon";
if (code == 102004) return "TommyGun";
if (code == 102007) return "MP5K";
if (code == 102002) return "UMP";
if (code == 102003) return "Vector";
if (code == 102001) return "Uzi";
if (code == 105002) return "DP28";
if (code == 105001) return "M249";
if (code == 103003) return "AWM";
if (code == 103010) return "QBU";
if (code == 103009) return "SLR";
if (code == 103004) return "SKS";
if (code == 103006) return "Mini14";
if (code == 103002) return "M24";
if (code == 103001) return "Kar98k";
if (code == 103005) return "VSS";
if (code == 103008) return "Win94";
if (code == 103007) return "Mk14";
if (code == 104003) return "S12K";
if (code == 104004) return "DBS";
if (code == 104001) return "S686";
if (code == 104002) return "S1897";
if (code == 108003) return "Sickle";
if (code == 108001) return "Machete";
if (code == 108002) return "Crowbar";
if (code == 107001) return "CrossBow";
if (code == 108004) return "Pan";
//pistols
if (code == 106006) return "SawedOff";
if (code == 106003) return "R1895";
if (code == 106008) return "Vz61";
if (code == 106001) return "P92";
if (code == 106004) return "P18C";
if (code == 106005) return "R45";
if (code == 106002) return "P1911";
if (code == 106010) return "Desert Eagle";
//Ammo
if (code == 302001) return "7.62";
if (code == 305001) return "45ACP";
if (code == 303001) return "5.56";
if (code == 301001) return "9mm";
if (code == 306001) return "300Magnum";
if (code == 304001) return "12 Guage";
if (code == 307001) return "Arrow";
//bag helmet vest
if (code == 501006 || code == 501003) return "Bag L 3";
if (code == 501004 || code == 501001) return "Bag L 1";
if (code == 501005 || code == 501002) return "Bag L 2";
if (code == 503002) return "Vest L 2";
if (code == 503001) return "Vest L 1";
if (code == 503003) return "Vest L 3";
if (code == 502002) return "Helmet 2";
if (code == 502001) return "Helmet 1";
if (code == 502003) return "Helmet 3";
//Healthkits
if (code == 601003) return "PainKiller";
if (code == 601002) return "Adrenaline";
if (code == 601001) return "Energy Drink";
if (code == 601005) return "FirstAidKit";
if (code == 601004) return "Bandage";
if (code == 601006) return "Medkit";
//Throwables
if (code == 602001) return "Stung";
if (code == 602004) return "Grenade";
if (code == 602002) return "Smoke";
if (code == 602003) return "Molotov";
//special
if (code == 106007 || code == 308001) return "Flare Gun";
if (code == 403989 || code == 403045 || code == 403187 || code == 403188) return "Gullie Suit";
if (code == 103011) return "Mosin";
if (code == 107005) return "PanzerFaust";

    return "Unknown";
    
}

struct Itemb
{
    std::string Displayname;
};

////--------------------------------------------------------------
struct ShootWeaponBase
{
    uintptr_t FromBase;
    uintptr_t Base;
    uintptr_t ShootWeaponEntity;
    int bIsWeaponFiring;
    int bIsOpenScope;
    ShootWeaponBase(uintptr_t Actor)
    {
    FromBase = getA(Actor + Offsets_WeaponManagerComponent);
    Base = getA(FromBase + Offsets_CurrentWeaponReplicated);
    ShootWeaponEntity = getA(Base + Offsets_ShootWeaponEntity);
    bIsWeaponFiring = getI(Actor + Offsets_bIsWeaponFiring);
    bIsOpenScope = getI(Actor + Offsets_blsGunADS);
//    bool scope = Read<bool>(Actor + Offsets_blsGunADS);
    }

    /////--------------------------------------------------------------
    void setInstantHit()
    {
//    Write(ShootWeaponEntity + Offset_BulletFireSpeed, OBFUSCATE("900000"), TYPE_FLOAT);
    }
    ////--------------------------------------------------------------
    void setLessRecoilsafe()
    {
//    Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilModifierStand, OBFUSCATE("0.4"), TYPE_FLOAT);
//    Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilModifierCrouch, OBFUSCATE("0.4"), TYPE_FLOAT);
    
	Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilSpeedVertical, OBFUSCATE("2.4"), TYPE_FLOAT);
    Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilSpeedHorizontal, OBFUSCATE("2.6"), TYPE_FLOAT);
    }

    ////--------------------------------------------------------------
    void setLessRecoil2()
    {
  //  Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilModifierStand, OBFUSCATE("0.3"), TYPE_FLOAT);
 //   Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilModifierCrouch, OBFUSCATE("0.3"), TYPE_FLOAT);
    
	Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilSpeedVertical, OBFUSCATE("2.0"), TYPE_FLOAT);
    Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilSpeedHorizontal, OBFUSCATE("2.2"), TYPE_FLOAT);
    
 //   Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilSpeedVertical, OBFUSCATE("1.3"), TYPE_FLOAT);
 //   Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilSpeedHorizontal, OBFUSCATE("1.6"), TYPE_FLOAT);
 //   Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecovertySpeedVertical, OBFUSCATE("0.4"), TYPE_FLOAT);
    }
    ////--------------------------------------------------------------
    void setSmallCrosshair()
    {
    Write(ShootWeaponEntity + Offset_GameDeviationFactor, OBFUSCATE("0.7"), TYPE_FLOAT);
    }
    ////--------------------------------------------------------------
    void setHitX()
    {
		
    Write(ShootWeaponEntity + Offset_ExtraHitPerformScale, OBFUSCATE("50"), TYPE_FLOAT);
    
 //   Write(ShootWeaponEntity + Offset_ExtraHitPerformScale, OBFUSCATE("16.0f"), TYPE_FLOAT);//float ExtraHitPerformScale;//[Offset:
  //  Write(ShootWeaponEntity + 0x9e8, OBFUSCATE("-400.0f"), TYPE_FLOAT);//float HUDAlphaDecreaseSpeedScale;//[Offset:

    
    }
    ////--------------------------------------------------------------
    void setZeroRecoil()
    {

//    Write(ShootWeaponEntity + Offset_RecoilKickADS, OBFUSCATE("0.2"), TYPE_FLOAT);
  //  Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilModifierStand, OBFUSCATE("0.3"), TYPE_FLOAT);
 //   Write(ShootWeaponEntity + Offset_RecoilInfo + Offset_RecoilModifierCrouch, OBFUSCATE("0.3"), TYPE_FLOAT);
    }
    ////--------------------------------------------------------------
    void setNoShake()
    {
 //   Write(ShootWeaponEntity + Offset_AnimationKick, OBFUSCATE("0.2"), TYPE_FLOAT);
    }
    ////--------------------------------------------------------------
    void setheadshot()
    {
/*
    Write(ShootWeaponEntity + Offset_WeaponHitPartCoff, OBFUSCATE("5"), TYPE_FLOAT);
    Write(ShootWeaponEntity + Offset_WeaponHitPartCoffZombie, OBFUSCATE("5"), TYPE_FLOAT);
    Write(ShootWeaponEntity + Offset_BulletMomentum, OBFUSCATE("5"), TYPE_FLOAT);
    Write(ShootWeaponEntity + Offset_WeaponWarnUpTime, OBFUSCATE("5"), TYPE_FLOAT);
    Write(ShootWeaponEntity + Offset_BaseImpactDamage, OBFUSCATE("5"), TYPE_FLOAT);
    Write(ShootWeaponEntity + Offset_MaxDamageRate, OBFUSCATE("5"), TYPE_FLOAT);
    Write(ShootWeaponEntity + Offset_DamageImpulse, OBFUSCATE("5"), TYPE_FLOAT);
*/
    }
    ////--------------------------------------------------------------
        void setaimbot1()
    {
    /*
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x0, OBFUSCATE("1090519040"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x4c, OBFUSCATE("1090519040"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x4, OBFUSCATE("1082130432"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x50, OBFUSCATE("1082130432"), TYPE_DWORD);
	*/
    }

    ////--------------------------------------------------------------
    void setaimbot2()
    {
    	/*
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x0) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x0, 4.0);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x8) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x8, 3);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0xC) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0xC, 3);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x10) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x10, 3);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x14) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x14, 3);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x38) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x38, 205);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x3C) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x3C, 1);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x40) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x40, 120);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x44) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x44, 8200);
        if (getI(ShootWeaponEntity + Offset_Aimbotvip + 0x48) != 0) {
        Write2<float>(ShootWeaponEntity + Offset_Aimbotvip + 0x48, 1);
        }
        }
        }
        }
        }
        }
        }
        }
        }
        }
    	*/
    	/*
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x0, OBFUSCATE("1090519040"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x4c, OBFUSCATE("1090519040"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x4, OBFUSCATE("1082130432"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x50, OBFUSCATE("1082130432"), TYPE_DWORD);
	*/
    }
    ////--------------------------------------------------------------
    void setAutoAim()
    {
    	/*
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x0, OBFUSCATE("1090519040"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x4c, OBFUSCATE("1090519040"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x4, OBFUSCATE("1082130432"), TYPE_DWORD);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x50, OBFUSCATE("1082130432"), TYPE_DWORD);
	*/
	/*
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x0, OBFUSCATE("8"), TYPE_FLOAT);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x4c, OBFUSCATE("8"), TYPE_FLOAT);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x4, OBFUSCATE("4"), TYPE_FLOAT);
	Write(ShootWeaponEntity + Offset_Aimbotvip + 0x50, OBFUSCATE("4"), TYPE_FLOAT);
	*/
	
    }
    ////--------------------------------------------------------------

    bool isFiring()
    {
        return (bIsWeaponFiring != 0);
    }
    
    bool isscope()
    {
        return (bIsOpenScope != 0);
    }

    bool isValid()
    {
        return (Base != 0);
    }
};

////--------------------------------------------------------------
struct CameraComponent
{
    uintptr_t Base;
    uintptr_t FieldOfView;
    CameraComponent(uintptr_t Actor)
    {
    Base = getA(Actor + Offset_ThirdPersonCameraComponent);
    FieldOfView = Base + Offset_FieldOfView;
    }

    void setCamFov()
    {
    Write(FieldOfView, OBFUSCATE("90"), TYPE_FLOAT);
    }

    void setCamFov1()
    {
    Write(FieldOfView, OBFUSCATE("95"), TYPE_FLOAT);
    }

    void setCamFov2()
    {
    Write(FieldOfView, OBFUSCATE("100"), TYPE_FLOAT);
    }

    void setCamFov3()
    {
    Write(FieldOfView, OBFUSCATE("105"), TYPE_FLOAT);
    }

    void setCamFov4()
    {
    Write(FieldOfView, OBFUSCATE("110"), TYPE_FLOAT);
    }

    void setCamFov5()
    {
    Write(FieldOfView, OBFUSCATE("115"), TYPE_FLOAT);
    }

    void setCamFov6()
    {
    Write(FieldOfView, OBFUSCATE("120"), TYPE_FLOAT);
    }

    void setCamFov7()
    {
    Write(FieldOfView, OBFUSCATE("125"), TYPE_FLOAT);
    }

    void setCamFov8()
    {
    Write(FieldOfView, OBFUSCATE("130"), TYPE_FLOAT);
    }

    void setCamFov9()
    {
    Write(FieldOfView, OBFUSCATE("135"), TYPE_FLOAT);
    }

    void setCamFov10()
    {
    Write(FieldOfView, OBFUSCATE("140"), TYPE_FLOAT);
    }

    bool isValid()
    {
        return (Base != 0);
    }
};


////--------------------------------------------------------------
    struct SpeedComponent
    {
    uintptr_t Speed;
    uintptr_t Weapon;
    uintptr_t CameraSettings;
    uintptr_t bIsWeaponFiring;
    SpeedComponent(uintptr_t Actor)
    {
    Speed = getA(Actor + Offsets_WeaponManagerComponent);//CharacterWeaponManagerComponent* WeaponManagerComponent;//[Offset: 0x1f08, Size: 8]  //Class: STExtraBaseCharacter.STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
    Weapon = getA(Speed + Offsets_CurrentWeaponReplicated);//STExtraWeapon* CurrentWeaponReplicated;//[Offset: 0x4e0, Size: 8]  //Class: WeaponManagerComponent.ActorComponent.Object
    CameraSettings = getA(Weapon + Offsets_ShootWeaponEntity);//ShootWeaponEntity* ShootWeaponEntityComp;//[Offset: 0xf68, Size: 8]  //Class: STExtraShootWeapon.STExtraWeapon.LuaActor.Actor.Object
    bIsWeaponFiring = getI(Actor + Offsets_bIsWeaponFiring);//bool bIsWeaponFiring;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x1518, Size: 1]  //Class: STExtraBaseCharacter.STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
    }
    void Speedfire()
    {
  //  Write(CameraSettings + Offset_Aimbotvip, OBFUSCATE("100000"), TYPE_FLOAT);
    	
    //Class: STExtraAnimInstanceBase.STPawnAnimInstanceBase.AnimInstance.Object
    Write(CameraSettings + Offset_Aimbottvipp, OBFUSCATE("10000"), TYPE_FLOAT);//SCOPE  //float C_CustomMovementBlendTime;//[Offset: 0x7cc, Size: 0x4]
    Write(CameraSettings + Offset_Aimbotttvippp, OBFUSCATE("10000"), TYPE_FLOAT);//FIRE   //float SwitchingPoseTimerInternal;//[Offset: 0x7c4, Size: 0x4]
 
    }
    bool isFiring() { return (bIsWeaponFiring != 0); }
    bool isValid() { return (Speed != 0); }
    };
    
    
////--------------------------------------------------------------
PlayerWeapon getPlayerWeapon(uintptr_t base)
{
    PlayerWeapon weapn;
    uintptr_t addr[3];
    vm_readv(Read<uintptr_t>(base + Offsets_ActorChildren), addr, sizeof(addr));
    for (int W = 0; W < (sizeof(addr) / sizeof(uintptr_t)); W++)
    {
        if (Read<int>(addr[W] + Offsets_DrawShootLineTime) == 2)
        {
            weapn.isWeapon = true;
            weapn.id = Read<int>(Read<uintptr_t>(addr[W] + Offsets_WeaponEntityComp) + Offsets_WeaponId);
            weapn.ammo = Read<int>(addr[W] + Offsets_CurBulletNumInClip);
        }
    }
    return weapn;
}

using namespace std;


string executeCommand(const char* cmd) {
    string result = "";
    char buffer[128];
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "Error";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

string getDeviceType() {
    return executeCommand("getprop ro.product.model");
}

string getAndroidVersion() {
    return executeCommand("getprop ro.build.version.release");
}



string getKernelVersion() {
    char buffer[128];
    string result = "";
    FILE* pipe = popen("uname -r", "r");
    if (!pipe) return "Error";
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

string getDeviceModel() {
    ifstream cpuinfo("/proc/cpuinfo");
    string line, result = "Unknown Model";

    while (getline(cpuinfo, line)) {
        if (line.find("model name") != string::npos || line.find("Hardware") != string::npos || line.find("Processor") != string::npos) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                result = line.substr(pos + 2);
                break;
            }
        }
    }
    cpuinfo.close();
    return result;
}



int main(int argc, char *argv[]) {
	
	// Usage example
    KernelDrivers->initKey("my_key");
    // Other operations...
  //  delete KernelDrivers;
	
	
    ofstream MyFile("/data/local/logsock");

    // Check if secure boot is enabled
    string secureBootStatus = executeCommand("mokutil --sb-state");
    if (secureBootStatus.find("SecureBoot enabled") != string::npos) {
    MyFile << "\n[System] Secure Boot is enabled\n";
    } else {
    MyFile << "\n[System] Secure Boot is disabled\n";
    }

    // Print operating system
    string osInfo = executeCommand("uname -a");
    MyFile << "\n[System] Operating System: " << osInfo;

    MyFile << "\n[System] Kernel Version: " << getKernelVersion();
    MyFile << "\n[System] Device System Model: " << getDeviceModel();

    // Print device model
    MyFile << "\n[System] Device Model: " << getDeviceType();

    // Print Android version
    MyFile << "\n[System] Android Version: A" << getAndroidVersion();

    MyFile << "\n[Server] main done";


///---------------------------------------------------------------------------------
	india = false;
	vetnam = false;
	allpkgg = false;
	
    if (!Create())
    {
    	MyFile << "[Server] Socket can't create";
        perror("[Server] Socket can't create");
        return -1;
    }
    if (Connect())
    {
    	MyFile << "\n[Server] Socket connected";
        printf("[Server] Socket connected");
        SetValue sv{};
        receive((void *)&sv);
        if (sv.mode == 1)
        {
        MyFile << "\n[Server] Mode 1: global";
        allpkgg = true;
        GNames = Offsets_GNames;
        GWorld = Offsets_GWorld;
        strcpy(version, "com.tencent.ig");
        }
        else if (sv.mode == 2)
        {
        MyFile << "\n[Server] Mode 2: koria";
        allpkgg = true;
        GNames = Offsets_GNames;
        GWorld = Offsets_GWorld;
        strcpy(version, "com.pubg.krmobile");
        }
        else if (sv.mode == 3)
        {
        MyFile << "\n[Server] Mode 3: vng";
        vetnam = true;
        GNames = Offsets_GNamesvn;
        GWorld = Offsets_GWorldvn;
        strcpy(version, "com.vng.pubgmobile");
        }
        else if (sv.mode == 4)
        {
        MyFile << "\n[Server] Mode 4: rekoo";
        allpkgg = true;
        GNames = Offsets_GNames;
        GWorld = Offsets_GWorld;
        strcpy(version, "com.rekoo.pubgm");
        }
        else if (sv.mode == 5)
        {
        MyFile << "\n[Server] Mode 5: India";
        allpkgg = true;
        GNames = Offsets_GNamesin;
        GWorld = Offsets_GWorldin;
        strcpy(version, "com.pubg.imobile");
        }

        pid = getPID(version);
        if (pid < 10)
        {
        MyFile << "\n[Server] Can't get game pid";
        perror("[Server] Can't get game pid");
        return -1;
        }
        MyFile << "\n[Server] Game pid obtained: " << pid;

        MyFile << "\n[Server] Initializing Kernel Drivers with pid: " << pid;
        KernelDrivers->initialize(pid);
        MyFile << "\n[Server] Kernel drivers initialized";
        
        MyFile << "\n[Server] Getting module base for libUE4.so";
     	uintptr_t base = KernelDrivers->getModuleBase("libUE4.so");
     	MyFile << "\n[Server] Module base for libUE4.so: " << std::hex << base;

    //    uintptr_t base = getBase();
        if (base <= 0)
        {
        MyFile << "\n[Server] Can't get UE4 base addr";
        perror("[Server] Can't get UE4 base addr");
        MyFile.close();
        return -1;
        }
        MyFile << "\n[Server] UE4 base address obtained: " << std::hex << base;
           
		   
    MyFile.close();
		    
    int Login = 25;
	bool aimbot = true;
	bool aimKnoced = false;
	
	bool aimAI = true;///*******
	
	int firing = 0, ads = 0, adss = 0;
	int aimBy = 1, aimFor = 1, aimWhen = 3;
    float aimRadius = 200, aimDist = 50, aimSpeed = 660 , recCom = 50;

	uintptr_t LocalController;
    int changed = 1;
	Vector3 targetAimPos;///******************
    uintptr_t MinimalView = 0;///********************
    int isFier = 0;///********************
    struct Vector3 xyz, exyz, targetLoc;
    
    #if defined(__aarch64__)
   	uint64_t cameraManager;
    #else
   	uint32_t cameraManager;
    #endif
    
    struct Vector3 cam;
    struct Vector3 pointingAngle,CameraW;
       
    float maxDist = FLT_MAX;
    uintptr_t enAddrPntr;

    uintptr_t PlayerCameraManager, STPlayerController;

    int myteamID = 101;
    char name[100];
    uintptr_t gname_buff[30];
    char loaded[0x4000], loadedpn[20];
        
    char cont[0x500];
    char boneData[1024];
        
    D3DMatrix vMat;
    char weaponData[100];

    bool isLessRecoilsafe = false;
    bool isLessRecoil2 = false;
    bool isZeroRecoil = false;
    bool isInstantHit = false;
    bool isSmallCrosshair = false;
    bool isFastSwitchWeapon = false;
    bool isHitX = false;
    bool isNoShake = false;
    bool isheadshot = false;

    bool isCamFov = false;
    bool isCamFov1 = false;
    bool isCamFov2 = false;
    bool isCamFov3 = false;
    bool isCamFov4 = false;
    bool isCamFov5 = false;
    bool isCamFov6 = false;
    bool isCamFov7 = false;
    bool isCamFov8 = false;
    bool isCamFov9 = false;
    bool isCamFov10 = false;

    bool isAutoAim = false;
    bool isaimbot1 = false;
    bool isaimbot2 = false;

    bool isBulletTrack = false;
    int DistBullet = false;
    int FovBullet = false;
    bool temb = false;
    
    int isVisible = 0;
    
    Request request{};
    Response response{};
    
    while ((receive((void *)&request) > 0)) {
    	
    if (request.Mode == InitMode) {
    	
    height = request.ScreenHeight;
    width = request.ScreenWidth;
    	
	aimRadius = (float)request.options.aimingRange;
    aimDist = (float)request.options.aimingDist;
    aimSpeed = (float)request.options.aimingSpeed;
    recCom = (float)request.options.recCompe;
	aimFor = request.options.aimbotmode;
	aimbot = request.options.openState == 0;
	aimWhen = request.options.aimingState;
	aimBy = request.options.priority;
	aimKnoced = request.options.pour;
    aimAI = request.options.ignoreBot;


                isLessRecoilsafe = request.memory.LessRecoilsafe;
                isLessRecoil2 = request.memory.LessRecoil2;

                isZeroRecoil = request.memory.ZeroRecoil;
                isInstantHit = request.memory.InstantHit;
                isHitX = request.memory.HitX;
                isNoShake = request.memory.NoShake;
                isSmallCrosshair = request.memory.SmallCrosshair;
                isFastSwitchWeapon = request.memory.FastSwitchWeapon;

                isaimbot1 = request.memory.aimbot1;
                isaimbot2 = request.memory.aimbot2;
                isAutoAim = request.memory.AutoAim;

                isheadshot = request.memory.headshot;

                isCamFov = request.memory.isCamFov;
                isCamFov1 = request.memory.isCamFov1;
                isCamFov2 = request.memory.isCamFov2;
                isCamFov3 = request.memory.isCamFov3;
                isCamFov4 = request.memory.isCamFov4;
                isCamFov5 = request.memory.isCamFov5;
                isCamFov6 = request.memory.isCamFov6;
                isCamFov7 = request.memory.isCamFov7;
                isCamFov8 = request.memory.isCamFov8;
                isCamFov9 = request.memory.isCamFov9;
                isCamFov10 = request.memory.isCamFov10;
                
                isBulletTrack = request.memory.isBulletTrack;///**************************
                FovBullet = request.memory.FovBullet;///****************************
                
           //     UseAimHelper(isBulletTrack);

            }

            response.Success = false;
            response.PlayerCount = 0;
            response.VehicleCount = 0;
            response.ItemsCount = 0;
            response.GrenadeCount = 0;
          	response.DeadBoxItemsCount = 0;
            response.ZoneCount = 0;
            response.InLobby = false;
          	
            auto PTarget = -1;
            auto MxDist = FLT_MAX;


        #if defined(__aarch64__)
        uintptr_t gname = Read<uintptr_t>(Read<uintptr_t>(base + GNames) + 0x110);
        uintptr_t uWorld = Read<uintptr_t>(Read<uintptr_t>(base + GWorld) - 0x20);
    //    uintptr_t uWorld = Read<uintptr_t>(Read<uintptr_t>(Read<uintptr_t>(base + Offsets_GWorld1) + 0x58) + 0x78);

        uintptr_t uLevel = Read<uintptr_t>(uWorld + 0x30);
        uintptr_t PlayerController = Read<uintptr_t>(Read<uintptr_t>(Read<uintptr_t>(uWorld + 0x38) + 0x78) + 0x30);
        uintptr_t uMyObject = Read<uintptr_t>(PlayerController + Offsets_STExtraBaseCharacter);
        uintptr_t PlayerCameraManager = Read<uintptr_t>(PlayerController + Offset_PlayerCameraManager);
    //    uintptr_t ActorsPointerAddress = getActorsArray(uLevel, 0xa0, 0x448); //--ActorsPointerAddress
    //    auto actors = Read<TArray<uint64_t>>(ActorsPointerAddress);
    //    uintptr_t ULevelToAActorsCount = Read<int>(ActorsPointerAddress + 0x8);
    auto ActorArray = Read<TArray<uint64_t>>(getActorsArray(uLevel, 0xa0, 0x448));
        #else
        uintptr_t gname = Read<uintptr_t>(Read<uintptr_t>(base + GNames) + 0x88);
        uintptr_t uWorld = Read<uintptr_t>(Read<uintptr_t>(base + GWorld) + 0x3C);
    //    uintptr_t uWorld = Read<uintptr_t>(Read<uintptr_t>(Read<uintptr_t>(base + Offsets_GWorld1) + 0x38) + 0x58);

        uintptr_t uLevel = Read<uintptr_t>(uWorld + 0x20);
        uintptr_t PlayerController = Read<uintptr_t>(Read<uintptr_t>(Read<uintptr_t>(uWorld + 0x24) + 0x60) + 0x20);
        uintptr_t  uMyObject = Read<uintptr_t>(PlayerController + Offsets_STExtraBaseCharacter);
        uintptr_t PlayerCameraManager = Read<uintptr_t>(PlayerController + Offset_PlayerCameraManager);
   //     uintptr_t ActorsPointerAddress = getActorsArray(uLevel, 0x70, 0x334); //--ActorsPointerAddress
    //    auto actors = Read<TArray<uint32_t>>(ActorsPointerAddress);
    //    uintptr_t ULevelToAActorsCount = Read<int>(ActorsPointerAddress + SIZE);
    auto ActorArray = Read<TArray<uint32_t>>(getActorsArray(uLevel, 0x70, 0x334));
        #endif

    MinimalViewInfo POV = MinimalViewInfo();

	if (PlayerCameraManager) {
    auto CameraCache = Read<CameraCacheEntry>(Read<uintptr_t>(PlayerController + Offset_PlayerCameraManager) + Offset_CameraCacheEntry);
    POV = CameraCache.POV;
	}

    
    response.fov = tanf(POV.FOV * ((float)PI) / 360.0f);
    vm_readv(gname, &gname_buff, sizeof(gname_buff));
    float nearest = -1.0f;
    firing = 0;
        
            
 //   for (int i = 0; i < ULevelToAActorsCount; i++) {
 //   uintptr_t Actor = actors[i];
 
	for (int i = 0; i < ActorArray.count; i++) {
    uintptr_t Actor = ActorArray[i]; 
    
    
    if (Read<int>(Actor + SIZE) != 8)
    continue;

    int ids = Read<int>(Actor + 8 + 2 * SIZE);
    int page = ids / 0x4000;
    int index = ids % 0x4000;
    if (page < 1 || page > 30)
    continue;
    if (gname_buff[page] == 0)
    gname_buff[page] = getA(gname + page * SIZE);
    strcpy(name, getText(getA(gname_buff[page] + index * SIZE)));
    if (strlen(name) < 5)
    continue;

		   
    auto oType = Read<int>(Actor + Offsets_oType);
	if (IsPlayerPawn(name)) {
	
//    if (getF(Actor + Offsets_WalkSpeed) == 479.5) {
	
    if (Read<int>(Actor + Offsets_bDead))
    continue;
    if (!Read<uintptr_t>(Actor + Offsets_SkeletalMeshComponent))
    continue;
    if (!Read<uintptr_t>(Actor + Offsets_CharacterMovementComponent))
    continue;
                        
     	
//	vm_readv(Actor + Offsets_Health, healthbuff, sizeof(healthbuff));
//	if (healthbuff[1] > 200.0f || healthbuff[1] < 50.0f || healthbuff[0] > healthbuff[1] || healthbuff[0] < 0.0f)
//	continue;
	if(Read<float>(Actor + Offsets_NearDeathBreath) <= 0.0f)
    continue;
	
    float Health[2];
    vm_readv(Actor + Offsets_Health, Health, sizeof(Health));
    PlayerData *data = &response.Players[response.PlayerCount];
    data->Health = Health[0] / Health[1] * 100;
    data->HealthKnock = getF(Actor + Offsets_NearDeathBreath);
    data->HealthKnockMax = getF(getA(Actor + Offsets_NearDeatchComponent) + Offsets_BreathMax);
    data->TeamID = Read<int>(Actor + Offsets_TeamID);
 //   uintptr_t me = Read<int>(Actor + Offsets_Role);
     	
    if (Actor == uMyObject)
    {

    if (aimbot) {
    /*
	uintptr_t control = getA(Actor + Offsets_STPlayerController);
	cameraManager = getA(control + Offset_PlayerCameraManager);
	if (aimWhen == 3 || aimWhen == 2)
	vm_readv(Actor + Offsets_bIsWeaponFiring, &firing, 1);
	if (aimWhen == 3 || aimWhen == 1)
	vm_readv(Actor + Offsets_blsGunADS, &ads, 1);
	*/
	}

    if (request.memory.isBulletTrack) {
    /*
    if(firing) {
//    fBypassLOD(Actor,Offsets_PartHitComponent,Offsets_OpenCollisionLODAngle);
    }
    uintptr_t control = getA(Actor + Offsets_STPlayerController);
	cameraManager = getA(control + Offset_PlayerCameraManager);
	if (aimWhen == 3 || aimWhen == 2)
	vm_readv(Actor + Offsets_bIsWeaponFiring, &isFier, 1);
	if (aimWhen == 3 || aimWhen == 1)
	vm_readv(Actor + Offsets_blsGunADS, &adss, 1);
	*/
    }


    ShootWeaponBase shootWeaponBase(Actor);
    if (shootWeaponBase.isValid()) {
	if (shootWeaponBase.isscope()) {

    if (isLessRecoilsafe)
    {
    shootWeaponBase.setLessRecoilsafe();
    }
                
    if (isLessRecoil2)
    {
    shootWeaponBase.setLessRecoil2();
    }
    
    if (isaimbot1) {//aimbot icon
    shootWeaponBase.setaimbot1();
    SpeedComponent speedComponent(Actor);
    if (speedComponent.isValid())
	{
    speedComponent.Speedfire();
    }
    }
    
    if (isaimbot2)
    {
    shootWeaponBase.setaimbot2();
    SpeedComponent speedComponent(Actor);
    if (speedComponent.isValid())
	{
    speedComponent.Speedfire();
    }
    }
    
    if (isAutoAim)
	{
    shootWeaponBase.setAutoAim();
    SpeedComponent speedComponent(Actor);
    if (speedComponent.isValid())
	{
    speedComponent.Speedfire();
    }
    }
    
    }
    
    if (shootWeaponBase.isFiring()) {
    if (isZeroRecoil)
	{
    shootWeaponBase.setZeroRecoil();
    }
                        
    if (isInstantHit)
	{
    shootWeaponBase.setInstantHit();
    }
                  
    if (isHitX)
	{
    shootWeaponBase.setHitX();
    }
    
    if (isNoShake)
	{
    shootWeaponBase.setNoShake();
    }
    
    if (isSmallCrosshair)
	{
    shootWeaponBase.setSmallCrosshair();
    }
    
    if (isheadshot)
	{
    shootWeaponBase.setheadshot();
    }
    
    }
    
    }
    if (isFastSwitchWeapon)
	{

    }

    CameraComponent cameraComponent(Actor);
    if (cameraComponent.isValid())
	{
		
    if (isCamFov)
	{
    cameraComponent.setCamFov();
    }
    
    if (isCamFov1)
	{
    cameraComponent.setCamFov1();
    }
    
    if (isCamFov2)
	{
    cameraComponent.setCamFov2();
    }
    
    if (isCamFov3)
	{
    cameraComponent.setCamFov3();
    }
    
    if (isCamFov4)
	{
    cameraComponent.setCamFov4();
    }
    
    if (isCamFov5)
	{
    cameraComponent.setCamFov5();
    }
    
    if (isCamFov6)
	{
    cameraComponent.setCamFov6();
    }
    
    if (isCamFov7)
	{
    cameraComponent.setCamFov7();
    }
    
    if (isCamFov8)
	{
    cameraComponent.setCamFov8();
    }
    
    if (isCamFov9)
	{
    cameraComponent.setCamFov9();
    }
    
    if (isCamFov10)
	{
    cameraComponent.setCamFov10();
    }
    
    }
   
    myteamID = data->TeamID;
    continue;
    }
 //   else if (me != 257)
 //   continue;

    if (data->TeamID == myteamID && myteamID <= 100)
    continue;
    
//	int IsBot = Read<int>(Actor + Offsets_bIsAI);
//	bool isBot = (IsBot != 0);
	
    if (vetnam){
    auto RootComponentPtr = Read<uintptr_t>(Actor + Offsets_RootComponent);
    auto Pos = Read<Vector3>(RootComponentPtr + Offsets_Position);
    auto RelPos = Read<Vector3>(RootComponentPtr + Offsets_Position2);
    Vector3 DifferenceinLocation = ((RelPos.X==0 && RelPos.Y==0) || (RelPos==Pos)) ? Vector3(0,0,0) : RelPos - Pos; 
    auto HeadPos = GetBonePos(Actor, BoneID::Head) + DifferenceinLocation;
    data->HeadLocation = WorldToScreen(HeadPos, POV);
    bool shit = false;
    data->RadarPosition = WorldToRadar(POV.Rotation.Yaw,POV.Location,HeadPos, 0.f, 0.f, Vector3(width, height, 0), shit);
    }
    
    if (allpkgg){
    auto HeadPos = GetBonePos(Actor, BoneID::Head);
    data->HeadLocation = WorldToScreen(HeadPos, POV);
    bool shit = false;
    data->RadarPosition = WorldToRadar(POV.Rotation.Yaw,POV.Location,HeadPos, 0.f, 0.f, Vector3(width, height, 0), shit);
    }

    data->Distance = Vector3::Distance(GetBonePos(Actor, BoneID::Root), POV.Location) / 100.0f;
    data->EnemyPoseSate = getI(Actor + Offsets_CurrentStates);
    
    auto DistAim = Vector2::Distance(Vector2((float)(width / 2), (float)(height / 2)), Vector2(data->HeadLocation.X, data->HeadLocation.Y));
    if (DistAim < MxDist)
    {
    PTarget = i;
    MxDist = DistAim;
    }

    if (data->Distance > 500.0f)
    continue;
    
    vm_readv(Actor + Offsets_bIsAI, &data->isBot, sizeof(data->isBot));
    strcpy(data->PlayerNameByte, OBFUSCATE("66:79:84:"));
    strcpy(data->PlayerNation, OBFUSCATE("69:999:000:"));
    strcpy(data->PlayerUID, OBFUSCATE("66:111:116:"));
    if (data->HeadLocation.Z > -0.001f && data->HeadLocation.X < width + 100 && data->HeadLocation.X > -50)
    {
          int pbones[15] = {5, 5, 2, 12, 33, 13, 34, 14, 35, 54, 58, 54, 58, 55, 59};
    const int tbones[15] = {5, 4, 2, 14, 35, 15, 36, 18, 40, 55, 59, 56, 60, 57, 61};
    const int mbones[15] = {5, 5, 2, 8, 14, 9, 15, 10, 16, 19, 22, 20, 24, 21, 24};

    if (strstr(name, "BP_CharacterModelTaget_C")) {
        std::copy(std::begin(tbones), std::end(tbones), pbones);
    } else if (strstr(name, "BP_PlayerPawn_TPlanAI_C")) {
        std::copy(std::begin(mbones), std::end(mbones), pbones);
    }
    
    
    PlayerBone Bone;
    Bone.isBone = true;
    Bone.neck = GetBonePosToScreen(Actor, pbones[0], POV);
    Bone.cheast = GetBonePosToScreen(Actor, pbones[1], POV);
    Bone.pelvis = GetBonePosToScreen(Actor, pbones[2], POV);
    Bone.lSh = GetBonePosToScreen(Actor, pbones[3], POV);
    Bone.rSh = GetBonePosToScreen(Actor, pbones[4], POV);
    Bone.lElb = GetBonePosToScreen(Actor, pbones[5], POV);
    Bone.rElb = GetBonePosToScreen(Actor, pbones[6], POV);
    Bone.lWr = GetBonePosToScreen(Actor, pbones[7], POV);
    Bone.rWr = GetBonePosToScreen(Actor, pbones[8], POV);
    Bone.lTh = GetBonePosToScreen(Actor, pbones[9], POV);
    Bone.rTh = GetBonePosToScreen(Actor, pbones[10], POV);
    Bone.lKn = GetBonePosToScreen(Actor, pbones[11], POV);
    Bone.rKn = GetBonePosToScreen(Actor, pbones[12], POV);
    Bone.lAn = GetBonePosToScreen(Actor, pbones[13], POV);
    Bone.rAn = GetBonePosToScreen(Actor, pbones[14], POV);
    Bone.root = GetBonePosToScreen(Actor, BoneID::Root, POV);
//    data->isBot = isBot;
    data->Weapon = getPlayerWeapon(Actor);
    data->Bone = Bone;
    if (!data->isBot)
    {
    strcpy(data->PlayerNameByte, getNameByte(getA(Actor + Offsets_PlayerName)));
    strcpy(data->PlayerNation, getNameByte(getA(Actor + Offsets_PlayerNation)));
    strcpy(data->PlayerUID, getNameByte(getA(Actor + Offsets_Playeruid)));
    if (strlen(data->PlayerNameByte) < 4)
    continue;
    if (strlen(data->PlayerNation) < 4)
    continue;
    if (strlen(data->PlayerUID) < 4)
    continue;
    }
    }
    if (response.PlayerCount >= maxplayerCount)
    {
    continue;
    }
                        
    ///******************************************************************
    if(ads){
    }else{
    }
    float aimbotDD = ads ? request.memory.scopeDistance : aimDist;

    if (data->HeadLocation.Z >= 1.0f && (aimKnoced || data->Health > 0) && data->Distance <= aimbotDD && !data->isVisible && aimbot) {
    /*
    if (!aimAI && data->isBot) {
    } else {
	float centerDist = sqrt((data->HeadLocation.X - width / 2) * (data->HeadLocation.X - width / 2) + (data->HeadLocation.Y - height / 2) * (data->HeadLocation.Y - height / 2));
	if (centerDist < aimRadius) {
	if (aimBy != 1)
	centerDist = data->Distance;
	if (nearest > centerDist || nearest < 0) {
	nearest = centerDist;
    if (aimFor == 1) {
    uintptr_t boneAddr = getA(Actor + Offsets_SkeletalMeshComponent);
    struct D3DMatrix baseMatrix = getOMatrix(boneAddr + Offsets_FixAttachInfoList);
    boneAddr = getA(boneAddr + Offsets_MinLOD);
    struct D3DMatrix oMatrix = getOMatrix(boneAddr + (6) * 48);
    targetAimPos = mat2Cord(oMatrix, baseMatrix);
    }
    else if (aimFor == 2) {
    uintptr_t boneAddr = getA(Actor + Offsets_SkeletalMeshComponent);
    struct D3DMatrix baseMatrix = getOMatrix(boneAddr + Offsets_FixAttachInfoList);
    boneAddr = getA(boneAddr + Offsets_MinLOD);
    struct D3DMatrix oMatrix = getOMatrix(boneAddr + (4) * 48);
    targetAimPos = mat2Cord(oMatrix, baseMatrix);;
    }
    else {
    uintptr_t boneAddr = getA(Actor + Offsets_SkeletalMeshComponent);
    struct D3DMatrix baseMatrix = getOMatrix(boneAddr + Offsets_FixAttachInfoList);
    boneAddr = getA(boneAddr + Offsets_MinLOD);
    struct D3DMatrix oMatrix = getOMatrix(boneAddr + (2) * 48);
    targetAimPos = mat2Cord(oMatrix, baseMatrix);
    }

    Vector3 cam = POV.Location;
    uintptr_t MovementComponent = getA(Actor + Offsets_MovementCharacter);
    uintptr_t CurrentVehicle = getA(Actor + Offsets_CurrentVehicle);
    float Dist = Vector3::Distance(cam, targetAimPos) / 100.0f;

    if (aimSpeed != 0) {
    if (CurrentVehicle) {
    Vector3 LinearVelocity = getVec3(CurrentVehicle + Offsets_ReplicatedMovement);
    auto timeToTravelX = Dist / targetAimPos.X + 0.12;
    auto timeToTravelY = Dist / targetAimPos.Y + 0.12;
    auto timeToTravelZ = Dist / targetAimPos.Z + 0.12;
    targetAimPos.X += LinearVelocity.X * timeToTravelX;
    targetAimPos.Y += LinearVelocity.Y * timeToTravelY;
    targetAimPos.Z += LinearVelocity.Z * timeToTravelZ;
    } else {
    Vector3 Velocity = Read<Vector3>(getA(Actor + Offsets_STCharacterMovement) + Offsets_Velocity);
    auto timeToTravelX = Dist / targetAimPos.X + 0.12;
    auto timeToTravelY = Dist / targetAimPos.Y + 0.12;
    auto timeToTravelZ = Dist / targetAimPos.Z + 0.12;
    targetAimPos.X += Velocity.X * timeToTravelX;
    targetAimPos.Y += Velocity.Y * timeToTravelY;
    targetAimPos.Z += Velocity.Z * timeToTravelZ;
    }
    }
    SetAimSwipeSpeed(0.20);
    SetAimRecoilCompensation(0.02);
    if (recCom > 1) {
    if (firing)
    SetAimRecoilCompensation(0.70);
    }
	}
	}
	}
	*/
    }


    if(adss){
    }else{
    }
    float dd = adss ? request.memory.scopeDistance : request.memory.DistBullet;
    if (data->HeadLocation.Z > -0.001f && (aimKnoced || data->Health > 0) > 0 && !data->isVisible && request.memory.isBulletTrack && data->Distance <= dd )//&& !data->isBot
    {
    /*
    if (!aimAI && data->isBot) {
    } else {
    float centerDist = sqrt((data->HeadLocation.X - width / 2) * (data->HeadLocation.X - width / 2) +
    (data->HeadLocation.Y - height / 2) * (data->HeadLocation.Y - height / 2));
    if (centerDist < request.memory.FovBullet) {
    if (aimBy != 1) {
    centerDist = data->Distance;
    }
    if (nearest > centerDist || nearest < 0) {
    nearest = centerDist;
    if (aimFor == 1) {
    uintptr_t boneAddr = getA(Actor + Offsets_SkeletalMeshComponent);
    struct D3DMatrix baseMatrix = getOMatrix(boneAddr + Offsets_FixAttachInfoList);
    boneAddr = getA(boneAddr + Offsets_MinLOD);
    // cheast 1
    struct D3DMatrix oMatrix = getOMatrix(boneAddr + (6) * 48);
    targetAimPos = mat2Cord(oMatrix, baseMatrix);
    }    
    else if (aimFor == 2) {
    uintptr_t boneAddr = getA(Actor + Offsets_SkeletalMeshComponent);
    struct D3DMatrix baseMatrix = getOMatrix(boneAddr + Offsets_FixAttachInfoList);
    boneAddr = getA(boneAddr + Offsets_MinLOD);
    // cheast 1
    struct D3DMatrix oMatrix = getOMatrix(boneAddr + (4) * 48);
    targetAimPos = mat2Cord(oMatrix, baseMatrix);;
    }
    else {
    uintptr_t boneAddr = getA(Actor + Offsets_SkeletalMeshComponent);
    struct D3DMatrix baseMatrix = getOMatrix(boneAddr + Offsets_FixAttachInfoList);
    boneAddr = getA(boneAddr + Offsets_MinLOD);
    // cheast 1
    struct D3DMatrix oMatrix = getOMatrix(boneAddr + (2) * 48);
    targetAimPos = mat2Cord(oMatrix, baseMatrix);
    }
    
    }
    }
    }
    */
    }


                response.PlayerCount++;
                }else if (strstr(name, OBFUSCATE("VH")) || (strstr(name, OBFUSCATE("PickUp_")) && !strstr(name, OBFUSCATE("BP"))) || strstr(name, OBFUSCATE("Rony")) || strstr(name, OBFUSCATE("Mirado")) || strstr(name, OBFUSCATE("LadaNiva")) || strstr(name, OBFUSCATE("AquaRail"))) {
                VehicleData *data = &response.Vehicles[response.VehicleCount];
                auto Pos = Read<Vector3>(Read<uintptr_t>(Actor + Offsets_RootComponent) + Offsets_Position2);

                uintptr_t VehicleCComp = Read<uintptr_t>(Actor + Offset_VehicleCommon);

                data->Fuel = Read<float>(VehicleCComp + Offset_VFuel) / Read<float>(VehicleCComp + Offset_VFuelMax) * 100;
                data->Health = Read<float>(VehicleCComp + Offset_VHp) / Read<float>(VehicleCComp + Offset_VHpMax) * 100;

                data->Location = WorldToScreen(Pos, POV);
                
                if (data->Location.Z > 0) {
                
                data->Distance = Vector3::Distance(Pos, POV.Location) / 100.0f;
                strcpy(data->VehicleName, name);
                if (response.VehicleCount >= maxvehicleCount)
                continue;
                response.VehicleCount++;
                }   
                }else if (strstr(name, OBFUSCATE("Pickup_C")) || strstr(name, OBFUSCATE("PickUp")) || strstr(name, OBFUSCATE("BP_Ammo")) || strstr(name, OBFUSCATE("BP_QK")) || strstr(name, OBFUSCATE("Wrapper"))) {

                ItemData *data = &response.Items[response.ItemsCount];
                auto Pos = Read<Vector3>(Read<uintptr_t>(Actor + Offsets_RootComponent) + Offsets_Position2);
                   
                data->Location = WorldToScreen(Pos, POV);
                
                if (data->Location.Z > 0) {
                
                data->Distance = Vector3::Distance(Pos, POV.Location) / 100.0f;
                if (data->Distance > 200.0f) {
                continue;
				}
                        
                         
                strcpy(data->ItemName, name);
                if (response.ItemsCount >= maxitemsCount) 
                continue;
                response.ItemsCount++;
                }
                }else if (strstr(name, OBFUSCATE("BP_AirDropPlane_C")) || strstr(name, OBFUSCATE("PlayerDeadInventoryBox_C")) || strstr(name, OBFUSCATE("BP_AirDropBox_C"))) {

				ItemData *data = &response.Items[response.ItemsCount];
                auto Pos = Read<Vector3>(Read<uintptr_t>(Actor + Offsets_RootComponent) + Offsets_Position2);
                    
                data->Location = WorldToScreen(Pos, POV);
                
                if (data->Location.Z > 0) {  
                
				data->Distance = Vector3::Distance(Pos, POV.Location) / 100.0f;
                strcpy(data->ItemName, name);
                        
                if (response.ItemsCount >= maxitemsCount) {
                continue;
				}
                    
                response.ItemsCount++;
                }    
                }else if (isGrenade(name)) {
                	
                GrenadeData *data = &response.Grenade[response.GrenadeCount];
                auto Pos = Read<Vector3>(Read<uintptr_t>(Actor + Offsets_RootComponent) + Offsets_Position2);
                data->Location = WorldToScreen(Pos, POV);
                
                if (data->Location.Z > 0) {
                
                data->Distance = Vector3::Distance(Pos, POV.Location) / 100.0f;
				if (data->Distance < 0.0f || data->Distance > 150.0f) {
                continue;
				}
                data->type = GrenadesSpawn(name);
                if (response.GrenadeCount >= maxgrenadeCount)
                continue;
                
                response.GrenadeCount++;
                } 
                }
				
//  √ﬂœ „‰ ≈÷«›… «·„ﬂ »… «··«“„…
std::unordered_set<std::string> processedItems;

if (IsLootBoxItemsPawn(name)) {
    uintptr_t boxItemCount = Offset_boxItemCount;
    uintptr_t boxItemBase = Offset_boxItemBase;

    uintptr_t count = getA(Actor + boxItemCount);
    float LocPtr = 0.0f;

    if (count > 30)
        count = 30;

    if (count > 0) {
        uintptr_t itemBase = getA(Actor + boxItemBase);

        for (int t = 0; t < count; t++) {
            uintptr_t itemAddv = itemBase + t * Offset_pukkk;
            std::string bitm = GetBoxItems(getA(itemAddv + 0x4));

            if (bitm.find("Unknown") == std::string::npos && processedItems.find(bitm) == processedItems.end()) {
                DeadBoxItems *data = &response.ItemsNames[response.DeadBoxItemsCount];

                auto Pos = Read<Vector3>(Read<uintptr_t>(Actor + Offsets_RootComponent) + Offsets_Position2);

                data->DeadBoxLocation = WorldToScreen(Pos, POV);

                if (data->DeadBoxLocation.Z > 0) {
                    data->DeadBoxDistance = Vector3::Distance(Pos, POV.Location) / 100.0f;

                    std::string itemName = bitm + " * " + std::to_string(t);
                    strncpy(data->DeadBoxItemsNames, itemName.c_str(), sizeof(data->DeadBoxItemsNames));
                    LocPtr += 25.0f;
                    data->DeadBoxLocation.Y -= LocPtr;
                    data->codeloot = getA(itemAddv + 0x4);

                    // ≈÷«›… «·⁄‰’— ≈·Ï „Ã„Ê⁄… «·⁄‰«’— «·„⁄«·Ã…
                    processedItems.insert(bitm);

                    if (response.DeadBoxItemsCount >= maxBoxItemsCount) {
                        continue;
                    }
                    response.DeadBoxItemsCount++;
                }
            }
        }
    }
}else if (strstr(name, OBFUSCATE("AirAttackBomb_C")) || strstr(name, OBFUSCATE("AirAttackBomb_Livik_C"))) {
                	
                ZoneData *data = &response.Zones[response.ZoneCount];
                
                auto Pos = Read<Vector3>(Read<uintptr_t>(Actor + Offsets_RootComponent) + Offsets_Position2);
                    
                data->Location = WorldToScreen(Pos, POV);

                if (data->Location.Z > 0) {  
                
                data->Distance = Vector3::Distance(Pos, POV.Location) / 100.0f;    
                    
                if (response.ZoneCount >= maxzonesCount) {
                continue;
                }
                response.ZoneCount++;
            //    printf("\nGW | %lX > XY: %0.1f %0.1f | D:%0.1fm %d", Actor, data->Location.X, data->Location.Y, data->Distance, name);
                }
                } else if (strstr(name, OBFUSCATE("Lobby")) || strstr(name, OBFUSCATE("_Lobby")) || strstr(name, OBFUSCATE("Lobby_"))) {
                response.InLobby = true;
               }
               
               
               }

            if (response.PlayerCount + response.ItemsCount + response.VehicleCount + response.GrenadeCount + response.DeadBoxItemsCount + response.ZoneCount > 0)
            {
                response.Success = true;
            }
            changed = 1;
            send((void *)&response, sizeof(response));
		 /*
		    if(request.memory.isBulletTrack){
			if((isFier || adss) && nearest > 0){
			SetBulletPosition({targetAimPos.X,targetAimPos.Y,targetAimPos.Z});
			} else SetBulletPosition({0,0,0});}
		 
		    if(aimbot){
		    if ((firing || ads) && nearest > 0){
            UseAimBot(true);
            SetAimPosition({targetAimPos.X,targetAimPos.Y,targetAimPos.Z});
            } else UseAimBot(false);}
*/
            
        }
    }
    else
    {
        perror("[Server] Socket can't connect");
    }
    Close();
    return 0;
}
