# serial
Low overhead implementation of serial reading and writing with POD datatypes for unix serial device files.

## Building
After building and installing the library you may use this cmake integration template to link to 
the serial export target.

```
find_package(serial)

add_executable(your_target ${YOUR_TARGET_SOURCES})
#add_library(your_target ${YOUR_TARGET_SOURCES})

target_link_libraries(your_target serial::serial)
```

## Compatability
This library strictly checks for POD (plain-old-data) types when creating buffers.
