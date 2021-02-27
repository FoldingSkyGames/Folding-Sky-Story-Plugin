using UnrealBuildTool;

public class FoldingSkyStoryBlueprintNodes : ModuleRules
{
	public FoldingSkyStoryBlueprintNodes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;			
		
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Json",
				"Engine",
				"BlueprintGraph",
				"KismetCompiler",
                "UnrealEd",
				"ToolMenus",
				"Slate",
				"SlateCore",

				"FoldingSkyStory"	
			});
	}
}
