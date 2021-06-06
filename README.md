# The Settlers 4 Camera Locations Plugin

This is a plugin for the game the settlers 4 using the modding API provided by nyfrk. It enabled camera location to be set and loaded like the ones that can be found it other RTS.

## Controls

| Hotkey  | Command |
| ------------- |:-------------:|
| Strg + F5      | Save Camera Location 1     |
| Strg + F8      | Save Camera Location 2     |
| Strg + F9      | Save Camera Location 3     |
| F5            | Load Camera Location 1     |
| F8      | Load Camera Location 2     |
| F9      | Load Camera Location 3     |

## Known Issues

The saved location is not 100% correct, because a read offset value seems to not be reflecting the value needed perfectly.

## How To Install

1. Download the .asi loader from nyfrk (https://github.com/nyfrk/Settlers4-ASI-Loader/releases) (It replaces the binkw32.dll with a custom one that loads .asi files)
2. Download the Settler 4 mod API (https://github.com/nyfrk/S4ModApi/releases/tag/v0.2) and place the .dll into the games folder, next to the S4_Main.exe
3. [Download this mod](https://github.com/Cydra/S4-CameraLocations/releases) and place it in the plugins folder of the game (create the folder if its not there)

Guide by: https://github.com/WizzardMaker

## Planned features

- Fix the small offset issue
- Add more locations
- Create and load a .ini file to let users rebind the hotkeys to their liking

## License

The project is licensed under the [MIT](LICENSE.md) License.
