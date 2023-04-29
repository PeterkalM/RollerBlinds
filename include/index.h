const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
  <head>
    <title>Rulookerija</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body {
        text-align: center;
        margin: 0px auto;
        padding-top: 30px;
        background-color: #2b2b2b;
      }

      .button {
        box-sizing: border-box;
        background-color: transparent;
        border:0.1em solid #FFFFFF;
        border-radius: 0.12em;
        color: #FFFFFF;
        cursor: pointer;
        display: inline-block;
        align-self: center;
        font-size: 1rem;
        margin: 0 0.3em 0.3em 0;
        padding: 0.35em 0.9em;
        text-decoration: none;
        text-align: center;
        font-family: 'Trebuchet MS', Helvetica, sans-serif;
        font-weight: 700;
        margin-top: 0.5em;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: transparent;
      }

      .btn-alert {
        border:0.1em solid #ff0000;
        color: #ff0000;
      }
      
      .btn-active {
        cursor: auto;
        color:#000000;
        background-color:#FFFFFF;
      }

      @media (hover: hover) and (pointer: fine) {
        .button:hover {
          color:#000000;
          background-color:#FFFFFF;
        } 
      }

      @media (hover: hover) and (pointer: fine) {
        .btn-alert:hover {
          color:#000000;
          background-color:#ff0000;
        } 
      }

      .arrow {
        font-size: 10rem;
      }

      .control {
        height: 90%;
        width: 90%;
        margin: 0.5em;
      }

      #header {
        position: fixed;
        left: 0;
        right: 0;
        top: 0;
        height: 50px;
        margin: 0 auto;
        max-width: 500px;
        max-height: 500px;
      }

      #top-content,
      #bottom-content {
        position: fixed;
        left: 0;
        right: 0;
        height: 45%;
        margin: 0 auto;
        max-width: 500px;
        max-height: 500px;
      }

      #top-content {
        top: 50px;
      }

      #bottom-content {
        bottom: 50px;
      }
    </style>
  </head>
  <body>
    <div id="header">
      <button class="button">Automatic</button>
      <button class="button btn-active">Manual</button>
      <button class="button">Settings</button>
      <button class="button btn-alert" onclick="toggleMotor('brake');">X</button>
    </div>
    <div id="top-content">
      <button class="button control" onclick="toggleMotor('up');">
      <span class="arrow">&#x2191;</span>
      </button>
    </div>
    <div id="bottom-content">
      <button class="button control" onclick="toggleMotor('down');">
      <span class="arrow">&#x2193;</span>
      </button>
    </div>
    <script>
      function toggleMotor(x) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/" + x, true);
        xhr.send();
      }
      
      // function moveUp(x) {
      //   var xhr = new XMLHttpRequest();
      //   xhr.open("GET", "/move_up", true);
      //   xhr.send();
      // }
      
      // function moveDown(x) {
      //   var xhr = new XMLHttpRequest();
      //   xhr.open("GET", "/move_down", true);
      //   xhr.send();
      // }
      
      // function loadNextPos(){
      //   var xhr = new XMLHttpRequest();
      //   xhr.onreadystatechange = function() {
      //     if (xhr.readyState == XMLHttpRequest.DONE) {
      //       var x = xhr.responseText
      //       document.getElementById("current-position").innerHTML = x
      //     }
      //   }
      //   xhr.open('GET', '/get_turns', true);
      //   xhr.send();
      // }
      
      // function loadSavedPos(){
      //   var xhr = new XMLHttpRequest();
      //   xhr.onreadystatechange = function() {
      //     if (xhr.readyState == XMLHttpRequest.DONE) {
      //       var x = xhr.responseText
      //       document.getElementById("saved-position").innerHTML = x
      //     }
      //   }
      //   xhr.open('GET', '/get_saved_turns', true);
      //   xhr.send();
      // }
      
      // function resetTurns(x) {
      //   var xhr = new XMLHttpRequest();
      //   xhr.open("GET", "/reset_turns", true);
      //   xhr.send();
      // }
      
      // function saveTurns(x) {
      //   var xhr = new XMLHttpRequest();
      //   xhr.open("GET", "/save_turns", true);
      //   xhr.send();
      // }
      
      // loadNextPos();
      // loadSavedPos();
      // setInterval(function(){
      //   loadNextPos();
      //   loadSavedPos();
      // }, 500);
    </script>
  </body>
)=====";