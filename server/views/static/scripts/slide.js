// Sliding effect on navbar

$(document).ready(function(){
	$(".navbar a, footer a[href='#MainPage']").on('click', function(event) {
    	if (this.hash !== "") {
      		event.preventDefault();
      		var hash = this.hash;
      		$('html, body').animate({
        		scrollTop: $(hash).offset().top
			}, 500, function(){ window.location.hash = hash;});
    	}
	});
  	$(window).scroll(function() {
    	$(".slideanim").each(function(){
      		var pos = $(this).offset().top;
      		var winTop = $(window).scrollTop();
        	if (pos < winTop + 600) {
          		$(this).addClass("slide");
        	}
    	});
  	});

	function launchArena() {
		document.location.href = "http://localhost/combat";
	}
})


