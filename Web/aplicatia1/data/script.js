const toggleBtn = document.getElementById("toggleBtn");
const ledStateSpan = document.getElementById("ledState");

// Toggle LED when button is clicked
toggleBtn.addEventListener("click", () => {
  fetch("/toggleLED")
    .then(response => response.text())
    .then(state => {
      ledStateSpan.innerText = state.split("LED is ")[1];
    })
    .catch(err => console.error(err));
});

// Auto-refresh LED state every 0.2 seconds
setInterval(() => {
  fetch("/getLEDState")
    .then(response => response.text())
    .then(state => {
      ledStateSpan.innerText = state.split("LED is ")[1];
    })
    .catch(err => console.error(err));
}, 200);
