using UnrealBuildTool;

public class FoldingSkyStoryEditor : ModuleRules
{
	public FoldingSkyStoryEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "Slate",
                "SlateCore",
                "Engine",
                "Kismet",  // for FWorkflowCentricApplication
                "EditorStyle",
				"InputCore",
				"UnrealEd",
				"KismetCompiler",
				"BlueprintGraph",

				"FoldingSkyStory"			}
			);
			
	}
}
