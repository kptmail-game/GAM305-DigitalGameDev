#include "FactoryCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "FactoryElement.h"
#include "EngineUtils.h"

AFactoryCharacter::AFactoryCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    GetCapsuleComponent()->InitCapsuleSize(30.f, 70.f);
    bUseControllerRotationYaw = false;
    auto* Movement = GetCharacterMovement();
    Movement->MaxWalkSpeed = 500.f;
    Movement->JumpZVelocity = 650.f;
    Movement->GravityScale = 1.8f;
    Movement->AirControl = .65f;
    Movement->BrakingDecelerationWalking = 2400.f;
    Movement->bOrientRotationToMovement = false;
    Movement->SetPlaneConstraintNormal(FVector(0, 1, 0));
    Movement->SetPlaneConstraintEnabled(true);
    Movement->bSnapToPlaneAtStart = true;
    PlaceholderBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderBody"));
    PlaceholderBody->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    PlaceholderBody->SetStaticMesh(Cube.Object);
    PlaceholderBody->SetRelativeScale3D(FVector(.5f,.5f,1.3f));
    PlaceholderBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SideCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideCamera"));
    SideCamera->SetupAttachment(RootComponent);
    SideCamera->SetRelativeLocation(FVector(0,1300,180));
    SideCamera->SetRelativeRotation(FRotator(0,-90,0));
    SideCamera->FieldOfView = 60.f;
}

void AFactoryCharacter::BeginPlay()
{
    Super::BeginPlay();
    SpawnLocation = GetActorLocation();
    if (auto* Material = LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Prototype/M_Player.M_Player")))
        PlaceholderBody->SetMaterial(0,Material);
    GetCharacterMovement()->SetPlaneConstraintOrigin(SpawnLocation);
    bAlphaMode = GetWorld()->GetMapName().Contains(TEXT("Alpha"));
    if (bAlphaMode)
    {
        PlaceholderBody->SetRelativeScale3D(FVector(.55f,.45f,.65f));
        struct FPart { const TCHAR* Name; FVector Location; FVector Scale; const TCHAR* Material; };
        const FPart Parts[]={
            {TEXT("RobotHead"),FVector(0,0,46),FVector(.48f,.46f,.3f),TEXT("/Game/Prototype/M_Player.M_Player")},
            {TEXT("RobotVisor"),FVector(0,25,48),FVector(.34f,.06f,.12f),TEXT("/Game/Alpha/M_Light.M_Light")},
            {TEXT("LeftFoot"),FVector(-17,0,-50),FVector(.2f,.5f,.35f),TEXT("/Game/Alpha/M_Trim.M_Trim")},
            {TEXT("RightFoot"),FVector(17,0,-50),FVector(.2f,.5f,.35f),TEXT("/Game/Alpha/M_Trim.M_Trim")},
            {TEXT("LeftArm"),FVector(-38,0,0),FVector(.15f,.3f,.5f),TEXT("/Game/Alpha/M_Pipe.M_Pipe")},
            {TEXT("RightArm"),FVector(38,0,0),FVector(.15f,.3f,.5f),TEXT("/Game/Alpha/M_Pipe.M_Pipe")}};
        for (const FPart& Part:Parts)
        {
            auto* PartMesh=NewObject<UStaticMeshComponent>(this,Part.Name);
            PartMesh->SetupAttachment(RootComponent); PartMesh->SetStaticMesh(PlaceholderBody->GetStaticMesh());
            PartMesh->SetRelativeLocation(Part.Location); PartMesh->SetRelativeScale3D(Part.Scale);
            PartMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            PartMesh->SetMaterial(0,LoadObject<UMaterialInterface>(nullptr,Part.Material)); PartMesh->RegisterComponent();
        }
    }
    StatusMessage = TEXT("Factory closed. Find four power cells to power the emergency exit.");
}

void AFactoryCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Independent camera height prevents abrupt vertical jumps while traversing platforms.
    SideCamera->SetWorldLocation(FVector(GetActorLocation().X, SpawnLocation.Y+CameraDistance, SpawnLocation.Z+CameraHeight));
    SideCamera->SetWorldRotation(FRotator(0,-90,0));
    if (bAlphaMode)
    {
        if (!bWon && !bDead) RunTime += DeltaSeconds;
        ShieldRemaining = FMath::Max(0.f, ShieldRemaining-DeltaSeconds);
        SpeedRemaining = FMath::Max(0.f, SpeedRemaining-DeltaSeconds);
        DamageCooldown = FMath::Max(0.f, DamageCooldown-DeltaSeconds);
        for (auto It=SlowingSources.CreateIterator(); It; ++It) if (!It->IsValid()) It.RemoveCurrent();
        GetCharacterMovement()->MaxWalkSpeed = 500.f * (SpeedRemaining>0 ? 1.5f : 1.f) * (SlowingSources.Num()>0 ? .45f : 1.f);
        if (GetActorLocation().Z < -500.f && !bWon && !bDead)
        {
            Health=0; bDead=true; StatusMessage=TEXT("Robot offline. Press R to restart.");
            GetCharacterMovement()->DisableMovement();
        }
    }
    else if (GetActorLocation().Z < -500.f) RestartPrototype();
}

