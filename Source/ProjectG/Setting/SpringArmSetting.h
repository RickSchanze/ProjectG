#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpringArmSetting.generated.h"

UCLASS(BlueprintType)
class PROJECTG_API USpringArmSetting : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpringLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator AbsoluteSpringArmRotation;
};
