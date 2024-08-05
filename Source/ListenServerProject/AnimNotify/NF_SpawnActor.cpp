#include "AnimNotify/NF_SpawnActor.h"
#include "Global.h"
#include "Characters/BombCharacter.h"

FString UNF_SpawnActor::GetNotifyName_Implementation() const
{
	return "SpawnActor";
}

void UNF_SpawnActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABombCharacter* character = Cast<ABombCharacter>(MeshComp->GetOwner()))
		{
			if (character->bBomb && character->Bomb && !character->bIsSpawningRestraint)
			{
				character->ServerSpawnRestraint();
			}

			else
			{
				character->ServerSpawnWall();
			}
		}
	}
}
