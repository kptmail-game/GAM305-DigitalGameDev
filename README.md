# GAM 305 - Blue Team

Team planning repository for GAM-305-10947-M01, August-October 2026.

Proposed engine: Unreal Engine 5.7; exact patch and team agreement pending.
No Unreal project has been added yet. Install Git LFS before cloning game assets.
Use feature branches and coordinate changes to shared maps and binary assets.
## Module Two Team Project Plan

**Status:** Draft for Blue Team discussion, not yet approved by the team.
**Kevin Thrush — proposed plan:**

### Game and four additional elements

One 2.5D side-scrolling level in an abandoned factory. The player collects four power cells to unlock the exit. Target 5–10 minutes, with a clear spawn and goal, a consistent theme, and all visible surfaces textured.

1. Three pickups: health, temporary shield, temporary speed boost.
2. Exit collectibles: four power cells required to finish.
3. Four stationary hazards: spikes, electrical panel, steam vent, slowing floor.
4. Three moving hazards: sliding press, swinging arm, moving electrical barrier.

Build a simple introduction, two challenge sections, and an exit area. Reuse props and materials to keep the workload reasonable.

### Proposed schedule

| Week ending | Goal |
|---|---|
| Sept 13 | Agree on scope, roles, engine version, repo setup, and this plan. |
| Sept 20 | Movement/camera prototype and QA plan; test spawn, goal, hazards, and pickups. |
| Sept 27 — Alpha | Full route playable; all four feature categories represented; record missing variants and bugs. |
| Oct 4 — Beta | All required feature variants, textures, and UI implemented; playtest for 5–10 minutes; fix progression blockers. |
| Oct 11 — Final | Complete testing and fixes; verify clean checkout and instructor access; create final-release branch and submit. |

Later milestone dates follow the module schedule and remain subject to instructor updates. Keep weekly notes for the Week 7 postmortem.

### Roles and communication

Divide gameplay programming, level design, art, and UI/testing based on member preferences. One member also coordinates the repository and documentation. **Owners are pending team discussion.** Kevin has offered to organize decisions and the schedule.

Use Blue Team's Discord channel, one short weekly meeting at an agreed time, and midweek/pre-deadline progress updates. Report blockers promptly. Track tasks in To Do / In Progress / Done, with an owner, deadline, and completion check for each. Use feature branches and coordinate edits to shared Unreal maps/assets.

### Team input to record before submission

- Each member's suggestions and the final agreed game/features.
- Role owners, exact Unreal version, repository URL/host, and setup owner.
- Meeting day/time and agreement on the task-reporting method.
- Final decisions and actual contributions labeled with each member's name.

**Setup note:** The rubric says to start blank and build player/camera functionality; the announcement recommends a starter template. Plan for blank unless clarified.

**Submission:** Put the approved section in the team README. Kevin submits a Word document with the repository URL by September 13. Verify instructor access and the announcement's repository/wiki visibility requirements with the team.


### September 9 planning update — Kevin Thrush

Christian supports the side-scroller proposal and Unreal 5.7 and volunteered for 3D level/background work in Blender. Abby supports the concept and volunteered for pickups/UI. Jason provided his GitHub username. These are recorded preferences, not approval of every task below.

| Member | Proposed responsibility | First task — by Sept 13 |
|---|---|---|
| Kevin Thrush | Coordination, repository integration, player movement/camera | Maintain plan and task list; confirm project setup and exact engine patch before creating the shared project. |
| Christian Gulley | Environment art and level layout | Sketch the factory route and a small reusable prop list; coordinate scale with Kevin before importing Blender assets. |
| Abby Mckenzie | Pickups and UI | Outline health/shield/speed pickups, power-cell counter, and a simple HUD. |
| Jason Elias | Stationary and moving hazards (proposed; preference pending) | Pick a first hazard to prototype and note its damage/timing behavior. |
| Adam Havens | QA and progression testing (proposed; preference pending) | Confirm availability and outline checks for spawn, collectibles, exit, and restart. |

All first tasks are To Do until the owner reports completion. Everyone playtests; QA is shared, with Adam proposed to organize the checklist. Roles are open to swaps. Implementation starts after the shared project and engine patch are agreed. Christian's suggested boss remains a stretch goal after required features are complete; it is not part of the committed scope.

GitHub write-access invitations sent to ciaro88, AbbyMckenzie, and JasonEliasSNHU on September 9; acceptance pending. Adam's username is still needed. Repository: https://github.com/kptmail-game/GAM305-DigitalGameDev

For this week's planning, use asynchronous Discord updates so nobody is blocked by meeting availability. Please confirm/swap roles and share the exact installed 5.7 patch by Friday, September 11; aim to finalize the README Saturday, September 12, ahead of Sunday's submission. A recurring meeting time remains to be agreed. Updates should state completed work, next task, and any blocker.
