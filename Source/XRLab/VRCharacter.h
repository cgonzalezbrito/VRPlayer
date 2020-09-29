#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHttpRequest.h"

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

	/**
	 * Delegate called when the request completes
	 *
	 * @param HttpRequest - object that started/processed the request
	 * @param HttpResponse - optional response object if request completed
	 * @param bSucceeded - true if Url connection was made and response was received
	 */
	
	void RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

private:

	void MoveForward(float throttle);
	void MoveRight(float throttle);

private:

	UPROPERTY()
	class USceneComponent* VRRoot;
	
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	/**
	 * Constructor
	 *
	 * @param Verb - verb to use for request (GET,POST,DELETE,etc)
	 * @param Payload - optional payload string
	 * @param Url - url address to connect to
	 * @param InIterations - total test iterations to run
	 */
	UFUNCTION()
	void testHttpRequest();


private:	// Configuration Parameters
	UPROPERTY(EditAnywhere)
	FString Verb = "GET";

	UPROPERTY(EditAnywhere)
	FString Url = "https://xrlab.ucacue.edu.ec/api/auth/token";

	UPROPERTY(EditAnywhere)
	int32 TestsToRun = 1;
	
	UPROPERTY(EditAnywhere)
	FString Payload;

	UPROPERTY(EditAnywhere)
	FString db = "XRLAB";
	
	UPROPERTY(EditAnywhere)
	FString username = "cesar.gonzalez@ucacue.edu.ec";

	UPROPERTY(EditAnywhere)
	FString password = "testpass";

};
