```mermaid
sequenceDiagram
    participant P1 as P1 Module
    participant MB as ESPtje
    participant SE as SolarEdge
    participant MQTT as MQTT Broker
    participant App as Telefoon

    MB->>MQTT: Subscribe: p1bridge/activated

    loop Elke seconde (Regellus)
        P1->>MB: Actueel vermogen (ESP-NOW)
        SE->>MB: Modbus RTU Request
        MB->>SE: Export-limiet (RS485)
        MB->>MQTT: Publish: p1bridge/power (double)
        MB->>MQTT: Publish: p1bridge/status ("running")
    end

    Note over App,MB: Bediening via telefoon
    App->>MQTT: Publish: p1bridge/activated (true / false)
    MQTT->>MB: Push: p1bridge/activated
    MB->>MQTT: Publish: p1bridge/status ("running" / "disabled")

    alt Watchdog > 5 sec geen ESP-NOW data
        MB->>SE: Fail-safe (export -> 0W)
        MB->>MQTT: Publish: p1bridge/status ("p1Error")
    else Geen reactie van omvormer
        MB->>MQTT: Publish: p1bridge/status ("transformerError")
    end
```
