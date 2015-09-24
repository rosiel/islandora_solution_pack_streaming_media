<?php

/**
 * File something
 */

/**
 * Implements hook_preprocess().
 */
function islandora_streaming_preprocess_islandora_streaming(array &$variables) {
  module_load_include('inc', 'islandora', 'includes/datastream');
  module_load_include('inc', 'islandora', 'includes/utilities');
  module_load_include('inc', 'islandora', 'includes/solution_packs');
  module_load_include('inc', 'islandora', 'includes/authtokens');
  module_load_include('inc', 'islandora', 'includes/metadata');
  module_load_include('inc', 'islandora_streaming', 'includes/utilities');

  drupal_add_js('misc/form.js');
  drupal_add_js('misc/collapse.js');

  $object = $variables['object'];
  $pid = $object->id;
  $repository = $object->repository;

  $variables['islandora_dublin_core'] = isset($dc_object) ? $dc_object : NULL;
  $variables['dc_array'] = isset($dc_object) ? $dc_object->asArray() : array();
  $variables['islandora_object_label'] = $object->label;
  $variables['theme_hook_suggestions'][] = 'islandora_streaming__' . str_replace(':', '_', $object->id);
  $variables['parent_collections'] = islandora_get_parents_from_rels_ext($object);
  $variables['metadata'] = islandora_retrieve_metadata_markup($object);
  $variables['description'] = islandora_retrieve_description_markup($object);


  $video_params = array(
    'pid' => $object->id,
  );
  // Thumbnail.
  if (isset($object['TN']) && islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $object['TN'])) {
    $video_params += array(
      'tn' => url("islandora/object/{$object->id}/datastream/TN/view", array('absolute' => TRUE)),
    );
  }
  else {
    $video_params['tn'] = '';
  }
  //Sources
  // Get sets of mimes and url's.
  $sources = array();
  if ($object['STREAMING']) {
    $sources = islandora_streaming_xml_to_array($object['STREAMING']->content);
  }

  $video_params['sources'] = $sources;

  // Get Viewer
  $viewer = islandora_get_viewer($video_params, 'islandora_streaming_viewers', $object);
  if ($viewer) {
    videojs_add();
  }
  $variables['islandora_content'] = $viewer;

  }