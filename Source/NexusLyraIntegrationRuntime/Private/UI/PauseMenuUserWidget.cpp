// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "CommonUIExtensions.h"
#include "NativeGameplayTags.h"

void UPauseMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		BackButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnBackButtonPressed);
	}

	if (ensureMsgf(IsValid(CreatorSupportButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		CreatorSupportButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnCreatorSupportButtonPressed);
	}

	if (ensureMsgf(IsValid(ReferralsBountiesButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		ReferralsBountiesButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnReferralsBountiesButtonPressed);
	}

	if (ensureMsgf(IsValid(ItemShopButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		ItemShopButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnItemShopButtonPressed);
	}
}

void UPauseMenuUserWidget::OnCreatorSupportButtonPressed()
{
	if (ensureMsgf(!CreatorSupportWidgetClass.IsNull(), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, CreatorSupportWidgetClass);
	}
}

void UPauseMenuUserWidget::OnReferralsBountiesButtonPressed()
{
	if (ensureMsgf(!ReferralsBountiesMenuWidgetClass.IsNull(), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, ReferralsBountiesMenuWidgetClass);
	}
}

void UPauseMenuUserWidget::OnItemShopButtonPressed()
{
	if (ensureMsgf(!ItemShopMenuWidgetClass.IsNull(), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, ItemShopMenuWidgetClass);
	}
}

void UPauseMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(CreatorSupportButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		GameAndUIMode.SetWidgetToFocus(CreatorSupportButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}