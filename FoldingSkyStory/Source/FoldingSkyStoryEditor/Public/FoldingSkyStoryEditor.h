#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"



class FFoldingSkyStoryEditorModule : public IModuleInterface
{
public:
	/** Constructor */
	FFoldingSkyStoryEditorModule() { }
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
};
