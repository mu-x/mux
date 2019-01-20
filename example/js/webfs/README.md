# Web Interface for File System

## Install Requirements

Node.js https://nodejs.org

```bash
    # For Ubuntu:
    curl -sL https://deb.nodesource.com/setup_11.x | sudo -E bash -
    sudo apt-get install -y nodejs
```

Node.js modules

```bash
    # Any platform:
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
    node start
```

