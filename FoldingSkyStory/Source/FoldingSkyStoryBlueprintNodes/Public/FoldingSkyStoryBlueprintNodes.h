#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"



class FFoldingSkyStoryBlueprintNodesModule : public IModuleInterface
{
public:
	/** Constructor */
	FFoldingSkyStoryBlueprintNodesModule() { }
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
};
