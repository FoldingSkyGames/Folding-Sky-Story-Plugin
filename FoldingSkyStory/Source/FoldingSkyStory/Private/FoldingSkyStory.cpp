// Copyright Folding Sky Games LLC 2021 All rights reserved.

#include "FoldingSkyStory.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FFoldingSkyStoryModule"

class FFoldingSkyStoryModule : public IFoldingSkyStoryModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFoldingSkyStoryModule, FoldingSkyStory);