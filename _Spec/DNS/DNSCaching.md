# [SCRIPT Specification](../)

## [Distributed Nomination System Specification](./)

### DNS Caching

The **Local DNS Authority** (**LDNSA**) is located at address 0.0.0.0.1. In Chinese Rooms expressions are indexed with printable Unicode characters and 0 is a no-op command. 0.0.0.0.1 gets turned into 4 no-ops and a single ASCII SOH Operation that pushes the Library onto the *Expression Stack*. If the key doesn't exist in the Local Cache, the DNS Query is passed on to a *Superior DNS Authority*, if the key does not exist in its cache it will be passed on to the next highest up authority until it is either resolved or returns a **Key Not Found Error**. All Automata have a cache and *Script Automata* shall regularly check with *Superior DNS Authorities* to update and remove keys.

**[<< Previous Section:](./) | [Next Section: >>](./)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
