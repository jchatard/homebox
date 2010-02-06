<?php
/**
 * @file
 * TODO Add file description for Tab Class
 */

class HomeboxTab {
  private $name  = NULL;
  private $slug  = NULL;
  private $boxes = array();
  
  public function __construct($name = NULL) {
    $this->name = $name;
    $this->setSlug($name);
  }
  
  public function __destruct() {
    module_invoke_all('hombebox_tab_destruct', $this);
  }
  
  public function setName($name) {
    if (!is_null($name)) {
      $this->name = $name;
    }
    $this->name = t('New tab');
  }
  
  public function getName() {
    return $this->name;
  }

  private function setSlug($name) {
    if (!is_null($name)) {
      $this->slug = drupal_strtolower(str_replace(' ', '-', $name));
      return $this->slug;
    }
    return $this->slug = t('new-tab');
  }

  public function addBox(&$box_object) {
    // Check array_push() for keyed value pairs
    return array_push($this->boxes, $box_object);
  }
  
}