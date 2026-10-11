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
        const float W=Canvas->SizeX;
        const FLinearColor Panel(.008f,.018f,.026f,.94f), Teal(.25f,.85f,.79f), Amber(1.f,.7f,.22f);
        DrawRect(Panel,18,18,290*Scale,100*Scale);
        DrawRect(Teal,18,18,3,100*Scale);
        DrawText(TEXT("FACTORY SHIFT"),FLinearColor::White,32,27,nullptr,1.5f*Scale);
        DrawText(TEXT("MAINTENANCE UNIT 07"),Teal,32,53*Scale,nullptr,.9f*Scale);
        DrawText(FString::Printf(TEXT("INTEGRITY  %.0f%%"),Player->Health),FLinearColor::White,32,77*Scale,nullptr,.95f*Scale);
        DrawRect(FLinearColor(.05f,.12f,.15f),32,101*Scale,252*Scale,6*Scale);
        DrawRect(Player->Health<=40 ? FLinearColor(1,.3f,.2f) : Teal,32,101*Scale,252*Scale*Player->Health/100.f,6*Scale);
        const float Right=W-280*Scale-18;
        DrawRect(Panel,Right,18,280*Scale,100*Scale);
        DrawText(TEXT("EMERGENCY POWER"),Amber,Right+16,29,nullptr,1.f*Scale);
        for(int32 I=0;I<4;++I)
        {
            DrawRect(FLinearColor(.08f,.16f,.19f),Right+16+I*60*Scale,55*Scale,48*Scale,20*Scale);
            if(I<Player->PowerCells) DrawRect(Amber,Right+19+I*60*Scale,58*Scale,42*Scale,14*Scale);
        }
        DrawText(FString::Printf(TEXT("%d / 4 CELLS    %02d:%02d"),Player->PowerCells,int32(Player->RunTime)/60,int32(Player->RunTime)%60),FLinearColor::White,Right+16,87*Scale,nullptr,.95f*Scale);
        if(Player->ShieldRemaining>0 || Player->SpeedRemaining>0)
            DrawText(FString::Printf(TEXT("SHIELD %.1fs   /   BOOST %.1fs"),Player->ShieldRemaining,Player->SpeedRemaining),Teal,32,130*Scale,nullptr,1.f*Scale);
        AFactoryElement* Nearest=nullptr; float Distance=MAX_flt; int32 CellActors=0;
        for(TActorIterator<AFactoryElement> It(GetWorld());It;++It)
        {
            if(It->Kind==EFactoryElementKind::Cell) ++CellActors;
            const bool Target=Player->PowerCells<4 ? It->Kind==EFactoryElementKind::Cell && !It->bCollected : It->Kind==EFactoryElementKind::Exit;
            const float D=FMath::Abs(It->GetActorLocation().X-Player->GetActorLocation().X);
            if(Target && D<Distance) { Nearest=*It; Distance=D; }
        }
        const FString Hint=CellActors!=4 ? TEXT("Gameplay assets missing: close editor, rebuild project, then reopen original map.") : Nearest ? FString::Printf(TEXT("%s  %s  %.0fm"),Player->PowerCells<4?TEXT("POWER CELL"):TEXT("EXIT"),Nearest->GetActorLocation().X>Player->GetActorLocation().X?TEXT(">>"):TEXT("<<"),Distance/100.f) : TEXT("");
        DrawRect(Panel,18,Canvas->SizeY-90,W-36,72);
        DrawRect(Amber,18,Canvas->SizeY-90,3,72);
        DrawText(Hint,Amber,32,Canvas->SizeY-80,nullptr,1.05f*Scale);
        DrawText(TEXT("A/D  MOVE     SPACE  JUMP     R  RESTART"),FLinearColor(.65f,.75f,.79f),32,Canvas->SizeY-48,nullptr,.85f*Scale);
        if(Player->RunTime<8.f)
            DrawText(TEXT("Restore emergency power. Get Unit 07 out of the abandoned factory."),FLinearColor::White,32,Canvas->SizeY-119,nullptr,.95f*Scale);
        if (Player->bWon || Player->bDead)
        {
            const float X=W*.25f, Y=Canvas->SizeY*.36f;
            DrawRect(Panel,X,Y,W*.5f,180*Scale);
            DrawRect(Player->bWon?Teal:FLinearColor(1,.3f,.2f),X,Y,W*.5f,4);
            DrawText(Player->bWon?TEXT("SHIFT COMPLETE"):TEXT("UNIT OFFLINE"),FLinearColor::White,X+28,Y+25,nullptr,2.f*Scale);
            DrawText(Player->bWon?TEXT("Emergency power restored. Unit 07 escaped."):TEXT("Factory hazards stopped this run."),Teal,X+28,Y+70*Scale,nullptr,1.f*Scale);
            DrawText(FString::Printf(TEXT("CELLS %d/4   |   TIME %02d:%02d   |   INTEGRITY %.0f%%"),Player->PowerCells,int32(Player->RunTime)/60,int32(Player->RunTime)%60,Player->Health),FLinearColor::White,X+28,Y+104*Scale,nullptr,.95f*Scale);
            DrawText(TEXT("R  /  START A NEW SHIFT"),Amber,X+28,Y+144*Scale,nullptr,1.1f*Scale);
        }
        return;
    }
    DrawRect(FLinearColor(0.02f,0.025f,0.04f,.85f),16,16,600,80);
    DrawText(TEXT("BLUE TEAM | MOVEMENT PROTOTYPE"), FLinearColor::White,30,26,nullptr,1.4f);
    DrawText(TEXT("A/D or arrows: move    Space: jump    R: restart"),FLinearColor::White,30,57,nullptr,1.1f);
}
