<?php

/**
 * @file
 * Handles the management of the streams datastream.
 */

/**
 * Defines a form to edit an XML datastreams defining streaming sources.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 *
 * @return array
 *   The drupal form definition.
 */
function islandora_streaming_edit_streams_form(array $form, array &$form_state, $islandora_object = NULL) {
  module_load_include('inc', 'islandora_streaming', 'includes/utilities');
  $first_load = FALSE;
  if ($islandora_object) {
    $editing = TRUE;
    if (!isset($form_state['islandora']['objects'])) {
      $form_state['islandora']['objects'] = array($islandora_object);
      $first_load = TRUE;
    }
    if ($islandora_object['STREAMING']) {
      $defaults = islandora_streaming_xml_to_array($islandora_object['STREAMING']->content);
      if ($first_load) {
        $form_state['num_sources'] = count($defaults);
      }
    }
  }
  else {
    $editing = FALSE;
  }

  $form['#tree'] = TRUE;
  if (empty($form_state['num_sources'])) {
    $form_state['num_sources'] = 1;
  }

  for ($i = 1; $i <= $form_state['num_sources']; $i++) {
    $form['source'][$i] = array(
      '#type' => 'fieldset',
      '#title' => t('Source #@num', array('@num' => $i)),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['source'][$i]['url'] = array(
      '#type' => 'textfield',
      '#title' => t('Stream URI'),
      '#description' => t("Enter uri of the stream. URI should point directly to the file."),
      '#size' => 40,
      '#maxlength' => 200,
      '#default_value' => isset($defaults[$i-1]['url']) ? $defaults[$i-1]['url'] : '',
      //'#required' => TRUE,
    );
    $form['source'][$i]['mime'] = array(
      '#type' => 'select',
      '#options' => array(
        'video/mp4' => t('video/mp4 - .mp4 files'),
        'application/x-mpegURL' => t('application/x-mpegURL - .m3u8 files'),
        'video/MP2T' => t('video/MP2T - .ts files'),
        'video/ogg' => t('video/ogg - OGG format'),
        'video/webm' => t('video/webm - WebM format'),
        'rtmp/mp4' => t('rtmp/mp4 - rtmp streaming protocol'),
        'audio/wave' => t('audio/wave'),
        'audio/wav' => t('audio/wav'),
        'audio/x-wav' => t('audio/x-wav'),
        'audio/x-pn-wav' => t('audio/x-pn-wav'),
        'audio/webm' => t('audio/webm'),
        'audio/ogg' => t('audio/ogg'),
        'application/ogg' => t('application/ogg')
        ),
      '#title' => t('Mimetype'),
      '#description' => t("Enter the mimetype of the stream."),
      '#size' => 20,
      '#maxlength' => 40,
      '#default_value' => isset($defaults[$i-1]['mime']) ? $defaults[$i-1]['mime'] : '',
      //'#required' => TRUE,
    );
  }
  // Add submit handler only if editing existing object.
  if ($editing) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t("Submit"),
    );
  }

  $form['add_source'] = array(
    '#type' => 'submit',
    '#value' => t("Add another source"),
    '#submit' => array('streaming_edit_streams_add_source'),
  );
  if ($form_state['num_sources'] > 1) {
    $form['remove_source'] = array(
      '#type' => 'submit',
      '#value' => t('Remove latest source'),
      '#submit' => array('streaming_edit_streams_remove_source'),
      '#limit_validation_errors' => array(),
    );
  }

  return $form;
}

/**
 * Submit handler for "Add another source" button.
 */
function streaming_edit_streams_add_source($form, &$form_state) {
  $form_state['num_sources']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for "Remove latest source" button.
 */
function streaming_edit_streams_remove_source($form, &$form_state) {
  if ($form_state['num_sources'] > 1) {
    $form_state['num_sources']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler, writes sources to STREAMING datastream.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 */
function islandora_streaming_edit_streams_form_submit(array $form, array &$form_state) {
  module_load_include('inc', 'islandora_streaming', 'includes/utilities');
  $object = $form_state['islandora']['objects'][0];
  // Organize output into array.
  $sources = array();
  for ($i = 1; $i <= $form_state['num_sources']; $i++) {
    $sources[] = array(
      'url' => $form_state['values']['source'][$i]['url'],
      'mime' => $form_state['values']['source'][$i]['mime'],
    );
  }
  // Turn array into xml.
  $output = islandora_streaming_to_xml_string($sources);

  if (empty($object['STREAMING'])) {
    $ds = $object->constructDatastream('STREAMING', 'M');
    $object->ingestDatastream($ds);
  }
  else {
    $ds = $object['STREAMING'];
  }

  $ds->setContentFromString($output, FALSE);
  $ds->label = 'Streaming Info';
  $ds->mimetype = 'application/xml';

  $form_state['redirect'] = "islandora/object/{$object->id}/manage/datastreams";

}
