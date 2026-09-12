# GAM 305 - Blue Team

Team planning repository for GAM-305-10947-M01, August-October 2026.

Proposed common engine: Unreal Engine 5.7.4; remaining version checks are listed below.
No Unreal project has been added yet. Install Git LFS before cloning game assets.
Use feature branches and coordinate changes to shared maps and binary assets.
## Module Two Team Project Plan

**Status:** Module Two planning record, compiled September 12. Team input and remaining setup decisions are recorded below.
**Compiled by Kevin Thrush with team input documented below.**

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

| Member | Work area |
|---|---|
| Kevin Thrush | Coordination, repository integration, player movement and camera |
| Christian Gulley | Factory layout, low-poly background and props; role accepted |
| Abby Mckenzie | Pickups and UI, following her volunteered preference |
| Jason Elias | Hazards, accepted; moving hazards proposed as his specific portion |
| Adam Havens | Stationary hazards, explicitly accepted; initial design supplied |

Everyone helps playtest. The working communication plan is Blue Team Discord with short Wednesday and Saturday updates covering completed work, next tasks, and blockers. Report blocking issues promptly; arrange a voice call when needed rather than holding up work for attendance. Kevin maintains the task list. Each task has an owner, due date, completion check, and To Do / In Progress / Done status. Coordinate shared map edits and use feature branches for implementation.

### Brainstorming and named contributions

This log was compiled by Kevin Thrush on September 12 from the team's Discord discussion. It records planning contributions, not completed game implementation.

- **Kevin Thrush:** Proposed the abandoned-factory side-scroller, four extra feature categories, milestone schedule, communication/task tracking approach, low-poly style, and work split. Created the public repository, configured Unreal ignore/LFS rules, invited teammates, and compiled this README and submission link document.
- **Christian Gulley:** Supported the side-scroller concept, volunteered and accepted environment work in Blender, asked about low- versus mid-poly art, and confirmed Unreal 5.7.4. Suggested a boss whose behavior changes with collected powerups. The boss is retained as a stretch idea after required features; it is outside the baseline scope. Christian also provided positive feedback on Adam's hazard design.
- **Abby Mckenzie:** Supported the proposed game, volunteered pickups and UI based on previous coursework, shared availability, and confirmed Unreal 5.7.4.
- **Jason Elias:** Accepted the proposed hazards responsibility and reported Unreal 5.7.1. Kevin proposed moving hazards as his portion after Adam volunteered stationary hazards; that specific split can still be adjusted.
- **Adam Havens:** Offered hazards/pickup support, confirmed Unreal 5.7.4, accepted stationary hazards, and supplied a design for all four stationary hazard types on September 12.

### Stationary hazard design from Adam Havens

- Spikes: overlap detection and damage, with optional knockback. Keep the baseline spikes fixed; retracting spikes are optional.
- Electrical panel: repeated damage while the player overlaps; stop the timer on exit and use sparks/light to communicate the powered state.
- Steam vent: alternate safe and damaging bursts, with a warning before activation. Damage values and intervals will be tuned during testing.
- Slowing floor: reduce movement speed while overlapping and restore it after exit.

**Kevin Thrush — integration notes:** Use one shared player damage path so shields and health UI behave consistently. The slowing floor and speed pickup should combine through shared movement modifiers rather than restoring an outdated saved speed. Test exiting/re-entering each hazard and player death so damage timers cannot continue incorrectly.

### Current task status and next milestone

| Owner | Task | Due | Status and completion check |
|---|---|---|---|
| Kevin | Repository, team log, and submission document | Sept 13 | Repository and log prepared; document links to the public README |
| Adam | Outline four stationary hazards | Sept 13 | Done as a design draft in Discord; implementation remains To Do |
| Christian | Factory route sketch and reusable prop list | Sept 13 | To Do; not yet reported complete |
| Abby | Pickup and HUD outline | Sept 13 | To Do; not yet reported complete |
| Jason | First moving-hazard design | Sept 13 | To Do; not yet reported complete |
| Kevin and team | Shared project setup, movement/camera prototype, QA plan | Sept 20 | To Do; verify consistent engine patch, player movement, camera, and test checklist |

The first art/UI/hazard outlines are internal planning targets. The Module Two submission is the repository link and this collaborative planning record; no completed playable build is claimed this week.

### Repository access and setup

Repository: https://github.com/kptmail-game/GAM305-DigitalGameDev

The repository is public for instructor viewing. All four teammates have accepted collaborator access, verified September 12: ciaro88, AbbyMckenzie, JasonEliasSNHU, and Aj8644.

Unreal 5.7.4 is the proposed common patch, based on Christian, Abby, and Adam's installed versions. Jason last reported 5.7.1 and has been asked whether updating is possible; Kevin's exact patch remains to be verified. Confirm the common patch before sharing the Unreal project. This setup item remains open and does not change the planned feature scope.

Start with a blank project and custom player/camera functionality to follow the rubric; seek clarification if the starter-template recommendation is needed. No Unreal project or game assets have been added yet.

### Submission

Each member submits a Word document containing the repository URL by September 13. The shared document is available in submissions/Module_Two_Project_Log.docx. Named contributions are recorded above for individual credit. Team members should flag corrections to their contributions or the working plan in Discord.
