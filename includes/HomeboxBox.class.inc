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
  private $is_block    = FALSE;

  // Default behaviour settings
  private $movable         = TRUE;
  private $collapsible     = TRUE;
  private $collapsed       = FALSE;
  private $handle_multiple = FALSE;

  // Boxes callbacks
  private $title_callback       = array(); // Callback function to call to set the title
  private $content_callback     = array(); // Callback function to call to set the content
  private $description_callback = array(); // Callback function to call to set the description
  private $add_callback         = array(); // Callback function to call when the box is added by the user to its homebox page
  private $remove_callback      = array(); // Callback function to call when the box is removeded by the user from its homebox page
  private $open_callback        = array(); // Callback function to call when the collapsing close button is clicked
  private $close_callback       = array(); // Callback function to call when the collapsing open button is clicked
  private $refresh_callback     = array(); // Callback function to call when the refresh button is clicked

  /**
   * Box object contructor
   *
   * @param $module
   *  Module name which handles this kind of box
   * @param $name
   *  Unique name of a particular box through it's module
   */
  public function __construct($module, $name, $is_block = FALSE) {
    if (module_exists($module)) {
      $this->module   = $module;
      $this->name     = $name;
      $this->is_block = $is_block;
      
      // Title callbacks
      $this->title_callback[]   = "{$module}_{$name}_set_box_title";           // Specific per box
      $this->title_callback[]   = "{$module}_set_box_title";                   // Fallback for module
      $this->title_callback[]   = "homebox_{$module}_{$name}_set_box_title";   // Specific per box but handled by homebox (core blocks for example)
      $this->title_callback[]   = "homebox_{$module}_set_box_title";           // Fallback for module handled by homebox
      
      // Content callbacks
      $this->content_callback[] = "{$module}_{$name}_set_box_content";         // Specific per box
      $this->content_callback[] = "{$module}_set_box_content";                 // Specific for module
      $this->content_callback[] = "homebox_{$module}_{$name}_set_box_content"; // Specific per box but handled by homebox (core blocks for example)
      $this->content_callback[] = "homebox_{$module}_set_box_content";         // Specific for module handled by homebox
      
      // Description callbacks
      $this->description_callback[] = "{$module}_{$name}_set_box_description";         // Specific per box
      $this->description_callback[] = "{$module}_set_box_description";                 // Specific for module
      $this->description_callback[] = "homebox_{$module}_set_box_description";         // Specific for module handled by homebox
      $this->description_callback[] = "homebox_{$module}_{$name}_set_box_description"; // Specific per box but handled by homebox (core blocks for example)
      
      // TODO add other callback, but not here to have a chance to detect available options
      // The idea is to let Homebox core module instanciate the HomeBox Object
      
      // Is this box a Drupal block?
      if ($is_block) {
        $this->title_callback[] = "homebox_block_set_box_title";
        $this->content_callback[] = "homebox_block_set_box_content";
        $this->description_callback[] = "homebox_block_set_box_description";
        $this->setTitle($module, $name);
        $this->setContent($module, $name);
        $this->setDescription(NULL, $module, $name);
      }
      else {
        // Init default values
        $this->setTitle();
      }
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

  public function setTitle($title = NULL) {
    $args = func_get_args();
    
    if ($title && count($args) === 1) {
      $this->title = $title;
    }
    
    foreach ($this->title_callback as $callback) {
      if (function_exists($callback)) {
        break;
      }
    }
    if ($this->title = call_user_func_array($callback, $args)) {
      return TRUE;
    }
    else {
      return FALSE;
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
    // TODO check callbacks ordering
    foreach ($this->content_callback as $callback) {
      if (function_exists($callback)) {
        break;
      }
    }
    if ($this->content = call_user_func_array($callback, $args)) {
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

  public function setDescription($description = NULL, $args) {
    $args = func_get_args();
    if ($description == NULL) {
      foreach ($this->description_callback as $callback) {
        if (function_exists($callback)) {
          break;
        }
      }
      // Remove args[0]
      array_shift($args);
      if ($this->description = call_user_func_array($callback, $args)) {
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
    return ($this->description = $description);
  }
}