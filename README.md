# qConnmanStress

qConnmanStress is a little tool that uses [libqtconnman-qt](https://git.merproject.org/mer-core/libconnman-qt) in order to connect to a given SSID.
If the service is disconnected, a connection is requested. On the contrary, once the network service goes online, it is disconnected again.
This can be used to stress-test Wifi drivers and network stacks. Note that connman connects to an external server in order to prove it is really
online, so all layers of a network stack are involved in a test cycle.

## Invocation

Call it from the command line with `./qConnmanStress -s <ssid> -p <pw>`

## License

GPLv2

