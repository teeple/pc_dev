(function ($) {   
    Drupal.behaviors.testModule = {
        doitnow: function(){
            alert("A new \"tear\" content has just been added!");
        },

        attach: function (context, settings) {
            try{
                if(settings.testModule.tear_just_added){
                    this.doitnow();
                }
            } catch(ex){}
        }
    };
})(jQuery);
