# Week 4 shared integration build

Development branch: `codex/week4-alpha`. Engine: Unreal 5.7.4.
This is a compact systems test map, not the finished Alpha release.

## Get and open the build

1. Save your current work before switching branches. Fetch the repository and check out `codex/week4-alpha`; pull its latest revision and run `git lfs pull`.
2. This is a C++ Unreal project. Use Visual Studio with the Unreal/C++ development tools, generate project files if needed, and build FactoryShiftEditor (Development Editor / Win64). Do not commit generated Binaries, Intermediate, or Saved folders.
3. Open FactoryShift.uproject and `/Game/Maps/AlphaIntegration` in the Content Browser, then Play. The existing Prototype map remains available separately.
4. A/D or arrows move, Space jumps, and R restarts. Collect four yellow cells, then reach the green exit. The player is a placeholder for the maintenance robot escaping the abandoned factory.

## Connecting teammate features

Use FactoryCharacter as the shared player. The Blueprint-callable methods are:

- `ApplyFactoryDamage(amount)` for hazards; respects shield, death/win state, and a 0.8-second damage cooldown.
- `AddPowerCell()` for a pickup that has its own one-time collection guard.
- `AddHealth(amount)`, `GiveShield(duration)`, and `GiveSpeed(duration)` for pickups. Current defaults: health 100 maximum, repair +35, shield/speed 8 seconds, speed boost 1.5x.
- `TryExit()` for the exit; requires four cells.

The shared character exposes Health, PowerCells, ShieldRemaining, SpeedRemaining, bWon, bDead, and StatusMessage for HUD bindings. Kevin can connect the slowing-floor method in C++ as needed; slowing multiplies speed by 0.45 and combines with an active boost.

The FactoryElement actors in this map are Kevin's provisional integration stand-ins. Keep them until replacement assets are connected and tested, then remove duplicate actors. Do not add a second independent health/cell system. Abby's separate project has not been merged. Coordinate shared map edits with Kevin; binary maps cannot be merged like text. Send a feature branch or the required Content files with dependencies, your engine version, a short feature list, and steps/results.

## Test and report

Play through normally before reporting Pass. Check real contact and leaving each object, not just whether an actor exists. Try dying and restarting after collecting cells and while effects are active. Record your name, branch commit, map, engine version, steps, expected/actual result, and any screenshot. Use the README QA01–QA14 checklist and GitHub Issues for reproducible problems.

September 21 local verification: build passed; 18 Alpha state assertions passed; 10 original movement/physics assertions passed; the rendered HUD was readable at 1280 x 720. Automated Alpha tests directly exercise functions/state; they do not replace trigger-overlap or complete-route playtests. Full hazard timing, route pacing, other-machine performance, and clean-checkout checks remain pending.

For reproducibility, launch UnrealEditor-Cmd with the project path and `/Game/Maps/AlphaIntegration -game -nullrhi -nosound -unattended -AlphaTest`. Original regression uses `/Game/Maps/Prototype` with `-PrototypeTest` instead. Logs contain ALPHA_TEST or PROTOTYPE_TEST pass/fail lines.

## Before the final Alpha handoff

Integrate incoming work, test all required variants, finish and time the route, verify the goal and reset, and compile named team reflections. Friday evening is the requested file handoff; Saturday is integration/retesting. The final release branch will be created only after the release checks. Git branch names cannot contain spaces, so `Final-Alpha` can represent the rubric's “Final Alpha” label in the submission notes.

## September 24 release and missing-actor troubleshooting

The default map now opens AlphaIntegration. The Final-Alpha branch is the Alpha snapshot; codex/week4-alpha remains the development branch. A Windows ZIP is published with the GitHub Alpha release so testers do not need Visual Studio or Unreal Editor. Extract the entire ZIP before launching FactoryShift.exe. Keep the Engine and FactoryShift folders beside it.

If the editor shows only floor/wall/CellStep objects, close Unreal and rebuild FactoryShiftEditor (Development Editor / Win64) after fetching the latest branch and Git LFS files. Reopen the original map from the repository. Do not save a map with missing-class warnings over the shared version. Preserve any local edits before restoring a source file. The cells are actors named PowerCell1 through PowerCell4; CellStep is just their platform. Christian's missing-actor cause is not yet confirmed, so report any load/compile error rather than assuming it is the same problem.

New checks: -AlphaRouteTest drives the player using movement/jump input logic through actual cell and exit overlaps, without teleporting or awarding items. It verifies four cells, win while alive, and reset. This is an automated route check, not a human pacing or fairness test. The short route still needs expansion toward 5–10 minutes for Beta.
