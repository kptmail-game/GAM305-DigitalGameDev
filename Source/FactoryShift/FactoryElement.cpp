#include "FactoryElement.h"
#include "FactoryCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"

AFactoryElement::AFactoryElement()
{
    PrimaryActorTick.bCanEverTick=true;
    Trigger=CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger")); RootComponent=Trigger;
    Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    Trigger->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
    Trigger->SetGenerateOverlapEvents(true);
    Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); Mesh->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    Mesh->SetStaticMesh(Cube.Object); Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Label=CreateDefaultSubobject<UTextRenderComponent>(TEXT("Label")); Label->SetupAttachment(RootComponent);
    Label->SetHorizontalAlignment(EHTA_Center); Label->SetWorldSize(28);
    Label->SetRelativeRotation(FRotator(0,90,0));
}
void AFactoryElement::BeginPlay() { Super::BeginPlay(); Start=GetActorLocation(); }
void AFactoryElement::Configure(EFactoryElementKind Type, FVector Size)
{
    Kind=Type; Start=GetActorLocation(); Trigger->SetBoxExtent(Size*.5f); Mesh->SetRelativeScale3D(Size/100.f);
    static const TCHAR* Names[]={TEXT("POWER CELL"),TEXT("REPAIR +35"),TEXT("SHIELD 8s"),TEXT("SPEED 8s"),TEXT("SPIKES"),TEXT("LIVE PANEL"),TEXT("STEAM"),TEXT("SLOW FLOOR"),TEXT("PRESS"),TEXT("SWING ARM"),TEXT("MOVING FIELD"),TEXT("EXIT: 4 CELLS")};
    Label->SetText(FText::FromString(Names[static_cast<int32>(Kind)]));
    Label->SetRelativeLocation(FVector(0,100,Size.Z*.5f+50));
    if (Kind==EFactoryElementKind::Cell)
    {
        Mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cylinder.Cylinder")));
        Mesh->SetRelativeScale3D(FVector(.65f,.65f,1.15f));
        Label->SetText(FText::FromString(TEXT("POWER CELL\nJUMP TO COLLECT")));
        Label->SetTextRenderColor(FColor(255,220,80));
    }
    const TCHAR* Mat=Kind==EFactoryElementKind::Cell ? TEXT("M_Cell") : Kind==EFactoryElementKind::Health || Kind==EFactoryElementKind::Exit ? TEXT("M_Green") : Kind==EFactoryElementKind::Shield ? TEXT("M_Blue") : Kind==EFactoryElementKind::Speed ? TEXT("M_Purple") : Kind==EFactoryElementKind::SlowFloor ? TEXT("M_Slow") : TEXT("M_Hazard");
    Mesh->SetMaterial(0,LoadObject<UMaterialInterface>(nullptr,*FString::Printf(TEXT("/Game/Alpha/%s.%s"),Mat,Mat)));
}
void AFactoryElement::ResetElement()
{
    bCollected=false; Elapsed=0; bActive=true; bLastActive=true;
    SetActorLocation(Start); Mesh->SetVisibility(true); Label->SetVisibility(true);
    Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    if (SlowedPlayer.IsValid()) SlowedPlayer->SetSlowingSource(this,false);
    SlowedPlayer.Reset();
}
void AFactoryElement::Interact(AFactoryCharacter* Player)
{
    if (!Player || Player->bWon || Player->bDead || bCollected) return;
    switch(Kind)
    {
    case EFactoryElementKind::Cell: Player->AddPowerCell(); break;
    case EFactoryElementKind::Health: if(Player->Health>=100) return; Player->AddHealth(35); break;
    case EFactoryElementKind::Shield: Player->GiveShield(); break;
    case EFactoryElementKind::Speed: Player->GiveSpeed(); break;
    case EFactoryElementKind::Exit: Player->TryExit(); return;
    case EFactoryElementKind::SlowFloor: Player->SetSlowingSource(this,true); SlowedPlayer=Player; return;
    default: if(bActive) Player->ApplyFactoryDamage(20); return;
    }
    bCollected=true; Mesh->SetVisibility(false); Label->SetVisibility(false);
    Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void AFactoryElement::Tick(float Dt)
{
    Super::Tick(Dt); if (bCollected) return;
    Elapsed+=Dt; const float Time=Elapsed+CycleOffset;
    if (Kind==EFactoryElementKind::Cell)
    {
        Mesh->SetRelativeLocation(FVector(0,0,8.f*FMath::Sin(Time*2.f)));
        Mesh->SetRelativeRotation(FRotator(0,Time*35.f,0));
    }
    if (Kind==EFactoryElementKind::Press) SetActorLocation(Start+FVector(0,0,180+180*FMath::Sin(Time*1.5f)));
    if (Kind==EFactoryElementKind::SwingArm) SetActorLocation(Start+FVector(150*FMath::Sin(Time*1.4f),0,90*(1-FMath::Cos(Time*1.4f))));
    if (Kind==EFactoryElementKind::MovingBarrier) SetActorLocation(Start+FVector(180*FMath::Sin(Time),0,0));
    if (Kind==EFactoryElementKind::Steam)
    {
        float Phase=FMath::Fmod(Time,5.f); bActive=Phase>=3.f;
        Label->SetText(FText::FromString(bActive ? TEXT("STEAM: HOT") : Phase>=2.f ? TEXT("STEAM: WARNING") : TEXT("STEAM: SAFE")));
        if (bActive!=bLastActive)
        {
            const TCHAR* Mat=bActive?TEXT("M_Hazard"):TEXT("M_Slow");
            Mesh->SetMaterial(0,LoadObject<UMaterialInterface>(nullptr,*FString::Printf(TEXT("/Game/Alpha/%s.%s"),Mat,Mat))); bLastActive=bActive;
        }
    }
    TArray<AActor*> Players; Trigger->GetOverlappingActors(Players,AFactoryCharacter::StaticClass());
    if(SlowedPlayer.IsValid() && !Players.Contains(SlowedPlayer.Get())) { SlowedPlayer->SetSlowingSource(this,false); SlowedPlayer.Reset(); }
    for(AActor* Actor:Players) Interact(Cast<AFactoryCharacter>(Actor));
}
