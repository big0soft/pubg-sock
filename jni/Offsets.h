//
// Created by day on 13/08/2022.
//

#ifndef DCHEATS_NEWGENZ_OFFSETS_H
#define DCHEATS_NEWGENZ_OFFSETS_H

#if defined(__aarch64__)

#define Offsets_GNames (uintptr_t) 0xc89b700 // + 0x110);
#define Offsets_GWorld (uintptr_t) 0xCF0A470 // - 0x20) + 0x30);
#define Offsets_GWorld1 (uintptr_t) 0xcee7650 // + 0x58) + 0x78) + 0x30);

#define Offsets_GUObject_Offset (uintptr_t) 0xc8d7570
#define Offsets_GNames_Offset (uintptr_t) 0x725f45c

#define Offsets_GNamesvn (uintptr_t) 0xC039990 // + 0x110);
#define Offsets_GWorldvn (uintptr_t) 0xC6A53A0 // - 0x20) + 0x30);
#define Offsets_GWorld1vn (uintptr_t) 0xc682e40 // + 0x58) + 0x78) + 0x30);

#define Offsets_GNamesin (uintptr_t) 0xbf2d480 // + 0x110);
#define Offsets_GWorldin (uintptr_t) 0xc5f5110 // - 0x20) + 0x30);
#define Offsets_GWorld1in (uintptr_t) 0xc5f5110 // + 0x58) + 0x78) + 0x30);

#define Offsets_WalkSpeed (uintptr_t) 0x27b8 //**///**0x1cc0   //float HighWalkSpeed;//[Offset: 0x1d80, Size: 0x4]

#define Offsets_oType (uintptr_t) 0x88
#define Offsets_Role (uintptr_t) 0x150 //byte Role;//[Offset:
///Class: ProjectileMovementComponent.MovementComponent.ActorComponent.Object
#define Offsets_Position2 (uintptr_t) 0x184  //Vector RelativeLocation;//[Offset: 0x118, Size: 0xc]////
#define Offsets_Position (uintptr_t) 0x1c0  //**/int[] ParachuteEquipItems;//[Offset: 0x1b0, Size: 16]             ****
#define Offsets_RootComponent (uintptr_t) 0x1b0 //**SceneComponent* RootComponent;//[Offset:

#define Offsets_SkeletalMeshComponent (uintptr_t) 0x488 //SkeletalMeshComponent* Mesh;//[Offset:
#define Offsets_StaticMesh (uintptr_t) 0x860 //StaticMesh* StaticMesh;//[Offset: 0x6b4
#define Offsets_StaticMeshComponentLODInfo (uintptr_t) 0x8e0 //StaticMeshComponentLODInfo[] LODData;//[Offset: 0x710, Size: 0xc]

#define Offsets_FixAttachInfoList (uintptr_t)  0x1b0 //** FixAttachInfoList                    ****
#define Offsets_MinLOD (uintptr_t) 0x860 //**int MinLOD;//[Offset:   ////***********

//int MinLOD;//[Offset: 0x81c, Size: 0x4]
//StaticMesh* StaticMesh;//[Offset: 0x820, Size: 0x8]


#define Offsets_CharacterMovementComponent (uintptr_t) 0x490 //**CharacterMovementComponent* CharacterMovement;//[Offset:
#define Offsets_Health (uintptr_t) 0xd98 //**float Health;//[Offset:

#define Offsets_NearDeathBreath (uintptr_t) 0x1930 //float NearDeathBreath;//[Offset: 0x12d0, Size: 0x4]
#define Offsets_NearDeatchComponent (uintptr_t) 0x1910 //STCharacterNearDeathComp* NearDeatchComponent;//[Offset: 0x12bc, Size: 0x4]
#define Offsets_BreathMax (uintptr_t) 0x16c //float BreathMax;//[Offset: 0x10c, Size: 0x4]

#define Offsets_CurrentStates (uintptr_t) 0xf58 //uint64 CurrentStates;//[Offset: 0xb50, Size: 0x8]   

