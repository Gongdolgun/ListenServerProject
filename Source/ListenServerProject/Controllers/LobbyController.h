#pragma once

#include "CoreMinimal.h"
#include "Characters/DefaultCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Structures.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LobbyController.generated.h"

UCLASS()
class LISTENSERVERPROJECT_API ALobbyController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ChangeCharacter(FColor MaterialColor, int32 ColorNum);

	UFUNCTION(BlueprintNativeEvent)
	void UpdatePlayerList(const TArray<FPlayerBaseInfo>& PlayerBaseInfos);
	void UpdatePlayerList_Implementation(const TArray<FPlayerBaseInfo>& PlayerBaseInfos);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetReadyStatus();

	// Camera
	UFUNCTION(BlueprintCallable)
	void SetViewCamera();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void LeaveSession_Server();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LobbyCamera_Class;

	UPROPERTY(Replicated)
	AActor* LobbyCamera;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FPlayerBaseInfo PlayerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPlayerBaseInfo> PlayerInfos;

	TArray<UMaterialInterface*> MyMaterials;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lobby Montage")
	TArray<UAnimMontage*> Ready_Montages;

private:
	UFUNCTION(Client, Reliable)
	void LeaveToMainMenu();
};