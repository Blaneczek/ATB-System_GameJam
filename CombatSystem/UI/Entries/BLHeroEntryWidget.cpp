// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "BLHeroEntryWidget.h"
#include "BLHeroEntryData.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "UI/BLCooldownBarWidget.h"


void UBLHeroEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UBLHeroEntryData* Item = Cast<UBLHeroEntryData>(ListItemObject);
	if (Item)
	{
		SetData(Item->Index, Item->Name, Item->HP, Item->ME);
	}
}

void UBLHeroEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CooldownBar->OnCooldownEnded.BindLambda([this](){ bCanDoAction = true; });
}

void UBLHeroEntryWidget::SetData(int32 InIndex, const FText& InName, float InHP, float InME)
{
	Index = InIndex;
	Name->SetText(InName);
	FFormatNamedArguments Args;
	Args.Add(TEXT("HP"), InHP);
	Args.Add(TEXT("ME"), InME);
	HP->SetText(FText::Format(FText::FromString("HP: {HP}/{HP}"), Args));
	ME->SetText(FText::Format(FText::FromString("ME: {ME}/{ME}"), Args));
}

void UBLHeroEntryWidget::GreyOutHero()
{
	bDied = true;
	Border->SetBrushColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.f));
	ResetCooldownBar();
}

void UBLHeroEntryWidget::HighlightHero()
{
	Border->SetBrushColor(FLinearColor(0.f, 0.35f, 0.5f, 1.f));
}

void UBLHeroEntryWidget::UnlightHero()
{
	Border->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
}

void UBLHeroEntryWidget::UpdateHP(float MaxHP, float CurrentHP)
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("MaxHP"), MaxHP);
	Args.Add(TEXT("CurrentHP"), CurrentHP);
	HP->SetText(FText::Format(FText::FromString("HP: {CurrentHP}/{MaxHP}"), Args));
}

void UBLHeroEntryWidget::UpdateME(float MaxME, float CurrentME)
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("MaxME"), MaxME);
	Args.Add(TEXT("CurrentME"), CurrentME);
	ME->SetText(FText::Format(FText::FromString("ME: {CurrentME}/{MaxME}"), Args));
}

void UBLHeroEntryWidget::StartCooldownBar(float Cooldown)
{
	bCanDoAction = false;
	CooldownBar->StartCooldown(Cooldown);
}

void UBLHeroEntryWidget::PauseCooldownBar()
{
	CooldownBar->PauseCooldown();
}

void UBLHeroEntryWidget::UnPauseCooldownBar()
{
	CooldownBar->UnPauseCooldown();
}

void UBLHeroEntryWidget::ResetCooldownBar()
{
	bCanDoAction = false;
	CooldownBar->ResetCooldown();
}
