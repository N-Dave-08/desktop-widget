const addon = require('node-gyp-build')(__dirname);

module.exports = {
  setWindowToDesktop: addon.setWindowToDesktop
};