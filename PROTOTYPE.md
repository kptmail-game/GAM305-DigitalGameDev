# Movement and camera prototype

Unreal Engine **5.7.4**. This is a small movement test map, not the finished factory level. Kevin Thrush prepared the custom player, camera, placeholder map, and runtime checks on September 14.

## Open and play

Open `FactoryShift.uproject` with Unreal 5.7.4, allow the C++ module to build if prompted, then press Play. The startup map is `Content/Maps/Prototype.umap`.

- A/D or left/right arrows: move.
- Space: jump.
- R: return to the spawn point.
- Falling below the map also returns the player to spawn.

The character moves along X and jumps along Z; Y is constrained. The camera looks along negative Y and follows horizontal movement at a fixed height. Walk across the steps and jump the two gaps. The cube is a temporary character visual.

## Build requirements

This project contains a small C++ module. Building from a clean clone requires Visual Studio with C++ game development tools and a Windows SDK, in addition to Unreal 5.7.4 and Git LFS. The local build passed with Visual Studio 2026/MSVC 14.51; Unreal reports that MSVC 14.44 is its preferred toolchain. Teammates should confirm they can build before adopting this branch. Generated binaries are not committed.

The `FactoryCharacter` class is Blueprintable; create a child Blueprint for additional gameplay and set it as the default pawn in a derived game mode. Movement and camera settings are exposed, and the prototype HUD can be replaced by Abby's UI. Hazards, pickups, health, power cells, and the final exit are not implemented here.

`Scripts/create_prototype_map.py` recreates the placeholder map through Unreal editor scripting. Do not run it over a map containing team edits. The committed map is ready to open without running the script.

## Verification

The editor target compiled successfully. Runtime checks passed in Unreal 5.7.4 with both headless and rendered execution:

- Spawn lands on the floor.
- Right and left movement advance the player.
- Movement stays in the side plane.
- Restart restores the spawn position.
- Jump gains height and lands back on the floor.
- Camera tracks horizontally and faces the movement plane.
- Falling below the level resets the player.

These are ten assertions. They exercise movement functions and physics; a human keyboard/controller playtest and a clean build on another machine remain to be done. This does not mark the whole course QA checklist as passed.

Run runtime checks using `UnrealEditor-Cmd.exe FactoryShift.uproject /Game/Maps/Prototype -game -nullrhi -nosound -unattended -PrototypeTest` with absolute paths to the executable and project. Find `PROTOTYPE_TEST_COMPLETE PASS` in the project log. A failing assertion exits with code 1.

