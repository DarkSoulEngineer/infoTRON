const toggleRedButton = document.getElementById("toggleRedButton");
const redLedState = document.getElementById("redLedState");

const toggleGreenButton = document.getElementById("toggleGreenButton");
const greenLedState = document.getElementById("greenLedState");

const updateElement = (button, span, state) => {
  span.innerText = state;
  span.classList.toggle("led-on", state === "ON");
  span.classList.toggle("led-off", state !== "ON");
  button.classList.toggle("on", state === "ON");
  button.classList.toggle("off", state !== "ON");
};

// Fetch LED states
const fetchRed = async () => {
  try {
    const { redLedState: serverState } = await (await fetch("/api/getRedLEDState")).json();
    updateElement(toggleRedButton, redLedState, serverState);
  } catch(e) { console.error(e); }
};

const fetchGreen = async () => {
  try {
    const { greenLedState: serverState } = await (await fetch("/api/getGreenLEDState")).json();
    updateElement(toggleGreenButton, greenLedState, serverState);
  } catch(e) { console.error(e); }
};

// Initialize
fetchRed();
fetchGreen();

// Button clicks toggle LEDs
toggleRedButton.addEventListener("click", async () => {
  const { redLedState: serverState } = await (await fetch("/api/toggleRedLED")).json();
  updateElement(toggleRedButton, redLedState, serverState);
});

toggleGreenButton.addEventListener("click", async () => {
  const { greenLedState: serverState } = await (await fetch("/api/toggleGreenLED")).json();
  updateElement(toggleGreenButton, greenLedState, serverState);
});

// Auto-refresh
setInterval(fetchRed, 200);
setInterval(fetchGreen, 200);
