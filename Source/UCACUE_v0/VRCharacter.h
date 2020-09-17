// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

UCLASS()
class UCACUE_V0_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVRCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool FindTeleportDestination(FVector &OutLocation);
	void UpdateDestinationMarker();
	void UpdateBlinkers();
	FVector2D GetBlinkerCenter();

	void MoveForward(float throttle);
	void MoveRight(float throttle);
	
	void  BeginTeleport();
	void  FinishTeleport();

	void StartFade(float fromAlpha, float toAlpha);

private:
	
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UMotionControllerComponent* LeftController;

	UPROPERTY(VisibleAnywhere)
	class UMotionControllerComponent* RightController;
	
	UPROPERTY()
	class USceneComponent* VRRoot;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DestinationMarker;

	UPROPERTY()
	class UPostProcessComponent* PostProcessComponent;
	
	UPROPERTY()
	class UMaterialInstanceDynamic* BlinkerMaterialInstance;


private:
	//
	UPROPERTY(EditAnywhere)
	float maxTeleportDistance = 1000;

	UPROPERTY(EditAnywhere)
	float teleportFadeTime = 1;

	UPROPERTY(EditAnywhere)
	FVector TeleportProjectionExtend = FVector(100, 100, 100);

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* BlinkerMaterialBase;

	UPROPERTY(EditAnywhere)
		class UCurveFloat* RadiusVsVelocity;
};
