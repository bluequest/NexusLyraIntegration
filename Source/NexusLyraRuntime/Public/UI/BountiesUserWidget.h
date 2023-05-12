// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "BountiesUserWidget.generated.h"

class UButton;

/**
 * Widget used to display a list of player's referral bounties
 */
UCLASS()
class NEXUSLYRARUNTIME_API UBountiesUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:
	void SetupInitialFocus(APlayerController* Controller) override;

protected:

	void NativeConstruct() override;

	/** UButton for returning to game */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

private:

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Bounties Menu Buttons")
	void OnBackButtonPressed();
	
};
