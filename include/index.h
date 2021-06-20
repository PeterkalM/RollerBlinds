const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>

<head>
  <title>Rulookerija</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: Arial;
      text-align: center;
      margin: 0px auto;
      padding-top: 30px;
    }
    hr {
      margin-top: 20px;
    }

    .button {
      margin-top: 10px;
      padding: 10px 20px;
      font-size: 24px;
      text-align: center;
      outline: none;
      color: #fff;
      background-color: #2f4468;
      border: none;
      border-radius: 5px;
      box-shadow: 0 6px #999;
      cursor: pointer;
      -webkit-touch-callout: none;
      -webkit-user-select: none;
      -khtml-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
      -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
    }

    .button:hover {
      background-color: #1f2e45
    }

    .button:active {
      background-color: #1f2e45;
      box-shadow: 0 4px #666;
      transform: translateY(2px);
    }


  </style>
</head>

<body>
  <h1>Rulookerija</h1>
  <hr>
  <h3>Manuaalne juhtmine</h3>
  <button class="button" onmousedown="toggleMotor('forward');" ontouchstart="toggleMotor('forward');"
    onmouseup="toggleMotor('brake');" ontouchend="toggleMotor('brake');">Ruloo yles</button>
  <button class="button" onmousedown="toggleMotor('reverse');" ontouchstart="toggleMotor('reverse');"
    onmouseup="toggleMotor('brake');" ontouchend="toggleMotor('brake');">Ruloo alla</button>
  <br><hr>
  <h3>Korguse seadistamine</h3>
  <br>
  <b>Praegune positsioon:</b> <span id="current-position"></span>
  <br>
  <b>Salvestatud positsioon:</b> <span id="saved-position"></span>
  <br>
  <button class="button" onmouseup="resetTurns();">Nulli positsioon</button>
  <button class="button" onmouseup="saveTurns();">Salvesta positsioon</button>
  <br>
  <button class="button" onmouseup="moveDown();">Keri alla</button>
  <button class="button" onmouseup="moveUp();">Keri yles</button>
  <script>
    function toggleMotor(x) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/" + x, true);
      xhr.send();
    }

    function moveUp(x) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/move_up", true);
      xhr.send();
    }

    function moveDown(x) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/move_down", true);
      xhr.send();
    }

    function loadNextPos(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (xhr.readyState == XMLHttpRequest.DONE) {
          var x = xhr.responseText
          document.getElementById("current-position").innerHTML = x
        }
      }
      xhr.open('GET', '/get_turns', true);
      xhr.send();
    }

    function loadSavedPos(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (xhr.readyState == XMLHttpRequest.DONE) {
          var x = xhr.responseText
          document.getElementById("saved-position").innerHTML = x
        }
      }
      xhr.open('GET', '/get_saved_turns', true);
      xhr.send();
    }

    function resetTurns(x) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/reset_turns", true);
      xhr.send();
    }

    function saveTurns(x) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/save_turns", true);
      xhr.send();
    }

    loadTime();
    loadNextPos();
    loadSavedPos();
    setInterval(function(){
      loadTime();
      loadNextPos();
      loadSavedPos();
    }, 5000);
  </script>
</body>
)=====";