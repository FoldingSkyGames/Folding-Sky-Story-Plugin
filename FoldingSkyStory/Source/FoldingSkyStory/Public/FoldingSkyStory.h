#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleInterface.h"

class FFoldingSkyStoryModule : public IModuleInterface
{
public:
	/** Constructor */
	FFoldingSkyStoryModule() { }
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
};
