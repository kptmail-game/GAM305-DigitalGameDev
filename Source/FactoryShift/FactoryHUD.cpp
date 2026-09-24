#include "FactoryHUD.h"
#include "Engine/Canvas.h"
#include "FactoryCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "FactoryElement.h"
#include "EngineUtils.h"
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
        DrawRect(FLinearColor(.08f,.12f,.15f,1),26,128*Scale,180*Scale,7*Scale);
        DrawRect(FLinearColor(.2f,.85f,.65f,1),26,128*Scale,180*Scale*Player->Health/100.f,7*Scale);
        AFactoryElement* Nearest=nullptr; float Distance=MAX_flt; int32 CellActors=0;
        for(TActorIterator<AFactoryElement> It(GetWorld());It;++It)
        {
            if(It->Kind==EFactoryElementKind::Cell) ++CellActors;
            const bool Target=Player->PowerCells<4 ? It->Kind==EFactoryElementKind::Cell && !It->bCollected : It->Kind==EFactoryElementKind::Exit;
            const float D=FMath::Abs(It->GetActorLocation().X-Player->GetActorLocation().X);
            if(Target && D<Distance) { Nearest=*It; Distance=D; }
        }
        const FString Hint=CellActors!=4 ? TEXT("Gameplay assets missing: close editor, rebuild project, then reopen original map.") : Nearest ? FString::Printf(TEXT("%s  %s  %.0fm"),Player->PowerCells<4?TEXT("POWER CELL"):TEXT("EXIT"),Nearest->GetActorLocation().X>Player->GetActorLocation().X?TEXT(">>"):TEXT("<<"),Distance/100.f) : TEXT("");
        DrawRect(FLinearColor(.015f,.025f,.045f,.94f),16,Canvas->SizeY-52,Canvas->SizeX-32,36);
        DrawText(Hint,FLinearColor(1,.85f,.35f),28,Canvas->SizeY-44,nullptr,1.15f*Scale);
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
