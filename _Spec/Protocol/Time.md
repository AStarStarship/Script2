# [SCRIPT Specification](../)

## [SCRIPT Protocol](./)

### Time

#### Time Epoch

The Unix timestamp cycles around in the year 3038, so to ensure stability on 32-bit systems with 32-bit kTMS timestamps, the time epoch shall be of the span of a decade, and such systems shall not be made to schedule events beyond a 6 epochs. Systems that require schedulers with more than the maximum number of epochs shall use a 64-bit kTME timestamp.

**[<< Previous Section: Group Automata](GroupAutomata.md) | [Next Section: Slots >>](Slots.md)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
