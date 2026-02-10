const picker = document.getElementById("colorPicker");
const hex = document.getElementById("hex");

function sendColor(color) {
  hex.textContent = color;
  fetch(`/setColor?value=${encodeURIComponent(color)}`).catch(err => console.error(err));
}

// Update LED when user picks a color
picker.addEventListener("input", () => {
  sendColor(picker.value);
});

// Sync picker with device color on load
window.addEventListener("load", () => {
  fetch("/getColor")
    .then(res => res.ok ? res.text() : Promise.reject(res.statusText))
    .then(color => {
        picker.value = color;
        hex.textContent = color;
      sendColor(picker.value);
    })
    .catch(err => {
      console.error(err);
    });
});