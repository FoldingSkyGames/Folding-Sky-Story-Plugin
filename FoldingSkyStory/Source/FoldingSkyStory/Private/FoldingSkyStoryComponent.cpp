#include "FoldingSkyStoryComponent.h"

#include "GameFramework/PlayerController.h"

DECLARE_LOG_CATEGORY_CLASS(LogFoldingSkyStoryComponent, Log, All);

UFoldingSkyStoryComponent::UFoldingSkyStoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	OneWayOptionText = NSLOCTEXT("StoryDefaultText", "OneWayContinueKey", "Continue");
	TwoWayStoryOptionOneText = NSLOCTEXT("StoryDefaultText", "TwoWayContinueKey", "Yes");
	TwoWayStoryOptionTwoText = NSLOCTEXT("StoryDefaultText", "TwoWayDiscontinueKey", "No");
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
	const FFoldingSkyStorySpeakerParams& IdentityParams = OnStoryGetSpeakerIdentity_BP();
	FFoldingSkyStoryParams Params(IdentityParams, NodeParams);
	PostStory(false, Params);
}

void UFoldingSkyStoryComponent::ResendStory(const FOnStoryChoiceMade& ChoiceCallback, const FFoldingSkyStoryParams& Params)
{
	PostStory(true, Params);
}
void UFoldingSkyStoryComponent::PostStory(const bool bIsReplayed, const FFoldingSkyStoryParams& Params)
{	
	ChosenValue = MIN_int32;
	CurrentPostedStory.NodeHardRef = nullptr;
	CurrentPostedStory = Params;
	CurrentPostedStory.NodeHardRef = CurrentPostedStory.NodeCallback.GetUObject();
	OnStoryPosted.Broadcast(bIsReplayed, Params);
	OnStoryPosted_BP(bIsReplayed, Params);
}

void UFoldingSkyStoryComponent::AcceptChoiceValue(int32 Choice)
{
	if (CurrentPostedStory.Choices.IsValidIndex(Choice) || Choice == -1)
	{
		ChosenValue = Choice;
		const FText& ChoiceText = CurrentPostedStory.Choices.IsValidIndex(Choice) ? CurrentPostedStory.Choices[Choice] : FText::GetEmpty();
		OnStoryChoiceAccepted_BP(Choice, ChoiceText);
		CurrentPostedStory.NodeCallback.ExecuteIfBound(Choice);
		CurrentPostedStory.NodeHardRef = nullptr;
	}
	else
	{
		UE_LOG(LogFoldingSkyStoryComponent, Error, TEXT("Choice Value %d does not exist in the currently posted array of choices. Number of choices is %d."), Choice, CurrentPostedStory.Choices.Num());
	}
}