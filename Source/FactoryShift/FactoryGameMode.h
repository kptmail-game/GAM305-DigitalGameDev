#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FactoryGameMode.generated.h"
UCLASS()
class FACTORYSHIFT_API AFactoryGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    AFactoryGameMode();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
private:
    bool bPrototypeTest = false;
    bool bPrototypeCapture = false;
    bool bTestFailed = false;
    int32 TestStage = 0;
    float StageTime = 0.f;
    float HighestJump = 0.f;
    FVector TestStart;
    void CheckPrototype(bool bPassed, const TCHAR* Name);
    bool bAlphaTest=false;
    void RunAlphaChecks(class AFactoryCharacter* Player);
};
