#include "FactoryHUD.h"
#include "Engine/Canvas.h"
void AFactoryHUD::DrawHUD()
{
    Super::DrawHUD();
    DrawRect(FLinearColor(0.02f,0.025f,0.04f,.85f),16,16,600,80);
    DrawText(TEXT("BLUE TEAM | MOVEMENT PROTOTYPE"), FLinearColor::White,30,26,nullptr,1.4f);
    DrawText(TEXT("A/D or arrows: move    Space: jump    R: restart"),FLinearColor::White,30,57,nullptr,1.1f);
}
