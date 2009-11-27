<?php
/**
 * @file
 * TODO Add file description for Box Class
 * TODO why not rename Homebox Box as Homebox Widget?
 */

class HomeboxBox
{
  // private $data = array();

  private $module      = NULL;
  private $name        = NULL; // Unique identifier through each module
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
  public function __construct($module, $name) {
    if (module_exists($module)) {
      $this->module           = $module;
      $this->name             = $name;
      $this->title_callback   = "{$module}_{$name}_set_box_title";
      $this->content_callback = "{$module}_{$name}_set_box_content";
      // TODO add other callback, but not here to have a chance to detect available options
      // The idea is to let Homebox core module instanciate the HomeBox Object
    }
    else {
      // TODO generate a dblog entry, fire an exception
      return FALSE;
    }
  }

  public function getModule() {
    return $this->module;
  }

  public function getName() {
    return $this->name;
  }

  /**
   * Identifier is made of the module name
   * and the unique box name
   */
  public function getIdentifier() {
    return "{$this->module}:{$this->name}";
  }

  // Title stuff
  public function getTitle() {
    return $this->title;
  }

  public function setTitle($title) {
    $args = func_get_args();
    // If more than one arg AND title_callback implementation exists use it
    if (count($args) > 1 && function_exists($this->title_callback)) {
      if ($this->title = call_user_func_array($this->title_callback, $args)) {
        return TRUE;
      }
      else {
        // Title callback doesn't exists
        // and more than 1 arg was given
        return FALSE;
      }
    }
    else {
      // Just return $title as defined in arg
      $this->title = $title;
      return TRUE;
    }
  }

  public function getTitleCallback() {
    return $this->title_callback;
  }

  public function setTitleCallback($callback) {
    return $this->title_callback = $callback;
  }

  //function setTitle($title) {

  // Content stuff
  public function getContent() {
    return $this->content;
  }

  public function getContentCallback() {
    return $this->content_callback;
  }

  public function setContentCallback($callback) {
    return $this->content_callback = $callback;
  }

  public function setContent() {
    $args = func_get_args();
    if ($this->content = call_user_func_array($this->content_callback, $args)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  // Description stuff
  public function getDescription() {
    return $this->description;
  }

  public function setDescription($description) {
    return $this->description = $description;
  }
}