(function ($) {



  		



  $(document).ready(function(){
    
    $("#first-tab .column").sortable({
			connectWith: '.column',
			opacity: 0.7,
			tolerance: 'pointer',
			revert: true
		});

		$(".portlet").addClass("ui-widget ui-widget-content ui-helper-clearfix ui-corner-all")
			.find(".portlet-header")
				.addClass("ui-widget-header ui-corner-all")
				.prepend('<span class="ui-icon ui-icon-plusthick"></span>')
				.end()
			.find(".portlet-content");

		$(".portlet-header .ui-icon").click(function() {
			$(this).toggleClass("ui-icon-minusthick");
			$(this).parents(".portlet:first").find(".portlet-content").toggle();
		});

		$(".column").disableSelection();
    
    
    // Init the jQuery UI tabs
    var tabs = $("#homebox-tabs").tabs({
      show: function(event, ui) {
        current_tab_is_loaded = 'homebox_tab_' + ui.tab.hash.replace('#', '') + '_loaded';
        // Test if the Tab is already loaded
        if (jQuery.data(document, current_tab_is_loaded) != true) {
          // If not load boxes names
          Drupal.Homebox.getBoxesIdentifiersForTab(ui);
          // ... and store loaded state for this tab
          jQuery.data(document, current_tab_is_loaded, true);
        };
      },
      //cookie: { expires: 30 }
    });
    
    // Add tab button
    $('#homebox-add-tab').click(function(e){
      $(tabs).tabs('add' , '#foo' , 'Mon 3ème');
      e.stopPropagation();
    });
    
  });

  Drupal.Homebox = Drupal.Homebox || {};

  Drupal.Homebox.getBoxesIdentifiersForTab = function (tab) {
    var url = Drupal.settings.basePath + '?q=homebox/get/tab/';
    try {
      $.ajax({
        type: "GET",
        url: url + tab.tab.hash.replace('#', ''),
        global: true,
        success: Drupal.Homebox.getBoxesForTab,
        error: function(xhr) {
          Drupal.CTools.AJAX.handleErrors(xhr, url);
        },
        complete: function() {
          
        },
        dataType: 'json'
      });
    }
    catch (err) {
      // alert("An error occurred while attempting to process " + url);
      return false;
    }
  },

  Drupal.Homebox.getBoxesForTab = function (data) {
    // TODO add correct CSS ID selector or XPath expr
    //$('#homebox').empty();
    
    $.each(data.boxes, function(index, value){
      // if (index < 5) {
        var url = Drupal.settings.basePath + '?q=homebox/get/box/' + value + '/' + data.tab;
        var object = $(this);
        try {
          url = url.replace(/nojs/g, 'ajax');
          $.ajax({
            type: "GET",
            url: url,
            global: true,
            success: Drupal.CTools.AJAX.respond,
            error: function(xhr) {
              Drupal.CTools.AJAX.handleErrors(xhr, url);
            },
            complete: function() {
              
            },
            dataType: 'json'
          });
        }
        catch (err) {
          // alert("An error occurred while attempting to process " + url);
          return false;
        }
      
      // };
    });
  }
  
})(jQuery);