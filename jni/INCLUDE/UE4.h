#define PI 3.141592653589793238

struct D3DMatrix {
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
};

D3DMatrix ToMatrixWithScale(Vector3 translation, Vector3 scale, Vector4 rot) {
    D3DMatrix m;
    m._41 = translation.X;
    m._42 = translation.Y;
    m._43 = translation.Z;


    float x2 = rot.X + rot.X;
    float y2 = rot.Y + rot.Y;
    float z2 = rot.Z + rot.Z;


    float xx2 = rot.X * x2;
    float yy2 = rot.Y * y2;
    float zz2 = rot.Z * z2;

    m._11 = (1.0f - (yy2 + zz2)) * scale.X;
    m._22 = (1.0f - (xx2 + zz2)) * scale.Y;
    m._33 = (1.0f - (xx2 + yy2)) * scale.Z;


    float yz2 = rot.Y * z2;
    float wx2 = rot.W * x2;

    m._32 = (yz2 - wx2) * scale.Z;
    m._23 = (yz2 + wx2) * scale.Y;

    float xy2 = rot.X * y2;
    float wz2 = rot.W * z2;

    m._21 = (xy2 - wz2) * scale.Y;
    m._12 = (xy2 + wz2) * scale.X;


    float xz2 = rot.X * z2;
    float wy2 = rot.W * y2;

    m._31 = (xz2 + wy2) * scale.Z;
    m._13 = (xz2 - wy2) * scale.X;


    m._14 = 0.0f;
    m._24 = 0.0f;
    m._34 = 0.0f;
    m._44 = 1.0f;

    return m;
}

Vector3 mat2Cord(D3DMatrix pM1, D3DMatrix pM2) {
    Vector3 pOut;

    pOut.X = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
    pOut.Y = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
    pOut.Z = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;

    return pOut;
}

D3DMatrix getOMatrix(uintptr_t boneAddr) {
    float oMat[11];
    vm_readv(boneAddr,&oMat,sizeof(oMat));
    rot.X = oMat[0];
    rot.Y = oMat[1];
    rot.Z = oMat[2];
    rot.W = oMat[3];

    tran.X = oMat[4];
    tran.Y = oMat[5];
    tran.Z = oMat[6];

    scale.X = oMat[8];
    scale.Y = oMat[9];
    scale.Z = oMat[10];

    return ToMatrixWithScale(tran,scale,rot);
}

Vector3 World2Screen(D3DMatrix viewMatrix, Vector3 pos) {
    Vector3 screen;
    float screenW = (viewMatrix._14 * pos.X) + (viewMatrix._24 * pos.Y) + (viewMatrix._34 * pos.Z) + viewMatrix._44;
	screen.Z = screenW;


    float screenX = (viewMatrix._11 * pos.X) + (viewMatrix._21 * pos.Y) + (viewMatrix._31 * pos.Z) + viewMatrix._41;
    float screenY = (viewMatrix._12 * pos.X) + (viewMatrix._22 * pos.Y) + (viewMatrix._32 * pos.Z) + viewMatrix._42;
    screen.Y = (height / 2) - (height / 2) * screenY / screenW;
    screen.X = (width / 2) + (width / 2) * screenX / screenW;

    return screen;

}
Vector2 World2ScreenMain(D3DMatrix viewMatrix, Vector3 pos) {
    Vector2 screen;
    float screenW = (viewMatrix._14 * pos.X) + (viewMatrix._24 * pos.Y) + (viewMatrix._34 * pos.Z) + viewMatrix._44;

    float screenX = (viewMatrix._11 * pos.X) + (viewMatrix._21 * pos.Y) + (viewMatrix._31 * pos.Z) + viewMatrix._41;
    float screenY = (viewMatrix._12 * pos.X) + (viewMatrix._22 * pos.Y) + (viewMatrix._32 * pos.Z) + viewMatrix._42;
    screen.Y = (height / 2) - (height / 2) * screenY / screenW;
    screen.X = (width / 2) + (width / 2) * screenX / screenW;

    return screen;
}


