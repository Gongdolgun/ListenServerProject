#include "Actors/OnlyUp/SpinObject.h"
#include "Components/StaticMeshComponent.h"
#include "Global.h"
#include "GameState/DefaultGameState.h"
#include "Net/UnrealNetwork.h"

ASpinObject::ASpinObject()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	Helpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	Helpers::CreateComponent<UStaticMeshComponent>(this, &StaticMesh1, "StaticMesh1", Root);
	Helpers::CreateComponent<UStaticMeshComponent>(this, &StaticMesh2, "StaticMesh2", Root);
	Helpers::CreateComponent<UStaticMeshComponent>(this, &StaticMesh3, "StaticMesh3", Root);

}

void ASpinObject::BeginPlay()
{
	Super::BeginPlay();

	ADefaultGameState* gameState = Cast<ADefaultGameState>(UGameplayStatics::GetGameState(this));
	if (gameState)
	{
		gameState->OnGameStateTypeChanged.AddDynamic(this, &ASpinObject::OnGamePlayStart);
	}
}

void ASpinObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, RotationDelta);
	DOREPLIFETIME(ThisClass, bCheck);
}

void ASpinObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCheck == true)
	{
		if (HasAuthority())
		{
			AddRotation_NMC(DeltaTime);
		}
		else
		{
			AddRotation_Server(DeltaTime);
		}
	}
}

void ASpinObject::AddRotation_NMC_Implementation(float InDeltaTime)
{
	RotationDelta = RotationSpeed * InDeltaTime;
	AddActorLocalRotation(RotationDelta);
}

void ASpinObject::AddRotation_Server_Implementation(float InDeltaTime)
{
	AddRotation_NMC(InDeltaTime);
}

void ASpinObject::AddRotation(float InDeltaTime)
{
	AddRotation_Server(InDeltaTime);
}

void ASpinObject::OnGamePlayStart(EGameStateType InPrevGameType, EGameStateType InNewGameType)
{
	if (InNewGameType == EGameStateType::GameStart)
	{
		bCheck = true;
	}
}

