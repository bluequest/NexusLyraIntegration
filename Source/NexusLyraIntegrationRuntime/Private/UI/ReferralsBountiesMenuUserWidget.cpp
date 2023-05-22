// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "UI/BountiesUserWidget.h"
#include "NexusLyraIntegrationRuntime/NexusSampleProjectCharacter.h"
#include "Components/Button.h"
#include "NexusSampleProjectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Runtime/ApplicationCore/Public/HAL/PlatformApplicationMisc.h"
#include "Components/EditableTextBox.h"
#include "CommonUIExtensions.h"
#include "NativeGameplayTags.h"

void UReferralsBountiesMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UReferralsBountiesMenuUserWidget::UpdatePlayerReferralCode()
{
	// #TODO Replace logic when Unreal SDK template is in.
	//OnGetReferralCodeCompleteDelegate.BindUObject(this, &UReferralsBountiesMenuUserWidget::OnGetPlayerReferralCodeComplete);
	//NexusSDK::GetPlayerReferralCode(32, 32, OnGetReferralCodeCompleteDelegate);

	// #TODO Replace logic below when NexusSDK::GetPlayerReferralCode is in
	FString TestString = TEXT("Testing!");
	OnGetPlayerReferralCodeComplete(TestString, true);
}

void UReferralsBountiesMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		BackButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnBackButtonPressed);
	}

	if (ensureMsgf(IsValid(SubmitButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		SubmitButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnSubmitButtonPressed);
	}

	if (ensureMsgf(IsValid(CopyCodeButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		CopyCodeButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnCopyButtonPressed);
	}

	if (ensureMsgf(IsValid(LinkAccountButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		LinkAccountButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnLinkAccountButtonPressed);
	}

	if (ensureMsgf(IsValid(ViewBoutniesButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		ViewBoutniesButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnViewBountiesButtonPressed);
	}

	// #TODO Generate auth code (https://api.nexus.gg/v1/referrals/player/{playerId}/authCode)

	// #TODO Query player's referral code (https://api.nexus.gg/v1/referrals/player/{playerId}/code)
	UpdatePlayerReferralCode();

	// #TODO If none exists, generate code for a user (https://api.nexus.gg/v1/referrals/code)

	// #TODO Query bounties (https://api.nexus.gg/v1/bounties/), then populate entries
}

void UReferralsBountiesMenuUserWidget::OnSubmitButtonPressed()
{
	if (ensureMsgf(IsValid(ReferralCodeInputTextBox), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		if (ReferralCodeInputTextBox->GetText().IsEmpty())
		{
			return;
		}

		// #TODO Replace logic when Unreal SDK template is in.
		//OnSubmitReferralCodeCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnSubmitReferralCodeComplete);
		//NexusSDK::SubmitReferralCode(FString GroupId, OnSubmitReferralCodeCompleteDelegate);

		// #TODO Replace logic below when NexusSDK::SubmitReferralCode is in
		FString TestGroupId = TEXT("TestGroupId");
		FString TestGroupName = TEXT("TestGroupName");
		OnSubmitReferralCodeComplete(TestGroupId, TestGroupName, true);
	
		ReferralCodeInputTextBox->SetText(FText());
	}
}

void UReferralsBountiesMenuUserWidget::OnCopyButtonPressed()
{
	if (ensureMsgf(IsValid(PlayerReferralCode), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		FPlatformApplicationMisc::ClipboardCopy(*PlayerReferralCode->GetText().ToString());
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Referral code copied!")));
	}
}

void UReferralsBountiesMenuUserWidget::OnLinkAccountButtonPressed()
{
	if (ensureMsgf(!EscapeMenuClass.IsNull(), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, LinkAccountWidgetClass);
	}
}

void UReferralsBountiesMenuUserWidget::OnViewBountiesButtonPressed()
{
	if(ensureMsgf(!EscapeMenuClass.IsNull(), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, BountiesWidgetClass);
	}
}

void UReferralsBountiesMenuUserWidget::OnGetPlayerReferralCodeComplete(FString& ReferralCode, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (ensureMsgf(IsValid(PlayerReferralCode), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
		{
			PlayerReferralCode->SetText(FText::FromString(ReferralCode));
		}

		// Logging
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Get player referral code succeeded! ReferralCode: %s"), *ReferralCode));
		}

		UE_LOG(LogTemp, Log, TEXT("Get player referral code succeeded! ReferralCode: %s"), *ReferralCode);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Get player referral code failed!"));
		}

		UE_LOG(LogTemp, Error, TEXT("Get player referral code failed!"));
	}
}

void UReferralsBountiesMenuUserWidget::OnSubmitReferralCodeComplete(FString& GroupId, FString& GroupName, /* FReferralStruct ReferralInfo, */ bool bWasSuccessful)
{
	if (bWasSuccessful && !GroupId.IsEmpty() && !GroupName.IsEmpty())
	{
		// Logging
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Submit creator (referral) code success! Response - GroupId: %s, GroupName: %s"), *GroupId, *GroupName));
		}

		UE_LOG(LogTemp, Log, TEXT("Submit referral code succeeded! Response - GroupId: %s, GroupName : %s"), *GroupId, *GroupName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Submit referral code failed!"));
	}
}
