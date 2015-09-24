<?php

/**
 * Utility function to turn an array into a string of XML.
 */
function islandora_streaming_to_xml_string($sources = array()) {
  $xml = new SimpleXMLElement('<sources/>');
  foreach ($sources as $source) {
    $xml_source = $xml->addChild('source');
    foreach ($source as $key => $value) {
      $xml_source->addChild("$key", htmlspecialchars($value));
    }
  }
  return $xml->asXML();
}

/**
 * Utility function to extract sources from an XML string.
 */
function islandora_streaming_xml_to_array($xmlstring = '') {
  $xml = new SimpleXMLElement($xmlstring);
  $output = array();
  foreach ($xml->source as $source) {
    $output[] = array(
      'url' => (string) $source->url,
      'mime' => (string) $source->mime,
    );
  }
  return $output;
}