// Copyright Folding Sky Games LLC 2021 All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "K2Node_AddPinInterface.h"
#include "K2Node_Switch.h"
#include "K2Node_TestyTest.generated.h"

UCLASS(MinimalAPI)
class UK2Node_TestyTest : public UK2Node_Switch //: public IK2Node_AddPinInterface
{
	GENERATED_UCLASS_BODY()
public:
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual bool ShouldShowNodeProperties() const override { return true; }

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	virtual FName GetUniquePinName() override;
	virtual FName GetPinNameGivenIndex(int32 Index) const override;
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual FEdGraphPinType GetPinType() const override;
	virtual bool CanRemoveExecutionPin(UEdGraphPin* TargetPin) const override;
	virtual void CreateFunctionPin() override;
protected:
	virtual void CreateCasePins() override;
	virtual void CreateSelectionPin() override;
	virtual void RemovePin(UEdGraphPin* TargetPin) override;
	UPROPERTY()
		int32 NumChoices;
	void SetNumChoices(const int32& NewValue);
};