// Shoot Them Up Game, All Rights Reserved


#include "UI/STUGameHUD.h"
#include <Engine/Canvas.h>

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);
	const float HalfLinerSize = 10.0f;
	const float LineThickness = 2.0f;
	FLinearColor LinearColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLinerSize, Center.Max, Center.Min + HalfLinerSize, Center.Max, LinearColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLinerSize, Center.Min, Center.Max + HalfLinerSize, LinearColor, LineThickness);
}
