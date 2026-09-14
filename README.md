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

## Module Three Project Log - Team Development: QA and Testing Plan

**Kevin Thrush — proposed QA plan, September 14, 2026.** Team review is pending. This records planned testing; no tests are claimed as completed.

### Communication and collaboration

Use Blue Team Discord for questions and Wednesday/Saturday updates. Keep the shared plan in this README, with each person's additions credited by name. Members can suggest edits in Discord or a GitHub pull request; Kevin will compile them and flag unresolved decisions. Use GitHub Issues for bugs so reports remain searchable and linked to fixes. Blocking problems should be reported immediately.

### Testing process and schedule

Test each object in a small test area first, then test it in the level with other systems, and finally play the whole game from launch to completion. The author checks their feature before integration; another member checks it afterward. Record the tester, date, engine version, commit/build, test IDs, and pass/fail results. Mark unavailable features Not Run rather than passing them.

| Stage and target | Test procedure and completion check |
|---|---|
| Play Test — preproduction/prototype, Sept 14–20 | Check movement, jumping, camera, collision, and the proposed route with simple placeholder objects. Try normal actions and edge cases such as jumping at platform edges. Record problems with controls and readability before adding detail. Unbuilt features remain Not Run. |
| Demo — before the Alpha presentation, Sept 21–27 | Run object checks, then complete the demo route from a fresh start. Check that each required feature category is represented and the objective is understandable. Fix crashes and progression blockers before presenting; list unfinished variants and remaining defects. No marketing demo is scheduled, so use the Alpha presentation as our demo checkpoint. |
| Beta regression — Sept 28–Oct 4 | Run the full checklist with all feature variants and textures. Have a teammate unfamiliar with a section play it without guidance, time the full run, and check interactions between pickups and hazards. Retest fixes and neighboring systems. |
| Code Release — Oct 5–11, before final submission | Test the release candidate against the complete checklist from a clean checkout on another teammate's machine using the agreed engine version. Check required assets, launch, restart, and a complete run. Compare results with the demo and Beta bugs. Release only after required tests pass and crashes/progression blockers are resolved; document any remaining minor defects. |

Wednesday updates identify failures and owners. Saturday reviews prioritize fixes and update the log. Repeat affected tests after every relevant change, even between these checkpoints.

### Pass and fail checklist

Record Pass or Fail for each executed check and attach an issue number for failures. Use Not Run until a check can actually be performed. For rows with several variants, record a separate result for every variant.

| ID | Item and pass condition | Initial result |
|---|---|---|
| QA01 | Clean checkout opens in the agreed Unreal version without missing project assets or compile errors. | Not Run |
| QA02 | Player spawns on safe ground, moves left/right, jumps and lands reliably, and stays in the intended movement plane. | Not Run |
| QA03 | Camera follows the player and keeps upcoming platforms/hazards visible without exposing areas outside the level. | Not Run |
| QA04 | Platforms, walls, and props have appropriate collision; the route has no unintended gaps or places where the player becomes stuck. | Not Run |
| QA05 | Each of four power cells can be collected once; the count stays accurate. The exit rejects fewer than four and completes the level with all four. | Not Run |
| QA06 | Health pickup increases health without exceeding its maximum and cannot be collected repeatedly after removal. | Not Run |
| QA07 | Shield pickup prevents the intended damage for its agreed duration and expires correctly; normal damage resumes afterward. | Not Run |
| QA08 | Speed pickup applies the agreed boost and expires correctly. Entering/leaving slowing floors during the boost cannot leave speed permanently changed. | Not Run |
| QA09 | Spikes damage only on valid contact. Electrical panels damage only while in range. Steam warns before harmful bursts and is safe between bursts. Slowing floors restore the correct speed on exit. Test each separately. | Not Run |
| QA10 | Sliding press, swinging arm, and moving electrical barrier follow their intended paths/cycles and damage only on valid contact. Test each separately. | Not Run |
| QA11 | Health, shield state, power-cell count, and completion feedback match actual gameplay state; text remains readable. | Not Run |
| QA12 | Leaving a hazard, dying, or restarting clears damage timers and temporary effects. Restart restores the agreed initial health, collectibles, and level state. | Not Run |
| QA13 | Full level has a clear spawn and goal, consistent factory theme, textured visible surfaces, all required variants, and a roughly 5–10 minute first completion. Record actual time. | Not Run |
| QA14 | Complete runs on team machines have no crashes or sustained stalls that prevent play; record hardware, settings, and observed performance issues. | Not Run |

Proposed coverage follows work areas: Kevin checks movement/camera and progression; Christian checks layout/art/collision; Abby checks pickups/UI; Adam checks stationary hazards; Jason checks moving hazards if he confirms that split. Everyone performs a full playthrough and checks at least one feature they did not create.

### Updating the plan

When a design or implementation change is proposed, its owner identifies the affected test IDs. Update expected behavior, add edge cases, and note the date, author, reason, and related issue/commit in the README or pull request. Kevin checks that the design notes and checklist agree before integrating the change. Keep old test results tied to their original builds, and rerun affected tests plus a brief launch-to-exit check on the new build. Set exact pickup durations and damage values in the design notes before judging those values as pass/fail.

### Reporting and tracking bugs

Create one GitHub Issue per reproducible bug. Include a short title, reporter/date, engine and build/commit, affected test ID, map/object, numbered reproduction steps, expected result, actual result, and frequency. Add a screenshot or video when useful. If a bug is intermittent, include the last actions taken and how many attempts reproduced it.

Prioritize blockers (crash or cannot finish), major problems (required feature broken), then minor visual/audio issues. Assign an owner and follow Open → In Progress → Ready to Retest → Closed using an issue checklist or comments. Link the fixing commit/pull request to the issue. A second tester repeats the original steps and related checks, recording the result and build. Close only after verification; reopen the same issue if the defect returns. GitHub issue comments and commit history preserve changes over time. Review open bugs Wednesday and Saturday.

### Named contributions

- **Kevin Thrush:** Drafted the testing process, milestone schedule, pass/fail checklist, plan-update procedure, and bug reporting/tracking workflow on September 14.
- Team additions and reviews will be credited as received. Adam's previously shared stationary-hazard outline informed the proposed hazard checks; it is not recorded as a new Week 3 contribution or a completed test.

