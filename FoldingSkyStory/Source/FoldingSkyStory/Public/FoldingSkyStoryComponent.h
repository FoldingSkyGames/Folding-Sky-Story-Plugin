// Copyright Folding Sky Games LLC 2021 All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "FoldingSkyStoryStructs.h"
#include "Components/ActorComponent.h"
#include "FoldingSkyStoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoryPosted, const FFoldingSkyStoryNodeParams&, Params);

class APlayerController;
class UPlayerStoryComponent;

UCLASS(Blueprintable, DisplayName = "FS Story Blueprint")
class FOLDINGSKYSTORY_API UFoldingSkyStoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFoldingSkyStoryComponent();
	/** Fires the OnBeginStoryGraph event, call this to 
	*	notify the blueprint it should begin traversing its story nodes  */
	UFUNCTION(BlueprintCallable, Category="Folding Sky Story|Component")
		void BeginStoryGraph();
	/** Accepts a numeric value representing the choice on the blueprint node that is desired
	*	-1 fires the cancellation event
	*	invalid choice indicies will not be processed */
	UFUNCTION(BlueprintCallable, Category = "Folding Sky Story|Component")
		void AcceptChoiceValue(int32 Choice);
	/**	Sends a set of story data through this component for posting */
	UFUNCTION(BlueprintCallable, Category = "Folding Sky Story|Component")
		void SendStory(const FFoldingSkyStoryNodeParams& Params);

	/**	Fired when BeginStoryGraph() is called to notify the blueprint
	*	it should start traversing it's story nodes */
	UPROPERTY(BlueprintAssignable, Category = "Folding Sky Story|Component")
		FOnStoryActionEvent OnStoryBeginGraph;
	/**	Called EVERY time a story node is reached on the blueprint graph, 
	*	even when resending a previously sent node  */
	UPROPERTY(BlueprintAssignable, Category = "Folding Sky Story|Component")
		FOnStoryPosted OnStoryPosted;

	/**	The default text that will display for one way story nodes belonging to this story component  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Folding Sky Story|Component")
		FText OneWayOptionText;
	/**	The default affirmative text that will display for two way story nodes belonging to this story component  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Folding Sky Story|Component")
		FText TwoWayStoryOptionOneText;
	/**	The default negative text that will display for two way story nodes belonging to this story component  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Folding Sky Story|Component")
		FText TwoWayStoryOptionTwoText;

	void SendStory_NodeInternalUseOnly(const FFoldingSkyStoryNodeParams& NodeParams);
	TArray<FText> GetBasicChoices() const;
	TArray<FText> GetBinaryChoices() const;
protected:
	
	/** An event to be bound by the story blueprint graph, signaling the story graph should begin traversal of it's nodes */
	UFUNCTION(BlueprintImplementableEvent, Category = "Folding Sky Story|Component", meta = (DisplayName = "On Story Begin Graph"))
		void OnStoryBeginGraph_BP();
	/** An event to be bound by the story blueprint graph, fired every time 
	/** An event to be bound by the story blueprint graph, fired every time 
	*	a story node is reached or story content has been supplied for posting */
	UFUNCTION(BlueprintImplementableEvent, Category = "Folding Sky Story|Component", meta = (DisplayName = "On Story Posted"))
		void OnStoryPosted_BP(const FFoldingSkyStoryNodeParams& Params);
	/**	A BlueprintImplementableEvent to be bound by the story blueprint graph
	*	called when AcceptChoiceValue is called and will provide the choice supplied therein at that time */
	UFUNCTION(BlueprintImplementableEvent, Category = "Folding Sky Story|Component", meta = (DisplayName = "On Story Choice Accepted"))
		void OnStoryChoiceAccepted_BP(const int32& Choice, const FText& ChoiceText);

	/**	 calls the OnStoryPosted events and sets the proxy callback */
	void PostStory(const FFoldingSkyStoryNodeParams& Params);
	/** Data involving the story node that is currently posted, includes the callback for the blueprint node */
	UPROPERTY()
		FFoldingSkyStoryNodeParams CurrentPostedStory;
	/** Data involving the story node that is currently posted, includes the callback for the blueprint node */
	UPROPERTY()
		int32 ChosenValue = MIN_int32;
};
