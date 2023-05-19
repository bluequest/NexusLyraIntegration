// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BountiesUserWidget.h"
#include "NexusLyraIntegrationRuntime/NexusSampleProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NexusSampleProjectHUD.h"
#include "Components/Button.h"

void UBountiesUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UBountiesUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		BackButton->OnClicked.AddDynamic(this, &UBountiesUserWidget::OnBackButtonPressed);
	}
}

void UBountiesUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		RemoveFromParent();
		HUD->BountiesWidget = nullptr;
	}
}
