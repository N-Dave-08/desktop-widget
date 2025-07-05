# My Widget (Electron Desktop Widget)

A transparent, always-on-desktop widget for Windows, built with Electron and native Node.js addon for true desktop pinning.

## Features
- Frameless, transparent, and non-intrusive widget
- Stays visible even when "Show desktop" is clicked
- Customizable position (top-right by default)
- Hot reload for rapid development

## Setup

1. **Clone the repository**
2. **Install dependencies:**
   ```bash
   npm install
   ```
3. **Build the native addon:**
   ```bash
   cd desktop-parent
   npx node-gyp configure
   npx node-gyp build
   cd ..
   ```

## Development (with Hot Reload)

1. **Install electronmon:**
   ```bash
   npm install --save-dev electronmon
   ```
2. **Start the app in development mode:**
   ```bash
   npx electronmon .
   ```
   Or add to your `package.json` scripts:
   ```json
   "scripts": {
     "dev": "electronmon ."
   }
   ```
   Then run:
   ```bash
   npm run dev
   ```

## Usage
- The widget appears at the top right of your primary display by default.
- To change its position, edit the `win.setPosition(x, y)` call in `main.js`.
- The widget content is in `index.html` and styled with `style.css`.

## Advanced: True Desktop Pinning
- The widget uses a native Node.js addon (`desktop-parent`) to set itself as a child of the Windows desktop (`WorkerW`/`Progman`).
- This allows it to remain visible even when "Show desktop" is clicked.
- The native addon is built with C++ and requires Windows build tools (Visual Studio Build Tools, Python, etc.).

## Troubleshooting
- If you see errors about missing Electron or native modules, ensure all dependencies are installed and the native addon is built.
- If hot reload does not work, make sure you are using `electronmon` and have removed any `electron-reload` code from `main.js`.

## License
ISC 