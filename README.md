# Project Protolab
A modular player behavior config system built in Unreal Engine 5.

## Overview
This project is an Unreal Engine tech prototype created as a personal learning exercise, where I am recreating a modular player behavior configuration system that I previously worked on — now in Unreal C++.
The system allows developers to define player capabilities and object behaviors as individual modules. Its data-driven configuration also enables designers to create variants of similar behaviors purely by tuning values and swapping assets — without changing code.

**The ultimate goal** is that, as the project expands, this prototype will become a test ground for various game mechanic prototypes, utilizing the modular player behavior system.

## Key Features
- **Player Behavior System** -- The core system that manages and updates currently active behavior configs.
- **Player Behavior Config** -- The data-driven component of a player behavior. Contains mostly tunings and other configurable fields related to a behavior.
- **Player Behavior Config Runtime** -- The runtime component containing actual game logic related to a certain player behavior. Instantiated by each Player Behavior Config, and utilizes the tunings from the config.
- **Item Behavior Config** and **Item Behavior Config Runtime** -- Similar to their player behavior counterparts, except that these defines what a particular item allows the player to do when held by the player. Added to and removed from the Player Behavior System upon picking up/dropping the item.
- **Other Player Components** -- In order to support basic gameplay logic, some simplified player components such as Player Input Handler, Player Locomotion, etc. are also implemented. While these components are **NOT** the focus of this prototype, they will be gradually updated to support more complicated mechanics down the line.
> ⚠️ *Work-in-progress*: The core architecture of these key features are complete and they are capable of realizing simple game interactions. Future updates and refactor will be made to these systems to support more complicated behaviors.

## Tech Details
TBA

## Roadmap
TBA
