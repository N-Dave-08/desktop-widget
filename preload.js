const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('electronAPI', {
  dragWindow: (dx, dy) => ipcRenderer.send('drag-window', dx, dy)
}); 