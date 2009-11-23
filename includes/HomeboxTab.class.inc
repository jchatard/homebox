<?php
/**
 * @file
 * TODO Add file description for Tab Class
 */

class homebox_tab {
  var $name = t('New tab');

  function homebox_tab($name = NULL) {
    $this->set_name($name);
  }
  function set_name($name) {
    if (!is_null($name)) {
      $this->name = $name;
    }
    return $this->name;
  }
  function delete_tab() {
    $success = module_invoke_all('hombebox_tab_delete', $this);
    $this = NULL;
  }
}