
#include "K2Node_TestyTest.h"
#include "Kismet/KismetMathLibrary.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"

UK2Node_TestyTest::UK2Node_TestyTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FunctionName = TEXT("NotEqual_IntInt");
	FunctionClass = UKismetMathLibrary::StaticClass();
}
void UK2Node_TestyTest::SetNumChoices(const int32& NewValue)
{
	NumChoices = NewValue;
}
void UK2Node_TestyTest::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);
}
FText UK2Node_TestyTest::GetTooltipText() const
{
	return FText::FormatOrdered(FTextFormat::FromString(TEXT("A story node with {0} to be passed along the story event graph\n{1}")), FText::FromString("meh"), FText::FromString("TESTY TEST"));
}

void UK2Node_TestyTest::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	// actions get registered under specific object-keys; the idea is that 
	// actions might have to be updated (or deleted) if their object-key is  
	// mutated (or removed)... here we use the node's class (so if the node 
	// type disappears, then the action should go with it)
	UClass* ActionKey = GetClass();
	// to keep from needlessly instantiating a UBlueprintNodeSpawner, first   
	// check to make sure that the registrar is looking for actions of this type
	// (could be regenerating actions for a specific asset, and therefore the 
	// registrar would only accept actions corresponding to that asset)
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}


FName UK2Node_TestyTest::GetPinNameGivenIndex(int32 Index) const
{
	return *FString::Printf(TEXT("%d"), Index);
}
FName UK2Node_TestyTest::GetUniquePinName()
{
	FName NewPinName;
	int32 i = NumChoices;
	while (true)
	{
		NewPinName = GetPinNameGivenIndex(i++);
		if (!FindPin(NewPinName))
		{
			break;
		}
	}
	return NewPinName;
}

void UK2Node_TestyTest::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	Super::ReallocatePinsDuringReconstruction(OldPins);

	int32 ExecOutPinCount = NumChoices;

	UEdGraphPin* DefaultPin = GetDefaultPin();

	for (int32 i = bHasDefaultPin ? 1 : 0; i < OldPins.Num(); ++i)
	{
		UEdGraphPin* TestPin = OldPins[i];
		if (UEdGraphSchema_K2::IsExecPin(*TestPin) && (TestPin->Direction == EGPD_Output))
		{
			// Skip the default pin to avoid creating an extra output pin in the case where the default pin has been toggled off
			if (TestPin->PinName != TEXT("Default"))
			{
				const FName NewPinName = GetPinNameGivenIndex(ExecOutPinCount);
				ExecOutPinCount++;

				// Make sure the old pin and new pin names match
				TestPin->PinName = NewPinName;

				// Create the new output pin to match
				CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, NewPinName);
				CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Text, NewPinName);
			}
		}
	}
}
FEdGraphPinType UK2Node_TestyTest::GetPinType() const
{
	FEdGraphPinType PinType;
	PinType.PinCategory = UEdGraphSchema_K2::PC_Int;
	return PinType;
}
bool UK2Node_TestyTest::CanRemoveExecutionPin(UEdGraphPin* TargetPin) const
{
	if (!Super::CanRemoveExecutionPin(TargetPin))
	{
		return false;
	}

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	int32 PinIndex = (NumChoices >= 0) ? NumChoices : 0;
	int32 FoundIndex = INDEX_NONE;

	UEdGraphPin* DefaultPin = GetDefaultPin();

	if (TargetPin == DefaultPin)
	{
		return true;
	}

	for (int32 i = 0; i < Pins.Num(); ++i)
	{
		UEdGraphPin* PotentialPin = Pins[i];
		if (K2Schema->IsExecPin(*PotentialPin) && (PotentialPin->Direction == EGPD_Output) && (PotentialPin != DefaultPin))
		{
			if (PotentialPin == TargetPin)
			{
				FoundIndex = PinIndex;
			}

			++PinIndex;
		}
	}

	// Only allow removing last pin
	if (FoundIndex != PinIndex - 1)
	{
		return false;
	}
	return true;
}

void UK2Node_TestyTest::CreateFunctionPin()
{
	// Set properties on the function pin
	UEdGraphPin* FunctionPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, FunctionClass, FunctionName);
	FunctionPin->bDefaultValueIsReadOnly = true;
	FunctionPin->bNotConnectable = true;
	FunctionPin->bHidden = true;

	UFunction* Function = FindUField<UFunction>(FunctionClass, FunctionName);
	const bool bIsStaticFunc = Function->HasAllFunctionFlags(FUNC_Static);
	if (bIsStaticFunc)
	{
		// Wire up the self to the CDO of the class if it's not us
		if (UBlueprint* BP = GetBlueprint())
		{
			UClass* FunctionOwnerClass = Function->GetOuterUClass();
			if (!BP->SkeletonGeneratedClass->IsChildOf(FunctionOwnerClass))
			{
				FunctionPin->DefaultObject = FunctionOwnerClass->GetDefaultObject();
			}
		}
	}
}

FText UK2Node_TestyTest::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("K2Node", "TestyText", "Testy Test");
}

void UK2Node_TestyTest::CreateCasePins() { }

void UK2Node_TestyTest::CreateSelectionPin()
{
	UEdGraphPin* Pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, TEXT("Selection"));
	GetDefault<UEdGraphSchema_K2>()->SetPinAutogeneratedDefaultValueBasedOnType(Pin);
}

void UK2Node_TestyTest::RemovePin(UEdGraphPin* TargetPin)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	int32 PinIndex = (NumChoices >= 0) ? NumChoices : 0;

	UEdGraphPin* DefaultPin = GetDefaultPin();

	for (int32 i = 0; i < Pins.Num(); ++i)
	{
		UEdGraphPin* PotentialPin = Pins[i];
		if (K2Schema->IsExecPin(*PotentialPin) && (PotentialPin->Direction == EGPD_Output) && (PotentialPin != DefaultPin) && (PotentialPin != TargetPin))
		{
			PotentialPin->PinName = GetPinNameGivenIndex(PinIndex);
			++PinIndex;
		}
	}
}