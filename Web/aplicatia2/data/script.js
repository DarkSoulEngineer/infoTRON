// Red LED Code
const toggleRedButton = document.getElementById("toggleRedButton");
const redLedStateSpan = document.getElementById("redLedState");

// Toggle Red LED when button is clicked
toggleRedButton.addEventListener("click", () => {
  fetch("/toggleRedLED")
    .then(response => response.text())
    .then(state => {
      redLedStateSpan.innerText = state.split("Red LED is ")[1];
    })
    .catch(err => console.error(err));
});

// Auto-refresh LED state every 0.2 seconds
setInterval(() => {
  fetch("/getRedLEDState")
    .then(response => response.text())
    .then(state => {
      redLedStateSpan.innerText = state.split("Red LED is ")[1];
    })
    .catch(err => console.error(err));
}, 200);

// Green LED Code
const toggleGreenButton = document.getElementById("toggleGreenButton");
const greenLedStateSpan = document.getElementById("greenLedState");

// Toggle Green LED when button is clicked
toggleGreenButton.addEventListener("click", () => {
  fetch("/toggleGreenLED")
    .then(response => response.text())
    .then(state => {
      greenLedStateSpan.innerText = state.split("Green LED is ")[1];
    })
    .catch(err => console.error(err));
});

// Auto-refresh LED state every 0.2 seconds
setInterval(() => {
  fetch("/getGreenLEDState")
    .then(response => response.text())
    .then(state => {
      greenLedStateSpan.innerText = state.split("Green LED is ")[1];
    })
    .catch(err => console.error(err));
}, 200);