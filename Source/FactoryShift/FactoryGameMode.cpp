#include "FactoryGameMode.h"
#include "FactoryCharacter.h"
#include "FactoryHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "UnrealClient.h"
#include "FactoryElement.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"
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
    bAlphaTest = FParse::Param(FCommandLine::Get(), TEXT("AlphaTest"));
    SetActorTickEnabled(bPrototypeTest || bPrototypeCapture || bAlphaTest);
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
    if (!bPrototypeTest && !bAlphaTest) return;
    auto* Player = Cast<AFactoryCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
    if (!Player)
    {
        if (StageTime > 5.f) { CheckPrototype(false,TEXT("player spawned")); FPlatformMisc::RequestExitWithStatus(false,1); }
        return;
    }
    if(bAlphaTest) { if(StageTime>1.f) RunAlphaChecks(Player); return; }
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

void AFactoryGameMode::RunAlphaChecks(AFactoryCharacter* P)
{
    auto Check=[this](bool Pass,const TCHAR* Name) { UE_LOG(LogTemp,Display,TEXT("ALPHA_TEST %s: %s"),Pass?TEXT("PASS"):TEXT("FAIL"),Name); bTestFailed|=!Pass; };
    Check(P->bAlphaMode,TEXT("Alpha map activates gameplay state"));
    Check(P->Health==100 && P->PowerCells==0,TEXT("fresh health and cell count"));
    Check(!P->TryExit() && !P->bWon,TEXT("exit rejects missing cells"));
    P->ApplyFactoryDamage(20); Check(P->Health==80,TEXT("damage reduces health"));
    P->ApplyFactoryDamage(20); Check(P->Health==80,TEXT("damage cooldown prevents every-frame damage"));
    P->AddHealth(100); Check(P->Health==100,TEXT("repair capped at maximum"));
    P->RestartPrototype(); P->GiveShield(.1f); P->ApplyFactoryDamage(20);
    Check(P->Health==100,TEXT("shield blocks damage"));
    P->Tick(.2f); P->ApplyFactoryDamage(20); Check(P->Health==80,TEXT("normal damage resumes after shield expires"));
    P->RestartPrototype(); P->GiveSpeed(.5f); P->SetSlowingSource(this,true); P->Tick(.1f);
    Check(FMath::IsNearlyEqual(P->GetCharacterMovement()->MaxWalkSpeed,337.5f),TEXT("boost combines with slow floor"));
    P->SetSlowingSource(this,false); P->Tick(.1f);
    Check(P->GetCharacterMovement()->MaxWalkSpeed==750,TEXT("leaving slow floor preserves active boost"));
    P->Tick(.5f); Check(P->GetCharacterMovement()->MaxWalkSpeed==500,TEXT("boost expiry restores base speed"));
    TArray<AFactoryElement*> Cells; int32 Types[12]={0};
    for(TActorIterator<AFactoryElement> It(GetWorld());It;++It) { Types[(int32)It->Kind]++; if(It->Kind==EFactoryElementKind::Cell) Cells.Add(*It); }
    Check(Cells.Num()==4,TEXT("level contains exactly four power cells"));
    bool All=true; for(int32 N:Types) All&=N>0; Check(All,TEXT("all pickup hazard and exit categories placed"));
    if(Cells.Num()==4)
    {
        Cells[0]->Interact(P); Cells[0]->Interact(P); Check(P->PowerCells==1,TEXT("cell cannot be collected twice"));
        for(int32 I=1;I<4;++I) Cells[I]->Interact(P);
        Check(P->PowerCells==4 && P->TryExit() && P->bWon,TEXT("four cells unlock win condition"));
    }
    P->RestartPrototype(); bool Reset=true; for(auto* C:Cells) Reset&=!C->bCollected;
    Check(P->Health==100 && P->PowerCells==0 && !P->bWon && Reset,TEXT("restart restores player and collectibles"));
    P->ApplyFactoryDamage(100); Check(P->bDead && !P->TryExit(),TEXT("death prevents winning"));
    P->RestartPrototype(); Check(!P->bDead && P->ShieldRemaining==0 && P->SpeedRemaining==0,TEXT("restart clears death and effects"));
    UE_LOG(LogTemp,Display,TEXT("ALPHA_TEST_COMPLETE %s"),bTestFailed?TEXT("FAIL"):TEXT("PASS"));
    FPlatformMisc::RequestExitWithStatus(false,bTestFailed?1:0); SetActorTickEnabled(false);
}