#define Offsets_bDead (uintptr_t) 0xdb4 //**bool bDead;//(ByteOffset:


#define Offsets_AcknowledgedPawn (uintptr_t) 0x4a0 //Class: PlayerController.Controller.Actor.Object  // Pawn* AcknowledgedPawn;//[Offset: 0x470
#define Offsets_ShootWeaponComponent (uintptr_t) 0xec8 //STExtraShootWeaponComponent* ShootWeaponComponent;//[Offset: 0xe58
#define Offsets_PartHitComponent (uintptr_t) 0x1020 //PartHitComponent* PartHitComponent;//[Offset: 0xfe0
#define Offsets_OpenCollisionLODAngle (uintptr_t) 0x198 //OpenCollisionLODAngle[] ConfigCollisionDistSqAngles;//[Offset: 0x198

///Class: BattleRoyaleGameModeBase.UAEGameMode.LuaGameMode.GameMode.GameModeBase.Info.Actor.Object
#define Offsets_bVisible (uintptr_t) 0x1668 //bool bVisibleCheck;//(ByteOffset:

///Class: UAECharacter.Character.Pawn.Actor.Object
#define Offsets_PlayerName (uintptr_t)  0x8d8 //FString PlayerName;//[Offset:
#define Offsets_PlayerNation (uintptr_t) 0x8e8 	// FString Nation;//[Offset: 0x890, Size: 0x10]
#define Offsets_Playeruid (uintptr_t) 0x900 //FString Playeruid;//[Offset:
#define Offsets_TeamID (uintptr_t)  0x920 ///Class: UAECharacter.Character.Pawn.Actor.Object     //int TeamID;//[Offset:

#define Offsets_bIsAI (uintptr_t) 0x9d1 //bool bEnsure;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset:0x74d


#define Offsets_LastSubmitTime (uintptr_t) 0x40c //float LastSubmitTime;//[Offset: 0x374, Size: 0x4]
#define Offsets_LastRenderTime (uintptr_t) 0x410 //float LastRenderTime;//[Offset: 0x3ec, Size: 0x4]
#define Offsets_LastRenderTimeOnScreen (uintptr_t) 0x414 //float LastRenderTimeOnScreen;//[Offset: 0x3f0, Size: 0x4]

//Class: UAEPlayerController.LuaPlayerController.PlayerController.Controller.Actor.Object
#define Offsets_localPKey (uintptr_t) 0x870 //uint32 PlayerKey;//[Offset: 0x664, Size: 0x4]

///Class: STExtraWeapon.Actor.Object
#define Offsets_ActorChildren (uintptr_t) 0x1a0 //**Actor*[] Children;//[Offset:
#define Offsets_WeaponEntityComp (uintptr_t) 0x818 //**WeaponEntity* WeaponEntityComp;//[Offset:

///Class: WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object
#define Offsets_DrawShootLineTime (uintptr_t) 0x13c //RepAttachment AttachmentReplication 0x108 + FName AttachSocket 0x30 + 0x4;    264 + 48 + 4 = 316
//Class: RepAttachment //FName AttachSocket
#define Offsets_UploadInterval (uintptr_t) 0x178 //**float UploadInterval;//[Offset:
#define Offsets_CurBulletNumInClip (uintptr_t) 0xef0 //***int CurBulletNumInClip;//[Offset:

///Class: PlayerController.Controller.Actor.Object
#define Offset_PlayerCameraManager (uintptr_t) 0x4c0 //PlayerCameraManager* PlayerCameraManager;//[Offset:
///Class: PlayerCameraManager.Actor.Object
#define Offset_CameraCacheEntry (uintptr_t) 0x4a0 //CameraCacheEntry CameraCache;//[Offset:

#define Offsets_MinimalViewInfo (uintptr_t) 0x10 //Class: CameraCacheEntry //MinimalViewInfo POV;//[Offset:

#define Offsets_MovementCharacter (uintptr_t) 0x490 //**CharacterMovementComponent* CharacterMovement;//[Offset:

