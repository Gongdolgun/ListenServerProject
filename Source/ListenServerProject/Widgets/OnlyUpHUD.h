#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OnlyUpHUD.generated.h"

UCLASS()
class LISTENSERVERPROJECT_API AOnlyUpHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<class UUserWidget> CharacterOverlayClass;

	class UCharacterOverlay* CharacterOverlay;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void AddCharacterOverlay();

private:


};
