# Streaming Media Solution Pack 

## Introduction

Create and manage Islandora objects representing streaming resources.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)
* [Tuque](https://github.com/islandora/tuque)
* Islandora video viewer of your choice (see Configuration below)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Configure default player in Administration > Islandora > Solution Pack Configuration > Streaming Media Solution Pack (admin/islandora/solution_pack_config/streaming_media). You can assign any player
that works with the 'video/mp4' mimetype, however this module uses the 'rtmp/mp4' media type and not all players that play video/mp4 have rtmp support. [VideoJS](https://github.com/islandora/islandora_videojs/) does, and this module works with Video.js library versions 4.12.5 and 4.12.11.

## Documentation

This module is intended to give access to externally hosted streaming resources that can be catalogued and displayed via an Islandora instance. Instead of uploading a file, the user is asked to provide a streaming URL for each object (e.g. rtmp://[mystreamingserver]:1935/vod/mp4::myvideo.mp4).  If it is also desired to store the original file in Islandora for preservation purposes, an option is given during ingest to upload an OBJ datastream. This is purely optional and no access datastreams or thumbnails will be generated.

There is also an option to provide a thumbnail during the ingest process. 

When creating an object, you may specify multiple types of streams for the same resource. See http://docs.videojs.com/docs/guides/tech.html#enabling-streaming-playback for more information.

## Maintainers/Sponsors
Current maintainers:

* [Rosie Le Faive](https://github.com/rosiel)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)


# TODO:

* add download link. 
* validate handler should strip out empty sources.
