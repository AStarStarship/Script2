# [SCRIPT Specification](../)

## [SCRIPT Protocol Specificaiton](./)

### Congestion Control Table

The **Script Congestion Control Table** (**CCT**) is an array of 2^16 (65536) time slices of 15-bit integers per day offset from midnight. Each value represents the average load of the network from 0 through 32767. This value is then translated directly into the maximum length of a *ASCII Packet*. Endpoints may request a copy of the CCT using the *ENQ Operation*.

Upon opening a *Packet Portal* between a *ASCII Router* and *ASCII Endpoint* the router sends the endpoint the 15-bit maximum packet size. The end-point then readjusts it's *US Book Header Entries* once per time slice.

Three years of data must be stored in order to detect annual cycles such as holidays. To calculate contention the following formula is used:

`current_sample = Sigma (0.85* previos_sample + 0.15 * current) / num_samples`

#### Memory Footprint

* *60 (seconds/minute) × 60 (minutes/hour) × 24 (hours/day)* = ***86400 (seconds/day)***
* *(86400 seconds/day) / 2^16(samples/day* = ***1.318359375 (seconds/sample)***

| One Day's Memory | One Week's Memory | Three Year's Memory |
|:----------------:|:-----------------:|:-------------------:|
|      128KB       |        1MB        |      140.928MB      |

**[<< Previous Section: Quality of Service](QualityOfService.md) | [Next Section: Abnormal Behavior >>](AbnormalBehavior.md)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
