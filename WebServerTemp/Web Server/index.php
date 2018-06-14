<html>
<head>
<title>HOME</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<script src="//code.jquery.com/jquery-1.11.0.min.js"></script>

 <link rel="stylesheet" type="text/css" href="style.css">
 <script>  
        function show()  
        {  
            $.ajax({  
                url: "transfer/temp-1.php",  
                cache: false,  
                success: function(html){  
                    $("#content").html(html); 
				}
             }); 
           $.ajax({  
                url: "transfer/temp-2.php",  
                cache: false,  
                success: function(html){  
                    $("#content-1").html(html); 
                }
             }); 
             
             $.ajax({  
                url: "transfer/ledstate.php",  
                cache: false,  
                success: function(html){  
                    $("#content-3").html(html); 
                }
             }); 
             
        }
        
        $(document).ready(function(){  
            show();  
            setInterval('show()',500);  
        }); 
        
 
      function AjaxFormRequest(result_id,led,url) {
      jQuery.ajax({
      url:     url,
      type:     "POST",
      dataType: "html",
      data: jQuery("#"+led).serialize(),
         });
}


</script>
    
    
    
</head>
    <body>
          <div class="r">
          <p class="r1">Температура  дома</p>
          <div class="r2" style="display:inline-block;">
          <div class="r3" id="content"></div> 
          <div class="r3"> C<sup>o</sup></div>
          </div>
          </div>
        

          <div class="r">
          <p class="r1">Температура W5100</p>
          <div class="r2" >
          <div class="r3" id="content-1"></div> 
          <div class="r3"> C<sup>o</sup></div>
          </div>
          </div>
          
          <div class="r">
          <div class="rl">
          <p class="r1">Выключатель</p>
          <div class="r2" style="font-size:35px" >
          <form  id="led" action="" method="post"  >
          <label><input type="radio" name="status" value="1"> ON </label>
          <label><input type="radio" name="status" value="0"> OFF </label>
          <br>
          <input class="submitButton" type="submit" value="Отправить" onclick="AjaxFormRequest('messegeResult', 'led', 'transfer/led.php')" >
          </form>
          </div>
          </div>
          
          <div class="rr">
          <p class="r1">Состояние</p>
          <div class="r2"style="font-size:35px" >
          <div class="r3" id="content-3"></div> 
          </div>
          </div>
          
          </div>
         

        
        
   </body>
</html> 