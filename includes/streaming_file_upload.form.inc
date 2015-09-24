<?php

/**
 * @file
 * Handles the uploading of the optional media file.
 */

/**
 * Defines a file upload form for uploading a preservation copy of the streaming data.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 *
 * @return array
 *   The drupal form definition.
 */
function islandora_streaming_upload_form(array $form, array &$form_state) {
  $upload_size = min((int) ini_get('post_max_size'), (int) ini_get('upload_max_filesize'));
  $extensions = array('ogg mp4 mov qt m4v avi mkv flv mp3 m4a wav');
  $form['upload_preservation'] = array(
    '#title' => t('Upload a preservation copy?'),
    '#type' => 'checkbox',
  );
  $form['media_file'] = array(
    '#title' => t('Upload File'),
    '#type' => 'managed_file',
    '#description' => t('Select file to upload. No access derivatives or thumbnails will be automatically created.<br/>Files must be less than <strong>@size MB.</strong><br/>Allowed file types: <strong>@ext.</strong>', array(
      '@size' => $upload_size,
      '@ext' => $extensions[0]
    )),
    '#default_value' => isset($form_state['values']['media_file']) ? $form_state['values']['media_file'] : NULL,
    '#upload_location' => 'temporary://',
    '#upload_validators' => array(
      'file_validate_extensions' => $extensions,
      // Assume its specified in MB.
      'file_validate_size' => array($upload_size * 1024 * 1024),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="upload_preservation"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['upload_thumbnail'] = array(
    '#title' => t('Upload a thumbnail image?'),
    '#type' => 'checkbox',
  );
  $form['thumbnail_file'] = array(
    '#title' => t('Thumbnail'),
    '#type' => 'managed_file',
    '#description' => t('Select thumbnail to upload.<br/>Files must be less than <strong>@size MB.</strong><br/>Allowed file types: <strong>JPEG, JPG, PNG.</strong>', array('@size' => $upload_size)),
    '#default_value' => isset($form_state['values']['thumbnail_file']) ? $form_state['values']['thumbnail_file'] : NULL,
    '#upload_location' => 'temporary://',
    '#upload_validators' => array(
      'file_validate_extensions' => array('jpg jpeg png'),
      // Assume its specified in MB.
      'file_validate_size' => array($upload_size * 1024 * 1024),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="upload_thumbnail"]' => array('checked' => TRUE),
      ),
    ),
  );
  return $form;
}

/**
 * Validation for the islandora_streaming upload form.
 *
 * @param array $form
 *   An array representing a Drupal form.
 * @param array $form_state
 *   An array containing the Drupal form state.
 */
function islandora_streaming_upload_form_validate(array $form, array &$form_state) {
  if ($form_state['values']['upload_thumbnail']) {
    if ($form_state['values']['thumbnail_file'] == 0) {
      form_error($form['thumbnail_file'], t('No thumbnail uploaded!'));
    }
  }
}

/**
 * Submit handler, adds uploaded file to the video object.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 */
function islandora_streaming_upload_form_submit(array $form, array &$form_state) {
  $object = $form_state['islandora']['objects'][0];
  if ($form_state['values']['media_file']) {
    if (empty($object['OBJ'])) {
      $ds = $object->constructDatastream('OBJ', 'M');
      $object->ingestDatastream($ds);
    }
    else {
      $ds = $object['OBJ'];
    }
    $file = file_load($form_state['values']['media_file']);
    $path = drupal_realpath($file->uri);
    $ds->setContentFromFile($path, FALSE);
    $ds->label = $file->filename;
    $ds->mimetype = $file->filemime;
  }
  // See if there's an attached thumbnail image to process.
  if ($form_state['values']['upload_thumbnail']) {
    if (empty($object['TN'])) {
      $thumbnail_ds = $object->constructDatastream('TN', 'M');
      $object->ingestDatastream($thumbnail_ds);
    }
    else {
      $thumbnail_ds = $object['TN'];
    }
    $image_file = file_load($form_state['values']['thumbnail_file']);
    $thumbnail_ds->setContentFromFile($image_file->uri, FALSE);
    $thumbnail_ds->label = $image_file->filename;
    $thumbnail_ds->mimetype = $image_file->filemime;
  }
}
