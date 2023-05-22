// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NexusSampleProjectBaseWidget.h"
#include "CommonUIExtensions.h"
#include "NativeGameplayTags.h"


UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layer.Menu");

void UNexusSampleProjectBaseWidget::SetupInitialFocus(APlayerController* Controller)
{
}

void UNexusSampleProjectBaseWidget::OnBackButtonPressed()
{
	if (ensure(!EscapeMenuClass.IsNull()))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, EscapeMenuClass);
	}
}

void UNexusSampleProjectBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetupInitialFocus(GetOwningPlayer());
}
