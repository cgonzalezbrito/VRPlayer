// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"
#include "Camera/CameraComponent.h"

#include "Core.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

//General Log
DEFINE_LOG_CATEGORY(LogXRLab);

// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	// testHttpRequest();
	
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AVRCharacter::MoveRight);
	//PlayerInputComponent->BindAction(TEXT("Teleport"), IE_Released, this, &AVRCharacter::BeginTeleport);
	
}

void AVRCharacter::testHttpRequest()
{
	UE_LOG(LogXRLab, Log, TEXT("Starting test [%s] Url=[%s]"),*Verb, *Url);

	TSharedPtr<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AVRCharacter::RequestComplete);
	
	/*Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));*/
	//Request->ProcessRequest();


	
	Request->SetURL(FString::Printf(TEXT("%s?db=%s&login=%s&password=%s"), *Url,*db, *username, *password)); //WORKS!!
	/*Request->SetURL(Url);
	Request->SetContentAsString(FString::Printf(TEXT("db=%s&login=%s&password=%s"), *db, *username, *password));*/
	if (Payload.Len() > 0)
	{
		Request->SetContentAsString(Payload);
	}
	Request->SetVerb(Verb);
	Request->ProcessRequest();

}

void AVRCharacter::RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	//if (FJsonSerializer::Deserialize(Reader, JsonObject))
	//{
	//	//Get the value of the json object by field name
	//	int32 recievedInt = JsonObject->GetIntegerField("customInt");

	//	//Output it to the engine
	//	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
	//}

	if (!HttpResponse.IsValid())
	{
		UE_LOG(LogXRLab, Log, TEXT("Test failed. NULL response"));
	}
	else
	{
		UE_LOG(LogXRLab, Log, TEXT("Completed test [%s] Url=[%s] Response=[%d] [%s]"),
			*HttpRequest->GetVerb(),
			*HttpRequest->GetURL(),
			HttpResponse->GetResponseCode(),
			*HttpResponse->GetContentAsString()
		);
	}

	//if ((--TestsToRun) <= 0)
	//{
	//	HttpRequest->OnProcessRequestComplete().Unbind();
	//	// Done with the test. Delegate should always gets called
	//	delete this;
	//}
}

void AVRCharacter::MoveForward(float throttle)
{
	AddMovementInput(throttle * Camera->GetForwardVector());
}

void AVRCharacter::MoveRight(float throttle)
{
	AddMovementInput(throttle * Camera->GetRightVector());
}