#define Offsets_STCharacterMovement (uintptr_t) 0x1bb0 //STCharacterMovementComponent* STCharacterMovement;//[Offset:

#define Offsets_CurrentVehicle (uintptr_t) 0xde0 //STExtraVehicleBase* CurrentVehicle;//[Offset:

#define Offsets_ReplicatedMovement (uintptr_t) 0xb0 //RepMovement ReplicatedMovement;//[Offset:

#define Offsets_Velocity (uintptr_t) 0x12c //Vector Velocity;//[Offset: 

#define Offsets_AcknowledgedPawn (uintptr_t) 0x4a0 //Pawn* AcknowledgedPawn;//[Offset:

#define Offsets_STExtraBaseCharacter (uintptr_t) 0x2570 //STExtraBaseCharacter* STExtraBaseCharacter;//[Offset:

#define Offsets_STPlayerController (uintptr_t) 0x3e70 //**STExtraPlayerController* STPlayerController;//[Offset:

#define Offsets_bIsWeaponFiring (uintptr_t) 0x1600 //**bool bIsWeaponFiring;//(ByteOffset:

#define Offsets_blsGunADS (uintptr_t) 0x1029 //**bool bIsGunADS;//(ByteOffset:

#define Offsets_WeaponOwnerProxy (uintptr_t) 0xe10 //Class: STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object  //WeaponOwnerProxy* WeaponOwnerProxy;//[Offset:
#define Offsets_BindedWeapon (uintptr_t) 0x50 //STExtraWeapon* BindedWeapon;//[Offset: 0x50, Size: 0x8]

//Class: WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object
#define Offsets_WeaponId (uintptr_t) 0x178 //int WeaponId;//[Offset: 0x178, Size: 0x4]

#define Offsets_WeaponManagerComponent (uintptr_t) 0x2298 //0x2058  CharacterWeaponManagerComponent* WeaponManagerComponent;//[Offset:

#define Offsets_CurrentWeaponReplicated (uintptr_t) 0x500 //STExtraWeapon* CurrentWeaponReplicated;//[Offset: 0x570, Size: 8]

#define Offsets_ShootWeaponEntity (uintptr_t) 0x1048 //ShootWeaponEntity* ShootWeaponEntityComp;//[Offset:

#define Offsets_CharaterMovement (uintptr_t) 0x1d0 //CharacterMovementComponent* CharaterMovement;//[Offset:

#define Offsets_LastUpdateVelocity (uintptr_t) 0x2d0 //**Vector LastUpdateVelocity;//[Offset:

#define Offsets_Controller (uintptr_t) 0x458 //0x328 0x428 //Controller* LastHitBy;//[Offset:************

#define Offset_ShootType (uintptr_t) 0x618 //byte ShootType;//[Offset:

#define Offset_OwnerCharacter (uintptr_t) 0x600 //STExtraPlayerCharacter* OwnerCharacter;//[Offset:

#define Offset_ViewPitchMin (uintptr_t) 0x1ccc //float ViewPitchMin
#define Offset_ViewPitchMax (uintptr_t) 0x1cd0 //float ViewPitchMax
#define Offset_ViewYawMin (uintptr_t) 0x1cd4 //float ViewYawMin
#define Offset_ViewYawMax (uintptr_t) 0x1cd8 //float ViewYawMax

///Class: STExtraVehicleBase.Pawn.Actor.Object
#define Offset_VehicleCommon (uintptr_t) 0xa08 //VehicleCommonComponent* VehicleCommon;//[Offset:
///Class: VehicleCommonComponent.VehicleComponent.LuaActorComponent.ActorComponent.Object
#define Offset_VHpMax (uintptr_t) 0x2c0 //float HPMax;//[Offset:
#define Offset_VHp (uintptr_t) 0x2c4 //float HP;//[Offset:
#define Offset_VFuelMax (uintptr_t) 0x334 //float FuelMax;//[Offset:
#define Offset_VFuel (uintptr_t) 0x338 //float Fuel;//[Offset:

