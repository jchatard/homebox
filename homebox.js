(function ($) {
  $(document).ready(function(){
    Drupal.Homebox.loadBoxesForCurrentTab();
    
  });
  Drupal.Homebox = Drupal.Homebox || {};

  Drupal.Homebox.loadBoxesForCurrentTab = function () {
    // TODO add correct CSS ID selector or XPath expr
    $('#homebox').empty();
    $.each(Drupal.settings.homebox.boxes, function(index, value){
      // if (index < 5) {
        var url = '/homebox2/homebox/content/'+ value
        var object = $(this);
        try {
          url = url.replace(/nojs/g, 'ajax');
          $.ajax({
            type: "POST",
            url: url,
            data: { 'js': 1, 'ctools_ajax': 1 },
            global: true,
            success: Drupal.CTools.AJAX.respond,
            error: function(xhr) {
              //Drupal.CTools.AJAX.handleErrors(xhr, url);
            },
            complete: function() {
              object.removeClass('ctools-ajaxing');
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