#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FactoryCharacter.generated.h"

UCLASS(Blueprintable)
class FACTORYSHIFT_API AFactoryCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    AFactoryCharacter();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* Input) override;
    UFUNCTION(BlueprintCallable, Category="Movement") void MoveHorizontal(float Value);
    UFUNCTION(BlueprintCallable, Category="Movement") void RestartPrototype();
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<class UCameraComponent> SideCamera;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<class UStaticMeshComponent> PlaceholderBody;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera") float CameraDistance = 1300.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera") float CameraHeight = 180.f;
protected:
    virtual void BeginPlay() override;
private:
    FVector SpawnLocation;
};