#define Offset_boxItemCount (uintptr_t) 0x960 + 0x4 //PickUpItemData[] PickUpDataList;//[Offset:  + 0x4
#define Offset_boxItemBase (uintptr_t) 0x960 //PickUpItemData[] PickUpDataList;//[Offset:
#define Offset_pukkk (uintptr_t) 0x38 // bool bHighPriority;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x38, Size: 0x1]

///Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object
#define Offset_GameDeviationFactor (uintptr_t) 0xb90 //float GameDeviationFactor;//[Offset:
#define Offset_ExtraHitPerformScale (uintptr_t) 0xc4c //float ExtraHitPerformScale;//[Offset:
#define Offset_AnimationKick (uintptr_t) 0xc64 //float AnimationKick;//[Offset:
#define Offset_RecoilKickADS (uintptr_t) 0xc48  //float RecoilKickADS;//[Offset:
#define Offset_AccessoriesHRecoilFactor (uintptr_t) 0xb1c  //float AccessoriesHRecoilFactor;//[Offset:
#define Offset_AccessoriesVRecoilFactor (uintptr_t) 0xb18  //float AccessoriesVRecoilFactor;//[Offset:
#define Offset_AccessoriesRecoveryFactor (uintptr_t) 0xb20  //float AccessoriesRecoveryFactor;//[Offset:
#define Offset_BulletFireSpeed (uintptr_t) 0x4f8 //float BulletFireSpeed;//[Offset:

#define Offset_Aimbotvip (uintptr_t) 0x990 //AutoAimingConfig AutoAimingConfig;//[Offset: 0x990, Size: 0x110]

#define Offset_Aimbottvipp (uintptr_t) 0x9a4 //SCOPE  //float C_CustomMovementBlendTime;//[Offset: 0x994, Size: 0x4]
#define Offset_Aimbotttvippp (uintptr_t) 0x994 //FIRE   //float SwitchingPoseTimerInternal;//[Offset: 0x98c, Size: 0x4]

#define Offset_Aimbottttvipppp (uintptr_t) 0x920


#define Offset_ParachuteComponent (uintptr_t) 0x15e8 //CharacterParachuteComponent* ParachuteComponent;//[Offset: 0x1580
#define Offset_CurrentFallSpeed (uintptr_t) 0x1cc //float CurrentFallSpeed;//[Offset: 0x1d4, Size: 0x4]

#define Offset_RecoilInfo (uintptr_t) 0xaa8 //SRecoilInfo RecoilInfo;//[Offset:
#define Offset_RecoilModifierStand (uintptr_t) 0x50
#define Offset_RecoilModifierCrouch (uintptr_t) 0x54
#define Offset_RecoilModifierProne (uintptr_t) 0x58 

#define Offset_RecoilSpeedVertical (uintptr_t) 0x3c //float RecoilSpeedVertical;//[Offset: 0x34, Size: 0x4]
#define Offset_RecoilSpeedHorizontal (uintptr_t) 0x40 //float RecoilSpeedHorizontal;//[Offset: 0x38, Size: 0x4]
#define Offset_RecovertySpeedVertical (uintptr_t) 0x44 //float RecovertySpeedVertical;//[Offset: 0x3c, Size: 0x4]

#define Offset_ThirdPersonCameraComponent (uintptr_t) 0x1a80 //CameraComponent* ThirdPersonCameraComponent;//[Offset: 0x18e0, Size: 8]
#define Offset_FieldOfView (uintptr_t) 0x33c //float FieldOfView;//[Offset: 0x2cc, Size: 4] 0x260 **********

#define Offset_WeaponHitPartCoff (uintptr_t) 0xb90 //float GameDeviationFactor;//[Offset:
#define Offset_WeaponHitPartCoffZombie (uintptr_t) 0xc4c //float ExtraHitPerformScale;//[Offset:
#define Offset_BulletMomentum (uintptr_t) 0xc64 //float AnimationKick;//[Offset:
#define Offset_WeaponWarnUpTime (uintptr_t) 0xc48  //float RecoilKickADS;//[Offset:
#define Offset_BaseImpactDamage (uintptr_t) 0xb24  //float AccessoriesHRecoilFactor;//[Offset:
#define Offset_MaxDamageRate (uintptr_t) 0xb20  //float AccessoriesVRecoilFactor;//[Offset:
#define Offset_DamageImpulse (uintptr_t) 0x4f0 //float BulletFireSpeed;//[Offset:

