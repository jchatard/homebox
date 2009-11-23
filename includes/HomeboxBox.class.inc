<?php
/**
 * @file
 * TODO Add file description for Box Class
 */

class HomeboxBox
{
  private $data = array();
  
  private $module      = NULL;
  private $name        = NULL; // Unique identifier through each module
  private $identifier  = NULL; // $module::$name
  private $title       = NULL;
  private $description = NULL;
  private $content     = NULL;

  // Default behaviour
  private $movable         = TRUE;
  private $collapsible     = TRUE;
  private $collapsed       = TRUE;
  private $handle_multiple = TRUE;

  // Boxes content callbacks
  private $title_callback   = NULL;
  private $content_callback = NULL;

  /**
   * Box object contructor
   * 
   * @param $module
   *  Module name which handles this kind of box
   * @param $name
   *  Unique name of a particular box through it's module
   */
  function __construct($module, $name) {
    $this->identifier       = "{$module}::{$name}";
    $this->title_callback   = "{$module}_{$name}_homebox_set_box_title";
    $this->content_callback = "{$module}_{$name}_homebox_set_box_content";    
  }
  
  function __destruct() {
    // TODO: really unsefull?
  }

  public function __set($name, $value) {
    $this->data[$name] = $value;
  }

  public function __isset($name) {
    if (array_key_exists($name, $this->data)) {
      return isset($this->data[$name]);
    }
    return FALSE;
  }

  public function __get($name) {
    if (array_key_exists($name, $this->data)) {
      return $this->data[$name];
    }
    return null;
  }

  public function __unset($name) {
    if (array_key_exists($name, $this->data)) {
      unset($this->data[$name]);
    }
  }

  function getModule() {
    return $this->module;
  }

  function getName() {
    return $this->name;
  }

  function getIdentifier() {
    return $this->identifier;
  }

  // Title stuff
  function getTitle() {
    return $this->title;
  }

  function setTitle($title) {
    $this->title = $title;
  }

  function getTitleCallback() {
    return $this->title_callback;
  }

  //function setTitle($title) {

  // Content stuff
  function getContent() {
    return $this->content;
  }

  function getContentCallback() {
    return $this->content_callback;
  }

  function setContent() {
    $args = func_get_args();
    $this->content = call_user_func($this->title_callback, $args);
  }

  // Description stuff
  function getDescription() {
    return $this->description;
  }

  function setDescription($description) {
    $this->description = $description;
  }
}