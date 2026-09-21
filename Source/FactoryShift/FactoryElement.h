#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FactoryElement.generated.h"

UENUM(BlueprintType)
enum class EFactoryElementKind : uint8 { Cell, Health, Shield, Speed, Spikes, Electrical, Steam, SlowFloor, Press, SwingArm, MovingBarrier, Exit };

UCLASS(Blueprintable)
class FACTORYSHIFT_API AFactoryElement : public AActor
{
    GENERATED_BODY()
public:
    AFactoryElement();
    virtual void Tick(float Dt) override;
    virtual void BeginPlay() override;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EFactoryElementKind Kind = EFactoryElementKind::Cell;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<class UBoxComponent> Trigger;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<class UStaticMeshComponent> Mesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<class UTextRenderComponent> Label;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float CycleOffset = 0.f;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool bCollected=false;
    UFUNCTION(BlueprintCallable) void Configure(EFactoryElementKind Type, FVector Size);
    void ResetElement();
    void Interact(class AFactoryCharacter* Player);
private:
    FVector Start;
    float Elapsed=0.f;
    bool bActive=true;
    bool bLastActive=true;
    TWeakObjectPtr<class AFactoryCharacter> SlowedPlayer;
};
