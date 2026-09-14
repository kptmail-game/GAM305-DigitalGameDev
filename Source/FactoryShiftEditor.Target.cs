using UnrealBuildTool;
public class FactoryShiftEditorTarget : TargetRules
{
    public FactoryShiftEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
        ExtraModuleNames.Add("FactoryShift");
    }
}
