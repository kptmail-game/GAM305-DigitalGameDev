using UnrealBuildTool;
public class FactoryShiftTarget : TargetRules
{
    public FactoryShiftTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
        ExtraModuleNames.Add("FactoryShift");
    }
}