void AFactoryCharacter::MoveHorizontal(float Value)
{
    if (!bWon && !bDead) AddMovementInput(FVector::ForwardVector, Value);
}

void AFactoryCharacter::RestartPrototype()
{
    StopJumping();
    GetCharacterMovement()->StopMovementImmediately();
    SetActorLocation(SpawnLocation, false, nullptr, ETeleportType::TeleportPhysics);
    GetCharacterMovement()->SetMovementMode(MOVE_Falling);
    if (bAlphaMode)
    {
        Health=100; PowerCells=0; bWon=false; bDead=false;
        ShieldRemaining=0; SpeedRemaining=0; DamageCooldown=0; RunTime=0;
        SlowingSources.Empty(); GetCharacterMovement()->MaxWalkSpeed=500;
        StatusMessage=TEXT("Factory closed. Find four power cells to power the emergency exit.");
        for (TActorIterator<AFactoryElement> It(GetWorld()); It; ++It) It->ResetElement();
    }
}

void AFactoryCharacter::ApplyFactoryDamage(float Amount)
{
    if (bWon || bDead || Amount<=0 || ShieldRemaining>0 || DamageCooldown>0) return;
    Health=FMath::Clamp(Health-Amount,0.f,100.f); DamageCooldown=.8f;
    if (Health<=0) { bDead=true; StatusMessage=TEXT("Robot offline. Press R to restart."); GetCharacterMovement()->DisableMovement(); }
}
void AFactoryCharacter::AddPowerCell()
{
    if (bWon || bDead) return;
    PowerCells=FMath::Min(4,PowerCells+1);
    StatusMessage=PowerCells==4 ? TEXT("All cells collected. Reach the green emergency exit!") : TEXT("Power cell collected.");
}
void AFactoryCharacter::AddHealth(float Amount) { if (!bDead && !bWon) Health=FMath::Clamp(Health+FMath::Max(0.f,Amount),0.f,100.f); }
void AFactoryCharacter::GiveShield(float Duration) { if (!bDead && !bWon) ShieldRemaining=FMath::Max(ShieldRemaining,Duration); }
void AFactoryCharacter::GiveSpeed(float Duration) { if (!bDead && !bWon) SpeedRemaining=FMath::Max(SpeedRemaining,Duration); }
void AFactoryCharacter::SetSlowingSource(AActor* Source, bool bInside) { if (bInside) SlowingSources.Add(Source); else SlowingSources.Remove(Source); }
bool AFactoryCharacter::TryExit()
{
    if (bDead) return false;
    if (PowerCells<4) { StatusMessage=FString::Printf(TEXT("Exit needs four cells. You have %d."),PowerCells); return false; }
    bWon=true; StatusMessage=TEXT("Emergency exit powered. You escaped! Press R to play again.");
    GetCharacterMovement()->StopMovementImmediately(); GetCharacterMovement()->DisableMovement();
    return true;
}

void AFactoryCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis("MoveHorizontal", this, &AFactoryCharacter::MoveHorizontal);
    Input->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    Input->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    Input->BindAction("Restart", IE_Pressed, this, &AFactoryCharacter::RestartPrototype);
}
