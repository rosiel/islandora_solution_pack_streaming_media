# Streaming Media Solution Pack 

## Introduction

Create and manage Islandora objects representing streaming resources.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)
* [Tuque](https://github.com/islandora/tuque)

*To successfully play streaming media, a compatible viewer must be enabled. Currently, Islandora VideoJS is the only known compatible viewer. RTMP streaming does not work with all versions of the videojs library. This module has been tested with 4.12.5 and 4.12.11.*

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Configure default player in Administration > Islandora > Solution Pack Configuration > Streaming Media Solution Pack (admin/islandora/solution_pack_config/streaming_media). 

## Documentation

This module is intended to give access to externally hosted streaming resources that can be catalogued and displayed via an Islandora instance. An option is provided to include a copy of the file in this islandora object (as the OBJ datastream) but this is purely optional. No access datastreams or thumbnails will be generated.

There is also an option to provide a thumbnail during the ingest process. 

When creating an object, you may specify multiple types of streams for the same resource.

## Maintainers/Sponsors
Current maintainers:

* [Rosie Le Faive](https://github.com/rosiel)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)


# TODO:

* add download link. 
* validate handler should strip out empty sources.