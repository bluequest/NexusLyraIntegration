// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NexusLyraIntegrationRuntime/Public/NexusSampleProjectGlobals.h"
#include "CommonActivatableWidget.h"
#include "NexusSampleProjectBaseWidget.generated.h"

/**
 *  Widget base class to derive from for this sample project
 */
UCLASS()
class NEXUSLYRAINTEGRATIONRUNTIME_API UNexusSampleProjectBaseWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	/**
	 * Used to setup initial focus and input mode
	 *
	 * @param Controller the APlayerController instance to set focus
	 */
	virtual void SetupInitialFocus(APlayerController* Controller);

	UPROPERTY(EditDefaultsOnly)
		TSoftClassPtr<UCommonActivatableWidget> EscapeMenuClass;

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Menu Buttons")
		void OnBackButtonPressed();

protected:

	void NativeConstruct() override;
	
};
