<?php
/**
 * @file
 * TODO Add file description for Page Class
 */

class HomeboxPage {
  private $name = NULL;
  private $slug = NULL;
  private $tabs = array();
  
  public function __construct($name) {
    $this->name = $name;
    $this->setSlug($name);
  }

  public function __destruct() {
    module_invoke_all('hombebox_page_destruct', $this);
  }
  
  public function addTab(&$tab_object) {
    // Check array_push() for keyed value pairs
    return array_push($this->tabs, $tab_object);
  }

  private function setSlug($name) {
    if (!is_null($name)) {
      $this->slug = drupal_strtolower(str_replace(' ', '-', $name));   
      return $this->slug;
    }
    return $this->slug = t('new-page');
  }

}
