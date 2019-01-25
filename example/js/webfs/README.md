# Web Interface for File System

Fast and simple but stylish web interface for your file system.

Core Features:

- Provides image previews to speed up manual search of photos.
- Works as fast as JavaScript can (no heavy frameworks are used).
- Supports all modern browsers e.g. Chorme, FireFox and Edge.

## Requirements

Node.js 11:

- For any platform: download and install from https://nodejs.org
- For ubuntu and debian:
    ```bash
        curl -sL https://deb.nodesource.com/setup_11.x | sudo -E bash -
        sudo apt-get install -y nodejs
    ```

Node.js modules:

```bash
    npm install
```

## Run Tests

Just to be sure your version is good to go.

```bash
    npm test
```

## Start Server

In this example environment variables are set to default.

```bash
    export PORT=8081
    export ROOT=$HOME
    npm start
```

Than open http://localhost:8081 in your browser and see WebFS in action.

## Developent Plans

- Configurable grid preview sizes (128, 64, 32px).
- Separate preview side bar for selected items description.
- Full screen preview in modal layer.
- Upload, delete, rename, copy and move buttons in preview side bar.
- Drag & drop uploads (and downloads if possible).
- Download and upload directories as ZIP archives.
- Advanced previews (directory content, text and video files).
- Use HTML5 player for video files.
- File search by name patterns.
