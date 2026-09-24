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
    bAlphaRouteTest = FParse::Param(FCommandLine::Get(), TEXT("AlphaRouteTest"));
    SetActorTickEnabled(bPrototypeTest || bPrototypeCapture || bAlphaTest || bAlphaRouteTest);
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
        if(StageTime>1.f && TestStage==0)
        {
            float CaptureX=0.f;
            if(FParse::Value(FCommandLine::Get(),TEXT("CaptureX="),CaptureX))
                if(auto* P=UGameplayStatics::GetPlayerCharacter(this,0)) P->SetActorLocation(FVector(CaptureX,0,100));
        }
        if (StageTime > 3.f && TestStage == 0)
        {
            FScreenshotRequest::RequestScreenshot(TEXT("PrototypePreview.png"),true,false);
            TestStage=1;
        }
        if (StageTime > 5.f) FPlatformMisc::RequestExitWithStatus(false,0);
        return;
    }
    if (!bPrototypeTest && !bAlphaTest && !bAlphaRouteTest) return;
    auto* Player = Cast<AFactoryCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
    if (!Player)
    {
        if (StageTime > 5.f) { CheckPrototype(false,TEXT("player spawned")); FPlatformMisc::RequestExitWithStatus(false,1); }
        return;
    }
    if(bAlphaRouteTest) { if(StageTime>1.f) RunAlphaRoute(Player,DeltaSeconds); return; }
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

void AFactoryGameMode::RunAlphaRoute(AFactoryCharacter* P, float Dt)
{
    RouteTime+=Dt;
    if(P->bWon || P->bDead || RouteTime>90.f)
    {
        const bool Pass=P->bWon && P->PowerCells==4 && !P->bDead;
        UE_LOG(LogTemp,Display,TEXT("ALPHA_ROUTE %s: normal movement and overlap, cells=%d health=%.0f time=%.1f x=%.0f"),Pass?TEXT("PASS"):TEXT("FAIL"),P->PowerCells,P->Health,RouteTime,P->GetActorLocation().X);
        P->RestartPrototype();
        bool Reset=P->PowerCells==0 && P->Health==100 && !P->bWon && !P->bDead;
        for(TActorIterator<AFactoryElement> It(GetWorld());It;++It) Reset &= !It->bCollected;
        UE_LOG(LogTemp,Display,TEXT("ALPHA_ROUTE_RESTART %s"),Reset?TEXT("PASS"):TEXT("FAIL"));
        FPlatformMisc::RequestExitWithStatus(false,Pass&&Reset?0:1); SetActorTickEnabled(false); return;
    }
    AFactoryElement* Target=nullptr; float SmallestX=MAX_flt;
    for(TActorIterator<AFactoryElement> It(GetWorld());It;++It)
    {
        bool Desired=P->PowerCells<4 ? It->Kind==EFactoryElementKind::Cell && !It->bCollected : It->Kind==EFactoryElementKind::Exit;
        if(Desired && It->GetActorLocation().X<SmallestX) { Target=*It; SmallestX=It->GetActorLocation().X; }
    }
    if(!Target) return;
    float Dx=Target->GetActorLocation().X-P->GetActorLocation().X;
    P->MoveHorizontal(FMath::Abs(Dx)>20.f?FMath::Sign(Dx):0.f);
    if(FMath::Abs(Dx)<280.f && P->GetCharacterMovement()->IsMovingOnGround()) P->Jump();
    else P->StopJumping();
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

