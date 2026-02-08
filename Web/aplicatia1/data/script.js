const updateUI = (button, span, stateText) => {
  const isOn = (stateText || "").trim().toUpperCase() === "ON";
  span.innerText = isOn ? "ON" : "OFF";
  span.classList.toggle("led-on", isOn);
  span.classList.toggle("led-off", !isOn);
  button.classList.toggle("on", isOn);
  button.classList.toggle("off", !isOn);
};

const toggleBtn = document.getElementById("toggleBtn");
const redLedStateSpan = document.getElementById("redLedState");
updateUI(toggleBtn, redLedStateSpan, redLedStateSpan.innerText);

// Toggle Red LED when button is clicked
toggleBtn.addEventListener("click", () => {
  fetch("/toggleRedLED")
    .then(response => response.text())
    .then(state => updateUI(toggleBtn, redLedStateSpan, state.split("Red LED is ")[1]))
    .catch(err => console.error(err));
});

// Auto-refresh LED state every 0.2 seconds
setInterval(() => {
  fetch("/getRedLEDState")
    .then(response => response.text())
    .then(state => updateUI(toggleBtn, redLedStateSpan, state.split("Red LED is ")[1]))
    .catch(err => console.error(err));
}, 200);
