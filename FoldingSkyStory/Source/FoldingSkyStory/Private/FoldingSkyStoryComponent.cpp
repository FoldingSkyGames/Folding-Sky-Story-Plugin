// Copyright Folding Sky Games LLC 2021 All rights reserved.

#include "FoldingSkyStoryComponent.h"

#include "GameFramework/PlayerController.h"

DECLARE_LOG_CATEGORY_CLASS(LogFoldingSkyStoryComponent, Log, All);
#define LOCTEXT_NAMESPACE "FoldingSkyStoryComponent"
UFoldingSkyStoryComponent::UFoldingSkyStoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	OneWayOptionText = LOCTEXT("OneWayContinueKey", "Continue");
	TwoWayStoryOptionOneText = LOCTEXT("TwoWayContinueKey", "Yes");
	TwoWayStoryOptionTwoText = LOCTEXT("TwoWayDiscontinueKey", "No");
}
TArray<FText> UFoldingSkyStoryComponent::GetBasicChoices() const
{
	return TArray<FText> { OneWayOptionText };
}
TArray<FText> UFoldingSkyStoryComponent::GetBinaryChoices() const
{
	return TArray<FText> { TwoWayStoryOptionOneText, TwoWayStoryOptionTwoText};
}

void UFoldingSkyStoryComponent::BeginStoryGraph()
{
	OnStoryBeginGraph_BP();
	OnStoryBeginGraph.Broadcast();
}

void UFoldingSkyStoryComponent::SendStory_NodeInternalUseOnly(const FFoldingSkyStoryNodeParams& NodeParams)
{
	PostStory(NodeParams);
}
void UFoldingSkyStoryComponent::SendStory(const FFoldingSkyStoryNodeParams& NodeParams)
{
	PostStory(NodeParams);
}

void UFoldingSkyStoryComponent::PostStory(const FFoldingSkyStoryNodeParams& Params)
{	
	ChosenValue = MIN_int32;
	CurrentPostedStory = Params;
	CurrentPostedStory.NodeHardRef = CurrentPostedStory.NodeCallback.GetUObject();
	OnStoryPosted.Broadcast(Params);
	OnStoryPosted_BP(Params);
}

void UFoldingSkyStoryComponent::AcceptChoiceValue(int32 Choice)
{
	if (CurrentPostedStory.Choices.IsValidIndex(Choice) || Choice == -1)
	{
		ChosenValue = Choice;
		const FText ChoiceText = CurrentPostedStory.Choices.IsValidIndex(Choice) ? CurrentPostedStory.Choices[Choice] : FText::GetEmpty();
		const UObject* OldNodeRef = CurrentPostedStory.NodeHardRef;
		const FOnStoryChoiceMade OldNodeCallback = CurrentPostedStory.NodeCallback;
		if (OldNodeRef) 
		{
			OnStoryChoiceAccepted_BP(Choice, ChoiceText);
			OldNodeCallback.ExecuteIfBound(Choice); // to stop self forwarding when posting new nodes on callbacks
			if (OldNodeRef == CurrentPostedStory.NodeHardRef)
			{
				CurrentPostedStory.NodeHardRef = nullptr;
				CurrentPostedStory.NodeCallback.Clear();
			}
		}
	}
	else
	{
		UE_LOG(LogFoldingSkyStoryComponent, Error, TEXT("Choice Value %d does not exist in the currently posted array of choices. Number of choices is %d."), Choice, CurrentPostedStory.Choices.Num());
	}
}
#undef LOCTEXT_NAMESPACE