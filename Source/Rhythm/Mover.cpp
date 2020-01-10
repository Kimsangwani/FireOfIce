// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"
#include "LevelGenerator.h"
#include "Kismet/KismetMathLibrary.h"
#include "RhythmGameModeBase.h"
#include "RhythmPlayerController.h"

// Sets default values
AMover::AMover()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Fire = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fire"));
	Ice = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ice"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = Root;
	Fire->SetupAttachment(Fire);
	Ice->SetupAttachment(Ice);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-45.0f, -45.0f, 0.0f));
	SpringArm->bDoCollisionTest = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FIRE(TEXT("/Game/Resource/Actor/SM_Fire.SM_Fire"));
	if (SM_FIRE.Succeeded())
	{
		Fire->SetStaticMesh(SM_FIRE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ICE(TEXT("/Game/Resource/Actor/SM_Ice.SM_Ice"));
	if (SM_ICE.Succeeded())
	{
		Ice->SetStaticMesh(SM_ICE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CURVE(TEXT("/Game/Blueprint/MoveCurve.MoveCurve"));
	if (CURVE.Succeeded())
	{
		FloatCurve = CURVE.Object;
	}

	Fire->SetWorldScale3D(FVector(1.0f, 1.0f, 0.1f));
	Ice->SetWorldScale3D(FVector(1.0f, 1.0f, 0.1f));

	AngleAxis = 0.0f;
	MoverLocationZ = 0.0f;
	RotateDistance = 0.0f;
	Perfect = 20.0f;
	Good = 30.0f;
	StartingAngle = 90.0f;

	Radius = FVector(100.0f, 0.0f, 0.0f);
	RotationSpeed = 100.0f;
	bIsFirePlaying = false;
}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();
	
	if (FloatCurve != NULL)
	{
		MoveTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		MoveTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(MoveTimeline);
		MoveTimeline->SetNetAddressable();

		MoveTimeline->SetLooping(false);
		MoveTimeline->SetTimelineLength(5.0f);

		InterpFunction.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		TimelineFinished.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		MoveTimeline->AddInterpFloat(FloatCurve, InterpFunction);
		MoveTimeline->SetTimelineFinishedFunc(TimelineFinished);

		MoveTimeline->RegisterComponent();
	}
}

// Called every frame
void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate(DeltaTime);
}

// Called to bind functionality to input
void AMover::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMover::TouchStarted);
}

void AMover::Rotate(float DelataTime)
{
	int RotateDirection = bClockwise == true ? 1 : -1;
	CurrentRoatation = RotationSpeed * DelataTime + CurrentRoatation;

	if (bIsFirePlaying)
	{
		FVector IceLocation = Ice->GetSocketLocation("");
		FVector RotateValue = Radius.RotateAngleAxis(90.0f + CurrentRoatation, FVector(0.0f, 0.0f, 1.0f));
		IceLocation += RotateValue;
		Fire->SetWorldLocation(IceLocation);
	}
	else
	{
		FVector FireLocation = Fire->GetSocketLocation("");
		FVector RotateValue = Radius.RotateAngleAxis(-90.0f + CurrentRoatation, FVector(0.0f, 0.0f, 1.0f));
		FireLocation += RotateValue;
		Ice->SetWorldLocation(FireLocation);
	}
}

FVector AMover::GetMeshZSize()
{
	FVector BoxExtent = Fire->CalcBounds(Fire->GetComponentTransform()).BoxExtent;

	return BoxExtent;
}

void AMover::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	CHECK(nullptr != LevelGenarator);

	ARhythmGameModeBase* RhythmGameModeBase = Cast<ARhythmGameModeBase>(GetWorld()->GetAuthGameMode());
	CHECK(nullptr != RhythmGameModeBase);

	ARhythmPlayerController* RhythmPlayerController = Cast<ARhythmPlayerController>(GetWorld()->GetFirstPlayerController());
	CHECK(nullptr != RhythmPlayerController);

	InteractTileLocation = LevelGenarator->GetInteractTileLocation();
	PreviousTileLocation = LevelGenarator->GetPreviousTileLocation();
	if (bIsFirePlaying)
	{
		FVector IceLocation = Fire->GetSocketLocation("");
		float Distance = FMath::Sqrt(powf(InteractTileLocation.X - IceLocation.X, 2) + powf(InteractTileLocation.Y - IceLocation.Y, 2));
		if (Distance <= Good)
		{
			Fire->SetWorldLocation(FVector(InteractTileLocation.X, InteractTileLocation.Y, MoverLocationZ));
			PlayTimeline();
			LevelGenarator->IncreaseIndex();
			CurrentLocation = InteractTileLocation;
			bIsFirePlaying = false;
			RhythmGameModeBase->SetAccuracyText(Distance <= Perfect ? "Perfect" : "Good");
			RhythmPlayerController->ShowAccuracyText();
		}
		else
		{
			RhythmPlayerController->ShowResultUI();
		}
	}
	else
	{
		FVector IceLocation = Ice->GetSocketLocation("");
		float Distance = FMath::Sqrt(powf(InteractTileLocation.X - IceLocation.X, 2) + powf(InteractTileLocation.Y - IceLocation.Y, 2));
		if(Distance <= Good)
		{
			Ice->SetWorldLocation(FVector(InteractTileLocation.X, InteractTileLocation.Y, MoverLocationZ));
			PlayTimeline();
			LevelGenarator->IncreaseIndex();
			CurrentLocation = InteractTileLocation;
			bIsFirePlaying = true;
			RhythmGameModeBase->SetAccuracyText(Distance <= Perfect ? "Perfect" : "Good");
			RhythmPlayerController->ShowAccuracyText();
		}
		else
		{
			RhythmPlayerController->ShowResultUI();
		}
	}
}

void AMover::TimelineCallback(float Value)
{
	FVector Location = GetActorLocation();
	float LocationX = FMath::Lerp(Location.X, InteractTileLocation.X, Value);
	float LocationY = FMath::Lerp(Location.Y, InteractTileLocation.Y, Value);
	SetActorLocation(FVector(LocationX, LocationY, MoverLocationZ));

}

void AMover::TimelineFinishedCallback()
{
	
}

void AMover::PlayTimeline()
{
	if (MoveTimeline != NULL)
	{
		MoveTimeline->PlayFromStart();
	}
}

void AMover::InitLocation(FVector Location)
{
	MoverLocationZ = Location.Z + (GetMeshZSize().Z);
	SetActorLocation(Location);
	Fire->SetWorldLocation(FVector(Location.X, Location.Y, MoverLocationZ));
	Ice->SetWorldLocation(FVector(Location.X, Location.Y + (GetMeshZSize().Y * 2.0f), MoverLocationZ));
	CurrentLocation = FVector(Location.X, Location.Y, MoverLocationZ);
}

void AMover::SetLevelGenarator(ALevelGenerator * _LevelGenarator)
{
	LevelGenarator = _LevelGenarator;
}

FVector AMover::GetCurrentLocation() const
{
	return bIsFirePlaying == true ? Fire->GetSocketLocation("") : Ice->GetSocketLocation("");
}

void AMover::Swap(FVector PlaceLocation)
{
	
}
