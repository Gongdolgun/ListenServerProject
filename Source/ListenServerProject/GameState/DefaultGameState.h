#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Misc/Structures.h"
#include "Misc/Enums.h"
#include "DefaultGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameStateTypeChanged, EGameStateType, InPrevGameType, EGameStateType, InNewGameType);

UCLASS()
class LISTENSERVERPROJECT_API ADefaultGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADefaultGameState();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetTimer(float InTime);
	virtual void SetScore() {};

	

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FGameStateTypeChanged OnGameStateTypeChanged;

public:
	// Time
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Game State")
	float GameStartTime = 5.0f;

	UPROPERTY(EditAnywhere, Replicated, Category = "Game State")
	float GamePlayTime = 30.0f;

	UPROPERTY(EditAnywhere, Replicated, Category = "Game State")
	float GameOverTime = 5.0f;

	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<FPlayerInGameData> PlayerDatas;

	UPROPERTY(BlueprintReadWrite)
	bool IsReady = false;

protected:
	// Game State
	UPROPERTY(Replicated, BlueprintReadOnly)
	EGameStateType GameStateType;

public:
	UFUNCTION(BlueprintCallable) 
	void SetGameState(EGameStateType InGameStateType);

	UFUNCTION(BlueprintCallable)
	EGameStateType GetGameStateType();

	UFUNCTION(BlueprintCallable)
	FPlayerInGameData GetPlayerData(FString PlayerName);

private:
	void ChangeGameType(EGameStateType InGameType);
	void CalRank();

public:
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerScore(const FString& PlayerName, int32 Score);

	void AddPlayerData(const FString& PlayerName, int32 Score, FColor PlayerColor);
};