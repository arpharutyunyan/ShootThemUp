// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include <STUCoreTypes.h>
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTULevelItemWidget;
class USTUGameInstance;


UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
		UHorizontalBox* LevelItemBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> LevelItemWidgetClass;


	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
		TArray<USTULevelItemWidget*> LevelItemWidgets;

	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	USTUGameInstance* GetSTUGameInstance() const;
	
};
