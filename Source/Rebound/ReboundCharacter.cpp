// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ReboundCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ReboundPlayerController.h"

//////////////////////////////////////////////////////////////////////////
// AReboundCharacter

AReboundCharacter::AReboundCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create and assign camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera)
	{
		Camera->SetupAttachment(GetCapsuleComponent());
		Camera->SetWorldLocationAndRotation(FVector(-2500.0f, 0.0f, 1000.0f), FRotator(340.0f, 0.0f, 0.0f));
	}

	// Create character skeletal mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FCharacterMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (FCharacterMesh.Object)
		GetMesh()->SetSkeletalMesh(FCharacterMesh.Object);
	static ConstructorHelpers::FObjectFinder<UClass> FCharacterAnim(TEXT("UClass'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
	if (FCharacterAnim.Object)
		GetMesh()->SetAnimInstanceClass(FCharacterAnim.Object);

	if (GetMesh())
	{
		FRotator RelativeMeshRotation = FRotator(0.0f, 270.0f, 0.0f);
		FVector RelativeMeshLocation = FVector(0.0f, 0.0f, -97.0f);
		FVector RelativeMeshScale = FVector(1.0f, 1.0f, 1.0f);
		FTransform RelativeMeshTransform = FTransform(RelativeMeshRotation, RelativeMeshLocation, RelativeMeshScale);
		GetMesh()->SetRelativeTransform(RelativeMeshTransform);
	}

	// Create particle system explosion
	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	if (ExplosionParticle)
	{
		static ConstructorHelpers::FObjectFinder<UParticleSystem> FExplosion(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
		if (FExplosion.Object)
			ExplosionParticle->SetTemplate(FExplosion.Object);
		ExplosionParticle->SetupAttachment(GetCapsuleComponent());
		ExplosionParticle->bAutoActivate = false;
	}

	// Create audio cues
	ExplosionSound = CreateDefaultSubobject<USoundWave>(TEXT("ExplosionSound"));
	if (ExplosionSound)
	{
		static ConstructorHelpers::FObjectFinder<USoundWave> FExplosionSound(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion01.Explosion01'"));
		if (FExplosionSound.Object)
			ExplosionSound = FExplosionSound.Object;
	}
	ScreamSound = CreateDefaultSubobject<USoundWave>(TEXT("ScreamSound"));
	if (ScreamSound)
	{
		static ConstructorHelpers::FObjectFinder<USoundWave> FScreamSound(TEXT("SoundWave'/Game/Audio/Scream.Scream'"));
		if (FScreamSound.Object)
			ScreamSound = FScreamSound.Object;
	}

	// Create player name widget blueprint
	static ConstructorHelpers::FClassFinder<UPlayerNameWidget> FBP_PlayerNameWidget(TEXT("WidgetBlueprint'/Game/UMG/BP_PlayerNameWidget.BP_PlayerNameWidget_C'"));
	if (FBP_PlayerNameWidget.Class)
		BP_PlayerNameWidget = FBP_PlayerNameWidget.Class;

	// Create player name widget component
	PlayerNameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerNameComponent"));
	if (PlayerNameWidgetComponent) {
		PlayerNameWidgetComponent->SetWidgetClass(BP_PlayerNameWidget);
		PlayerNameWidgetComponent->SetupAttachment(GetMesh());
		FRotator RelativeRotation = FRotator(0.0f, 90.0f, 0.0f);
		FVector RelativeLocation = FVector(0.0f, 0.0f, 250.0f);
		FVector RelativeScale = FVector(2.0f, 2.0f, 2.0f);
		FTransform RelativeTransform = FTransform(RelativeRotation, RelativeLocation, RelativeScale);
		PlayerNameWidgetComponent->SetRelativeTransform(RelativeTransform);
	}

	static ConstructorHelpers::FClassFinder<UEndWidget> FBP_EndWidget(TEXT("WidgetBlueprint'/Game/UMG/BP_EndWidget.BP_EndWidget_C'"));
	if (FBP_EndWidget.Class)
		BP_EndWidget = FBP_EndWidget.Class;


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AReboundCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setup Camera
	FDetachmentTransformRules DetachmentTransformRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, true);
	if (Camera) {
		Camera->DetachFromComponent(DetachmentTransformRules);
		Camera->SetWorldLocationAndRotation(FVector(-2500.0f, 0.0f, 1000.0f), FRotator(340.0f, 0.0f, 0.0f));
	}
}

void AReboundCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform PlayerNameWidgetTransform = PlayerNameWidgetComponent->GetComponentTransform();
	FVector PlayerNameWidgetLocation = PlayerNameWidgetTransform.GetLocation();

	FVector CameraLocation = Camera->GetComponentLocation();
	FRotator BetweenRotation = UKismetMathLibrary::FindLookAtRotation(PlayerNameWidgetLocation, CameraLocation);
	PlayerNameWidgetComponent->SetWorldRotation(BetweenRotation);

	FVector PlayerLocation = GetActorLocation();
	if (PlayerLocation.Z < -1000.f) {
		ExplodeCharacter();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input	

void AReboundCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AReboundCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AReboundCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AReboundCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AReboundCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AReboundCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AReboundCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AReboundCharacter::OnResetVR);
}

void AReboundCharacter::ExplodeCharacter()
{
	// create explosion particle
	UParticleSystemComponent* Explosion = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle->Template, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), true);
	if (Explosion) {
		Explosion->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
		Explosion->CustomTimeDilation = 0.25f;
	}

	// play audio
	if (ExplosionSound && ScreamSound) {
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Cast<USoundBase>(ExplosionSound), GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), true);
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Cast<USoundBase>(ScreamSound), GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), true);
	}
	
	AReboundPlayerController* PlayerController = Cast<AReboundPlayerController>(GetController());
	if (BP_EndWidget)
	{
		if (!EndWidget)
		{
			EndWidget = CreateWidget<UEndWidget>(PlayerController, BP_EndWidget);
			if (EndWidget)
				EndWidget->AddToViewport();
		}
	}
	Destroy();
}

void AReboundCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AReboundCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AReboundCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AReboundCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AReboundCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AReboundCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AReboundCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
