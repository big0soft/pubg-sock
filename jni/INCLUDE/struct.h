#include "support.h"
//#include "obfuscate.h"
#include "init.h"
#include <string>
#define maxplayerCount 100
#define maxvehicleCount 50
#define maxitemsCount 400
#define maxgrenadeCount 10
#define maxBoxItemsCount 30
#define maxzonesCount 10
using namespace std;

struct PlayerBone {
    bool isBone = false;
    Vector3 neck;
    Vector3 cheast;
    Vector3 pelvis;
    Vector3 lSh;
    Vector3 rSh;
    Vector3 lElb;
    Vector3 rElb;
    Vector3 lWr;
    Vector3 rWr;
    Vector3 lTh;
    Vector3 rTh;
    Vector3 lKn;
    Vector3 rKn;
    Vector3 lAn;
    Vector3 rAn;
    Vector3 root;
};

struct PlayerWeapon {
    bool isWeapon=false;
    int id;
    int ammo;
};
enum Mode {
    InitMode = 1,
    ESPMode = 2,
    HackMode = 3,
    StopMode = 4,
};
struct Options {
    int aimbotmode;
    int openState;
    int aimingState;
    bool ignoreBot;
    bool tracingStatus;
    int priority;
    bool pour;
    int aimingRange;
    int aimingDist;
    int aimingSpeed;
    int recCompe;
};

struct Memory {
    bool LessRecoilsafe;
    bool LessRecoil2;

    bool ZeroRecoil;
    bool InstantHit;
    bool FastSwitchWeapon;
    bool HitX;
    bool SmallCrosshair;
    bool NoShake;

    bool aimbot1;
    bool aimbot2;
    bool AutoAim;

    bool headshot;

    bool isCamFov;
    bool isCamFov1;
    bool isCamFov2;
    bool isCamFov3;
    bool isCamFov4;
    bool isCamFov5;
    bool isCamFov6;
    bool isCamFov7;
    bool isCamFov8;
    bool isCamFov9;
    bool isCamFov10;

    bool isBulletTrack;
    int DistBullet;
    int scopeDistance;
    int FovBullet;
};

struct Request {
    int Mode;
    Options options;
    Memory memory;
    int ScreenWidth;
    int ScreenHeight;
};

struct SetValue {
    int mode;
    int type;
};

struct VehicleData {
    char VehicleName[50];
    float Distance;
    float Health;
    float Fuel;
    Vector3 Location;
};

struct ItemData {
    char ItemName[50];
    float Distance;
    Vector3 Location;
};


struct GrenadeData {
    int type;
    float Distance;
    Vector3 Location;
};

struct ZoneData {
    float Distance;
    Vector3 Location;
};

struct PlayerData {
    char PlayerNameByte[100];
    int TeamID;
    float Health;
    float HealthKnock;
    float HealthKnockMax;
    float Distance;
    bool isBot;
    Vector3 HeadLocation;
    Vector2 RadarPosition;
    PlayerWeapon Weapon;
    PlayerBone Bone;
    char PlayerNation[100];
    char PlayerUID[100];
    bool isVisible;
    int EnemyPoseSate;
};

struct DeadBoxItems {
    char DeadBoxItemsNames[50];
    float DeadBoxDistance;
    Vector3 DeadBoxLocation;
    int codeloot;
};

struct Response {
    bool Success;
    bool InLobby;
    int PlayerCount;
    int VehicleCount;
    int ItemsCount;
    int GrenadeCount;
    int DeadBoxItemsCount;
    int ZoneCount;
    float fov;
    PlayerData Players[maxplayerCount];
    DeadBoxItems ItemsNames[maxBoxItemsCount];
    VehicleData Vehicles[maxvehicleCount];
    ItemData Items[maxitemsCount];
    GrenadeData Grenade[maxgrenadeCount];
    ZoneData Zones[maxzonesCount];
};
