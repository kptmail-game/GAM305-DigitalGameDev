#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FactoryHUD.generated.h"
UCLASS()
class FACTORYSHIFT_API AFactoryHUD : public AHUD
{
    GENERATED_BODY()
public:
    virtual void DrawHUD() override;
};
