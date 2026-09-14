#include "FactoryGameMode.h"
#include "FactoryCharacter.h"
#include "FactoryHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "UnrealClient.h"
AFactoryGameMode::AFactoryGameMode()
{
    DefaultPawnClass = AFactoryCharacter::StaticClass();
    HUDClass = AFactoryHUD::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
}

void AFactoryGameMode::BeginPlay()
{
    Super::BeginPlay();
    bPrototypeTest = FParse::Param(FCommandLine::Get(), TEXT("PrototypeTest"));
    bPrototypeCapture = FParse::Param(FCommandLine::Get(), TEXT("PrototypeCapture"));
    SetActorTickEnabled(bPrototypeTest || bPrototypeCapture);
}

void AFactoryGameMode::CheckPrototype(bool bPassed, const TCHAR* Name)
{
    UE_LOG(LogTemp, Display, TEXT("PROTOTYPE_TEST %s: %s"), bPassed ? TEXT("PASS") : TEXT("FAIL"), Name);
    bTestFailed |= !bPassed;
}

void AFactoryGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    StageTime += DeltaSeconds;
    if (bPrototypeCapture)
    {
        if (StageTime > 3.f && TestStage == 0)
        {
            FScreenshotRequest::RequestScreenshot(TEXT("PrototypePreview.png"),true,false);
            TestStage=1;
        }
        if (StageTime > 5.f) FPlatformMisc::RequestExitWithStatus(false,0);
        return;
    }
    if (!bPrototypeTest) return;
    auto* Player = Cast<AFactoryCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
    if (!Player)
    {
        if (StageTime > 5.f) { CheckPrototype(false,TEXT("player spawned")); FPlatformMisc::RequestExitWithStatus(false,1); }
        return;
    }
    switch (TestStage)
    {
    case 0:
        if (StageTime > 1.f)
        {
            CheckPrototype(Player->GetCharacterMovement()->IsMovingOnGround(), TEXT("spawn lands on floor"));
            TestStart = Player->GetActorLocation();
            ++TestStage; StageTime=0;
        }
        break;
    case 1:
        Player->MoveHorizontal(1.f);
        if (StageTime > .3f)
        {
            CheckPrototype(Player->GetActorLocation().X > TestStart.X+50, TEXT("right input moves player"));
            CheckPrototype(FMath::Abs(Player->GetActorLocation().Y-TestStart.Y)<.1f,TEXT("movement stays in side plane"));
            Player->RestartPrototype(); ++TestStage; StageTime=0;
        }
        break;
    case 2:
        if (StageTime > .5f)
        {
            CheckPrototype(FMath::Abs(Player->GetActorLocation().X-TestStart.X)<1,TEXT("restart restores spawn"));
            Player->Jump(); HighestJump=TestStart.Z; ++TestStage; StageTime=0;
        }
        break;
    case 3:
        HighestJump=FMath::Max(HighestJump,Player->GetActorLocation().Z);
        if (StageTime > .2f) Player->StopJumping();
        if (StageTime > 1.5f)
        {
            CheckPrototype(HighestJump > TestStart.Z+50,TEXT("jump gains height"));
            CheckPrototype(Player->GetCharacterMovement()->IsMovingOnGround(),TEXT("jump lands on floor"));
            CheckPrototype(FMath::Abs(Player->SideCamera->GetComponentLocation().X-Player->GetActorLocation().X)<1,TEXT("camera tracks horizontal position"));
            CheckPrototype(Player->SideCamera->GetForwardVector().Y<-.99f,TEXT("camera faces movement plane"));
            Player->SetActorLocation(FVector(0,0,-600)); ++TestStage; StageTime=0;
        }
        break;
    case 4:
        if (StageTime > .75f)
        {
            CheckPrototype(Player->GetActorLocation().Z>0 && FMath::Abs(Player->GetActorLocation().X-TestStart.X)<1,TEXT("fall below level resets player"));
            ++TestStage; StageTime=0;
        }
        break;
    case 5:
        Player->MoveHorizontal(-1.f);
        if (StageTime > .3f)
        {
            CheckPrototype(Player->GetActorLocation().X<TestStart.X-50,TEXT("left input moves player"));
            UE_LOG(LogTemp,Display,TEXT("PROTOTYPE_TEST_COMPLETE %s"),bTestFailed?TEXT("FAIL"):TEXT("PASS"));
            FPlatformMisc::RequestExitWithStatus(false,bTestFailed?1:0);
            SetActorTickEnabled(false);
        }
        break;
    }
}