#else

#define Offsets_GNames (uintptr_t) 0x91c8da4 //+ 0x88);
#define Offsets_GWorld (uintptr_t) 0x96F9E6C // + 0x3C) + 0x20);
#define Offsets_GWorld1 (uintptr_t) 0x96e2770 // + 0x38) + 0x58) + 0x20);

#define Offsets_GUObject_Offset (uintptr_t) 0x9582594
#define Offsets_GNames_Offset (uintptr_t) 0x48cd030

#define Offsets_GNamesvn (uintptr_t) 0x8942CA4 //+ 0x88);
#define Offsets_GWorldvn (uintptr_t) 0x8E66AB4 // + 0x3C) + 0x20);
#define Offsets_GWorld1vn (uintptr_t) 0xc682e40 // + 0x38) + 0x58) + 0x20);

#define Offsets_GNamesin (uintptr_t) 0x8997924 //+ 0x88);
#define Offsets_GWorldin (uintptr_t) 0x8ee62f8 // + 0x3C) + 0x20);
#define Offsets_GWorld1in (uintptr_t) 0x8ee62f8 // + 0x38) + 0x58) + 0x20);


#define Offsets_WalkSpeed (uintptr_t) 0x1e98 //0x1cc0   //float HighWalkSpeed;//[Offset: 0x1d80, Size: 0x4]

#define Offsets_oType (uintptr_t) 0x60 // Pointer Manual
#define Offsets_Role (uintptr_t) 0x108 //*byte Role;//[Offset:
///Class: ProjectileMovementComponent.MovementComponent.ActorComponent.Object
#define Offsets_Position2 (uintptr_t) 0x120  //*Vector RelativeLocation;//[Offset: 0x118, Size: 0xc]////
#define Offsets_Position (uintptr_t) 0x160  //int[] ParachuteEquipItems;//[Offset: 0x1b0, Size: 16]                 ****
#define Offsets_RootComponent (uintptr_t) 0x158 //*SceneComponent* RootComponent;//[Offset:

#define Offsets_SkeletalMeshComponent (uintptr_t) 0x378 //*SkeletalMeshComponent* Mesh;//[Offset:
#define Offsets_StaticMesh (uintptr_t) 0x6b4 //StaticMesh* StaticMesh;//[Offset: 0x6b4
#define Offsets_StaticMeshComponentLODInfo (uintptr_t) 0x744 //*StaticMeshComponentLODInfo[] LODData;//[Offset: 0x710, Size: 0xc]

#define Offsets_FixAttachInfoList (uintptr_t)  0x150 // FixAttachInfoList
#define Offsets_MinLOD (uintptr_t) 0x6e4 //*int MinLOD;//[Offset:   ////***********
#define Offsets_CharacterMovementComponent (uintptr_t) 0x37c //*CharacterMovementComponent* CharacterMovement;//[Offset:
#define Offsets_Health (uintptr_t) 0xa4c //*float Health;//[Offset:

#define Offsets_NearDeathBreath (uintptr_t) 0x132c //*float NearDeathBreath;//[Offset: 0x12d0, Size: 0x4]
#define Offsets_NearDeatchComponent (uintptr_t) 0x1318 //*STCharacterNearDeathComp* NearDeatchComponent;//[Offset: 0x12bc, Size: 0x4]
#define Offsets_BreathMax (uintptr_t) 0x10c //*float BreathMax;//[Offset: 0x10c, Size: 0x4]

#define Offsets_CurrentStates (uintptr_t) 0xb88 //*uint64 CurrentStates;//[Offset: 0xb50, Size: 0x8] 

#define Offsets_bDead (uintptr_t) 0xa64 //*bool bDead;//(ByteOffset:

