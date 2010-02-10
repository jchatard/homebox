<?php

/**
 * @file
 * homebox.tpl.php
 * Default layout for homebox.
 */
?>

<?php // print ctools_ajax_text_button(t('Load boxes'), 'homebox/loadboxes', t('Load boxes')); ?>

<a href="#" onclick="Drupal.Homebox.loadBoxesForCurrentTab();">Load boxes</a>

<div id="homebox-tabs">
  <ul>
    <?php foreach ($tabs as $key => $tab): ?>
      <li><a href="#<?php print $tab->getSlug() ?>"><span><?php print $tab->getName() ?></span></a></li>
    <?php endforeach ?>
  </ul>
  <a id="homebox-add-tab" href="#">+</a>
</div>

<?php foreach ($tabs as $key => $tab): ?>
<div id="<?php print $tab->getSlug() ?>">
  
  <?php for ($i=0; $i < 3; $i++) { ?>
    <div class='column'>
      
    </div>
  <?php } ?>
  
</div>
<?php endforeach ?>
<div class="clear-block"></div>


<style type="text/css" media="screen">
  #homebox-tabs {
    clear: both;
    height: 50px;
  }
  #homebox-tabs li {
    float: left;
    margin: 0 5px;
    padding: 0;
    border: 1px solid #999;
    background: none;
  }
  #homebox-tabs li a {
    display: block;
    padding: 3px 4px;
  }
  #homebox-tabs li.ui-tabs-selected a {
    font-weight: bold;
  }
  .homebox-box {
    -webkit-box-shadow: 0px 0px 5px rgba(0, 0, 0, 0.5);
    -moz-box-shadow: 0px 0px 5px rgba(0, 0, 0, 0.5);
    -moz-border-radius: 5px;
    -webkit-border-radius: 5px;
    background: #eee;
    width: 300px;
    margin: 15px;
    float: left;
  }
  .homebox-box .title {
    font-weight: bold;
    padding: 3px 7px;
    border-bottom: 1px solid #ddd;
  }
  .homebox-box .content {
    padding: 7px;
    background: #fff;
  }
  .ui-tabs-hide {
       display: none;
  }
  
  
  
  .column { width: 330px; float: left; padding-bottom: 100px; border: 1px solid red;}
  	.portlet { margin: 0 1em 1em 0; }
  	.portlet-header { margin: 0.3em; padding-bottom: 4px; padding-left: 0.2em; }
  	.portlet-header .ui-icon { float: right; }
  	.portlet-content { padding: 0.4em; }
  	.ui-sortable-placeholder { border: 1px dotted black; visibility: visible !important; height: 50px !important; }
  	.ui-sortable-placeholder * { visibility: hidden; }
</style>