// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BLCombatUtilities.h"
#include "BLActionsWidget.generated.h"

class UButton;
class UBorder;
class UWidgetSwitcher;
class UBLActionWidget;
class UBLAttackActionWidget;
class UBLDefendActionWidget;
class UBLCrystalActionWidget;

DECLARE_DELEGATE_FiveParams(FOnChosenAction, ECombatActionType /*ActionType*/, int32 /*ActionIndex*/, ECrystalColor /*CrystalColor*/, float /*ActionMECost*/, int32 /*TargetsNum*/);

/**
 * 
 */
UCLASS()
class BLADEOFLEGEND_API UBLActionsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetActionsData(const FCombatCharData& BaseData, const TArray<TSoftClassPtr<UBLAction>>& InAttackActions, const TArray<TSoftClassPtr<UBLAction>>& InDefendActions, const TMap<ECrystalColor, FCrystalSkills>& InCrystalActions, const TArray<TSoftClassPtr<UBLAction>>& InSpecialActions);

	/** Returns widget to default state */
	void ResetWidget();

private:
	void BindButtons();
	void BindActions();

	UFUNCTION()
	void OnBTAttackClicked();
	UFUNCTION()
	void OnBTDefendClicked();
	UFUNCTION()
	void OnBTCrystalClicked();
	UFUNCTION()
	void OnBTSpecialSkillClicked();
	UFUNCTION()
	void OnBTItemClicked();
	UFUNCTION()
	void OnBTRunClicked();

	/** Returns clicked button to normal color */
	void ResetButton();
	/** Returns clicked action to default state */
	void ResetAction();
	
	/** Calls delegate with chosen action and index */
	void ChosenAction(ECombatActionType Action, int32 ActionIndex, ECrystalColor CrystalColor = ECrystalColor::NONE, float ActionMECost = 0.f, int32 TargetsNum = 1);

public:
	FOnChosenAction OnChosenAction;

protected:
	/** Action type buttons */
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UButton> BTAttack;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UButton> BTDefend;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UButton> BTCrystal;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UButton> BTSpecial;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UButton> BTItem;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UButton> BTRun;

	/** Switcher for different type of actions  */
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> ActionTypeSwitcher;

	/** Actions to display*/
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UBorder> NoneAction;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UBLActionWidget> AttackAction;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UBLActionWidget> DefendAction;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UBLActionWidget> CrystalAction;
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UBLActionWidget> SpecialAction;
	//TODO: Other actions

private:
	UPROPERTY()
	TObjectPtr<UButton> ClickedButton;
	UPROPERTY()
	TObjectPtr<UBLActionWidget> ClickedAction;
};
