const unix = require("./install_unix.js");

process.on("exit", code => {
  if (code === 1) {
    console.log("Installation aborted.\n\n");
  }
});
unix();
