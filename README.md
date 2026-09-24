# GAM 305 - Blue Team

Team planning repository for GAM-305-10947-M01, August-October 2026.

**Latest log:** [Module Four Alpha and team reflection](#module-four-project-log---team-reflection), September 24. The Module Two and Three sections below preserve their submitted history.

Proposed common engine: Unreal Engine 5.7.4; remaining version checks are listed below.
The Unreal project is available on the development branches linked below. Install Git LFS before cloning game assets.
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

**Compiled by Kevin Thrush, September 19, 2026, from the QA draft and Blue Team contributions.** The plan below separates completed prototype checks, teammate-reported results, and tests still to be run. This is the Week 3 submission record; game integration continues toward Alpha.

### Communication and collaboration

Use Blue Team Discord for questions and Wednesday/Saturday updates. Keep the shared plan in this README, with each person's additions credited by name. Members can suggest edits in Discord or a GitHub pull request; Kevin will compile them and flag unresolved decisions. Use GitHub Issues for bugs so reports remain searchable and linked to fixes. Blocking problems should be reported immediately.

### Testing process and schedule

Test each object in a small test area first, then test it in the level with other systems, and finally play the whole game from launch to completion. The author checks their feature before integration; another member checks it afterward. Record the tester, date, engine version, commit/build, test IDs, and pass/fail results. Mark unavailable features Not Run rather than passing them.

| Stage and target | Test procedure and completion check |
|---|---|
| Play Test — preproduction/prototype, Sept 14–20 | Check movement, jumping, camera, collision, and the proposed route with simple placeholder objects. Try normal actions and edge cases such as jumping at platform edges. Record problems with controls and readability before adding detail. Unbuilt features remain Not Run. |
| Demo — before the Alpha presentation, Sept 21–27 | Run object checks, then complete the demo route from a fresh start. Following Sara Wade's feedback, deliver a complete playable game from start to finish, including required mechanics, an understandable objective, working win/lose/restart behavior, and a tested route. Placeholder geometry is acceptable. Fix crashes and progression blockers before presenting; track remaining polish and defects. Apply the same complete-playthrough expectation to Beta. No marketing demo is scheduled, so use the Alpha presentation as our demo checkpoint. |
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

### Week 3 results and current build

The checklist above defines full acceptance criteria. Its initial Not Run column is retained as the baseline; the narrower executed checks below do not imply that every part of a checklist row has passed. The shared prototype is on [codex/week3-prototype](https://github.com/kptmail-game/GAM305-DigitalGameDev/tree/codex/week3-prototype), latest published commit `70ea565`. It is a movement/camera blockout, not a complete Alpha build.

| Tester and date | Check and result | Limits and follow-up |
|---|---|---|
| Kevin Thrush, Sept 14 | Ten runtime assertions passed: safe landing, left/right movement, movement plane, restart position, jump ascent/landing, camera tracking/direction, and fall reset. | Function/physics checks in Unreal 5.7.4; not a complete gameplay acceptance test. |
| Christian Gulley, Sept 17 | Reported Pass for traversing the current route, reaching platforms by jumping, no sticking on current floors/platforms, and side-camera readability. | Exact tested commit not supplied. Covers parts of QA02–QA04; final props and hazard spacing remain pending. |
| Abby Mckenzie, Sept 16–17 | Reported Pass for placing a power cell in her map, starting Play, walking into it, and collecting it. | Local feature test only. Four-cell counting, duplicate prevention, UI synchronization, and exit behavior in the shared project remain Not Run. |
| Kevin Thrush, Sept 19 | Downloaded Abby's ZIP and verified its file list includes BP_PowerCell, WBP_HUD, Content, Config, and the project descriptor. | File inventory only; no archive code executed, gameplay test performed, or integration claimed. |

**Open bug:** Christian reported that the player briefly appeared black, then yellow after contacting a wall; after restarting it stayed yellow. This is recorded as [Issue 1](https://github.com/kptmail-game/GAM305-DigitalGameDev/issues/1), awaiting reproduction. Kevin handles triage; Christian can supply a screenshot, exact build, and steps if it recurs. No fix has been verified.

**Still Not Run in the shared build:** pickup effects and UI, four-cell progression and exit, stationary/moving hazard behavior, interactions and reset state, full timed playthrough, and final release/clean-checkout checks. These remain open work toward Alpha, not reasons to delay the Week 3 QA-plan submission. As of the September 19 review, no new hazard branch or files had been received from Adam or Jason; the remote repository contained main and the prototype branch.

### Instructor feedback and plan update

Sara Wade requested a defined player and motivation and emphasized complete playable Alpha/Beta builds with early, repeated playtests. Kevin proposed a maintenance robot left behind in a closed factory, gathering four power cells to power the emergency exit and escape. Christian supported the idea on September 18; other responses are still welcome. This is the working premise, with placeholder geometry permitted during development. Store meshes/textures can support the theme while the team creates its own gameplay logic, level layout, and mechanics.

Kevin updated the demo completion criteria above on September 19. Each integrated feature will receive an object test, an interaction check, and a full-route regression check when the complete route exists. Aim for at least a short 15-minute team playtest each development week. Prioritize a working beginning, objective, hazards, ending, and restart before cosmetic polish.

### Named contributions

- **Kevin Thrush:** Drafted and compiled the QA process, milestone schedule, acceptance checklist, change procedure, and bug workflow; developed the shared movement/camera prototype and shaded blockout; recorded ten runtime assertions; coordinated file handoffs and Saturday review; incorporated instructor feedback and opened the visual bug report.
- **Christian Gulley:** Tested the current prototype and supplied four Pass results with two pending checks; reported the intermittent player-color issue; shared a factory-route sketch and reusable prop suggestions; supported the robot premise. Final prop collision and hazard-spacing tests remain pending.
- **Abby Mckenzie:** Developed a power-cell pickup in her separate project and supplied its local collection test steps/results; shared the project ZIP on September 18, including pickup and HUD assets. Shared-project integration and UI behavior have not yet been verified.
- **Adam Havens:** Previously supplied the stationary-hazard design that informed QA09. No new Week 3 test report or implementation files were available at compilation; his earlier design is not counted as a newly completed Week 3 test.
- **Jason Elias:** Hazard responsibility was previously accepted. No new Week 3 test report or implementation files were available at compilation; moving-hazard implementation/testing remains pending.

### Submission and next handoff

The Word submission document is [Module Three Project Log](submissions/Module_Three_Project_Log.docx). Each member submits their own copy through 3-2 Project Log. The shared README preserves named contributions so the record does not imply equal or unverified work. Kevin can integrate incoming feature files after review, then request another teammate's test of the combined build. Later contributions and test results will be added as dated updates rather than changing the history of this submission.



## Module Four Project Log - Team Reflection

**Compiled by Kevin Thrush, September 24, 2026, using the named contributions below.**

Alpha source: [Final-Alpha](https://github.com/kptmail-game/GAM305-DigitalGameDev/tree/Final-Alpha). Git does not allow spaces in branch names; Final-Alpha is the repository branch corresponding to the rubric's “Final Alpha.” The repository is public for instructor access. [Word submission document](submissions/Module_Four_Project_Log.docx).

### Alpha status and testing

The Alpha contains a playable start-to-finish loop in Maps/AlphaIntegration. A maintenance robot collects four power cells to power the emergency exit while encountering three pickup types, four stationary hazards, and three moving hazards. Health, temporary effects, cell count, exit gating, death, and restart are connected. The visual pass adds a simple robot, factory props/signs, brighter animated cell models, objective direction/distance, and a health bar. Kevin implemented the shared systems and stand-in actors; these do not represent merged teammate implementation files.

| Tester and date | Result | Scope |
|---|---|---|
| Christian Gulley, Sept 23 | Map opened in Unreal 5.7.4; readable route; no major floor/wall collision blocker in the area tested. | Teammate-reported test on codex/week4-alpha, exact commit not supplied. Full objective was not confirmed because cells were difficult to find. |
| Christian Gulley, Sept 23 | Player stayed yellow; earlier color change did not recur. | A non-reproduction result, not proof that the intermittent issue is fixed. |
| Kevin Thrush, Sept 24 | Built the updated editor project and standalone Windows package. Completed an automated run using normal movement, jumping, collision, and pickup/exit overlaps: four cells, exit reached alive at 80 health, then successful reset. | No teleportation, invulnerability, or direct cell-award calls in the route test. About 21 seconds of simulated route time; this is not a first-time human pacing result. |
| Kevin Thrush, Sept 21 | 18 shared-state assertions and 10 movement/camera assertions passed. | Baseline checks; individual hazard timing/fairness and final human acceptance still need broader testing. |

The game remains a compact Alpha. It is below our intended 5–10 minute play length, uses simple geometry, and has no finished audio. The complete loop works in the tested build, but full human playthroughs and performance checks across team machines remain pending. See ALPHA_INTEGRATION.md for exact setup and test commands.

### What went well

Christian's specific pass/pending notes and screenshot made his test useful: they separated working route/collision behavior from the unverified cell objective. Kevin's state tests checked interactions such as a speed boost combined with a slowing floor, and the full-route test then exercised real collection and exit overlaps. This caught the distinction between functioning code and a feature teammates can actually find and use.

### Bugs and corrections

Christian reported poor cell visibility. Kevin enlarged the cells into animated yellow cylinders, added objective markers and direction/distance guidance, and improved label readability. Local collection-to-exit testing passed after the change; Christian's retest remains requested. His screenshot appeared to lack gameplay actors, suggesting an older compiled module or incomplete handoff, but that cause is not confirmed on his machine. Rebuild instructions and a standalone Windows build reduce that setup dependency.

The first packaged visual check revealed a missing robot material; Kevin corrected the packaging asset list. Visual inspection also revealed poorly oriented/dark signs, which were corrected before publication. These findings show why checking the actual packaged output matters beyond compiling the editor project. The earlier player-color report remains [Issue 1](https://github.com/kptmail-game/GAM305-DigitalGameDev/issues/1); Christian could not reproduce it on Sept 23, but no confirmed root-cause fix is claimed.

### What we would do differently

Kevin would distribute a reproducible playable build earlier, request its exact revision with each report, and have another member attempt the full objective immediately. That would expose missing actors or unclear pickups sooner. Christian recommended making pickups stand out with bright colors, labels, glow, or an icon and offered to retest. Keep the checklist's Not Run state for untested behavior instead of treating one local pass as coverage of the entire game.

### Tools and team approach

Unreal Play mode helped Christian inspect the route and collision. GitHub branches keep source versions identifiable, Issues retain bug history, and Discord supports quick questions, screenshots, and handoffs. The team's early scope analysis identified interacting pickups and hazards, which led to shared damage/effect logic and a checklist organized by feature. Christian's layout observations and Adam's earlier hazard design informed those checks.

Separate project/ZIP handoffs have been less effective than a shared tested revision: Abby's initial descriptor did not include assets, and the later ZIP has not been integrated. Automated state checks alone were also insufficient for visual clarity or teammate setup. Combining them with a rendered build and human testing gives better coverage. These are Kevin's process conclusions plus Christian's documented feedback; no unreceived reflection is attributed to another member.

### Named contributions

- **Kevin Thrush:** Shared movement/camera and gameplay systems; provisional pickup/hazard actors; Alpha map and visual improvements; build/package checks and full-route automation; test documentation, coordination, and this compiled log.
- **Christian Gulley:** Sept 23 Alpha map/route/collision test, screenshot, cell-visibility finding and improvement suggestions, and follow-up that the player-color issue did not recur. His earlier sketch and prop suggestions informed the environment direction.
- **Abby Mckenzie:** Previously supplied a separate pickup/HUD project and local cell test. No new Week 4 report was available as of Sept 24; shared integration remains pending and is not claimed complete.
- **Adam Havens:** Earlier stationary-hazard design informed the provisional implementation. No new Week 4 implementation files or test report were available as of Sept 24.
- **Jason Elias:** Previously accepted hazard work. No new Week 4 implementation files or test report were available as of Sept 24.

### Schedule through Beta

The current Alpha is available ahead of the Sept 27 deadline. Friday evening remains the requested handoff for any remaining files; Saturday is reserved for optional team retests and corrections to this record. These later contributions can be added without claiming they were present in this snapshot.

For Beta due Oct 4: review available assets and refine the route Sept 28–29; extend pacing and improve hazard readability Sept 30–Oct 1; collect timed human runs and fix blockers Oct 2–3; verify the release Oct 4. Keep required mechanics and a complete playable loop ahead of optional decoration. If incoming files remain unavailable, continue improving the working shared implementation and preserve accurate contribution credits.

![Alpha gameplay preview](docs/alpha-preview.png)

[Download the Windows Alpha build](https://github.com/kptmail-game/GAM305-DigitalGameDev/releases/tag/alpha-week4). Extract the whole ZIP and launch FactoryShift.exe. No editor or C++ build is required for this download.
