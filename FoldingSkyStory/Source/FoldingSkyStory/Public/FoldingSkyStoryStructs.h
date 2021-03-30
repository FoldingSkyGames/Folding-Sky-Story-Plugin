// Copyright Folding Sky Games LLC 2021 All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "FoldingSkyStoryStructs.generated.h"

class UDialogueWave;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoryActionEvent);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnStoryChoiceMade, int32, Choice);

USTRUCT(Blueprintable, BlueprintType)
struct FOLDINGSKYSTORY_API FFoldingSkyStoryNodeParams
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Folding Sky Story|Structs")
		FOnStoryChoiceMade NodeCallback;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Folding Sky Story|Structs")
		TSoftObjectPtr<UDialogueWave> Dialogue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Folding Sky Story|Structs")
		FText Words;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Folding Sky Story|Structs")
		TArray<FText> Choices;
	UPROPERTY()
		UObject* NodeHardRef = nullptr;
	FFoldingSkyStoryNodeParams() {};
	FFoldingSkyStoryNodeParams(const FOnStoryChoiceMade& Callback, const FText& InText, const TArray<FText>& InChoices) :
		Words(InText), Choices(InChoices) 
	{
		SetCallback(Callback);
	};
	FFoldingSkyStoryNodeParams(const FOnStoryChoiceMade& Callback, const TSoftObjectPtr<UDialogueWave>& InDialogue, const TArray<FText>& InChoices) :
		Dialogue(InDialogue), Choices(InChoices) 
	{
		SetCallback(Callback);
	};
	void SetCallback(const FOnStoryChoiceMade& Callback)
	{
		NodeCallback = Callback;
		NodeHardRef = NodeCallback.GetUObject();
	}
};
