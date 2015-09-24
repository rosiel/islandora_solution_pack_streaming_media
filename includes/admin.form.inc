<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_streaming_admin(array $form, array &$form_state) {
  module_load_include('inc', 'islandora', 'includes/solution_packs');
  $form = array();
  // Get viewer table.
  $viewer_table = islandora_viewers_form('islandora_streaming_viewers', 'rtmp/mp4');
  $form += $viewer_table;

  // Viewer stuff.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
    '#weight' => 1,
    '#submit' => array('islandora_streaming_admin_submit'),
  );

  return system_settings_form($form);
}

/**
 * Form submit for allowing the deletion of the viewer variable.
 */
function islandora_streaming_admin_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#id'];
  switch ($op) {
    case 'edit-reset':
      variable_del('islandora_streaming_viewers');
      break;
  }
}
