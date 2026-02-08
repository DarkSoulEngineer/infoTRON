const updateUI = (button, span, stateText, colorClass) => {
  const isOn = (stateText || "").trim().toUpperCase() === "ON";
  span.innerText = isOn ? "ON" : "OFF";
  span.classList.toggle("led-on", isOn);
  span.classList.toggle("led-off", !isOn);
  button.classList.toggle("on", isOn);
  button.classList.toggle("off", !isOn);
  button.classList.add(colorClass);
};

// Red LED Code
const toggleRedButton = document.getElementById("toggleRedButton");
const redLedStateSpan = document.getElementById("redLedState");
updateUI(toggleRedButton, redLedStateSpan, redLedStateSpan.innerText, "red");

toggleRedButton.addEventListener("click", () => {
  fetch("/toggleRedLED")
    .then(response => response.text())
    .then(state => updateUI(toggleRedButton, redLedStateSpan, state.split("Red LED is ")[1], "red"))
    .catch(err => console.error(err));
});

setInterval(() => {
  fetch("/getRedLEDState")
    .then(response => response.text())
    .then(state => updateUI(toggleRedButton, redLedStateSpan, state.split("Red LED is ")[1], "red"))
    .catch(err => console.error(err));
}, 200);

// Green LED Code
const toggleGreenButton = document.getElementById("toggleGreenButton");
const greenLedStateSpan = document.getElementById("greenLedState");
updateUI(toggleGreenButton, greenLedStateSpan, greenLedStateSpan.innerText, "green");

toggleGreenButton.addEventListener("click", () => {
  fetch("/toggleGreenLED")
    .then(response => response.text())
    .then(state => updateUI(toggleGreenButton, greenLedStateSpan, state.split("Green LED is ")[1], "green"))
    .catch(err => console.error(err));
});

setInterval(() => {
  fetch("/getGreenLEDState")
    .then(response => response.text())
    .then(state => updateUI(toggleGreenButton, greenLedStateSpan, state.split("Green LED is ")[1], "green"))
    .catch(err => console.error(err));
}, 200);
