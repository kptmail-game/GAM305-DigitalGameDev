#include "FactoryHUD.h"
#include "Engine/Canvas.h"
#include "FactoryCharacter.h"
#include "Kismet/GameplayStatics.h"
void AFactoryHUD::DrawHUD()
{
    Super::DrawHUD();
    auto* Player=Cast<AFactoryCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
    if (Player && Player->bAlphaMode)
    {
        const float Scale=FMath::Clamp(Canvas->SizeX/1280.f,.65f,1.2f);
        DrawRect(FLinearColor(.015f,.025f,.045f,.94f),12,12,Canvas->SizeX-24,116*Scale);
        DrawText(TEXT("FACTORY SHIFT | BLUE TEAM"),FLinearColor::White,26,22,nullptr,1.35f*Scale);
        DrawText(FString::Printf(TEXT("Health: %.0f    Cells: %d/4    Shield: %.1fs    Speed: %.1fs    Time: %.0fs"),Player->Health,Player->PowerCells,Player->ShieldRemaining,Player->SpeedRemaining,Player->RunTime),FLinearColor(.5f,.9f,1),26,48*Scale,nullptr,1.15f*Scale);
        DrawText(TEXT("A/D or arrows: move    Space: jump    R: restart    Yellow cells power the green exit"),FLinearColor::White,26,73*Scale,nullptr,1.f*Scale);
        DrawText(Player->StatusMessage,FLinearColor(1,.85f,.4f),26,96*Scale,nullptr,1.f*Scale);
        if (Player->bWon || Player->bDead)
        {
            DrawRect(FLinearColor(.015f,.02f,.03f,.94f),Canvas->SizeX*.2f,Canvas->SizeY*.42f,Canvas->SizeX*.6f,100*Scale);
            DrawText(Player->bWon?TEXT("YOU ESCAPED!"):TEXT("ROBOT OFFLINE"),Player->bWon?FLinearColor::Green:FLinearColor::Red,Canvas->SizeX*.25f,Canvas->SizeY*.44f,nullptr,2.f*Scale);
            DrawText(TEXT("Press R to restart"),FLinearColor::White,Canvas->SizeX*.25f,Canvas->SizeY*.44f+40*Scale,nullptr,1.25f*Scale);
        }
        return;
    }
    DrawRect(FLinearColor(0.02f,0.025f,0.04f,.85f),16,16,600,80);
    DrawText(TEXT("BLUE TEAM | MOVEMENT PROTOTYPE"), FLinearColor::White,30,26,nullptr,1.4f);
    DrawText(TEXT("A/D or arrows: move    Space: jump    R: restart"),FLinearColor::White,30,57,nullptr,1.1f);
}
