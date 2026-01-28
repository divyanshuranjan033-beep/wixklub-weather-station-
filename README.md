<!DOCTYPE html>
<html>
<head>
  <title>JARVIS AI</title>
</head>
<body>

<h2>JARVIS – Chrome Voice Assistant</h2>
<button onclick="startJarvis()">Start JARVIS</button>
<p id="output">Waiting...</p>

<script>
  const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
  const recognition = new SpeechRecognition();
  recognition.lang = "en-US";

  let learnStep = 0;
  let learnQuestion = "";
  let audio = new Audio();

  function speak(text) {
    const speech = new SpeechSynthesisUtterance(text);
    window.speechSynthesis.speak(speech);
  }

  function startJarvis() {
    speak("Hello, I am Jarvis. How can I help you?");
    recognition.start();
  }

  recognition.onresult = function(event) {
    const command = event.results[0][0].transcript.toLowerCase();
    document.getElementById("output").innerText = "You said: " + command;
    handleCommand(command);
  };

  function handleCommand(command) {

    // Learning mode
    if (learnStep === 1) {
      learnQuestion = command;
      speak("What should be the answer?");
      learnStep = 2;
      return;
    }

    if (learnStep === 2) {
      localStorage.setItem(learnQuestion, command);
      speak("I have learned this.");
      learnStep = 0;
      return;
    }

    if (command.includes("learn")) {
      speak("What should I learn?");
      learnStep = 1;
    }

    else if (localStorage.getItem(command)) {
      speak(localStorage.getItem(command));
    }

    // Music
    else if (command.includes("play song")) {
      speak("Playing song");
      audio.src = "https://www.soundhelix.com/examples/mp3/SoundHelix-Song-1.mp3";
      audio.play();
    }

    else if (command.includes("stop song")) {
      speak("Stopping song");
      audio.pause();
    }

    // Apps
    else if (command.includes("youtube")) {
      speak("Opening YouTube");
      window.open("https://www.youtube.com");
    }

    else if (command.includes("netflix")) {
      speak("Opening Netflix");
      window.open("https://www.netflix.com");
    }

    else if (command.includes("spotify")) {
      speak("Opening Spotify");
      window.open("https://open.spotify.com");
    }

    else if (command.includes("time")) {
      speak("The time is " + new Date().toLocaleTimeString());
    }

    else {
      speak("Sorry, I do not know this yet");
    }
  }
</script>

</body>
</html>