enum BoneID {
    Root,//0
    pelvis,//1
    spine_01,//2
    spine_02,//3
    spine_03,//4
    neck_01,//5
    Head,//6
    hair_01,//7
    hair_02,//8
    hair_03,//9
    hair_04,//10
    clavicle_l,//11
    upperarm_l,//12
    lowerarm_l,//13
    hand_l,//14
    thumb_01_l,//15
    thumb_02_l,//16
    thumb_03_l,//17
    index_01_l,//18
    index_02_l,//19
    index_03_l,//20
    middle_01_l,//21
    middle_02_l,//22
    middle_03_l,//23
    ring_01_l,//24
    ring_02_l,//25
    ring_03_l,//26
    pinky_01_l,//27
    pinky_02_l,//28
    pinky_03_l,//29
    item_l,//30
    lowerarm_twist_01_l,//31
    clavicle_r,//32
    upperarm_r,//33
    lowerarm_r,//34
    hand_r,//35
    thumb_01_r,//36
    thumb_02_r,//37
    thumb_03_r,//38
    index_01_r,//39
    index_02_r,//40
    index_03_r,//41
    middle_01_r,//42
    middle_02_r,//43
    middle_03_r,//44
    ring_01_r,//45
    ring_02_r,//46
    ring_03_r,//47
    pinky_01_r,//48
    pinky_02_r,//49
    pinky_03_r,//50
    item_r,//51
    lowerarm_twist_01_r,//52
    thigh_l,//53
    calf_l,//54
    foot_l,//55
    ball_l,//56
    thigh_r,//57
    calf_r,//58
    foot_r,//59
    ball_r,//60
    ik_hand_root,//61
    ik_hand_gun,//62
    ik_hand_r,//63
    ik_hand_l//64
};

Vector3 GetBonePos(uintptr_t Actors, int BoneID) {
    uintptr_t boneAddress = Read<uintptr_t>(Actors + Offsets_SkeletalMeshComponent);
    D3DMatrix baseMatrix = getOMatrix(boneAddress + Offsets_FixAttachInfoList);
    boneAddress = Read<uintptr_t>(boneAddress + Offsets_MinLOD);
    D3DMatrix oMatrix = getOMatrix(boneAddress + (BoneID) * 48);
    return mat2Cord(oMatrix, baseMatrix);
}

Vector3 CalcMousePos(Vector3 headPos, Vector3 uMyobejctPos) {
    Vector3 AimPos;
    float x = headPos.X - uMyobejctPos.X;
    float y = headPos.Y - uMyobejctPos.Y;
    float z = headPos.Z - uMyobejctPos.Z;
    AimPos.X = atan2(y, x) * 180.f / M_PI;
    AimPos.Y = atan2(z, sqrt(x * x + y * y)) * 180.f / PI;
    return AimPos;
}

struct Rotator {
	float Pitch;
	float Yaw;
	float Roll;
};

float getDistance(struct Vector3 mxyz,struct Vector3 exyz)
{
	return sqrt ((mxyz.X-exyz.X)*(mxyz.X-exyz.X)+(mxyz.Y-exyz.Y)*(mxyz.Y-exyz.Y)+(mxyz.Z-exyz.Z)*(mxyz.Z-exyz.Z))/100;
}

Rotator ToRotator(Vector3 local, Vector3 target)
{
	Vector3 rotation; // = local - target;
	rotation.X = local.X - target.X;
	rotation.Y = local.Y - target.Y;
	rotation.Z = local.Z - target.Z;
	Rotator newViewAngle = {0};

	float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

	newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float)3.14159265358979323846);
	newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float)3.14159265358979323846);
	newViewAngle.Roll = (float)0.f;

	if (rotation.X >= 0.f)
		newViewAngle.Yaw += 180.0f;

	return newViewAngle;
}

struct MinimalViewInfo {
	Vector3 Location;
	Vector3 LocationLocalSpace;
	Rotator Rotation;
	float FOV;
};

struct CameraCacheEntry {
	float TimeStamp;
	char chunks[0xC];
	MinimalViewInfo POV;
};

struct FMatrix {
	float M[4][4];
};

