#include "DefaultGameState.h"
#include "Global.h"
#include "Net/UnrealNetwork.h"
#include "Algo/Sort.h"

ADefaultGameState::ADefaultGameState()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	GameStateType = EGameStateType::Ready;
}

void ADefaultGameState::BeginPlay()
{
	Super::BeginPlay();


}

void ADefaultGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsReady)
	{
		SetTimer(DeltaSeconds);
	}

}

void ADefaultGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, GameStartTime);
	DOREPLIFETIME(ThisClass, GamePlayTime);
	DOREPLIFETIME(ThisClass, GameOverTime);
	DOREPLIFETIME(ThisClass, RankBoardTime);

	DOREPLIFETIME(ThisClass, GameStateType);

	DOREPLIFETIME(ThisClass, PlayerDatas);
}

void ADefaultGameState::SetTimer(float InTime)
{
	switch (GameStateType)
	{
	case EGameStateType::Ready:
		SetGameState(EGameStateType::GameStart);
		break;

	case EGameStateType::GameStart:
		if (GameStartTime >= 0.0f)
		{
			GameStartTime -= InTime;
			if (GameStartTime <= 0.0f)
			{
				SetGameState(EGameStateType::GamePlay);
			}
		}

		break;

	case EGameStateType::GamePlay:
		if (GamePlayTime >= 0.0f)
		{
			GamePlayTime -= InTime;
			if (GamePlayTime <= 0.0f)
			{
				SetGameState(EGameStateType::GameOver);
			}
		}

		break;

	case EGameStateType::GameOver:
		if (GameOverTime >= 0.0f)
		{
			GameOverTime -= InTime;
			if (GameOverTime <= 0.0f)
			{
				SetGameState(EGameStateType::RankBoard);
			}
		}

		break;

	case EGameStateType::RankBoard:
		if (RankBoardTime >= 0.0f)
		{
			RankBoardTime -= InTime;
		}

		break;
	}
}

void ADefaultGameState::SetGameState(EGameStateType InGameStateType)
{
	if (GameStateType != InGameStateType)
	{
		switch (InGameStateType)
		{
		case EGameStateType::GameStart:
			ChangeGameType(EGameStateType::GameStart);
			break;

		case EGameStateType::GamePlay:
			ChangeGameType(EGameStateType::GamePlay);
			break;

		case EGameStateType::GameOver:
			CalRank();
			ChangeGameType(EGameStateType::GameOver);
			break;

		case EGameStateType::RankBoard:
			ChangeGameType(EGameStateType::RankBoard);
			break;
		}
		
	}
}

EGameStateType ADefaultGameState::GetGameStateType()
{
	return GameStateType;
}

void ADefaultGameState::ChangeGameType(EGameStateType InGameType)
{
	EGameStateType prevGameType = GameStateType;
	GameStateType = InGameType;

	if (OnGameStateTypeChanged.IsBound())
		OnGameStateTypeChanged.Broadcast(prevGameType, GameStateType);
}

void ADefaultGameState::CalRank()
{
	Algo::Sort(PlayerDatas, [](const FPlayerInGameData& A, const FPlayerInGameData& B)
	{
		return A.Score > B.Score;
	});
}

void ADefaultGameState::UpdatePlayerScore(const FString& PlayerName, int32 Score)
{
	for (FPlayerInGameData& PlayerData : PlayerDatas)
		if (PlayerData.PlayerName == PlayerName)
			PlayerData.Score += Score;
}

void ADefaultGameState::AddPlayerData(const FString& PlayerName, int32 Score, FColor PlayerColor)
{
	// 새 플레이어 추가
	PlayerDatas.Add(FPlayerInGameData(PlayerName, Score, PlayerColor));
}

void ADefaultGameState::SomeoneDeadEvent(FString InAttackerName, FString InHittedCharacterName)
{
	if (OnSomeoneDead.IsBound())
		OnSomeoneDead.Broadcast(InAttackerName, InHittedCharacterName);
}

FPlayerInGameData ADefaultGameState::GetPlayerData(FString PlayerName)
{
	for (FPlayerInGameData& PlayerData : PlayerDatas)
		if (PlayerData.PlayerName == PlayerName)
			return PlayerData;

	return FPlayerInGameData();
}