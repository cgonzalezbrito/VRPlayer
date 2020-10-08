// Fill out your copyright notice in the Description page of Project Settings.


#include "APIRESTClient.h"
#include "Core.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

// Sets default values
AAPIRESTClient::AAPIRESTClient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAPIRESTClient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPIRESTClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAPIRESTClient::httpRequest()
{
	//UE_LOG(LogAPIREST, Log, TEXT("Starting test [%s] Url=[%s]"), *Verb, *Url);

	TSharedPtr<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AAPIRESTClient::RequestComplete);

	/*Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));*/
	//Request->ProcessRequest();



	Request->SetURL(FString::Printf(TEXT("%s?db=%s&login=%s&password=%s"), *Url, *db, *username, *password)); //WORKS!!
	/*Request->SetURL(Url);
	Request->SetContentAsString(FString::Printf(TEXT("db=%s&login=%s&password=%s"), *db, *username, *password));*/
	if (Payload.Len() > 0)
	{
		Request->SetContentAsString(Payload);
	}
	Request->SetVerb(Verb);
	Request->ProcessRequest();

}

void AAPIRESTClient::RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
		//UE_LOG(LogAPIREST, Log, TEXT("Test failed. NULL response"));
	}
	else
	{
		/*UE_LOG(LogAPIREST, Log, TEXT("Completed test [%s] Url=[%s] Response=[%d] [%s]"),
			*HttpRequest->GetVerb(),
			*HttpRequest->GetURL(),
			HttpResponse->GetResponseCode(),
			*HttpResponse->GetContentAsString()
		);*/
	}

	//if ((--TestsToRun) <= 0)
	//{
	//	HttpRequest->OnProcessRequestComplete().Unbind();
	//	// Done with the test. Delegate should always gets called
	//	delete this;
	//}
}

