#pragma once

#include "Includes.h"
#include "Helper.h"

namespace Offsets {
	//Offsets
	FN_POINTER UWorld = 0xF1BEEE8; //0xec90bd8
	FN_POINTER ObjectID = 0x18;

	//UWorld
	FN_POINTER OwningGameInstance = 0x1b8; //UGameInstance*
	FN_POINTER Levels = 0x170; //TArray<ULevel*>
	FN_POINTER GameState = 0x158; //AGameStateBase*
	FN_POINTER PersistentLevel = 0x30; //ULevel*


	//UWorld -> PersistentLevel (ULevel)
	FN_POINTER AActors = 0x98;
	FN_POINTER ActorCount = 0xA0;

	//UGameInstance
	FN_POINTER LocalPlayers = 0x38; //TArray<ULocalPlayer*>

	//UPlayer
	FN_POINTER PlayerController = 0x30; //APlayerController*

	//APlayerController
	FN_POINTER AcknowledgedPawn = 0x330; //APawn*
	FN_POINTER PlayerCameraManager = 0x340; //APlayerCameraManager*


	//AActor
	FN_POINTER bHidden = 0x58; //char
	FN_POINTER RootComponent = 0x190; //USceneComponent*
	FN_POINTER CustomTimeDilation = 0x64; //float

	//ACharacter
	FN_POINTER Mesh = 0x310; //USkeletalMeshComponent*

	//APawn
	FN_POINTER PlayerState = 0x2a8; //APlayerState*


	FN_POINTER TeamIndex = 0x10b8; //AFortPlayerStateAthena
	FN_POINTER ReviveFromDBNOTime = 0x45b0; //AFortPlayerStateAthena
	FN_POINTER LocalActorPos = 0x128;
	FN_POINTER CurrentWeapon = 0x8f0;

}
namespace camera
{
	Vector3 rotation;
	Vector3 nigga;
	Vector3 nigga2;
	Vector3 location;
	float fov;
	float zoom;
}
