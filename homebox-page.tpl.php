<?php
// $Id: homebox.tpl.php,v 1.1.2.1 2009/05/19 13:58:39 jchatard Exp $

/**
 * @file
 * homebox.tpl.php
 * Default layout for homebox.
 */
?>

<?php // print ctools_ajax_text_button(t('Load boxes'), 'homebox/loadboxes', t('Load boxes')); ?>

<a href="#" onclick="Drupal.Homebox.loadBoxesForCurrentTab();">Load boxes</a>

<ul id="homebox-tabs">
  <?php foreach ($tabs as $key => $tab): ?>
    <li><a href="#"><?php print $tab->getName() ?></a></li>
  <?php endforeach ?>
</ul>
<div class="clear-block"></div>
<div id="homebox">

  <div class="clear-block"></div>
</div>
<style type="text/css" media="screen">
  ul#homebox-tabs {
    clear: both;
  }
  ul#homebox-tabs li {
    float: left;
    margin: 0 5px;
    padding: 0;
    border: 1px solid #999;
    background: none;
  }
  ul#homebox-tabs li a {
    display: block;
    padding: 3px 4px;
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
  
</style>