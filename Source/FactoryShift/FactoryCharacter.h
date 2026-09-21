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
    UFUNCTION(BlueprintCallable, Category="Gameplay") void ApplyFactoryDamage(float Amount);
    UFUNCTION(BlueprintCallable, Category="Gameplay") void AddPowerCell();
    UFUNCTION(BlueprintCallable, Category="Gameplay") void AddHealth(float Amount);
    UFUNCTION(BlueprintCallable, Category="Gameplay") void GiveShield(float Duration = 8.f);
    UFUNCTION(BlueprintCallable, Category="Gameplay") void GiveSpeed(float Duration = 8.f);
    UFUNCTION(BlueprintCallable, Category="Gameplay") bool TryExit();
    UFUNCTION(BlueprintCallable, Category="Gameplay") void SetSlowingSource(AActor* Source, bool bInside);
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay") float Health = 100.f;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay") int32 PowerCells = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay") bool bWon = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay") bool bDead = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay") float ShieldRemaining = 0.f;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay") float SpeedRemaining = 0.f;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay") FString StatusMessage;
    bool bAlphaMode = false;
    float RunTime = 0.f;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<class UCameraComponent> SideCamera;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<class UStaticMeshComponent> PlaceholderBody;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera") float CameraDistance = 1300.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera") float CameraHeight = 180.f;
protected:
    virtual void BeginPlay() override;
private:
    FVector SpawnLocation;
    float DamageCooldown = 0.f;
    TSet<TWeakObjectPtr<AActor>> SlowingSources;
};
