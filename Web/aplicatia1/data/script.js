const toggleRedButton = document.getElementById("toggleRedButton");
const redLedState = document.getElementById("redLedState");


const updateElement = (button, span, state) => {
  // Update text
  span.innerText = state;
  // Toggle LED text color
  span.classList.toggle("led-on", state === "ON");
  span.classList.toggle("led-off", state !== "ON");
  // Toggle button color
  button.classList.toggle("on", state === "ON");
  button.classList.toggle("off", state !== "ON");
};

// Fetch LED state and update inline
const fetchRed = async () => {
  try {
    const { redLedState: serverState } = await (await fetch("/api/getRedLEDState")).json();
    updateElement(toggleRedButton, redLedState, serverState);
  } catch(e) { console.error(e); }
};

// Initialize
fetchRed();

// Button clicks toggle directly
toggleRedButton.addEventListener("click", async () => {
  const { redLedState: serverState } = await (await fetch("/api/toggleRedLED")).json();
  updateElement(toggleRedButton, redLedState, serverState);
});

// Auto-refresh
setInterval(fetchRed, 200);