///Class: BattleRoyaleGameModeBase.UAEGameMode.LuaGameMode.GameMode.GameModeBase.Info.Actor.Object
#define Offsets_bVisible (uintptr_t) 0xf4c //*bool bVisibleCheck;//(ByteOffset:

#define Offsets_WeaponOwnerProxy (uintptr_t) 0xa9c //*Class: STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object  //WeaponOwnerProxy* WeaponOwnerProxy;//[Offset:
#define Offsets_BindedWeapon (uintptr_t) 0x34 //*STExtraWeapon* BindedWeapon;//[Offset: 0x50, Size: 0x8]

//Class: WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object
#define Offsets_WeaponId (uintptr_t) 0x108 //*int WeaponId;//[Offset: 0x178, Size: 0x4]

#define Offsets_AcknowledgedPawn (uintptr_t) 0x388 //*Class: PlayerController.Controller.Actor.Object  // Pawn* AcknowledgedPawn;//[Offset: 0x368
#define Offsets_ShootWeaponComponent (uintptr_t) 0xbbc //*STExtraShootWeaponComponent* ShootWeaponComponent;//[Offset: 0xb4c
#define Offsets_PartHitComponent (uintptr_t) 0xc24 //*PartHitComponent* PartHitComponent;//[Offset: 0xbdc
#define Offsets_OpenCollisionLODAngle (uintptr_t) 0x120 //*OpenCollisionLODAngle[] ConfigCollisionDistSqAngles;//[Offset: 0x120


///Class: UAECharacter.Character.Pawn.Actor.Object
#define Offsets_PlayerName (uintptr_t)  0x6b0 //*FString PlayerName;//[Offset:
#define Offsets_PlayerNation (uintptr_t) 0x6bc 	//* FString Nation;//[Offset: 0x890, Size: 0x10]
#define Offsets_Playeruid (uintptr_t) 0x6cc //*FString Playeruid;//[Offset:
#define Offsets_TeamID (uintptr_t)  0x6e4 ///*Class: UAECharacter.Character.Pawn.Actor.Object     //int TeamID;//[Offset:

#define Offsets_bIsAI (uintptr_t) 0x77d //*bool bEnsure;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset:0x74d
//bool bIsAI;

#define Offsets_LastSubmitTime (uintptr_t) 0x394 //*float LastSubmitTime;//[Offset: 0x374, Size: 0x4]
#define Offsets_LastRenderTime (uintptr_t) 0x398 //*float LastRenderTime;//[Offset: 0x3ec, Size: 0x4]
#define Offsets_LastRenderTimeOnScreen (uintptr_t) 0x39c //*float LastRenderTimeOnScreen;//[Offset: 0x3f0, Size: 0x4]

//Class: UAEPlayerController.LuaPlayerController.PlayerController.Controller.Actor.Object
#define Offsets_localPKey (uintptr_t) 0x684 //*uint32 PlayerKey;//[Offset: 0x664, Size: 0x4]

#define Offsets_AcknowledgedPawn (uintptr_t) 0x388 //*Class: PlayerController.Controller.Actor.Object  // Pawn* AcknowledgedPawn;//[Offset: 0x470
#define Offsets_ShootWeaponComponent (uintptr_t) 0xbbc //*STExtraShootWeaponComponent* ShootWeaponComponent;//[Offset: 0xe58
#define Offsets_PartHitComponent (uintptr_t) 0xc24 //*PartHitComponent* PartHitComponent;//[Offset: 0xfe0
#define Offsets_OpenCollisionLODAngle (uintptr_t) 0x120 //*OpenCollisionLODAngle[] ConfigCollisionDistSqAngles;//[Offset: 0x198

///Class: STExtraWeapon.Actor.Object
#define Offsets_ActorChildren (uintptr_t) 0x14c //*Actor*[] Children;//[Offset:
#define Offsets_WeaponEntityComp (uintptr_t) 0x680 //*WeaponEntity* WeaponEntityComp;//[Offset:

