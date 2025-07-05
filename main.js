require('electron-reload')(__dirname, {
    electron: require('path').join(__dirname, 'node_modules', '.bin', 'electron.cmd')
  });
const { app, BrowserWindow, ipcMain, screen } = require('electron');
const path = require('path');
const { setWindowToDesktop } = require('./desktop-parent');

function createWindow() {
  const win = new BrowserWindow({
    width: 300,
    height: 200,
    frame: false,
    transparent: true,
    resizable: false,
    skipTaskbar: true,
    alwaysOnTop: false,
    webPreferences: {
      nodeIntegration: false,
      contextIsolation: true,
      preload: path.join(__dirname, 'preload.js')
    }
  });

  // Position at top right corner
  const { width: displayWidth } = screen.getPrimaryDisplay().workAreaSize;
  win.setPosition(displayWidth - 310, 10);

  win.loadFile('index.html');

  // Try to set the window to desktop level using Electron's built-in methods
  win.once('ready-to-show', () => {
    const hwndBuffer = win.getNativeWindowHandle();
    setWindowToDesktop(hwndBuffer);
  });

  win.setMenu(null);
  return win;
}

app.whenReady().then(createWindow);

ipcMain.on('drag-window', (event, dx, dy) => {
  const win = BrowserWindow.getFocusedWindow();
  if (win) {
    const [x, y] = win.getPosition();
    win.setPosition(x + dx, y + dy);
  }
});
