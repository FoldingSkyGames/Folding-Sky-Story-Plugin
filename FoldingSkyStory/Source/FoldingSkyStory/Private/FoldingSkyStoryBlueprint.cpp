#include "FoldingSkyStoryBlueprint.h"

UFoldingSkyStoryBlueprint::UFoldingSkyStoryBlueprint() : Super()
{
}

#if WITH_EDITOR

UFoldingSkyStoryBlueprint* UFoldingSkyStoryBlueprint::FindRootStoryBlueprint(UFoldingSkyStoryBlueprint* DerivedBlueprint)
{
	UFoldingSkyStoryBlueprint* ParentBP = NULL;

	// Is there a story blueprint in the ancestry of this class ?
	for (UClass* ParentClass = DerivedBlueprint->ParentClass; ParentClass != UObject::StaticClass(); ParentClass = ParentClass->GetSuperClass())
	{
		if (UFoldingSkyStoryBlueprint* TestBP = Cast<UFoldingSkyStoryBlueprint>(ParentClass->ClassGeneratedBy))
		{
			ParentBP = TestBP;
		}
	}

	return ParentBP;
}

#endif
