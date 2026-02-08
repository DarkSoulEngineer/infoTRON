const toggleBtn = document.getElementById("toggleBtn");
const redLedStateSpan = document.getElementById("redLedState");

// Toggle Red LED when button is clicked
toggleBtn.addEventListener("click", () => {
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
