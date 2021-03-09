// Copyright Folding Sky Games LLC 2021 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/Blueprint.h"
#include "FoldingSkyStoryBlueprint.generated.h"

UCLASS(Category = "Story", meta = (DisplayName = "Story Blueprint", Tooltip = "New Story Blueprint"))
class FOLDINGSKYSTORY_API UFoldingSkyStoryBlueprint : public UBlueprint
{
	GENERATED_BODY()
public:
	UFoldingSkyStoryBlueprint();
#if WITH_EDITOR	
	// UBlueprint interface
	virtual bool SupportedByDefaultBlueprintFactory() const override
	{
		return false;
	}
	// End of UBlueprint interface
#endif
};
