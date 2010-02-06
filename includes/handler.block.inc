<?php // $Id$

function homebox_declare_boxes() {
  global $theme_key;

  $boxes = array();

  $result = db_query("SELECT module, delta FROM {blocks}");
  
  while ($block = db_fetch_object($result)) {
    $box = new HomeboxBox($block->module, $block->delta, TRUE);
    $boxes[] = $box;
  }
  return $boxes;
}

function homebox_block_set_box_title($module, $delta) {
  $block = (object) module_invoke($module, 'block', 'view', $delta);
  
  if (!$block->subject) {
    $block->subject = db_result(db_query("SELECT title FROM {blocks} WHERE module = '%s' AND delta = '%s'", $module, $delta));
  }
  if (!$block->subject && $module == 'views') {
    $block->subject = _homebox_get_view_name($delta);
  }
  if (!$block->subject) {
    $module_blocks = module_invoke($module, 'block', 'list');
    $block->subject = $module_blocks[$delta]['info'];
  }
  // Fail safe
  if (!$block->subject) {
    // Is this still necessary?
    $block->subject = t('<em>No title defined</em>');
  }
  
  return $block->subject;
}

function homebox_block_set_box_content($module, $delta) {
  static $count = 0;
  // Render block content
  $array = module_invoke($module, 'block', 'view', $delta);

  if (isset($array) && is_array($array)) {
    foreach ($array as $k => $v) {
      $block->$k = $v;
    }
  }
  return $block->content;
}

function homebox_block_set_box_description($module, $delta) {
  if ($module == 'views') {
    // if this is 32, this should be an md5 hash.
    if (drupal_strlen($delta) == 32) {
      $hashes = variable_get('views_block_hashes', array());
      if (!empty($hashes[$delta])) {
        $delta = $hashes[$delta];
      }
    }

    // This indicates it's a special one.
    if (drupal_substr($delta, 0, 1) == '-') {
      list($nothing, $type, $name, $display_id) = explode('-', $delta);
      if ($view = views_get_view($name)) {
        $description = $view->description;
        $view->destroy();
      }
    }

    list($name, $display_id) = explode('-', $delta);

    // Load the view
    if ($view = views_get_view($name)) {
      $description = $view->description;
      $view->destroy();
    }

    return $description;
  }
  else {
    return NULL;
  }
}

function _homebox_get_view_name($delta) {

  // if this is 32, this should be an md5 hash.
  if (drupal_strlen($delta) == 32) {
    $hashes = variable_get('views_block_hashes', array());
    if (!empty($hashes[$delta])) {
      $delta = $hashes[$delta];
    }
  }

  // This indicates it's a special one.
  if (drupal_substr($delta, 0, 1) == '-') {
    list($nothing, $type, $name, $display_id) = explode('-', $delta);
    if ($view = views_get_view($name)) {
      $name = $view->display[$display_id]->display_options['block_description'];
      $view->destroy();
    }
  }

  list($name, $display_id) = explode('-', $delta);

  // Load the view
  if ($view = views_get_view($name)) {
    $name = $view->display[$display_id]->display_options['block_description'];
    $view->destroy();
  }

  return $name;
}