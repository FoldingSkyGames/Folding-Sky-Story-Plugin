#pragma once

#include "CoreMinimal.h"

#include "FoldingSkyStoryStructs.generated.h"

DECLARE_DELEGATE_RetVal(int32, FOnStoryChoiceReturn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoryActionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoryVectorEvent, FVector, Vector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoryEngagement, APlayerController*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoryChoiceEvent, int32, Choice);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnStoryChoiceMade, int32, Choice);

class APlayerController;
class USceneComponent;
class USoundCue;
class UTexture2D;
class UDialogueWave;

USTRUCT(Blueprintable, BlueprintType)
struct FOLDINGSKYSTORY_API FFoldingSkyStorySpeakerParams
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* Anchor = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSoftObjectPtr<UTexture2D> Image;
	FFoldingSkyStorySpeakerParams() {};
	FFoldingSkyStorySpeakerParams(USceneComponent* InAnchor, const FText& InName, const TSoftObjectPtr<UTexture2D>& InImage) {};
};

USTRUCT()
struct FOLDINGSKYSTORY_API FFoldingSkyStoryNodeParams
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FOnStoryChoiceMade NodeCallback;
	UPROPERTY()
		TSoftObjectPtr<UDialogueWave> Dialogue;
	UPROPERTY()
		FText Words;	
	UPROPERTY()
		FString JsonData;
	UPROPERTY()
		TArray<FText> Choices;
	
	FFoldingSkyStoryNodeParams() {};
	FFoldingSkyStoryNodeParams(const FOnStoryChoiceMade& Callback, const FText& InText, const TArray<FText>& InChoices) :
		NodeCallback(Callback), Words(InText), Choices(InChoices) {};
	FFoldingSkyStoryNodeParams(const FOnStoryChoiceMade& Callback, const TSoftObjectPtr<UDialogueWave>& InDialogue, const TArray<FText>& InChoices) :
		NodeCallback(Callback), Dialogue(InDialogue), Choices(InChoices) {};
	FFoldingSkyStoryNodeParams(const FOnStoryChoiceMade& Callback, const FString& InJson, const TArray<FText>& InChoices) :
		NodeCallback(Callback), JsonData(InJson), Choices(InChoices) {};
};
USTRUCT(Blueprintable, BlueprintType)
struct FOLDINGSKYSTORY_API FFoldingSkyStoryParams
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Words;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FText> Choices;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSoftObjectPtr<UTexture2D> Image;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSoftObjectPtr<UDialogueWave> Dialogue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FOnStoryChoiceMade NodeCallback;
	UPROPERTY()
		UObject* NodeHardRef = nullptr;
	FFoldingSkyStoryParams() {};
	FFoldingSkyStoryParams(const FText& InName, const FText& InText, const TArray<FText>& InChoices, const TSoftObjectPtr<UTexture2D>& InImage) :
		Name(InName), Words(InText), Choices(InChoices), Image(InImage) {};
	FFoldingSkyStoryParams(const FFoldingSkyStorySpeakerParams& SpeakerParams, const FFoldingSkyStoryNodeParams& NodeParams) :
		Name(SpeakerParams.Name), Words(NodeParams.Words), Choices(NodeParams.Choices), Image(SpeakerParams.Image), Dialogue(NodeParams.Dialogue), NodeCallback(NodeParams.NodeCallback)  {};

};


DECLARE_DELEGATE_FourParams(
	FOnStorySaveReengage,
	APlayerController*,
	USceneComponent*,
	FOnStoryChoiceMade,
	const FFoldingSkyStoryParams&
);