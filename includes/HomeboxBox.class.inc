<?php
/**
 * @file
 * TODO Add file description for Box Class
 */

class HomeboxBox
{
  // private $data = array();

  private $module      = NULL;
  private $name        = NULL; // Unique identifier through each module
  private $identifier  = NULL; // $module::$name
  private $title       = NULL;
  private $description = NULL;
  private $content     = NULL;

  // Default behaviour settings
  private $movable         = TRUE;
  private $collapsible     = TRUE;
  private $collapsed       = FALSE;
  private $handle_multiple = FALSE;

  // Boxes callbacks
  // TODO why not use arrays to multiple functions fired
  private $title_callback   = NULL; // Callback function to call to set the title
  private $content_callback = NULL; // Callback function to call to set the content
  private $add_callback     = NULL; // Callback function to call when the box is added by the user to its homebox page
  private $remove_callback  = NULL; // Callback function to call when the box is removeded by the user from its homebox page
  private $open_callback    = NULL; // Callback function to call when the collapsing close button is clicked
  private $close_callback   = NULL; // Callback function to call when the collapsing open button is clicked
  private $refresh_callback = NULL; // Callback function to call when the refresh button is clicked

  /**
   * Box object contructor
   *
   * @param $module
   *  Module name which handles this kind of box
   * @param $name
   *  Unique name of a particular box through it's module
   */
  function __construct($module, $name) {
    if (module_exists($module)) {
      $this->module           = $module;
      $this->name             = $name;
      $this->identifier       = "{$module}::{$name}";
      $this->title_callback   = "{$module}_{$name}_homebox_set_box_title";
      $this->content_callback = "{$module}_{$name}_homebox_set_box_content";
      // TODO add other callback, but not here to have a chance to detect available options
      // The idea is to let Homebox core module instanciate the Object
      return TRUE;
    }
    else {
      // TODO generate a dblog entry, fire an exception
      return FALSE;
    }
  }

  function __destruct() {
    // TODO: really usefull?
  }

  /***
  public function __set($name, $value) {
    if (!isset($this->{$name})) {
      $this->data[$name] = $value;
    }
    else {
      // TODO: Fire exception or something to prevent
      // from redefining reserved members
      return FALSE;
    }
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
  */
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
    $args = func_get_args();
    if (count($args) > 1 || function_exists($this->title_callback)) {
      if ($this->title = call_user_func_array($this->title_callback, $args)) {
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
    else {
      $this->title = $title;
      return TRUE;
    }
  }

  function getTitleCallback() {
    return $this->title_callback;
  }

  function setTitleCallback($callback) {
    return $this->title_callback = $callback;
  }

  //function setTitle($title) {

  // Content stuff
  function getContent() {
    return $this->content;
  }

  function getContentCallback() {
    return $this->content_callback;
  }

  function setContentCallback($callback) {
    return $this->content_callback = $callback;
  }

  function setContent() {
    $args = func_get_args();
    if ($this->content = call_user_func_array($this->content_callback, $args)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  // Description stuff
  function getDescription() {
    return $this->description;
  }

  function setDescription($description) {
    return $this->description = $description;
  }
}