///Class: WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object
#define Offsets_DrawShootLineTime (uintptr_t) 0xfc //*RepAttachment AttachmentReplication 0xd0 + FName AttachSocket 0x28 + 0x4;   208 + 40 + 4 = 252
//Class: RepAttachment //FName AttachSocket
#define Offsets_UploadInterval (uintptr_t) 0x108 //*float UploadInterval;//[Offset:
#define Offsets_CurBulletNumInClip (uintptr_t) 0xbd0 //*int CurBulletNumInClip;//[Offset:

///Class: PlayerController.Controller.Actor.Object
#define Offset_PlayerCameraManager (uintptr_t) 0x398 //*PlayerCameraManager* PlayerCameraManager;//[Offset:
///Class: PlayerCameraManager.Actor.Object
#define Offset_CameraCacheEntry (uintptr_t) 0x3a0 //*CameraCacheEntry CameraCache;//[Offset:

#define Offsets_MinimalViewInfo (uintptr_t) 0x10 //*Class: CameraCacheEntry //MinimalViewInfo POV;//[Offset:

#define Offsets_MovementCharacter (uintptr_t) 0x37c //*CharacterMovementComponent* CharacterMovement;//[Offset:

#define Offsets_STCharacterMovement (uintptr_t) 0x1524 //*STCharacterMovementComponent* STCharacterMovement;//[Offset:

#define Offsets_CurrentVehicle (uintptr_t) 0xa84 //*STExtraVehicleBase* CurrentVehicle;//[Offset:

#define Offsets_ReplicatedMovement (uintptr_t) 0x80 //*RepMovement ReplicatedMovement;//[Offset:

#define Offsets_Velocity (uintptr_t) 0xd0 //*Vector Velocity;//[Offset:  

#define Offsets_STExtraBaseCharacter (uintptr_t) 0x1ce0 //*STExtraBaseCharacter* STExtraBaseCharacter;//[Offset:

#define Offsets_STPlayerController (uintptr_t) 0x3174 //*STExtraPlayerController* STPlayerController;//[Offset:

#define Offsets_bIsWeaponFiring (uintptr_t) 0x1084 //*bool bIsWeaponFiring;//(ByteOffset:

#define Offsets_blsGunADS (uintptr_t) 0xc29 //*bool bIsGunADS;//(ByteOffset:

#define Offsets_WeaponManagerComponent (uintptr_t) 0x1af0 //*0x2058  CharacterWeaponManagerComponent* WeaponManagerComponent;//[Offset:

#define Offsets_CurrentWeaponReplicated (uintptr_t) 0x40c //*STExtraWeapon* CurrentWeaponReplicated;//[Offset: 0x570, Size: 8]

#define Offsets_ShootWeaponEntity (uintptr_t) 0xcf8 //*ShootWeaponEntity* ShootWeaponEntityComp;//[Offset:

#define Offset_ViewPitchMin (uintptr_t) 0x1ac0 //*float ViewPitchMin
#define Offset_ViewPitchMax (uintptr_t) 0x1ac4 //*float ViewPitchMax
#define Offset_ViewYawMin (uintptr_t) 0x1ac8 //*float ViewYawMin
#define Offset_ViewYawMax (uintptr_t) 0x1acc //*float ViewYawMax

///Class: STExtraVehicleBase.Pawn.Actor.Object
#define Offset_VehicleCommon (uintptr_t) 0x7c8 //*VehicleCommonComponent* VehicleCommon;//[Offset:
///Class: VehicleCommonComponent.VehicleComponent.LuaActorComponent.ActorComponent.Object
#define Offset_VHpMax (uintptr_t) 0x1fc //*float HPMax;//[Offset:
#define Offset_VHp (uintptr_t) 0x200 //*float HP;//[Offset:
#define Offset_VFuelMax (uintptr_t) 0x258 //*float FuelMax;//[Offset:
#define Offset_VFuel (uintptr_t) 0x25c //*float Fuel;//[Offset:

