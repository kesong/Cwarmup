# Android Activity Launch Sequence Diagram

## Key Components
- **Client**: The app or launcher initiating the activity
- **AMS**: ActivityManagerService (system service)
- **PMS**: PackageManagerService (system service)
- **WMS**: WindowManagerService (system service)
- **AT**: ActivityThread (main thread of target app)
- **Zygote**: Process that forks new app processes

## Sequence Flow

```
Client App                    AMS                 PMS         Zygote      Target App      ActivityThread      Activity        WMS
    |                          |                   |             |             |               |                |             |
    |--startActivity(Intent)--->|                   |             |             |               |                |             |
    |                          |--resolveActivity->|             |             |               |                |             |
    |                          |<-ActivityInfo-----|             |             |               |                |             |
    |                          |--checkPermissions |             |             |               |                |             |
    |                          |                   |             |             |               |                |             |
    |                          |    [IF COLD START]              |             |               |                |             |
    |                          |--fork process-------------------->|             |               |                |             |
    |                          |                   |             |--create----->|               |                |             |
    |                          |                   |             |             |--main()------->|                |             |
    |                          |<-attachApplication---------------------------|               |                |             |
    |                          |--bindApplication--------------------------->|               |                |             |
    |                          |                   |             |             |--handleBindApp |                |             |
    |                          |                   |             |             |--Application.onCreate()        |             |
    |                          |                   |             |             |               |                |             |
    |                          |--scheduleLaunchActivity----------------------->|                |             |
    |                          |                   |             |             |--handleLaunch--|                |             |
    |                          |                   |             |             |--newActivity()------------------>|             |
    |                          |                   |             |             |--attach()----------------------->|             |
    |                          |                   |             |             |--callActivityOnCreate()--------->|             |
    |                          |                   |             |             |               |--onCreate()----->|             |
    |                          |                   |             |             |               |                |--setContentView()
    |                          |                   |             |             |               |<-return---------|             |
    |                          |                   |             |             |               |                |             |
    |                          |                   |             |             |               |                |--addWindow()->|
    |                          |                   |             |             |               |                |             |--createWindow
    |                          |                   |             |             |               |                |<-return------|
    |                          |                   |             |             |               |                |             |
    |                          |                   |             |             |--callActivityOnStart()--------->|             |
    |                          |                   |             |             |               |--onStart()------>|             |
    |                          |                   |             |             |               |<-return---------|             |
    |                          |                   |             |             |               |                |             |
    |                          |                   |             |             |--callActivityOnResume()-------->|             |
    |                          |                   |             |             |               |--onResume()----->|             |
    |                          |                   |             |             |               |                |--setVisible()->|
    |                          |                   |             |             |               |                |             |--makeVisible
    |                          |                   |             |             |               |<-return---------|             |
    |                          |                   |             |             |               |                |<-onWindowFocusChanged-|
    |                          |                   |             |             |               |                |             |
    |                          |<-activityResumed-------------------------------|               |                |             |
    |<-onActivityResult---------|                   |             |             |               |                |             |
    |   [if needed]            |                   |             |             |               |                |             |
```

## Phase Breakdown

### Phase 1: Launch Request (Lines 1-4)
1. Client calls `startActivity(Intent)`
2. AMS resolves the Intent using PMS
3. AMS checks permissions and task management

### Phase 2: Process Management (Lines 5-10)
- **Cold Start**: New process created via Zygote fork
- **Warm Start**: Existing process, new activity
- **Hot Start**: Activity already in memory

### Phase 3: Activity Creation (Lines 11-16)
1. AMS schedules activity launch
2. ActivityThread handles the launch
3. New Activity instance created and attached

### Phase 4: Lifecycle Execution (Lines 17-28)
1. `onCreate()` - Activity initialization
2. `setContentView()` - UI layout inflation
3. `onStart()` - Activity becomes visible
4. `onResume()` - Activity becomes interactive

### Phase 5: Window Management (Lines 19-20, 25-27)
1. Window creation and registration with WMS
2. Surface creation for rendering
3. Window made visible and focused

### Phase 6: Completion (Lines 29-30)
1. Activity reports resumed state to AMS
2. Launch process complete

## Timeline Estimates
- **Cold Start**: 1-3 seconds
- **Warm Start**: 500ms-1 second  
- **Hot Start**: 100-500ms

## Key Points
- All lifecycle methods run on the main UI thread
- Window creation happens in parallel with lifecycle
- Input system setup occurs after window focus
- SurfaceFlinger composites the final display