FMatrix RotatorToMatrix(Rotator rotation) {
	float radPitch = rotation.Pitch * ((float)PI / 180.0f);
	float radYaw = rotation.Yaw * ((float)PI / 180.0f);
	float radRoll = rotation.Roll * ((float)PI / 180.0f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	FMatrix matrix;

	matrix.M[0][0] = (CP * CY);
	matrix.M[0][1] = (CP * SY);
	matrix.M[0][2] = (SP);
	matrix.M[0][3] = 0;

	matrix.M[1][0] = (SR * SP * CY - CR * SY);
	matrix.M[1][1] = (SR * SP * SY + CR * CY);
	matrix.M[1][2] = (-SR * CP);
	matrix.M[1][3] = 0;

	matrix.M[2][0] = (-(CR * SP * CY + SR * SY));
	matrix.M[2][1] = (CY * SR - CR * SP * SY);
	matrix.M[2][2] = (CR * CP);
	matrix.M[2][3] = 0;

	matrix.M[3][0] = 0;
	matrix.M[3][1] = 0;
	matrix.M[3][2] = 0;
	matrix.M[3][3] = 1;

	return matrix;
}

Vector3 WorldToScreen(Vector3 worldLocation, MinimalViewInfo camViewInfo) {
	FMatrix tempMatrix = RotatorToMatrix(camViewInfo.Rotation);

	Vector3 vAxisX(tempMatrix.M[0][0], tempMatrix.M[0][1], tempMatrix.M[0][2]);
	Vector3 vAxisY(tempMatrix.M[1][0], tempMatrix.M[1][1], tempMatrix.M[1][2]);
	Vector3 vAxisZ(tempMatrix.M[2][0], tempMatrix.M[2][1], tempMatrix.M[2][2]);
	Vector3 vDelta = worldLocation - camViewInfo.Location;
	Vector3 vTransformed(Vector3::Dot(vDelta, vAxisY), Vector3::Dot(vDelta, vAxisZ), Vector3::Dot(vDelta, vAxisX));
	/*
	if (vTransformed.Z < 1.0f) {
		vTransformed.Z = 1.0f;
	}
	*/
	float fov = camViewInfo.FOV;
	float screenCenterX = (width / 2.0f);
	float screenCenterY = (height / 2.0f);

	return Vector3(
		(screenCenterX + vTransformed.X * (screenCenterX / tanf(fov * ((float)M_PI / 360.0f))) / vTransformed.Z),
		(screenCenterY - vTransformed.Y * (screenCenterX / tanf(fov * ((float)M_PI / 360.0f))) / vTransformed.Z),
		vTransformed.Z
	);
}

Vector2 WorldToRadar(float Yaw, Vector3 Origin, Vector3 LocalOrigin, float PosX, float PosY, Vector3 Size, bool& outbuff)
{
bool flag = false;
double num = (double)Yaw;
double num2 = num * 0.017453292519943295;
float num3 = (float)cosl(num2);
float num4 = (float)sinf(num2);
float num5 = Origin.X - LocalOrigin.X;
float num6 = Origin.Y - LocalOrigin.Y;
Vector2 vector;
vector.X = (num6 * num3 - num5 * num4) / 150.f;
vector.Y = (num5 * num3 + num6 * num4) / 150.f;
Vector2 vector2;
vector2.X = vector.X + PosX + Size.X / 2.f;
vector2.Y = -vector.Y + PosY + Size.Y / 2.f;
bool flag2 = vector2.X > PosX + Size.X;
if (flag2)
{
vector2.X = PosX + Size.X;
}
else
{
bool flag3 = vector2.X < PosX;
if (flag3)
{
vector2.X = PosX;
}
}
bool flag4 = vector2.Y > PosY + Size.Y;
if (flag4)
{
vector2.Y = PosY + Size.Y;
}
else
{
bool flag5 = vector2.Y < PosY;
if (flag5)
{
vector2.Y = PosY;
}
}
bool flag6 = vector2.Y == PosY || vector2.X == PosX;
if (flag6)
{
flag = true;
}
outbuff = flag;
return vector2;
}



Vector3 GetBonePosToScreen(uintptr_t Actors, int BoneID, MinimalViewInfo camViewInfo) {
    uintptr_t boneAddress = Read<uintptr_t>(Actors + Offsets_SkeletalMeshComponent);
    D3DMatrix baseMatrix = getOMatrix(boneAddress + Offsets_FixAttachInfoList);
    boneAddress = Read<uintptr_t>(boneAddress + Offsets_MinLOD);
    D3DMatrix oMatrix = getOMatrix(boneAddress + (BoneID) * 48);
    return WorldToScreen(mat2Cord(oMatrix, baseMatrix), camViewInfo);
}
