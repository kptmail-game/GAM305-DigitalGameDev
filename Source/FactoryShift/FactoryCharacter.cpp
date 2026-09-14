#include "FactoryCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"

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
}

void AFactoryCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Independent camera height prevents abrupt vertical jumps while traversing platforms.
    SideCamera->SetWorldLocation(FVector(GetActorLocation().X, SpawnLocation.Y+CameraDistance, SpawnLocation.Z+CameraHeight));
    SideCamera->SetWorldRotation(FRotator(0,-90,0));
    if (GetActorLocation().Z < -500.f) RestartPrototype();
}

void AFactoryCharacter::MoveHorizontal(float Value)
{
    AddMovementInput(FVector::ForwardVector, Value);
}

void AFactoryCharacter::RestartPrototype()
{
    StopJumping();
    GetCharacterMovement()->StopMovementImmediately();
    SetActorLocation(SpawnLocation, false, nullptr, ETeleportType::TeleportPhysics);
    GetCharacterMovement()->SetMovementMode(MOVE_Falling);
}

void AFactoryCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis("MoveHorizontal", this, &AFactoryCharacter::MoveHorizontal);
    Input->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    Input->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    Input->BindAction("Restart", IE_Pressed, this, &AFactoryCharacter::RestartPrototype);
}

