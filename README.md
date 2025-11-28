# SFML 3.0 CMake Template

Simple SFML 3.0 CMake project template. Builds SFML via FetchContent and provides a small `Game` class with a fixed-timestep loop.

Setup and build (PowerShell / Windows)

1. Configure (Visual Studio generator, x64):

```powershell
cd C:\Users\Muscu\source\repos\sfml-template
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
```

2. Build (Release):

```powershell
cmake --build build --config Release
```

3. Run:

```powershell
.\build\Release\SfmlTemplate.exe
```

How to change the executable/project name

-- The default executable name is set by the CMake cache variable `projectExecutableName` (default: `SfmlTemplate`).
- You can change it at configure time without editing `CMakeLists.txt` by passing `-DprojectExecutableName=MyApp` to `cmake`:

```powershell
cmake -S . -B build -DprojectExecutableName=MyApp -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

- In Visual Studio you can also edit the CMake cache variable in the CMake settings UI or in `CMakeSettings.json` variables.

Notes
- `assets/` is copied into the build output directory on each build by a POST_BUILD command so the executable can load assets at runtime.
- This template fetches and builds SFML via CMake FetchContent; the first configure/build may take several minutes.

- If `assets/fonts/` or `assets/images/` are empty, CMake will attempt to download a demo font and image at configure time into those folders. You can still replace them with your own assets.

Reconfiguring after changing the project name

- If you change `projectExecutableName` and you already have a `build/` directory from a previous configure, the generated target name and output filenames in `build/` will not update automatically.
- Recommended approaches:
	- Reconfigure the existing build directory with the new value:

```powershell
cmake -S . -B build -DprojectExecutableName=MyApp -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

	- Or remove the `build/` directory and run a fresh configure (this guarantees a clean cache):

```powershell
Remove-Item -Recurse -Force build
cmake -S . -B build -DprojectExecutableName=MyApp -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

- In Visual Studio, edit the `projectExecutableName` CMake variable in CMake Settings and then select "Generate Cache" / reconfigure to apply the change.

