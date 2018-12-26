# Web Interface for File System

## Requirements

Node.js 8: https://nodejs.org
```
    # Ubuntu
    curl -sL https://deb.nodesource.com/setup_11.x | sudo -E bash -
    sudo apt-get install -y nodejs
```

Node.js express and some other packages
```
    # Any platform
    npm install
```

## Start Server

```
    export PORT=8080    #< Default port.
    export ROOT=$HOME   #< Root directory to browse.
    node app            #< Run Server.
```
