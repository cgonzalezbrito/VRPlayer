// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"

#include "APIRESTClient.generated.h"

//My Log
//DECLARE_LOG_CATEGORY_EXTERN(LogAPIREST, Log, All);

UCLASS()
class XRLAB_API AAPIRESTClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPIRESTClient();

	/**
	 * Delegate called when the request completes
	 *
	 * @param HttpRequest - object that started/processed the request
	 * @param HttpResponse - optional response object if request completed
	 * @param bSucceeded - true if Url connection was made and response was received
	 */

	void RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/**
	 * Constructor
	 *
	 * @param Verb - verb to use for request (GET,POST,DELETE,etc)
	 * @param Payload - optional payload string
	 * @param Url - url address to connect to
	 * @param InIterations - total test iterations to run
	 */
	UFUNCTION()
		void httpRequest();

private:	// Configuration Parameters
	
	UPROPERTY(EditAnywhere)
	FString Verb = "GET";

	UPROPERTY(EditAnywhere)
	FString Url = "";

	UPROPERTY(EditAnywhere)
	int32 TestsToRun = 1;

	UPROPERTY(EditAnywhere)
	FString Payload;

	UPROPERTY(EditAnywhere)
	FString db = "";

	UPROPERTY(EditAnywhere)
	FString username = "";

	UPROPERTY(EditAnywhere)
	FString password = "";

};
