#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "HandController.h"

#include "VRCharacter.generated.h"

//My Log
DECLARE_LOG_CATEGORY_EXTERN(LogXRLab, Log, All);

UCLASS()
class XRLAB_API AVRCharacter : public ACharacter
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

	void MoveForward(float throttle);
	void MoveRight(float throttle);

	bool FindTeleportDestination(TArray<FVector>& OutPath, FVector& OutLocation);
	void DrawTeleportPath(const TArray<FVector>& Path);
	void UpdateSpline(const TArray<FVector>& Path);
	void UpdateDestinationMarker();

	void  BeginTeleport();
	void  FinishTeleport();

	void StartFade(float fromAlpha, float toAlpha);

	void GripLeft() { LeftController->Grip(); }
	void ReleaseLeft() { LeftController->Release(); }

	void GripRight() { RightController->Grip(); }
	void ReleaseRight() { RightController->Release(); }

private:

	UPROPERTY()
	class USceneComponent* VRRoot;
	
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY()
	AHandController* LeftController;

	UPROPERTY()
	AHandController* RightController;

	UPROPERTY(VisibleAnywhere)
	class USplineComponent* TeleportPath;

	UPROPERTY()
	TArray<class USplineMeshComponent*> TeleportPathMeshPool;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DestinationMarker;

	UPROPERTY(EditDefaultsOnly)
	class AAPIRESTClient* APIRESTInterface;


private:	// Configuration Parameters

	UPROPERTY(EditAnywhere)
	float TeleportProjectileRadius = 10;

	UPROPERTY(EditAnywhere)
	float TeleportProjectileSpeed = 800;

	UPROPERTY(EditAnywhere)
	float TeleportSimulationTime = 1;

	UPROPERTY(EditAnywhere)
	float teleportFadeTime = 1;

	UPROPERTY(EditAnywhere)
	FVector TeleportProjectionExtend = FVector(100, 100, 100);

	UPROPERTY(EditDefaultsOnly)
	class UStaticMesh* TeleportArchMesh;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* TeleportArchMaterial;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController> HandControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAPIRESTClient> APIRESTClass;

};