#define Offset_boxItemCount (uintptr_t) 0x774 + 0x4 //*PickUpItemData[] PickUpDataList;//[Offset:  + 0x4
#define Offset_boxItemBase (uintptr_t) 0x774 //*PickUpItemData[] PickUpDataList;//[Offset:
#define Offset_pukkk (uintptr_t) 0x30 //* bool bHighPriority;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x38, Size: 0x1]

#define Offset_ThirdPersonCameraComponent (uintptr_t) 0x1450 //*CameraComponent* ThirdPersonCameraComponent;//[Offset: 0x18e0, Size: 8]
#define Offset_FieldOfView (uintptr_t) 0x2cc //*float FieldOfView;//[Offset: 0x2cc, Size: 4] 0x260 **********

///Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object
#define Offset_GameDeviationFactor (uintptr_t) 0x98c //float GameDeviationFactor;//[Offset:
#define Offset_ExtraHitPerformScale (uintptr_t) 0xa3c //float ExtraHitPerformScale;//[Offset:
#define Offset_AnimationKick (uintptr_t) 0xa54 //float AnimationKick;//[Offset:
#define Offset_RecoilKickADS (uintptr_t) 0xa38  //float RecoilKickADS;//[Offset:
#define Offset_AccessoriesHRecoilFactor (uintptr_t) 0x928  //float AccessoriesHRecoilFactor;//[Offset:
#define Offset_AccessoriesVRecoilFactor (uintptr_t) 0x924  //float AccessoriesVRecoilFactor;//[Offset:
#define Offset_AccessoriesRecoveryFactor (uintptr_t) 0x92c  //float AccessoriesRecoveryFactor;//[Offset:
#define Offset_BulletFireSpeed (uintptr_t) 0x420 //float BulletFireSpeed;//[Offset:

#define Offset_Aimbotvip (uintptr_t) 0x7c0 //AutoAimingConfig AutoAimingConfig;//[Offset: 0x7b8, Size: 0xfc]

#define Offset_Aimbottvipp (uintptr_t) 0x7dc //SCOPE  //float C_CustomMovementBlendTime;//[Offset: 0x7cc, Size: 0x4]
#define Offset_Aimbotttvippp (uintptr_t) 0x7cc //FIRE   //float SwitchingPoseTimerInternal;//[Offset: 0x7c4, Size: 0x4]

#define Offset_RecoilInfo (uintptr_t) 0x8c0 //SRecoilInfo RecoilInfo;//[Offset:
#define Offset_RecoilModifierStand (uintptr_t) 0x48
#define Offset_RecoilModifierCrouch (uintptr_t) 0x4c
#define Offset_RecoilModifierProne (uintptr_t) 0x50 

#define Offset_RecoilSpeedVertical (uintptr_t) 0x34 //float RecoilSpeedVertical;//[Offset: 0x34, Size: 0x4]
#define Offset_RecoilSpeedHorizontal (uintptr_t) 0x38 //float RecoilSpeedHorizontal;//[Offset: 0x38, Size: 0x4]
#define Offset_RecovertySpeedVertical (uintptr_t) 0x3c //float RecovertySpeedVertical;//[Offset: 0x3c, Size: 0x4]

#define Offset_WeaponHitPartCoff (uintptr_t) 0xb30 //float GameDeviationFactor;//[Offset:
#define Offset_WeaponHitPartCoffZombie (uintptr_t) 0xbec //float ExtraHitPerformScale;//[Offset:
#define Offset_BulletMomentum (uintptr_t) 0xc04 //float AnimationKick;//[Offset:
#define Offset_WeaponWarnUpTime (uintptr_t) 0xbe8  //float RecoilKickADS;//[Offset:
#define Offset_BaseImpactDamage (uintptr_t) 0xabc  //float AccessoriesHRecoilFactor;//[Offset:
#define Offset_MaxDamageRate (uintptr_t) 0xab8  //float AccessoriesVRecoilFactor;//[Offset:
#define Offset_DamageImpulse (uintptr_t) 0x4e0 //float BulletFireSpeed;//[Offset:

#endif

#endif DCHEATS_NEWGENZ_OFFSETS_H

